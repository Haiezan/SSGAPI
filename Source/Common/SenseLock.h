#pragma once
#include <string>

//返回值 0 -- 硬件锁  1 -- 局域网网络硬锁（也可能是以前login的软锁） 2 -- 软锁 其他 -- 错误代码
//status1 - 本地锁错误代码
//status2 - 局域网网络硬锁错误代码
//status3 - 阮锁错误代码

int login_ssg(int license_id, int &status1, int& status2, int& status3, std::string& user_name, std::string password="");
bool check_ssg_module(int module_id);

void logout_ssg();
int isalive_ssg();				//保持占用锁 主函数

//void logout_cloud(std::string username);

std::wstring getErrorMsg(int status);

//使用例子
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
//	strTxt = L"硬锁. User= " + strUser;
//} else if(check == 2)
//	strTxt = L"软锁. User= " + strUser;
//else if(check == 1) {
//	strTxt = L"网络硬锁. User = " + strUser;
//}
//else {
//	CString str1 = L"本地硬锁状态："; str1 += getErrorMsg(status1).c_str(); str1 += L"\n";
//	CString str2 = L"局域网硬锁状态："; str2 += getErrorMsg(status2).c_str();  str2 += L"\n";
//	CString str3 = L"软锁状态："; str3 += getErrorMsg(status3).c_str();  str3 += L"\n";
//	strTxt = str1 + str2 + str3;
//}
//
//AfxMessageBox(strTxt);
