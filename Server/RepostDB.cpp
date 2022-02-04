#include <string>
#include "RepostDB.h"
#include "RepostCommentDB.h"
#include "UserBD.h"
#include "PostDB.h"
#include "RepostDislikeDB.h"
#include "RepostLikeDB.h"
#include "DatabaseUtility.h"
void RepostDB::InsertDataRepost(const char* path, const std::string& repost, const std::string& timeOfRepost, int id_user, int id_post)
{
	sqlite3* DB;
	char* errorMessage;

	int exit = sqlite3_open(path, &DB);

	std::string sql("INSERT INTO REPOST (id_user, id_post, repost, timeofrepost) VALUES(" + std::to_string(id_user) + "," + std::to_string(id_post) + ",'" + repost + "','" + timeOfRepost + "'); ");


	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

	if (exit != SQLITE_OK) {
		std::cerr << "Error to insert in Repost Table" << "\n";
		sqlite3_free(errorMessage);
	}
	else {
		std::cout << "Data for Repost inserted succesfully" << "\n";
	}
}

void RepostDB::SelectDataRepost(const char* path)
{
	sqlite3* DB;

	int exit = sqlite3_open(path, &DB);

	std::string sql = "SELECT * FROM REPOST;";

	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}

std::vector<std::vector<std::string>> RepostDB::SelectDataRepostOfPost(const char* path, int id_post)
{
	std::vector<std::vector<std::string>> resultData;

	for (int i = 0; i < 5; i++)
		resultData.push_back(std::vector< std::string >());

	sqlite3* DB;

	int exit = sqlite3_open(path, &DB);
	struct sqlite3_stmt* selectstmt;

	if (sqlite3_open(path, &DB) == SQLITE_OK) {
		std::string sql = "SELECT * FROM REPOST WHERE id_post=" + std::to_string(id_post) + ";";
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

std::vector<std::vector<std::string>> RepostDB::SelectDataRepostOfUser(const char* path, int id_user)
{
	std::vector<std::vector<std::string>> resultData;

	for (int i = 0; i < 5; i++)
		resultData.push_back(std::vector< std::string >());

	sqlite3* DB;

	int exit = sqlite3_open(path, &DB);
	struct sqlite3_stmt* selectstmt;

	if (sqlite3_open(path, &DB) == SQLITE_OK) {
		std::string sql = "SELECT * FROM REPOST WHERE id_user=" + std::to_string(id_user) + ";";
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

std::vector<std::vector<std::string>> RepostDB::SelectDataRepostForSearch(const char* path)
{
	std::vector<std::vector<std::string>> resultData;

	for (int i = 0; i < 5; i++)
		resultData.push_back(std::vector< std::string >());

	sqlite3* DB;

	int exit = sqlite3_open(path, &DB);
	struct sqlite3_stmt* selectstmt;

	if (sqlite3_open(path, &DB) == SQLITE_OK) {
		std::string sql = "SELECT * FROM REPOST;";
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

std::vector<std::shared_ptr<Repost>> RepostDB::ReturnVectorRepostSearch(const char* path)
{
	
	std::vector<std::vector<std::string>>matrixRepost=std::move(
	DatabaseUtility::SelectData(path, "SELECT * FROM REPOST;",DatabaseUtility::Table::eRepost));
	std::vector<std::shared_ptr<Repost>>RepostPosts;
	std::vector<std::shared_ptr<CommentServer>>commentPostProf;
	if (matrixRepost.size() > 0)
	{
		uint64_t nrCol = matrixRepost[0].size();
		for (int i = 0; i < nrCol; i++)
		{
			int id_repost, id_user_repost,id_post;
			std::string repost, timeOfRepost;

			for (int j = 0; j < matrixRepost.size(); j++)
			{
				if (j == 0)
				{
					id_repost = std::move(std::stoi(matrixRepost[j][i]));
				}
				else if (j == 1)
				{
					id_user_repost = std::move(std::stoi(matrixRepost[j][i]));
				}
				else if (j == 2)
				{
				   id_post= std::move(std::stoi(matrixRepost[j][i]));
				}
				else if (j == 3)
				{
					repost = std::move(matrixRepost[j][i]);
				}
				else if (j == 4)
					timeOfRepost = std::move(matrixRepost[j][i]);
			}

			//std::vector<std::vector<std::string>>matrixComm = std::move(RepostCommentDB::SelectDataRepostCommentOfRepost(path, id_repost));
			std::vector<std::vector<std::string>>matrixComm = std::move(
			DatabaseUtility::SelectData(path, "SELECT * FROM REPOSTCOMMENT WHERE id_repost=" + std::to_string(id_repost) + ";",DatabaseUtility::Table::eRepostComment));

			if (matrixComm.size() > 0)
			{
				int nrColoaneComment = matrixComm[0].size();
				for (int i = 0; i < nrColoaneComment; i++)
				{
					uint64_t id_comment, id_user, id_post_com;
					std::string comment, dateTimeComment;
					for (int j = 0; j < matrixComm.size(); j++)
					{
						if (j == 0)
							id_comment = std::move(std::stoi(matrixComm[j][i]));
						else if (j == 1)
							id_user = std::move(std::stoi(matrixComm[j][i]));
						else if (j == 3)
							comment = std::move(matrixComm[j][i]);
						else if (j == 4)
							dateTimeComment = std::move(matrixComm[j][i]);
					}
					std::string username = DatabaseUtility::SelectOneDataType(path, "SELECT username FROM USER WHERE ID_USER=" + std::to_string(id_user) + ";",
						DatabaseUtility::Table::eUser);

					commentPostProf.emplace_back(new CommentServer(id_comment, id_user, comment, dateTimeComment,username));
					username.clear();
					comment.clear();
					dateTimeComment.clear();
				}

			}
			Post temp = PostDB::ReturnPost(path,id_post);
			uint32_t nrLikes = DatabaseUtility::CountNumberOfRows(path, "select count(*) from REPOSTLIKE WHERE id_repost=" + std::to_string(id_repost) + ";", DatabaseUtility::Table::eRepostLike);
			uint32_t nrDislike = DatabaseUtility::CountNumberOfRows(path, "select count(*) from REPOSTDISLIKE WHERE id_repost=" + std::to_string(id_repost) + ";", DatabaseUtility::Table::eRepostDislike);
			temp.SetDislikes(nrDislike);
			temp.SetLikes(nrLikes);



			temp.SettUsernameUserPost(DatabaseUtility::SelectOneDataType(path, "SELECT username FROM USER WHERE ID_USER=" + std::to_string(temp.GetIdUser()) + ";",
				DatabaseUtility::Table::eUser));

			std::string username = DatabaseUtility::SelectOneDataType(path, "SELECT username FROM USER WHERE ID_USER=" + std::to_string(id_user_repost) + ";",
				DatabaseUtility::Table::eUser);

			RepostPosts.emplace_back(new Repost(id_repost,id_user_repost,username, repost, timeOfRepost,
				temp.GetIdUser(),temp.GetUsernameUserPost(),temp.GetIdPost(),temp.GetPostText(),commentPostProf,temp.GetLikes(),temp.GetDislikes(),temp.GetDate()));

			username.clear();
			repost.clear();
			timeOfRepost.clear();		
			commentPostProf.clear();

		}

	}

	matrixRepost.clear();	
	return RepostPosts;
}

void RepostDB::DeleteDataRepost(const char* path, int id_repost)
{
	sqlite3* DB;
	char* errorMessage;
	int exit = sqlite3_open(path, &DB);

	std::string sql = "DELETE FROM REPOST WHERE id_post= " + std::to_string(id_repost) + ";";

	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, &errorMessage);
	if (exit != SQLITE_OK) {
		std::cerr << "Error to delete from REPOST" << "\n";
		sqlite3_free(errorMessage);
	}
	else {
		std::cout << "Delete successful from REPOST" << "\n";
	}
}

int RepostDB::callback(int argc, char** argv, char** azColName)
{
	for (int index = 0; index < argc; ++index) {
		std::cout << azColName[index] << ": " << argv[index] << "\n";
	}

	std::cout << "\n";

	return 0;
}
