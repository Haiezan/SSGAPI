#pragma once
#include "afx.h"
#include "HeadDefine.h"

//�������ţ�
//<mark>---����
//@@---�ָ�ͬһ�����еĲ�ͬ�ַ����ֶ�

const int MAX_KEYWORD=32;  //���ؼ��ֳ���

//16�����ַ���תΪ����
extern "C" _SSG_DLLIMPEXP int atoi_hex(char* c_data=0); 
extern "C" _SSG_DLLIMPEXP void UTF8ToUnicode( const char *str, CString &rt );

//������CFile�����ڶ�ȡ�ı��ļ�������
//���ж�ȡ���ݺ��������س�������



class _SSG_DLLIMPEXP CASCFile :	public CFile
{
public:
	CASCFile(int iCode=CP_ACP);
	CASCFile(char *pBuf,DWORD len){lpBuf=pBuf;pPos=pBuf;dwLength=len;}
	~CASCFile(void);

	//����Open����,���ļ���ʱֱ�Ӷ������ݵ�������lpBuf
	virtual BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags,CFileException* pError = NULL);
	virtual char * FindKey(const char *pkey);				//�ӿ�ʼλ�ÿ�ʼ��λ�ؼ���,pkey�м���԰����κ��ַ����ı�pPos,��׼����ȡ����,���Զ����У�������һ������λ��
	virtual char * FindKeyNext(const char *pkey);	//�ӵ�ǰλ�ÿ�ʼ��λ�ؼ���,pkey�м���԰����κ��ַ����ı�pPos,��׼����ȡ����,���Զ����У�������һ������λ��
	virtual void ToNextLine();  //��һ����Ч���ݵĵ�ַ
	virtual int NextData(char *tempBuf,int maxlen);  //������һ���ֶΣ��������ո񡢶��š��س�

	int m_iCode; //����ҳ

	//������һ�����ݣ�������֮��ָ��������һ��λ��
	int GetInt();  //����
	long GetLong();  //����
	__int64 GetInt64();  //int64
	long GetHexLong();  //��16�����ַ����õ�����
	float GetFloat();  //������
	float GetDouble();  //������
	virtual CString GetQuotationStr(bool bSkipEmpty=true); //��ȡ�����ڵ��ַ��������Կ��ж�ȡ����ȡ֮���������б�־����л���
	virtual CString GetStr(); //ֱ�Ӷ�ȡ�ַ����������ָ���ֹͣ���ַ����ڲ��ܺ��������ַ�
	int GetKeyValueInt(const char *pkey);  //�ӵ�ǰλ�ÿ�ʼ��λ�ؼ���,�ı�pPos,����ȡ��������
	float GetKeyValueFloat(const char *pkey);  //�ӵ�ǰλ�ÿ�ʼ��λ�ؼ���,�ı�pPos,����ȡ��������
	CString GetKeyValueStr(const char *pkey);  //��λ�ؼ���,�ı�pPos,����ȡ�ַ�������
	CString GetLine();  //���ص�ǰ���ַ�����Ȼ����
	int GetMemAbility(){return iMemAbility;} //�õ��ڴ�����(0-100)

	void GetItemPair(char *pKey,char *pVal);  //����key=val��
	int GetCurrentLineDataCount();  //�õ���ǰ��ʣ������ݸ��������޸�ָ��



	//void ToLastLine();  //�õ����һ����Ч���ݵĵ�ַ
	//void PushPos(){pTemp=pPos;};  //������ʱָ�룬�������Ϊ1
	//void PopPos(){pPos=pTemp;};   //�ָ���ʱָ��
	//BOOL EOB(){return pPos>=lpBuf+dwLength;}; //�жϻ������ݽ�β
	BOOL EOB(){return(pPos==NULL)||( pPos>=lpBuf+dwLength);}; //�жϻ������ݽ�β	//�Ǳ��� 2016.7.12

protected:
	char *lpBuf;  //���ݻ���
	char *pPos;   //��������ʱ�Ŀ�ʼλ��
	char *pTemp;  //��PushPos��PopPos���֮��
	UINT  dwLength;  //�ļ�����,Ϊ��Ӧ�ڴ�,���ܱ��޸�Ϊ�ܶ�ȡ�ĳ���
	int iMemAbility;  //�ڴ�����(%),int(100*�����ڴ�/�����ڴ�)

};


