#pragma once
#include <stdio.h>
#include <iostream>
#include<string>
#include <sqlite3.h>
#include <vector>
class RepostDislikeDB
{
public:
	static	void InsertDataRepostDislike(const char* path, int id_user, int id_repost);
	static	void SelectDataRepostDislike(const char* path);
	static std::vector < std::vector<std::string> > SelectDataRepostDislikeOfUser(const char* s, int id_user);
	static  std::vector < std::vector<std::string> > SelectDataRepostDislikeOfPost(const char* s, int id_post);
	static void DeleteRepostDislike(const char* path, int id_user, int id_repost);


	static bool UserDislikeRepost(const char* path, int id_user, int id_repost);

	static int callback(int argc, char** argv, char** azColName);
	static uint64_t NumberOfDislike(const char* path,uint64_t id_repost);
	static int c_callback(void* NotUsed, int argc, char** argv, char** azColName) {
		RepostDislikeDB* database = reinterpret_cast<RepostDislikeDB*>(NotUsed);
		return database->callback(argc, argv, azColName);
	}
};

