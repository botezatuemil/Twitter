#include "DatabaseUtility.h"
#include "../CommonClasses/Logger.h"

void DatabaseUtility::InsertData(const char* s, const std::string& sql, DatabaseUtility::Table table)
{
	sqlite3* DB;
	char* errorMessage;

	int exit = sqlite3_open(s, &DB);
	std::cout << sql;
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

	if (exit != SQLITE_OK) {
		Logger::Log(Logger::Level::eInfo, "Data in " + FromTableToString(table) + " not inserted");
		sqlite3_free(errorMessage);
	}
	else {
		Logger::Log(Logger::Level::eInfo, "Data in " + FromTableToString(table) + " inserted succesfully");
	}


	
}

std::vector<std::vector<std::string>> DatabaseUtility::SelectData(const char* s, const std::string& sql, DatabaseUtility::Table table)
{
	std::vector<std::vector<std::string>> resultData;
	size_t vectorSize = CountNumberOfColumns(s, table);
	for (int i = 0; i < vectorSize; i++)
		resultData.push_back(std::vector< std::string >());

	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);
	struct sqlite3_stmt* selectstmt;

	if (sqlite3_open(s, &DB) == SQLITE_OK) {

		sqlite3_prepare(DB, sql.c_str(), -1, &selectstmt, NULL);
		sqlite3_step(selectstmt);

		while (sqlite3_column_text(selectstmt, 0))
		{
			for (int i = 0; i < vectorSize; i++)
				resultData[i].push_back(std::string((char*)sqlite3_column_text(selectstmt, i)));
			sqlite3_step(selectstmt);	
		}
		sqlite3_finalize(selectstmt);
	}
	//sqlite3_close(DB);


	return resultData;
}

void DatabaseUtility::DeleteData(const char* s, const std::string& sql, DatabaseUtility::Table table)
{
	sqlite3* DB;
	char* errorMessage;
	int exit = sqlite3_open(s, &DB);


	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, &errorMessage);
	if (exit != SQLITE_OK) {
		Logger::Log(Logger::Level::eInfo, "Data in " + FromTableToString(table) + " deleted succesfully");
		sqlite3_free(errorMessage);
	}
	else {
		Logger::Log(Logger::Level::eInfo, "Data in " + FromTableToString(table) + " not deleted");
	}

	//sqlite3_close(DB);
}

int DatabaseUtility::CountNumberOfColumns(const char* s, DatabaseUtility::Table table)
{
	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);
	struct sqlite3_stmt* selectstmt;
	std::string sql = "Select * from " + FromTableToString(table);
	//Logger::Log(Logger::Level::eInfo, sql);
	int rc = sqlite3_prepare_v2(DB, sql.c_str(), -1, &selectstmt, 0);
	int cols = sqlite3_column_count(selectstmt);
	
	sqlite3_finalize(selectstmt);
	//sqlite3_close(DB);
	return cols;
}

uint32_t DatabaseUtility::CountNumberOfRows(const char* s, const std::string& sql, DatabaseUtility::Table table)
{
	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);
	struct sqlite3_stmt* selectstmt;
//	Logger::Log(Logger::Level::eInfo, sql);
	 sqlite3_prepare_v2(DB, sql.c_str(), -1, &selectstmt, 0);
	//Logger::Log(Logger::Level::eInfo, sql);
	int rc = sqlite3_prepare_v2(DB, sql.c_str(), -1, &selectstmt, 0);
	sqlite3_step(selectstmt);
	int result = std::stoi(std::string((char*)sqlite3_column_text(selectstmt, 0)));
	//sqlite3_close(DB);
	sqlite3_finalize(selectstmt);
	return result;
	
}

int DatabaseUtility::callback(int argc, char** argv, char** azColName)
{
	for (int index = 0; index < argc; ++index) {
		std::cout << azColName[index] << ": " << argv[index] << "\n";
	}

	std::cout << "\n";

	return 0;
}

std::string DatabaseUtility::SelectOneDataType(const char* s, const std::string& sql, DatabaseUtility::Table table)
{
	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);
	struct sqlite3_stmt* selectstmt;
	//Logger::Log(Logger::Level::eInfo, sql);
	int rc = sqlite3_prepare_v2(DB, sql.c_str(), -1, &selectstmt, 0);
	sqlite3_step(selectstmt);
	
	std::string st= std::string((char*)sqlite3_column_text(selectstmt, 0));
	sqlite3_finalize(selectstmt);

	return st;
}

std::string DatabaseUtility::FromTableToString(DatabaseUtility::Table table)
{
	switch (table)
	{
	case Table::ePost:
		return "Post";
		break;
	case Table::eRepost:
		return "Repost";
		break;
	case Table::eComment:
		return "Comment";
		break;
	case Table::eRepostComment:
		return "RepostComment";
		break;
	case Table::eLike:
		return "Like";
		break;
	case Table::eRepostLike:
		return "RepostLike";
		break;
	case Table::eDislike:
		return "Dislike";
		break;
	case Table::eRepostDislike:
		return "RepostLike";
		break;
	case Table::eUser:
		return "User";
		break;
	case Table::eFollowersAndFollowing:
		return "FollowersAndFollowing";
		break;
	}

	return std::string();
}
