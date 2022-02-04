
#include<string>
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
class DatabaseUtility
{

public:
	enum class Table {
		ePost,
		eRepost,
		eComment,
		eRepostComment,
		eLike,
		eDislike,
		eRepostDislike,
		eRepostLike,
		eUser,
		eFollowersAndFollowing

	};

	static void InsertData(const char* s, const std::string& sql, DatabaseUtility::Table table);
	static std::vector<std::vector<std::string>> SelectData(const char* s, const std::string& sql, DatabaseUtility::Table table);
	static void DeleteData(const char* s, const std::string& sql, DatabaseUtility::Table table);
	static int CountNumberOfColumns(const char* s, DatabaseUtility::Table table);
	static uint32_t  CountNumberOfRows(const char* path, const std::string& sql, DatabaseUtility::Table table);
	static int callback(int argc, char** argv, char** azColName);
	static std::string SelectOneDataType(const char* s, const std::string& sql, DatabaseUtility::Table table);
	static std::string FromTableToString(DatabaseUtility::Table table);

	static int c_callback(void* NotUsed, int argc, char** argv, char** azColName) {
		DatabaseUtility* database = reinterpret_cast<DatabaseUtility*>(NotUsed);
		return database->callback(argc, argv, azColName);
	}
};

