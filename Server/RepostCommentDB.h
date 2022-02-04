#pragma once
#include <sqlite3.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>

class RepostCommentDB
{
public:
	static void InsertDataRepostComment(const char* path, const std::string& repostComment, const std::string& timeOfRepostComment, int id_user, int id_repost);
	static void SelectDataRepostComment(const char* path);

	static std::vector<std::vector<std::string>> SelectDataRepostCommentOfUser(const char* s, int id_user);
	static std::vector<std::vector<std::string>> SelectDataRepostCommentOfRepost(const char* s, int id_repost); 
	

	static void DeleteDataRepostComment(const char* path, int id_comment);
	static int callback(int argc, char** argv, char** azColName);

	static int c_callback(void* NotUsed, int argc, char** argv, char** azColName) {
		RepostCommentDB* database = reinterpret_cast<RepostCommentDB*>(NotUsed);
		return database->callback(argc, argv, azColName);
	}
};