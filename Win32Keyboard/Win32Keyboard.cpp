// Win32Keyboard.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Win32Keyboard.h"

#define MAX_LOADSTRING 100
//定义控件ID
#define IDB_Start 3301
#define IDE_Title 3302
#define IDE_Frequency 2203

// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
int freq;                                       // 获取的频率
char title[MAX_LOADSTRING], button[MAX_LOADSTRING]; //获取的标题，可以使用spy++查看浏览器标题



// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void OnButtonPushed(HWND hWnd);
//定时器回调函数
void CALLBACK TimerProc(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime);


//主程序入口
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,//handle to current instance
                     _In_opt_ HINSTANCE hPrevInstance,//handle to previous instance
                     _In_ LPTSTR    lpCmdLine,//command line 主函数一些参数如文件路径
                     _In_ int       nCmdShow)//show state 进程显示方式如最大化和最小化
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32KEYBOARD, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32KEYBOARD));

	// 主消息循环: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  函数:  MyRegisterClass()
//
//  目的:  注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); //结构体大小

	wcex.style			= CS_HREDRAW | CS_VREDRAW; //窗口类风格
	wcex.lpfnWndProc	= WndProc; //lpfnWndProc是窗口过程地址
	wcex.cbClsExtra		= 0; 
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance; //hInstance是实例句柄
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32KEYBOARD)); //hIcon是图标句柄
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW); //hCursor是鼠标句柄
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1); //背景颜色
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32KEYBOARD); 
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数:  InitInstance(HINSTANCE, int)
//
//   目的:  保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	//定义绘图代码所需变量
	HWND hbutton, hstatic1, hstatic2, hstatic3, hedit1, hedit2;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDB_Start:
			//MessageBox(hWnd, _T("找到了开始"), _T("GG"), MB_OK);
			OnButtonPushed(hWnd);
			break;
		case IDE_Title:
			//MessageBox(hWnd, _T("找到了标题框"), _T("GG"), MB_OK);
			break;
		case IDE_Frequency:
			//MessageBox(hWnd, _T("找到了标题框"), _T("GG"), MB_OK);
			break;
		default:
			MessageBox(hWnd, _T("没有找到对应的消息处理"), _T("GG"), MB_OK);
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  在此添加任意绘图代码...
		hbutton = CreateWindow(L"Button", L"开始刷新！", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			400, 300, 160, 65, hWnd, (HMENU)IDB_Start//定义ID
			, hInst, NULL);
		hstatic1 = CreateWindow(L"Static", L"IE浏览器标题", WS_VISIBLE | WS_CHILD | SS_CENTER | SS_CENTERIMAGE,
			440, 20, 80, 45, hWnd, NULL
			, hInst, NULL);
		SendMessage(hstatic1, WM_SETFONT, (WPARAM)GetStockObject(17), 0);//更改字体

		hedit1 = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER,
			400, 70, 160, 45, hWnd, (HMENU)IDE_Title, hInst, NULL);
		
		hstatic2 = CreateWindow(L"Static", L"频率", WS_VISIBLE | WS_CHILD | SS_CENTER | SS_CENTERIMAGE,
			460, 120, 40, 45, hWnd, NULL
			, hInst, NULL);
		SendMessage(hstatic2, WM_SETFONT, (WPARAM)GetStockObject(17), 0);//更改字体

		hedit2 = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER,
			420, 170, 80, 45, hWnd, (HMENU)IDE_Frequency, hInst, NULL);

		hstatic3 = CreateWindow(L"Static", L"Hz", WS_VISIBLE | WS_CHILD | SS_CENTER | SS_CENTERIMAGE,
			500, 170, 40, 45, hWnd, NULL
			, hInst, NULL);
		SendMessage(hstatic3, WM_SETFONT, (WPARAM)GetStockObject(17), 0);//更改字体

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
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

void OnButtonPushed(HWND hWnd){
	
	//获取输入的浏览器标题
	int res = GetDlgItemText(hWnd,IDE_Title, (LPWSTR)title,sizeof(title));
	if (res == 0){
		MessageBox(hWnd, L"IE标题未设置", _T("WARNING"), MB_OK);
		return;
	}
	//获取输入的刷新频率
	freq = GetDlgItemInt(hWnd, IDE_Frequency, false, true);
	//TODO：频率应该为间隔
	if (freq == 0){
		MessageBox(hWnd, L"频率未设置", _T("WARNING"), MB_OK);
		return;
	}
	GetDlgItemText(hWnd, IDB_Start, (LPWSTR)button,sizeof(button));
	CString txt;
	txt.Format(_T("%s"), button);
	if (txt == "开始刷新！"){
		SetTimer(hWnd, 1, 5000, TimerProc);
		SetDlgItemText(hWnd, IDB_Start, L"停止刷新!");
	}
	else{
		KillTimer(hWnd, 1);
		SetDlgItemText(hWnd, IDB_Start, L"开始刷新!");
	}
}

void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime){
	CString wndTitle;
	wndTitle.Format(_T("%s"), title);
	HWND explor = FindWindow(NULL,wndTitle);
	if (explor == NULL){
		MessageBox(hwnd, wndTitle, _T("没有找到窗口"), MB_OK);
		return;
	}
	//postmessage可以在后台发
	//PostMessage(explor, WM_KEYDOWN, VK_F5, 1);//模拟键盘F5按下
	//Sleep(50);
	//PostMessage(explor, WM_KEYUP, VK_F5, 1);//模拟键盘F5抬起
	
	//api函数keyboard_event则必须使窗口处于最前的激活状态
	//SetForegroundWindow(explor);//使窗口在激活状态
	//Sleep(50);
	//keybd_event(VK_F5, 0, 0, 0);

	//下面是模拟鼠标的操作,同样需要窗口最前
	SetForegroundWindow(explor);//使窗口在激活状态
	POINT pos = {0};
	ClientToScreen(explor,&pos);//获取窗口的位置
	SetCursorPos(pos.x + 200, pos.y + 200);//设置鼠标位置
	//模拟单击鼠标右键,会弹出菜单
	mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
	Sleep(500);
	mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
	Sleep(500);
	//弹出菜单后按下r键会刷新0x52=R
	keybd_event(0x52, 0, 0, 0);
}