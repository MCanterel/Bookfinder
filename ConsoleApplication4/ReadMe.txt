Bookfinder uses libcurl to query Addall.com book database to find prices.


NOTES:

Libcurl has to be referenced in the linker as follows:

- Project-> properties-> C++ -> General -> Additional Include Directories. Add the directory that curl subdirectory is in.
DO NOT reference the curl directory, but rather its parent

- Project-> Properties->Linker -> General -> Additional Lib Directories. Add the cur lib dir

- Project->Properties-> Linker-> Input. Add libcurl.a and libcurldll.a

- Put a copy of libcurl.dll (the dynamic lib) in your executable directory


jnc May 21, 2017

