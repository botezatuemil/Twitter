#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma once
#include <fstream>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <mutex>
#include <fstream>

class Logger
{
	
public:

	enum class Level
	{
		eInfo,
		eError,
		eLogin,
		eLogout,
		eRegister
	};

public:	
	template<class ... Args>
	static void Log(Level level, Args&& ... params)
	{
		std::ofstream out;
		out.open("../Server/Logger.txt", std::ofstream::app);
		//std::lock_guard<std::mutex> lockCout(mutexCout);
		switch (level)
		{
		case Level::eInfo:
			std::cout << "[Info]";
			out << "[Info]";
			break;

		case Level::eError:
			std::cout << "[Error]";
			out << "[Error]";
			break;

		case Level::eLogin:
			std::cout << "[Login]";
			out << "[Login]";
			break;

		case Level::eLogout:
			std::cout << "[Logout]";
			out << "[Logout]";
			break;





		case Level::eRegister:
			std::cout << "[Register]";
			out << "[Register]";
			break;
		}
		std::time_t crtTime = std::time(nullptr);
		std::cout << '[' << std::put_time(std::localtime(&crtTime), "%Y-%m-%d %H:%M:%S") << ']';
		out << '[' << std::put_time(std::localtime(&crtTime), "%Y-%m-%d %H:%M:%S") << ']';
		((std::cout << ' ' << std::forward<Args>(params)), ...);
		((out << ' ' << std::forward<Args>(params)), ...);
		std::cout << '\n';
		out << '\n';
	}

private:
	//static std::mutex mutexCout;
};

template<class ... Args>
void log(Args&& ... params)
{
	Logger::Log(Logger::Level::Info, std::forward<Args>(params)...);
}
