#include "UserBD.h"
#include<vector>

std::vector<std::string> UserBD::getUserNames()
{
	return m_allUserNames;
}



void UserBD::InsertDataClient(const char* s, User user)
{
	sqlite3* DB;
	char* errorMessage;

	int exit = sqlite3_open(s, &DB);
	std::cout << user.GetPassword() << " " << user.GetUsername();

	std::string sql("INSERT INTO USER (USERNAME,PASSWORD) VALUES('" + user.GetUsername() + "', '" + user.GetPassword() + "');");

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

	if (exit != SQLITE_OK) {
		std::cerr << "Error to insert in User Table" << "\n";
		sqlite3_free(errorMessage);
	}
	else {
		std::cout << "Data for client inserted succesfully" << "\n";
	}
}



int UserBD::LevenshteinDistance(std::string searchedWord, std::string value)
{
	int sizeSearch = searchedWord.size() + 1;
	int sizeValue = value.size() + 1;

	std::vector<std::vector<int>> Lev(sizeSearch, std::vector<int>(sizeValue, 0));

	for (int i = 0; i < sizeSearch; i++) {
		for (int j = 0; j < sizeValue; j++) {
			if (i == 0)
				Lev[i][j] = j;
			else if (j == 0)
				Lev[i][j] = i;
			else {
				if (searchedWord[i - 1] == value[j - 1])
					Lev[i][j] = Lev[i - 1][j - 1];
				else
					Lev[i][j] = std::min(std::min(Lev[i][j - 1], Lev[i - 1][j - 1]), Lev[i - 1][j]) + 1;
			}
		}
	}
	return Lev[sizeSearch - 1][sizeValue - 1];
}

std::vector<std::vector<std::string>> UserBD::extractUserNames(const char* path)
{
	std::vector<std::vector<std::string>> resultData;

	for (int i = 0; i < 3; i++)
		resultData.push_back(std::vector< std::string >());

	sqlite3* DB;

	int exit = sqlite3_open(path, &DB);
	struct sqlite3_stmt* selectstmt;

	if (sqlite3_open(path, &DB) == SQLITE_OK) {

		sqlite3_prepare(DB, "SELECT * FROM USER;", -1, &selectstmt, NULL);
		sqlite3_step(selectstmt);

		while (sqlite3_column_text(selectstmt, 0))
		{
			for (int i = 0; i < 3; i++)
				resultData[i].push_back(std::string((char*)sqlite3_column_text(selectstmt, i)));
			sqlite3_step(selectstmt);
		}
	}

	return resultData;

	/*for (int i = 0; i < resultData[1].size(); ++i) {
		m_allUserNames.push_back(resultData[1][i]);
	}*/

}

int UserBD::callback(int argc, char** argv, char** azColName)
{
	for (int index = 0; index < argc; ++index) {


		std::cout << azColName[index] << ": " << argv[index] << "\n";

	}

	std::cout << "\n";

	return 0;
}

void UserBD::SelectDataUser(const char* s)
{
	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);

	std::string sql = "SELECT * FROM USER;";

	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}

int UserBD::SelectIdUser(const char* path, std::string username)
{
	std::vector<std::vector<std::string>> resultData;

	for (int i = 0; i < 3; i++)
		resultData.push_back(std::vector< std::string >());

	sqlite3* DB;

	int exit = sqlite3_open(path, &DB);
	struct sqlite3_stmt* selectstmt;

	if (sqlite3_open(path, &DB) == SQLITE_OK) {

		std::string sql = "SELECT * FROM USER WHERE username='" + username + "';";
		const char* c = sql.c_str();
		sqlite3_prepare(DB, c, -1, &selectstmt, NULL);
		sqlite3_step(selectstmt);

		while (sqlite3_column_text(selectstmt, 0))
		{
			for (int i = 0; i < 3; i++)
				resultData[i].push_back(std::string((char*)sqlite3_column_text(selectstmt, i)));
			sqlite3_step(selectstmt);
		}
		sqlite3_finalize(selectstmt);
		sqlite3_close(DB);
	}
	
	return std::stoi(resultData[0][0]);
}

