#pragma once
#include "HeadDefine.h"

//点和墙的索引关系，用于处理连梁
class _SSG_DLLIMPEXP CPointWallIndex
{
public:
	CPointWallIndex(void) {nWalls=0;}

	int nWalls;  //周围的墙数，不包括墙梁(即悬空墙)
	//int idPoint[Sys_Max_Connect_Wall];  //墙体中除该点外最近端点的IDM，-1表示无效
	int idWall[Sys_Max_Connect_Wall];  //墙体IDM
	float fAng[Sys_Max_Connect_Wall];    //此点与idPoint构成的射线与X轴夹角，弧度，0-2*PI

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

