;NSIS Modern User Interface
;Basic Example Script
;Written by Joost Verburg

;--------------------------------
;Include Modern UI

!include "MUI2.nsh"

;--------------------------------
;General

!addplugindir "."

  ;Name and file
  Name "Modern UI Test"
  OutFile "Inetc.exe"

  ;Default installation folder
  InstallDir "$LOCALAPPDATA\Modern UI Test"
  
  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\Modern UI Test" ""

  ;Request application privileges for Windows Vista
  RequestExecutionLevel user
  
  SetCompressor lzma
  
;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "Dummy Section" SecDummy

	Inetc::get /NOUNLOAD /NOCOOKIES /NOCANCEL /SILENT /TOSTACK /RESUME "" "https://yadi.sk/i/akG8GkPssSQCUg" "" /END
	Pop $0
	Pop $1
	DetailPrint $1
	Inetc::get /NOUNLOAD /NOCOOKIES /NOCANCEL /SILENT /TOSTACK /RESUME "" "https://yadi.sk/d/djTuVOBvEyv1ow" "" /END
	Pop $0
	Pop $1
	DetailPrint $1

SectionEnd


;--------------------------------
;Uninstaller Section


Function .onInit
	
FunctionEnd
