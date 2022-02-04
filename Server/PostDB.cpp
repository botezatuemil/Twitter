#include "PostDB.h"
#include"../CommonClasses/CommentServer.h"
#include"../CommonClasses/PostPersonalProfile.h"
#include"CommentDB.h"
#include"LikeDB.h"
#include"DislikeDB.h"
#include"UserBD.h"
#include"DatabaseUtility.h"

static std::unordered_multimap<std::string, std::shared_ptr<Post>> m_indexTable;

void PostDB::InsertDataPost(const char* s, const std::string& postare, const std::string& timeOfPost, int id_user)
{
	sqlite3* DB;
	char* errorMessage;

	int exit = sqlite3_open(s, &DB);

	std::string sql("INSERT INTO POST (post,timeofpost,id_user) VALUES('" + postare + "','" + timeOfPost + "'," + std::to_string(id_user) + "); ");

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

	if (exit != SQLITE_OK) {
		std::cerr << "Error to insert in post Table" << "\n";
		sqlite3_free(errorMessage);
	}
	else {
		std::cout << "Data for Post inserted succesfully" << "\n";
	}
}


void PostDB::SelectDataPost(const char* path)
{
	sqlite3* DB;

	int exit = sqlite3_open(path, &DB);

	std::string sql = "SELECT * FROM POST;";

	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, NULL);
}

std::vector<std::vector<std::string>> PostDB::SelectDataOfUser(const char* path, int id_user)
{
	std::vector<std::vector<std::string>> resultData;

	for (int i = 0; i < 4; i++)
		resultData.push_back(std::vector< std::string >());

	sqlite3* DB;

	int exit = sqlite3_open(path, &DB);
	struct sqlite3_stmt* selectstmt;

	if (sqlite3_open(path, &DB) == SQLITE_OK) {
		std::string sql = "SELECT * FROM POST WHERE id_user=" + std::to_string(id_user) + ";";
		const char* c = sql.c_str();
		sqlite3_prepare(DB, c, -1, &selectstmt, NULL);
		sqlite3_step(selectstmt);

		while (sqlite3_column_text(selectstmt, 0))
		{
			for (int i = 0; i < 4; i++)
				resultData[i].push_back(std::string((char*)sqlite3_column_text(selectstmt, i)));
			sqlite3_step(selectstmt);
		}
	}

	return resultData;
}

std::vector<std::vector<std::string>> PostDB::SelectDataOfUserSearch(const char* path)
{
	std::vector<std::vector<std::string>> resultData;

	for (int i = 0; i < 4; i++)
		resultData.push_back(std::vector< std::string >());

	sqlite3* DB;

	int exit = sqlite3_open(path, &DB);
	struct sqlite3_stmt* selectstmt;

	if (sqlite3_open(path, &DB) == SQLITE_OK) {
		std::string sql = "SELECT * FROM POST;";
		const char* c = sql.c_str();
		sqlite3_prepare(DB, c, -1, &selectstmt, NULL);
		sqlite3_step(selectstmt);

		while (sqlite3_column_text(selectstmt, 0))
		{
			for (int i = 0; i < 4; i++)
				resultData[i].push_back(std::string((char*)sqlite3_column_text(selectstmt, i)));
			sqlite3_step(selectstmt);
		}
	}

	return resultData;
}

void PostDB::DeleteDataPost(const char* path, int id_post)
{
	sqlite3* DB;
	char* errorMessage;
	int exit = sqlite3_open(path, &DB);

	std::string sql = "DELETE FROM POST WHERE id_post= " + std::to_string(id_post) + ";";

	sqlite3_exec(DB, sql.c_str(), c_callback, NULL, &errorMessage);
	if (exit != SQLITE_OK) {
		std::cerr << "Error to delete" << "\n";
		sqlite3_free(errorMessage);
	}
	else {
		std::cout << "Delete succ" << "\n";
	}
}

int PostDB::callback(int argc, char** argv, char** azColName)
{
	for (int index = 0; index < argc; ++index) {
		std::cout << azColName[index] << ": " << argv[index] << "\n";
	}

	std::cout << "\n";

	return 0;
}

std::vector<std::shared_ptr<PostPersonalProfile>> PostDB::CreatePersonalPostObject(const char* path, int id_user)
{
	std::vector<std::shared_ptr<PostPersonalProfile>> personalProfilePost;
	std::vector<std::shared_ptr<CommentServer>>commentPostProf;

	std::vector<std::vector<std::string>> matrixUserPost = std::move(DatabaseUtility::SelectData(path, "SELECT * FROM POST WHERE id_user=" + std::to_string(id_user) + ";",
		DatabaseUtility::Table::ePost));
	if (matrixUserPost.size() > 0)
	{
		uint64_t nrCol = matrixUserPost[0].size();
		for (int i = 0; i < nrCol; i++)
		{

			int id_post;
			std::string post, timeOfPost;

			for (int j = 0; j < matrixUserPost.size(); j++)
			{
				if (j == 0)
				{
					id_post = std::stoi(matrixUserPost[j][i]);
				}				
				else if (j == 2)
				{
					post = std::move(matrixUserPost[j][i]);
				}
				else if (j == 3)
					timeOfPost = std::move(matrixUserPost[j][i]);
			}


			std::vector<std::vector<std::string>>matrixComm = std::move(DatabaseUtility::SelectData(path, "SELECT * FROM COMMENT WHERE id_post=" + std::to_string(id_post) + ";"
				, DatabaseUtility::Table::eComment));

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
							id_comment = std::stoi(matrixComm[j][i]);
						else if (j == 1)
							id_user = std::stoi(matrixComm[j][i]);
						else if (j == 3)
							comment = std::move(matrixComm[j][i]);
						else if (j == 4)
							dateTimeComment = std::move(matrixComm[j][i]);
					}

					std::string username = DatabaseUtility::SelectOneDataType(path, "SELECT username FROM USER WHERE ID_USER=" + std::to_string(id_user) + ";",
						DatabaseUtility::Table::eUser);
					commentPostProf.emplace_back(new CommentServer(id_comment, id_user, comment, dateTimeComment, username));
					username.clear();
				}

			}
			uint32_t nrLikes = DatabaseUtility::CountNumberOfRows(path, "select count(*) from LIKE WHERE id_post=" + std::to_string(id_post) + ";", DatabaseUtility::Table::eLike);
			uint32_t nrDislike = DatabaseUtility::CountNumberOfRows(path, "select count(*) from DISLIKE WHERE id_post=" + std::to_string(id_post) + ";", DatabaseUtility::Table::eDislike);
			
		personalProfilePost.emplace_back(new PostPersonalProfile(id_post, post, commentPostProf, nrLikes, nrDislike, timeOfPost));			
		commentPostProf.clear();

		}
		
	}	
		matrixUserPost.clear();
		return personalProfilePost;	
}

