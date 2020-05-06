#include "stdafx.h"
#include "math.h"
#include "Interpolation.h"

CInterpolation::CInterpolation(const char* Xs, const char* Ys)
{
	Init(m_Xs, Xs);
	Init(m_Ys, Ys);
	m_Xmax = m_Xs[m_Xs.size() - 1];
}

CInterpolation::CInterpolation(const char* Xs, const char* Ys, const char* Zs)
{
	Init(m_Xs, Xs);
	Init(m_Ys, Ys);
	Init(m_Zs, Zs);
}

CInterpolation::CInterpolation(const INTERPOLATINGTYPE eType, const char* szFileName)
{
	if (eType == eInterpolationOneD)
		ReadOneD(szFileName);
	else//eType==eInterpolationTwoD
		ReadTwoD(szFileName);
}

CInterpolation::~CInterpolation()
{

}

//��ʼ��var
void CInterpolation::Init(vector<float>& var, const char* string)
{
	var.clear();
	CString strV(string);
	strV += ',';

	int nStart = 0;
	float fVar = 0.;
	int iPos = 0;
	while ((iPos = strV.Find(',', nStart)) > 0)
	{
		fVar = _ttof(strV.Mid(nStart, iPos - nStart));
		var.push_back(float(fVar));
		nStart = iPos + 1;
	}
}

//���ļ��ж�ȡx,y
BOOL  CInterpolation::ReadOneD(const char* szFileName)
{//����,��1��x,��2��y
	return TRUE;

err:
	return FALSE;
}

//���ļ��ж�ȡx,y,z
BOOL  CInterpolation::ReadTwoD(const char* szFileName)
{//��1��x,�ٶ�������19��,�ӵ�2�п�ʼ,��1��y,������z(x,y)
	return TRUE;

err:
	return FALSE;
}

//����xֵ��ֵ�õ�y
float CInterpolation::InterpolateOneD(float x)
{
	ASSERT(int(m_Xs.size()) > 0);
	ASSERT(m_Xs.size() == m_Ys.size());

	bool bAscending = true;//�����
	//�����һ��Ԫ�ش������һ��Ԫ��,����Ϊ�����ǽ����
	if (m_Xs.front() > m_Xs.back()) bAscending = false;

	if (bAscending)
	{
		if (x <= m_Xs.front()) return m_Ys.front();
		if (x >= m_Xs.back()) return m_Ys.back();

		for (int i = 0; i<int(m_Xs.size()) - 1; i++)
		{
			if (x <= m_Xs[i + 1])
			{
				if (fabs(m_Xs[i + 1] - m_Xs[i]) < 1e-5) return m_Ys[i];
				return m_Ys[i] + (x - m_Xs[i]) / (m_Xs[i + 1] - m_Xs[i])*(m_Ys[i + 1] - m_Ys[i]);
			}
		}
		return m_Ys.back();
	}
	else
	{
		if (x >= m_Xs.front()) return m_Ys.front();
		if (x <= m_Xs.back()) return m_Ys.back();

		for (int i = 0; i<int(m_Xs.size()) - 1; i++)
		{
			if (x >= m_Xs[i + 1])
			{
				if (fabs(m_Xs[i + 1] - m_Xs[i]) < 1e-5) return m_Ys[i];
				return m_Ys[i] + (x - m_Xs[i]) / (m_Xs[i + 1] - m_Xs[i])*(m_Ys[i + 1] - m_Ys[i]);
			}
		}
		return m_Ys.back();
	}
}

//����x,yֵ��ֵ�õ�z
float CInterpolation::InterpolateTwoD(float x, float y)
{
	ASSERT(int(m_Xs.size()) >= 2);
	ASSERT(int(m_Ys.size()) >= 2);
	ASSERT(m_Xs.size()*m_Ys.size() == m_Zs.size());

	bool bAscending = true;//�����
	//�����һ��Ԫ�ش������һ��Ԫ��,����Ϊ�����ǽ����
	if (m_Xs.front() > m_Xs.back()) bAscending = false;

	int ix = 0;
	if (bAscending)
	{
		if (x <= m_Xs.front()) { ix = 0; x = m_Xs.front(); }
		else if (x >= m_Xs.back()) { ix = m_Xs.size() - 2; x = m_Xs[m_Xs.size() - 1]; }
		else
		{
			for (int i = 0; i<int(m_Xs.size()) - 1; i++)
			{
				if (x <= m_Xs[i + 1]) { ix = i; break; }
			}
		}
	}
	else
	{
		if (x >= m_Xs.front()) { ix = 0; x = m_Xs.front(); }
		else if (x <= m_Xs.back()) { ix = m_Xs.size() - 2; x = m_Xs[m_Xs.size() - 1]; }
		else
		{
			for (int i = 0; i<int(m_Xs.size()) - 1; i++)
			{
				if (x >= m_Xs[i + 1]) { ix = i; break; }
			}
		}
	}

	bAscending = true;//�����
	//�����һ��Ԫ�ش������һ��Ԫ��,����Ϊ�����ǽ����
	if (m_Ys.front() > m_Ys.back()) bAscending = false;

	int iy = 0;
	if (bAscending)
	{
		if (y <= m_Ys.front()) { iy = 0; y = m_Ys.front(); }
		else if (y >= m_Ys.back()) { iy = m_Ys.size() - 2; y = m_Ys[m_Ys.size() - 1]; }
		else
		{
			for (int i = 0; i<int(m_Ys.size()) - 1; i++)
			{
				if (y <= m_Ys[i + 1]) { iy = i; break; }
			}
		}
	}
	else
	{
		if (y >= m_Ys.front()) { iy = 0; y = m_Ys.front(); }
		else if (y <= m_Ys.back()) { iy = m_Ys.size() - 2; y = m_Ys[m_Ys.size() - 1]; }
		else
		{
			for (int i = 0; i<int(m_Ys.size()) - 1; i++)
			{
				if (y >= m_Ys[i + 1]) { iy = i; break; }
			}
		}
	}

	//��x,y��ļ�Ȩ����
	float t = (x - m_Xs[ix]) / (m_Xs[ix + 1] - m_Xs[ix]);
	float u = (y - m_Ys[iy]) / (m_Ys[iy + 1] - m_Ys[iy]);

	//���ֵ������Ľǵ�
	int iXLen = m_Xs.size();
	float z0, z1, z2, z3;
	z0 = m_Zs[ix + iXLen * iy];
	z1 = m_Zs[ix + 1 + iXLen * iy];
	z2 = m_Zs[ix + 1 + iXLen * (iy + 1)];
	z3 = m_Zs[ix + iXLen * (iy + 1)];

	return (1 - t)*(1 - u)*z0 + t * (1 - u)*z1 + t * u*z2 + (1 - t)*u*z3;
}