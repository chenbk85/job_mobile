set path=%path%;%cd%\bin;
set ZLIB_SOURCE="%cd%\..\zlib-1.2.5"
set BZIP2_SOURCE="%cd%\..\bzip2-1.0.6"
set PYTHON_ROOT="c:\Python27"
set PYTHON_VERSION=2.7
set ICU_PATH="%cd%\..\icu\source\common"

pushd %cd%\tools\build\v2\build\
move configure.jam configure.jam.org
popd
copy configure.jam %cd%\tools\build\v2\build\configure.jam
bjam --prefix=%cd%\\..\boost_lib\Win32 --toolset=msvc-9.0 --build-type=complete link=static runtime-link=static warnings=off --without-mpi install architecture=x86 address-model=32 --without-python  
bjam --prefix=%cd%\\..\boost_lib\x64 --toolset=msvc-9.0 --build-type=complete link=static runtime-link=static warnings=off --without-mpi install architecture=x86 address-model=64 --without-python  

pause

