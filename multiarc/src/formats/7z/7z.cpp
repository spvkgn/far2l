/*
  7z.cpp

  Second-level plugin module for FAR Manager and MultiArc plugin

  Copyright (c) 1996 Eugene Roshal
  Copyrigth (c) 2000 FAR group
  Copyrigth (c) 2016 elfmz
*/
#define _UNICODE
#include <windows.h>
#include <utils.h>
#include <string.h>
#if !defined(__APPLE__) && !defined(__FreeBSD__)
# include <malloc.h>
#endif
#include <stddef.h>
#include <memory.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <vector>
#include <exception>
#include <stdexcept>
#include <farplug-mb.h>
using namespace oldfar;
#include "fmt.hpp"

#include "7zcommon.h"

#if defined(__BORLANDC__)
  #pragma option -a1
#elif defined(__GNUC__) || (defined(__WATCOMC__) && (__WATCOMC__ < 1100)) || defined(__LCC__)
  #pragma pack(1)
#else
  #pragma pack(push,1)
  #if _MSC_VER
    #define _export
  #endif
#endif


static FARAPIMESSAGE       FarMessage = NULL;
static INT_PTR             FarModuleNumber = 0;

struct PluginStartupInfo gInfo;

/////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define PYPLUGIN_DEBUGLOG "/tmp/far2.7z.cpp.log"
#if !defined(__APPLE__) && !defined(__FreeBSD__)
# include <alloca.h>
#endif

static void z_log(const char *function, unsigned int line, const char *format, ...)
{
    va_list args;
    char *xformat = (char *)alloca(strlen(format) + strlen(function) + 64);
    sprintf(xformat, "[7Z]: %s@%u%s%s",
        function, line, (*format != '\n') ? " - " : "", format);

    FILE *stream = nullptr;
    if (PYPLUGIN_DEBUGLOG[0]) {
        stream = fopen(PYPLUGIN_DEBUGLOG, "at");
    }
    if (!stream) {
        stream = stderr;
    }
    va_start(args, format);
    vfprintf(stream, xformat, args);
    va_end(args);

    if (stream != stderr) {
        fclose(stream);
    }
}

#define Z_LOG(args...) z_log(__FUNCTION__, __LINE__, args)

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "../../marclng.hpp"

class Traverser
{
	std::wstring _tmp_str;
	unsigned int _index;
	bool _valid, _passwordIsDefined;
	void * _context;
	static char ArchPassword[512];
	struct stat _archStat;

	bool GetFileStat(const char *path, struct stat * fileStat)
	{
		int filedes = open(path, O_RDONLY);
		if( filedes > 0 ) {
			int res = fstat(filedes, fileStat);
			close(filedes);
			if( res == 0 )
				return true;
		}
		return false;
	}
public:
	Traverser(const char *path) : _index(0), _valid(false), _context(nullptr)
	{
		Z_LOG("Traverser()\n");
		if( !GetFileStat(path, &_archStat) )
			return;
		memset(ArchPassword, 0, sizeof(ArchPassword));
		_context = OpenFile7z(path, _passwordIsDefined);
		if ( _context != nullptr )
			_valid = true;
		else {
			const char *NamePtr = path;
			while(*path) {
				if(*path=='/')
				NamePtr=path+1;
				path++;
			}
			std::string title = "MultiArc: ";
			title += NamePtr;
			const char *MsgItems[] = { title.c_str(), (const char*)gInfo.GetMsg(gInfo.ModuleNumber, MAddPswNotMatch)};
			gInfo.Message(gInfo.ModuleNumber, FMSG_WARNING | FMSG_MB_OK, NULL, MsgItems, ARRAYSIZE(MsgItems), 0);
		}
	}

	friend std::wstring CryptoGetTextPassword(const wchar_t * archive);
	
	~Traverser()
	{
		Z_LOG("~Traverser()\n");
		if (_context) {
			ClozeFile7z(_context);
			_context = nullptr;
			memset(ArchPassword, 0, sizeof(ArchPassword));
		}
	}
	
