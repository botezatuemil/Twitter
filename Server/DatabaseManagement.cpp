#include"DatabaseManagement.h"
#include"User.h"
#include"UserBD.h"
#include"PostDB.h"
#include"CommentDB.h"
#include <iomanip>
#include <chrono>
#include <ctime>
#include "date.h"
#include<thread>
#include"FollowingAndFollowerDB.h"
#include "../CommonClasses/Repost.h"
#include "../CommonClasses/Logger.h"
#include "RepostDB.h"
#include"DislikeDB.h"
#include"RepostDislikeDB.h"
#include"RepostLikeDB.h"
#include"RepostCommentDB.h"
#include"LikeDB.h"
#include "DatabaseUtility.h"
#include"SocialGraph.h"

void DatabaseManagement::PersonalProfilePost(std::ifstream& pFile, const char* database)
{
	std::string id_user;
	std::ofstream out("../Server/server.out");
	std::ifstream fin("../Server/server.out");
	std::getline(pFile, id_user);
	std::vector<std::shared_ptr<PostPersonalProfile>>m_personalProfilePosts = std::move(PostDB::CreatePersonalPostObject(database, std::stoi(id_user)));


	while (true)
	{
		if (IsEmpty(fin) == true)
		{
			out << FromActionToaString(Action::eUserPostPersonal) << "\n";
			out << id_user << "\n";
			if (m_personalProfilePosts.size() == 0)
			{
				out << "FALSE";
				break;
			}
			else
			{
				out << "TRUE\n";
				out << m_personalProfilePosts.size() << "\n";
				for (auto index : m_personalProfilePosts)
				{
					out << index->GetIdPost() << "\n";
					out << index->GetPostText() << "\n";
					out << index->GetDate() << "\n";
					out << index->GetLikes() << "\n";
					out << index->GetDislikes() << "\n";
					if (index->GetComments().size() > 0)
					{
						out << "COMTRUE\n";
						out << index->GetComments().size() << "\n";
						for (auto indexCom : index->GetComments())
						{
							out << indexCom->GetIdComment() << "\n";
							out << indexCom->GetIdUser() << "\n";
							out << indexCom->GetUsername() << "\n";
							out << indexCom->GetComment() << "\n";
							out << indexCom->GetTimeOfComment() << "\n";
						}

					}
					else
					{
						out << "COMFALS\n";
					}
				}

			}
			break;
		}
	}
}
void DatabaseManagement::PostForSearch(std::ifstream& pFile, const char* database)
{
	std::string id_user;
}
void DatabaseManagement::RegisterAction(std::ifstream& pFile, const char* database)
{
	uint64_t time;
	std::string username, password;
	pFile >> username;
	pFile >> password;
	pFile >> time;

	User userTemp(username, password);
	//bool exista = UserBD::ExistUsername(database, userTemp.GetUsername());//fol count
	int var = DatabaseUtility::CountNumberOfRows(database, "SELECT COUNT(*) FROM USER WHERE username= '"+ username + "';", DatabaseUtility::Table::eUser);

	bool exista = false;
	if (var > 0)
		exista = true;

	std::ofstream out("../Server/server.out");
	std::ifstream fin("../Server/server.out");
	while (true)
	{
		if (exista == true && IsEmpty(fin) == true)
		{
			out << FromActionToaString(Action::eRegister) << "\n";
			out << time << "\n";
			out << "FALSE";
			break;
		}

		else if (exista == false && IsEmpty(fin) == true)
		{
			//UserBD::InsertDataClient(database, userTemp);
			DatabaseUtility::InsertData(database, "INSERT INTO USER(USERNAME, PASSWORD) VALUES('" + userTemp.GetUsername() + "', '" + userTemp.GetPassword() + "');", DatabaseUtility::Table::eUser);
			out << FromActionToaString(Action::eRegister) << "\n";
			out << time << "\n";
			out << "TRUE";

			break;
		}
	}

}
bool DatabaseManagement::IsEmpty(std::ifstream& pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();;
}

