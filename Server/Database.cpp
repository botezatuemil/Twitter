#include "Database.h"

void Database::CreateDB(const char* s)
{
	sqlite3* DB;
	int exit = 0;

	exit = sqlite3_open(s, &DB);

	sqlite3_close(DB);
}

void Database::CreateUserTable(const char* s)
{
	sqlite3* DB;

	std::string sql = "CREATE TABLE IF NOT EXISTS USER(" //basically the query where data is inserted (SQL)
		"id_user INTEGER PRIMARY KEY AUTOINCREMENT, "
		"username TEXT NOT NULL UNIQUE,"
		"password TEXT NOT NULL );";

	try {
		int exit = 0;
		exit - sqlite3_open(s, &DB); //tries to open sqlite

		char* errorMessage;
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

		if (exit != SQLITE_OK) { //if it fails
			std::cerr << "[ERROR] Table was not created" << "\n";
			sqlite3_free(errorMessage);
		}
		else {
			std::cout << "Table created succesfully" << "\n";
		}
		sqlite3_close(DB);
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}

}

void Database::CreatePostTable(const char* s)
{
	sqlite3* DB;

	std::string sql = "CREATE TABLE IF NOT EXISTS POST("
		"id_post INTEGER PRIMARY KEY AUTOINCREMENT, "
		"id_user INTEGER,"
		"post TEXT NOT NULL,"
		"timeofpost TEXT NOT NULL,"
		//	"PRAGMA foreign_keys = ON;"
		"constraint FK_id_user Foreign KEY (id_user) References USER (id_user) ON DELETE CASCADE ON UPDATE CASCADE);";

	try {
		int exit = 0;
		exit - sqlite3_open(s, &DB);

		char* errorMessage;
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

		if (exit != SQLITE_OK) {
			std::cerr << "[ERROR] Table was not created" << "\n";
			sqlite3_free(errorMessage);
		}
		else {
			std::cout << "Table post created succesfully" << "\n";
		}
		sqlite3_close(DB);
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}
}



void Database::CreateCommentTable(const char* s)
{
	sqlite3* DB;
	std::string sql = "CREATE TABLE IF NOT EXISTS COMMENT("
		"id_comment INTEGER PRIMARY KEY AUTOINCREMENT,"
		"id_user INTEGER,"
		"id_post INTEGER,"
		"comment TEXT NOT NULL,"
		"timeofcomment TEXT NOT NULL,"
		"CONSTRAINT FK_id_user FOREIGN KEY(id_user) references USER(id_user) ON DELETE CASCADE ON UPDATE CASCADE,"
		"CONSTRAINT FK_id_post FOREIGN KEY(id_post) references POST(id_post) ON DELETE CASCADE ON UPDATE CASCADE);";
	try
	{
		int exit = 0;
		exit - sqlite3_open(s, &DB);

		char* errorMessage;
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

		if (exit != SQLITE_OK) {
			std::cerr << "[ERROR] Table was not created" << "\n";
			sqlite3_free(errorMessage);
		}
		else {
			std::cout << "Table COMMENT created succesfully" << "\n";
		}
		sqlite3_close(DB);
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}
}

void Database::CreateDislikeTable(const char* s)
{
	sqlite3* DB;
	std::string sql = "CREATE TABLE IF NOT EXISTS DISLIKE("
		"id_dislike INTEGER PRIMARY KEY AUTOINCREMENT,"
		"id_user INTEGER,"
		"id_post INTEGER,"
		"CONSTRAINT FK_id_user FOREIGN KEY(id_user) references USER(id_user) ON DELETE CASCADE ON UPDATE CASCADE,"
		"CONSTRAINT FK_id_post FOREIGN KEY(id_post) references POST(id_post) ON DELETE CASCADE ON UPDATE CASCADE );";
	try
	{
		int exit = 0;
		exit - sqlite3_open(s, &DB);

		char* errorMessage;
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

		if (exit != SQLITE_OK) {
			std::cerr << "[ERROR] Table was not created" << "\n";
			sqlite3_free(errorMessage);
		}
		else {
			std::cout << "Table Dislike created succesfully" << "\n";
		}
		sqlite3_close(DB);
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}
}

