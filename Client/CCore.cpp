#include "pch.h"
#include "CCore.h"
#include "CObject.h"

// dynamic allocate 이용하는 방법
// 정적 멤버변수 초기화
// CCore* CCore::g_pInst = nullptr;

CObject g_obj;

/**
* Window에서 제공하는 함수에서 사용하는, 성공/실패를 나타내는 매크로 : S_OK, E_FAIL
* Window에서 제공하는 함수에서 자주 사용하는 구문(구조)
* HRESULT hr;
* if (FAILED(hr)) { }
*/
int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정
	RECT ClientArea = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&ClientArea, WS_OVERLAPPEDWINDOW, true);																// 작업 영역을 포함한 윈도우의 크기를 구한다.
	SetWindowPos(m_hWnd, NULL, 100, 100, ClientArea.right - ClientArea.left, ClientArea.bottom - ClientArea.top, 0);		// 윈도우 위치와 크기 조정

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
* Message 기반 방식을 사용하지 않고 코드가 돌아가는 순간 입력이 들어왔는지 아닌 지를 따져야되기 때문에 '비동기 키 입출력 함수'를 쓴다.
* -> '비동기 키 입출력 함수'를 사용하기 때문에, 윈도우의 focusing 여부를 판단해서 동작하게 만들어야 한다.
*/
void CCore::Update()
{
	// 현재 키가 눌렸는지 판단
	/**
	* GetAsyncKeyState() : 현재 키 상태를 bit값으로 조합하여 반환
	* -> 현재 순간에 눌렸는지 확인하고 싶으면 return 값의 상위 bit를 체크(return 값과 0x8000를 AND 연산)한 결과를 보면 된다.
	*	 -> true : 눌림 / false : 떼어짐
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
	// Rendering 작업
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
