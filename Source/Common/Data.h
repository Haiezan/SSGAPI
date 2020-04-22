#pragma once
#include "HeadDefine.h"
#include "Vector4.h"
#include "Matrix4x4.h"
//#include "SysPara.h"
#include "PublicFunc.h"
#include "PublicFunc_MFC.h"


#include "ASCFile.h"
#include "UserDefine.h"
#include "BeamSection.h"
#include "Material.h"
#include "EdgeStruct.h"


#include <afxtempl.h>
#include <vector>
//#include <algorithm>
//#include <functional>

using namespace std;




class CLine;
class CFrame;
class CMesh;

//���������ཻ���
struct LINE_CROSS_POLY
{
	//type--�ཻ���ͣ�
	//-1 -- ��������
	//0--���ཻ����������Ͳ�����
	//1--�߽��ڶ����1�����㣬��������Ͳ�����
	//�����ཻ��2--���������ཻ��2���㣬3--�������α���(����)�غϣ�6--���ڶ������
	//�������ཻ��4--�������α߽����ཻ(�����ڽ����幹��֮ǰ�ͽ����˽ṹ�ߣ����������߶�֮����ཻ�������˸��߶�һ�㲻���ܽ��ڱ߽��ߵ��м��)��
	//			  5--���������ڲ��ཻ
	int type; 
	int pointid1;  //����ID1��type=1,2��Ч
	int pointid2;  //����ID2��type=2��Ч
	int plateid1,plateid2; //�µĶ����ID
};

struct CROSS_POINT
{
	int id;
	float t;
	int iLine;
	CROSS_POINT *pPair;

	bool operator < (const CROSS_POINT& cp ) const //��������ʱ����д�ĺ���
	{
		return t < cp.t;
	}
};

struct CROSS_PLATE
{
	int plateid;  //�湹��ID
	int crossvexid;  //�����

	bool operator == (const CROSS_PLATE& cp)
	{
		return (plateid==cp.plateid) && (crossvexid==cp.crossvexid);
	};

	bool operator < (const CROSS_PLATE& cp) //��������ʱ����д�ĺ���
	{
		if(plateid < cp.plateid) 
			return TRUE;
		else if(plateid == cp.plateid) 
			return crossvexid < cp.crossvexid;
		else
			return FALSE;
	};
};


//¥�㷶Χ�ṹ
struct STORY_RANGE
{
	int iStoryMin;
	int iStoryMax; 
};

//�����ɵ����򹹼�����Ԫ
struct BEAM_CONN_LAYER
{
	int idBeam;  //��Ԫ���
	int idNode;  //�ֲ������ţ�0-1
};

//�����ɵĿǵ�Ԫ
struct SHELL_CONN_LAYER
{
	int idShell;  //�ǵ�Ԫ���
	int idNode1;  //��¥�������ľֲ����,������0~2���ı���0~3
	int idNode2;  //��¥�������ľֲ����,������1~2���ı���1~3��-1��ʾ������
};

//ͳ�Ƹ���������
struct STRUCT_COUNT
{
	int nPoint   	;       //��
	int nLine    	;       //�ṹ��
	int nBeam    	;       //��
	int nPillar  	;       //��
	int nBracing 	;       //б��
	int nEdge		;       //Լ����Ե����
	int nHidebeam   ;       //����
	int nLongirebar ;       //�����ݽ�
	int nLink ;       //������	//�Ǳ��� 2015.5.21
	int nPlate 		;       //��
	int nWall  		;       //ǽ
	int nGuides    	;       //������
};

//�߽��ͱ߽��߹�����ϵ
struct BND_NODE_LINE
{
	int nline;
	int line[2];  //�߱�ţ����2��
};

//�ṹ���Ƽ��ؼ���
struct STRUCT_KEYWORD
{
	int iType;
	CString sTitle;
	CString sKeyword;

};

//�õ�g_StructKeyword�еĵĽṹ����������
//int GetStructKeywordIndex(STRUCT_TYPE itype);
int _SSG_DLLIMPEXP GetStructKeywordIndex(STRUCT_TYPE itype);
extern "C" _SSG_DLLIMPEXP int GetStructKeywordIndex(const CString  &keyword);


//�㵽�߹���(�����ṹ�ߡ���������)�����ӹ�ϵ��������
struct _SSG_DLLIMPEXP PT2LINESTRUCT
{
	PT2LINESTRUCT(void) {conn_vex1=conn_vex2=conn_beam1=conn_beam2=-1;}

	int conn_beam1,conn_vex1; //�����ĵ�һ���߹�����id�͵�ţ��Լ��߹���¥���
	int conn_beam2,conn_vex2; //�����ĵڶ����߹�����id�͵�ţ��Լ��߹���¥���

	void Append(int beam, int vex)
	{
		if(conn_beam1==-1)
		{
			conn_beam1=beam;
			conn_vex1=vex;
		}
		else
		{
			conn_beam2=beam;
			conn_vex2=vex;
		}
	}
};

//һ���㵽�����߶εĹ�����-1Ϊ��ЧID�����ڶ���α߽�
struct _SSG_DLLIMPEXP PT2LINE
{
	PT2LINE(void) {iVexID=-1;iLeftLineID=iRightLineID=-1;}
	int iVexID; //��ID
	int iLeftLineID,iRightLineID;  //��ߵ��߶�ID���ұߵ��߶�ID
};

//��Ϲ���
struct _SSG_DLLIMPEXP COMBO_STRUCT
{
	COMBO_STRUCT(void) {sName=L"";}
	~COMBO_STRUCT() {Clear();}
	void Clear(void) {vIDG.clear();sName=L"";}
	CString sName;
	vector<int> vIDG;
};

struct _SSG_DLLIMPEXP STRUCT_PROPERTY1
{
	int iCode;  //���Դ���=����Ԫ����ţ������������
	CString sName;  //��������
	CString sUnit;  //���Ե�λ
	BOOL bBeam,bPillar,bBrace,bPlate,bWall,bBeamWall;  //�Ƿ�����ĳ�๹��ʹ��
	int iDataType; //0-float,1-CString
};

//���ǽ��������ϵ�����ڴ�������
class _SSG_DLLIMPEXP CPointWallIndex
{
public:
	CPointWallIndex(void) {nWalls=0;}

	int nWalls;  //��Χ��ǽ����������ǽ��(������ǽ)
	//int idPoint[Sys_Max_Connect_Wall];  //ǽ���г��õ�������˵��IDM��-1��ʾ��Ч
	int idWall[Sys_Max_Connect_Wall];  //ǽ��IDM
	float fAng[Sys_Max_Connect_Wall];    //�˵���idPoint���ɵ�������X��нǣ����ȣ�0-2*PI

	BOOL Add(int id_wall,float Angle)
	{
		if(nWalls>=Sys_Max_Connect_Wall) 
		{
			TRACE("too namy walls:  id_wall=%d\r\n",id_wall);
			return FALSE;
		}
		idWall[nWalls]=id_wall;
		fAng[nWalls]=Angle;
		nWalls++;
		return TRUE;
	}
};

//�ඨ��------------------------------------------------------------------------
//ͼԪ����
class _SSG_DLLIMPEXP CPrimitiveProp
{
public:
	CPrimitiveProp(void);

	int idmStory;     //¥��IDF=IDM,��0��ʼ���,0Ϊ����
	int iStage;        //ʩ���׶�,��0��ʼ���
	int iTower;		//�ֿ�ţ����ţ���0��ʼ���

	//��ʱ����,�������ļ�
	union
	{
		DWORD dwColor;  //��ɫ
		unsigned char RGBA[4];
	};

	//cmliu 2016/3/22  ����һ�� ��ʱ������ɫ���ڻָ�
	DWORD dwColor1;		

	unsigned char iStatus;  //״̬��־��0��Ч��1-������2-ѡ�У�3-�ο���(Ŀǰֻ�Ե���Ч)
	CString sComments;  //������ʾ��˵������,�ɳ�����ʱ����
	CString sComments2;  //������ʾ��˵������,�ɳ�����ʱ����//��ʾ�ڶ����ڵ��� 

	float fMeshRatio; //�������ϵ����>1���ܣ������ڵ������ݶ�

	CPrimitiveProp & operator=(const CPrimitiveProp &prop)
	{
		if(this==&prop) return *this;

		idmStory=prop.idmStory; 
		iStage=prop.iStage;
		iTower=prop.iTower;
		dwColor=prop.dwColor;
		iStatus=prop.iStatus;  
		//iStatus=1; //�����Ƶ�ͼԪ�Զ������Ч2012-10-25
		sComments=prop.sComments;
		sComments2=prop.sComments2;
		fMeshRatio=prop.fMeshRatio;

		return *this;
	}

	void Clear();

	virtual BOOL Read(CASCFile &fin);   
	virtual BOOL Write(CASCFile &fout);

	virtual void ReadBin(CFile &fin);   
	virtual BOOL WriteBin(CFile &fout);

	virtual BOOL IsValid(void) const;
};

enum LOAD_TYPE
{
	LOAD_DEAD=0,		//0-���Ϸֲ����Ӻ��أ�
	LOAD_LIVE=1,		//1-���Ϸֲ����ӻ��أ�
	LOAD_SLAB_DEAD=2,	//2-�帽�Ӻ��ش��������Ϸֲ����أ�
	LOAD_SLAB_LIVE=3,	//3-�帽�ӻ��ش��������Ϸֲ����أ�
	LOAD_SLAB_WEIGHT=4,	//4-�����ش��������Ϸֲ�����
};

