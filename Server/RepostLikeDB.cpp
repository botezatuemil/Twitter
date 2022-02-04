#include "RepostLikeDB.h"

void RepostLikeDB::InsertDataRepostLike(const char* path, int id_user, int id_repost)
{
    sqlite3* DB;
    char* errorMessage;

    int exit = sqlite3_open(path, &DB);

    std::string sql("INSERT INTO REPOSTLIKE (id_user, id_repost) VALUES(" + std::to_string(id_user) +","+std::to_string(id_repost) + "); ");


    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

    if (exit != SQLITE_OK) {
        std::cerr << "Error to insert in REPOSTLIKE Table" << "\n";
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "Data for client inserted succesfully" << "\n";
    }
}

void RepostLikeDB::SelectDataRepostLike(const char* path)
{
    sqlite3* DB;

    int exit = sqlite3_open(path, &DB);

    std::string sql = "SELECT * FROM REPOSTLIKE;";

    sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}

std::vector<std::vector<std::string>> RepostLikeDB::SelectDataRepostLikeOfUser(const char* path, int id_user)
{
    std::vector<std::vector<std::string>> resultData;

    for (int i = 0; i < 3; i++)
        resultData.push_back(std::vector< std::string >());

    sqlite3* DB;

    int exit = sqlite3_open(path, &DB);
    struct sqlite3_stmt* selectstmt;

    if (sqlite3_open(path, &DB) == SQLITE_OK) {
        std::string sql = "SELECT * FROM REPOSTLIKE WHERE id_user=" + std::to_string(id_user) + ";";

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


std::vector<std::vector<std::string>> RepostLikeDB::SelectDataRepostLikeOfPost(const char* path, int id_repost)
{
    std::vector<std::vector<std::string>> resultData;

    for (int i = 0; i < 3; i++)
        resultData.push_back(std::vector< std::string >());

    sqlite3* DB;

    int exit = sqlite3_open(path, &DB);
    struct sqlite3_stmt* selectstmt;

    if (sqlite3_open(path, &DB) == SQLITE_OK) {
        std::string sql = "SELECT * FROM REPOSTLIKE WHERE id_repost=" + std::to_string(id_repost) + ";";

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

void RepostLikeDB::DeleteRepostLike(const char* path, int id_user, int id_repost)
{
    sqlite3* DB;
    char* errorMessage;
    int exit = sqlite3_open(path, &DB);

    std::string sql = "DELETE FROM REPOSTLIKE WHERE id_user= " + std::to_string(id_user) + " AND id_repost=" + std::to_string(id_repost) + ";";;

    sqlite3_exec(DB, sql.c_str(), c_callback, NULL, &errorMessage);
    if (exit != SQLITE_OK) {
        std::cerr << "Error to delete from POSTLIKE" << "\n";
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "RepostLike deleted" << "\n";
    }
}

uint64_t RepostLikeDB::NumberOfLikes(const char* path, int id_repost)
{
    return SelectDataRepostLikeOfPost(path,id_repost)[0].size();
}

bool RepostLikeDB::UserLIkeRepost(const char* path, int id_user, int id_repost)
{
    std::vector<std::vector<std::string>> resultData;

    for (int i = 0; i < 3; i++)
        resultData.push_back(std::vector< std::string >());

    sqlite3* DB;

    int exit = sqlite3_open(path, &DB);
    struct sqlite3_stmt* selectstmt;

    if (sqlite3_open(path, &DB) == SQLITE_OK) {
        std::string sql = "SELECT * FROM REPOSTLIKE WHERE id_user= " + std::to_string(id_user) + " AND id_repost=" + std::to_string(id_repost) + ";";

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



int RepostLikeDB::callback(int argc, char** argv, char** azColName)
{
    for (int index = 0; index < argc; ++index) {
        std::cout << azColName[index] << ": " << argv[index] << "\n";
    }

    std::cout << "\n";

    return 0;
}
