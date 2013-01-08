/* file : file_util.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2009-12-01 15:20:18
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __file_util_header__
#define __file_util_header__
#pragma once


namespace nMech
{

	inline void load_file_from_ifstream(std::tstring& s, std::tifstream& is)
	{
		s.erase();
		if(is.bad()) return;
		//
		// attempt to grow string buffer to match file size,
		// this doesn't always work...
		s.reserve(is.rdbuf()->in_avail());
		TCHAR c;
		while(is.get(c))
		{
			// use logarithmic growth stategy, in case
			// in_avail (above) returned zero:
			if(s.capacity() == s.size())
				s.reserve(s.capacity() * 3);
			s.append(1, c);
		}
	}

	inline nMech::tcstr  asdf_read_file(nMech::tcstr  filename , std::tstring& sBuf)
	{
		std::tifstream iF(filename);
		load_file_from_ifstream(sBuf, iF);
		iF.close();
		return sBuf.c_str();
	}

}


#endif // __file_util_header__