//�ṹ����
class _SSG_DLLIMPEXP CStrucProp : public CPrimitiveProp
{
public:
	CStrucProp(void);
	//���ƹ��캯��
	CStrucProp(const CStrucProp &prop) 
	{
		*this=prop;
	}

	~CStrucProp()
	{
		aElms.RemoveAll();
	};
	int PmID;
	STRUCT_TYPE iStrucType;

	CString ConcMat;         //�Ų���
	CString RebarMat;        //�ֽ����,��Ե�����������ݽ���Ϸ���RebarMat�����Ҳ���ڸֽ������
	CString StirrupMat;        //�������	//�Ǳ��� 2015.6.5
	CString SteelMat;  //�͸ֲ���

	float fDeadLoad; //����أ���λ�����λ����,��KN/m2����KN/m,����Ϊ����б�尴ʵ��������㣬б����ʵ�ʳ��ȼ���
	float fLiveLoad; //����أ���λ�����λ����,��KN/m2����KN/m,����Ϊ����б�尴ʵ��������㣬б����ʵ�ʳ��ȼ���

	int iMidSeismContstiType;//��������Ŀ��
	int iRareSeismContstiType;//��������Ŀ��
	//int iKill;//��Ԫ����
	int iSeismicGrade;//����ȼ�
	int iDatailsGrade;//������ȼ�
	CString sMemberName;//��������

	//��ʱ����
	CArray<int,int> aElms;  //��Ԫ����,����Ԫ�������ε�Ԫ���Ϊԭʼ��ţ��ı��ε�Ԫ���=m_nTriangle+i,����ȫ�������Լ�����������γ�


	CStrucProp & operator=(const CStrucProp &prop)
	{
		if(this==&prop) return *this;

		*(CPrimitiveProp *)this=(CPrimitiveProp &)prop;
		PmID=prop.PmID;
		iStrucType=prop.iStrucType;

		ConcMat=prop.ConcMat;        
		RebarMat=prop.RebarMat;   
		StirrupMat=prop.StirrupMat;  
		SteelMat=prop.SteelMat; 

		fDeadLoad=prop.fDeadLoad;
		fLiveLoad=prop.fLiveLoad;

		iMidSeismContstiType=prop.iMidSeismContstiType;
		iRareSeismContstiType=prop.iRareSeismContstiType;

		iSeismicGrade=prop.iSeismicGrade;
		iDatailsGrade=prop.iDatailsGrade;
		sMemberName=prop.sMemberName;

		//���ڿ�ܸ���ʱ�����ڵ�Ԫ���ݣ���˲���Ҫ����
		aElms.RemoveAll();

		return *this;
	}

	//virtual BOOL Read(CASCFile &fin);   
	//virtual BOOL Write(CASCFile &fout);

	//virtual void ReadBin(CFile &fin);   
	//virtual BOOL WriteBin(CFile &fout);
};

//�����
class _SSG_DLLIMPEXP CVertex : public CPrimitiveProp
{
public:
	CVertex(void){Clear();}

	//�����������
	CVertex(float x1,float y1,float z1)
	{
		Clear();
		x=x1;y=y1;z=z1;
	} 

	//�����������
	CVertex(const Vector4 &v)
	{
		Clear();
		x=v.x;y=v.y;z=v.z;
	} 

	CVertex(float x1,float y1,float z1,int istory,BOOL bCrossStory)
	{
		Clear();
		x=x1;y=y1;z=z1;
		idmStory=istory;
		SetCrossStory(bCrossStory);
		memset(fDeadLoad,0,sizeof(fDeadLoad));
		memset(fLiveLoad,0,sizeof(fLiveLoad));
		idRigidBody=-1;
		idmBoundary=-1;
	} //�����ͼԪ

