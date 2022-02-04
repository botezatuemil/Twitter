#pragma once
#include<string>
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <iostream>
#include<string>
#include <sqlite3.h>
#include <string>
#include <stdio.h>
#include <vector>
class CommentDB
{
public:
	//The way to store dates in SQLite is:yyyy - mm - dd hh : mm:ss.xxxxxx
	static void InsertComment(const char* s, const std::string& comment, const std::string& timeOfComment, int id_user, int id_post);
	//should identify comment by id
	void UpdateComment(const char* s, int id_comment, const std::string& newComment);
	static void SelectComment(const char* s);
	static void ExistComment(const char* s, const std::string& username);
	static void DeleteCommment(const char* s, int id_comment);
	static std::vector<std::vector<std::string>> selectCommentOfUser(const char* s, int id_post);
	//EXTRACT DATA//
	//argc: holds the number of results, argv: holds each value in array, azColName: holds each column
	static int callback(int argc, char** argv, char** azColName);

	//cast callback
	static int c_callback(void* NotUsed, int argc, char** argv, char** azColName) {
		CommentDB* database = reinterpret_cast<CommentDB*>(NotUsed);
		return database->callback(argc, argv, azColName);
	}
};