#pragma once
#include<string>
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include"User.h"

class UserBD
{

private:
    std::vector<std::string>m_allUserNames;
    User m_userReturnat;

public:
    std::vector<std::string> getUserNames();

public:
    static void InsertDataClient(const char* s, User user);
   static void UpdateDataUser(const char* s, std::string username, std::string initiralUsername);
    static void SelectDataUser(const char* s);
    static int SelectIdUser(const char* s, std::string username);
    void DeleteAnUser(const char* s, User user);
    static bool ExistUsername(const char* s, std::string username); //aici se muta in cpp, dupa ce imi dau seama cum sa linkez 
      
    static std::string SelectUsernameWithId(const char* path, int id_user);
    static int UserSize(const char* s);


    static bool ExistUser(const char* s, User user); //aici se muta in cpp, dupa ce imi dau seama cum sa linkez 
      


    static int LevenshteinDistance(std::string searchedWord, std::string value);

    static std::vector<std::vector<std::string>> extractUserNames(const char* path);


    //EXTRACT DATA//
    //argc: holds the number of results, argv: holds each value in array, azColName: holds each column
    static int callback(int argc, char** argv, char** azColName);

    //cast callback
    static int c_callback(void* NotUsed, int argc, char** argv, char** azColName) {
        UserBD* database = reinterpret_cast<UserBD*>(NotUsed);
        return database->callback(argc, argv, azColName);
    }

};

