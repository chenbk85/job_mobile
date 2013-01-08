/* file : jIGuiListBox.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-12-28 11:05:12
title : 
desc : 

*/

#ifndef __jIGuiListBox123423_header__
#define __jIGuiListBox123423_header__
#pragma once

#include "jIGuiScrollBar.h"

namespace nMech
{
	namespace nGUI
	{
		struct jIGuiStatic;
		struct jIGuiListBox;

#define jINTERFACE_jIGuiListBox(XX) public:	\
	virtual jIGuiControl* BaseI() ##XX \
	virtual DWORD GetStyle() const ##XX \
	virtual int GetSize() const ##XX \
	virtual void SetMultiLineFlag( bool dwStyle ) ##XX \
	virtual void SetBorder( int nBorder, int nMargin ) ##XX \
	virtual void SetScrollBarWidth( int nWidth ) ##XX \
	virtual void AddItem( cstr  wszText, void *pData )##XX \
	virtual void InsertItem( int nIndex, cstr  wszText, void *pData )##XX \
	virtual void RemoveItem( int nIndex )##XX \
	virtual void RemoveItemByText( TCHAR *wszText )##XX \
	virtual void RemoveItemByData( void *pData )##XX \
	virtual void RemoveAllItems()##XX \
	/*virtual _jGuiListItem *GetItem( int nIndex )##XX \*/\
	virtual jIE* GetSelectItem( jIE* pePrevItem =0 )##XX \
	virtual void SelectItem( int nNewIndex )##XX \
	virtual jIGuiScrollBar* GetScrollBar() ##XX \

		jINTERFACE_END(jIGuiListBox);



#define jINTERFACE_jIGuiListBoxMulti(XX) public:	\
	virtual jIGuiControl* BaseI() ##XX \
	\
	/*GetSize() == colume size */\
	virtual int GetSize() const ##XX \
	virtual void SetMultiLineFlag( bool dwStyle ) ##XX \
	virtual void SetBorder( int nBorder, int nMargin ) ##XX \
	virtual void SetScrollBarWidth( int nWidth ) ##XX \
	\
	/*주의 : wszTextColumes.resize(pListBoxMulti->GetSize());를 반드시 미리 호출할것 */\
	virtual void AddItem( IN const std::vector<std::tstring>& wszTextColumes, IN const std::vector<void*> &pDataColumes )##XX \
	virtual void InsertItem( int nIndex, IN std::vector<std::tstring>& wszTextColumes, IN const std::vector<void*>&pDataColumes )##XX \
	virtual void RemoveItem( int nIndex )##XX \
	virtual void RemoveItemByText( int iColume,TCHAR *wszText )##XX \
	virtual void RemoveItemByData( int iColume,void *pData )##XX \
	virtual void RemoveAllItems()##XX \
	virtual jIE* GetSelectItem( OUT int &iColume ,IN jIE* pePrevItem = 0 )##XX \
	virtual void SelectItem( int nNewIndex )##XX \
	virtual jIGuiScrollBar* GetScrollBar() ##XX \
	\
	/*주의 : comumes.resize(pListBoxMulti->GetSize());를 반드시 미리 호출할것 */\
	virtual void GetHeaders(OUT std::vector<jIGuiStatic*>& comumes) ##XX \
	virtual void GetColumes(OUT std::vector<jIGuiListBox*>& comumes) ##XX \

	jINTERFACE_END(jIGuiListBoxMulti);

		

	}
}



#endif // __jIGuiListBox123423_header__
