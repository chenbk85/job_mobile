#ifndef __ICompressionHelper_h__
#define __ICompressionHelper_h__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace nMech
{
	namespace nJC_stream
	{

		class nMech::nJC_stream::CStream;

		struct ICompressionHelper
		{
			//!
			virtual bool Write( nMech::nJC_stream::CStream &outStream, const unsigned char inChar )=0;
			//!
			virtual bool Read( nMech::nJC_stream::CStream &inStream, unsigned char &outChar )=0;
			//!
			virtual bool Write( nMech::nJC_stream::CStream &outStream, const char *inszString )=0;
			//!
			virtual bool Read( nMech::nJC_stream::CStream &inStream, char *outszString, const DWORD indwStringSize )=0;
		};
	}
}

#endif // __ICompressionHelper_h__
