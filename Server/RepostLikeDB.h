#pragma once
#include <string>
#include <iostream>
#include <sqlite3.h>
#include <vector>
class RepostLikeDB
{
public:
	static void InsertDataRepostLike(const char* path, int id_user, int id_repost);
	static void SelectDataRepostLike(const char* path);

	static std::vector < std::vector<std::string> > SelectDataRepostLikeOfUser(const char* s, int id_user);
	static  std::vector < std::vector<std::string> > SelectDataRepostLikeOfPost(const char* s, int id_post);
	static void DeleteRepostLike(const char* path, int id_user, int id_repost);

	static uint64_t NumberOfLikes(const char* path, int id_repost);
	static bool UserLIkeRepost(const char* path, int id_user, int id_repost);

	static int callback(int argc, char** argv, char** azColName);

	static int c_callback(void* NotUsed, int argc, char** argv, char** azColName) {
		RepostLikeDB* database = reinterpret_cast<RepostLikeDB*>(NotUsed);
		return database->callback(argc, argv, azColName);
	}
};