std::vector<std::shared_ptr<Post>> PostDB::CreateVectorSearch(const char* path)
{
	std::vector<std::shared_ptr<Post>>vectorPost;
	std::vector<std::vector<std::string>>matrixPost = std::move(DatabaseUtility::SelectData(path, "SELECT * FROM POST;", DatabaseUtility::Table::ePost));
	std::vector<std::shared_ptr<CommentServer>>commentPostProf;
	if (matrixPost.size() > 0)
	{
		uint64_t nrCol = matrixPost[0].size();
		for (int i = 0; i < nrCol; i++)
		{
			int id_post, id_user_post;
			std::string post, timeOfPost;

			for (int j = 0; j < matrixPost.size(); j++)
			{
				if (j == 0)
				{
					id_post = std::stoi(matrixPost[j][i]);
				}
				else if (j == 1)
				{
					id_user_post = std::stoi(matrixPost[j][i]);
				}
				else if (j == 2)
				{
					post = std::move(matrixPost[j][i]);
				}
				else if (j == 3)
					timeOfPost = std::move(matrixPost[j][i]);
			}

			std::vector<std::vector<std::string>>matrixComm = std::move(DatabaseUtility::SelectData(path, "SELECT * FROM COMMENT WHERE id_post=" + std::to_string(id_post) + ";",
				DatabaseUtility::Table::eComment));

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
							id_comment = std::stoi(matrixComm[j][i]);
						else if (j == 1)
							id_user = std::stoi(matrixComm[j][i]);
						else if (j == 3)
							comment = matrixComm[j][i];
						else if (j == 4)
							dateTimeComment = matrixComm[j][i];
					}
					std::string username = DatabaseUtility::SelectOneDataType(path, "SELECT username FROM USER WHERE ID_USER=" + std::to_string(id_user) + ";",
						DatabaseUtility::Table::eUser);
					commentPostProf.emplace_back(new CommentServer(id_comment, id_user, comment, dateTimeComment, username));
					username.clear();
				}

			}
			uint32_t nrLikes = DatabaseUtility::CountNumberOfRows(path, "select count(*) from LIKE WHERE id_post=" + std::to_string(id_post) + ";", DatabaseUtility::Table::eLike);
			uint32_t nrDislike = DatabaseUtility::CountNumberOfRows(path, "select count(*) from DISLIKE WHERE id_post=" + std::to_string(id_post) + ";", DatabaseUtility::Table::eDislike);

			vectorPost.emplace_back(new Post(id_user_post, UserBD::SelectUsernameWithId(path, id_user_post), id_post, post, commentPostProf, nrLikes,nrDislike, timeOfPost));
			commentPostProf.clear();

		}

	}
	matrixPost.clear();
	return vectorPost;
}

Post PostDB::ReturnPost(const char* path, int id_post)
{
	std::vector<std::vector<std::string>> resultData=std::move(DatabaseUtility::SelectData(path, "SELECT * FROM POST WHERE id_post =" + std::to_string(id_post) + ";",DatabaseUtility::Table::ePost));

	int id_repost, id_user, id_post_t;
	std::string post, timeOfPost;

	for (int i = 0; i < resultData[0].size(); i++)
	{
		for (int j = 0; j < resultData.size(); j++)
		{
			if (j == 0)
				id_post_t = std::stoi(resultData[j][i]);
			else if (j == 1)
				id_user = std::stoi(resultData[j][i]);
			else if (j == 2)
				post = resultData[j][i];
			else if (j == 3)
				timeOfPost = resultData[j][i];
		}
	}
	Post postareRet;
	postareRet.SetIdUser(id_user);
	postareRet.SetText(post);
	postareRet.SetDate(timeOfPost);
	postareRet.SetIdPost(id_post_t);
	std::cout << id_user << " " << id_post_t << " " << timeOfPost << "\n";
	return postareRet;
}

std::unordered_multimap<std::string, std::shared_ptr<Post>> PostDB::GetIndexTable()
{
	return m_indexTable;
}

void PostDB::SetIndexTable(const std::unordered_multimap<std::string, std::shared_ptr<Post>>& indexTable)
{
	m_indexTable = indexTable;
}


