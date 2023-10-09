#include "pch.h"
#include "CCore.h"
#include "CObject.h"

// dynamic allocate �̿��ϴ� ���
// ���� ������� �ʱ�ȭ
// CCore* CCore::g_pInst = nullptr;

CObject g_obj;

/**
* Window���� �����ϴ� �Լ����� ����ϴ�, ����/���и� ��Ÿ���� ��ũ�� : S_OK, E_FAIL
* Window���� �����ϴ� �Լ����� ���� ����ϴ� ����(����)
* HRESULT hr;
* if (FAILED(hr)) { }
*/
int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// �ػ󵵿� �°� ������ ũ�� ����
	RECT ClientArea = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&ClientArea, WS_OVERLAPPEDWINDOW, true);																// �۾� ������ ������ �������� ũ�⸦ ���Ѵ�.
	SetWindowPos(m_hWnd, NULL, 100, 100, ClientArea.right - ClientArea.left, ClientArea.bottom - ClientArea.top, 0);		// ������ ��ġ�� ũ�� ����

	m_hDeviceContext = GetDC(m_hWnd);

	g_obj.m_ptPos = POINT{ m_ptResolution.x / 2, m_ptResolution.y / 2 };
	g_obj.m_ptScale = POINT{ 100, 100 };

	HRESULT hr = S_OK;

	if (FAILED(hr))
	{

	}

	return hr;
}

void CCore::Progress()
{
	Update();

	Render();
	
}

/**
* Message ��� ����� ������� �ʰ� �ڵ尡 ���ư��� ���� �Է��� ���Դ��� �ƴ� ���� �����ߵǱ� ������ '�񵿱� Ű ����� �Լ�'�� ����.
* -> '�񵿱� Ű ����� �Լ�'�� ����ϱ� ������, �������� focusing ���θ� �Ǵ��ؼ� �����ϰ� ������ �Ѵ�.
*/
void CCore::Update()
{
	// ���� Ű�� ���ȴ��� �Ǵ�
	/**
	* GetAsyncKeyState() : ���� Ű ���¸� bit������ �����Ͽ� ��ȯ
	* -> ���� ������ ���ȴ��� Ȯ���ϰ� ������ return ���� ���� bit�� üũ(return ���� 0x8000�� AND ����)�� ����� ���� �ȴ�.
	*	 -> true : ���� / false : ������
	*/
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		g_obj.m_ptPos.x -= 10;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		g_obj.m_ptPos.x += 10;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		g_obj.m_ptPos.y -= 10;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		g_obj.m_ptPos.y += 10;
	}
}

void CCore::Render()
{
	// Rendering �۾�
	Rectangle(m_hDeviceContext,
		g_obj.m_ptPos.x - g_obj.m_ptScale.x / 2,
		g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2,
		g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2, 
		g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2);
}

CCore::CCore() :
	m_hWnd(NULL),
	m_ptResolution{},
	m_hDeviceContext(NULL)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDeviceContext);
}
