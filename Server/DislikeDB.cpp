#include "DislikeDB.h"

void DislikeDB::InsertDataDislike(const char* s, int id_user, int id_post)
{
	sqlite3* DB;
	char* errorMessage;

	int exit = sqlite3_open(s, &DB);

	//can't introduce int values into the table 
	std::string sql("PRAGMA foreign_keys = ON; INSERT INTO DISLIKE (id_user, id_post) VALUES(" + std::to_string(id_user) + "," + std::to_string(id_post) + ");");

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

	if (exit != SQLITE_OK) {
		std::cerr << "Error to insert in Dislike Table" << "\n";
		sqlite3_free(errorMessage);
	}
	else {
		std::cout << "Dislike inserted succesfully" << "\n";
	}
}

void DislikeDB::SelectDataDislike(const char* path)
{
	sqlite3* DB;

	int exit = sqlite3_open(path, &DB);

	std::string sql = "SELECT * FROM DISLIKE;";

	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}

std::vector<std::vector<std::string>> DislikeDB::SelectDataDislikeOfUser(const char* path, int id_user)
{
	std::vector<std::vector<std::string>> resultData;

	for (int i = 0; i < 3; i++)
		resultData.push_back(std::vector< std::string >());

	sqlite3* DB;

	int exit = sqlite3_open(path, &DB);
	struct sqlite3_stmt* selectstmt;

	if (sqlite3_open(path, &DB) == SQLITE_OK) {
		std::string sql = "SELECT * FROM DISLIKE WHERE id_user=" + std::to_string(id_user) + ";";

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

std::vector<std::vector<std::string>> DislikeDB::SelectDataDislikeOfPost(const char* path, int id_post)
{
	std::vector<std::vector<std::string>> resultData;

	for (int i = 0; i < 3; i++)
		resultData.push_back(std::vector< std::string >());

	sqlite3* DB;

	int exit = sqlite3_open(path, &DB);
	struct sqlite3_stmt* selectstmt;

	if (sqlite3_open(path, &DB) == SQLITE_OK) {
		std::string sql = "SELECT * FROM DISLIKE WHERE id_post=" + std::to_string(id_post) + ";";

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

bool DislikeDB::UserDislikePost(const char* s, int id_user, int id_post)
{
	std::vector<std::vector<std::string>> resultData;

	for (int i = 0; i < 3; i++)
		resultData.push_back(std::vector< std::string >());

	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);
	struct sqlite3_stmt* selectstmt;

	if (sqlite3_open(s, &DB) == SQLITE_OK) {
		std::string sql = "SELECT * FROM DISLIKE WHERE id_user= " + std::to_string(id_user) + " AND id_post=" + std::to_string(id_post) + ";";

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

void DislikeDB::DeletePostDislike(const char* path, int id_user, int id_post)
{
	sqlite3* DB;
	char* errorMessage;
	int exit = sqlite3_open(path, &DB);

	std::string sql = "DELETE FROM DISLIKE WHERE id_user= " + std::to_string(id_user) + " AND id_post=" + std::to_string(id_post) + ";";

	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, &errorMessage);
	if (exit != SQLITE_OK) {
		std::cerr << "Error to delete from POSTDISLIkE" << "\n";
		sqlite3_free(errorMessage);
	}
	else {
		std::cout << "PostDislike deleted" << "\n";
	}
}

int DislikeDB::callback(int argc, char** argv, char** azColName)
{
	for (int index = 0; index < argc; ++index) {
		std::cout << azColName[index] << ": " << argv[index] << "\n";
	}

	std::cout << "\n";

	return 0;
}

uint64_t DislikeDB::NumberOfDislike(const char* path, int id_post)
{
	std::vector<std::vector<std::string>> resultData = SelectDataDislikeOfPost(path,id_post);
	return resultData[0].size();
}