DatabaseManagement::Action DatabaseManagement::FromStringToAction(const std::string& actionString)
{
	if (actionString == "Register")
		return Action::eRegister;
	else if (actionString == "Login")
		return Action::eLogin;
	else if (actionString == "UserSearch")
		return Action::eUserSearch;
	else if (actionString == "UserPostSend")
		return Action::eUserPostSend;
	else if (actionString == "UserPostPersonal")
		return Action::eUserPostPersonal;
	else if (actionString == "FollowAndFollowing")
		return Action::eFollowAndFollowing;
	else if (actionString == "FollowStats")
		return Action::eFollowStats;
	else if (actionString == "FollowOrUnfollow")
		return Action::eFollowOrUnfollow;
	else if (actionString == "PostForSearch")
		return Action::ePostForSearch;
	else if (actionString == "KeywordSearch")
		return Action::eKeywordSearch;
	else if (actionString == "LikeAndDislikeStats")
		return Action::eLikeAndDislikeStats;
	else if (actionString == "LikeOrDislikeMake")
		return Action::eLikeOrDislikeMake;
	else if (actionString == "Comment")
		return Action::eComment;
	else if (actionString == "Feed")
		return Action::eFeed;
	else if (actionString == "Repost")
		return Action::eRepost;
}

void DatabaseManagement::LoginAction(std::ifstream& pFile)
{
	Logger::Log(Logger::Level::eInfo, "LOGIN REQUEST");
	const char* database = "./Twitter.db";
	std::string username, password, time;
	std::getline(pFile, username);
	std::getline(pFile, password);
	std::getline(pFile, time);
	User userTemp(username, password);

	/*bool exista = UserBD::ExistUser(database, userTemp);*/
	bool exista = false;
	int var = DatabaseUtility::CountNumberOfRows(database, "SELECT COUNT(*) FROM USER WHERE PASSWORD='" +password+ "' AND username='" + username + "';", DatabaseUtility::Table::eUser);

	if (var > 0)
		exista = true;

	std::ofstream out("../Server/server.out");
	std::ifstream fin("../Server/server.out");


	while (true)
	{
		if (exista == true && IsEmpty(fin) == true)
		{
			out << FromActionToaString(Action::eLogin) << "\n";
			out << UserBD::SelectIdUser(database, username) << "\n";	
			out << time << "\n";
			out << "TRUE";
			Logger::Log(Logger::Level::eInfo, "LOGIN USER: " + username + " TRUE");
			break;
		}

		else if (exista == false && IsEmpty(fin) == true)
		{
			out << FromActionToaString(Action::eLogin) << "\n";
			out << -1 << "\n";
			out << time << "\n";
			out << "FALSE";
			Logger::Log(Logger::Level::eInfo, "LOGIN USER: " + username + " FALSE");
			break;
		}
	}
}


void DatabaseManagement::FollowAndFollowing(std::ifstream& pFile, const char* database)
{
	std::string id_user;
	std::getline(pFile, id_user);
	Logger::Log(Logger::Level::eInfo, id_user + " REQUEST FOLLOWANDFOLLOWING NUMBERS");
	std::ofstream out("../Server/server.out");
	std::ifstream fin("../Server/server.out");
	while (true)
	{
		if (IsEmpty(fin) == true)
		{
			out << FromActionToaString(Action::eFollowAndFollowing) << "\n";
			out << id_user << "\n";
			//		out << FollowingAndFollowerDB::NumberOfFollowing(database, std::stoi(id_user)) << "\n";
			out << DatabaseUtility::CountNumberOfRows(database, "SELECT COUNT(*) FROM FOLLOWERSANDFOLLOWING WHERE id_user_follower=" + id_user + ";",
				DatabaseUtility::Table::eFollowersAndFollowing) << "\n";

			//	out << FollowingAndFollowerDB::NumberOfFollowers(database, std::stoi(id_user));
			out << DatabaseUtility::CountNumberOfRows(database, "SELECT COUNT(*) FROM FOLLOWERSANDFOLLOWING WHERE id_user_following=" + id_user + ";",
				DatabaseUtility::Table::eFollowersAndFollowing);
			break;
		}
	}

}

void DatabaseManagement::FollowStats(std::ifstream& pFile, const char* database)
{
	std::string id_user, id_user_search;
	std::getline(pFile, id_user);
	std::getline(pFile, id_user_search);
	//std::cout << "USER " << id_user << "REQUEST FOLLOW STATS FOR USER=" << id_user_search << "\n";
	Logger::Log(Logger::Level::eInfo, id_user + " REQUEST FOLLOWANDFOLLOWING NUMBERS " + id_user_search);
	std::ofstream out("../Server/server.out");
	std::ifstream fin("../Server/server.out");
	while (true)
	{
		if (IsEmpty(fin) == true)
		{
			out << FromActionToaString(Action::eFollowStats) << "\n";
			out << id_user << "\n";//de facut tot cu count
			/*if (FollowingAndFollowerDB::SelectDataFollowingAndFollower(database, std::stoi(id_user), std::stoi(id_user_search)) ==true)*/
			if (DatabaseUtility::CountNumberOfRows(database, "SELECT COUNT(*) FROM FOLLOWERSANDFOLLOWING WHERE id_user_follower= " + id_user + " AND id_user_following=" + id_user_search + ";", DatabaseUtility::Table::eFollowersAndFollowing) > 0)
			{
				out << "TRUE";
				break;
			}
			else
			{
				out << "FALSE";
				break;
			}
		}
	}
}

