// ���� ifdef ����� DLL���� ���������ϴ� �۾��� ���� �� �ִ� ��ũ�θ� ����� 
// ǥ�� ����Դϴ�. �� DLL�� ��� �ִ� ������ ��� ����ٿ� ���ǵ� _EXPORTS ��ȣ��
// �����ϵǸ�, �ٸ� ������Ʈ������ �� ��ȣ�� ������ �� �����ϴ�.
// �̷��� �ϸ� �ҽ� ���Ͽ� �� ������ ��� �ִ� �ٸ� ��� ������Ʈ������ 
// BCOMMONCLIENT_API �Լ��� DLL���� �������� ������ ����, �� DLL��
// �� DLL�� �ش� ��ũ�η� ���ǵ� ��ȣ�� ���������� ������ ���ϴ�.
#ifdef BCOMMONCLIENT_EXPORTS
#define BCOMMONCLIENT_API __declspec(dllexport)
#else
#define BCOMMONCLIENT_API __declspec(dllimport)
#endif

// �� Ŭ������ BCommonClient.dll���� ������ ���Դϴ�.
class BCOMMONCLIENT_API CBCommonClient {
public:
	CBCommonClient(void);
	// TODO: ���⿡ �޼��带 �߰��մϴ�.
};

extern BCOMMONCLIENT_API int nBCommonClient;

BCOMMONCLIENT_API int fnBCommonClient(void);
