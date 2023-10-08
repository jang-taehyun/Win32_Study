// Client.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Client.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
HWND g_hwnd;                                    // ���� ������ handle
WCHAR szTitle[MAX_LOADSTRING];                  // �������� ���� string
WCHAR szWindowClass[MAX_LOADSTRING];            // ������ Ŭ������ Ű ��

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// SAL ���(�ּ� ���) : �ش� variable, function�� �ǹ̸� ������� ��
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,                 // ����� ���μ����� �����ϴ� �ּ�
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,                  // ���α׷� ���� ��, ������ ���ڿ�(�߰� ��ɾ�)
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    /*
    LoadStringW() : ID�� �ش�� caption ���� ������ �ش� string�� �־��ִ� function
    - ID�� string table ������ Ȯ�� ����
    */
    MyRegisterClass(hInstance); // -> ������ ����ü(����) �ʱ�ȭ

    // ������ ����
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    /*
    * ������� �������̽� ����!
    * -> �������̽� : ����ڿ� ���α׷��� ������ �� �ֵ��� �����ִ� ��
    
    * ���μ��� != ������
    * Ư�� ���μ����� �����츦 ���� ���� �ְ�, �ƴ� ���� �ִ�.
    * Ư�� ���μ����� ���� ���� �����츦 ���� �� �ִ�.
    */

    /* ����Ű ���̺� ���� �ε� */
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));
    /* ���ҽ� �信�� Accelator �κп� ����Ű table�� �����Ѵ�. */

    MSG msg;

    /**
    * GetMessage()�� ����ϴ� ����, ������ message�� �߻���Ű�� ��� : Timer�� �̿��� ������ message�� �߻���Ų��.
    * -> 1 parameter : ������ handle
    * -> 2 parameter : Timer ID
    * -> 3 parameter : �����ð�
    * -> 4 parameter : Timer �߻� �� ���� ȣ��Ǵ� fucntion pointer
    * -> SetTimer() �Լ����� 3��° parameter�� 1000�� ������ Window OS������ 1�ʷ� �ν��Ѵ�.
    */

    // Ÿ�̸� ����
    SetTimer(g_hwnd, 10, 0, nullptr);

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))                     // -> message�� �޾ƿ´�.
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // -> ����Ű message ���� Ȯ��
        {
            TranslateMessage(&msg);                             // -> message �м�
            DispatchMessage(&msg);                              // -> message ó��
        }
    }

    /**
    * Window OS�� ��Ŀ�̵� process������ message�� �־��ְ�, process�� ���� message�� ó���Ѵ�.
    * message �ȿ��� message�� �߻��� ������ ������ ������ �ִ�.
    * -> ������ message�� �߻���Ų �����찡 message�� ó���Ѵ�.(���ν��� �Լ�)
    */

    /**
    * GetMesaage()�� Ư¡
    * - message queue���� message�� Ȯ�� �� ������ ����Ѵ�.(�޼����� ������ �������� �ʰ� ����Ѵ�.)
    * - false�� ��ȯ�ϴ� ��� : (msg.message == WM_QUIT)�� true�� ���
    *   -> ���α׷� ����
    */

    /**
    * Window OS�� �޼��� ���������� �����Ѵ�.
    */

    // Ÿ�̸� ����
    KillTimer(g_hwnd, 10);

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
    wcex.lpfnWndProc    = WndProc;                                                  // ���ν��� �Լ� ���
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT);                             // �޴��ٸ� �����ϴ� ��
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

   g_hwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hwnd)
   {
      return FALSE;
   }

   ShowWindow(g_hwnd, nCmdShow);
   UpdateWindow(g_hwnd);

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
* message�� ���� ����ڰ� ó���� custom�� �� �ִ�.
* custom���� �ʴ� message�� �⺻ ó���⿡�� ó��
* 
* wParam : ����/������ Ű���� ����
* lParam : ���콺 ��ǥ ����
*/

#include <vector>
using std::vector;

struct tObjInfo
{
    POINT g_ptObjectPosition;
    POINT g_ptObjectScale;
};

vector<tObjInfo> g_vecInfo;

// �»��
POINT g_ptLT;
// ���ϴ�
POINT g_ptRB;