void DatabaseManagement::FollowAndUnfollow(std::ifstream& pFile, const char* database)
{
	std::string action, id_user, id_user_action;
	std::getline(pFile, action);
	std::getline(pFile, id_user);
	std::getline(pFile, id_user_action);

	if (action == "FOLLOW")
	{
		//std::cout << "USER " << id_user << " FOLLOW " << id_user_action<<"\n";
		Logger::Log(Logger::Level::eInfo, "USER " + id_user + " FOLLOW " + id_user_action);
		//FollowingAndFollowerDB::InsertDataFolowerAndFollowing(database, std::stoi(id_user), std::stoi(id_user_action));
		DatabaseUtility::InsertData(database, "INSERT INTO FOLLOWERSANDFOLLOWING (id_user_follower, id_user_following) VALUES(" + id_user + "," + id_user_action + "); ",
			DatabaseUtility::Table::eFollowersAndFollowing);
	}
	else if (action == "UNFOLLOW")
	{
		Logger::Log(Logger::Level::eInfo, "USER " + id_user + " UNFOLLOW " + id_user_action);
		//FollowingAndFollowerDB::DeleteFollowing(database, std::stoi(id_user), std::stoi(id_user_action));
		DatabaseUtility::DeleteData(database, "DELETE FROM FOLLOWERSANDFOLLOWING WHERE id_user_follower= " + id_user + " AND id_user_following=" + id_user_action + ";",
			DatabaseUtility::Table::eFollowersAndFollowing);
	}
}

void DatabaseManagement::LikeAndDislikeStats(std::ifstream& pFile, const char* database)
{
	int id_user, id_post;
	std::string type;
	pFile >> id_user >> id_post >> type;
	std::cout << "LIKE AND DISLIKE STATS FOR USER " << id_user << " AT POST " << id_post << "\n";
	while (true)
	{
		std::ifstream fin("server.out");
		if (IsEmpty(fin) == true)
		{
			std::ofstream out("server.out");
			out << FromActionToaString(Action::eLikeAndDislikeStats) << "\n";
			out << id_user << "\n";
			if (type == "POST")
			{
				//if (DislikeDB::UserDislikePost(database, id_user, id_post))
				if (DatabaseUtility::CountNumberOfRows(database, "SELECT COUNT(*) FROM DISLIKE WHERE id_user= " + std::to_string(id_user) + " AND id_post=" + std::to_string(id_post) + ";",
					DatabaseUtility::Table::eDislike) > 0)
					out << "DISLIKE";
				//	else if (LikeDB::UserLikePost(database, id_user, id_post))
				else if (DatabaseUtility::CountNumberOfRows(database, "SELECT COUNT(*) FROM LIKE WHERE id_user= " + std::to_string(id_user) + " AND id_post=" + std::to_string(id_post) + ";",
					DatabaseUtility::Table::eLike) > 0)
					out << "LIKE";
				else
					out << "NO";
				break;
			}
			else if (type == "REPOST")
			{
				//	if (RepostLikeDB::UserLIkeRepost(database, id_user, id_post))
				if (DatabaseUtility::CountNumberOfRows(database, "SELECT COUNT(*) FROM REPOSTLIKE WHERE id_user= " + std::to_string(id_user) + " AND id_repost=" + std::to_string(id_post) + ";",
					DatabaseUtility::Table::eRepostLike) > 0)
					out << "LIKE";
				//	else if (RepostDislikeDB::UserDislikeRepost(database, id_user, id_post))
				else if (DatabaseUtility::CountNumberOfRows(database, "SELECT COUNT(*) FROM REPOSTDISLIKE WHERE id_user= " + std::to_string(id_user) + " AND id_repost=" + std::to_string(id_post) + ";",
					DatabaseUtility::Table::eRepostLike) > 0)
					out << "DISLIKE";
				else
					out << "NO";
				break;
			}
		}
	}


}

