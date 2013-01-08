/* file : jIXmlCallBackManager.h
Coder : by icandoit ( mech12@nate.com)
Date : 2006-12-07 17:33:34
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jIXmlCallBackManager_header__
#define __jIXmlCallBackManager_header__
#pragma once


#include <boost/any.hpp>
namespace nMech
{
	namespace nXML
	{
		typedef boost::function<void (boost::any&)> jXml_Callback_ft;

		struct  jIXmlCallBackManager
		{
		public:
			// "Save" : 문서가 저장될때 호출 . param = jID*
			// "UnLoad" : 문서가 unload될때 호출 , param = jID*
			virtual void SetCallback(cstr, jXml_Callback_ft)=0;
			virtual void RunCallBack(cstr, boost::any a)=0;
		};

	}//nXML

}


#endif // __jIXmlCallBackManager_header__
