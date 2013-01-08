/* file : jIGuiComboBox.h
Coder : by ALo (jung0582@hotmail.com)
Date : 2005-12-29 10:27:42
*/

#ifndef __jIGuiComboBox_h__
#define __jIGuiComboBox_h__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000
namespace nMech
{
	namespace nGUI
	{

		struct _jGuiListItem;

#define jINTERFACE_jIGuiComboBox(x) public:	\
	virtual jIGuiControl* BaseI() ##x \
	virtual void	AddItem( cstr   strText, void* pData ) ##x \
	virtual void    RemoveAllItems() ##x \
	virtual void    RemoveItem( UINT index ) ##x \
	virtual jIE*	FindItem( cstr   strText, UINT iStart=0 ) ##x \
	virtual void    SetScrollBarWidth( int nWidth )  ##x \
	virtual void*   GetSelectedData() ##x \
	virtual _jGuiListItem* GetSelectItem() ##x \
	virtual cstr	GetSelectItemText() ##x \
	virtual UINT    GetNumItems() ##x \
	virtual _jGuiListItem* GetItem( UINT index ) ##x \
	virtual cstr	GetItemTextOfNum(UINT index) ##x \
	virtual HRESULT SetSelectedByIndex( UINT index ) ##x \
	virtual HRESULT SetSelectedByText( cstr   strText ) ##x \
	virtual HRESULT SetSelectedByData( void* pData ) ##x \
	virtual void    SetDropHeight( UINT nHeight ) ##x \
	virtual int		GetDropHeight() ##x \

		jINTERFACE_END(jIGuiComboBox);

	}
}

#endif //__jIGuiComboBox_h__
