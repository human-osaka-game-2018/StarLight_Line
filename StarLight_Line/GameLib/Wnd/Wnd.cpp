﻿#include "Wnd.h"

#include <windows.h>

#include "Data\RectSize.h"

Wnd::Wnd(const HINSTANCE hInst, const TCHAR* pAppName)
{
	ZeroMemory(&m_msg, sizeof(MSG));

	Create(hInst, pAppName);
}

BOOL Wnd::ExistsWinMSG()
{
	if (PeekMessage(&m_msg, NULL, 0U, 0U, PM_REMOVE))
	{
		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);

		return TRUE;
	}

	return FALSE;
}

VOID Wnd::Create(const HINSTANCE hInst, const TCHAR* pAppName)
{
	WNDCLASSEX wndclass;
	wndclass.cbSize			= sizeof(wndclass);
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc	= WndProc;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= hInst;
	wndclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= pAppName;
	wndclass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndclass);

	m_hWnd = CreateWindow(
				pAppName,pAppName,
				WS_OVERLAPPEDWINDOW | WS_VISIBLE,
				CW_USEDEFAULT, CW_USEDEFAULT, 
				(INT)m_WND_SIZE.m_x, (INT)m_WND_SIZE.m_y, 
				NULL, NULL, 
				hInst,
				NULL);

	ResizeWnd();

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return;
}

VOID Wnd::ResizeWnd() const
{
	RECT wndRect;
	GetWindowRect(m_hWnd, &wndRect);

	RECT clientRect;
	GetClientRect(m_hWnd, &clientRect);

	RectSize wndSize = {
		wndRect.right - wndRect.left,
		wndRect.bottom - wndRect.top };

	RectSize clientSize = {
		clientRect.right - clientRect.left,
		clientRect.bottom - clientRect.top };

	RectSize frameSize = {
		wndSize.m_x - clientSize.m_x,
		wndSize.m_y - clientSize.m_y };

	SetWindowPos(
		m_hWnd,
		NULL,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		m_WND_SIZE.m_x + frameSize.m_x,
		m_WND_SIZE.m_y + frameSize.m_y,
		SWP_NOMOVE);
}

LRESULT CALLBACK Wnd::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_DESTROY:										//ウィンドウの終了ボタンが押された時
		PostQuitMessage(0);									//プログラムの終了メッセージを投げる

		break;

	case WM_SYSKEYDOWN:										// Alt + 特殊キーの処理に使う
		if (wParam == VK_RETURN) PostQuitMessage(0);		//プログラムの終了メッセージを投げる
	
		break;
	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
