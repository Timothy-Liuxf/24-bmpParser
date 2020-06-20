#pragma once

#include "framework.h"


//主窗口属性
static LPCTSTR wndClassName = TEXT("bmpParserMainWnd"); 
static LPCTSTR wndTitleName = TEXT("24位位图解析器"); 
static LPCTSTR MAINMENUNAME = TEXT("MAINMENU"); 
static LPCTSTR iconName = TEXT("MAINICON"); 

//输入文件路径对话框属性
static LPCTSTR inputBmpDlgName = TEXT("INPUTBMP"); 

//正在解析对话框属性
static LPCTSTR loadingDlgName = TEXT("LOADING"); 

//异常
static LPCTSTR mustBeTwentyFourBmp = TEXT("图片文件必须是24色位图\nThe file must be a 24-color bitmap!"); 
static LPCTSTR bmpDestroyed = TEXT("位图文件已损坏\nThe bitmap has been destroyed!"); 
static LPCTSTR unknownError = TEXT("未知错误！\nUnknown error!"); 
static LPCTSTR failToOpenBmp = TEXT("打开位图文件失败\nFail to open the bitmap file!"); 
static LPCSTR failToOpenBmpA = "打开位图文件失败\nFail to open the bitmap file!";
static LPCTSTR failToGetClient = TEXT("获取用户区失败！\nFail to get client!"); 
static LPCTSTR failToGetDCMem = TEXT("获取内存失败！\nFail to get Mem!");
static LPCTSTR bmpToolarge = TEXT("位图文件过大！\nThe bitmap is too large!"); 
static LPCTSTR error = TEXT("Error"); 
static LPCSTR errorA = "Error";

//界面
static LPCTSTR welcome = TEXT("欢迎来到！"); 

//菜单
static LPCTSTR help = TEXT(
"1.点击开始->文件输入文件的路径和名称\n\
2.文件必须是无压缩24位位图\n\
3.鼠标点击可拖动图片"); 
static LPCTSTR helpTitle = TEXT("Help"); 
static LPCTSTR about = TEXT(
"名称：\t24位位图解析器/24-bmp Parser\n\
用途：\t对24位位图文件进行解析并显示在屏幕上\n\
版本：\tv1.0\n\
作者：\tTimothy Liu\n\
Copyright(C): Timothy Liu\tAll rights reserved"); 
static LPCTSTR aboutTitle = TEXT("About"); 
