#pragma once
#include "ASCFile.h"

//���ɷǸ���ģ��
class _SSG_DLLIMPEXP CNonISOModel
{
public:
	CNonISOModel(void);
	CNonISOModel(CNonISOModel &data)
	{
		*this=data;
	}
	~CNonISOModel(){}
	CNonISOModel& operator=(const CNonISOModel& data);

	//�Ǹ���ģ��
	BOOL m_bBaseStory; //�ײ����
	BOOL m_bOtherStory; //�м�����
	int m_iBndType1; //�ײ�Լ������
	int m_iBndPos1; //�ײ�Լ��λ��
	int m_iBndType2; //�м��Լ������
	int m_iBndPos2; //�м��Լ��λ��
	float m_fSpringStiff1[6];//�ײ��նȵ��ɸն� 
	float m_fSpringStiff2[6];//�м���նȵ��ɸն�
	
	void Read(CASCFile &fin);
	void Write(CFile &fout);
};
