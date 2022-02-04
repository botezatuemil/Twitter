#include "CommentDB.h"

void CommentDB::InsertComment(const char* s, const std::string& comment, const std::string& timeOfComment, int id_user, int id_post)
{
    sqlite3* DB;
    char* errorMessage;

    int exit = sqlite3_open(s, &DB);

    std::string sql("PRAGMA foreign_keys = ON; INSERT INTO COMMENT (id_user,id_post,comment,timeofcomment) VALUES(" + std::to_string(id_user) + "," + std::to_string(id_post) + ",'" + comment + "','" + timeOfComment + "');");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

    if (exit != SQLITE_OK) {
        std::cerr << "Error to insert in Comment Table" << "\n";
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "Comment inserted succesfully" << "\n";
    }
}


//needs a review
void CommentDB::UpdateComment(const char* s, int id_comment, const std::string& newComment)
{
    sqlite3* DB;
    char* errorMessage;

    int exit = sqlite3_open(s, &DB);

    //can't insert int through this query
    std::string sql("UPDATE COMMENT SET COMMENT - '" + newComment + "' WHERE ID_COMMENT - '" + std::to_string(id_comment) + "'");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

    if (exit != SQLITE_OK) {
        std::cerr << "Error update comment in COMMENT" << "\n";
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "Comment updated succesfully" << "\n";
    }
}

void CommentDB::SelectComment(const char* s)
{
    sqlite3* DB;

    int exit = sqlite3_open(s, &DB);

    std::string sql = "SELECT * FROM COMMENT;";

    sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}

void CommentDB::ExistComment(const char* s, const std::string& username)
{
    sqlite3* DB;

    int exit = sqlite3_open(s, &DB);

    std::string sql = ("SELECT * FROM COMMENT"
        " WHERE ID_COMMENT='" + username + "';");

    sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}

void CommentDB::DeleteCommment(const char* s, int id_comment)
{
    sqlite3* DB;
    char* errorMessage;
    int exit = sqlite3_open(s, &DB);

    std::string sql = "DELETE FROM COMMENT WHERE id_comment= " + std::to_string(id_comment) + ";";

    sqlite3_exec(DB, sql.c_str(), c_callback, NULL, &errorMessage);
    if (exit != SQLITE_OK) {
        std::cerr << "Error to delete from COMMENT" << "\n";
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "Delete successful from COMMENT" << "\n";
    }
}

std::vector<std::vector<std::string>> CommentDB::selectCommentOfUser(const char* path, int id_post)
{
    std::vector<std::vector<std::string>> resultData;

    for (int i = 0; i < 5; i++)
        resultData.push_back(std::vector< std::string >());

    sqlite3* DB;

    int exit = sqlite3_open(path, &DB);
    struct sqlite3_stmt* selectstmt;

    if (sqlite3_open(path, &DB) == SQLITE_OK) {
        std::string sql = "SELECT * FROM COMMENT WHERE id_post=" + std::to_string(id_post) + ";";
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

int CommentDB::callback(int argc, char** argv, char** azColName)
{
    for (int index = 0; index < argc; ++index) {
        std::cout << azColName[index] << ": " << argv[index] << "\n";
    }

    std::cout << "\n";

    return 0;
}
