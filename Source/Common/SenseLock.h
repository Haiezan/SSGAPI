#pragma once
#include <string>

//����ֵ 0 -- Ӳ����  1 -- ����������Ӳ����Ҳ��������ǰlogin�������� 2 -- ���� ���� -- �������
//status1 - �������������
//status2 - ����������Ӳ���������
//status3 - �����������

int login_ssg(int license_id, int &status1, int& status2, int& status3, std::string& user_name, std::string password="");
bool check_ssg_module(int module_id);

void logout_ssg();
int isalive_ssg();				//����ռ���� ������

//void logout_cloud(std::string username);

std::wstring getErrorMsg(int status);

//ʹ������
//USES_CONVERSION;
//
//std::string user=W2A(m_UserName);
//std::string pwd = W2A(m_Pwd);
//
//int status1 = 0;
//int status2 = 0;
//int status3 = 0;
//
//int check=login_ssg(m_LicenseId, status1, status2, status3, user, pwd);
//
//
//CString strUser=A2W(user.c_str());
//CString strTxt;
//
//// TODO: Add your control notification handler code here
//if(check == 0) {
//	strTxt = L"Ӳ��. User= " + strUser;
//} else if(check == 2)
//	strTxt = L"����. User= " + strUser;
//else if(check == 1) {
//	strTxt = L"����Ӳ��. User = " + strUser;
//}
//else {
//	CString str1 = L"����Ӳ��״̬��"; str1 += getErrorMsg(status1).c_str(); str1 += L"\n";
//	CString str2 = L"������Ӳ��״̬��"; str2 += getErrorMsg(status2).c_str();  str2 += L"\n";
//	CString str3 = L"����״̬��"; str3 += getErrorMsg(status3).c_str();  str3 += L"\n";
//	strTxt = str1 + str2 + str3;
//}
//
//AfxMessageBox(strTxt);
