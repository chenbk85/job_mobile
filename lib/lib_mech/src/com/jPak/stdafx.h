// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� �����Դϴ�.
#include <windows.h>

#define NOT_USE_JCGAME_MEMORY_MANAGER
/* *_* by icandoit : 2006-05-15 15:32:12

#include "jc\platform.h"
#define USE_NEWPOOL
#include <jc\jcMemoryManager.h>
*/ //*_* by icandoit : 2006-05-15 15:32:13


#include "common/jCommon.h"
#include <set>
#include "jc\\smartptr.h"
#include "interface\\jIPak.h"
#include "jc\\IStreamEngine.h"


using namespace std;

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