void DatabaseManagement::LikeOrDislikeMake(std::ifstream& pFile, const char* database)
{
	uint64_t id_user, id_post;
	std::string action, type, exist;
	pFile >> id_user >> id_post >> action >> type >> exist;
	if (action == "LIKE" && type == "POST" && exist == "NO")
		//LikeDB::InsertDataLike(database, id_user, id_post);
		DatabaseUtility::InsertData(database, "INSERT INTO LIKE(id_user, id_post) VALUES(" + std::to_string(id_user) + ", " + std::to_string(id_post) + "); ",
			DatabaseUtility::Table::eLike);

	else if (action == "DISLIKE" && type == "POST" && exist == "NO")
		//DislikeDB::InsertDataDislike(database, id_user, id_post);
		DatabaseUtility::InsertData(database, "INSERT INTO DISLIKE(id_user, id_post) VALUES(" + std::to_string(id_user) + ", " + std::to_string(id_post) + "); ",
			DatabaseUtility::Table::eDislike);

	else if (action == "LIKE" && type == "REPOST" && exist == "NO")
		//RepostLikeDB::InsertDataRepostLike(database, id_user, id_post);
		DatabaseUtility::InsertData(database, "INSERT INTO REPOSTLIKE(id_user, id_repost) VALUES(" + std::to_string(id_user) + ", " + std::to_string(id_post) + "); ",
			DatabaseUtility::Table::eRepostLike);

	else if (action == "DISLIKE" && type == "REPOST" && exist == "NO")
		//RepostDislikeDB::InsertDataRepostDislike(database, id_user, id_post);
		DatabaseUtility::InsertData(database, "INSERT INTO REPOSTDISLIKE(id_user, id_repost) VALUES(" + std::to_string(id_user) + ", " + std::to_string(id_post) + "); ",
			DatabaseUtility::Table::eRepostDislike);
	else if (action == "DISLIKE" && type == "REPOST" && exist == "EXIST")
	{
		//RepostLikeDB::DeleteRepostLike(database, id_user, id_post);
		DatabaseUtility::DeleteData(database, "DELETE FROM REPOSTLIKE WHERE id_user = " + std::to_string(id_user) + " AND id_repost = " + std::to_string(id_post) + "; ",
			DatabaseUtility::Table::eRepostLike);
		//RepostDislikeDB::InsertDataRepostDislike(database, id_user, id_post);
		DatabaseUtility::InsertData(database, "INSERT INTO REPOSTDISLIKE(id_user, id_repost) VALUES(" + std::to_string(id_user) + ", " + std::to_string(id_post) + "); ",
			DatabaseUtility::Table::eRepostDislike);

	}
	else if (action == "LIKE" && type == "REPOST" && exist == "EXIST")
	{
		//RepostDislikeDB::DeleteRepostDislike(database, id_user, id_post);
		DatabaseUtility::DeleteData(database, "DELETE FROM REPOSTDISLIKE WHERE id_user = " + std::to_string(id_user) + " AND id_repost = " + std::to_string(id_post) + "; ",
			DatabaseUtility::Table::eRepostDislike);
		//RepostLikeDB::InsertDataRepostLike(database, id_user, id_post);
		DatabaseUtility::InsertData(database, "INSERT INTO REPOSTLIKE(id_user, id_repost) VALUES(" + std::to_string(id_user) + ", " + std::to_string(id_post) + "); ",
			DatabaseUtility::Table::eRepostLike);
	}
	else if (action == "DISLIKE" && type == "POST" && exist == "EXIST")
	{
		//	LikeDB::DeletePostLike(database, id_user, id_post);
		DatabaseUtility::DeleteData(database, "DELETE FROM LIKE WHERE id_user = " + std::to_string(id_user) + " AND id_post = " + std::to_string(id_post) + "; ",
			DatabaseUtility::Table::eLike);
		//DislikeDB::InsertDataDislike(database, id_user, id_post);
		DatabaseUtility::InsertData(database, "INSERT INTO DISLIKE(id_user, id_post) VALUES(" + std::to_string(id_user) + ", " + std::to_string(id_post) + "); ",
			DatabaseUtility::Table::eDislike);
	}
	else if (action == "LIKE" && type == "POST" && exist == "EXIST")
	{
		//DislikeDB::DeletePostDislike(database, id_user, id_post);
		DatabaseUtility::DeleteData(database, "DELETE FROM DISLIKE WHERE id_user = " + std::to_string(id_user) + " AND id_post = " + std::to_string(id_post) + "; ",
			DatabaseUtility::Table::eDislike);
		//LikeDB::InsertDataLike(database, id_user, id_post);
		DatabaseUtility::InsertData(database, "INSERT INTO LIKE(id_user, id_post) VALUES(" + std::to_string(id_user) + ", " + std::to_string(id_post) + "); ",
			DatabaseUtility::Table::eLike);
	}


	if (action == "LIKE" && type == "POST" && exist == "DELETE")
		//LikeDB::DeletePostLike(database, id_user, id_post);
		DatabaseUtility::DeleteData(database, "DELETE FROM LIKE WHERE id_user = " + std::to_string(id_user) + " AND id_post = " + std::to_string(id_post) + "; ",
			DatabaseUtility::Table::eLike);

	else if (action == "DISLIKE" && type == "POST" && exist == "DELETE")
		//DislikeDB::DeletePostDislike(database, id_user, id_post);
		DatabaseUtility::DeleteData(database, "DELETE FROM DISLIKE WHERE id_user = " + std::to_string(id_user) + " AND id_post = " + std::to_string(id_post) + "; ",
			DatabaseUtility::Table::eDislike);

	else if (action == "LIKE" && type == "REPOST" && exist == "DELETE")
		//RepostLikeDB::DeleteRepostLike(database, id_user, id_post);
		DatabaseUtility::DeleteData(database, "DELETE FROM REPOSTLIKE WHERE id_user = " + std::to_string(id_user) + " AND id_repost = " + std::to_string(id_post) + "; ",
			DatabaseUtility::Table::eRepostLike);
	else if (action == "DISLIKE" && type == "REPOST" && exist == "DELETE")
		//	RepostDislikeDB::DeleteRepostDislike(database, id_user, id_post);
		DatabaseUtility::DeleteData(database, "DELETE FROM REPOSTDISLIKE WHERE id_user = " + std::to_string(id_user) + " AND id_repost = " + std::to_string(id_post) + "; ",
			DatabaseUtility::Table::eRepostDislike);



}

