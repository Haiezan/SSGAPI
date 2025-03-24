#pragma once
#include "HeadDefine.h"
#include "Vector4.h"
#include "DataStrucProp.h"

//�����
class _SSG_DLLIMPEXP CVertex : public CPrimitiveProp
{
public:
	CVertex(void)
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
		, fDeadLoad()
		, fLiveLoad()
		, idRigidBody(-1)
		, idmBoundary(-1)
		, iGeoType(0)
	{
	}

	//�����������
	CVertex(float x1,float y1,float z1)
		: x(x1)
		, y(y1)
		, z(z1)
		, fDeadLoad()
		, fLiveLoad()
		, idRigidBody(-1)
		, idmBoundary(-1)
		, iGeoType(0)
	{
	} 

	//�����������
	CVertex(const Vector4 &v)
		: x(v.x)
		, y(v.y)
		, z(v.z)
		, fDeadLoad()
		, fLiveLoad()
		, idRigidBody(-1)
		, idmBoundary(-1)
		, iGeoType(0)
	{
	} 

	CVertex(float x1,float y1,float z1,int istory,BOOL bCrossStory)
		: CPrimitiveProp(g_cSysColorPara.Sys_VexColor, istory)
		, x(x1)
		, y(y1)
		, z(z1)
		, fDeadLoad()
		, fLiveLoad()
		, idRigidBody(-1)
		, idmBoundary(-1)
		, iGeoType(bCrossStory? 0x01:0)
	{
	} //�����ͼԪ

	//���ƹ��캯��,�ù��캯�����CVectorʹ�ò�����
	CVertex(const CVertex& v)
	{
		*this = v;
	}

	CVertex& operator=(const CVertex& v)
	{
		if (this == &v)
			return *this;

		*(CPrimitiveProp *)this=(CPrimitiveProp &)v;

		x=v.x;y=v.y;z=v.z;
		idRigidBody=v.idRigidBody;
		idmBoundary=v.idmBoundary;
		iGeoType=v.iGeoType;
		aload=v.aload;
		aDyload = v.aDyload;
		aPin = v.aPin;
		for (int i=0;i<6;i++)
		{
			fDeadLoad[i]=v.fDeadLoad[i];
			fLiveLoad[i]=v.fLiveLoad[i];
		}
		return *this;
	}

	union
	{
		struct
		{
			float x,y,z;  //����
		};
		float coor[3];
	};

	float fDeadLoad[6]; //����ؼ�����,fx,fy,fz,mx,my,mz,KN,KN.M,���������귽����
	float fLiveLoad[6]; //����ؼ�����
	int idRigidBody;	//���Ը�����,-1ʱ��Ч
	int idmBoundary;	//�߽�����ID�����������*BOUNDARY�ж�д�����������д���������������ж�ȡReadBin/WriteBin�����������mesh.m_pBoundary
	int iGeoType;		//����,��λ���壬0x01--��㡣���������*POINTPROP���ж�ȡ�����������д���������������ж�ȡReadBin/WriteBin
	//LOADMAP mapload;//��Ӧ���ع����ĺ���
	LOADASSIGN aload;//��Ӧ���ع����ĺ���
	LOADASSIGN aDyload;//��Ӧ���ع����Ķ�����
	CPinData aPin;

	CVertex & operator=(const Vector4 &v)
	{
		x=v.x;y=v.y;z=v.z;
		return *this;
	}

	BOOL IsCrossStory(void) const {return iGeoType & 0x01;}
	void SetCrossStory(BOOL bCrossStory=TRUE) {if(bCrossStory) iGeoType |= 0x01;else iGeoType &= ~0x01;}

	//�����߶���������
	void CopyProp(const CLine &line, const CVertex* v);

	//������ȣ�����΢С���
	BOOL operator==(const CVertex &v) const
	{
		return abs(x-v.x)<g_cSysSizePara.Sys_PointError && abs(y-v.y)<g_cSysSizePara.Sys_PointError && abs(z-v.z)<g_cSysSizePara.Sys_PointError;
	}

	//����ȣ�����΢С���
	BOOL operator!=(const CVertex &v) const
	{
		return abs(x-v.x)>=g_cSysSizePara.Sys_PointError || abs(y-v.y)>=g_cSysSizePara.Sys_PointError || abs(z-v.z)>=g_cSysSizePara.Sys_PointError;
	}

	//��ȷ���
	BOOL Equal(const CVertex &v) const {return x==v.x && y==v.y && z==v.z;}  

	//+=
	void operator+=(const CVertex &v)
	{
		x+=v.x;
		y+=v.y;
		z+=v.z;
	}

	//-=
	void operator-=(const CVertex &v)
	{
		x-=v.x;
		y-=v.y;
		z-=v.z;
	}

	//  *=
	void operator*=(float f)
	{
		x*=f;
		y*=f;
		z*=f;
	}

