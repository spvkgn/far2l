/*
  7zcommon.cpp
  Common plugin module for FAR Manager and MultiArc plugin
  Copyrigth (c) 2022 VPROFi
*/

#include "./CPP/Common/MyWindows.h"
#include "./CPP/Common/Common.h"

#ifdef _WIN32
#include <Psapi.h>
#else
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/times.h>
#endif

#include "./CPP/../C/CpuArch.h"

//#include "./CPP/Common/MyInitGuid.h"

#include "./CPP/Common/CommandLineParser.h"
#include "./CPP/Common/IntToString.h"
#include "./CPP/Common/MyException.h"
#include "./CPP/Common/StdInStream.h"
#include "./CPP/Common/StdOutStream.h"
#include "./CPP/Common/StringConvert.h"
#include "./CPP/Common/StringToInt.h"
#include "./CPP/Common/UTFConvert.h"

#include "./CPP/Windows/ErrorMsg.h"
#include "./CPP/Windows/TimeUtils.h"

//#include "../Common/ArchiveCommandLine.h"
//#include "../Common/Bench.h"
//#include "../Common/ExitCode.h"
//#include "../Common/Extract.h"

//#ifdef EXTERNAL_CODECS
//#include "../Common/LoadCodecs.h"
//#endif

#include "./CPP/7zip/Common/RegisterCodec.h"

//#include "BenchCon.h"
//#include "ConsoleClose.h"
//#include "ExtractCallbackConsole.h"
//#include "HashCon.h"
//#include "List.h"
//#include "OpenCallbackConsole.h"
//#include "UpdateCallbackConsole.h"

#ifdef PROG_VARIANT_R
#include "./CPP/../C/7zVersion.h"
#else
#include "./CPP/7zip/MyVersion.h"
#endif

#if defined(PROG_VARIANT_Z)
  #define PROG_POSTFIX      "z"
  #define PROG_POSTFIX_2  " (z)"
#elif defined(PROG_VARIANT_R)
  #define PROG_POSTFIX      "r"
  #define PROG_POSTFIX_2  " (r)"
#elif !defined(EXTERNAL_CODECS)
  #define PROG_POSTFIX      "a"
  #define PROG_POSTFIX_2  " (a)"
#else
  #define PROG_POSTFIX    ""
  #define PROG_POSTFIX_2  ""
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define PYPLUGIN_DEBUGLOG "/tmp/far2.7zcommon.cpp.log"
#if !defined(__APPLE__) && !defined(__FreeBSD__)
# include <alloca.h>
#endif

