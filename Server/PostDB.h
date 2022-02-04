#pragma once
#include<string>
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include"../CommonClasses/Post.h"
#include"../CommonClasses/Repost.h"
#include"../CommonClasses/PostPersonalProfile.h"
#include<unordered_map>

class PostDB
{
	
public:
	static void InsertDataPost(const char* s, const std::string& postare, const std::string& timeOfPost, int id_user);
	static void SelectDataPost(const char* path);
	static std::vector<std::vector<std::string>> SelectDataOfUser(const char* path, int id_user);
	static std::vector<std::vector<std::string>> SelectDataOfUserSearch(const char* path);

	static void DeleteDataPost(const char* s, int id_post);
	static int callback(int argc, char** argv, char** azColName);
	static std::vector<std::shared_ptr<PostPersonalProfile>> CreatePersonalPostObject(const char* path, int id_user);

	static std::vector<std::shared_ptr<Post>> CreateVectorSearch(const char* path);
	static Post ReturnPost(const char* path, int id_post);

	static std::unordered_multimap<std::string, std::shared_ptr<Post>> GetIndexTable();
	static void SetIndexTable(const std::unordered_multimap<std::string, std::shared_ptr<Post>>& indexTable);

	//cast callback
	static int c_callback(void* NotUsed, int argc, char** argv, char** azColName) {
		PostDB* database = reinterpret_cast<PostDB*>(NotUsed);
		return database->callback(argc, argv, azColName);
	}
};