	//  /=
	void operator/=(float f)
	{
		x/=f;
		y/=f;
		z/=f;
	}

	void Normalize(void)
	{
		float len = Length();

		if(abs(len) < ZEROTOL)
			return;

		float fLen = 1.f / len;
		x*= fLen;
		y*= fLen;
		z*= fLen;
	}

	//����ʸ������
	float Length()
	{
		return sqrtf(x*x+y*y+z*z);
	}

	void Clear(void)
	{
		CPrimitiveProp::Clear();
		x=y=z=0.0f;
		for(int i=0;i<6;i++)
		{
			fDeadLoad[i]=fLiveLoad[i]=0;
		}
		idRigidBody=-1;
		idmBoundary=-1;
		iGeoType=0;
		aload.clear();
		aDyload.clear();
		aPin.clear();
	}

	//���´����ڴ棬����ԭ�����ݣ��ͷ�ԭ�����ڴ档���¾�ָ�벻��ͬһ������ʱ�����ó���Ӧ���þ�ָ��ΪNULL
	static CVertex *Renew(CVertex  *&oldp,int oldCount,int newCount)
	{
		if(oldCount==newCount) return oldp;

		CVertex *newp=new CVertex[newCount];
		if(!newp) return NULL;

		int k=min(oldCount,newCount);
		for(int i=0;i<k;i++)
		{
			newp[i]=oldp[i];
		}
		delete[] oldp;
		oldp=newp;
		return newp;
	}


	virtual BOOL Read(CASCFile &fin);
	virtual BOOL Write(CASCFile &fout,int idf); 
	virtual BOOL Write2020(CASCFile &fout,int idf); 
	virtual void ReadBin(CFile &fin);   
	virtual BOOL WriteBin(CFile &fout);
	virtual BOOL IsVisible(const CVertex &vMin,const CVertex &vMax) const;

	void GenLoadId(bool bReWrtie=true);//��	float fDeadLoad ��float fLiveLoad����Load����mapload ��2020֮��汾��ȡ
	void GenLoadVal();//��mapload����fDeadLoad��fLiveLoad ��2020֮ǰ�汾��ȡ
	void ClearLoad();//��պ���
};

//���,����������v1��ͬ
inline CVertex operator+(const CVertex &v1,const CVertex &v2) 
{
	CVertex v0=v1;
	v0.x+=v2.x;
	v0.y+=v2.y;
	v0.z+=v2.z;
	return v0;
}

//���,����������v1��ͬ
inline CVertex operator-(const CVertex &v1,const CVertex &v2) 
{
	CVertex v0=v1;
	v0.x-=v2.x;
	v0.y-=v2.y;
	v0.z-=v2.z;
	return v0;
}

//���,����������v1��ͬ
inline CVertex operator-(const CVertex &v1) 
{
	CVertex v0=v1;
	v0.x=-v1.x;
	v0.y=-v1.y;
	v0.z=-v1.z;
	return v0;
}

//���,����������v1��ͬ
inline CVertex operator*(const CVertex &v1,float f)
{
	CVertex v0=v1;
	v0.x*=f;
	v0.y*=f;
	v0.z*=f;
	return v0;
}

//float * v,����������v��ͬ
inline CVertex operator*(float f,CVertex &v)
{
	CVertex v1=v;
	v1.x=f*v.x;
	v1.y=f*v.y;
	v1.z=f*v.z;
	return v1;
}

//����/,����������v1��ͬ
inline CVertex operator/(const CVertex &v1,float f)
{
	CVertex v0=v1;
	v0.x/=f;
	v0.y/=f;
	v0.z/=f;
	return v0;
}

//�����,����������a��ͬ
inline CVertex CrossProduct(const CVertex &a,const CVertex &b)
{
	CVertex c=a;
	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return c;
}

//�м���˫���Ȳ��
inline CVertex CrossProductDouble(const CVertex &a,const CVertex &b)
{
	CVertex c=a;
	c.x = (float)((double)a.y * b.z - (double)a.z * b.y);
	c.y = (float)((double)a.z * b.x - (double)a.x * b.z);
	c.z = (float)((double)a.x * b.y - (double)a.y * b.x);
	return c;
}

//���
inline float DotProduct(const CVertex &a,const CVertex &b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

//���
inline float DotProduct(const CPoint &a,const CPoint &b)
{
	return (float)a.x * b.x + (float)a.y * b.y;
}

//˫���ȵ��
inline double DotProductDouble(const CVertex &a,const CVertex &b)
{
	return (double)a.x * b.x + (double)a.y * b.y + (double)a.z * b.z;
}

//���
inline float VexDistance(const CVertex &a,const CVertex &b)
{
	float x = a.x - b.x;
	float y = a.y - b.y;
	float z = a.z - b.z;
	return sqrtf(x*x+y*y+z*z);
}