void DatabaseManagement::CommentPost(std::ifstream& pFile, const char* database)
{
	std::string id_user, id_post;
	std::string comment, type;
	std::getline(pFile, id_user);
	std::getline(pFile, id_post);
	std::getline(pFile, type);
	std::getline(pFile, comment);
	std::string dateAndTime = date::format("%F %T", std::chrono::system_clock::now());
	if (type == "POST")
		//	CommentDB::InsertComment(database, comment, dateAndTime, std::stoi(id_user), std::stoi(id_post));
		DatabaseUtility::InsertData(database, "INSERT INTO COMMENT (id_user,id_post,comment,timeofcomment) VALUES(" + id_user + ","
			+ id_post + ",'" + comment + "','" + date::format("%F %T", std::chrono::system_clock::now()) + "');", DatabaseUtility::Table::eComment);
	else if (type == "REPOST")
		DatabaseUtility::InsertData(database, "INSERT INTO REPOSTCOMMENT (id_user, id_repost,repostcomment, timeofrepostcomment) VALUES(" + id_user + ","
			+ id_post + ",'" + comment + "','" + date::format("%F %T", std::chrono::system_clock::now()) + "');", DatabaseUtility::Table::eRepostComment);
}

void DatabaseManagement::RepostAction(std::ifstream& pFile, const char* database)
{
	std::string id_user, id_postare, repost, timeOfRepost;
	std::getline(pFile, id_user);
	std::getline(pFile, id_postare);
	std::getline(pFile, repost);
	timeOfRepost = date::format("%F %T", std::chrono::system_clock::now());

	DatabaseUtility::InsertData(database, "INSERT INTO REPOST (id_user, id_post, repost, timeofrepost) "
		"VALUES(" + id_user + "," + id_postare + ",'" + repost + "','" + timeOfRepost + "');", DatabaseUtility::Table::eRepost);
	timeOfRepost.clear();
	id_postare.clear();
	repost.clear();
	id_user.clear();
}

void DatabaseManagement::UserPostSend(std::ifstream& pFile, const char* database)
{

	const char* dir = "./Twitter.db";
	std::string postare, id_user;
	std::getline(pFile, id_user);
	std::getline(pFile, postare);
	std::string timeOfPost = date::format("%F %T", std::chrono::system_clock::now());

	//std::cout << "USER " << id_user << " INSERED A POSTA AT " << timeOfPost << "\N";
	//PostDB::InsertDataPost(dir, postare, timeOfPost, std::stoi(id_user)); 
	DatabaseUtility::InsertData(database, "INSERT INTO POST (post,timeofpost,id_user) VALUES('" + postare + "','" + timeOfPost + "'," + id_user + ");",
		DatabaseUtility::Table::ePost);


	postare.erase();
	id_user.erase();
}



