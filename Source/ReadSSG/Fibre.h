#pragma once
struct XYFibre
{
	float fX;
	float fY;
	float fA;
	char cMat;//材料
};

struct PM
{
	float fR;
	float fTheata;
	float fP;
	float fM;
};
struct PMM
{
	float fAngle; //加载角度
	float fR; //中性轴位置
	float fTheata; //截面转角
	float fP; //轴力
	float fMx; //x轴弯矩
	float fMy; //y轴弯矩
};