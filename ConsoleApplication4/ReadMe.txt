Bookfinder uses libcurl to query Addall.com book database to find prices.


NOTES:

Libcurl has to be referenced in the linker as follows:

- Project-> properties-> C++ -> General -> Additional Include Directories. Add the directory that curl subdirectory is in.
DO NOT reference the curl directory, but rather its parent

- Project-> Properties->Linker -> General -> Additional Lib Directories. Add the cur lib dir

- Project->Properties-> Linker-> Input. Add libcurl.a and libcurldll.a

- Put a copy of libcurl.dll (the dynamic lib) in your executable directory

PHEW! It works.
jnc May 21, 2017


========================================================================
    CONSOLE APPLICATION : ConsoleApplication4 Project Overview
========================================================================

ConsoleApplication4.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

ConsoleApplication4.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

ConsoleApplication4.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named ConsoleApplication4.pch and a precompiled types file named StdAfx.obj.