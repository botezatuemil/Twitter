#pragma once
#include <string>
#include <iostream>
#include <sqlite3.h>
#include <vector>
#include"../CommonClasses/Repost.h"
class RepostDB
{
public:
	static void InsertDataRepost(const char* path, const std::string& repost, const std::string& timeOfRepost, int id_user, int id_post);
	static void SelectDataRepost(const char* path);
	static std::vector<std::vector<std::string>> SelectDataRepostOfPost(const char* path, int id_post);
	static std::vector<std::vector<std::string>> SelectDataRepostOfUser(const char* path, int id_user);

	static std::vector<std::vector<std::string>> SelectDataRepostForSearch(const char* path);
	static std::vector<std::shared_ptr<Repost>>ReturnVectorRepostSearch(const char* path);

	static void DeleteDataRepost(const char* path, int id_repost);
	static int callback(int argc, char** argv, char** azColName);

	static int c_callback(void* NotUsed, int argc, char** argv, char** azColName) {
		RepostDB* database = reinterpret_cast<RepostDB*>(NotUsed);
		return database->callback(argc, argv, azColName);
	}
};

