// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#ifndef _WIN32_WINNT		// Windows XP �̻󿡼��� ����� ����� �� �ֽ��ϴ�.                   
#define _WIN32_WINNT 0x0501	// �ٸ� ������ Windows�� �µ��� ������ ������ ������ �ֽʽÿ�.
#endif						

#include <stdarg.h> 
#include <stdio.h>
#if 0
#include <string>
//#define SQPLUS_SUPPORT_STD_STRING
#define SQPLUS_SUPPORT_SQ_STD_STRING
#endif
//#define SQPLUS_CONST_OPT
#include "interface/Squirrel/jISquirrel.h"

#include "common/jCommon.h"

using namespace nMech;
using namespace nMech::nSQ;



// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
