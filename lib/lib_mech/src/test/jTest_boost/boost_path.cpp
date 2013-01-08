#include "stdafx.h"
//  path_info.cpp  ---------------------------------------------------------------------//

//  Copyright Beman Dawes 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

#include <iostream>
#include <boost/filesystem.hpp>
using namespace std;
using namespace boost::filesystem;

const char * say_what(bool b) { return b ? "true" : "false"; }
/*
윈도우즈 출력.

composed path:
cout << -------------: "o:\out\BaseballServer\BaseballServer\MDebug/csv/file_S
ys__T_Base.csv"
make_preferred()----------: "o:\out\BaseballServer\BaseballServer\MDebug\csv\f
ile_Sys__T_Base.csv"

elements:
"o:"
"/"
"out"
"BaseballServer"
"BaseballServer"
"MDebug"
"csv"
"file_Sys__T_Base.csv"

observers, native format:
native()-------------: o:\out\BaseballServer\BaseballServer\MDebug/csv/file_Sy
s__T_Base.csv
c_str()--------------: o:\out\BaseballServer\BaseballServer\MDebug/csv/file_Sy
s__T_Base.csv
string()-------------: o:\out\BaseballServer\BaseballServer\MDebug/csv/file_Sy
s__T_Base.csv
wstring()------------: o:\out\BaseballServer\BaseballServer\MDebug/csv/file_Sy
s__T_Base.csv

observers, generic format:
generic_string()-----: o:/out/BaseballServer/BaseballServer/MDebug/csv/file_Sy
s__T_Base.csv
generic_wstring()----: o:/out/BaseballServer/BaseballServer/MDebug/csv/file_Sy
s__T_Base.csv

decomposition:
root_name()----------: "o:"
root_directory()-----: "\"
root_path()----------: "o:\"
relative_path()------: "out\BaseballServer\BaseballServer\MDebug/csv/file_Sys_
_T_Base.csv"
parent_path()--------: "o:\out\BaseballServer\BaseballServer\MDebug/csv"
filename()-----------: "file_Sys__T_Base.csv"
stem()---------------: "file_Sys__T_Base"
extension()----------: ".csv"

query:
empty()--------------: false
is_absolute()--------: true
has_root_name()------: true
has_root_directory()-: true
has_root_path()------: true
has_relative_path()--: true
has_parent_path()----: true
has_filename()-------: true
has_stem()-----------: true
has_extension()------: true

*/
int test_path()
{

	path p="o:\\out\\BaseballServer\\BaseballServer\\MDebug/csv/file_Sys__T_Base.csv";

	cout  <<  "\ncomposed path:\n";
	cout  <<  "  cout << -------------: " << p << "\n";
	cout  <<  "  make_preferred()----------: " << path(p).make_preferred() << "\n";

	cout << "\nelements:\n";

	for (path::iterator it(p.begin()), it_end(p.end()); it != it_end; ++it)
		cout << "  " << *it << '\n';

	cout  <<  "\nobservers, native format:" << endl;
# ifdef BOOST_POSIX_API
	cout  <<  "  native()-------------: " << p.native() << endl;
	cout  <<  "  c_str()--------------: " << p.c_str() << endl;
# else  // BOOST_WINDOWS_API
	wcout << L"  native()-------------: " << p.native() << endl;
	wcout << L"  c_str()--------------: " << p.c_str() << endl;
# endif
	cout  <<  "  string()-------------: " << p.string() << endl;
	wcout << L"  wstring()------------: " << p.wstring() << endl;

	cout  <<  "\nobservers, generic format:\n";
	cout  <<  "  generic_string()-----: " << p.generic_string() << endl;
	wcout << L"  generic_wstring()----: " << p.generic_wstring() << endl;

	cout  <<  "\ndecomposition:\n";
	cout  <<  "  root_name()----------: " << p.root_name() << '\n';
	cout  <<  "  root_directory()-----: " << p.root_directory() << '\n';
	cout  <<  "  root_path()----------: " << p.root_path() << '\n';
	cout  <<  "  relative_path()------: " << p.relative_path() << '\n';
	cout  <<  "  parent_path()--------: " << p.parent_path() << '\n';
	cout  <<  "  filename()-----------: " << p.filename() << '\n';
	cout  <<  "  stem()---------------: " << p.stem() << '\n';
	cout  <<  "  extension()----------: " << p.extension() << '\n';

	cout  <<  "\nquery:\n";
	cout  <<  "  empty()--------------: " << say_what(p.empty()) << '\n';
	cout  <<  "  is_absolute()--------: " << say_what(p.is_absolute()) << '\n';
	cout  <<  "  has_root_name()------: " << say_what(p.has_root_name()) << '\n';
	cout  <<  "  has_root_directory()-: " << say_what(p.has_root_directory()) << '\n';
	cout  <<  "  has_root_path()------: " << say_what(p.has_root_path()) << '\n';
	cout  <<  "  has_relative_path()--: " << say_what(p.has_relative_path()) << '\n';
	cout  <<  "  has_parent_path()----: " << say_what(p.has_parent_path()) << '\n';
	cout  <<  "  has_filename()-------: " << say_what(p.has_filename()) << '\n';
	cout  <<  "  has_stem()-----------: " << say_what(p.has_stem()) << '\n';
	cout  <<  "  has_extension()------: " << say_what(p.has_extension()) << '\n';

	return 0;
}
/*
icandoit-mac:linux_test_boost daystar$ ./a /Users/daystar/pc/lib/lib_mech/src/base/base/linux_test_boost/aaa.xml

composed path:
cout << -------------: "/Users/daystar/pc/lib/lib_mech/src/base/base/linux_test_boost/aaa.xml"
make_preferred()----------: "/Users/daystar/pc/lib/lib_mech/src/base/base/linux_test_boost/aaa.xml"

elements:
"/"
"Users"
"daystar"
"pc"
"lib"
"lib_mech"
"src"
"base"
"base"
"linux_test_boost"
"aaa.xml"

observers, native format:
native()-------------: /Users/daystar/pc/lib/lib_mech/src/base/base/linux_test_boost/aaa.xml
c_str()--------------: /Users/daystar/pc/lib/lib_mech/src/base/base/linux_test_boost/aaa.xml
string()-------------: /Users/daystar/pc/lib/lib_mech/src/base/base/linux_test_boost/aaa.xml
wstring()------------: /Users/daystar/pc/lib/lib_mech/src/base/base/linux_test_boost/aaa.xml

observers, generic format:
generic_string()-----: /Users/daystar/pc/lib/lib_mech/src/base/base/linux_test_boost/aaa.xml
generic_wstring()----: /Users/daystar/pc/lib/lib_mech/src/base/base/linux_test_boost/aaa.xml

decomposition:
root_name()----------: ""
root_directory()-----: "/"
root_path()----------: "/"
relative_path()------: "Users/daystar/pc/lib/lib_mech/src/base/base/linux_test_boost/aaa.xml"
parent_path()--------: "/Users/daystar/pc/lib/lib_mech/src/base/base/linux_test_boost"
filename()-----------: "aaa.xml"
stem()---------------: "aaa"
extension()----------: ".xml"

query:
empty()--------------: false
is_absolute()--------: true
has_root_name()------: false
has_root_directory()-: true
has_root_path()------: true
has_relative_path()--: true
has_parent_path()----: true
has_filename()-------: true
has_stem()-----------: true
has_extension()------: true
*/
