#pragma once
#include <stdio.h>
#include <iostream>
#include<string>
#include <sqlite3.h>
#include <vector>
class DislikeDB
{
public:

	static void InsertDataDislike(const char* s, int id_user, int id_post);

	static void SelectDataDislike(const char* s);
	static std::vector < std::vector<std::string> > SelectDataDislikeOfUser(const char* s, int id_user);
	static  std::vector < std::vector<std::string> > SelectDataDislikeOfPost(const char* s, int id_post);
	static bool UserDislikePost(const char* s, int id_user,int id_post);
	static void DeletePostDislike(const char* path, int id_user, int id_post);
	//EXTRACT DATA//
	//argc: holds the number of results, argv: holds each value in array, azColName: holds each column
	static int callback(int argc, char** argv, char** azColName);
	static uint64_t NumberOfDislike(const char* path, int id_post);
	//cast callback
	static int c_callback(void* NotUsed, int argc, char** argv, char** azColName) {
		DislikeDB* database = reinterpret_cast<DislikeDB*>(NotUsed);
		return database->callback(argc, argv, azColName);
	}
};
