#pragma once
#include <string>

//����ֵ 0 -- Ӳ����  1 -- ����������Ӳ����Ҳ��������ǰlogin�������� 2 -- ���� ���� -- �������
int login_ssg(int license_id, std::string& user_name, std::string password="");
bool check_ssg_module(int module_id);

void logout_ssg();
int isalive_ssg();				//����ռ���� ������

//void logout_cloud(std::string username);

std::wstring getErrorMsg(int status);