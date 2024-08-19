cmake_minimum_required(VERSION 3.26)

set(TIERAZON_PROJECT_NAME "tierazon" CACHE STRING "Project name for IDEs")

project("${TIERAZON_PROJECT_NAME}")

set(CMAKE_MFC_FLAG $<$<CONFIG:Debug>:2,1>)
add_executable(tierazon WIN32
    Cmplx.cpp
    cmplx.h
    ColorMethods.cpp
    Convolut.cpp
    Convolut.h
    Dib.cpp
    Dib.h
    Expression.h
    External.h
    Formulae.cpp
    Fparams.cpp
    Fparams.h
    gradient.cpp
    gradient.h
    icon1.ico
    icon2.ico
    MainFrm.cpp
    MainFrm.h
    Movie.cpp
    Movie.h
    Orient.cpp
    Orient.h
    Pattern.cpp
    ReadMe.md
    resource.h
    StdAfx.cpp
    StdAfx.h
    Tierazon.cpp
    Tierazon.h
    Tierazon.rc
    Tierazon.rc2
    TierazonDoc.cpp
    TierazonDoc.h
    TierazonView.cpp
    TierazonView.h
    Toolbar.bmp
    Unique.cpp
    Unique.h
    Xysize.cpp
    Xysize.h
)
target_compile_definitions(tierazon PUBLIC $<$<CONFIG:Debug>:_AFXDLL> _WIN32_WINNT=_WIN32_WINNT_WIN7)
target_precompile_headers(tierazon PUBLIC StdAfx.h)
target_link_libraries(tierazon PUBLIC Vfw32.lib)
