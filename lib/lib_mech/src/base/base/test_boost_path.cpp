#include "stdafx.h"
#include "base/jFolder.h"
#include "base/jTestUnit.h"
#include "header/jBoost.h"


using namespace nMech;
using namespace boost::filesystem;
typedef boost::filesystem::tpath boost_path;

inline void jpath_print(std::tstring str, boost_path& p)
{
	return;
	/* 더자세한건 
	http://boost.cppll.jp/HEAD/libs/filesystem/doc/path.htm#Canonical
	*/
	tcout << str<< _T(" : string------------------: ") << p.string() << _T('\n')
		<< _T("native_directory_string-: ") << p.native_directory_string() << _T('\n')
		<< _T("native_file_string------: ") << p.native_file_string() << '\n'
		<< _T("leaf------: ") << p.leaf() << endl
		<< _T("root_path : ") << p.root_path().string() << endl
		<< _T("root_name : ") << p.root_name() << endl
		<< _T("relative_path : ") << p.relative_path().string() << endl <<endl;
}

#define JPATH_PRINT(X) jpath_print(_T(#X) , X);

jTEST_SUITE_BEGIN(boost_test)
jTEST(path_test)
{

	{
		boost_path my_path( _T("foo/bar/data.txt") );
		JPATH_PRINT(my_path);

		jTEST_CHECK(my_path.string()							==_T("foo/bar/data.txt") );
		jTEST_CHECK(my_path.native_directory_string()	==_T("foo\\bar\\data.txt"));
		jTEST_CHECK(my_path.native_file_string()				==_T("foo\\bar\\data.txt"));
		jTEST_CHECK(my_path.leaf()											==_T("data.txt"));
		jTEST_CHECK(my_path.root_path().string()				==_T(""));
		jTEST_CHECK(my_path.root_name()								==_T(""));
		jTEST_CHECK(my_path.relative_path().string()		==_T("foo/bar/data.txt"));
	}

	{
		boost_path my_path( /*initial_path()*/boost_path(_T("z:/TR_Server/bin/Debug"))  / _T("foo") );
		JPATH_PRINT(my_path);
		jTEST_CHECK(my_path.string()										==_T("z:/TR_Server/bin/Debug/foo"));
		jTEST_CHECK(my_path.native_directory_string()	==_T("z:\\TR_Server\\bin\\Debug\\foo"));
		jTEST_CHECK(my_path.native_file_string()				==_T("z:\\TR_Server\\bin\\Debug\\foo"));
		jTEST_CHECK(my_path.leaf()											==_T("foo"));
		jTEST_CHECK(my_path.root_path().string()				==_T("z:/"));
		jTEST_CHECK(my_path.root_name()								==_T("z:"));
		jTEST_CHECK(my_path.relative_path().string()		==_T("TR_Server/bin/Debug/foo"));
	}

	{
		boost_path my_path(_T("c:"), native );
		my_path /= _T("/foo");
		assert( my_path.string() ==_T("c:/foo") );
		JPATH_PRINT(my_path);

		jTEST_CHECK(my_path.string()										==_T("c:/foo"));
		jTEST_CHECK(my_path.native_directory_string()	==_T("c:\\foo"));
		jTEST_CHECK(my_path.native_file_string()				==_T("c:\\foo"));
		jTEST_CHECK(my_path.leaf()											==_T("foo"));
		jTEST_CHECK(my_path.root_path().string()				==_T("c:/"));
		jTEST_CHECK(my_path.root_name()								==_T("c:"));
		jTEST_CHECK(my_path.relative_path().string()		==_T("foo"));
	}
}


jTEST(filesystem_test)
{
	if( filesystem::exists("foobar") )
		filesystem::remove_all( "foobar" );

	filesystem::create_directory( "foobar" );

	std::ofstream file( "foobar/cheeze" );
	file << "tastes good!\n";
	file.close();
	jTEST_CHECK( filesystem::exists( "foobar/cheeze" ) );
	filesystem::remove_all( "foobar" );

}
jTEST_SUITE_END(boost_test)

