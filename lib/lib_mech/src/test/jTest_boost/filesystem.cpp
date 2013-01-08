#include <stdafx.h>
                          

int main_filesystem0()

{
	if( filesystem::exists("foobar") )
		filesystem::remove_all( "foobar" );

	filesystem::create_directory( "foobar" );
	ofstream file( "foobar/cheeze" );
	file << "tastes good!\n";
	file.close();
	if ( !filesystem::exists( "foobar/cheeze" ) )
	std::cout << "Something is rotten in foobar\n";

	return 0;
}

/*
Additional class path constructors provide for an operating system dependent format, useful for user provided input:

int main( int argc, char * argv[] ) {
path arg_path( argv[1], native ); // native means use O/S path format
To make class path objects easy to use in expressions, operator/ appends paths:

ifstream file1( arg_path / "foo/bar" );
ifstream file2( arg_path / "foo" / "bar" );
The expressions arg_path / "foo/bar" and arg_path / "foo" / "bar" yield identical results.

Paths can include references to the parent directory, using the ".." notation. Paths are always automatically converted to canonical form, so "foo/../bar" gets converted to "bar", and "../foo/../bar" gets converted to "../bar".


*/
bool find_file(	const boost::filesystem::path & dir_path,     
					// in this directory,
					const std::string & file_name, 
					// search for this name,
					boost::filesystem::path & path_found )        
					// placing boost::filesystem::path here if found
{
#if 0
  if ( !exists( dir_path ) ) return false;
  boost::filesystem::directory_iterator end_itr; 
  // default construction yields past-the-end
  for ( boost::filesystem::directory_iterator itr( dir_path );
        itr != end_itr;
        ++itr )
  {
    if ( boost::filesystem::is_directory( *itr ) )
    {
      if ( find_file( *itr, file_name, path_found ) ) return true;
    }
    else if ( itr->leaf() == file_name ) // see below
    {
      path_found = *itr;
      return true;
    }
  }
#endif
  return false;
}
