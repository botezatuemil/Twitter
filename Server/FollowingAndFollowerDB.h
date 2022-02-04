#pragma once
#include <string>
#include <iostream>
#include <sqlite3.h>
#include <vector>
class FollowingAndFollowerDB
{
public:
	static void InsertDataFolowerAndFollowing(const char* path, int id_userFollower, int id_userFollowing);
	static void SelectDataFollowingAndFollower(const char* path);
	static void DeleteFollowing(const char* path, int id_userFollower, int id_userFollowing);

	static std::vector<std::vector<std::string>> SelectDataFollowingAndFollowerOfFollowing(const char*path, int id_userFollowing);
	static std::vector<std::vector<std::string>> SelectDataFollowingAndFollowerOfFollower(const char*path, int id_userFollower);
	static bool SelectDataFollowingAndFollower(const char*path, int id_userFollower, int id_userFollowing) ;
	static std::vector<std::string> SelectDataFollowingAndFollowerTable(const char* path, uint64_t id_user);

	static uint64_t NumberOfFollowers(const char* path,uint64_t id_user);
	static uint64_t NumberOfFollowing(const char* path, uint64_t id_user);
	static int callback(int argc, char** argv, char** azColName);

	static int c_callback(void* NotUsed, int argc, char** argv, char** azColName) {
		FollowingAndFollowerDB* database = reinterpret_cast<FollowingAndFollowerDB*>(NotUsed);
		return database->callback(argc, argv, azColName);
	}

	
};