void UserBD::DeleteAnUser(const char* s, User user)
{
	sqlite3* DB;
	std::string usernameBD = user.GetUsername();
	int exit = sqlite3_open(s, &DB);

	std::string sql = "DELETE FROM USER"
		"WHERE username = usernameBD; ";

	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}

bool UserBD::ExistUsername(const char* s, std::string username)
{
	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);

	std::string sql = ("SELECT * FROM USER"
		" WHERE USERNAME='" + username + "';");

	struct sqlite3_stmt* selectstmt;
	int result = sqlite3_prepare_v2(DB, sql.c_str(), -1, &selectstmt, NULL);
	if (result == SQLITE_OK)
	{
		if (sqlite3_step(selectstmt) == SQLITE_ROW)
		{
			sqlite3_finalize(selectstmt);
			sqlite3_close(DB);
			return true;
		}
		else
		{
			sqlite3_finalize(selectstmt);
			sqlite3_close(DB);
			return false;
		}
	}
	
}
std::string UserBD::SelectUsernameWithId(const char* path, int id_user)
{
	std::vector<std::vector<std::string>> resultData;

	for (int i = 0; i < 3; i++)
		resultData.push_back(std::vector< std::string >());

	sqlite3* DB;

	int exit = sqlite3_open(path, &DB);
	struct sqlite3_stmt* selectstmt;

	if (sqlite3_open(path, &DB) == SQLITE_OK) {

		std::string sql = "SELECT * FROM USER WHERE ID_USER="+std::to_string(id_user)+";";
		const char* c = sql.c_str();
		sqlite3_prepare(DB, c, -1, &selectstmt, NULL);
		sqlite3_step(selectstmt);

		while (sqlite3_column_text(selectstmt, 0))
		{
			for (int i = 0; i < 3; i++)
				resultData[i].push_back(std::string((char*)sqlite3_column_text(selectstmt, i)));
			sqlite3_step(selectstmt);
		}
		sqlite3_finalize(selectstmt);
		sqlite3_close(DB);
	}

	return resultData[1][0];
}
int UserBD::UserSize(const char* s)
{
	std::vector<std::vector<std::string>> resultData;

	for (int i = 0; i < 3; i++)
		resultData.push_back(std::vector< std::string >());

	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);
	struct sqlite3_stmt* selectstmt;

	if (sqlite3_open(s, &DB) == SQLITE_OK) {

		std::string sql = "SELECT * FROM USER";
		const char* c = sql.c_str();
		sqlite3_prepare(DB, c, -1, &selectstmt, NULL);
		sqlite3_step(selectstmt);

		while (sqlite3_column_text(selectstmt, 0))
		{
			for (int i = 0; i < 3; i++)
				resultData[i].push_back(std::string((char*)sqlite3_column_text(selectstmt, i)));
			sqlite3_step(selectstmt);
		}
		sqlite3_finalize(selectstmt);
		sqlite3_close(DB);
	}

	return resultData[0].size();
}

bool UserBD::ExistUser(const char* s, User user)
{
	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);


	std::string sql = ("SELECT * FROM USER WHERE PASSWORD='" + user.GetPassword() + "' AND username='" + user.GetUsername() + "';");
	struct sqlite3_stmt* selectstmt;
	int result = sqlite3_prepare_v2(DB, sql.c_str(), -1, &selectstmt, NULL);
	if (result == SQLITE_OK)
	{
		if (sqlite3_step(selectstmt) == SQLITE_ROW)
		{
			sqlite3_finalize(selectstmt);
			sqlite3_close(DB);
			return true;
		}
		else
		{
			sqlite3_finalize(selectstmt);
			sqlite3_close(DB);
			return false;
		}
	}
	sqlite3_finalize(selectstmt);
	sqlite3_close(DB);

}

void UserBD::UpdateDataUser(const char* s, std::string username, std::string initialUsername)
{
	sqlite3* DB;
	char* errorMessage;

	int exit = sqlite3_open(s, &DB);

	std::string sql("UPDATE USER SET NAME - '" + username + "' WHERE NAME - '" + initialUsername + "'");

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

	if (exit != SQLITE_OK) {
		std::cerr << "Error update data in USER" << "\n";
		sqlite3_free(errorMessage);
	}
	else {
		std::cout << "Data for client updated succesfully" << "\n";
	}
}