This is the final production version.
Reviewed July 31, 2017

Bookfinder uses libcurl to query Addall.com book database to find prices.


NOTES:

Libcurl has to be referenced in the linker as follows:

- Project-> properties-> C++ -> General -> Additional Include Directories. Add the directory that curl subdirectory is in.
DO NOT reference the curl directory, but rather its parent

- Project-> Properties->Linker -> General -> Additional Lib Directories. Add the cur lib dir, which is currently in the jnc-code/lib folder of d:\\OneDrive-CLS.

- Project->Properties-> Linker-> Input->Additional dependencies. Add libcurl.a and libcurldll.a

- Put a copy of libcurl.dll (the dynamic lib) in your executable directory

-- MAKE SURE THE TARGET PLATFORM IS WIN32!


jnc May 21, 2017
changed May 24, 2017

Moved to u:/vs/Projects-old/~jnc_code folder Sept 26, 2018

