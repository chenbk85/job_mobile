// ���� ifdef ����� DLL���� ���������ϴ� �۾��� ���� �� �ִ� ��ũ�θ� ����� 
// ǥ�� ����Դϴ�. �� DLL�� ��� �ִ� ������ ��� ����ٿ� ���ǵ� _EXPORTS ��ȣ��
// �����ϵǸ�, �ٸ� ������Ʈ������ �� ��ȣ�� ������ �� �����ϴ�.
// �̷��� �ϸ� �ҽ� ���Ͽ� �� ������ ��� �ִ� �ٸ� ��� ������Ʈ������ 
// MSG_PRESENCE_DUMMY_CLIENT_DLL_API �Լ��� DLL���� �������� ������ ����, �� DLL��
// �� DLL�� �ش� ��ũ�η� ���ǵ� ��ȣ�� ���������� ������ ���ϴ�.
#ifdef TEMPLATE_VC2010_DLL_EXPORTS
#define MSG_PRESENCE_DUMMY_CLIENT_DLL_API __declspec(dllexport)
#else
#define MSG_PRESENCE_DUMMY_CLIENT_DLL_API __declspec(dllimport)
#endif



#include "util/jUtil.h"
#include "util/jConsoleDLL.h"

//--------------------------------------------------------------------------
class MSG_presence_client_DLL : public nCONSOLE::jConsoleDLL_Net
  //--------------------------------------------------------------------------
{
public:
  jINTERFACE_HEADER(jIConsoleDLL);

};

extern MSG_presence_client_DLL* g_pjConsoleDLL;
extern jIPlugIn_Connection* g_pCurrPlugInBE;

