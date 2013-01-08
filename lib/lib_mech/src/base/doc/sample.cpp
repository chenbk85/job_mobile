template < class Container, class UnaryFunction >
UnaryFunction for_each( Container & c, UnaryFunction f )
{
    return for_each( c.begin(), c.end(), f );
}

template < class Container, class UnaryFunction >
UnaryFunction for_each( const Container & c, UnaryFunction f )
{
    return for_each( c.begin(), c.end(), f );
}



//http://www.testors.net/tt/767
FILE *fp = fopen( "test", "wbc" );
fwrite( "DATA", 4, 1, fp );
fflush( fp );
fclose( fp );
// #END

HANDLE hFile = CreateFile( "test", 0, FILE_SHARE_WRITE, 0, TRUNCATE_EXISTING, FILE_FLAG_WRITE_THROUGH );
DWORD sz = 0;
WriteFile( hFile, "data", 4, &sz, NULL );
FlushFileBuffers( hFile );
CloseHandle( hFile );
// #END

while( true )
{
	FILE *fp = fopen( "test", "wb" );   // #1
	fwrite( "data", 4, 1, fp );         //
	//fflush( fp );                     // #2
	fclose( fp );
}