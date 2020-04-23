#pragma once
#include <Windows.h>

/*
功能：  登录
函数名：Login
参数：
hParent - 登录对话框父窗口句柄
width   - 指定对话框宽度（与height同时大于0才有效）
height  - 指定对话框高度（与width同时大于0才有效）
bReset  - 忽略已保存的用户自动登录信息（切换用户使用）
返回值：
登录成功返回true
*/
extern "C" bool __stdcall Login(HWND hParent = NULL, int width = 0, int height = 0, bool bReset = false, const wchar_t* productId = nullptr, const wchar_t* lockNo = nullptr);
extern "C" void __stdcall Logout();
extern "C" bool __stdcall GetLoginName(wchar_t *bufName, int lenMax);
/*
功能：  查询提示消息（目前仅包含版本更新提示）
函数名：CheckNotify
参数：
hParent - 登录对话框父窗口句柄
*/
extern "C" bool __stdcall CheckNotify(HWND hParent = NULL, bool bTipNoUpgrade = false);
