#pragma once
#ifndef _VECTOR4_
#define _VECTOR4_
#include "HeadDefine.h"
#define _GENERAL_CPU_

// GENERAL CPU Version, reference code.
#include "Vector4_Reference.h"
// Intel SSE instruction Version
//#include "Vector4_SSE.h"
//#include<xmmintrin.h>

#ifdef _GENERAL_CPU_
typedef Vector4CPU Vector4;
#else
typedef Vector4SSE Vector4;
#endif

#endif // _VECTOR4_

//���������η��߷�������w,p0,p1,p2Ϊ���������飬ÿ����4*4�ֽ�(x,y,z,reserved)����,n--����
/*
void vcross( float* w, const float* p0, const float* p1, const float* p2, int n )
{
	__asm
	{
		MOV    edi, w
			MOV    esi, p0
			MOV    eax, p1   
			MOV    edx, p2
			MOV    ecx, n
__loop:
		MOVAPS xmm0,XMMWORD [esi]
		MOVAPS xmm1,XMMWORD [eax]
		SUBPS  xmm0,xmm1
			SHUFPS xmm0,xmm0,11001001b
			MOVAPS xmm2,XMMWORD [edx]
		SUBPS  xmm1,xmm2
			SHUFPS xmm1,xmm1,11010010b
			MULPS  xmm0,xmm1
			MOVAPS xmm1,XMMWORD [esi]
		SHUFPS xmm1,xmm1,11010010b
			MOVAPS xmm2,XMMWORD [edx]
		SHUFPS xmm2,xmm2,11001001b
			MULPS  xmm1,xmm2
			SUBPS  xmm0,xmm1
			MOVAPS XMMWORD [edi],xmm0

			ADD    edi, 16
			ADD    esi, 16
			ADD    eax, 16
			ADD    edx, 16
			DEC    ecx
			JNZ  __loop
	}
}
*/

//������dp=v0 * v1, v0,v1Ϊ������ÿ����4*4�ֽ�(x,y,z,reserved)���룬n--����
/*
void vdp( float* dp, const float* v0, const float* v1, int n )
{
	__asm{
		MOV    eax,DWORD PTR [ dp ]
		MOV    esi,DWORD PTR [ v0 ]
		MOV    edi,DWORD PTR [ v1 ]
		MOV    ecx,n

__loop:
		MOVAPS xmm1,XMMWORD PTR [ esi ]
		MOVAPS xmm2,XMMWORD PTR [ edi ]
		XORPS  xmm0,xmm0
			MULPS  xmm1,xmm2
			ADDPS  xmm0,xmm1
			HADDPS xmm0,xmm0
			HADDPS xmm0,xmm0
			MOVSS  DWORD PTR [ eax ],xmm0
			ADD    esi,16
			ADD    edi,16
			DEC    ecx
			JNZ    __loop
	}
}
*/