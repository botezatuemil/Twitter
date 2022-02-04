#include "User.h"
#include <vector>

const std::string& User::GetUsername() const
{
	return this->m_username;
}

const std::string& User::GetPassword() const
{
	return this->m_password;
}

void User::SetUsername(const std::string& username)
{
	this->m_username = username;
}

void User::SetPassword(const std::string& password)
{
	this->m_password = password;
}

const std::string& User::GetUsername()
{
	return  m_username;
}

const std::string& User::GetPassword()
{
	return m_password;
}

User::User(const std::string& username, const std::string& password):m_username(username),m_password(password)
{
}


