#include <string>
int Main2(int numArgs, char *args[]);
void * OpenFile7z(const char *path, bool & PasswordIsDefined);
unsigned int GetNumFiles7z(void * _context);
unsigned IsDir7z(void * _context, unsigned int _index);
void ClozeFile7z(void * _context);
bool GetName7z(void * _context, unsigned int _index, std::wstring & _tmp_str);
uint32_t GetAttrib7z(void * _context, unsigned int _index);
uint64_t GetSize7z(void * _context, unsigned int _index);
uint64_t GetPackSize7z(void * _context, unsigned int _index);
uint32_t GetCRC7z(void * _context, unsigned int _index);
void GetCTime7z(void * _context, unsigned int _index, FILETIME & ftc);
void GetMTime7z(void * _context, unsigned int _index, FILETIME & ftm);
