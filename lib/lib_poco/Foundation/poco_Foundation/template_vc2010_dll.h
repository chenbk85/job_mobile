// ���� ifdef ����� DLL���� ���������ϴ� �۾��� ���� �� �ִ� ��ũ�θ� ����� 
// ǥ�� ����Դϴ�. �� DLL�� ��� �ִ� ������ ��� ����ٿ� ���ǵ� _EXPORTS ��ȣ��
// �����ϵǸ�, �ٸ� ������Ʈ������ �� ��ȣ�� ������ �� �����ϴ�.
// �̷��� �ϸ� �ҽ� ���Ͽ� �� ������ ��� �ִ� �ٸ� ��� ������Ʈ������ 
// TEMPLATE_VC2010_DLL_API �Լ��� DLL���� �������� ������ ����, �� DLL��
// �� DLL�� �ش� ��ũ�η� ���ǵ� ��ȣ�� ���������� ������ ���ϴ�.
#ifdef Foundation_EXPORTS
#define TEMPLATE_VC2010_DLL_API __declspec(dllexport)
#else
#define TEMPLATE_VC2010_DLL_API __declspec(dllimport)
#endif

// �� Ŭ������ template_vc2010_dll.dll���� ������ ���Դϴ�.
class TEMPLATE_VC2010_DLL_API Ctemplate_vc2010_dll {
public:
	Ctemplate_vc2010_dll(void);
	// TODO: ���⿡ �޼��带 �߰��մϴ�.
};

extern TEMPLATE_VC2010_DLL_API int ntemplate_vc2010_dll;

TEMPLATE_VC2010_DLL_API int fntemplate_vc2010_dll(void);