bool bLbtnDown = false;

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
     /* 
     WM_PAINT message�� �߻��ϴ� ��� : ��ȿȭ ����(invalidate)�� �߻��ϴ� ���
     -> ��ȿȭ ����(invalidate)�� �߻��ϴ� ��� : �����찡 ȭ�� �󿡼� ������ٰ� �ٽ� ��Ÿ�� ��
     */
    case WM_PAINT:
        {
            /**
            * ������ ��ǥ
            * - �»�� : (0, 0) / ���ϴ� : (End_Width, End_Height)
            * - ���� : pixel
            *   -> pixel �ϳ��ϳ��� memory�̴�!
            *      -> pixel �� ĭ�� �޸𸮴� RGB�� 1byte��, �� 3byte�̴�.
            * 
            * Handle : kernel object(Window OS���� ���� ��ü)�� ����Ű�� ������ ID
            * - Window OS���� �����ϴ� Object(kernel object)�� handle�� WIN API�� �־� control�Ѵ�.
            * - kernel object�� ���¸� �����ϱ� ���� �� ���¿� �´� handle Ÿ���� ���������.(������ �ڷ������� �������)
            * 
            * Device Context : Rendering �۾��� �����ϱ� ���� �ʿ��� data���� ����ü
            * - �����쿡�� Rendering �۾��� �ϱ� ���ؼ��� �ݵ�� Device Context�� �̿��ؾ� �Ѵ�.
            * - Default PEN�� BRUSH : ������ �⺻ PEN, �Ͼ�� �⺻ BRUSH
            */
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // TODO: Add any drawing code that uses hdc here...

            /*
            WIN32 SDK���� Rendering �ڵ� ���� ����
            1. Device Context�� �����ϰ� �ڵ� ���� �޾ƿ´�.
            1. PEN, BRUSH�� �����Ѵ�.
            2. ������ PEN�� BRUSH�� Device Context�� �����ϰ�, Default PEN�� BRUSH�� ����Ѵ�.
            3. Rendering ����
            4. Device Context�� Default PEN�� BRUSH�� �ǵ����ش�.
            5. ������ PEN�� BRUSH�� �����Ѵ�.
            */

            // PEN�� BRUSH ����(������ PEN�� BRUSH�� kernel object)
            // GetStockObject() : ���� ����ϴ�(�Ǵ� �̹� �޸� �� �����ϴ�) PEN, BRUSH ���� �̸� ����� ���� Object���� ã�� function
            // -> GetStockObject()�� �ҷ��� Object�� ���� ��û�� �ϸ� �ȵȴ�.
            HPEN hRedPen = CreatePen(PS_DOT, 3, COLORREF(RGB(0, 255, 255)));
            // HBRUSH hBlueBrush = CreateSolidBrush(COLORREF(RGB(0, 0, 255)));
            HBRUSH hBlueBrush = (HBRUSH)GetStockObject(DKGRAY_BRUSH);

            // Device Context�� ������ PEN�� BRUSH�� �����ϰ� default PEN�� BRUSH�� ���
            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

            // Rendering
            if (bLbtnDown)
            {
                Rectangle(hdc,
                    g_ptLT.x, g_ptLT.y,
                    g_ptRB.x, g_ptRB.y);
            }
            for (size_t i = 0; i < g_vecInfo.size(); i++)
            {
                Rectangle(hdc,
                    g_vecInfo[i].g_ptObjectPosition.x - g_vecInfo[i].g_ptObjectScale.x / 2,
                    g_vecInfo[i].g_ptObjectPosition.y - g_vecInfo[i].g_ptObjectScale.y / 2,
                    g_vecInfo[i].g_ptObjectPosition.x + g_vecInfo[i].g_ptObjectScale.x / 2,
                    g_vecInfo[i].g_ptObjectPosition.y + g_vecInfo[i].g_ptObjectScale.y / 2);
            }
            

            // Device Context�� default PEN�� BRUSH�� �ٽ� �������ְ�, ������ PEN�� BRUSH�� ����
            SelectObject(hdc, hDefaultPen);
            DeleteObject(hRedPen);

            SelectObject(hdc, hDefaultBrush);
            // DeleteObject(hBlueBrush);

            EndPaint(hWnd, &ps);
        }
        break;
    // Ű���� ��ư down message
    case WM_KEYDOWN:
        {
            switch (wParam)
            {
                //  ����Ű �Ʒ�
                case VK_DOWN:
                // S ��ư
                case 'S':
                    {
                        // g_ptObjectPosition.y += 10;
                        InvalidateRect(hWnd, nullptr, true);        // -> ������ invalidate�� �߻���Ű�� function
                    }
                    break;
                default:
                    break;
            }
        }
        break;
    // ���� ���콺 ��ư down message
    case WM_LBUTTONDOWN:
        {
            // ���콺 X ��ǥ
            g_ptLT.x= LOWORD(lParam);
            // ���콺 Y ��ǥ
            g_ptLT.y = HIWORD(lParam);

            bLbtnDown = true;
        }
        break;
    // ���콺 ������ message
    case WM_MOUSEMOVE:
        {
            /**
            * ���� ȭ���� �����Ÿ��� ������ ����� ȭ���� ���� Ÿ�̹�(���� ����)�� �ٸ��� ������
            * -> ���� �ý��ۿ��� ����� ȭ���� ���� Ÿ�̹��� Rendering ���� �� ���� �ְ�, �����츦 clear�ϴ� ������ ���� �ְ�, Rendering�� ��� �� ���� ���̴�.
            * -> ��, Rendering�� �ϴ� �����찡 1���̱� ������, ������� Rendering�Ǵ� ������ ������, ����� ȭ��(Rendering�� �̹���)�� �����ϴ� ������ Rendering�Ǵ� ������
            *    �¹��� ȭ���� �����̴� ��ó�� ���̱� �����̴�.
            * -> �ذ�� : Rendering �ϴ� �����츦 2���� ����, �ϼ��� �̹����� �����ش�. 
            */
            if (bLbtnDown)
            {
                g_ptRB.x = LOWORD(lParam);
                g_ptRB.y = HIWORD(lParam);

                
            }
            InvalidateRect(hWnd, nullptr, true);
        }
        break;
    // ���� ���콺 ��ư up message
    case WM_LBUTTONUP:
        {
            tObjInfo info = {};
            info.g_ptObjectPosition.x = (g_ptLT.x + g_ptRB.x) / 2;
            info.g_ptObjectPosition.y = (g_ptLT.y + g_ptRB.y) / 2;
            info.g_ptObjectScale.x = abs(g_ptLT.x - g_ptRB.x);
            info.g_ptObjectScale.y = abs(g_ptLT.y - g_ptRB.y);

            g_vecInfo.push_back(info);
            bLbtnDown = false;
            InvalidateRect(hWnd, nullptr, true);
        }
        break;
    // Timer�� �߻���Ű�� messsage
    case WM_TIMER:
        {
            InvalidateRect(hWnd, nullptr, true);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);        // -> �����쿡�� �����ϴ� �⺻ ���ν���
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
