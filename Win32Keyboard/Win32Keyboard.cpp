// Win32Keyboard.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Win32Keyboard.h"

#define MAX_LOADSTRING 100
//����ؼ�ID
#define IDB_Start 3301
#define IDE_Title 3302
#define IDE_Frequency 2203

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
int freq;                                       // ��ȡ��Ƶ��
char title[MAX_LOADSTRING], button[MAX_LOADSTRING]; //��ȡ�ı��⣬����ʹ��spy++�鿴���������



// �˴���ģ���а����ĺ�����ǰ������: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void OnButtonPushed(HWND hWnd);
//��ʱ���ص�����
void CALLBACK TimerProc(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime);


//���������
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,//handle to current instance
                     _In_opt_ HINSTANCE hPrevInstance,//handle to previous instance
                     _In_ LPTSTR    lpCmdLine,//command line ������һЩ�������ļ�·��
                     _In_ int       nCmdShow)//show state ������ʾ��ʽ����󻯺���С��
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32KEYBOARD, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32KEYBOARD));

	// ����Ϣѭ��: 
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
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); //�ṹ���С

	wcex.style			= CS_HREDRAW | CS_VREDRAW; //��������
	wcex.lpfnWndProc	= WndProc; //lpfnWndProc�Ǵ��ڹ��̵�ַ
	wcex.cbClsExtra		= 0; 
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance; //hInstance��ʵ�����
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32KEYBOARD)); //hIcon��ͼ����
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW); //hCursor�������
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1); //������ɫ
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32KEYBOARD); 
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	//�����ͼ�����������
	HWND hbutton, hstatic1, hstatic2, hstatic3, hedit1, hedit2;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDB_Start:
			//MessageBox(hWnd, _T("�ҵ��˿�ʼ"), _T("GG"), MB_OK);
			OnButtonPushed(hWnd);
			break;
		case IDE_Title:
			//MessageBox(hWnd, _T("�ҵ��˱����"), _T("GG"), MB_OK);
			break;
		case IDE_Frequency:
			//MessageBox(hWnd, _T("�ҵ��˱����"), _T("GG"), MB_OK);
			break;
		default:
			MessageBox(hWnd, _T("û���ҵ���Ӧ����Ϣ����"), _T("GG"), MB_OK);
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  �ڴ���������ͼ����...
		hbutton = CreateWindow(L"Button", L"��ʼˢ�£�", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			400, 300, 160, 65, hWnd, (HMENU)IDB_Start//����ID
			, hInst, NULL);
		hstatic1 = CreateWindow(L"Static", L"IE���������", WS_VISIBLE | WS_CHILD | SS_CENTER | SS_CENTERIMAGE,
			440, 20, 80, 45, hWnd, NULL
			, hInst, NULL);
		SendMessage(hstatic1, WM_SETFONT, (WPARAM)GetStockObject(17), 0);//��������

		hedit1 = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER,
			400, 70, 160, 45, hWnd, (HMENU)IDE_Title, hInst, NULL);
		
		hstatic2 = CreateWindow(L"Static", L"Ƶ��", WS_VISIBLE | WS_CHILD | SS_CENTER | SS_CENTERIMAGE,
			460, 120, 40, 45, hWnd, NULL
			, hInst, NULL);
		SendMessage(hstatic2, WM_SETFONT, (WPARAM)GetStockObject(17), 0);//��������

		hedit2 = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER,
			420, 170, 80, 45, hWnd, (HMENU)IDE_Frequency, hInst, NULL);

		hstatic3 = CreateWindow(L"Static", L"Hz", WS_VISIBLE | WS_CHILD | SS_CENTER | SS_CENTERIMAGE,
			500, 170, 40, 45, hWnd, NULL
			, hInst, NULL);
		SendMessage(hstatic3, WM_SETFONT, (WPARAM)GetStockObject(17), 0);//��������

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

// �����ڡ������Ϣ�������
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
	
	//��ȡ��������������
	int res = GetDlgItemText(hWnd,IDE_Title, (LPWSTR)title,sizeof(title));
	if (res == 0){
		MessageBox(hWnd, L"IE����δ����", _T("WARNING"), MB_OK);
		return;
	}
	//��ȡ�����ˢ��Ƶ��
	freq = GetDlgItemInt(hWnd, IDE_Frequency, false, true);
	//TODO��Ƶ��Ӧ��Ϊ���
	if (freq == 0){
		MessageBox(hWnd, L"Ƶ��δ����", _T("WARNING"), MB_OK);
		return;
	}
	GetDlgItemText(hWnd, IDB_Start, (LPWSTR)button,sizeof(button));
	CString txt;
	txt.Format(_T("%s"), button);
	if (txt == "��ʼˢ�£�"){
		SetTimer(hWnd, 1, 5000, TimerProc);
		SetDlgItemText(hWnd, IDB_Start, L"ֹͣˢ��!");
	}
	else{
		KillTimer(hWnd, 1);
		SetDlgItemText(hWnd, IDB_Start, L"��ʼˢ��!");
	}
}

void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime){
	CString wndTitle;
	wndTitle.Format(_T("%s"), title);
	HWND explor = FindWindow(NULL,wndTitle);
	if (explor == NULL){
		MessageBox(hwnd, wndTitle, _T("û���ҵ�����"), MB_OK);
		return;
	}
	//postmessage�����ں�̨��
	//PostMessage(explor, WM_KEYDOWN, VK_F5, 1);//ģ�����F5����
	//Sleep(50);
	//PostMessage(explor, WM_KEYUP, VK_F5, 1);//ģ�����F5̧��
	
	//api����keyboard_event�����ʹ���ڴ�����ǰ�ļ���״̬
	//SetForegroundWindow(explor);//ʹ�����ڼ���״̬
	//Sleep(50);
	//keybd_event(VK_F5, 0, 0, 0);

	//������ģ�����Ĳ���,ͬ����Ҫ������ǰ
	SetForegroundWindow(explor);//ʹ�����ڼ���״̬
	POINT pos = {0};
	ClientToScreen(explor,&pos);//��ȡ���ڵ�λ��
	SetCursorPos(pos.x + 200, pos.y + 200);//�������λ��
	//ģ�ⵥ������Ҽ�,�ᵯ���˵�
	mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
	Sleep(500);
	mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
	Sleep(500);
	//�����˵�����r����ˢ��0x52=R
	keybd_event(0x52, 0, 0, 0);
}