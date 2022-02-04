#pragma once
#include"User.h"
#include"UserBD.h"
class WriteInFile
{
public:
	static void WriteInFileLogin(User *user);
	static bool IsEmpty(std::ifstream& pFile);
};

