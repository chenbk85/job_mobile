#include <stdafx.h>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include <iostream>

namespace fs = boost::filesystem;

int main_simple_ls(  )
{
#if 0
	int argc=0;
	char* argv[2];
	fs::path full_path( fs::initial_path() );

	if ( argc > 1 )
		full_path = fs::system_complete( fs::path( argv[1], fs::native ) );
	else
		std::cout << "\nusage:   simple_ls [path]" << std::endl;

	unsigned long file_count = 0;
	unsigned long dir_count = 0;
	unsigned long err_count = 0;

	if ( !fs::exists( full_path ) )
	{
		std::cout << "\nNot found: " << full_path.string() << std::endl;
		return 1;
	}

	if ( fs::is_directory( full_path ) )
	{
		std::cout << "\nIn directory: "
			<< full_path.string() << "\n\n";
		fs::directory_iterator end_iter;
		for ( fs::directory_iterator dir_itr( full_path );
			dir_itr != end_iter;
			++dir_itr )
		{
			try
			{
				if ( fs::is_directory( *dir_itr ) )
				{
					++dir_count;
					std::cout << dir_itr->leaf()<< " [directory]\n";
				}
				else
				{
					++file_count;
					std::cout << dir_itr->leaf() << "\n";
				}
			}
			catch ( const std::exception & ex )
			{
				++err_count;
				std::cout << dir_itr->leaf() << " " << ex.what() << std::endl;
			}
		}
		std::cout << "\n" << file_count << " files\n"
			<< dir_count << " directories\n"
			<< err_count << " errors\n";
	}
	else // must be a file
	{
		std::cout << "\nFound: " << full_path.native_file_string() << "\n";    
	}

	int main_filesystem_ls2();main_filesystem_ls2();
	return 0;
}



#include <iostream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
using namespace std;

int main_filesystem_ls2()
{
	namespace fs = boost::filesystem;

	// ���丮 �ۼ�
	fs::path dir( "my_dir" );
	fs::create_directory( dir );

	// ������ ���� ���ԡ�
	// ���丮��� ���ϸ��� ������ / �����ڷ�
	fs::ofstream f( dir/"test.txt" );
	f << "Hello!" << endl;
	f.close();

	// Ŀ��Ʈ ���丮�� ���� �϶� �� ����
	fs::directory_iterator end;
	for( fs::directory_iterator it(fs::current_path()); it!=end; ++it )
	{
		if( fs::is_directory(*it) )
			cout << "D ";
		else
			cout << "F ";
		// leaf() �н� ������ �ڸ���, ������ �̸� �κи� ����
		cout << it->leaf() << endl;
	}
#endif
	return 0;
}
/*
��¿�
D jstl
D kix
D my_dir
F test.cpp
F test.d
F test.exe
F test.obj

*/