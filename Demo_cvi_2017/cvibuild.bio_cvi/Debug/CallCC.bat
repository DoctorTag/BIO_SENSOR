@set INCLUDE=
@set LIB=
@set FileNum=%1
@shift
@set SrcFileName=%1
@shift
@set ObjFileName=%1
@shift
@set DefProts=%1
@shift
@set OutFileName=%1
@shift
@set REST=%1 %2 %3 %4 %5 %6 %7 %8 %9
@rem d:\software\2018\feelkit\cvi\Demo_labwindows_cvi
@echo Compiling %FileNum% %SrcFileName%
@"c:\program files (x86)\national instruments\cvi2017\bin\clang\3.3\clang.exe" -cc1 -nostdsysteminc -fno-builtin-include-notes -emit-obj -add-plugin cvi-emit-defprots -plugin-arg-cvi-emit-defprots %DefProts% -target-cpu i386  %REST% -std=gnu89 -trigraphs     @"CC_no_dep_options.txt"  @"CC_options.txt" -D_CVI_="1700"  -D_NI_i386_="1"  -D_NI_mswin_="1"  -D_NI_mswin32_="1"  -D_CVI_DEBUG_="1"  -D_CVI_EXE_="1"  -D_LINK_CVIRTE_="1"  -D_CVI_FDS_="1"  -D_CVI_USE_FUNCS_FOR_VARS_="1"  -D__DEFALIGN="8"  -D_NI_VC_="220"  -D_WIN32="1"  -DWIN32="1"  -D__WIN32__="1"  -D_WINDOWS="1"  -D__NT__="1"  -D_M_IX86="400"  -D__FLAT__="1"  -D_PUSHPOP_SUPPORTED="1"  -D_CVI_C99_EXTENSIONS_="0"  -D_CVI_PROFILE_LEVEL_="0"  -D_TARGET_FILE_VERSION_="\"1.0.0.0\""  -D_TARGET_PRODUCT_VERSION_="\"1.0.0.0\""  -D_CVI_CONFIGURATION_NAME_="\"Debug\""  -D_CVI_RTE_SHARED_="1"  -o %ObjFileName%  %SrcFileName%  > %OutFileName% 2>&1
@if errorlevel 1 goto err
@echo Compile succeeded for %FileNum% %SrcFileName%
@exit 0
:err
@echo Compile failed for %FileNum% %SrcFileName%
@exit 1