	bool Valid() const
	{
		Z_LOG("Valid() %u\n", _valid);
		return _valid;
	}

	bool IsSameFile(const char *path) {
		if( !Valid() )
			return false;
		struct stat fileStat;
		if( !GetFileStat(path, &fileStat) )
			return false;
		return ( fileStat.st_dev == _archStat.st_dev && fileStat.st_ino == _archStat.st_ino
#ifdef __APPLE__
			  && memcmp(&fileStat.st_mtimespec, &_archStat.st_mtimespec, sizeof(fileStat.st_mtimespec)) == 0
			  && memcmp(&fileStat.st_ctimespec, &_archStat.st_ctimespec, sizeof(fileStat.st_ctimespec)) == 0
#else
			  && memcmp(&fileStat.st_mtim, &_archStat.st_mtim, sizeof(fileStat.st_mtim)) == 0
			  && memcmp(&fileStat.st_ctim, &_archStat.st_ctim, sizeof(fileStat.st_ctim)) == 0
#endif
			);
	}
	
	int Next(struct PluginPanelItem *Item, struct ArcItemInfo *Info)
	{
		Z_LOG("Next()\n");
		if (!_valid)
			return GETARC_READERROR;

		unsigned is_dir = 0;
		DWORD attribs = 0;
		uint64_t file_size = 0;
		uint64_t packed_size = 0;
		DWORD crc32 = 0;
		FILETIME ftm = {}, ftc = {};

		if ( _context != nullptr ) {
			if (_index >= GetNumFiles7z(_context))
				return GETARC_EOF;
			is_dir = IsDir7z(_context, _index);
			if ( !GetName7z(_context, _index, _tmp_str) )
				return GETARC_READERROR;
			attribs = (DWORD)GetAttrib7z(_context, _index);
			file_size = GetSize7z(_context, _index);
			packed_size = GetPackSize7z(_context, _index);
			crc32 = (DWORD)GetCRC7z(_context,_index);
			GetCTime7z(_context, _index, ftc);
			GetMTime7z(_context, _index, ftm);
			Z_LOG("file: %S attribs: 0x%08X size: %llu pack size: %llu crc32: 0x%08X\n", _tmp_str.c_str(), attribs, file_size, packed_size, crc32);
		}

		const std::string &name = StrWide2MB(_tmp_str);
		++_index;
		
		attribs&=~ (FILE_ATTRIBUTE_BROKEN | FILE_ATTRIBUTE_EXECUTABLE);
		strncpy(Item->FindData.cFileName, name.c_str(), ARRAYSIZE(Item->FindData.cFileName)-1);
		Item->FindData.dwFileAttributes = attribs;
		Item->FindData.dwUnixMode = is_dir ? 0755 : 0644;
		Item->FindData.nFileSize = file_size;
		Item->FindData.nPhysicalSize = packed_size;
		Item->CRC32 = crc32;
		
		Item->FindData.ftLastWriteTime = ftm;
		Item->FindData.ftCreationTime = ftc;
		

		Info->Solid = 0;
		Info->Comment = 0;
		Info->Encrypted = _passwordIsDefined;
		Info->DictSize = 0;
		Info->UnpVer = 0;		
		
		return GETARC_SUCCESS;
	}
};

///////////////////////////////////
char Traverser::ArchPassword[512];
int WINAPI GetPassword(char *Password,const char *FileName);
std::wstring CryptoGetTextPassword(const wchar_t * archive)
{
	std::wstring pass;
	if( !Traverser::ArchPassword[0] ) {
		const std::string &title = StrWide2MB(std::wstring(archive));
		if( !GetPassword(Traverser::ArchPassword,title.c_str()) ) {
			const char *MsgItems[] = { title.c_str(), "can't open without password" };
			gInfo.Message(gInfo.ModuleNumber, FMSG_WARNING | FMSG_MB_OK, NULL, MsgItems, ARRAYSIZE(MsgItems), 0);
			return pass;
		}
	}
	pass = MB2Wide(Traverser::ArchPassword);
	return pass;
}

