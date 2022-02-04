#include "LikeDB.h"

void LikeDB::InsertDataLike(const char* path, int id_user, int id_post)
{
	sqlite3* DB;
	char* errorMessage;

	int exit = sqlite3_open(path, &DB);

	std::string sql("PRAGMA foreign_keys = ON; INSERT INTO LIKE (id_user, id_post) VALUES(" + std::to_string(id_user) + "," + std::to_string(id_post) + "); ");


	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

	if (exit != SQLITE_OK) {
		std::cerr << "Error to insert in Like Table" << "\n";
		sqlite3_free(errorMessage);
	}
	else {
		std::cout << "Data for Like inserted succesfully" << "\n";
	}
}

void LikeDB::SelectDataLike(const char* path)
{
	sqlite3* DB;

	int exit = sqlite3_open(path, &DB);

	std::string sql = "SELECT * FROM LIKE;";

	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}

std::vector<std::vector<std::string>> LikeDB::SelectDataLikeOfUser(const char* path, int id_user)
{
	std::vector<std::vector<std::string>> resultData;

	for (int i = 0; i < 3; i++)
		resultData.push_back(std::vector< std::string >());

	sqlite3* DB;

	int exit = sqlite3_open(path, &DB);
	struct sqlite3_stmt* selectstmt;

	if (sqlite3_open(path, &DB) == SQLITE_OK) {
		std::string sql = "SELECT * FROM LIKE WHERE id_user=" + std::to_string(id_user) + ";";

		const char* c = sql.c_str();
		sqlite3_prepare(DB, c, -1, &selectstmt, NULL);
		sqlite3_step(selectstmt);

		while (sqlite3_column_text(selectstmt, 0))
		{
			for (int i = 0; i < 3; i++)
				resultData[i].push_back(std::string((char*)sqlite3_column_text(selectstmt, i)));
			sqlite3_step(selectstmt);
		}
	}

	return resultData;
}

std::vector<std::vector<std::string>> LikeDB::SelectDataLikeOfPost(const char* path, int id_post)
{
	std::vector<std::vector<std::string>> resultData;

	for (int i = 0; i < 3; i++)
		resultData.push_back(std::vector< std::string >());

	sqlite3* DB;

	int exit = sqlite3_open(path, &DB);
	struct sqlite3_stmt* selectstmt;

	if (sqlite3_open(path, &DB) == SQLITE_OK) {
		std::string sql = "SELECT * FROM LIKE WHERE id_post=" + std::to_string(id_post) + ";";

		const char* c = sql.c_str();
		sqlite3_prepare(DB, c, -1, &selectstmt, NULL);
		sqlite3_step(selectstmt);

		while (sqlite3_column_text(selectstmt, 0))
		{
			for (int i = 0; i < 3; i++)
				resultData[i].push_back(std::string((char*)sqlite3_column_text(selectstmt, i)));
			sqlite3_step(selectstmt);
		}
	}

	return resultData;
}

void LikeDB::DeletePostLike(const char* path, int id_user, int id_post)
{
	sqlite3* DB;
	char* errorMessage;
	int exit = sqlite3_open(path, &DB);

	std::string sql = "DELETE FROM LIKE WHERE id_user= " + std::to_string(id_user) + " AND id_post=" + std::to_string(id_post) + ";";;

	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, &errorMessage);
	if (exit != SQLITE_OK) {
		std::cerr << "Error to delete" << "\n";
		sqlite3_free(errorMessage);
	}
	else {
		std::cout << "RepostDislike deleted" << "\n";
	}
}

bool LikeDB::UserLikePost(const char* s, int id_user, int id_post)
{
	std::vector<std::vector<std::string>> resultData;

	for (int i = 0; i < 3; i++)
		resultData.push_back(std::vector< std::string >());

	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);
	struct sqlite3_stmt* selectstmt;

	if (sqlite3_open(s, &DB) == SQLITE_OK) {
		std::string sql = "SELECT * FROM LIKE WHERE id_user= " + std::to_string(id_user) + " AND id_post=" + std::to_string(id_post) + ";";

		const char* c = sql.c_str();
		sqlite3_prepare(DB, c, -1, &selectstmt, NULL);
		sqlite3_step(selectstmt);

		while (sqlite3_column_text(selectstmt, 0))
		{
			for (int i = 0; i < 3; i++)
				resultData[i].push_back(std::string((char*)sqlite3_column_text(selectstmt, i)));
			sqlite3_step(selectstmt);
		}
	}

	if (resultData[0].size() > 0)
	{
		resultData.clear();
		return true;
	}
	else
	{
		resultData.clear();
		return false;
	}
}

uint64_t LikeDB::NumberOfLikes(const char* path, int id_post)
{
	std::vector<std::vector<std::string>> resultData = SelectDataLikeOfPost(path,id_post);
	return resultData[0].size();
}


int LikeDB::callback(int argc, char** argv, char** azColName)
{
	for (int index = 0; index < argc; ++index) {
		std::cout << azColName[index] << ": " << argv[index] << "\n";
	}

	std::cout << "\n";

	return 0;
}
