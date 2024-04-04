# Microsoft Developer Studio Project File - Name="Tierazon" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Tierazon - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Tierazon.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Tierazon.mak" CFG="Tierazon - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Tierazon - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Tierazon - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Tierazon - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 vfw32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Tierazon - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 vfw32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Tierazon - Win32 Release"
# Name "Tierazon - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Cmplx.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorMethods.cpp
# End Source File
# Begin Source File

SOURCE=.\Convolut.cpp
# End Source File
# Begin Source File

SOURCE=.\Dib.cpp
# End Source File
# Begin Source File

SOURCE=.\Formulae.cpp
# End Source File
# Begin Source File

SOURCE=.\Fparams.cpp
# End Source File
# Begin Source File

SOURCE=.\gradient.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Movie.cpp
# End Source File
# Begin Source File

SOURCE=.\Orient.cpp
# End Source File
# Begin Source File

SOURCE=.\Pattern.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Tierazon.cpp
# End Source File
# Begin Source File

SOURCE=.\Tierazon.rc

!IF  "$(CFG)" == "Tierazon - Win32 Release"

!ELSEIF  "$(CFG)" == "Tierazon - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TierazonDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\TierazonView.cpp
# End Source File
# Begin Source File

SOURCE=.\Unique.cpp
# End Source File
# Begin Source File

SOURCE=.\Xysize.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\Dib.h
# End Source File
# Begin Source File

SOURCE=.\Expression.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Movie.h
# End Source File
# Begin Source File

SOURCE=.\Orient.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Tierazon.h
# End Source File
# Begin Source File

SOURCE=.\TierazonDoc.h
# End Source File
# Begin Source File

SOURCE=.\TierazonView.h
# End Source File
# Begin Source File

SOURCE=.\Unique.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\Tierazon.ico
# End Source File
# Begin Source File

SOURCE=.\res\Tierazon.rc2
# End Source File
# Begin Source File

SOURCE=.\res\TierazonDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section Tierazon : {A82AB342-BB35-11CF-8771-00A0C9039735}
# 	1:26:CG_IDR_POPUP_TIERAZON_VIEW:102
# End Section
# Section Tierazon : {00000000-0001-0000-0000-000000000000}
# 	1:17:CG_IDS_DISK_SPACE:107
# 	1:19:CG_IDS_PHYSICAL_MEM:104
# 	1:25:CG_IDS_DISK_SPACE_UNAVAIL:108
# 	2:14:PhysicalMemory:CG_IDS_PHYSICAL_MEM
# 	2:9:DiskSpace:CG_IDS_DISK_SPACE
# 	2:16:SpaceUnavailable:CG_IDS_DISK_SPACE_UNAVAIL
# 	2:7:NewFunc:1
# 	2:10:SysInfoKey:1234
# End Section