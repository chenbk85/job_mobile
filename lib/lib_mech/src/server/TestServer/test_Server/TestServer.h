// ���� ifdef ����� DLL���� ���������ϴ� �۾��� ���� �� �ִ� ��ũ�θ� ����� 
// ǥ�� ����Դϴ�. �� DLL�� ��� �ִ� ������ ��� ����ٿ� ���ǵ� _EXPORTS ��ȣ��
// �����ϵǸ�, ������ DLL�� ����ϴ� �ٸ� ������Ʈ������ �� ��ȣ�� ������ �� �����ϴ�.
// �̷��� �ϸ� �ҽ� ���Ͽ� �� ������ ��� �ִ� �ٸ� ��� ������Ʈ������ 
// TESTSERVER_API �Լ��� DLL���� �������� ������ ����, �� DLL��
// �� DLL�� �ش� ��ũ�η� ���ǵ� ��ȣ�� ���������� ������ ���ϴ�.
#ifdef TESTSERVER_EXPORTS
#define TESTSERVER_API __declspec(dllexport)
#else
#define TESTSERVER_API __declspec(dllimport)
#endif


#include "util/jUtil.h"
#include "util/jConsoleDLL.h"

//--------------------------------------------------------------------------
class Aq_NetDLL : public nCONSOLE::jConsoleDLL_Net
	//--------------------------------------------------------------------------
{
public:
	jINTERFACE_HEADER(jIConsoleDLL);

};

extern Aq_NetDLL* g_pjConsoleDLL;
