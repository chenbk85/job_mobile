/* file : jIGuiButtonInventory.h
Coder : by ALo (jung0582@hotmail.com)
Date : 2006-01-03 09:45:43
*/

#ifndef __jIGuiButtonInventory_h__
#define __jIGuiButtonInventory_h__
#pragma once

namespace nMech
{
	namespace nGUI
	{

#define jINTERFACE_jIGuiButtonInventory(x) public: \
	virtual jIGuiControl* BaseI() ##x \
	virtual jIGuiButtonInventory* GetGlobalDragCtrl() ##x \
	virtual void SetGlobalDragCtrl(jIGuiButtonInventory* pItem) ##x \
	virtual POINT& GetGlobalDragCursor() ##x \
	virtual void SetGlobalDragCursor(POINT& poDragItemCursor) ##x \
	virtual bool GetDragInventory() ##x \
	virtual void SetDragInventory(bool DlagInven) ##x \
	virtual POINT& GetDragPoint() ##x \
	virtual void* GetInterface( StringID id ) ##x \
	virtual void SetChangeTexture(cstr szTextureName) ##x \

		jINTERFACE_END(jIGuiButtonInventory);

	}
}


#endif // __jIGuiButtonInventory_h__