void DatabaseManagement::CheckFile(const char* database)
{

	while (true)
	{
		std::ifstream fin("server.in");
		if (IsEmpty(fin) == false)
		{
			Action action;
			std::string actionString;
			std::getline(fin, actionString);
			action = FromStringToAction(actionString);

			if (action == Action::eRegister)
				RegisterAction(fin, database);
			if (action == Action::eLogin)
			{

				std::thread log{ DatabaseManagement::LoginAction,std::ref(fin) };
				log.join();
			}
			if (action == Action::eUserSearch)
			{

				std::thread userSearch{ DatabaseManagement::WriteInFileUserSearch,std::ref(fin) };
				userSearch.join();
			}
			if (action == Action::eUserPostSend)
			{
				UserPostSend(fin, database);
				DatabaseManagement::CreateInvertedIndex();
			}
			if (action == Action::eUserPostPersonal)
			{
				std::thread userSearch{ DatabaseManagement::PersonalProfilePost,std::ref(fin),database };
				userSearch.join();
			}
			if (action == Action::eFollowAndFollowing)
			{
				std::thread follow{ DatabaseManagement::FollowAndFollowing,std::ref(fin),database };
				follow.join();
			}
			if (action == Action::eFollowStats)
			{
				std::thread follow{ DatabaseManagement::FollowStats,std::ref(fin),database };
				follow.join();
			}
			if (action == Action::eFollowOrUnfollow)
			{

				std::thread FollowAndUnfollow{ DatabaseManagement::FollowAndUnfollow,std::ref(fin),database };
				FollowAndUnfollow.join();
			}
			if (action == Action::eKeywordSearch)
			{

				WriteInFileKeyword(fin);
			}
			if (action == Action::eLikeAndDislikeStats)
			{
				DatabaseManagement::LikeAndDislikeStats(fin, database);
			}
			if (action == Action::eLikeOrDislikeMake)
			{
				DatabaseManagement::LikeOrDislikeMake(fin, database);
			}
			if (action == Action::eComment)
			{
				DatabaseManagement::CommentPost(fin, database);
			}
			if (action == Action::eFeed)
			{
				FeedPosts(fin);
			}
			if (action == Action::eRepost)
				RepostAction(fin, database);

			std::ofstream ofs("server.in", std::ios::out | std::ios::trunc);

		}
	}
}

std::string DatabaseManagement::FromActionToaString(DatabaseManagement::Action action)
{
	switch (action)
	{
	case Action::eLogin:
		return "Login";
		break;
	case Action::ePost:
		return "Post";
		break;
	case Action::eRegister:
		return "Register";
		break;
	case Action::eUserSearch:
		return "UserSearch";
		break;
	case Action::eUserPostSend:
		return "UserPostSend";
		break;
	case Action::eUserPostPersonal:
		return "UserPostPersonal";
		break;
	case Action::eFollowAndFollowing:
		return "FollowAndFollowing";
		break;
	case Action::eFollowStats:
		return "FollowStats";
		break;
	case Action::eFollowOrUnfollow:
		return "FollowOrUnfollow";
		break;
	case Action::ePostForSearch:
		return "PostForSearch";
		break;
	case Action::eKeywordSearch:
		return "KeywordSearch";
		break;
	case Action::eLikeAndDislikeStats:
		return "LikeAndDislikeStats";
		break;
	case Action::eLikeOrDislikeMake:
		return "LikeOrDislikeMake";
		break;
	case Action::eComment:
		return "Comment";
		break;
	case Action::eFeed:
		return "Feed";
	case Action::eRepost:
		return "Repost";
		break;
	}

	return std::string();
}


