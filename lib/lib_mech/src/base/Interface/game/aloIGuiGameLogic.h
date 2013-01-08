/* file : aloGuiGameLogic.h
Coder : by ALo (jung0582@hotmail.com)
Date : 2005-11-14 10:10:00
*/

#ifndef __aloGuiGameLogic_h23344dfg44g4eader__
#define __aloGuiGameLogic_h23344dfg44g4eader__
#pragma once
#include "jMessageObject.h"
#include "Interface/gui/jIGuiRender.h"

struct jIXmlEntity;

#ifndef jINTERFACE_BASE1_DEFINE
#define jINTERFACE_BASE1_DEFINE( x, y) struct x : public y { jINTERFACE_BASE(x);	};
#endif

#define jINTERFACE_aloIGuiGameLogic(x) public:	\

jINTERFACE_BASE1_DEFINE(aloIGuiGameLogic,jIMessageObject);

extern JBASE_API aloIGuiGameLogic* g_paloIGuiGameLogic;

#endif
