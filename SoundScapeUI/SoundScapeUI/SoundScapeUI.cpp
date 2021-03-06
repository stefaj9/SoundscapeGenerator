// WindowsProject1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SoundScapeUI.h"
#include "AudioChannel.h"
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <commctrl.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

void CreateControls(HWND hWnd, int num);
void UpdateOutsideValue(HWND hWnd);
void UpdateInsideValue(HWND hWnd);
void UpdateVolumeValue(HWND hWnd);

HWND outsideSlider;
HWND outsideValue;
HWND volumeSlider;

HWND insideSlider;
HWND insideValue;
HWND volumeValue;

MSG msg;
HACCEL hAccelTable;

AudioChannel outside;
AudioChannel inside;
long outsidePos, insidePos;


int BIRDS_1, BIRDS_2;
int RAIN_1;
int THUNDER_1;
int WIND_1, WIND_2, WIND_3;
int SCREAM_1;	
int HELI_1;
int GUNS_1;

int FIRE_1, FIRE_2;
int KETTLE_1;
int DRIP_1;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_SOUNDSCAPEUI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SOUNDSCAPEUI));
		
		return FALSE;
	}

	BIRDS_1 = outside.addAudioFile("Audio/Birds/birds1.wav");
	BIRDS_2 = outside.addAudioFile("Audio/Birds/birds2.wav");	
	RAIN_1 = outside.addAudioFile("Audio/Rain/rain1.wav");
	THUNDER_1 = outside.addAudioFile("Audio/Thunder/thunder1.wav");
	WIND_1 = outside.addAudioFile("Audio/Wind/wind1.wav");
	WIND_2 = outside.addAudioFile("Audio/Wind/wind2.wav");
	WIND_3 = outside.addAudioFile("Audio/Wind/wind3.wav");
	SCREAM_1 = outside.addAudioFile("Audio/Scream/scream1.wav");
	HELI_1 = outside.addAudioFile("Audio/Heli/heli1.wav");
	GUNS_1 = outside.addAudioFile("Audio/Guns/guns1.wav");

	FIRE_1 = inside.addAudioFile("Audio/Fire/fire1.wav");
	FIRE_2 = inside.addAudioFile("Audio/Fire/fire2.wav");
	KETTLE_1 = inside.addAudioFile("Audio/Kettle/kettle1.wav");
	DRIP_1 = inside.addAudioFile("Audio/Drip/drip1.wav");

	outsidePos = 0;
	insidePos = 0;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SOUNDSCAPEUI));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SOUNDSCAPEUI);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
		CW_USEDEFAULT, 0, 400, 350, nullptr, nullptr, hInstance, nullptr);

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
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	TCHAR greeting[] = _T("");
	switch (message)
	{
	case WM_CREATE:
		CreateControls(hWnd, 1);
		CreateControls(hWnd, 2);
		CreateControls(hWnd, 3);
		break;
	case WM_HSCROLL:
		UpdateOutsideValue(hWnd);
		UpdateInsideValue(hWnd);
		UpdateVolumeValue(hWnd);
		break;
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
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
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

void CreateControls(HWND hwnd, int num) {

	HWND hLeftLabel = CreateWindowW(L"Static", L"0",
		WS_CHILD | WS_VISIBLE, 0, 0, 10, 30, hwnd, (HMENU)1, NULL, NULL);

	HWND hRightLabel = CreateWindowW(L"Static", L"100",
		WS_CHILD | WS_VISIBLE, 0, 0, 30, 30, hwnd, (HMENU)2, NULL, NULL);

	if (num == 1) {
		CreateWindowW(L"Static", L"Outside", WS_CHILD | WS_VISIBLE,
			140, 40, 60, 30, hwnd, (HMENU)3, NULL, NULL);

		outsideValue = CreateWindowW(L"Static", L"0", WS_CHILD | WS_VISIBLE,
			310, 60, 30, 30, hwnd, (HMENU)3, NULL, NULL);
	}
	else if (num == 2) {
		CreateWindowW(L"Static", L"Inside", WS_CHILD | WS_VISIBLE,
			140, 100, 60, 30, hwnd, (HMENU)3, NULL, NULL);

		insideValue = CreateWindowW(L"Static", L"0", WS_CHILD | WS_VISIBLE,
			310, 120, 30, 30, hwnd, (HMENU)3, NULL, NULL);
	}
	else {
		CreateWindowW(L"Static", L"Volume Boost", WS_CHILD | WS_VISIBLE,
			120, 160, 100, 30, hwnd, (HMENU)3, NULL, NULL);

		volumeValue = CreateWindowW(L"Static", L"0", WS_CHILD | WS_VISIBLE,
			310, 180, 30, 30, hwnd, (HMENU)3, NULL, NULL);
	}


	INITCOMMONCONTROLSEX icex;

	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	//InitCommonControlsEx(&icex);

	if (num == 1) {
		outsideSlider = CreateWindowW(TRACKBAR_CLASSW, L"Trackbar Control",
			WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
			60, 60, 170, 30, hwnd, (HMENU)3, NULL, NULL);

		SendMessageW(outsideSlider, TBM_SETRANGE, TRUE, MAKELONG(0, 100));
		SendMessageW(outsideSlider, TBM_SETPAGESIZE, 0, 0);
		SendMessageW(outsideSlider, TBM_SETTICFREQ, 10, 0);
		SendMessageW(outsideSlider, TBM_SETPOS, FALSE, 0);
		SendMessageW(outsideSlider, TBM_SETBUDDY, TRUE, (LPARAM)hLeftLabel);
		SendMessageW(outsideSlider, TBM_SETBUDDY, FALSE, (LPARAM)hRightLabel);
	}
	else if(num == 2) {
		insideSlider = CreateWindowW(TRACKBAR_CLASSW, L"Trackbar Control",
			WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
			60, 120, 170, 30, hwnd, (HMENU)3, NULL, NULL);

		SendMessageW(insideSlider, TBM_SETRANGE, TRUE, MAKELONG(0, 100));
		SendMessageW(insideSlider, TBM_SETPAGESIZE, 0, 0);
		SendMessageW(insideSlider, TBM_SETTICFREQ, 10, 0);
		SendMessageW(insideSlider, TBM_SETPOS, FALSE, 0);
		SendMessageW(insideSlider, TBM_SETBUDDY, TRUE, (LPARAM)hLeftLabel);
		SendMessageW(insideSlider, TBM_SETBUDDY, FALSE, (LPARAM)hRightLabel);
	}
	else {
		volumeSlider = CreateWindowW(TRACKBAR_CLASSW, L"Trackbar Control",
			WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
			60, 180, 170, 30, hwnd, (HMENU)3, NULL, NULL);

		SendMessageW(volumeSlider, TBM_SETRANGE, TRUE, MAKELONG(0, 100));
		SendMessageW(volumeSlider, TBM_SETPAGESIZE, 0, 0);
		SendMessageW(volumeSlider, TBM_SETTICFREQ, 10, 0);
		SendMessageW(volumeSlider, TBM_SETPOS, FALSE, 0);
		SendMessageW(volumeSlider, TBM_SETBUDDY, TRUE, (LPARAM)hLeftLabel);
		SendMessageW(volumeSlider, TBM_SETBUDDY, FALSE, (LPARAM)hRightLabel);
	}


}

void UpdateOutsideValue(HWND hWnd) {

	LRESULT pos = SendMessageW(outsideSlider, TBM_GETPOS, 0, 0);
	wchar_t buf[4];
	wsprintfW(buf, L"%ld", pos);
	SetWindowTextW(outsideValue, buf);

	if (pos > 5) {
		outside.fadeInAudioFile(WIND_1, 4);
	}
	else {
		outside.fadeOutAudioFile(WIND_1, 4);
	}

	if (pos > 20 && pos < 40) {
		outside.fadeInAudioFile(BIRDS_1, 4);
	}
	else {
		outside.fadeOutAudioFile(BIRDS_1, 4);
	}

	if (pos > 30 && pos < 40) {
		outside.fadeInAudioFile(BIRDS_2, 4);
	}
	else {
		outside.fadeOutAudioFile(BIRDS_2, 4);
	}

	if (pos > 40) {
		outside.fadeInAudioFile(RAIN_1, 4);
	}
	else {
		outside.fadeOutAudioFile(RAIN_1, 4);
	}

	if (pos > 60) {
		outside.fadeInAudioFile(THUNDER_1, 2);
	}
	else {
		outside.fadeOutAudioFile(THUNDER_1, 4);
	}

	if (pos > 80) {
		outside.fadeInAudioFile(HELI_1, 4);
	}
	else {
		outside.fadeOutAudioFile(HELI_1, 3);
	}

	if (pos >= 100) {
		outside.fadeInAudioFile(GUNS_1, 1);
		outside.fadeInAudioFile(SCREAM_1, 2);
	}
	else {
		outside.fadeOutAudioFile(SCREAM_1, 2);
		outside.fadeOutAudioFile(GUNS_1, 1);
	}

	
	outsidePos = pos;
}

void UpdateInsideValue(HWND hWnd) {

	LRESULT pos = SendMessageW(insideSlider, TBM_GETPOS, 0, 0);
	wchar_t buf[4];
	wsprintfW(buf, L"%ld", pos);
	SetWindowTextW(insideValue, buf);

	if (pos > 0) {
		outside.fadeInFilter();
		inside.fadeInAudioFile(FIRE_2, 10);
	}
	else {
		outside.fadeOutFilter();
		inside.fadeOutAudioFile(FIRE_2, 2);
	}

	if (pos > 20) {
		inside.fadeInAudioFile(FIRE_1, 2);
	}
	else {
		inside.fadeOutAudioFile(FIRE_1, 2);
	}

	if (pos > 80) {
		inside.fadeInAudioFile(KETTLE_1, 2);
	}
	else {
		inside.fadeOutAudioFile(KETTLE_1, 2);
	}	

	if (outsidePos > 40 && pos > 0) {
		inside.fadeInAudioFile(DRIP_1, 4);
	}
	else {
		inside.fadeOutAudioFile(DRIP_1, 4);
	}

	insidePos = pos;
}

void UpdateVolumeValue(HWND hWnd) {

	LRESULT pos = SendMessageW(volumeSlider, TBM_GETPOS, 0, 0);
	wchar_t buf[4];
	wsprintfW(buf, L"%ld", pos);
	SetWindowTextW(volumeValue, buf);

	outside.setGlobalVolume(pos);
	inside.setGlobalVolume(pos);
}

