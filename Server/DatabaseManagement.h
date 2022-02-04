#pragma once
#include <fstream>
#include <algorithm>
#include "UserBD.h"

class DatabaseManagement
{
public:
	enum class Action
	{
		eRegister,
		eLogin,
		ePost,
		eUserSearch,
		eUserPostPersonal,
		eUserPostSend,
		eFollowAndFollowing,
		eFollowStats,
		eFollowOrUnfollow,
		ePostForSearch,
		eKeywordSearch,
		eLikeAndDislikeStats,
		eLikeOrDislikeMake,
		eComment,
		eFeed,
		eRepost,
	};
public:
	 static void CheckFile(const char* database);
	 static void CreateInvertedIndex();
private:
	static void UserPostSend(std::ifstream& pFile, const char* database);

	static void PersonalProfilePost(std::ifstream& pFile, const char* database);
	static void PostForSearch(std::ifstream& pFile, const char* database);

	static void RegisterAction(std::ifstream& pFile, const char* database);
	static bool IsEmpty(std::ifstream& );
	
	static void LoginAction(std::ifstream& pFile);
	static void PostUserAction(std::ifstream& pFile, const char* database);

	static void FollowAndFollowing(std::ifstream& pFile, const char* database);
	static void FollowStats(std::ifstream& pFile, const char* database);
	static void FollowAndUnfollow(std::ifstream& pFile, const char* database);

	static void LikeAndDislikeStats(std::ifstream& pFile, const char* database);
	static void LikeOrDislikeMake(std::ifstream& pFile, const char* database);

	static void CommentPost(std::ifstream& pFile, const char* database);
	static void RepostAction(std::ifstream& pFile, const char* database);

	static Action FromStringToAction(const std::string& actionString);
	static std::string FromActionToaString(DatabaseManagement::Action action);
	static void WriteInFileUserSearch(std::ifstream& pFile);

	static void WriteInFileKeyword(std::ifstream& pFile);
	static void FeedPosts(std::ifstream& pFile);


};

 