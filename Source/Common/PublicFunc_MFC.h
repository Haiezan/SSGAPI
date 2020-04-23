#pragma once
#include "HeadDefine.h"
#include "Vector4.h"
#include <vector>
using namespace std;

extern "C" _SSG_DLLIMPEXP BOOL DeleteDirectory(const CString &sDirName); //删除文件夹目录(非空)
extern "C" _SSG_DLLIMPEXP BOOL DeleteFiles(const CString &sName);  //删除多个文件，不删除目录，可以采用匹配符*

extern "C" _SSG_DLLIMPEXP BOOL IsDirectoryExists(const CString &path); //目录是否存在
extern "C" _SSG_DLLIMPEXP BOOL IsFileExists(const CString &sFile); //文件是否存在
extern "C" _SSG_DLLIMPEXP int  CopyDirectoryFiles(const CString &sourceDir,const CString &destDir);  //复制目录下的所有文件
extern "C" _SSG_DLLIMPEXP BOOL CreateFullDirectory(LPCWSTR lpPathName,LPSECURITY_ATTRIBUTES lpSecurityAttributes);
//复制项目根目录下的所有文件
//sPrjPath,sNewPrjPath: 包含全路径和项目名，不含扩展名，最后字符为"."
extern "C" _SSG_DLLIMPEXP int CopyPrjFiles(CString sPrjPath, CString sNewPrjPath);



//转换为文件格式字符串
inline CString EncodeStr(CString str)
{
	str.Replace(L"\"",L"<mark>");  //Double quotation mark
	str.Replace(L",",L"<comma>");  //comma mark
	str.Replace(L"\t",L"<tab>");  // mark
	return str;
}
//转换为实际字符串
inline CString DecodeStr(CString str)
{
	str.Replace(L"<mark>",L"\"");
	str.Replace(L"<MARK>",L"\"");
	str.Replace(L"<comma>",L",");
	str.Replace(L"<COMMA>",L",");	//乔保娟 2015.9.24
	str.Replace(L"<tab>",L"\t");
	str.Replace(L"<TAB>",L"\t");
	return str;
}

//解析枚举、循环的浮点数据
//exam: 1.1,2*3.0 4.2
extern "C" _SSG_DLLIMPEXP void ParseFloat(CString str,vector<float> &data);
extern "C" _SSG_DLLIMPEXP void ParseDouble(CString str,vector<double> &data);

//解析枚举、循环、范围的整型数据
//exam: 1,2*3,7-8
extern "C" _SSG_DLLIMPEXP void ParseInt(CString str,vector<int> &data);

extern "C" _SSG_DLLIMPEXP int ErrMsg(UINT id);  //输出信息

//文件信息
struct FILEDATA
{
	CString sFileName;				//文件名称
	COleDateTime cFileTime;	//文件时间
};
extern "C" _SSG_DLLIMPEXP BOOL GetFiles(LPCTSTR lpFileName,vector<FILEDATA> &filename);  //得到文件夹中所有文件
extern "C" _SSG_DLLIMPEXP bool SortByFileTime(const FILEDATA &v1, const FILEDATA &v2);  //将文件按时间排序，新在前，旧在后
extern "C" _SSG_DLLIMPEXP BOOL CompareFile(string file1, string file2);  //比较两个文件是否相同


extern "C" _SSG_DLLIMPEXP void GetDirectory(const CString &sDirName,vector<CString> &vDirectory);  //得到文件夹中所有文件夹
