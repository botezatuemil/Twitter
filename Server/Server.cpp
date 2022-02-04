#include <iostream>
#include "Database.h"
#include"DatabaseManagement.h"
#include "UserBD.h"
#include "CommentDB.h"
#include "PostDB.h"
#include "LikeDB.h"
#include "DislikeDB.h"
#include "RepostDB.h"
#include "RepostCommentDB.h"
#include "RepostLikeDB.h"
#include "RepostDislikeDB.h"
#include "FollowingAndFollowerDB.h"
#include "date.h"
#include <iomanip>
#include <chrono>
#include <ctime>
#include<vector>
#include"../CommonClasses/PostPersonalProfile.h"
#include"../CommonClasses/Post.h"
#include "../CommonClasses/CommonClasses.h"
#include "../CommonClasses/Logger.h"
#include "SocialGraph.h"
#include "DatabaseUtility.h"

int main()
{
	
	Database db;
	const char* dir = "./Twitter.db";
	sqlite3* DB;

	std::time_t result = std::time(nullptr);
	std::string dateAndTime = date::format("%F %T", std::chrono::system_clock::now());
	
	DatabaseManagement check;

	DatabaseManagement::CreateInvertedIndex();
	check.CheckFile(dir);

	return 1;

}