void DatabaseManagement::WriteInFileUserSearch(std::ifstream& pFile)
{

	std::ofstream out("server.out");
	std::ifstream fin("server.out");
	const char* dir = "./Twitter.db";
	std::string searchedUsername;
	pFile >> searchedUsername;
	std::vector<std::vector<std::string>> usernames = std::move(UserBD::extractUserNames(dir));
	std::vector<std::pair<std::string, std::string>> positionFirst;

	while (true)
	{
		if (IsEmpty(fin) == true)
		{
			out << FromActionToaString(Action::eUserSearch) << "\n";

			int index = 0;

			for (std::vector<std::string>::iterator it = usernames[1].begin(); it != usernames[1].end();) {

				int pos = (*it).find(searchedUsername);

				if (pos == 0) {
					positionFirst.push_back(std::make_pair(*it, usernames[0][index]));
					it = usernames[1].erase(it);

				}
				else {
					++it;
					index++;
				}
			}

			std::sort(positionFirst.begin(), positionFirst.end(), [searchedUsername](std::pair<std::string, std::string> username1, std::pair<std::string, std::string> username2) {
				return UserBD::LevenshteinDistance(searchedUsername, username1.first) < UserBD::LevenshteinDistance(searchedUsername, username2.first);
				});

			for (const auto& position : positionFirst) {
				out << position.first << "\n" << position.second << "\n";
			}

			/*std::sort(usernames.begin(), usernames.end(), [searchedUsername](std::pair<std::string, std::string> username1, std::pair<std::string, std::string> username2) {
				return UserBD::LevenshteinDistance(searchedUsername, username1.first) < UserBD::LevenshteinDistance(searchedUsername, username2.first);
				});*/

			for (int i = 0; i < usernames[1].size(); ++i) {
				//std::cout << usernames[1][i];
				if (UserBD::LevenshteinDistance(searchedUsername, usernames[1][i]) <= 2) {
					out << usernames[1][i] << "\n" << usernames[0][i];
				}

			}
			break;
		}
	}
}



void DatabaseManagement::CreateInvertedIndex()
{
	const char* dir = "./Twitter.db";

	std::vector<std::shared_ptr<Repost>>repost = std::move(RepostDB::ReturnVectorRepostSearch(dir));
	std::vector<std::shared_ptr<Post>>allPosts = std::move(PostDB::CreateVectorSearch(dir));
	std::unordered_multimap<std::string, std::shared_ptr<Post>> indexTable;

	for (auto index : repost)
	{
		allPosts.emplace_back(std::move(index));
	}

	for (const auto& post : allPosts) {

		std::string word;

		if (std::dynamic_pointer_cast<Repost>(post)) {

			auto cast = std::dynamic_pointer_cast<Repost>(post);
			std::istringstream iss(cast->GetRepostText());
			while (iss >> word) {

				indexTable.insert(std::make_pair(word, post));
			}
		}
		else {
			std::istringstream iss(post->GetPostText());
			while (iss >> word) {

				indexTable.insert(std::make_pair(word, post));
			}
		}

	}

	PostDB::SetIndexTable(indexTable);
}

void DatabaseManagement::WriteInFileKeyword(std::ifstream& pFile)
{

	std::ofstream out("server.out");
	std::ifstream fin("server.out");
	
	const char* dir = "./Twitter.db";

	std::string searchedQuery;
	std::getline(pFile, searchedQuery);

	std::cout << searchedQuery;

	std::string queryWord;
	std::istringstream iss(searchedQuery);
	std::istringstream is(searchedQuery);
	int counterPost = 0, counterRepost = 0;

	std::unordered_multimap<std::string, std::shared_ptr<Post>> indexTable = std::move(PostDB::GetIndexTable());


	while (true) {

		if (IsEmpty(fin) == true) {

			out << FromActionToaString(Action::eKeywordSearch) << "\n";

			while (iss >> queryWord) {

				auto postInstances = indexTable.equal_range(queryWord);

				for (auto& it = postInstances.first; it != postInstances.second; ++it) {

					if (std::dynamic_pointer_cast<Repost>(it->second)) {
						auto cast = std::dynamic_pointer_cast<Repost>(it->second);
						counterPost++;
					}
					else {
						counterRepost++;
						//std::cout << it->second->GetIdPost() << "\n";
					}
				}
			}

			out << counterPost + counterRepost << "\n";

			while (is >> queryWord) {

				auto postInstances = indexTable.equal_range(queryWord);

				for (auto& it = postInstances.first; it != postInstances.second; ++it) {

					if (std::dynamic_pointer_cast<Repost>(it->second)) {

						auto cast = std::dynamic_pointer_cast<Repost>(it->second);
						
						out << "REPOSTARE\n";
						out << cast->GetIdRepost() << "\n";
						out << cast->GetIdPost() << "\n";
						out << cast->GetRepostText() << "\n";
						out << cast->GetPostText() << "\n";
						out << cast->GetUsernameUserPost() << "\n";
						out << cast->GetUsernameRepost() << "\n";
						out << cast->GetIdUser() << "\n";
						out << cast->GetIdUserRepost() << "\n";
						out << cast->GetTimeOfRepost() << "\n";
						out << cast->GetDate() << "\n";
						out << cast->GetLikes() << "\n";
						out << cast->GetDislikes() << "\n";

						if (cast->GetComments().size() > 0)
						{
							out << "COMTRUE\n";
							out << cast->GetComments().size() << "\n";
							for (auto indexCom : cast->GetComments())
							{
								out << indexCom->GetIdComment() << "\n";
								out << indexCom->GetIdUser() << "\n";
								out << indexCom->GetUsername() << "\n";
								out << indexCom->GetComment() << "\n";
								out << indexCom->GetTimeOfComment() << "\n";
							}
						}
						else
						{
							out << "COMFALS\n";
						}
					}
					else {
						out << "POSTARE\n";
						
						out << it->second->GetIdPost() << "\n";
						out << it->second->GetPostText() << "\n";
						out << it->second->GetUsernameUserPost() << "\n";
						out << it->second->GetIdUser() << "\n";
						out << it->second->GetDate() << "\n";
						out << it->second->GetLikes() << "\n";
						out << it->second->GetDislikes() << "\n";

						if (it->second->GetComments().size() > 0)
						{
							out << "COMTRUE\n";
							out << it->second->GetComments().size() << "\n";
							for (auto indexCom : it->second->GetComments())
							{
								out << indexCom->GetIdComment() << "\n";
								out << indexCom->GetIdUser() << "\n";
								out << indexCom->GetUsername() << "\n";
								out << indexCom->GetComment() << "\n";
								out << indexCom->GetTimeOfComment() << "\n";
							}
						}
						else
						{
							out << "COMFALS\n";
						}
					}
				}
			}

			break;
		}

	}

}

