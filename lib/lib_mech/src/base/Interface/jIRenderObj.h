/* file : jIRenderObj.h
Coder : by icandoit ( mech12@nate.com)
Date : 2006-11-20 14:33:28
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jIRenderObj_header__
#define __jIRenderObj_header__
#pragma once

#define jINTERFACE_jIRenderObj(x) public:	\
	virtual HRESULT OnCreateDevice( HWND, void* pd3dDevice) ##x \
	virtual void Render()##x \
	virtual void FrameMove() ##x \
	virtual void Close() ##x \
	virtual void OnLostDevice() ##x \
	virtual void OnResetDevice() ##x \
	virtual void OnDestroyDevice() ##x \

jINTERFACE_END(jIRenderObj);

#endif // __jIRenderObj_header__
