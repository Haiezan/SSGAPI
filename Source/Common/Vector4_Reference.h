#pragma once
#ifndef _VECTOR4_GENERAL_
#define _VECTOR4_GENERAL_

#if !defined(_ENABLE_GENERALCPU_)
	#define _ENABLE_GENERALCPU_
#endif 

#include <assert.h>
#include <stdio.h>
#include "FastMath.h"
#include "UserDefine.h"

class Vector4CPU;

extern Vector4CPU g_VectorCPU_Zero;
extern Vector4CPU g_VectorCPU_One;


class Vector4CPU
{
public:
	union
	{
		struct
		{
			float x,y,z,w;
		};
		float felem[4];
		float coor[4];
		unsigned int ielem[4];
		struct
		{
			int id[3],n;
		};
	};

public:
	inline Vector4CPU(void)
	{
		// do nothing
	}

	inline Vector4CPU(float x, float y, float z, float w=1.0f)
	{
		Set(x, y, z, w);
	}

	inline Vector4CPU(float value)
	{
		Set(value);
	}

	inline Vector4CPU(unsigned int x, unsigned int y, unsigned int z, unsigned int w)
	{
		ielem[0] = x;
		ielem[1] = y;
		ielem[2] = z;
		ielem[3] = w;
	}

	inline Vector4CPU(unsigned int x)
	{
		ielem[0] = x;
		ielem[1] = x;
		ielem[2] = x;
		ielem[3] = x;
	}

	inline Vector4CPU(const float *coor)
	{
		Set(coor[0], coor[1], coor[2], 1.0f);
	}

