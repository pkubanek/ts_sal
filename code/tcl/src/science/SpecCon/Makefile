# Microsoft Developer Studio Generated NMAKE File, Based on SpecCon.dsp
!IF "$(CFG)" == ""
CFG=SpecCon - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SpecCon - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SpecCon - Win32 Release" && "$(CFG)" !=\
 "SpecCon - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SpecCon.mak" CFG="SpecCon - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SpecCon - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "SpecCon - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "SpecCon - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SpecCon.exe"

!ELSE 

ALL : "$(OUTDIR)\SpecCon.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\NddsComm.obj"
	-@erase "$(INTDIR)\SpecCon.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\SpecCon.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D\
 "_MBCS" /Fp"$(INTDIR)\SpecCon.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c\
 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SpecCon.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)\SpecCon.pdb" /machine:I386 /out:"$(OUTDIR)\SpecCon.exe" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\NddsComm.obj" \
	"$(INTDIR)\SpecCon.obj"

"$(OUTDIR)\SpecCon.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SpecCon - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\SpecCon.exe"

!ELSE 

ALL : "$(OUTDIR)\SpecCon.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\NddsComm.obj"
	-@erase "$(INTDIR)\SpecCon.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\SpecCon.exe"
	-@erase "$(OUTDIR)\SpecCon.ilk"
	-@erase "$(OUTDIR)\SpecCon.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /I "k:\include" /I\
 "c:\progra~1\nddswin\include\share" /I "c:\progra~1\nddswin\include\win32" /D\
 "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "RTI_THREADS" /D "RTI_WIN32" /D\
 "RTI_ENDIAN_LITTLE" /Fp"$(INTDIR)\SpecCon.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SpecCon.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=libSpectrometerNdds.lib libndds.lib libutilsip.lib libutilsxx.lib\
 libxdr_fixes.lib libxdr.lib netapi32.lib wsock32.lib Ooidrv32.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\SpecCon.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)\SpecCon.exe" /pdbtype:sept\
 /libpath:"k:\lib\i86Win32" /libpath:"c:\progra~1\nddswin\lib\i86Win32" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\NddsComm.obj" \
	"$(INTDIR)\SpecCon.obj"

"$(OUTDIR)\SpecCon.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "SpecCon - Win32 Release" || "$(CFG)" ==\
 "SpecCon - Win32 Debug"
SOURCE=.\main.cpp

!IF  "$(CFG)" == "SpecCon - Win32 Release"

DEP_CPP_MAIN_=\
	".\NddsComm.h"\
	".\Ooidrv.h"\
	".\SpecCon.h"\
	"K:\include\mpTypes.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SpecCon - Win32 Debug"

DEP_CPP_MAIN_=\
	".\NddsComm.h"\
	".\Ooidrv.h"\
	".\SpecCon.h"\
	"K:\include\mpTypes.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ENDIF 

SOURCE=.\NddsComm.cpp

!IF  "$(CFG)" == "SpecCon - Win32 Release"

DEP_CPP_NDDSC=\
	".\NddsComm.h"\
	".\Ooidrv.h"\
	".\SpecCon.h"\
	".\spectypes.h"\
	"K:\include\mpTypes.h"\
	
NODEP_CPP_NDDSC=\
	".\dbFieldNames.h"\
	".\dbFieldReply.h"\
	".\dbIDListReply.h"\
	".\dbMessagesNames.h"\
	".\NDDS.h"\
	".\nomadNddsDomain.h"\
	".\specCommand.h"\
	".\specMessageNames.h"\
	".\specReply.h"\
	

"$(INTDIR)\NddsComm.obj" : $(SOURCE) $(DEP_CPP_NDDSC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SpecCon - Win32 Debug"

DEP_CPP_NDDSC=\
	"..\..\..\..\progra~1\nddswin\include\share\ndds.h"\
	"..\..\..\..\progra~1\nddswin\include\share\nddsxdr.h"\
	"..\..\..\..\progra~1\nddswin\include\share\rtilib\rti_types.h"\
	".\NddsComm.h"\
	".\Ooidrv.h"\
	".\SpecCon.h"\
	".\spectypes.h"\
	"K:\include\mpTypes.h"\
	"k:\include\nomadnddsdomain.h"\
	"k:\include\speccommand.h"\
	"k:\include\specmessagenames.h"\
	"k:\include\specreply.h"\
	

"$(INTDIR)\NddsComm.obj" : $(SOURCE) $(DEP_CPP_NDDSC) "$(INTDIR)"


!ENDIF 

SOURCE=.\SpecCon.cpp

!IF  "$(CFG)" == "SpecCon - Win32 Release"

DEP_CPP_SPECC=\
	".\Ooidrv.h"\
	".\SpecCon.h"\
	".\spectypes.h"\
	"K:\include\mpTypes.h"\
	
NODEP_CPP_SPECC=\
	".\nomadNddsDomain.h"\
	".\specCommand.h"\
	".\specMessageNames.h"\
	".\specReply.h"\
	

"$(INTDIR)\SpecCon.obj" : $(SOURCE) $(DEP_CPP_SPECC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SpecCon - Win32 Debug"

DEP_CPP_SPECC=\
	"..\..\..\..\progra~1\nddswin\include\share\ndds.h"\
	"..\..\..\..\progra~1\nddswin\include\share\nddsxdr.h"\
	"..\..\..\..\progra~1\nddswin\include\share\rtilib\rti_types.h"\
	".\Ooidrv.h"\
	".\SpecCon.h"\
	".\spectypes.h"\
	"K:\include\mpTypes.h"\
	"k:\include\nomadnddsdomain.h"\
	"k:\include\speccommand.h"\
	"k:\include\specmessagenames.h"\
	"k:\include\specreply.h"\
	

"$(INTDIR)\SpecCon.obj" : $(SOURCE) $(DEP_CPP_SPECC) "$(INTDIR)"


!ENDIF 


!ENDIF 

