#pragma once
#include "HeadDefine.h"

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

