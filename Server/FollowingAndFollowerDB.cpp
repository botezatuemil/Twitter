#include "FollowingAndFollowerDB.h"

void FollowingAndFollowerDB::InsertDataFolowerAndFollowing(const char* path, int id_userFollower, int id_userFollowing)
{
    sqlite3* DB;
    char* errorMessage;

    int exit = sqlite3_open(path, &DB);

    std::string sql("INSERT INTO FOLLOWERSANDFOLLOWING (id_user_follower, id_user_following) VALUES(" + std::to_string(id_userFollower) + "," + std::to_string(id_userFollowing) + "); ");


    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

    if (exit != SQLITE_OK) {
        std::cerr << "Error to insert in FollowerAndFollowing Table" << "\n";
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "Data for FollowerAndFollowing inserted succesfully" << "\n";
    }
}

void FollowingAndFollowerDB::SelectDataFollowingAndFollower(const char* path)
{
    sqlite3* DB;

    int exit = sqlite3_open(path, &DB);

    std::string sql = "SELECT * FROM FOLLOWERSANDFOLLOWING;";

    sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}

void FollowingAndFollowerDB::DeleteFollowing(const char* path, int id_userFollower, int id_userFollowing)
{
    sqlite3* DB;
    char* errorMessage;
    int exit = sqlite3_open(path, &DB);

    std::string sql = "DELETE FROM FOLLOWERSANDFOLLOWING WHERE id_user_follower= " + std::to_string(id_userFollower) + " AND id_user_following=" + std::to_string(id_userFollowing) + ";";

    sqlite3_exec(DB, sql.c_str(), c_callback, NULL, &errorMessage);
    if (exit != SQLITE_OK) {
        std::cerr << "Error to delete" << "\n";
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "Delete succ" << "\n";
    }
}

 std::vector<std::vector<std::string>> FollowingAndFollowerDB::SelectDataFollowingAndFollowerOfFollowing(const char* path, int id_userFollowing)
{
     std::vector<std::vector<std::string>> resultData;

     for (int i = 0; i < 3; i++)
         resultData.push_back(std::vector< std::string >());

     sqlite3* DB;

     int exit = sqlite3_open(path, &DB);
     struct sqlite3_stmt* selectstmt;

     if (sqlite3_open(path, &DB) == SQLITE_OK) {
         std::string sql = "SELECT * FROM FOLLOWERSANDFOLLOWING WHERE id_user_following=" + std::to_string(id_userFollowing) + ";";

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

 std::vector<std::vector<std::string>>FollowingAndFollowerDB::SelectDataFollowingAndFollowerOfFollower(const char* path, int id_userFollower)
{
     std::vector<std::vector<std::string>> resultData;

     for (int i = 0; i < 3; i++)
         resultData.push_back(std::vector< std::string >());

     sqlite3* DB;

     int exit = sqlite3_open(path, &DB);
     struct sqlite3_stmt* selectstmt;

     if (sqlite3_open(path, &DB) == SQLITE_OK) {
         std::string sql = "SELECT * FROM FOLLOWERSANDFOLLOWING WHERE id_user_follower=" + std::to_string(id_userFollower) + ";";

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

bool FollowingAndFollowerDB::SelectDataFollowingAndFollower(const char* path, int id_userFollower, int id_userFollowing)
 {
    std::vector<std::vector<std::string>> resultData;

    for (int i = 0; i < 3; i++)
        resultData.push_back(std::vector< std::string >());

    sqlite3* DB;

    int exit = sqlite3_open(path, &DB);
    struct sqlite3_stmt* selectstmt;

    if (sqlite3_open(path, &DB) == SQLITE_OK) {
        std::string sql = "SELECT * FROM FOLLOWERSANDFOLLOWING WHERE id_user_follower= " + std::to_string(id_userFollower)+" AND id_user_following="+std::to_string(id_userFollowing) + ";";

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
        return true;
    return false;
 }

 uint64_t FollowingAndFollowerDB::NumberOfFollowers(const char* path,uint64_t id_user)
 {
     std::vector<std::vector<std::string>> resultData = SelectDataFollowingAndFollowerOfFollowing(path, id_user);
     return resultData[0].size();
 }

 uint64_t FollowingAndFollowerDB::NumberOfFollowing(const char* path, uint64_t id_user)
 {

     std::vector<std::vector<std::string>> resultData = SelectDataFollowingAndFollowerOfFollower(path, id_user);
     return resultData[0].size();
 }

 int FollowingAndFollowerDB::callback(int argc, char** argv, char** azColName)
{
    for (int index = 0; index < argc; ++index) {
        std::cout << azColName[index] << ": " << argv[index] << "\n";
    }

    std::cout << "\n";

    return 0;
}

 std::vector<std::string > FollowingAndFollowerDB::SelectDataFollowingAndFollowerTable(const char* path, uint64_t id_user)
 {
     std::vector<std::vector<std::string>> resultData;

     for (int i = 0; i < 3; i++)
         resultData.push_back(std::vector< std::string >());

     sqlite3* DB;

     int exit = sqlite3_open(path, &DB);
     struct sqlite3_stmt* selectstmt;

     if (sqlite3_open(path, &DB) == SQLITE_OK) {
         std::string sql = "SELECT * FROM FOLLOWERSANDFOLLOWING WHERE id_user_follower= " + std::to_string(id_user) + ";";

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

     return resultData[2];
 }
