thrift-0.9.0.exe -r --gen cpp tutorial.thrift
mkdir gen_cpp_template
thrift-0.9.0.exe -r -out gen_cpp_template --gen cpp:templates=1 tutorial.thrift
mkdir gen_cpp_cob_style
thrift-0.9.0.exe -r -out gen_cpp_cob_style --gen cpp:cob_style=1 tutorial.thrift
mkdir gen_cpp_no_client_completion
thrift-0.9.0.exe -r -out gen_cpp_no_client_completion --gen cpp:templates=1 tutorial.thrift
mkdir gen_cpp_pure_enums
thrift-0.9.0.exe -r -out gen_cpp_pure_enums --gen cpp:pure_enums=1 tutorial.thrift
mkdir gen_cpp_dense
thrift-0.9.0.exe -r -out gen_cpp_dense --gen cpp:dense=1 tutorial.thrift

@rem http://mail-archives.apache.org/mod_mbox/incubator-thrift-dev/200907.mbox/%3Ca03ecfdb0907090541q6a0b94b8ya7c72761d5ae674d@mail.gmail.com%3E
mkdir gen_cpp_asnyc
thrift-0.9.0.exe -r -out gen_cpp_asnyc --gen cpp:async tutorial.thrift

rem mkdir gen_cpp_cassandra
rem thrift-0.9.0.exe -r -out gen_cpp_cassandra --gen cpp cassandra.thrift


thrift-0.9.0.exe -r --gen csharp tutorial.thrift
mkdir gen-csharp_serial
thrift-0.9.0.exe -r -out gen-csharp_serial --gen csharp:serial=1 tutorial.thrift


@REM -r : recurse
pause