#include <stdafx.h>
using namespace boost::filesystem;

/*
path foo( argv[1], native );
    foo /= "foo";

http://boost.cppll.jp/HEAD/libs/filesystem/doc/path.htm#Canonical

The difference between the representations returned by string(), native_directory_string(), and native_file_string() are illustrated by the following code:

path my_path( "foo/bar/data.txt" );
std::cout
  << "string------------------: " << my_path.string() << '\n'
  << "native_directory_string-: " << my_path.native_directory_string() << '\n'
  << "native_file_string------: " << my_path.native_file_string() << '\n';
On POSIX systems, the output would be:

string------------------: foo/bar/data.txt
native_directory_string-: foo/bar/data.txt
native_file_string------: foo/bar/data.txt
On Windows, the output would be:

string------------------: foo/bar/data.txt
native_directory_string-: foo\bar\data.txt
native_file_string------: foo\bar\data.txt
On classic Mac OS, the output would be:

string------------------: foo/bar/data.txt
native_directory_string-: foo:bar:data.txt
native_file_string------: foo:bar:data.txt
On a hypothetical operating system using OpenVMS format representations, it would be:

string------------------: foo/bar/data.txt
native_directory_string-: [foo.bar.data.txt]
native_file_string------: [foo.bar]data.txt

*/

inline void jpath_print(std::string str, path& p)
{
	/* 더자세한건 
	http://boost.cppll.jp/HEAD/libs/filesystem/doc/path.htm#Canonical
	*/
	std::cout
		<< str << " : string------------------: " << p.string() << '\n'
  //<< "native_directory_string-: " << p.native_directory_string() << '\n'
//  << "native_file_string------: " << p.native_file_string() << '\n'
  << "leaf------: " << p.leaf() << '\n' << endl
  << "root_path : " << p.root_path().string() << endl
  << "root_name : " << p.root_name() << endl
  << "relative_path : " << p.relative_path().string() << endl ;
}

#define JPATH_PRINT(X) jpath_print(#X , X);
int main_path()
{

	typedef boost::filesystem::path path_t;
	path_t my_path( "foo/bar/data.txt" );
	JPATH_PRINT(my_path);

	path_t foo( initial_path() / "foo" );
	JPATH_PRINT(foo);

	path_t p( "c:", native );
	p /= "/foo";
	assert( p.string() == "c:/foo" );
	JPATH_PRINT(p);

	return 0;
}

