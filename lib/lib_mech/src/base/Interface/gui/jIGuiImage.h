/* file : jIGuiImage.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-01-17 13:36:02
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jIGuiImage_header__
#define __jIGuiImage_header__
#pragma once

namespace nMech
{
	namespace nGUI
	{

#define jINTERFACE_jIGuiImageAni(x) public: \
	virtual jIGuiControl* BaseI() ##x \
	virtual void SetTexUV_AnimationPos(float fRange) ##x \
	/* 0 ~ 1까지의 레인지 , 0 이면 ResetKey와 같음 , 1이면 맨마지막 장면*/\

		jINTERFACE_END(jIGuiImageAni);

	}
}


#endif // __jIGuiImage_header__
