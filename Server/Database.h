#pragma once
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <stdio.h>

class Database
{
public:
	void CreateDB(const char* s); //creates Twitter database

	//CREATE TABLE//
	void CreateUserTable(const char* s); //Creates table for user
	void CreatePostTable(const char* s); //Creates table for posts
	void CreateCommentTable(const char* s); //Creates table for comment
	void CreateDislikeTable(const char* s);//Creates table for dislikes
	void CreateLikeTable(const char* s);//Creates table for likes
	void CreateRepostTable(const char* s);//Creates table for repost 
	void CreateRepostCommentTable(const char* s);//Creates table for repost comment
	void CreateRepostLikeTable(const char* s);//Create table for repost like
	void CreateRepostDislikeTable(const char* s);//Crea table for repost dislike
	void CreateFollowersAndFollowingTable(char const* s);//Create table for following and followers

	//EXTRACT DATA//
	//argc: holds the number of results, argv: holds each value in array, azColName: holds each column
	static int callback(int argc, char** argv, char** azColName);

	//cast callback
	static int c_callback(void* NotUsed, int argc, char** argv, char** azColName) {
		Database* database = reinterpret_cast<Database*>(NotUsed);
		return database->callback(argc, argv, azColName);
	}


	//DELETE TABLES //
	void DeleteUserTable(const char* s);
	void DeletePostTable(const char* s);
	void DeleteCommentTable(const char* s);
	void DeleteLikeTable(const char* s);
	void DeleteDislikeTable(const char* s);
	void DeleteFollowersAndFollowingTable(const char* s);
	void DeleteRepostTable(const char* s);
	void DeleteRepostCommentTable(const char* s);
	void DeleteRepostLikeTable(const char* s);
	void DeleteRepostDislikeTable(const char* s);

	//DELETE DATA //


};



