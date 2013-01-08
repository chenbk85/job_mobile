#include "stdafx.h"
#include <iostream>
#include <boost/filesystem.hpp>
using namespace boost::filesystem;
using namespace std;
#include "nOS_filesystem.h"

namespace nMech { namespace nOS
{

	bool is_exist_file(const char* sz)
	{
		path p (sz);   // p reads clearer than argv[1] in the following code

		bool is = exists(p);
		if(is)
		{
			printf("ok");
		}
		else
			printf("fail");

		return is;
	}
	void create_dir_force(cstr sz)
	{
		fs::path pa = sz;
		fs::create_directories(pa);
	}


	const char * say_what(bool b) { return b ? "true" : "false"; }

	void print_boost_path(cstr szPath)
	{
		path p;  //  compose a path from the command line arguments

		p = szPath;

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

	}


}} //namespace nMech { namespace nOS
