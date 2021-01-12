#pragma once

#include "paint.h"

void paintMainInterface(HWND hWnd, HDC hdc) 
{
	RECT cltRect; 
	GetWindowRect(hWnd, &cltRect); 
	if (cltRect.right - cltRect.left != MAIN_WIN_WIDTH || cltRect.bottom - cltRect.top != MAIN_WIN_HEIGHT)
		MoveWindow(hWnd, cltRect.left, cltRect.top, MAIN_WIN_WIDTH, MAIN_WIN_HEIGHT, FALSE); 
	GetClientRect(hWnd, &cltRect); 
	HDC hdcMem = CreateCompatibleDC(hdc); 
	BITMAP bmMain; 
	GetObject(hBmMain, sizeof(BITMAP), &bmMain); 
	HBITMAP hBmOld = (HBITMAP)SelectObject(hdcMem, hBmMain); 
	StretchBlt(hdc, 0, 0, cltRect.right - cltRect.left, cltRect.bottom - cltRect.top,
		hdcMem, 0, 0, bmMain.bmWidth, bmMain.bmHeight, SRCCOPY);
	SelectObject(hdcMem, hBmOld); 
	DeleteDC(hdcMem); 
}
INT paintBmp(HWND hWnd, HDC hdc, PAINTSTRUCT& ps)
{
	UINT32 width = *(UINT32*)bmpBuf, height = *(UINT32*)(bmpBuf + sizeof(UINT32) / sizeof(UCHAR)); 
	HDC hdcMem = CreateCompatibleDC(hdc); 
	if (hdcMem == NULL) return FAIL_TO_GET_DCMEM;
	HBITMAP hBmOld = (HBITMAP)SelectObject(hdcMem, hBmMem); 
	BitBlt(hdc, xMv, yMv, width, height, hdcMem, 0, 0, SRCCOPY); 
	SelectObject(hdcMem, hBmOld); 
	DeleteDC(hdcMem); 
	return PAINT_SUCCESS; 
}

INT paintBmpMem(UINT32 width, UINT32 height)
{
	HDC hdc = GetDC(hWndMain); 
	if (hBmMem) DeleteObject(hBmMem); 
	hBmMem = NULL; 
	HDC hdcMem = CreateCompatibleDC(hdc); 
	if (hdcMem == NULL) return FAIL_TO_GET_DCMEM; 
	hBmMem = CreateCompatibleBitmap(hdc, width, height); 
	if (hBmMem == NULL)
	{
		DeleteDC(hdcMem); 
		ReleaseDC(hWndMain, hdc); 
		return FAIL_TO_GET_DCMEM; 
	}
	HBITMAP hBmOld = (HBITMAP)SelectObject(hdcMem, hBmMem);
	UINT8 R, G, B;
	UINT8* tmp = (UINT8*)(bmpBuf + sizeof(UINT32) / sizeof(UCHAR) * 2);
	HPEN hPen = CreatePen(PS_NULL, 0, RGB(255, 0, 0));
	HPEN hPenOld = (HPEN)SelectObject(hdcMem, hPen);
	HBRUSH hBr = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH hBrOld = (HBRUSH)SelectObject(hdcMem, hBr);
	HBRUSH hBrTmp;
	HPEN hPenTmp;
	
	HWND hLdDlg = CreateDialog(hInst, loadingDlgName, hWndMain, NULL); 

	for (UINT32 y = height - 1; y >= 0; --y)
	{
		for (UINT32 x = 0; x < width; ++x)
		{
			B = *(tmp++);
			G = *(tmp++);
			R = *(tmp++);
			hBrTmp = hBr;
			hBr = CreateSolidBrush(RGB(R, G, B));
			SelectObject(hdcMem, hBr);
			DeleteObject(hBrTmp);
			Rectangle(hdcMem, x, y, x + 2, y + 2); 
		}
		if (y == 0) break;
	}

	DestroyWindow(hLdDlg); 

	SelectObject(hdcMem, hBrOld);
	DeleteObject(hBr);
	SelectObject(hdcMem, hPenOld);
	DeleteObject(hPen);
	BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY); 
	SelectObject(hdcMem, hBmOld);
	DeleteDC(hdcMem); 
	ReleaseDC(hWndMain, hdc); 
	return PAINT_SUCCESS; 
}