	//重新创建内存，复制原来数据，释放原来的内存。若新旧指针不是同一个变量时，调用程序应设置旧指针为NULL
	static Vector4CPU *Renew(Vector4CPU  *&oldp,int oldCount,int newCount)
	{
		if(oldCount==newCount) return oldp;

		Vector4CPU *newp=new Vector4CPU[newCount];
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

	void ConsoleOutput(void);

	inline void Set(float x, float y, float z, float w=0.0f)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	inline void Set(float value)
	{
		this->x = value;
		this->y = value;
		this->z = value;
		this->w = value;
	}

	inline void Set(float *p)
	{
		this->x = p[0];
		this->y = p[1];
		this->z = p[2];
		this->w = p[3];
	}

	inline void SetX(float x)
	{
		this->x = x;
	}

	inline void SetY(float y)
	{
		this->y = y;
	}

	inline void SetZ(float z)
	{
		this->z = z;
	}

	inline void SetW(float w)
	{
		this->w = w;
	}

	inline void SetXYZ(const float *p)
	{
		x = p[0];
		y = p[1];
		z = p[2];
	}

	inline float GetX(void) const
	{
		return x;
	}

	inline Vector4CPU GetXXXX(void) const
	{
		Vector4CPU result(x);
		return result;
	}

	inline float GetY(void) const
	{
		return y;
	}

	inline Vector4CPU GetYYYY(void) const
	{
		Vector4CPU result(y);
		return result;
	}

	inline float GetZ(void) const
	{
		return z;
	}

	inline Vector4CPU GetZZZZ(void) const
	{
		Vector4CPU result(z);
		return result;
	}

	inline float GetW(void) const
	{
		return w;
	}

	inline Vector4CPU GetWWWW(void) const
	{
		Vector4CPU result(w);
		return result;
	}

	inline void StoreAligned(float *p)
	{
		p[0] = x;
		p[1] = y;
		p[2] = z;
		p[3] = w;
	}

	inline void Store(float *p)
	{
		p[0] = x;
		p[1] = y;
		p[2] = z;
		p[3] = w;
	}

	inline void StoreXYZ(float *p)
	{
		p[0] = x;
		p[1] = y;
		p[2] = z;
	}

	inline void Reciprocal(void)
	{
		x = 1.0f/x;
		y = 1.0f/y;
		z = 1.0f/z;
		w = 1.0f/w;
	}

	inline void Sqrt(void)
	{
		x = sqrtf(x);
		y = sqrtf(y);
		z = sqrtf(z);
		w = sqrtf(w);
	}

	//inline void ReciprocalSqrt(void)
	//{
	//	x = FastMath::ReciprocalSqrt(x);
	//	y = FastMath::ReciprocalSqrt(y);
	//	z = FastMath::ReciprocalSqrt(z);
	//	w = FastMath::ReciprocalSqrt(w);
	//}

	inline float Length(void) const
	{
		float vectorlength;
		
		float sum = x*x + y*y + z*z;
		vectorlength = sqrtf(sum);

		return vectorlength;
	}

	inline void Normalize(void)
	{
		float len = Length();
		if(len==0) return;
		x/=len;
		y/=len;
		z/=len;
	}

	inline float NormalizeAndGetLength(void)
	{
		float len = Length();
		x/=len;
		y/=len;
		z/=len;
		return len;
	}

	inline Vector4CPU &Abs(void)
	{
		x = fabs(x);
		y = fabs(y);
		z = fabs(z);
		w = fabs(w);

		return *this;
	}

	inline Vector4CPU &InvertSign(void)
	{
		x = -x;
		y = -y;
		z = -z;
		w = -w;

		return *this;
	}


	inline Vector4CPU Reverse(void)
	{
		Vector4CPU v1;
		v1.x = -x;
		v1.y = -y;
		v1.z = -z;
		v1.w = w;
		return v1;
	}

	inline Vector4CPU &Saturate(void)
	{
		if ( x > 1.0f ) x = 1.0f;
		if ( y > 1.0f ) y = 1.0f;
		if ( z > 1.0f ) z = 1.0f;
		if ( w > 1.0f ) w = 1.0f;

		if ( x < 0.0f ) x = 0.0f;
		if ( y < 0.0f ) y = 0.0f;
		if ( z < 0.0f ) z = 0.0f;
		if ( w < 0.0f ) w = 0.0f;
	
		return *this;
	}

	inline Vector4CPU &Clamp_to_0(void)
	{
		if ( x < 0.0f ) x = 0.0f;
		if ( y < 0.0f ) y = 0.0f;
		if ( z < 0.0f ) z = 0.0f;
		if ( w < 0.0f ) w = 0.0f;
	
		return *this;
	}

	inline Vector4CPU &Clamp_to_1(void)
	{
		if ( x > 1.0f ) x = 1.0f;
		if ( y > 1.0f ) y = 1.0f;
		if ( z > 1.0f ) z = 1.0f;
		if ( w > 1.0f ) w = 1.0f;

		return *this;
	}

	inline Vector4CPU &Floor(void)
	{
		x = floor(x);
		y = floor(y);
		z = floor(z);
		w = floor(w);
		return *this;
	}

	inline static Vector4CPU &GetZero(void)
	{
		return g_VectorCPU_Zero;
	}

	inline static Vector4CPU &GetOne(void)
	{
		return g_VectorCPU_One;
	}

	inline Vector4CPU &operator=(const Vector4CPU &rhs)
	{
		if(this==&rhs) return *this;

		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		return *this;
	}

	inline Vector4CPU &operator=(float value)
	{
		Set(value);
		return *this;
	}

	inline Vector4CPU &operator+=(const Vector4CPU &rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	inline Vector4CPU &operator+=(float value)
	{
		x += value;
		y += value;
		z += value;
		w += value;
		return *this;
	}

	inline Vector4CPU &operator-=(const Vector4CPU &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	inline Vector4CPU &operator-=(float value)
	{
		x -= value;
		y -= value;
		z -= value;
		w -= value;
		return *this;
	}

	inline Vector4CPU &operator*=(const Vector4CPU &rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		w *= rhs.w;
		return *this;
	}

	inline Vector4CPU &operator*=(float value)
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}

	inline Vector4CPU &operator/=(const Vector4CPU &rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		w /= rhs.w;
		return *this;
	}

	inline Vector4CPU &operator/=(float value)
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}

	inline float &operator[](int index)
	{
		assert(index>=0 && index<4);
		return felem[index];
	}

	static const char *InstructionType(void)
	{
		return "General_CPU";
	}

	inline bool operator<(const Vector4CPU that) const
	{
		return memcmp((void*)this, (void*)&that, sizeof(Vector4CPU)) > 0;
	}
};

inline bool operator==(const Vector4CPU &a, const Vector4CPU &b)
{
	bool result = (fabs(a.x-b.x)<g_cSysSizePara.Sys_PointError && fabs(a.y-b.y)<g_cSysSizePara.Sys_PointError && fabs(a.z-b.z)<g_cSysSizePara.Sys_PointError);
	return result;
}

inline bool operator!=(const Vector4CPU &a, const Vector4CPU &b)
{
	bool result = (a==b);
	return !result;
}

//精确相等
inline bool Equal(const Vector4CPU &a, const Vector4CPU &b) 
{
	return a.x==b.x && a.y==b.y && a.z==b.z;
}  

inline Vector4CPU operator+(const Vector4CPU &a, const Vector4CPU &b)
{
	Vector4CPU c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	c.w = a.w + b.w;

	return c;
}

inline Vector4CPU operator-(const Vector4CPU &b)
{
	Vector4CPU c;

	c.x = - b.x;
	c.y = - b.y;
	c.z = - b.z;
	c.w = - b.w;

	return c;
}

inline Vector4CPU operator-(const Vector4CPU &a, const Vector4CPU &b)
{
	Vector4CPU c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	c.w = a.w - b.w;

	return c;
}

inline Vector4CPU operator*(const Vector4CPU &a, const Vector4CPU &b)
{
	Vector4CPU c;

	c.x = a.x * b.x;
	c.y = a.y * b.y;
	c.z = a.z * b.z;
	c.w = a.w * b.w;

	return c;
}

inline Vector4CPU operator*(float f, const Vector4CPU &v)
{
	Vector4CPU result;

	result.x = f * v.x;
	result.y = f * v.y;
	result.z = f * v.z;
	result.w = f * v.w;

	return result;
}

inline Vector4CPU operator*(const Vector4CPU &v, float f)
{
	Vector4CPU result;

	result.x = f * v.x;
	result.y = f * v.y;
	result.z = f * v.z;
	result.w = f * v.w;

	return result;
}

inline Vector4CPU operator/(const Vector4CPU &a, const Vector4CPU &b)
{
	Vector4CPU c;

	c.x = a.x / b.x;
	c.y = a.y / b.y;
	c.z = a.z / b.z;
	c.w = a.w / b.w;

	return c;
}

inline Vector4CPU operator/(const Vector4CPU &a, float f)
{
	Vector4CPU c;

	c.x = a.x / f;
	c.y = a.y / f;
	c.z = a.z / f;
	c.w = a.w / f;

	return c;
}

inline Vector4CPU operator/(float f, const Vector4CPU &a)
{
	Vector4CPU c;

	c.x = f / a.x;
	c.y = f / a.y;
	c.z = f / a.z;
	c.w = f / a.w;

	return c;
}

inline float Vector3Dotf(const Vector4CPU &a, const Vector4CPU &b)
{
	float result = a.x * b.x + a.y * b.y + a.z * b.z;
	return result;
}

//inline float Vector4Dotf(const Vector4CPU &a, const Vector4CPU &b)
//{
//	float result = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
//	return result;
//}

inline Vector4CPU Vector3Dot(const Vector4CPU &a, const Vector4CPU &b)
{
	Vector4CPU c = Vector3Dotf(a, b);
	return c;
}

//inline Vector4CPU Vector4Dot(const Vector4CPU &a, const Vector4CPU &b)
//{
//	Vector4CPU c = Vector4Dotf(a,b);
//	return c;
//}

inline Vector4CPU Vector3CrossProduct(const Vector4CPU &a, const Vector4CPU &b)
{
	Vector4CPU c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	c.w = 0.0f;

	return c;
}

//(axb).c
inline float Vector3CrossAndDotProduct(const Vector4CPU &a, const Vector4CPU &b, const Vector4CPU &c)
{
	Vector4CPU d;

	d.x = a.y * b.z - a.z * b.y;
	d.y = a.z * b.x - a.x * b.z;
	d.z = a.x * b.y - a.y * b.x;
	d.w = 0.0f;

	return Vector3Dotf(d,c);
}

inline Vector4CPU VectorLerp(const Vector4CPU &a, const Vector4CPU &b, float t)
{
	Vector4CPU c = a + (b - a) * t;
	return c;
}

inline Vector4CPU VectorGetMax(const Vector4CPU &a, const Vector4CPU &b)
{
	Vector4CPU c;

	c.x = a.x > b.x ? a.x : b.x;
	c.y = a.y > b.y ? a.y : b.y;
	c.z = a.z > b.z ? a.z : b.z;
	c.w = a.w > b.w ? a.w : b.w;

	return c;
}

inline Vector4CPU VectorGetMin(const Vector4CPU &a, const Vector4CPU &b)
{
	Vector4CPU c;

	c.x = a.x < b.x ? a.x : b.x;
	c.y = a.y < b.y ? a.y : b.y;
	c.z = a.z < b.z ? a.z : b.z;
	c.w = a.w < b.w ? a.w : b.w;

	return c;
}

inline Vector4CPU VectorReciprocal(const Vector4CPU &a)
{
	Vector4CPU result = a;
	result.Reciprocal();
	return result;
}

inline Vector4CPU VectorSqrt(const Vector4CPU &a)
{
	Vector4CPU result = a;
	result.Sqrt();
	return result;
}
//
//inline Vector4CPU VectorReciprocalSqrt(Vector4CPU &a)
//{
//	Vector4CPU result = a;
//	result.ReciprocalSqrt();
//	return result;
//}

inline Vector4CPU VectorNormalize(const Vector4CPU &a)
{
	Vector4CPU result = a;
	result.Normalize();
	return result;
}

inline float VectorNormalizeAndGetLength(const Vector4CPU &a, Vector4CPU &result)
{
	result = a;
	float vectorlength = result.NormalizeAndGetLength();
	return vectorlength;
}

inline Vector4CPU VectorAbs(const Vector4CPU &a)
{
	Vector4CPU result = a;
	result.Abs();
	return result;
}

inline Vector4CPU VectorInvertSign(const Vector4CPU &a)
{
	Vector4CPU result = a;
	result.InvertSign();

	return result;
}

inline Vector4CPU VectorSaturate(const Vector4CPU &a)
{
	Vector4CPU result = a;
	result.Saturate();
	return result;
}

inline Vector4CPU VectorQuaternionToRotation(const Vector4CPU &v)
{
	Vector4CPU result;

	float cosvalue = FastMath::ACos(v.w);
	float s = FastMath::ASin(cosvalue);

	if ( s==0.0f )
	{
		result.Set(1.0f, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		result = v / s;
		result.w = cosvalue * 2.0f;
	}

	return result;
}

//矢量绕Z轴旋转一个角度
inline Vector4CPU VectorRotationZ(const Vector4CPU &v,float degree)
{
	Vector4CPU result;

	float rad = degree*MATH_PI/180.0f;
	float sinvalue, cosvalue;
	FastMath::SinCos(rad, sinvalue, cosvalue);

	result.x = v.x * cosvalue - v.y*sinvalue;
	result.y = v.x * sinvalue + v.y*cosvalue;
	result.z = v.z;
	result.w = 1.0f;

	return result;
}

//矢量绕axis轴旋转一个角度
inline Vector4CPU VectorRotationV(const Vector4CPU &v,const Vector4CPU &axis,float degree)
{
	Vector4CPU result,ey,ex;

	//把axis作为局部z轴
	ey=Vector3CrossProduct(axis,v);
	ex=Vector3CrossProduct(ey,axis);

	ey.Normalize();
	ex.Normalize();

	float x1=Vector3Dotf(v,ex);

	float rad = degree*MATH_PI/180.0f;
	float sinvalue, cosvalue;
	FastMath::SinCos(rad, sinvalue, cosvalue);

	float x2 = x1 * cosvalue;
	float y2 = x1 * sinvalue;

	result=x2*ex+y2*ey;
	result.w = v.w;

	return result;
}

inline Vector4CPU VectorRotationToQuaternion(const Vector4CPU &v)
{
	Vector4CPU result;

	float radius_half = v.w * 0.5f;
	float sinvalue, cosvalue;
	FastMath::SinCos(radius_half, sinvalue, cosvalue);

	result.x = v.x * sinvalue;
	result.y = v.y * sinvalue;
	result.z = v.z * sinvalue;
	result.w = cosvalue;

	return result;
}

inline Vector4CPU PointToPlaneDistance(const Vector4CPU &point, const Vector4CPU &plane)
{
	return Vector3Dot(point, plane);
}

inline Vector4CPU MirrorPoint(const Vector4CPU &point, const Vector4CPU &plane)
{
	Vector4CPU mirrored_point;
	
	float d = PointToPlaneDistance(point, plane)[0];
	mirrored_point = point - (2.0f * d ) * plane;

	return mirrored_point;
}

// 计算vector对plane平面镜射后的3D方向
inline Vector4CPU MirrorVector(const Vector4CPU &vector, const Vector4CPU &plane)
{
	Vector4CPU mirrored_a, mirrored_b, mirrored_vector;
	Vector4CPU vZero = Vector4CPU::GetZero();

	float d = PointToPlaneDistance(vector, plane)[0];
	mirrored_a = vector - (2.0f * d ) * plane;

	d = ((Vector4CPU &)plane)[3];
	mirrored_b = vZero - (2.0f * d ) * plane;
	
	mirrored_vector = mirrored_a - mirrored_b;
	mirrored_vector[3] = 1.0f;

	return mirrored_vector;
}

//inline函数只能定义在头文件中

//计算2D局部坐标系中p1-p2和p2-p3线段的夹角[0-360)，角度定义在p1-p2-p3左手边，p1,p2,p3为二维坐标(不用z分量)，单位：度
//只使用XY坐标
inline float Angle2D( const Vector4CPU &p1, const Vector4CPU &p2, const Vector4CPU &p3) 
{
	Vector4CPU ez(0,0,-1.0f);
	
	Vector4CPU ex=p1-p2; 
	ex.z=0;  //强制为0
	ex.Normalize();

	Vector4CPU vr=p3-p2;
	vr.z=0;  //强制为0

	Vector4CPU ey=Vector3CrossProduct(ez,ex);

	Vector4CPU vr1;
	vr1.x=Vector3Dotf(vr,ex);
	vr1.y=Vector3Dotf(vr,ey);

	float ang=atan2(vr1.y,vr1.x)*180.0f/MATH_PI;
	if(ang<0) ang+=360.0f;
	return ang;
}

//计算3D局部坐标系中p1-p2和p2-p3线段的夹角[0-180]，p1,p2,p3为三维坐标，单位：度
inline float Angle3D( const Vector4CPU &p1, const Vector4CPU &p2, const Vector4CPU &p3) 
{
	Vector4CPU v1=p1-p2; v1.Normalize();
	Vector4CPU v2=p3-p2; v2.Normalize();

	float ff=Vector3Dotf(v1,v2);
	if(ff>=1.0f) return 0.0f;
	if(ff<=-1.0f) return 180.0f;

	return acos(ff)*180.0f/MATH_PI;
}

//判断两个矢量是否共线，包括方向相同或相反,err_degree角度容限(度)
inline BOOL IsCollinear(const Vector4CPU &v1, const Vector4CPU &v2,int err_degree=5)
{
	float d1=v1.Length();
	float d2=v2.Length();
	float dd=d1*d2;
	if(dd==0) return TRUE; //矢量为0也算共线

	float ff=Vector3Dotf(v1,v2)/dd;

	return (abs(ff)>=cos(err_degree*MATH_PI/180.0f));
}

#endif // _VECTOR4_GENERAL_