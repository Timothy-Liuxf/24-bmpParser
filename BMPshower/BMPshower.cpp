

#include "framework.h"
#include "resource.h"
#include "msgproc.h"
#include "glb.h"
#include "str.h"

#define MAX_LOADSTRING 100


// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPTSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    
    // TODO: 在此处放置代码。

    // 初始化全局字符串

    if (!MyRegisterClass(hInstance)) {
        MessageBox(NULL, _T("Register failed!"), error, NULL);
    }

    // 执行应用程序初始化:
    if (!InitInstance(hInstance, nCmdShow))
    {
        MessageBox(NULL, _T("Failed!"), error, NULL);
        return FALSE;
    }


    MSG msg;
    HACCEL hAccel = LoadAccelerators(hInst, MAINMENUNAME); 
    hBmMain = LoadBitmap(hInst, TEXT("XP")); 

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(hWndMain, hAccel, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    delete[] bmpBuf;        //释放缓冲区

    return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInst, iconName);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAINMENUNAME;
    wcex.lpszClassName = wndClassName;
    wcex.hIconSm = LoadIcon(wcex.hInstance, iconName);

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 将实例句柄存储在全局变量中

    HWND hWnd = CreateWindow(wndClassName, wndTitleName, WS_VISIBLE | WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_BORDER | WS_MINIMIZEBOX,
        CW_USEDEFAULT, 0, MAIN_WIN_WIDTH, MAIN_WIN_HEIGHT, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    hWndMain = hWnd; 

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