static Traverser *s_selected_traverser = NULL;
BOOL WINAPI _export SEVENZ_IsArchive(const char *Name,const unsigned char *Data,int DataSize)
{
	Z_LOG("SEVENZ_IsArchive()\n");
	if(s_selected_traverser && s_selected_traverser->IsSameFile(Name))
		return TRUE;

	Traverser *t = new Traverser(Name);
	if (!t->Valid()) {
		delete t;
		s_selected_traverser = NULL;
		return FALSE;
	}

	delete s_selected_traverser;
	s_selected_traverser = t;
	return TRUE;
/*
static const unsigned char s_magic_of_7z[] = {'7', 'z', 0xBC, 0xAF, 0x27, 0x1C, 0x00};//last byte actually k7zMajorVersion
	if (DataSize < (int)sizeof(s_magic_of_7z) || memcmp(Data, s_magic_of_7z, sizeof(s_magic_of_7z))!=0) {
		return FALSE;
	}

	return TRUE;
*/
}


BOOL WINAPI _export SEVENZ_OpenArchive(const char *Name,int *Type,bool Silent)
{
	Z_LOG("SEVENZ_OpenArchive()\n");
	if (!s_selected_traverser)
		return FALSE;
	return TRUE;
}



int WINAPI _export SEVENZ_GetArcItem(struct PluginPanelItem *Item, struct ArcItemInfo *Info)
{
	Z_LOG("SEVENZ_GetArcItem()\n");
	if (!s_selected_traverser)
		return GETARC_READERROR;
		
	return s_selected_traverser->Next(Item, Info);
}


BOOL WINAPI _export SEVENZ_CloseArchive(struct ArcInfo *Info)
{
	Z_LOG("SEVENZ_CloseArchive()\n");
	if (!s_selected_traverser)
		return FALSE;
		
	delete s_selected_traverser;
	s_selected_traverser = NULL;
	return TRUE;
}

void  WINAPI _export SEVENZ_SetFarInfo(const struct PluginStartupInfo *Info)
{
   Z_LOG("Info %p\n", Info);
   gInfo = *Info;
   FarMessage = Info->Message;
   FarModuleNumber = Info->ModuleNumber;
}

BOOL WINAPI _export SEVENZ_GetFormatName(int Type,char *FormatName,char *DefaultExt)
{
	Z_LOG("SEVENZ_GetFormatName()\n");
  if (Type==0)
  {
    strcpy(FormatName,"7Z");
    strcpy(DefaultExt,"7z");
    return TRUE;
  }
  return FALSE;
}

BOOL WINAPI _export SEVENZ_GetDefaultCommands(int Type,int Command,char *Dest)
{
	Z_LOG("SEVENZ_GetDefaultCommands() Type %i Command %i\n", Type, Command);
  if (Type==0)
  {
    static const char *Commands[]={
    /*Extract               */"^7z x %%A %%FMq*4096",
    /*Extract without paths */"^7z e {-p%%P} %%A %%FMq*4096",
    /*Test                  */"^7z t %%A",
    /*Delete                */"^7z d {-p%%P} %%A @%%LN",
    /*Comment archive       */"",
    /*Comment files         */"",
    /*Convert to SFX        */"",
    /*Lock archive          */"",
    /*Protect archive       */"",
    /*Recover archive       */"",
    /*Add files             */"^7z a -y {-p%%P} %%A @%%LN",
    /*Move files            */"^7z a -y -sdel {-p%%P} %%A @%%LN",
    /*Add files and folders */"^7z a -y -r {-p%%P} %%A @%%LN",
    /*Move files and folders*/"^7z a -y -r -sdel {-p%%P} %%A @%%LN",
    /*"All files" mask      */"*"
    };
    if (Command<(int)(ARRAYSIZE(Commands)))
    {
      strcpy(Dest,Commands[Command]);
      return(TRUE);
    }
  }
  return(FALSE);
}
