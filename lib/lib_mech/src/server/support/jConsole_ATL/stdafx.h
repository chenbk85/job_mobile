// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

// Change these values to use different versions
#define WINVER		0x0400
//#define _WIN32_WINNT	0x0400
#define _WIN32_IE	0x0400
#define _RICHEDIT_VER	0x0100

#include <atlbase.h>
#include <atlapp.h>

#include <atlwin.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlstr.h>

#include <list>

#include "common/jCommon.h"
#include "interface/net/jINet.h"
#include "interface/jIConsoleDLL.h"
#include "header/jDllLoader.h"
#include "interface/jIConsoleDlg.h"
#include "interface/jIConsoleCmd.h"


using namespace nMech;
using namespace nMech::nNET;

