#pragma once
#include "afx.h"
#include "HeadDefine.h"

//保留符号：
//<mark>---引号
//@@---分隔同一个串中的不同字符串字段

const int MAX_KEYWORD=32;  //最大关键字长度

//16进制字符串转为整数
extern "C" _SSG_DLLIMPEXP int atoi_hex(char* c_data=0); 
extern "C" _SSG_DLLIMPEXP void UTF8ToUnicode( const char *str, CString &rt );

//派生于CFile，用于读取文本文件的数据
//所有读取数据函数遇到回车均跳过



class _SSG_DLLIMPEXP CASCFile :	public CFile
{
public:
	CASCFile(int iCode=CP_ACP);
	CASCFile(char *pBuf,DWORD len){lpBuf=pBuf;pPos=pBuf;dwLength=len;}
	~CASCFile(void);

	//重载Open函数,读文件打开时直接读入数据到缓冲区lpBuf
	virtual BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags,CFileException* pError = NULL);
	virtual char * FindKey(const char *pkey);				//从开始位置开始定位关键字,pkey中间可以包括任何字符，改变pPos,并准备读取数据,不自动换行，返回下一个数据位置
	virtual char * FindKeyNext(const char *pkey);	//从当前位置开始定位关键字,pkey中间可以包括任何字符，改变pPos,并准备读取数据,不自动换行，返回下一个数据位置
	virtual void ToNextLine();  //下一行有效数据的地址
	virtual int NextData(char *tempBuf,int maxlen);  //搜索下一个字段，可跳过空格、逗号、回车

	int m_iCode; //代码页

	//读入下一个数据，读数据之后指针移向下一个位置
	int GetInt();  //整数
	long GetLong();  //整数
	__int64 GetInt64();  //int64
	long GetHexLong();  //从16进制字符串得到整数
	float GetFloat();  //浮点数
	float GetDouble();  //浮点数
	virtual CString GetQuotationStr(bool bSkipEmpty=true); //读取引号内的字符串，可以跨行读取，读取之后遇到换行标志则进行换行
	virtual CString GetStr(); //直接读取字符串，遇到分隔符停止，字符串内不能含有特殊字符
	int GetKeyValueInt(const char *pkey);  //从当前位置开始定位关键字,改变pPos,并读取整形数据
	float GetKeyValueFloat(const char *pkey);  //从当前位置开始定位关键字,改变pPos,并读取浮点数据
	CString GetKeyValueStr(const char *pkey);  //定位关键字,改变pPos,并读取字符串数据
	CString GetLine();  //返回当前行字符串，然后换行
	int GetMemAbility(){return iMemAbility;} //得到内存能力(0-100)

	void GetItemPair(char *pKey,char *pVal);  //返回key=val对
	int GetCurrentLineDataCount();  //得到当前行剩余的数据个数，不修改指针



	//void ToLastLine();  //得到最后一行有效数据的地址
	//void PushPos(){pTemp=pPos;};  //保存临时指针，保存深度为1
	//void PopPos(){pPos=pTemp;};   //恢复临时指针
	//BOOL EOB(){return pPos>=lpBuf+dwLength;}; //判断缓存数据结尾
	BOOL EOB(){return(pPos==NULL)||( pPos>=lpBuf+dwLength);}; //判断缓存数据结尾	//乔保娟 2016.7.12

protected:
	char *lpBuf;  //数据缓存
	char *pPos;   //搜索数据时的开始位置
	char *pTemp;  //与PushPos和PopPos配合之用
	UINT  dwLength;  //文件长度,为适应内存,可能被修改为能读取的长度
	int iMemAbility;  //内存能力(%),int(100*申请内存/需求内存)

};


