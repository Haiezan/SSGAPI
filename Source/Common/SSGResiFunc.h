#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "ResiHeadDef.h"
#include "HeadDefine.h"
#include "SSGData.h"
//#include "BeamData.h"

namespace ssgResi
{
	_RESI_FUN void IntialAllResiData();
	_RESI_FUN BOOL IsResOn();
	_RESI_FUN BOOL IsLoadOn();
	_RESI_FUN BOOL IsExtendLoadOn();
	_RESI_FUN BOOL IsFileOn();
	_RESI_FUN void Save();
	_RESI_FUN void Clear();
	_RESI_FUN BOOL GetModifiedStatus();

	_RESI_FUN void InitialResiData();
	_RESI_FUN void ReInitialResiData();
	_RESI_FUN void SelLoadCase();
	
	_RESI_FUN void SetProjectInfo(); //设置项目信息
	_RESI_FUN void SetPrjData(); //设置建筑信息
	_RESI_FUN void ViewStrucData(); //查看构件信息
	_RESI_FUN void ViewNonStrucNumData(); //非结构构件数量评估参数
	_RESI_FUN void ViewNonStrucData(); //查看非结构构件信息
	_RESI_FUN void ViewStrucType(); //查看构件类别
	_RESI_FUN void SetResiCost(); //设置材料造价信息
	_RESI_FUN void ViewResiCost(); //查看造价统计结果
	_RESI_FUN void SetNonStrucCost(); //设置非结构构件造价信息

	_RESI_FUN void SetStrucLossCoe(); //设置构件损失系数
	_RESI_FUN void SetStrucRepairCoe(); //设置构件修复系数
	_RESI_FUN void SetEngReducCoe(); //设置修复费用工程量折减系数
	_RESI_FUN void SetStoryRepairFactor(); //设置结构修复费用楼层影响系数
	_RESI_FUN void SetStrucRepairTime(); //设置结构构件修复工时
	_RESI_FUN void SetTimeReduceCoe(); //设置结构构件修复时间工程量折减系数
	_RESI_FUN void SetStoryTimeFactor(); //设置结构构件修复时间楼层影响系数
	_RESI_FUN void SetStoryPerformStd(); //设置楼层破坏等级判定标准
	_RESI_FUN void SetStoryHarmStd(); //设置楼层名义伤亡率标准
	_RESI_FUN void SetStoryPersonDensity(); //设置修改楼层人员密度
	_RESI_FUN void SetLevelPar(); //设置评价指标等级

	_RESI_FUN void SetNonStrucLossCoe(); //设置非结构构件损失系数
	_RESI_FUN void SetNonStrucRepairCoe(); //设置非结构构件修复系数
	_RESI_FUN void SetNSEngReducCoe(); //设置非结构构件修复费用工程量折减系数
	_RESI_FUN void SetNSStoryRepairFactor(); //设置非结构构件修复费用楼层影响系数
	_RESI_FUN void SetNonStrucRepairTime(); //设置非结构构件修复工时
	_RESI_FUN void SetNSTimeReducCoe(); //设置非结构构件修复工时工程量折减系数
	_RESI_FUN void SetNSStoryTimeFactor(); //设置非结构构件修复时间楼层影响系数
	_RESI_FUN void SetNSEDP(); //设置非结构构件工程需求参数

	_RESI_FUN void RunCalcLoad(); //计算分析工况结果
	_RESI_FUN void RunCalcExtendLoad(); //计算扩充工况结果
	_RESI_FUN void RunMontecarloMethod(); //进行蒙特卡洛计算
	_RESI_FUN void RunPartialMontecarloMethod(); //进行分部蒙特卡洛计算

	_RESI_FUN void ViewMatrixEdp(); //查看工程需求参数矩阵
	_RESI_FUN void ViewMatrixEdpExtend(); //查看工程需求参数扩充矩阵

	_RESI_FUN void ViewStrucResult(); //查看构件韧性评价计算结果
	_RESI_FUN void ViewNonStrucResult(); //查看非结构构件韧性评价结果
	_RESI_FUN void ViewStrucResultExtend(); //查看扩充工况构件韧性评价计算结果
	_RESI_FUN void ViewNonStrucResultExtend(); //查看扩充工况非结构构件韧性评价结果
	_RESI_FUN void ViewStroyResult(); //查看楼层韧性评价计算结果
	_RESI_FUN void ViewStroyResultExtend(); //查看扩充工况楼层韧性评价计算结果
	_RESI_FUN void ViewEPLoadResult(); //分析工况韧性评价
	_RESI_FUN void ViewExtendLoadResult(); //扩充工况韧性评价结果
	_RESI_FUN void ViewNormalResult(); //查看正态分布拟合结果

	_RESI_FUN void OutputResiReport(); //输出韧性评价报告
	_RESI_FUN void OutputResiReportSimple(); //输出简易评价报告
}