	//���ƹ��캯��,�ù��캯�����CVectorʹ�ò�����
	CVertex(const CVertex &v) 
	{
		*this=v;
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
	int	  idRigidBody;	//���Ը�����,-1ʱ��Ч

	int idmBoundary;	//�߽�����ID�����������*BOUNDARY�ж�д�����������д���������������ж�ȡReadBin/WriteBin�����������mesh.m_pBoundary
	int iGeoType;		//����,��λ���壬0x01--��㡣���������*POINTPROP���ж�ȡ�����������д���������������ж�ȡReadBin/WriteBin

	CVertex & operator=(const Vector4 &v)
	{
		x=v.x;y=v.y;z=v.z;
		return *this;
	}


	BOOL IsCrossStory(void) const {return iGeoType & 0x01;}
	void SetCrossStory(BOOL bCrossStory=TRUE) {if(bCrossStory) iGeoType |= 0x01;else iGeoType &= ~0x01;}

	BOOL IsCrossTower(void) const {return iGeoType & 0x02;}
	void SetCrossTower(BOOL bCrossTower=TRUE) {if(bCrossTower) iGeoType |= 0x02;else iGeoType &= ~0x02;}

	//�����߶���������
	void CopyProp(const CLine &line);

	//������ȣ�����΢С���
	BOOL operator==(const CVertex &v) const
	{
		return fabs(x-v.x)<g_cSysSizePara.Sys_PointError && fabs(y-v.y)<g_cSysSizePara.Sys_PointError && fabs(z-v.z)<g_cSysSizePara.Sys_PointError;
	}

	//����ȣ�����΢С���
	BOOL operator!=(const CVertex &v) const
	{
		return fabs(x-v.x)>=g_cSysSizePara.Sys_PointError || fabs(y-v.y)>=g_cSysSizePara.Sys_PointError || fabs(z-v.z)>=g_cSysSizePara.Sys_PointError;
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
		if(len==0) return;
		x/=len;
		y/=len;
		z/=len;
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
	virtual void ReadBin(CFile &fin);   
	virtual BOOL WriteBin(CFile &fout);
	virtual BOOL IsVisible(const CVertex &vMin,const CVertex &vMax) const;
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

//�߶���
class _SSG_DLLIMPEXP CLine:public CPrimitiveProp
{
public:
	CLine(void);
	CLine(int i1,int i2,int istory);

	int VexIDM1,VexIDM2;  //�˵�IDM
	float fDeadLoad,fLiveLoad; //���غ�,�����в���ȡ����Ӧ��ʱ��д��ֵ��KN/m
	int idmBoundary;  //�߽�����ID�����������д����������

	//�жϱ�����ͬ
	BOOL operator==(const CLine &line) const
	{
		if(line.VexIDM1==VexIDM1 && line.VexIDM2==VexIDM2) return TRUE;
		if(line.VexIDM1==VexIDM2 && line.VexIDM2==VexIDM1) return TRUE;
		return FALSE;
	}

	BOOL IsCrossStory(void) const;
	//void SetCrossStory(BOOL bCrossStory=TRUE);  //ʵ�����������ߵĶ˵㣬�����ݱ��п�����ԣ�Ӧ����ʹ�õ����Դ���

	BOOL IsCrossTower(void) const;
	//void SetCrossTower(BOOL bCrossTower=TRUE);  //ʵ�����������ߵĶ˵㣬�����ݱ��п������ԣ�Ӧ����ʹ�õ����Դ���

	inline float Length(const CVertex *vex) const //vexΪ������������
	{
		return (vex[VexIDM1]-vex[VexIDM2]).Length();
	}
	inline float Angle(const CVertex *vex) const //vexΪ������������
	{
		float length= (vex[VexIDM1]-vex[VexIDM2]).Length();
		float high=abs(vex[VexIDM1].z-vex[VexIDM2].z);
		return acos(high/length);
	}
	inline BOOL InRectXY(const CVertex &vMin,const CVertex &vMax,const CVertex *vex)  //��ѡ���߶��Ƿ���ȫ�ھ��η�Χ�ڣ������߽��غ�
	{
		const CVertex &vex1=vex[VexIDM1];
		const CVertex &vex2=vex[VexIDM2];
		if((vex1.x-vMin.x)*(vex1.x-vMax.x)>0) return FALSE;
		if((vex1.y-vMin.y)*(vex1.y-vMax.y)>0) return FALSE;
		if((vex2.x-vMin.x)*(vex2.x-vMax.x)>0) return FALSE;
		if((vex2.y-vMin.y)*(vex2.y-vMax.y)>0) return FALSE;
		return TRUE;
	}

	inline BOOL CrossRectXY(const CVertex &vMin,const CVertex &vMax,const CVertex *vex)  //��ѡ���߶��Ƿ�������ص��������߽��غ�
	{
		const CVertex &vex1=vex[VexIDM1];
		const CVertex &vex2=vex[VexIDM2];
		if((vex1.x-vMin.x)*(vex1.x-vMax.x)<0 && (vex1.y-vMin.y)*(vex1.y-vMax.y)<0) return TRUE;
		if((vex2.x-vMin.x)*(vex2.x-vMax.x)<0 && (vex2.y-vMin.y)*(vex2.y-vMax.y)<0) return TRUE;
		return FALSE;
	}

	void Clear(void);
	virtual BOOL Read(CASCFile &fin);
	virtual BOOL Write(CASCFile &fout,int idf);
};

//�����Ĺ����棬������ʾ����
class _SSG_DLLIMPEXP CSurface
{
public:
	CSurface(void) {nVertex=0;pVertex=NULL;color=0;}
	~CSurface() {delete[] pVertex;}

	CSurface(CSurface &surf)
	{
		pVertex=NULL;
		*this=surf;
	}

	//��ֵ���������
	CSurface & operator=(const CSurface& surf)
	{
		if(this==&surf) return *this;

		delete[] pVertex;
		nVertex=surf.nVertex;
		pVertex=new Vector4[nVertex];
		for(int i=0;i<nVertex;i++)
		{
			pVertex[i]=surf.pVertex[i];
		}
		return *this;
	}

	int nVertex; //������
	Vector4 *pVertex; //�����������飬����ڹ����ľֲ�����
	DWORD color; //ʵ�ʻ�����ɫ
};

class _SSG_DLLIMPEXP CBeamFace
{
public:
	CBeamFace(void);
	~CBeamFace();

	Vector4 a1,b1,c1,d1; //��һ����Ķ���
	Vector4 a2,b2,c2,d2; //�ڶ�����Ķ���
	float fColor1,fColor2,fColor3; //a1-a2����ϵ����a1-b1����ϵ����a1-d1����ϵ��
};

//��״��������һ���߶����
class _SSG_DLLIMPEXP CBeamStruc : public CStrucProp
{
public:
	CBeamStruc(void);
	//���ƹ��캯��
	CBeamStruc(const CBeamStruc &beam) 
	{
		Clear();
		*this=beam;
	};

	CBeamStruc(STRUCT_TYPE istructype,int lineid,int istory,DWORD color);
	~CBeamStruc()
	{

	};

	//int id; //��������id����1��ʼ��ţ������߹����������
	int LineIDM; //�ṹ�߱��
	int iSectionID;  //����ID

	/*
	�߹���������
	�����ש������ש������ש������ש������ש������ש������ש������ש���������
	��  ��  Bit7�� Bit6 �� Bit5 �� Bit4 �� Bit3 �� Bit2 �� Bit1 �� Bit0   ��
	�ǩ��贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈��������
	������  0   �� 0    ��0     �� ���� ����������ת������ ���� �� ����   ��
	�ǩ��贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈��������
	������  0   �� 0    ��0     �� 0    ��0     ��0     �� 0    ����֧��  ��
	�ǩ��贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈��������
	���ũ�  0   �� 0    ��0     �� 0    ��0     ��0     �� 0    ������֧�ũ�
	�����ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ���������
	*/
	int iSubType;	//�����ͣ����Լ�¼һ�����ӵ������� 

	BOOL bArtiNode1,bArtiNode2;	//��Ӧ�Ķ˵��Ƿ�½ӣ�FALSEΪ�̽�,��ѡĳ���������������Ķ˵�Ϊ�½ӣ������ʹ������ɽ½ӣ��������˻�һ�˽½�
	int iBottomStory; //�׵�¥��ţ�����б����Ч����ʱ����
	//�����������ߵķ���ǣ���λ���ȣ�2->3����Ϊ��,fAng�ṩ���û��޸�,�޸ĺ���������CalRefPoint����ο���
	float fRotateAng;  //�޸�ת��ʱ��Ҫ���¾ֲ�����
	float fOffsetX1,fOffsetY1,fOffsetZ1;  //�׵�ƫ�ƾ��루m��,�ֲ�����ϵ������ΪX
	float fOffsetX2,fOffsetY2,fOffsetZ2;  //ĩ��ƫ�ƾ��루m��
	float fRatio1,fRatio2;  //����ʣ��������׽����б�ţ�B��H����ĵ�������ʣ������ǽ,��λ���ٷ���
	float fCornerArea;  //һ���ǽ�����(m^2)������б����Ч
	float f_StirArea_D,f_StirArea_UD;  //�������������, �Ǽ����������������������б����Ч

	//��ʱ���ݣ��������ļ�,u.x>1���Ϸ�����ʼ��u.x=10.0f��ʾδ���㣬���롢���ӡ��ƶ��˵���޸�ת��ʱ��Ҫ����LocalCoorVector���¼���
	Vector4 u,v,w;  //�ֲ�����ϵ��ʸ��������ԭ�㣬wΪ���߷���,

	BOOL IsSecondBeam(void) const {return iStrucType==STRUCT_BEAM && iSubType&0x01;}	 //FALSE--������ʹ�ý����е���ά��TRUE-��������ʹ����ά��Ϣ��ֻ����������Ч
	void SetSecondBeam(BOOL bSecondBeam) 
	{
		if(iStrucType!=STRUCT_BEAM) return;
		if(bSecondBeam)
			iSubType |= 0x01; 
		else
			iSubType &= ~0x01; 
	}

	BOOL IsPropEqual(const CBeamStruc &beam) const;  //���пɺϲ�������

	//�Ƿ���������,����ֻ�������أ����ṩ�նȵ�Ԫ������
	BOOL IsVirtualBeam(void) const 
	{
		return (iStrucType==STRUCT_BEAM && (iSubType&0x10)) || iStrucType==STRUCT_HIDEBEAM;
	} 

	float GetWidth(const CSectionCollection *pSecCollection) const; //������
	float GetHeight(const CSectionCollection *pSecCollection) const; //�߶ȷ�Χ

	//�õ����귶Χ
	void GetRange(Vector4 &rMin,Vector4 &rMax);

	void Clear(void);

	//��ֵ���������
	CBeamStruc & operator=(const CBeamStruc& beam)
	{
		if(this==&beam) return *this;

		Clear();
		*(CStrucProp *)this=(CStrucProp &)beam;

		LineIDM=beam.LineIDM;
		iSectionID=beam.iSectionID;
		iSubType=beam.iSubType;
		bArtiNode1=beam.bArtiNode1;
		bArtiNode2=beam.bArtiNode2;
		iBottomStory=beam.iBottomStory;
		fRotateAng=beam.fRotateAng;
		fOffsetX1=beam.fOffsetX1;
		fOffsetY1=beam.fOffsetY1;
		fOffsetZ1=beam.fOffsetZ1;
		fOffsetX2=beam.fOffsetX2;
		fOffsetY2=beam.fOffsetY2;
		fOffsetZ2=beam.fOffsetZ2;
		fRatio1=beam.fRatio1;
		fRatio2=beam.fRatio2;
		fCornerArea=beam.fCornerArea;
		f_StirArea_D=beam.f_StirArea_D;
		f_StirArea_UD=beam.f_StirArea_UD;

		u=beam.u;
		v=beam.v;
		w=beam.w;
		return *this;
	}
	
	void SetRebarRatio(float Ratio1,float Ratio2)
	{
		fRatio1=Ratio1;
		fRatio2=Ratio2;
	}

	//�����߹����ֲ����굥λ��ʸ����������ת��
	//ˮƽ������e1Ϊ���߷���e2��e3Ϊ����ֲ����귽��
	//���򹹼���e1=eZΪ���߷���e2��e3Ϊ����ֲ����귽��
	void LocalCoorVector(Vector4 &u,Vector4 &v,Vector4 &w);

	//������β���������ο��㣬��ֱ�����ͷǴ�ֱ�������巽ʽ��ͬ��angΪ����ǣ���λ����
	CVertex CalRefPoint(const CVertex &v1,const CVertex &v2,float ang); 
	//������β����������ͼ���ο��㣬���Ӻͱ�Ե������������X��ת�ǣ������������վֲ���ʼZ��ת�Ƕ��壬angΪ����ǣ���λ����
	CVertex CalRefPoint(const CVertex &v1,const CVertex &v2,STRUCT_TYPE type,float ang);

	//int GetSectionIDM(){return SectionIDM;} //��ý���ID
	inline float GetRatioUpper(){return fRatio1;}  //��������������
	inline float GetRatioLower(){return fRatio2;}  //������׽������
	inline float GetRatioB(){return fRatio1;}    //����б�Ž���B���򵥱������
	inline float GetRatioH(){return fRatio2;}    //����б�Ž���H���򵥱������

	float Length(const CLine *pLine,const CVertex *pVex) const;  //���㹹�����ȣ� pLineΪ�ṹ�����飬pVexΪ������������
	BOOL Weight(float fConcArea, float fSteelArea, float fRebarArea, float &wConc, float &wSt, float &wRebar); //������������λkN

	//Ҫ�����ȶ������Ͳ�������
	virtual BOOL Read(CASCFile &fin,STRUCT_TYPE iType);
	virtual BOOL Write(CASCFile &fout,int idf);
	//�����Ϣ��д
	virtual BOOL ReadDesignInfo(CASCFile &fin,STRUCT_TYPE iType,int idf);
	virtual BOOL WriteDesignInfo(CASCFile &fout,int idf);
};


//��״�������ɶ���߶���ɶ���Σ����溬��̬���飬������ɾ��ʱҪ�ȵ���CPlateStruc::Clear()
class _SSG_DLLIMPEXP CPlateStruc: public CStrucProp
{
public:
	CPlateStruc(void);

	CPlateStruc(const CPlateStruc &plate)
	{
		pLineIDM=NULL;
		*this=plate;
	}

	CPlateStruc(STRUCT_TYPE istructype,int istory,DWORD color);

	~CPlateStruc(void){Clear();}

	//int id; //��������id����1��ʼ��ţ������湹���������
	//�߽��߶���
	int nLine; 
	//�߽��߶�����
	int *pLineIDM;

	float fThickness;  //����ܺ�ȣ������������͸ֲ�
	int iSubType;  //������ 0-ǽ����1-ǽ��
	int nRebarLayer; //�ֽ�������(ÿ������������)��0��ʾ�޸ֽ�
	int iBottomStory;  //�ײ���¥��ţ�ֻ��ǽ����Ч����ʱ����
	float fOffset; //ƫ�ľ࣬����3���򣨷��߷���
	float fRatio[2];  //����ʣ��壺���׽�,����������ʣ�ǽ��ˮƽ�����,���в㵥�������֮�ͣ��ٷ���
	float Angle[2];  //���ڸֽ��������XZƽ�潻�ߵļнǣ���λ���ȣ�����ǽ��������XYƽ��н�
	float fRebarArea;  //�ݽ������(m^2), ֻ��ǽ����Ч

	SECTION_MAT_TYPE SecType; //��������,��ѡ���Ͷ����� ȫ������gPlateSectionTypeTable[] ��,CFeaInterface::GetPlateTypeSpecValue�и��ݲ������ͶԸֽ����͸ְ�����������
	int nSteelLayer;   //�ְ������0��ʾ�޸ְ�
	float fSteelThick;  //�ְ��ܺ��

	//���²��������ڸ��������ֶ�
	float fAs; //��Ե���������(��λ��m2)����ֵ��ֻ��ǽ��Ч

	//����PKPM�ӿں���OnImportpkpm��ʹ�õ���ʱ�������������ļ���ֻ��ǽ��Ч
	float fAs_top;
	float fLine_Dead_load;
	float fLine_Live_load;
	float fAs_bot;

	//��ʱ���ݣ��������ļ�,u.x>1���Ϸ�����ʼ��u.x=10.0f��ʾδ���㣬���롢���ӡ��ƶ������ʱ��Ҫ����LocalCoorVector���¼���
	Vector4 u,v,w,c0;  //�ֲ�����ϵ��ʸ��������ԭ�㣬wΪ���߷���,
	//����ǽ��u��ǽ���ڣ���Z��ֱ������X�нǳ���ǣ�v��Z�غϣ�wΪ���ߡ���������ǽ��X�ᴹֱʱ��u=Y��
	//���ڰ壬u=X��v=Y��w=Z��wΪ���ߡ�
	//�����湹����uΪ��c0���XZ���빹��ƽ��Ľ��ߣ�����X�����ǣ�wΪ���ߡ���ʱ���á�

	//���ظ�ֵ�����
	CPlateStruc & operator=(const CPlateStruc &plate);

	void Clear();

	//���ñ����������������Сԭ���ݱ����
	void SetLineNum(int nline) 
	{
		nLine=nline;
		if(pLineIDM) delete[] pLineIDM; 
		pLineIDM=new int[nLine];
		ASSERT(pLineIDM);
	}

	//���ض������������˳�����еĶ������PointID����β�㲻�غϣ��ⲿ����ά���ڴ�PointID��pLineΪϵͳ�߶α������飬
	//��������Ľ�����겻�غϣ���û��������ͬ�����벻ͬ�ĵ�
	int GetVexID(int *PointID,const CLine *pLine) const; 

	//���ص㵽��ID�Ĺ�����
	BOOL GetPt2Line(PT2LINE *pPt2Line,const CLine *pLine);

	//��������ҵϰ�߼���ֲ�����ϵ��ʸ����ԭ��,pVexArray,pLineArrayΪȫ�ֵĵ��������
	BOOL LocalCoorVector_Standard(const CVertex *pVexArray,const CLine *pLineArray,Vector4 &c0,Vector4 &u,Vector4 &v,Vector4 &w);

	//�����ι�ϵ����ֲ�����ʸ����wΪ���ߣ������ŷ������ֶ���u��v����������ϵû�й�ϵ
	BOOL LocalCoorVector(const CVertex *pVexArray,const CLine *pLineArray,Vector4 &c0,Vector4 &u,Vector4 &v,Vector4 &w);

	//���������߶�ID���ӵ�j���߶ο�ʼ��way>0�����������У�way<0������������
	void RenewLineID(int j,int way);

	//�������ֲ�,nLayer--�ֲ�����fThick--ÿ���ȣ����ȷֲ㣬pos--ÿ��λ�����飬iMaxLayers--pos��������
	//void GetConcLayer(int &nLayer,double &fThick,double *pos,int iMaxLayers);

	//���,���طֲ�����pThick--ÿ���ȣ�iMaxLayers--������
	int GetRebarLayer(double *pThick,int iMaxLayers);
	int GetRebarLayer(float *pThick,int iMaxLayers);

	//�õ����귶Χ
	void GetRange(Vector4 &rMin,Vector4 &rMax);

	//����ǽ�ĸ߶ȺͿ�ȣ��ڰ�����
	void GetWallSize(float &fWidth,float &fHeight);

	//����ǽ�Ĺ涨��෶Χ��������
	void GetWallRebarUnitArea(float &fHorzArea,float &fVertArea);

	//������ǽ�ֽ���������λ��kN
	float GetRebarWeight();

	virtual BOOL Read(CASCFile &fin,STRUCT_TYPE iType,int &idf);   //�Զ��ͷ�ԭ��pLineIDM�ڴ棬���������ڴ�,iType֧��ǽ��
	virtual BOOL Write(CASCFile &fout,int idf,int secid,STRUCT_TYPE iType);
	
	//�����Ϣ��д
	virtual BOOL ReadDesignInfo(CASCFile &fin,int idf);   //�Զ��ͷ�ԭ��pLineIDM�ڴ棬���������ڴ�,iType֧��ǽ��
	virtual BOOL WriteDesignInfo(CASCFile &fout,int idf);
};

#define NUM_STORY_PROP 13  //¥�����Բ�������

//¥����
class _SSG_DLLIMPEXP CStory
{
public:
	CStory(void)
	{
		Init();
	}

	~CStory(void){;}

	CStory(CStory &story)
	{
		*this=story;
	}

	float fHeight; //���
	float zTop;  //�ݶ����
	int iStoryType;  //1-��ͨ¥�㣻2-�ռ�¥��

	float fStifCenterX;
	float fStifCenterY;
	float fMassCenterX;
	float fMassCenterY;
	//��Ե��������
	//bit0-2: ��ֵ���壬����λ��0--Լ����Ե������1-�ײ���ǿ֮�ڵĹ����Ե������2-�ײ���ǿ֮�ϵĹ����Ե����
	//bit8-15:  ��ֵ���壬����λ��������ȼ�,0-- ��һ����1 -- һ��(9��)��2 -- һ��(8��)��3 -- ������ 4 -- ������5 -- �ļ�
	////bit3-5: ��ֵ���壬����λ������ȼ� 0-��һ����1-һ����2 -- ������ 3-- ����,4- �ļ���5-������
	int iStoryProp;

	//¥�㹹������,��Ϊ�������ݶ�д,��9�ֹ���
	float fPara[16][Sys_StructTypeNum];  //16��������STRUCT_PROPERTY1˳�򱣳�һ��(��3��ʼ),0-12���ã����ݵ�λ�����һ��
	CString sRebar[Sys_StructTypeNum],/*sStirrup[Sys_StructTypeNum],*/sConc[Sys_StructTypeNum],sSteel[Sys_StructTypeNum]; //������g_StructKeywordһ��
	float zBottom(void) const {return zTop-fHeight;} //��ױ��

	int GetEarthQuakeClass(void)
	{
		int k=(iStoryProp>>8)&0xff;
		//if(k==0xff) k=-1;
		if(k>=Sys_EQ_Class_Num) k=Sys_EQ_Class_Num-1;
		if(k<0) k=0;
		return k;
	};
	void SetEarthQuakeClass(int k)
	{
		if(k>=Sys_EQ_Class_Num) k=Sys_EQ_Class_Num-1;
		if(k<0) k=0;
		//if(k==-1) k=0xff;
		k=k<<8;
		iStoryProp &= 0xffff00ff;
		iStoryProp |= k;
	};

	//��ע��¥�㿹��ȼ� 2017��10��9��
	//int GetEarthQuakeGrade(void)
	//{
	//	int k=(iStoryProp>>3)&0x1f;
	//	if(k>=Sys_EQ_Class_Num) k=Sys_EQ_Class_Num-1;
	//	if(k<0) k=0;
	//	return k;
	//};
	//void SetEarthQuakeGrade(int k)
	//{
	//	if(k>=Sys_EQ_Class_Num) k=Sys_EQ_Class_Num-1;
	//	if(k<0) k=0;
	//	k=k<<3;
	//	iStoryProp &= 0xffffffe3;
	//	iStoryProp |= k;
	//};

	int GetEdgeType(void)
	{
		int k=iStoryProp&0x07;
		if(k<0) k=0;
		if(k>2) k=2;
		return k;
	}

	void SetEdgeType(int k)
	{
		iStoryProp &= 0xfffffff8;
		iStoryProp |= k;
		if(k<0) k=0;
		if(k>2) k=2;
	}

	void Init(void); //����Ĭ��ֵ

	void SetName(CString sname)
	{
		sname.Trim(); 
		if(sname==L"") 
		{
			AfxMessageBox(L"Story name is empty.");
			return;
		}
		sName=sname;
	}
	CString GetName(void) const {return sName;}
	void SetGroup(CString sgroup)
	{
		sgroup.Trim();
		if(sgroup==L"") 
		{
			AfxMessageBox(L"Group name is empty.");
			return;
		}
		sGroup=sgroup;
	}
	CString GetGroup(void) const {return sGroup;}

	CStory & operator=(const CStory &story)
	{
		if(this==&story) return *this;
		sName=story.sName;
		sGroup=story.sGroup;
		fHeight=story.fHeight;
		iStoryType=story.iStoryType;
		zTop=story.zTop;
		iStoryProp=story.iStoryProp;
		fStifCenterX		=story.fStifCenterX		;
		fStifCenterY		=story.fStifCenterY		;
		fMassCenterX	=story.fMassCenterX	;
		fMassCenterY	=story.fMassCenterY	;
		for(int j=0;j<Sys_StructTypeNum;j++) 
		{
			for(int i=0;i<16;i++) 
			{
				fPara[i][j]=story.fPara[i][j];
			}
			sRebar[j]=story.sRebar[j];
			//	sStirrup[j]=story.sStirrup[j];
			sConc[j] =story.sConc[j] ;
			sSteel[j]=story.sSteel[j];
		}
		return *this;
	}

	virtual void Read(CASCFile &fin);   
	virtual void Write(CASCFile &fout,int idf);
	//�����Ϣ��д
	virtual void ReadDesignInfo(CASCFile &fin);   
	virtual void WriteDesignInfo(CASCFile &fout,int idf);

protected:
	//¥����Ʋ���
	CString sName;  //¥����
	CString sGroup; //��������


};



//����Ԫ����������
class _SSG_DLLIMPEXP CBeamElm : public CPrimitiveProp
{
public:
	CBeamElm(){	Clear();}

	union
	{
		struct
		{
			int VexIDM1,VexIDM2;  //�˵�IDM
		};
		int pVexIDM[2];
	};

	int BeamStrucIDM; //�����Ĺ���ID�����ڻ�������Ϣ
	//STRUCT_TYPE iStrucType;  //�������ͣ���Ҫ����opengl��ʾ�����Բ�ѯ


	//���������½ӵ����˻����ɴ����½ӵ�Ԫ���������Ҫ����һ�ݱ�ʶ��
	DWORD dwFlag;	//��λ���ƣ���0λ��0--������ʹ�ý����е���ά��1--����(�����ǽԼ����Ե������)����ʹ����ά��Ϣ��//��1λ:1-���쵽ǽ����ĵ�Ԫ
	BOOL bArtiNode1,bArtiNode2;  //false--�̽ӣ�true--�½�,��VexIDM1,VexIDM2��Ӧ

	//CFeaInterface���ɽӿ�����ʱ�Ų���������������ļ�
	int iBlock;  //�ֿ�ID,ע�ⲻ����ţ�������

	DWORD dwHingeColor;  //���Խ���ɫ  ����ɫ����
	BOOL bHaveHinge;

	//�Ƿ������Ԫ
	BOOL IsSecendBeam(void) { return dwFlag&0x01; };

	//�Ƿ����������Ԫ
	BOOL IsExtendElm(void) { return dwFlag&0x02; };

	const CBeamStruc &GetBeam(const CArray<CBeamStruc,CBeamStruc&>  &aBeam) const
	{
		if(BeamStrucIDM<0 || BeamStrucIDM>=aBeam.GetCount()) return *(CBeamStruc *)NULL;
		return aBeam[BeamStrucIDM];
	}

	const CBeamStruc *GetBeamP(const CBeamStruc *pBeam,int nBeamStruct) const
	{
		if(!pBeam) return NULL;
		if(BeamStrucIDM<0 || BeamStrucIDM>=nBeamStruct) return NULL;
		return pBeam+BeamStrucIDM;
	}


	float Length(const CVertex *pVex);  //���㵥Ԫ����,pVexΪ�����������

	//�õ����귶Χ
	void GetRange(Vector4 &rMin,Vector4 &rMax);

	//���չ�����������
	void CopyProp(const CBeamStruc &beam)
	{
		*(CPrimitiveProp *)this=beam;
		if(beam.IsSecondBeam())
			dwFlag |= 0x01;
		else
			dwFlag &= ~0x01;
	}

	void Clear(void)
	{
		iBlock=0;
		BeamStrucIDM=-1;
		dwFlag=0;
		bArtiNode1=bArtiNode2=FALSE;
		VexIDM1=VexIDM2=-1;
		bHaveHinge=FALSE;
	}

	//���´����ڴ棬����ԭ�����ݣ��ͷ�ԭ�����ڴ档���¾�ָ�벻��ͬһ������ʱ�����ó���Ӧ���þ�ָ��ΪNULL
	static CBeamElm *Renew(CBeamElm  *&oldp,int oldCount,int newCount)
	{
		if(oldCount==newCount) return oldp;

		CBeamElm *newp=new CBeamElm[newCount];
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

	//�����߹����ֲ����굥λ��ʸ����������ת��
	//ˮƽ������e1Ϊ���߷���e2��e3Ϊ����ֲ����귽��
	//���򹹼���e1=eZΪ���߷���e2��e3Ϊ����ֲ����귽��
	void LocalCoorVector(Vector4 &u,Vector4 &v,Vector4 &w) const;


	virtual BOOL Read(CASCFile &fin);
	virtual BOOL Write(CASCFile &fout,int idf,int idf_Struct,STRUCT_TYPE itype);

	virtual inline void ReadBin(CFile &fin);
	virtual inline BOOL WriteBin(CFile &fout);

};

//�������浥Ԫ����������
class _SSG_DLLIMPEXP CTriangleElm : public CPrimitiveProp
{
public:
	CTriangleElm(void) {Clear();}

	//enum {nVex=3}; //�߽���������غ�
	int pVexIDM[3];  //�˵�ID����
	int PlateStrucIDM; //�����Ĺ���ID�����ڻ�������Ϣ
	//STRUCT_TYPE iStrucType;

	//CFeaInterface���ɽӿ�����ʱ�Ų���������������ļ�
	int iBlock;  //�ֿ�ID

	const CPlateStruc &GetPlate(const CArray<CPlateStruc,CPlateStruc&>  &aPlate) const
	{
		if(PlateStrucIDM<0 || PlateStrucIDM>=aPlate.GetCount()) return *(CPlateStruc *)NULL;
		return aPlate[PlateStrucIDM];
	}

	const CPlateStruc *GetPlateP(const CPlateStruc *pPlate,int nPlate) const
	{
		if(!pPlate) return NULL;
		if(PlateStrucIDM<0 || PlateStrucIDM>=nPlate) return NULL;
		return pPlate+PlateStrucIDM;
	}

	//���չ�����������
	void CopyProp(const CPlateStruc &plate) 
	{
		*(CPrimitiveProp *)this=plate;
		//iStrucType=plate.iStrucType;
	}

	float Area(const CVertex *pNode) const;  //�������������>0,pNodeΪ�����������

	void Clear(void) {PlateStrucIDM=-1;iBlock=0;}

	//���´����ڴ棬����ԭ�����ݣ��ͷ�ԭ�����ڴ档���¾�ָ�벻��ͬһ������ʱ�����ó���Ӧ���þ�ָ��ΪNULL
	static CTriangleElm *Renew(CTriangleElm  *&oldp,int oldCount,int newCount)
	{
		if(oldCount==newCount) return oldp;

		CTriangleElm *newp=new CTriangleElm[newCount];
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

	//����ֲ�����ϵ��ʸ��(u,v,w)��ԭ��c0���빹���涨��ͬ
	//�빹����LocalCoorVector_Standardһ��
	BOOL LocalCoorVector_Standard(Vector4 &c00,Vector4 &u,Vector4 &v,Vector4 &w) const;
	//wΪ���ߣ������ŷ������ֶ���u��v����������ϵû�й�ϵ
	BOOL LocalCoorVector(const CVertex *pVexArray,Vector4 &c00,Vector4 &u,Vector4 &v,Vector4 &w) const;

	//�������ĵ����꣬pVexΪȫ�ֽ������,�����������Σ��������Ҫ�ô���������������������м���
	CVertex GetCenter(const CVertex *pVex) const;

	//�õ����귶Χ
	void GetRange(Vector4 &rMin,Vector4 &rMax);

	virtual BOOL Read(CASCFile &fin); //��������麯���ؼ���virtual��д�ɲ�д���������麯��
	virtual BOOL Write(CASCFile &fout,int idf,int idf_Struct,STRUCT_TYPE itype);

	virtual inline void ReadBin(CFile &fin);
	virtual inline BOOL WriteBin(CFile &fout);
};


//�Ľ���ı����浥Ԫ����������
class _SSG_DLLIMPEXP CQuadElm : public CPrimitiveProp
{
public:
	CQuadElm(void) {Clear();}

	enum {VEXNUM=4}; //�߽���������غ�
	int pVexIDM[VEXNUM];  //�˵�ID����
	int PlateStrucIDM; //�����Ĺ���ID�����ڻ�������Ϣ
	//STRUCT_TYPE iStrucType;

	//CFeaInterface���ɽӿ�����ʱ�Ų���������������ļ�
	int iBlock;  //�ӿ��е�Ԫ����ID

	const CPlateStruc &GetPlate(const CArray<CPlateStruc,CPlateStruc&>  &aPlate) const
	{
		if(PlateStrucIDM<0 || PlateStrucIDM>=aPlate.GetCount()) return *(CPlateStruc *)NULL;
		return aPlate[PlateStrucIDM];
	}

	const CPlateStruc *GetPlateP(const CPlateStruc *pPlate,int nPlate) const
	{
		if(!pPlate) return NULL;
		if(PlateStrucIDM<0 || PlateStrucIDM>=nPlate) return NULL;
		return pPlate+PlateStrucIDM;
	}

	//���չ�����������
	void CopyProp(const CPlateStruc &plate) 
	{
		*(CPrimitiveProp *)this=plate;
		//iStrucType=plate.iStrucType;
	}

	float Area(const CVertex *pNode) const;  //�����ı������>0,pNodeΪ�����������

	//�õ����귶Χ
	void GetRange(Vector4 &rMin,Vector4 &rMax);

	void Clear(void) {PlateStrucIDM=-1;iBlock=0;}

	//���´����ڴ棬����ԭ�����ݣ��ͷ�ԭ�����ڴ档���¾�ָ�벻��ͬһ������ʱ�����ó���Ӧ���þ�ָ��ΪNULL
	static CQuadElm *Renew(CQuadElm  *&oldp,int oldCount,int newCount)
	{
		if(oldCount==newCount) return oldp;

		CQuadElm *newp=new CQuadElm[newCount];
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

	//����ֲ�����ϵ��ʸ��(u,v,w)��ԭ��c0���빹���涨LocalCoorVector_Standard��ͬ
	BOOL LocalCoorVector_Standard(Vector4 &c00,Vector4 &u,Vector4 &v,Vector4 &w) const;
	//wΪ���ߣ������ŷ������ֶ���u��v����������ϵû�й�ϵ
	BOOL LocalCoorVector(const CVertex *pVexArray,Vector4 &c00,Vector4 &u,Vector4 &v,Vector4 &w) const;

	//�������ĵ����꣬pVexΪȫ�ֽ�����飬�������Ҫ�ô���������������������м���
	CVertex GetCenter(const CVertex *pVex) const;

	virtual BOOL Read(CASCFile &fin); //��������麯���ؼ���virtual��д�ɲ�д���������麯��
	virtual BOOL Write(CASCFile &fout,int idf,int idf_Struct,STRUCT_TYPE itype);

	virtual void ReadBin(CFile &fin);
	virtual BOOL WriteBin(CFile &fout);
};

struct DATA_SEQUENCE2
{
	float t,v;
};
//����ϵ���࣬2������
class _SSG_DLLIMPEXP CDataSequence2
{
public:
	CDataSequence2(void){fname=L"";iWaveLibIndex=-1; iWaveLib=0; pData=NULL; nPoints=0; 
	fMinValue=fMaxValue=0;fMinValueTime=fMaxValueTime=0;fMaxFileTime=0;}

	CDataSequence2(const CDataSequence2 &ds)
	{
		*this=ds;
	}

	~CDataSequence2()
	{
		Clear();
	}

	CString fname; //�ļ���
	int iWaveLibIndex; //�Ǳ��� 2015.6.11
	int iWaveLib;	//0----SSG���𲨿⣬ 1-----�û��Զ��岨
	int nPoints;  //���ݵ���

	//����Ϊ��ʱ����
	float fMinValue,fMaxValue;  //�����Сֵ�������ļ�ʱͳ�Ƶõ�
	float fMinValueTime,fMaxValueTime;  //�����Сֵʱ�̣������ļ�ʱͳ�Ƶõ� //2016.3.16
	float fMaxFileTime;  //�����ļ��е����ʱ��

	DATA_SEQUENCE2	*pData;

	void Clear(void) 
	{
		if (pData){delete[] pData;	pData=NULL;}

		nPoints=0;
		//fMinValue=fMaxValue=0;
		//fname=L"";
	}
	BOOL IsValid(){return nPoints>0 && pData;}

	//��ֵ���������
	CDataSequence2 & operator=(const CDataSequence2& data)
	{
		if(this==&data) return *this;
		Clear();
		fname=data.fname;
		iWaveLibIndex = data.iWaveLibIndex;
		iWaveLib =data.iWaveLib;
		nPoints=data.nPoints;
		pData=new DATA_SEQUENCE2[nPoints];
		ASSERT(pData);
		for(int i=0;i<nPoints;i++)
		{
			pData[i]=data.pData[i]; 
		}
		fMinValue=data.fMinValue;
		fMaxValue=data.fMaxValue;
		fMinValueTime=data.fMinValueTime;
		fMaxValueTime=data.fMaxValueTime;
		fMaxFileTime=data.fMaxFileTime;
		return *this;
	}

	//2017�汾����
	void ReadAcc2017(void); //ֻ��ȡ����nPoints��pData

};

//������ص�һ����������
class _SSG_DLLIMPEXP CEarthQuake
{
public:
	CEarthQuake(void);
	CEarthQuake(CEarthQuake &eq) {*this=eq;}
	~CEarthQuake(){;}

	int iEarthQuakeProbility;
	int iAccDefineMethod;
	float fMainAmpEffect,f2ndAmpEffect,f3rdAmpEffect;  //��Ч��ֵ��������ٶȷ�ֵ���η����ֵ���ٶȣ���ֱ�����ֵ���ٶ� 
	float fMainAmp,f2ndAmp,f3rdAmp; // ʵ�ʷ�ֵ��������ٶȷ�ֵ���η����ֵ���ٶȣ���ֱ�����ֵ���ٶ�
	float fTimeInterval;	//���ݵ�ʱ����
	float fStartComputeTime;//ʱ�̷�����ʼʱ��
	float fEndComputeTime;  //ʱ�̷�����ֹʱ��
	float fMaxFileTime;		//�������ʱ��=max(X-�ļ����ʱ��, Y-�ļ����ʱ��, Z-�ļ����ʱ��)
	int iMainDir;			//������0--X��1--Y


	CDataSequence2 cAX,cAY,cAZ;  //�����ļ��е�ԭֵ

	void GetRatio(float &fRatioX,float &fRatioY,float &fRatioZ);  //����fMainAmp,fRatio1,fRatio2����fRatioX,fRatioY,fRatioZ
	void ReadData();  //��ȡ��������ĵ�������
	int CreateData(float *&ax,float *&ay,float *&az);  //�������飬��ֵ���㵱ǰ������е�����ص�
	void  GetRealPeakAccValue(); //��fMainAmp
	CEarthQuake & operator=(const CEarthQuake &eq);
	BOOL  operator==(const CEarthQuake &eq);//�� 2018��3��2��

	void Read10(CASCFile &fin);  //ֻ��ȡ������Ϣ������ϵ����ʹ��ʱ��ȡ
	void Read(CASCFile &fin);  //ֻ��ȡ������Ϣ������ϵ����ʹ��ʱ��ȡ
	void Write(CFile &fout); //ֻ����������Ϣ
};



class CLoadCase;
class _SSG_DLLIMPEXP COutput
{
public:
	//	COutput() {value=0;}
	COutput() {value=23;}	//�Ǳ��� 2015.6.18
	COutput(const COutput &out) {*this=out;}
	~COutput() {;}

	void SetValue(int v) {value=v&0xff;}
	int GetValue() const {return value;}

	void SetOutputStrain(BOOL bOut) {bOut?value|=0x01:value&=~0x01;}
	void SetOutputStress(BOOL bOut) {bOut?value|=0x02:value&=~0x02;}
	void SetOutputForce(BOOL bOut) {bOut?value|=0x04:value&=~0x04;}
	void SetOutputDamage(BOOL bOut) {bOut?value|=0x08:value&=~0x08;}
	void SetOutputPlasticStrain(BOOL bOut) {bOut?value|=0x10:value&=~0x10;}

	BOOL IsOutputStrain() const {return (value&0x01)!=0?1:0;}
	BOOL IsOutputStress() const {return (value&0x02)!=0?1:0;}
	BOOL IsOutputForce() const {return (value&0x04)!=0?1:0;}
	BOOL IsOutputDamage() const {return (value&0x08)!=0?1:0;}
	BOOL IsOutputPlasticStrain() const {return (value&0x10)!=0?1:0;}

	COutput &operator=(const COutput &out)
	{
		if(this==&out) return *this;
		value=out.GetValue();
		return *this;
	}

private:
	// 0     1     2     3      4         5    6     7  
	//Ӧ��  Ӧ��  ����  ����  ����Ӧ��  ����  ����  ����
	int value;
};

//�������
class _SSG_DLLIMPEXP CLoadCase
{
public:
	CLoadCase(void);
	CLoadCase(CLoadCase &lc)
	{
		*this=lc;
	}

	~CLoadCase() {}

	CString sCaseName;  //�����������
	CString sMemo;  //˵��
	float fCoeffLiveLoad;		//�����������Ȩϵ��
	float fCoeffDeadLoad;		//�����������Ȩϵ��

	//��ʽ�������ز���
	BOOL  bCloseNonLinear; //�Ƿ�رռ��η����ԣ�1-�ر�
	BOOL  bCalIsolatorBeta; //�Ƿ�رռ��η����ԣ�1-�ر�
	float fMassDamp;	//��������ϵ����
	float fStiffDamp; //�ն�����ϵ��
	float fTerm1;  	//��������1
	float fTerm2;  	//��������2
	float fKsi1;   	//���������1
	float fKsi2;   	//���������2
	BOOL bInputAlpha;	//�Ƿ�ֱ������ //ver32
	float fTimeStep;  //����ʱ�䲽��
	int iCrtCons;  //��������ά����ģ��,0���ԡ�1�������ˡ�2-���ܻ����
	int iRebarCons;  //�ֽ��ģ��,0���ԡ�1�����ԡ�2-���ܻ����
	int	iStirrupCons;  //��������ͣ�ȡֵΪ0--���ԡ�1--�淶ģ�͡�2---Լ��������ģ��
	int iSlabElastic; //�Ƿ���¥�嵯��
	int iShearNonLinear; //�Ƿ��Ǽ��з�����
	float fShearGama; //��������Ӧ��
	float fShearRatio; //����������նȱ�
	float fWallShear; //����ǽ�ֲ��ֽ������ϵ��
	int	iDamage;  //���˶��巽ʽ
	int	iMethod;  //��������
	float fWaveAngle; //����������������ϵ�н�
	BOOL bStiffDamp;  //�Ƿ����ն�����
	int	iDampType;  //�������ͣ�0-Rayleigh���ᣬ1-��������
	int nModeNum;  //���͸��������ڼ����������ᣬm_iDampType=1ʱ��Ч
	int iModalDampType;  //�����������ͣ�0-ȫ¥ͳһ��1-����������
	int iSimpleModalDamp;  //����������
	float fModeDamp[Sys_MaxModeNum];  //��Ӧ��m_iModeNum�ĸ������͵�����ȣ�m_iDampType=1ʱ��Ч
	float fModeDampSteel[Sys_MaxModeNum];  //��Ӧ��m_iModeNum�ĸ������͵�����ȣ�m_iDampType=1ʱ��Ч//2017.8.26

	CEarthQuake cEarchQuake;  //������Ϣ

	CLoadCase& operator=(const CLoadCase& lc);
	BOOL operator==(const CLoadCase& lc);//ISO��������ã���2018��3��6��
	BOOL isIsoParaEqual(const CLoadCase& lc);//ISO��������ã��жϹ��������Ƿ�ı� ��2018��3��6�� ������������Ϣ�͹�����


	void Read10(CASCFile &fin);
	void Read20(CASCFile &fin);
	void Read(CASCFile &fin);
	void Write(CFile &fout);


};

class _SSG_DLLIMPEXP CLoadCollection
{
public:
	CLoadCollection(){;}
	CLoadCollection(const CLoadCollection &load) 
	{
		*this=load;
	};
	~CLoadCollection(){RemoveAll();}

	int Append(CLoadCase *load);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const {return aLoadCasePtr.GetCount();}

	CLoadCase *GetAt(int i) {return aLoadCasePtr.GetAt(i);}

	CLoadCase *operator[](int i) {return aLoadCasePtr[i];}

	void SetAt(int i,CLoadCase *load) {aLoadCasePtr[i]=load;}

	CLoadCollection& operator=(const CLoadCollection&load);

	void Write(CFile &fout) 
	{
		for(int i=0;i<aLoadCasePtr.GetCount();i++)
			aLoadCasePtr[i]->Write(fout);
	}

private:
	CArray<CLoadCase*,CLoadCase*> aLoadCasePtr; //���ع�����ϼ���
};

//��ѡ����
class _SSG_DLLIMPEXP CWaveCollection
{
public:
	CWaveCollection(){;}
	CWaveCollection(const CWaveCollection &wave) 
	{
		*this=wave;
	};
	~CWaveCollection(){RemoveAll();}

	int Append(CEarthQuake *wave);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const {return awavePtr.GetCount();}

	CEarthQuake *GetAt(int i) {return awavePtr.GetAt(i);}

	CEarthQuake *operator[](int i) {return awavePtr[i];}

	void SetAt(int i,CEarthQuake *wave) {awavePtr[i]=wave;}

	CWaveCollection& operator=(const CWaveCollection&wave);

	void Write(CFile &fout) 
	{
		for(int i=0;i<awavePtr.GetCount();i++)
			awavePtr[i]->Write(fout);
	}

private:
	CArray<CEarthQuake*,CEarthQuake*> awavePtr; //���ع�����ϼ���
};


//������
class _SSG_DLLIMPEXP CGroup
{
public:
	CGroup(void){nPrimitive=0; pIDG=NULL;}
	~CGroup(void){if(pIDG) delete[] pIDG; nPrimitive=0; pIDG=NULL;}

	CString sName;  //����
	int nPrimitive; //����ͼԪ��Ŀ
	int *pIDG; //����ͼԪIDG

	CGroup &operator=(const CGroup &grp)
	{
		if(this==&grp) return *this;
		sName=grp.sName;
		nPrimitive=grp.nPrimitive;
		delete[] pIDG;
		pIDG=new int[nPrimitive];
		for(int i=0;i<grp.nPrimitive;i++)
		{
			pIDG[i]=grp.pIDG[i];
		}
		return *this;
	}

	//�õ�����������Ԫ�Ϳǵ�Ԫ����
	void CreateElmGroup(const CFrame &frame,const CMesh &mesh,int &nBeamElm,int *&pBeamElm,int &nShellElm, int *&pShellElm,int &nQuadElm, int *&pQuadElm);   

	//�õ�������һά�����Ͷ�ά��������
	void CreateStructGroup(const CFrame &frame,int &nBeam,int *&pBeam,int &nPlate, int *&pPlate);   

	void Read(CASCFile &fin);
	void Write(CFile &fout);
};

class _SSG_DLLIMPEXP CGroupCollection
{
public:
	CGroupCollection(){;}
	CGroupCollection(const CGroupCollection &gc) 
	{
		*this=gc;
	};
	~CGroupCollection(){RemoveAll();}

	int Append(CGroup *group);

	void RemoveAt(int index);

	void RemoveAll();

	INT_PTR GetCount() const {return aGroupPtr.GetCount();}

	CGroup *GetAt(int i) {return aGroupPtr.GetAt(i);}

	CGroup *operator[](int i) {return aGroupPtr[i];}

	CGroupCollection& operator=(const CGroupCollection& gc);

	void Write(CFile &fout) 
	{
		for(int i=0;i<aGroupPtr.GetCount();i++)
			aGroupPtr[i]->Write(fout);
	}

private:
	CArray<CGroup*,CGroup*> aGroupPtr; //������Ϣ��������Ϣֻ������ܣ�����������
};

//һ��ʩ���׶���Ϣ
class _SSG_DLLIMPEXP CStage
{
public:
	CStage(void) {iStoryMin=iStoryMax=-1;}
	~CStage(void) {aGroupName.RemoveAll();}

	//��Ա����
	int iStoryMin;  //¥�㷶Χ,��ͬ�ļ��ز�¥�㲻���ظ�����������ز�������¥��֮�⣬������¥�㷶ΧΪ��-1��-1��
	int iStoryMax;
	CArray<CString,CString&> aGroupName;   //���ڱ��μ��ز��ķ�����������

	//��Ա����
	CStage & operator=(const CStage &stage)
	{
		if(this==&stage) return *this;
		iStoryMin=stage.iStoryMin;
		iStoryMax=stage.iStoryMax;
		aGroupName.RemoveAll();
		aGroupName.Copy(stage.aGroupName);
		//for(int i=0;i<stage.aGroupName.GetCount();i++)
		//{
		//	CString str=stage.aGroupName[i];
		//	aGroupName.Add(str);
		//}
		return *this;
	}


	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
};


//ʩ���׶����ݼ���
class _SSG_DLLIMPEXP CStageCollection
{
public:
	CStageCollection(void){;}

	~CStageCollection(void);
	//��Ա����
	CArray<CStage*,CStage*> aStagePtr; //¥��ʩ���׶����飬���еĹ���Ҫ�ų�ǰ���������ù�������

	//��Ա����

	void Clear(void) ;

	CStageCollection & operator=(const CStageCollection &stage)
	{
		if(this==&stage) return *this;

		Clear();

		for(int i=0;i<stage.aStagePtr.GetCount();i++)
		{
			CStage *pstage=new CStage;
			*pstage=*(stage.aStagePtr[i]);
			aStagePtr.Add(pstage);
		}

		return *this;
	}

	void Read(CASCFile &fin);
	void Write(CASCFile &fout);
};

class _SSG_DLLIMPEXP CStoryItem
{
public:
	CStoryItem(void) {pStory=NULL;}

	CStoryItem(CStoryItem &item)
	{
		*this=item;
	}

	~CStoryItem() {delete[] pStory;pStory=NULL;}

	int nStory;
	CStory *pStory;
	int iStoryMin;//��ʾ�����¥�� �� 2016��12��13��
	int iStoryMax;//��ʾ�����¥��

	CStoryItem & operator=(CStoryItem &item)
	{
		if(this==&item) return *this;

		Clear();

		nStory=item.nStory;
		if(nStory>0)
		{
			pStory=new CStory[nStory];
			if(!pStory)
			{
				Clear();
				return *this;
			}

			for(int i=0;i<=nStory;i++)
				pStory[i]=item.pStory[i];
		}
		iStoryMin=item.iStoryMin;
		iStoryMax=item.iStoryMax;

		return *this;
	}

	void Clear(void)
	{
		nStory=0;
		delete[] pStory;
		pStory=NULL;
		iStoryMin=0;
		iStoryMax=0;
	}

};

STRUCT_TYPE GetStructType(const CBeamElm &elm);
STRUCT_TYPE GetStructType(const CTriangleElm &elm);
STRUCT_TYPE GetStructType(const CQuadElm &elm);


//��ĿȺ��Ϣ
struct MUL_PROJRCT
{
	MUL_PROJRCT(void)
	{
		sFile=L"";
		iFirstNode=0;
		iFirstBeamElm=0;
		iFirstTriElm=0;
		iFirstQuadElm=0;
		nNode=0;
		nBeamElm=0;
		nTriElm=0;
		nQuadElm=0;

		c0.x=0.0f;
		c0.y=0.0f;
		c0.z=0.0f;
		angle=0.0f;

		sName=L"";

		fRadium=0;
		fHalfHeight=0;
	};

	CString sFile;
	int iFirstNode;
	int iFirstBeamElm;
	int iFirstTriElm;
	int iFirstQuadElm;
	int nNode;
	int nBeamElm;
	int nTriElm;
	int nQuadElm;

	CVertex c0; //����ԭ��ƫ����
	Vector4 vMin,vMax; //ʵ�����귶Χ������������ƫ�ƺ���ת
	float fRadium; //���ռ�ذ뾶����
	float fHalfHeight; //¥�ߵ�һ�룬��
	float angle; //��z��ת�ǣ���λ��
	CString sName; //����������
};

class _SSG_DLLIMPEXP CRefPoint
{
public:
	CRefPoint(void){;}
	~CRefPoint() {aVex.RemoveAll();}

	void Clear(void) {aVex.RemoveAll();}


	//�л�һ����,���������������������TRUE������Ѿ�������ɾ��������FALSE
	BOOL SetVex(int vexid)
	{
		for (int i=0;i<aVex.GetCount();i++)
		{
			if(aVex[i]==vexid)
			{
				aVex.RemoveAt(i);
				return FALSE;
			}
		}
		aVex.Add(vexid);
		return TRUE;
	}

	CArray<int,int> aVex; //�������⽻����õĲο���ID
};

//���򹹼��Ƿ�λ���û�ѡ��Ĳ��λ�ƽ����λ�õļ����ڣ�������ţ��������򷵻�-1
//����û�δ���壬�򷵻�-2����ʾȱʡȫ�����
extern "C" _SSG_DLLIMPEXP int DriftPosEle(const CBeamElm &elm);
extern "C" _SSG_DLLIMPEXP int DriftPos(const CBeamStruc &pillar);


//�ߵ�Ԫ�Ƿ�ȫ�����ھ��η�Χ��
int IsInRect(const CBeamElm &elm,float xmin,float ymin,float xmax,float ymax);
int IsInRect(const CTriangleElm &elm,float xmin,float ymin,float xmax,float ymax);
int IsInRect(const CQuadElm &elm,float xmin,float ymin,float xmax,float ymax);
//�߹����Ƿ�ȫ�����ھ��η�Χ��
BOOL IsInRect(const CBeamStruc &beam,float xmin,float ymin,float xmax,float ymax);
BOOL IsInRect(const CPlateStruc &plate,float xmin,float ymin,float xmax,float ymax);

//����·��
class _SSG_DLLIMPEXP CDataPath
{
public:
	CDataPath(void) {;}
	~CDataPath() {aIDM.RemoveAll();}
	CDataPath(const CDataPath &path) 
	{
		*this=path;
	}

	CString sName;

	enum PATH_TYPE
	{
		PATHTYPE_ELEM=0,
		PATHTYPE_NODE=1,
	}iDataType;

	CArray<int,int> aIDM; //IDM����

	CDataPath &operator=(const CDataPath &path)
	{
		if(this==&path) return *this;

		sName=path.sName;
		iDataType=path.iDataType;
		aIDM.RemoveAll();
		aIDM.Copy(path.aIDM);
		return *this;
	}

	BOOL Read(CASCFile &fin);
	void Write(CASCFile &fout);
};

class _SSG_DLLIMPEXP CDataPathCollection
{
public:
	CDataPathCollection(void){;}
	~CDataPathCollection()
	{
		Clear();
	}
	CArray<CDataPath*,CDataPath*> aPathPtrArray;

	void Clear();

	BOOL Read(CASCFile &fin);
	void Write(CASCFile &fout);
};

//ȫ�ֺ���---------------------------------------------------------------------


//��ȡ������ȱʡ��ɫ
extern "C" _SSG_DLLIMPEXP COLORREF GetStructDefaultColor(STRUCT_TYPE type,int iSubType);



//���ڴ�ID(IDM)����ʰȡID(IDG),�궨���б�������ţ�����������Ԥ֪
//#define GETIDG(IDM,ArrayType) ((IDM)+(ArrayType))  
extern "C" _SSG_DLLIMPEXP int GetIDG(int idm,STRUCT_TYPE iType); 

//��ʰȡID(IDG)�����ڴ�ID(IDM)
extern "C" _SSG_DLLIMPEXP int GetIDM(int IDG);
//���ڴ�ID(IDM)����ʰȡID(IDG)
extern "C" _SSG_DLLIMPEXP STRUCT_TYPE GetPickedType(int IDG);

//��IDG����������ʼ����ֵ
extern "C" _SSG_DLLIMPEXP int GetBaseType(int IDG);



//��������ͬ�ĵ���кϲ�,���ؾɵ��ŵ��µ��ŵ�����index�� ͬʱԭ����������鱻���£���������Ϊ���������Ķ�̬�ڴ棬���ó��������Ӧ�ͷ�
//ʧ���򷵻ؿ�ָ��
extern "C" _SSG_DLLIMPEXP int *Merge(CVertex *pVex,int nOldNPoint,int &nNewPoint);

//��������Ժϲ�
//pVex2��pVex1����ƥ�䣬���ҵ��򷵻�pVex1��Ӧ��pID1���룬���򷵻�StartID��ʼ�ı���
//pID1��pVex2��pVex1�����±����0��ʼ
//pID1ΪpVex1��Ӧ�Ľ�����
extern "C" _SSG_DLLIMPEXP int *MergeWithArray(const int *pID1,int nVex1,const Vector4 *pVex1,int nVex2,const Vector4 *pVex2,int StartID);

//���ض���ζ����������,��β�㲻�غ�,���ɹ��򷵻�NULL
//��������Ľ�����겻�غϣ���û��������ͬ�����벻ͬ�ĵ�,���ó���Ӧ�ͷŷ��ص�ָ���ڴ�
//����: pPolygonLine--��˳��Χ�ɶ���ε��߶�����,�߶α��밴˳��������߶α�ŷ����������
extern "C" _SSG_DLLIMPEXP int *GetPolygonVexID(int nLine,const CLine *pPolygonLine);

//���׶�����,vex--�����׶δ�С��������,nData--�����С
//���ض�̬�����������������,�ⲿ��������ͷ�
extern "C" _SSG_DLLIMPEXP int *StackSortNodeByStage(int nData,CVertex  *vex); 

//���׶�����,beam--�����׶δ�С��������,nData--�����С
//���ض�̬�����������������,�ⲿ��������ͷ�
extern "C" _SSG_DLLIMPEXP int *StackSortBeamElmByStage(int nData,CBeamElm  *beam); 

//���׶�����,tri--�����׶δ�С��������,nData--�����С
//���ض�̬�����������������,�ⲿ��������ͷ�
extern "C" _SSG_DLLIMPEXP int *StackSortTriElmByStage(int nData,CTriangleElm  *tri); 
extern "C" _SSG_DLLIMPEXP int *StackSortQuadElmByStage(int nData,CQuadElm  *quad); 


//����XY���ڵ���ת�ǣ���λ���ȣ�center--��ת���ģ�p1,p2--��ת�������յ㣬��������Բ���ͬһԲ���ϣ�ֻ�����center�����������ϵĵ�
//��������ֻ��x,y����
extern "C" _SSG_DLLIMPEXP double RotateAngleDouble(const CVertex &center,const CVertex &p1,const CVertex &p2);



//�ṹ���ʷ����������ɵ����߶�
struct _SSG_DLLIMPEXP SUB_LINE
{
	int		nSubLine;	//��ʼ��Ϊ0����ʾû�л������߶�
	CLine	*pSubLine;	//���߶����飬��ʼ��ΪNULL
};

//�ṹ���Ƿ�����ǽ�õ�
struct _SSG_DLLIMPEXP LINE_USED
{
	LINE_USED(void) {bBeam=FALSE;bPillar=FALSE;bWall=FALSE;bBeamWall=FALSE;bAlong=TRUE;bLink=FALSE;bAnti=FALSE;}
	BOOL bBeam;    //�Ƿ����õ�
	BOOL bPillar;  //�Ƿ����õ�
	BOOL bWall;    //�Ƿ�ǽ�õ�������ǽ��ṹ���Ƿ�ͬ¥�㣬ǽ������ǽ
	BOOL bBeamWall;//�Ƿ�ǽ���õ�������ǽ����ṹ���Ƿ�ͬ¥��
	BOOL bAlong;   //�Ƿ���������˽½ӵ��߹���ʹ��
	BOOL bLink;    //�Ƿ�һ������ʹ��
	BOOL bAnti;    //�Ƿ����˽½ӵ��߹���ʹ��
	float	fWeight;	//�����ۼ�Ȩ��
	float	fMeshRatio;	//�����ۼƼ���ϵ��
};


//������ЧͼԪ
class _SSG_DLLIMPEXP CRemoveInvalidPrimitive
{
public:
	CRemoveInvalidPrimitive(void) {;}
	~CRemoveInvalidPrimitive(void) {;}

protected:
	virtual void RearrangeID()=0;  //���±���ID��ȥ����ЧͼԪ
	void RemoveInvalidVex(int &nVex,CVertex *pVex,int *index1,CGroupCollection &aGroup);      //ȥ����Ч��ܵ㣬��RearrengeID����
	void RemoveInvalidNode(int &nVex,CVertex *pVex,int *index1);      //ȥ����Ч�����㣬��RearrengeID����
	void RemoveInvalidBeamElm(int &nElm,CBeamElm *pElm,CVertex *pVex);   //��RearrengeID����
	void RemoveInvalidTriangleElm(int &nElm,CTriangleElm *pElm,CVertex *pVex);   //��RearrengeID����
	void RemoveInvalidQuadElm(int &nElm,CQuadElm *pElm,CVertex *pVex);   //��RearrengeID����
	void RemoveInvalidLine(int &nLine,CLine *pLine,CArray<CVertex,CVertex&> &aVex,int *index2,CGroupCollection &aGroup);   //��RearrengeID����
	void RemoveInvalidGuides(int &nGuides,CVertex *pVex,CLine *pLine,CGroupCollection &aGroup);   //��RearrengeID����
	void RemoveInvalidBeamStruc(int &nStruc,CArray<CLine,CLine&> &aLine,CBeamStruc *pStruc,int *index4,CGroupCollection &aGroup);   //��RearrengeID����
	void RemoveInvalidPlateStruc(int &nStruc,CArray<CLine,CLine&> &aLine,CPlateStruc *pStruc,int *index3,CGroupCollection &aGroup);   //��RearrengeID����

	void RemoveInvalidGroup(STRUCT_TYPE iPrimType,int nStruc,const int *index1,CGroupCollection &aGroup);  //�����ϸ�ͼԪ��������
};

extern "C" _SSG_DLLIMPEXP STRUCT_KEYWORD g_StructKeyword[Sys_StructTypeNum];
extern "C" _SSG_DLLIMPEXP STRUCT_PROPERTY1 g_PropTable1[16];
