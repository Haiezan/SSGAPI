#pragma once

#include "HeadDefine.h"
#include "SysPara.h"

class CASCFile;
//�߽�����ֵ��������һ������
class _SSG_DLLIMPEXP CBoundary  
{
public:
	CBoundary(void)
	{
		Clear();
	}

	unsigned short Type;  //���ɶ�����,�ӵ͵��߰�λ�洢,ÿ�����ɶ�2bit,�ֱ��Ӧ0-5���ɶȣ�0--��λ��Լ����1--λ��Լ����2--�������ɸն�
	float Value[Sys_DOF];  //6�����ɶȵ�ֵ��λ��ֵdx,dy,dz,ax,ay,az

	//�������ɶȳ�ʼ��Ϊ0
	void Clear(void)
	{
		Type=0;
		for(int i=0;i<Sys_DOF;i++) 
		{
			Value[i]=0;
		}
	}

	void SetFix(void)  //Լ��ȫ�����ɶ�
	{
		Type=0x555;
		for(int i=0;i<Sys_DOF;i++) 
			Value[i]=0;
	}

	void SetDisp(int idof,float fDisp) //����λ��Լ��
	{
		ASSERT(idof<Sys_DOF && idof>=0); 
		Type|=(1<<(idof<<1)); Value[idof]=fDisp;
	}

	void Release(int idof) //�ͷ�λ��Լ��
	{
		ASSERT(idof<Sys_DOF && idof>=0); 
		Type&=~(1<<(idof<<1)); Value[idof]=0;
	}

	void SetStiff(int idof,float fStiff) //���õ���Լ��
	{
		ASSERT(idof<Sys_DOF && idof>=0); 
		Type|=(2<<(idof<<1)); Value[idof]=fStiff;
	}

	BOOL IsConstraint(int idof) const //1--λ��Լ����0-��λ��Լ��
	{
		ASSERT(idof<Sys_DOF && idof>=0); 
		return (Type&(1<<(idof<<1)))>0?1:0;
	}

	BOOL HasConstraint() const //1--λ��Լ����0-û��Լ��
	{
		for(int i=0;i<Sys_DOF;i++) 
		{
			if((Type&(1<<(i<<1)))>0)
				return TRUE;
		}
		return FALSE;
	}

	int GetType(int idof) const
	{
		ASSERT(idof<Sys_DOF && idof>=0); 
		return (Type>>(idof<<1))&0x03;

	}

	//��12λ�߽�������Ϣ����Ϊ6λ
	unsigned int Get6BitBnd(void)
	{
		unsigned int bnd=0;
		bnd|=(Type&0x01);
		bnd|=(Type&0x04)>>1;
		bnd|=(Type&0x10)>>2;
		bnd|=(Type&0x40)>>3;
		bnd|=(Type&0x100)>>4;
		bnd|=(Type&0x400)>>5;
		return bnd;
	}

	BOOL operator==(const CBoundary &bnd) const
	{
		if(Type!=bnd.Type) return FALSE;
		for (int i=0;i<Sys_DOF;i++)
		{
			if(Value[i]!=bnd.Value[i]) return FALSE;
		}
		return TRUE;
	}

	virtual void Read(CASCFile &fin);
	BOOL Write(CASCFile &fout);
	BOOL Write2020(CASCFile &fout);
	virtual BOOL Write(CASCFile &fout,int idf);  //���߸�ʽ��ͬ

	virtual void ReadBin(CFile &fin);
	virtual BOOL WriteBin(CFile &fout);
};

//�����߽���������ʩ�ӵ������㣨��Ӧ�߹��������߶Σ���Ӧ�湹������
//����ʩ�ӵ��ߺ����ϣ�ʵ��Ҫӳ�䵽�������ڵ�������϶����ǵ�Ԫ
class _SSG_DLLIMPEXP CBoundaryCollection
{
public:
	CBoundaryCollection(void){;}
	~CBoundaryCollection() {Clear();}

	CArray<CBoundary,CBoundary&> aBoundary;

	void Clear(void) {aBoundary.RemoveAll();}

	CBoundary operator[](int i) {return aBoundary[i];}

	CBoundaryCollection& operator=(const CBoundaryCollection& bnd)
	{
		if(this==&bnd) return *this;
		aBoundary.Copy(bnd.aBoundary);
		return *this;
	}

	//�������
	int Append(CBoundary &bnd)
	{
		for (int i=0;i<aBoundary.GetCount();i++)
		{
			if(aBoundary[i]==bnd) return i;
		}
		return (int)aBoundary.Add(bnd);
	}
};
