#pragma once
#include "HeadDefine.h"
#include "Vector4.h"
#include <vector>
using namespace std;

extern "C" _SSG_DLLIMPEXP BOOL DeleteDirectory(const CString &sDirName); //ɾ���ļ���Ŀ¼(�ǿ�)
extern "C" _SSG_DLLIMPEXP BOOL DeleteFiles(const CString &sName);  //ɾ������ļ�����ɾ��Ŀ¼�����Բ���ƥ���*

extern "C" _SSG_DLLIMPEXP BOOL IsDirectoryExists(const CString &path); //Ŀ¼�Ƿ����
extern "C" _SSG_DLLIMPEXP BOOL IsFileExists(const CString &sFile); //�ļ��Ƿ����
extern "C" _SSG_DLLIMPEXP int  CopyDirectoryFiles(const CString &sourceDir,const CString &destDir);  //����Ŀ¼�µ������ļ�
extern "C" _SSG_DLLIMPEXP BOOL CreateFullDirectory(LPCWSTR lpPathName,LPSECURITY_ATTRIBUTES lpSecurityAttributes);
//������Ŀ��Ŀ¼�µ������ļ�
//sPrjPath,sNewPrjPath: ����ȫ·������Ŀ����������չ��������ַ�Ϊ"."
extern "C" _SSG_DLLIMPEXP int CopyPrjFiles(CString sPrjPath, CString sNewPrjPath);



//ת��Ϊ�ļ���ʽ�ַ���
inline CString EncodeStr(CString str)
{
	str.Replace(L"\"",L"<mark>");  //Double quotation mark
	str.Replace(L",",L"<comma>");  //comma mark
	str.Replace(L"\t",L"<tab>");  // mark
	return str;
}
//ת��Ϊʵ���ַ���
inline CString DecodeStr(CString str)
{
	str.Replace(L"<mark>",L"\"");
	str.Replace(L"<MARK>",L"\"");
	str.Replace(L"<comma>",L",");
	str.Replace(L"<COMMA>",L",");	//�Ǳ��� 2015.9.24
	str.Replace(L"<tab>",L"\t");
	str.Replace(L"<TAB>",L"\t");
	return str;
}

//����ö�١�ѭ���ĸ�������
//exam: 1.1,2*3.0 4.2
extern "C" _SSG_DLLIMPEXP void ParseFloat(CString str,vector<float> &data);
extern "C" _SSG_DLLIMPEXP void ParseDouble(CString str,vector<double> &data);

//����ö�١�ѭ������Χ����������
//exam: 1,2*3,7-8
extern "C" _SSG_DLLIMPEXP void ParseInt(CString str,vector<int> &data);

extern "C" _SSG_DLLIMPEXP int ErrMsg(UINT id);  //�����Ϣ

//�ļ���Ϣ
struct FILEDATA
{
	CString sFileName;				//�ļ�����
	COleDateTime cFileTime;	//�ļ�ʱ��
};
extern "C" _SSG_DLLIMPEXP BOOL GetFiles(LPCTSTR lpFileName,vector<FILEDATA> &filename);  //�õ��ļ����������ļ�
extern "C" _SSG_DLLIMPEXP bool SortByFileTime(const FILEDATA &v1, const FILEDATA &v2);  //���ļ���ʱ����������ǰ�����ں�
extern "C" _SSG_DLLIMPEXP BOOL CompareFile(string file1, string file2);  //�Ƚ������ļ��Ƿ���ͬ


extern "C" _SSG_DLLIMPEXP void GetDirectory(const CString &sDirName,vector<CString> &vDirectory);  //�õ��ļ����������ļ���
