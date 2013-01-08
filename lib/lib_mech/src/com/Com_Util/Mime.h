/* file : Mime.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-13 16:56:26
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __Mime_header__
#define __Mime_header__
#pragma once

namespace nMech
{
	namespace nUtil
	{
		namespace nDebug
		{
			class Mime
			{
			public:
				Mime();
				~Mime();

				LPSTR	GetContentType( LPCSTR extension );
				LPSTR	GetDefaultBoundary()
				{
					return m_defaultBoundary;
				}

				LPSTR	CreateMimeBoundary();

			private:
				CHAR	m_contentType[128];
				CHAR	m_defaultBoundary[128];
				CHAR	m_boundry[128];
			};

		}
	}
}


#endif // __Mime_header__
