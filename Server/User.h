#pragma once
#include<string>
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <stdio.h>
class User
{ 
public:
	User(const std::string& username, const std::string& password);

	const std::string& GetUsername() const;  
	const std::string& GetPassword() const;

	void SetUsername(const std::string& username);
	void SetPassword(const std::string& password);

	const std::string& GetUsername();
	const std::string& GetPassword();

private:
	std::string m_username;
	std::string m_password;
};

