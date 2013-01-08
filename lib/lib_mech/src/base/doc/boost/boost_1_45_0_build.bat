rem bjam -sTOOLS=vc-9_0 architecture=x86 address-model=64 --build-type=complete install
rem bjam --toolset=msvc-9.0 address-model=64 --build-type=complete

@rem bjam link=static runtime-link=static  --with-filesystem architecture=x86 address-model=32 
@rem bjam link=static runtime-link=static  --with-filesystem architecture=x86 address-model=64 

@rem bjam link=static runtime-link=static  --with-regex architecture=x86 address-model=32 
@rem bjam link=static runtime-link=static  --with-regex architecture=x86 address-model=64 

@rem bjam link=static runtime-link=static  --with-serialization architecture=x86 address-model=64
@rem bjam link=static runtime-link=static  --with-serialization architecture=x86 address-model=32

@rem bjam link=static runtime-link=static  --with-signals architecture=x86 address-model=64
@rem bjam link=static runtime-link=static  --with-signals architecture=x86 address-model=32

@rem bjam link=static runtime-link=static  --with-system architecture=x86 address-model=32
@rem bjam link=static runtime-link=static  --with-system architecture=x86 address-model=64

@rem bjam link=static runtime-link=static  --with-test architecture=x86 address-model=32
@rem bjam link=static runtime-link=static  --with-test architecture=x86 address-model=64


rem date_time은 asio를 사용할때 필요.
rem bjam link=static runtime-link=static  --with-date_time architecture=x86 address-model=32
rem bjam link=static runtime-link=static  --with-date_time architecture=x86 address-model=64






@rem 안됨 bjam --build-type=complete --build-dir="D:\boost_1_35_0\build" --toolset=msvc stage
@rem 안됨 bjam.exe -sTOOLS=vc-8_0 -sICU_PATH=F:\dev\icu threading=multi address-model=64 --build-type=complete --prefix=d:\dev\boost64 --without-python  runtime-link=static  --without-mpi install

pause
