// Client.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Client.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // 윈도우의 제목 string
WCHAR szWindowClass[MAX_LOADSTRING];            // 윈도우 클래스의 키 값

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// SAL 언어(주석 언어) : 해당 variable, function의 의미를 적어놓은 것
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,                 // 실행된 프로세스가 시작하는 주소
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,                  // 프로그램 시작 시, 들어오는 문자열(추가 명령어)
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    /*
    LoadStringW() : ID에 해당된 caption 값을 가져와 해당 string에 넣어주는 function
    - ID는 string table 내에서 확인 가능
    */
    MyRegisterClass(hInstance); // -> 윈도우 구조체(정보) 초기화

    // 윈도우 생성
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    /*
    * 윈도우는 인터페이스 역할!
    * -> 인터페이스 : 사용자와 프로그램이 소통할 수 있도록 도와주는 것
    
    * 프로세스 != 윈도우
    * 특정 프로세스는 윈도우를 가질 수도 있고, 아닐 수도 있다.
    * 특정 프로세스는 여러 개의 윈도우를 가질 수 있다.
    */

    /* 단축키 테이블 정보 로딩 */
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));
    /* 리소스 뷰에서 Accelator 부분에 단축키 table이 존재한다. */

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))                     // -> message를 받아온다.
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // -> 단축키 message 인지 확인
        {
            TranslateMessage(&msg);                             // -> message 분석
            DispatchMessage(&msg);                              // -> message 처리
        }
    }

    /**
    * Window OS는 포커싱된 process쪽으로 message들 넣어주고, process는 받은 message를 처리한다.
    * message 안에는 message가 발생한 윈도우 정보를 가지고 있다.
    * -> 때문에 message를 발생시킨 윈도우가 message를 처리한다.(프로시저 함수)
    */

    /**
    * GetMesaage()의 특징
    * - message queue에서 message를 확인 될 때까지 대기한다.(메세지가 없으면 종료하지 않고 대기한다.)
    * - false를 반환하는 경우 : (msg.message == WM_QUIT)이 true인 경우
    *   -> 프로그램 종료
    */

    /**
    * Window OS는 메세지 반응형으로 동작한다.
    */

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;                                                  // 프로시져 함수 등록
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT);                             // 메뉴바를 설정하는 곳
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

/**
* message에 따라 사용자가 처리를 custom할 수 있다.
* custom하지 않는 message는 기본 처리기에서 처리
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            /**
            * 윈도우 좌표
            * - 좌상단 : (0, 0) / 우하단 : (End_Width, End_Height)
            * - 단위 : pixel
            *   -> pixel 하나하나는 memory이다!
            */
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);        // -> 윈도우에서 제공하는 기본 프로시져
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
