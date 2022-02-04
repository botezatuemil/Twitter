#pragma once
#include <string>
#include <iostream>
#include <sqlite3.h>
#include <vector>
class LikeDB
{
public:
	static void InsertDataLike(const char* path, int id_user, int id_post);
	static void SelectDataLike(const char* path);
	static std::vector < std::vector<std::string>> SelectDataLikeOfUser(const char* path, int id_user);
	static std::vector < std::vector<std::string>> SelectDataLikeOfPost(const char* path, int id_post);
	static void DeletePostLike(const char* path, int id_user, int id_post);

	static bool UserLikePost(const char* s, int id_user, int id_post);
	static uint64_t NumberOfLikes(const char* path, int id_post);
	static int callback(int argc, char** argv, char** azColName);

	static int c_callback(void* NotUsed, int argc, char** argv, char** azColName) {
		LikeDB* database = reinterpret_cast<LikeDB*>(NotUsed);
		return database->callback(argc, argv, azColName);
	}
};

