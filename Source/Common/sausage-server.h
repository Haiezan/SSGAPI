#pragma once
#include <Windows.h>

/*
���ܣ�  ��¼
��������Login
������
hParent - ��¼�Ի��򸸴��ھ��
width   - ָ���Ի����ȣ���heightͬʱ����0����Ч��
height  - ָ���Ի���߶ȣ���widthͬʱ����0����Ч��
bReset  - �����ѱ�����û��Զ���¼��Ϣ���л��û�ʹ�ã�
����ֵ��
��¼�ɹ�����true
*/
extern "C" bool __stdcall Login(HWND hParent = NULL, int width = 0, int height = 0, bool bReset = false, const wchar_t* productId = nullptr, const wchar_t* lockNo = nullptr);
extern "C" void __stdcall Logout();
extern "C" bool __stdcall GetLoginName(wchar_t *bufName, int lenMax);
/*
���ܣ�  ��ѯ��ʾ��Ϣ��Ŀǰ�������汾������ʾ��
��������CheckNotify
������
hParent - ��¼�Ի��򸸴��ھ��
*/
extern "C" bool __stdcall CheckNotify(HWND hParent = NULL, bool bTipNoUpgrade = false);
