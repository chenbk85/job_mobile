// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

// os system header
#include <stdio.h>
#include <tchar.h>
#include <stddef.h>
#include <exception>
#include <stdlib.h>

// STL
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


// BOOST
#include <boost/thread.hpp>
#include <boost/any.hpp>
#include <boost/asio.hpp>
#include <boost/make_shared.hpp>
#include "boost/function.hpp"
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/lexical_cast.hpp>
#include "boost/filesystem.hpp"
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include <boost/thread/thread.hpp>

//#include "header/jDefine.h"
//#include "header/jTypedef_type.h"



// �ܺ� third party �ش�.
#include "yaml-cpp/yaml.h"
#include "header/lib_poco_header.h"
#include "../common/MSG_presence_common.h"

#pragma comment(lib, "lib_thrift.lib")
#pragma comment(lib, "poco_Foundation.lib")
#pragma comment(lib, "poco_XML.lib")
#pragma comment(lib, "poco_Util.lib")
#pragma comment(lib, "poco_Net.lib")

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.


#include "log.hpp"