static void z_log(const char *function, unsigned int line, const char *format, ...)
{
    va_list args;
    char *xformat = (char *)alloca(strlen(format) + strlen(function) + 64);
    sprintf(xformat, "[7ZCOMMON]: %s@%u%s%s",
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

#include "./CPP/7zip/UI/Common/LoadCodecs.h"
#include "./CPP/7zip/UI/Common/HashCalc.h"
#include "./CPP/7zip/UI/Console/OpenCallbackConsole.h"
#include "./CPP/Common/StdOutStream.h"
#include "./CPP/7zip/PropID.h"
#include "./CPP/Windows/PropVariantConv.h"

#include <time.h>

static time_t FileTime_to_POSIX(FILETIME ft)
{
    FILETIME localFileTime;
    FileTimeToLocalFileTime(&ft,&localFileTime);
    SYSTEMTIME sysTime;
    FileTimeToSystemTime(&localFileTime,&sysTime);
    struct tm tmtime = {0};
    tmtime.tm_year = sysTime.wYear - 1900;
    tmtime.tm_mon = sysTime.wMonth - 1;
    tmtime.tm_mday = sysTime.wDay;
    tmtime.tm_hour = sysTime.wHour;
    tmtime.tm_min = sysTime.wMinute;
    tmtime.tm_sec = sysTime.wSecond;
    tmtime.tm_wday = 0;
    tmtime.tm_yday = 0;
    tmtime.tm_isdst = -1;
    time_t ret = mktime(&tmtime);
    return ret;
}

#include "7zcommon.h"

class COpenCallbackFar2l: public IOpenCallbackUI
{
protected:

public:

  bool PasswordIsDefined;
  UString Password;
  UString Archive;

  bool MultiArcMode;

  void ClosePercents();

  COpenCallbackFar2l():
      PasswordIsDefined(false)
  {
    Password.Empty();
  }

  virtual ~COpenCallbackFar2l() {}
  
  void Init(const char * archive)
  {
	Archive = archive;
  }

  INTERFACE_IOpenCallbackUI(;)
};

//#include "showpassdialog.h"
std::wstring CryptoGetTextPassword(const wchar_t * archive);

HRESULT COpenCallbackFar2l::Open_CryptoGetTextPassword(BSTR *password)
{
  Z_LOG("\n");
  *password = NULL;
  if (!PasswordIsDefined)
  {
    std::wstring pass = CryptoGetTextPassword(Archive.Ptr(Archive.ReverseFind_PathSepar()+1));
    Password = pass.c_str();
    PasswordIsDefined = true;
  }
  return StringToBstr(Password, password);
}

HRESULT COpenCallbackFar2l::Open_Finished()
{
  Z_LOG("\n");
  return S_OK;
}

HRESULT COpenCallbackFar2l::Open_CheckBreak()
{
  Z_LOG("\n");
  return S_OK;
}

HRESULT COpenCallbackFar2l::Open_SetTotal(const UInt64 *files, const UInt64 *bytes)
{
  if(bytes && files) {
    Z_LOG("files %llu, bytes %llu\n", *files, *bytes);
  } else if(bytes) {
    Z_LOG("bytes %llu\n", *bytes);
  } else {
    Z_LOG("files %p, bytes %p\n", files, bytes);
  }
  return S_OK;
}

HRESULT COpenCallbackFar2l::Open_SetCompleted(const UInt64 *files, const UInt64 *bytes)
{
  if(bytes && files) {
    Z_LOG("files %llu, bytes %llu\n", *files, *bytes);
  } else if(bytes) {
    Z_LOG("bytes %llu\n", *bytes);
  } else {
    Z_LOG("files %p, bytes %p\n", files, bytes);
  }
  return S_OK;
}

extern
CStdOutStream *g_StdStream;
CStdOutStream *g_StdStream = &g_StdOut;
extern
CStdOutStream *g_ErrStream;
CStdOutStream *g_ErrStream = &g_StdErr;

void * OpenFile7z(const char *path, bool & passwordIsDefined)
{
	Z_LOG("... %s\n", path);

	CREATE_CODECS_OBJECT
	codecs->CaseSensitiveChange = false;
	codecs->CaseSensitive = false;

	HRESULT res = codecs->Load();
	if( res != S_OK) {
		Z_LOG("... codecs->Load() error %u\n", res);
		return nullptr;
	}
	Codecs_AddHashArcHandler(codecs);

	CArchiveLink * arcLink = new CArchiveLink();

	COpenOptions options;
	options.codecs = codecs;
	CObjectVector<COpenType> types;
	options.types = &types;
	CIntVector excludedFormats;
	options.excludedFormats = &excludedFormats;
	options.stdInMode = false;
	options.stream = NULL;
	options.filePath = UString(path);
	CObjectVector<CProperty> Properties;
	options.props = &Properties;

	COpenCallbackFar2l openCallbackFar2l;
	openCallbackFar2l.Init(path);
	res = arcLink->Open_Strict(options, &openCallbackFar2l);
	if( res != S_OK) {
		Z_LOG("... arcLink->Open_Strict(%s) error %u\n", path, res);
		return nullptr;
	}

	passwordIsDefined = openCallbackFar2l.PasswordIsDefined;

	const CArc &arc = arcLink->Arcs.Back();
	IInArchive *archive = arc.Archive;
	UInt32 numItems;
	archive->GetNumberOfItems(&numItems);
	Z_LOG("... numItems %u\n", numItems);
	CReadArcItem item;
	for (UInt32 i = 0; i < numItems; i++)
	{
		UString FilePath;
		HRESULT res = arc.GetItemPath2(i, FilePath);
		if (arc.Ask_Aux)
		{
			bool isAux;
			Archive_IsItem_Aux(archive, i, isAux);
			if (isAux) {
				Z_LOG("isAux: %S \n", FilePath.Ptr());
				continue;
			}
		}

		bool isAltStream = false;
		if (arc.Ask_AltStream)
		{
			Archive_IsItem_AltStream(archive, i, isAltStream);
			if (isAltStream) {
				Z_LOG("isAltStream: %S \n", FilePath.Ptr());
				//continue;
			}
		}

		bool isDir = false;
		Archive_IsItem_Dir(archive, i, isDir);
		if( isDir ) {
			Z_LOG("isDir: %S \n", FilePath.Ptr());
			continue;
		}

		NWindows::NCOM::CPropVariant prop;

		UInt64 Size;
		UInt64 PackSize;
		FILETIME MTime;

		archive->GetProperty(i, kpidSize, &prop);
		ConvertPropVariantToUInt64(prop, Size);

		archive->GetProperty(i, kpidPackSize, &prop);
		ConvertPropVariantToUInt64(prop, PackSize);


		archive->GetProperty(i, kpidMTime, &prop);
		MTime = prop.filetime;
		time_t time_t_var = FileTime_to_POSIX(MTime);

		Z_LOG("file: %S size: %llu pack size: %llu time: %s\n", FilePath.Ptr(), Size, PackSize, ctime( &time_t_var ));
	}
	Z_LOG("arcLink %p\n", arcLink);
	return arcLink;
}
void ClozeFile7z(void * _context)
{
	CArchiveLink * arcLink = (CArchiveLink*)_context;
	delete arcLink;
}

unsigned int GetNumFiles7z(void * _context)
{
	CArchiveLink * arcLink = (CArchiveLink*)_context;
	const CArc &arc = arcLink->Arcs.Back();
	IInArchive *archive = arc.Archive;
	UInt32 numItems;
	archive->GetNumberOfItems(&numItems);
	Z_LOG("... numItems %u\n", numItems);
	return (unsigned int)numItems;
}

unsigned IsDir7z(void * _context, unsigned int _index)
{
	CArchiveLink * arcLink = (CArchiveLink*)_context;
	const CArc &arc = arcLink->Arcs.Back();
	IInArchive *archive = arc.Archive;
	bool isDir = false;
	Archive_IsItem_Dir(archive, _index, isDir);
	Z_LOG("isDir: %u\n", isDir);
	return isDir;
}

bool GetName7z(void * _context, unsigned int _index, std::wstring & _tmp_str)
{
	CArchiveLink * arcLink = (CArchiveLink*)_context;
	const CArc &arc = arcLink->Arcs.Back();
	UString FilePath;
	HRESULT res = arc.GetItemPath2(_index, FilePath);
	if( res != S_OK) {
		Z_LOG("... codecs->Load() error %u\n", res);
		return false;
	}
	_tmp_str = std::wstring(FilePath.Ptr());
	Z_LOG("file: %S\n", _tmp_str.c_str());
	return true;
}

uint32_t GetAttrib7z(void * _context, unsigned int _index)
{
	CArchiveLink * arcLink = (CArchiveLink*)_context;
	const CArc &arc = arcLink->Arcs.Back();
	IInArchive *archive = arc.Archive;

	NWindows::NCOM::CPropVariant prop;
	archive->GetProperty(_index, kpidAttrib, &prop);
	if (prop.vt == VT_EMPTY || prop.vt != VT_UI4)
		return 0;
	return prop.ulVal;
}

uint64_t GetSize7z(void * _context, unsigned int _index)
{
	CArchiveLink * arcLink = (CArchiveLink*)_context;
	const CArc &arc = arcLink->Arcs.Back();
	IInArchive *archive = arc.Archive;

	NWindows::NCOM::CPropVariant prop;
	archive->GetProperty(_index, kpidSize, &prop);
	UInt64 Size = 0;
	ConvertPropVariantToUInt64(prop, Size);
	return Size;
}

uint64_t GetPackSize7z(void * _context, unsigned int _index)
{
	CArchiveLink * arcLink = (CArchiveLink*)_context;
	const CArc &arc = arcLink->Arcs.Back();
	IInArchive *archive = arc.Archive;

	NWindows::NCOM::CPropVariant prop;
	archive->GetProperty(_index, kpidPackSize, &prop);
	UInt64 PackSize;
	ConvertPropVariantToUInt64(prop, PackSize);
	return PackSize;
}

uint32_t GetCRC7z(void * _context, unsigned int _index)
{
	CArchiveLink * arcLink = (CArchiveLink*)_context;
	const CArc &arc = arcLink->Arcs.Back();
	IInArchive *archive = arc.Archive;

	NWindows::NCOM::CPropVariant prop;
	archive->GetProperty(_index, kpidCRC, &prop);
	if (prop.vt == VT_EMPTY || prop.vt != VT_UI4)
		return 0;
	return prop.ulVal;
}

void GetCTime7z(void * _context, unsigned int _index, FILETIME & ftc)
{
	CArchiveLink * arcLink = (CArchiveLink*)_context;
	const CArc &arc = arcLink->Arcs.Back();
	IInArchive *archive = arc.Archive;
	NWindows::NCOM::CPropVariant prop;
	archive->GetProperty(_index, kpidCTime, &prop);
	ftc = prop.filetime;
	return;
}

void GetMTime7z(void * _context, unsigned int _index, FILETIME & ftm)
{
	CArchiveLink * arcLink = (CArchiveLink*)_context;
	const CArc &arc = arcLink->Arcs.Back();
	IInArchive *archive = arc.Archive;
	NWindows::NCOM::CPropVariant prop;
	archive->GetProperty(_index, kpidMTime, &prop);
	ftm = prop.filetime;
	return;
}

extern "C" int sevenz_main(int numargs, char *args[])
{
	return Main2(numargs, args);
}
