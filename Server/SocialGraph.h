#pragma once
#include <iostream>
#include <queue>
#include "UserBD.h"
#include "Database.h"
#include "FollowingAndFollowerDB.h"
#include <unordered_set>
#include "../CommonClasses/Post.h"
#include "../CommonClasses/Repost.h"
#include "RepostDB.h"
#include "PostDB.h"
#include <time.h>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <sstream>


class SocialGraph
{

public:

	static void createQueue(uint64_t id_user);
	static void AddInVectorOfUsers(std::vector<std::pair<uint64_t,uint16_t>>vectorOfUsers,uint64_t id_user);

	static void CreateGraph(const char* dir);
	static void PrintGraph();
	static int FindDistance(uint64_t id_user, uint64_t followers);

	static void SetGraph(struct Graph* other);
	static struct Graph* GetGraph();

	static std::vector<std::shared_ptr<Post>> CreateFeedPosts();

	static void SetId(uint64_t id_userLogged);
	uint64_t GetId();

	static int CalculateTime(const std::string& dateTime);
	static long long int hashing(uint64_t id_user, std::shared_ptr<Post> p);
private:
	
	
};