void Database::CreateLikeTable(const char* s)
{

	sqlite3* DB;
	std::string sql = "CREATE TABLE IF NOT EXISTS LIKE("
		"id_like INTEGER PRIMARY KEY AUTOINCREMENT,"
		"id_user INTEGER,"
		"id_post INTEGER,"
		"CONSTRAINT FK_id_user FOREIGN KEY(id_user) references USER(id_user) ON DELETE CASCADE ON UPDATE CASCADE,"
		"CONSTRAINT FK_id_post FOREIGN KEY(id_post) references POST(id_post) ON DELETE CASCADE ON UPDATE CASCADE );";
	try
	{
		int exit = 0;
		exit - sqlite3_open(s, &DB);

		char* errorMessage;
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

		if (exit != SQLITE_OK) {
			std::cerr << "[ERROR] Table was not created" << "\n";
			sqlite3_free(errorMessage);
		}
		else {
			std::cout << "Table Like created succesfully" << "\n";
		}
		sqlite3_close(DB);
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}

}

void Database::CreateRepostTable(const char* s)
{

	sqlite3* DB;

	std::string sql = "CREATE TABLE IF NOT EXISTS REPOST("
		"id_repost INTEGER PRIMARY KEY AUTOINCREMENT, "
		"id_user INTEGER,"
		"id_post INTEGER,"
		"repost TEXT  NOT NULL,"
		"timeofrepost TEXT NOT NULL,"
		"constraint FK_id_user Foreign KEY (id_user) References USER (id_user) ON DELETE CASCADE ON UPDATE CASCADE ,"
		"constraint FK_id_post Foreign KEY (id_post) References POST (id_post) ON DELETE CASCADE ON UPDATE CASCADE );";

	try {
		int exit = 0;
		exit - sqlite3_open(s, &DB);

		char* errorMessage;
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

		if (exit != SQLITE_OK) {
			std::cerr << "[ERROR] Table was not created" << "\n";
			sqlite3_free(errorMessage);
		}
		else {
			std::cout << "Table Repost created succesfully" << "\n";
		}
		sqlite3_close(DB);
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}

}

void Database::CreateRepostCommentTable(const char* s)
{
	sqlite3* DB;
	std::string sql = "CREATE TABLE IF NOT EXISTS REPOSTCOMMENT("
		"id_repostcomment INTEGER PRIMARY KEY AUTOINCREMENT,"
		"id_user INTEGER,"
		"id_repost INTEGER,"
		"repostcomment TEXT NOT NULL,"
		"timeofrepostcomment TEXT NOT NULL,"
		"CONSTRAINT FK_id_user FOREIGN KEY(id_user) references USER(id_user) ON DELETE CASCADE ON UPDATE CASCADE,"
		"CONSTRAINT FK_id_repost FOREIGN KEY(id_repost) references REPOST(id_repost) ON DELETE CASCADE ON UPDATE CASCADE);";
	try
	{
		int exit = 0;
		exit - sqlite3_open(s, &DB);

		char* errorMessage;
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

		if (exit != SQLITE_OK) {
			std::cerr << "[ERROR] Table was not created" << "\n";
			sqlite3_free(errorMessage);
		}
		else {
			std::cout << "Table REPOSTCOMMENT created succesfully" << "\n";
		}
		sqlite3_close(DB);
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}
}

void Database::CreateRepostLikeTable(const char* s)
{
	sqlite3* DB;
	std::string sql = "CREATE TABLE IF NOT EXISTS REPOSTLIKE("
		"id_repostLike INTEGER PRIMARY KEY AUTOINCREMENT,"
		"id_user INTEGER,"
		"id_repost INTEGER,"
		"CONSTRAINT FK_id_user FOREIGN KEY(id_user) references USER(id_user) ON DELETE CASCADE ON UPDATE CASCADE ,"
		"CONSTRAINT FK_id_repost FOREIGN KEY(id_repost) references REPOST(id_repost) ON DELETE CASCADE ON UPDATE CASCADE );";
	try
	{
		int exit = 0;
		exit - sqlite3_open(s, &DB);

		char* errorMessage;
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

		if (exit != SQLITE_OK) {
			std::cerr << "[ERROR] Table was not created" << "\n";
			sqlite3_free(errorMessage);
		}
		else {
			std::cout << "Table Repostlike created succesfully" << "\n";
		}
		sqlite3_close(DB);
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}
}

