/* file : jBoost.h
Coder : by icandoit ( mech12@nate.com)
Date : 2006-10-27 10:36:07
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jBoost_header__
#define __jBoost_header__
#pragma once

#pragma warning(disable:4819) // signed/unsigned mismatch
#define BOOST_FILESYSTEM_VERSION 3

#include <boost/config.hpp>

#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <cstring>
#include <cassert>
#include <vector>
#include <list>
#include <algorithm>

#include <boost/array.hpp>
#include <boost/utility.hpp>
#include <boost/any.hpp>
#include <boost/signal.hpp>

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>

#include <boost/iterator_adaptors.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/indirect_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>



#include <boost/function.hpp>
#include <boost/functional.hpp>

#include "boost/filesystem/fstream.hpp"    // ditto
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/exception.hpp>

#include <boost/format.hpp>

//Serialization 사용
#include <fstream>
// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


using namespace std;
using namespace boost;                   // for ease of tutorial presentation;

namespace boost
{
	namespace filesystem
	{
#ifdef _UNICODE
		typedef wpath tpath;
		typedef wdirectory_iterator tdirectory_iterator;
#else
		typedef path tpath;
		typedef directory_iterator tdirectory_iterator;
#endif
	}

#ifdef _UNICODE
	typedef wformat tformat;
#else
	typedef format tformat;
#endif

}

//#pragma warning(default:4819) 


#endif // __jBoost_header__
