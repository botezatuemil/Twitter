#include "RepostCommentDB.h"

void RepostCommentDB::InsertDataRepostComment(const char* path, const std::string& repostComment, const std::string& timeOfRepostComment, int id_user, int id_repost)
{
    sqlite3* DB;
    char* errorMessage;

    int exit = sqlite3_open(path, &DB);

    std::string sql("INSERT INTO REPOSTCOMMENT(repostcomment, timeofrepostcomment, id_user, id_repost) VALUES('" + repostComment + "', '" + timeOfRepostComment + "', " + std::to_string(id_user) + ", " + std::to_string(id_repost) + "); ");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

    if (exit != SQLITE_OK) {
        std::cerr << "Error to insert in RepostComment Table" << "\n";
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "Data for RepostComment inserted succesfully" << "\n";
    }
}

void RepostCommentDB::SelectDataRepostComment(const char* path)
{
    sqlite3* DB;

    int exit = sqlite3_open(path, &DB);

    std::string sql = "SELECT * FROM REPOSTCOMMENT;";

    sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}

std::vector<std::vector<std::string>> RepostCommentDB::SelectDataRepostCommentOfUser(const char* path, int id_user)
{
    std::vector<std::vector<std::string>> resultData;

    for (int i = 0; i < 5; i++)
        resultData.push_back(std::vector< std::string >());

    sqlite3* DB;

    int exit = sqlite3_open(path, &DB);
    struct sqlite3_stmt* selectstmt;

    if (sqlite3_open(path, &DB) == SQLITE_OK) {
        std::string sql = "SELECT * FROM REPOSTCOMMENT WHERE id_user=" + std::to_string(id_user) + ";";
        const char* c = sql.c_str();
        sqlite3_prepare(DB, c, -1, &selectstmt, NULL);
        sqlite3_step(selectstmt);

        while (sqlite3_column_text(selectstmt, 0))
        {
            for (int i = 0; i < 5; i++)
                resultData[i].push_back(std::string((char*)sqlite3_column_text(selectstmt, i)));
            sqlite3_step(selectstmt);
        }
    }

    return resultData;
}

std::vector<std::vector<std::string>> RepostCommentDB::SelectDataRepostCommentOfRepost(const char* path, int id_repost)
{
    std::vector<std::vector<std::string>> resultData;

    for (int i = 0; i < 5; i++)
        resultData.push_back(std::vector< std::string >());

    sqlite3* DB;

    int exit = sqlite3_open(path, &DB);
    struct sqlite3_stmt* selectstmt;

    if (sqlite3_open(path, &DB) == SQLITE_OK) {
        std::string sql = "SELECT * FROM REPOSTCOMMENT WHERE id_repost=" + std::to_string(id_repost) + ";";
        const char* c = sql.c_str();
        sqlite3_prepare(DB, c, -1, &selectstmt, NULL);
        sqlite3_step(selectstmt);

        while (sqlite3_column_text(selectstmt, 0))
        {
            for (int i = 0; i < 5; i++)
                resultData[i].push_back(std::string((char*)sqlite3_column_text(selectstmt, i)));
            sqlite3_step(selectstmt);
        }
    }

    return resultData;
}

void RepostCommentDB::DeleteDataRepostComment(const char* path, int id_repost_comment)
{
    sqlite3* DB;
    char* errorMessage;
    int exit = sqlite3_open(path, &DB);

    std::string sql = "DELETE FROM REPOSTCOMMENT WHERE id_comment= " + std::to_string(id_repost_comment) + ";";

    sqlite3_exec(DB, sql.c_str(), c_callback, NULL, &errorMessage);
    if (exit != SQLITE_OK) {
        std::cerr << "Error to delete from REPOSTCOMMENT" << "\n";
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "Delete successful from REPOST COMMENT" << "\n";
    }
}

int RepostCommentDB::callback(int argc, char** argv, char** azColName)
{
    for (int index = 0; index < argc; ++index) {
        std::cout << azColName[index] << ": " << argv[index] << "\n";
    }

    std::cout << "\n";

    return 0;
}