void Database::CreateRepostDislikeTable(const char* s)
{

	sqlite3* DB;
	std::string sql = "CREATE TABLE IF NOT EXISTS REPOSTDISLIKE("
		"id_repostdislike INTEGER PRIMARY KEY AUTOINCREMENT,"
		"id_user INTEGER,"
		"id_repost INTEGER,"
		"CONSTRAINT FK_id_user FOREIGN KEY(id_user) references USER(id_user) ON DELETE CASCADE ON UPDATE CASCADE ,"
		"CONSTRAINT FK_id_repost FOREIGN KEY(id_repost) references REPOST(id_repost) ON DELETE CASCADE ON UPDATE CASCADE );";
	try
	{
		int exit = 0;
		exit - sqlite3_open(s, &DB);

		char* errorMessage;
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

		if (exit != SQLITE_OK) {
			std::cerr << "[ERROR] Table was not created" << "\n";
			sqlite3_free(errorMessage);
		}
		else {
			std::cout << "Table Repostlike created succesfully" << "\n";
		}
		sqlite3_close(DB);
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}

}

void Database::CreateFollowersAndFollowingTable(char const* s)
{
	sqlite3* DB;
	std::string sql = "CREATE TABLE IF NOT EXISTS FOLLOWERSANDFOLLOWING("
		"id_followersandfollowing INTEGER PRIMARY KEY AUTOINCREMENT,"
		"id_user_follower INTEGER,"
		"id_user_following INTEGER,"
		"CONSTRAINT FK_id_follower FOREIGN KEY(id_user_follower) references USER(id_user) ON DELETE CASCADE ON UPDATE CASCADE  ,"
		"CONSTRAINT FK_id_following FOREIGN KEY(id_user_following) references USER(id_user) ON DELETE CASCADE ON UPDATE CASCADE );";
	try
	{
		int exit = 0;
		exit - sqlite3_open(s, &DB);

		char* errorMessage;
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

		if (exit != SQLITE_OK) {
			std::cerr << "[ERROR] Table was not created" << "\n";
			sqlite3_free(errorMessage);
		}
		else {
			std::cout << "Table FOLLOWERSANDFOLLOWING created succesfully" << "\n";
		}
		sqlite3_close(DB);
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}
}

int Database::callback(int argc, char** argv, char** azColName)
{
	for (int index = 0; index < argc; ++index) {
		std::cout << azColName[index] << ": " << argv[index] << "\n";
	}

	std::cout << "\n";

	return 0;
}


void Database::DeleteUserTable(const char* s)
{
	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);

	std::string sql = "DROP TABLE USER;";

	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);

}

void Database::DeletePostTable(const char* s)
{
	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);

	std::string sql = "DROP TABLE POST;";

	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}



void Database::DeleteCommentTable(const char* s)
{
	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);

	std::string sql = "DROP TABLE COMMENT;";

	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}

void Database::DeleteLikeTable(const char* s)
{
	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);

	std::string sql = "DROP TABLE LIKE;";

	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}

void Database::DeleteDislikeTable(const char* s)
{
	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);

	std::string sql = "DROP TABLE DISLIKE;";

	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}

void Database::DeleteFollowersAndFollowingTable(const char* s)
{
	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);

	std::string sql = "DROP TABLE FOLLOWERSANDFOLLOWING;";

	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}

void Database::DeleteRepostTable(const char* s)
{
	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);

	std::string sql = "DROP TABLE REPOST;";

	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}

void Database::DeleteRepostCommentTable(const char* s)
{
	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);

	std::string sql = "DROP TABLE REPOSTCOMMENT;";

	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}

void Database::DeleteRepostLikeTable(const char* s)
{
	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);

	std::string sql = "DROP TABLE REPOSTLIKE;";

	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}

void Database::DeleteRepostDislikeTable(const char* s)
{
	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);

	std::string sql = "DROP TABLE REPOSTDISLIKE;";

	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}

