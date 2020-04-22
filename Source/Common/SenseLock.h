#pragma once
#include <string>

//返回值 0 -- 硬件锁  1 -- 局域网网络硬锁（也可能是以前login的软锁） 2 -- 软锁 其他 -- 错误代码
int login_ssg(int license_id, std::string& user_name, std::string password="");
bool check_ssg_module(int module_id);

void logout_ssg();
int isalive_ssg();				//保持占用锁 主函数

//void logout_cloud(std::string username);

std::wstring getErrorMsg(int status);