void DatabaseManagement::FeedPosts(std::ifstream& pFile)
{

	std::ofstream out("server.out");
	std::ifstream fin("server.out");
	const char* dir = "./Twitter.db";

	std::string current_id, action;

	pFile >> current_id;
	std::ofstream ofs("server.in", std::ios::out | std::ios::trunc);
	std::cout << current_id << "\n\n\n";


	SocialGraph::CreateGraph(dir);
	SocialGraph::SetId(std::stoi(current_id));
	//SocialGraph::PrintGraph();
	auto feedPosts = SocialGraph::CreateFeedPosts();
	

	while (true) {

		if (IsEmpty(fin) == true) {

			out << FromActionToaString(Action::eFeed) << "\n";
		
			out << feedPosts.size() << "\n";

			for (const auto& post : feedPosts) {

				if (std::dynamic_pointer_cast<Repost>(post)) {

					auto cast = std::dynamic_pointer_cast<Repost>(post);
					out << "REPOSTARE\n";
					out << cast->GetIdRepost() << "\n";
					out << cast->GetIdPost() << "\n";
					out << cast->GetRepostText() << "\n";
					out << cast->GetPostText() << "\n";
					std::cout << cast->GetPostText() << "\n";
					out << cast->GetUsernameUserPost() << "\n";
					out << cast->GetUsernameRepost() << "\n";
					out << cast->GetIdUser() << "\n";
					out << cast->GetIdUserRepost() << "\n";
					out << cast->GetTimeOfRepost() << "\n";
					out << cast->GetDate() << "\n";
					out << cast->GetLikes() << "\n";
					out << cast->GetDislikes() << "\n";

					if (cast->GetComments().size() > 0)
					{
						out << "COMTRUE\n";
						out << cast->GetComments().size() << "\n";
						for (auto indexCom : cast->GetComments())
						{
							out << indexCom->GetIdComment() << "\n";
							out << indexCom->GetIdUser() << "\n";
							out << indexCom->GetUsername() << "\n";
							out << indexCom->GetComment() << "\n";
							out << indexCom->GetTimeOfComment() << "\n";
						}
					}
					else
					{
						out << "COMFALS\n";
					}

				}
				else {
					out << "POSTARE\n";
					out << post->GetIdPost() << "\n";
					out << post->GetPostText() << "\n";
					std::cout << post->GetPostText() << "\n";
					out << post->GetUsernameUserPost() << "\n";
					out << post->GetIdUser() << "\n";
					out << post->GetDate() << "\n";
					out << post->GetLikes() << "\n";
					out << post->GetDislikes() << "\n";

					if (post->GetComments().size() > 0)
					{
						out << "COMTRUE\n";
						out << post->GetComments().size() << "\n";
						for (auto indexCom : post->GetComments())
						{
							out << indexCom->GetIdComment() << "\n";
							out << indexCom->GetIdUser() << "\n";
							out << indexCom->GetUsername() << "\n";
							out << indexCom->GetComment() << "\n";
							out << indexCom->GetTimeOfComment() << "\n";
						}
					}
					else
					{
						out << "COMFALS\n";
					}
				}
			}
			
		}
		break;

	}

}
