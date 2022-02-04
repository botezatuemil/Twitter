#include "RepostDislikeDB.h"
#include <string>
#include <iostream>
#include <sqlite3.h>

void RepostDislikeDB::InsertDataRepostDislike(const char* path, int id_user, int id_repost)
{
    sqlite3* DB;
    char* errorMessage;

    int exit = sqlite3_open(path, &DB);

    std::string sql("INSERT INTO REPOSTDISLIKE (id_user, id_repost) VALUES(" + std::to_string(id_user) + "," + std::to_string(id_repost) +  "); ");


    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

    if (exit != SQLITE_OK) {
        std::cerr << "Error to insert in RepostDislike Table" << "\n";
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "Data for RepostDislike inserted succesfully" << "\n";
    }
}

void RepostDislikeDB::SelectDataRepostDislike(const char* path)
{
    sqlite3* DB;

    int exit = sqlite3_open(path, &DB);

    std::string sql = "SELECT * FROM REPOSTDISLIKE;";

    sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}

std::vector<std::vector<std::string>> RepostDislikeDB::SelectDataRepostDislikeOfUser(const char* path, int id_user)
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

std::vector<std::vector<std::string>> RepostDislikeDB::SelectDataRepostDislikeOfPost(const char* path, int id_repost)
{
    std::vector<std::vector<std::string>> resultData;

    for (int i = 0; i < 3; i++)
        resultData.push_back(std::vector< std::string >());

    sqlite3* DB;

    int exit = sqlite3_open(path, &DB);
    struct sqlite3_stmt* selectstmt;

    if (sqlite3_open(path, &DB) == SQLITE_OK) {
        std::string sql = "SELECT * FROM REPOSTDISLIKE WHERE id_repost=" + std::to_string(id_repost) + ";";

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

void RepostDislikeDB::DeleteRepostDislike(const char* path, int id_user, int id_repost)
{
    sqlite3* DB;
    char* errorMessage;
    int exit = sqlite3_open(path, &DB);

    std::string sql = "DELETE FROM REPOSTDISLIKE WHERE id_user= " + std::to_string(id_user) + " AND id_repost=" + std::to_string(id_repost) + ";";;

    sqlite3_exec(DB, sql.c_str(), c_callback, NULL, &errorMessage);
    if (exit != SQLITE_OK) {
        std::cerr << "Error to delete" << "\n";
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "RepostDislike deleted"<<"\n";
    }
}

bool RepostDislikeDB::UserDislikeRepost(const char* path, int id_user, int id_repost)
{
    std::vector<std::vector<std::string>> resultData;

    for (int i = 0; i < 3; i++)
        resultData.push_back(std::vector< std::string >());

    sqlite3* DB;

    int exit = sqlite3_open(path, &DB);
    struct sqlite3_stmt* selectstmt;

    if (sqlite3_open(path, &DB) == SQLITE_OK) {
        std::string sql = "SELECT * FROM REPOSTDISLIKE WHERE id_user= " + std::to_string(id_user) + " AND id_repost=" + std::to_string(id_repost) + ";";

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


int RepostDislikeDB::callback(int argc, char** argv, char** azColName)
{
    for (int index = 0; index < argc; ++index) {
        std::cout << azColName[index] << ": " << argv[index] << "\n";
    }

    std::cout << "\n";

    return 0;
}

uint64_t RepostDislikeDB::NumberOfDislike(const char* path, uint64_t id_repost)
{
    return SelectDataRepostDislikeOfPost(path,id_repost)[0].size();
}
