#include "CppDebug.h"

#include <tchar.h>
#include <strsafe.h>
#include <shlwapi.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <clocale>
using namespace std;

typedef std::basic_string<TCHAR> _tstring;
typedef std::basic_fstream<TCHAR, std::char_traits<TCHAR> > _tfstream;
typedef std::basic_ofstream<TCHAR, std::char_traits<TCHAR> > _tofstream;
typedef basic_ostringstream<TCHAR, char_traits<TCHAR>, allocator<TCHAR> > _tostringstream;


#define MAX_ERROR_STRING 255
// #define PRINT_DATETIME

CppDebug::CppDebug(void) {
}

CppDebug::~CppDebug(void) {
}

LPTSTR g_logFileName = NULL;

LPTSTR CppDebug::getLogFileName() {
    
    if(g_logFileName == NULL) {
        g_logFileName = (LPTSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_PATH * sizeof(TCHAR));

        HMODULE hModule = GetModuleHandle(NULL);
        TCHAR lptFileName[MAX_PATH];
        ZeroMemory(lptFileName, MAX_PATH * sizeof(TCHAR));
        GetModuleFileName(hModule, lptFileName, MAX_PATH);
        PathRemoveFileSpec(lptFileName);
        
        StringCchCat(lptFileName, MAX_PATH, TEXT("\\debug.txt"));
        StringCbCopy(g_logFileName, MAX_PATH * sizeof(TCHAR), lptFileName);

        return g_logFileName;
    } else {
        return g_logFileName;
    }
    
    
}


void CppDebug::log(LPCTSTR arg) {

	_tfstream outFileStream;

	outFileStream.open(getLogFileName(), _tfstream::binary | _tfstream::app);
	if (outFileStream.is_open()) {
#		ifdef PRINT_DATETIME
			tm tmDest;
			time_t now;
			time(&now);
			TCHAR buf[1024];
			gmtime_s(&tmDest, &now);
			_tcsftime(buf, 1024, TEXT("%Y-%m-%dT%H:%M:%SZ "), &tmDest);
			outFileStream << buf;
#		endif
		outFileStream << arg << std::endl;
		outFileStream.close();
	}

}


void CppDebug::log(INT arg) {

	_tstring strMessage = TEXT("");
	_tostringstream stream;
	stream << arg;
	strMessage.assign(stream.str());
	log(strMessage.data());

}

void CppDebug::log(LONG arg) {

	_tstring strMessage = TEXT("");
	_tostringstream stream;
	stream << arg;
	strMessage.assign(stream.str());
	log(strMessage.data());

}


void CppDebug::log(DWORD arg) {

	_tstring strMessage = TEXT("");
	_tostringstream stream;
	stream << arg;
	strMessage.assign(stream.str());
	log(strMessage.data());

}


void CppDebug::log(const char *file, int line, LPCTSTR message, HRESULT hr) {
    
    size_t cchDest = MAX_ERROR_STRING;
    TCHAR pszDest[MAX_ERROR_STRING];
    LPCTSTR pszFormat = TEXT("%s:%d: %s: 0x%08lx\n");
    
    wchar_t *wcFile;
    size_t size = strlen(file) + 1;
    wcFile = new wchar_t[size];
    size_t outSize;
    mbstowcs_s(&outSize, wcFile, size, file, strlen(file) - 1);
    
    HRESULT hres = StringCchPrintf(
        pszDest, cchDest, pszFormat, wcFile, line, message, hr
    );
    
    CppDebug::log(pszDest);
    
}


void CppDebug::log(const CppException *exception) {
    
    size_t cchDest = MAX_ERROR_STRING;
    TCHAR pszDest[MAX_ERROR_STRING];
    
    if( (exception->wcFilePath != NULL) && (exception->iLineCode > 0) ) {
        
        LPCTSTR pszFormat = TEXT("%s:%d: %s: 0x%08lx\n");
        
        HRESULT hres = StringCchPrintf(
            pszDest, cchDest, pszFormat, exception->wcFilePath,
            exception->iLineCode, exception->wcError, exception->herr
        );
        
    } else {
        
        LPCTSTR pszFormat = TEXT("%s: 0x%08lx\n");
        
        HRESULT hres = StringCchPrintf(
            pszDest, cchDest, pszFormat, exception->wcError, exception->herr
        );
        
    }
    
    CppDebug::log(pszDest);
    
}
