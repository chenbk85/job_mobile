/* 
	filename:	uStringParsor.h
	coder	:	Cho Wook Rea (mech12@dreamwiz.com)(icq:74456993) 
	comp.	:	esofnet 
	compiler:	vc++ 6.0
	date	:	2000-07-14오전 2:33:27
	title	:	
*/


#ifndef __uStringParsor_h__

#define __uStringParsor_h__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


namespace nMech
{

	namespace nString
	{

#ifdef UNICODE
#define jSplit jSplitW
#else
#define jSplit jSplitA
#endif
		inline void jSplitA(const std::string& inLine, const std::string& Separ, std::vector<std::string>& out)
			////////////////////////////////////////////////////////////////
		{
			const size_t N = inLine.length();
			size_t iStart, iEnd;

			iStart = inLine.find_first_not_of(Separ);
			while ((iStart < N)) 
			{
				iEnd = inLine.find_first_of(Separ, iStart);
				if (iEnd > N) iEnd = N;
				out.push_back(inLine.substr(iStart, iEnd - iStart));
				iStart = inLine.find_first_not_of(Separ, iEnd+1);
			}
		}
		inline void jSplitW(const std::wstring& inLine, const std::wstring& Separ, std::vector<std::wstring>& out)
			////////////////////////////////////////////////////////////////
		{
			const size_t N = inLine.length();
			size_t iStart, iEnd;

			iStart = inLine.find_first_not_of(Separ);
			while (iStart < N)
			{
				iEnd = inLine.find_first_of(Separ, iStart);
				if (iEnd > N) iEnd = N;
				out.push_back(inLine.substr(iStart, iEnd - iStart));
				iStart = inLine.find_first_not_of(Separ, iEnd+1);
			}
		}

		JBASE_API bool MatchWildcard (acstr  szString, acstr  szWildcard);
		JBASE_API bool MatchWildcard (wcstr  szString, wcstr  szWildcard);


	}//namespace nString

}//namespace nMech

#endif //__uStringParsor_h__
