#pragma once
#include<string>
#include<vector>
#include<cstdint>
#include"../CommonClasses/CommentServer.h"
#include <memory>

#define DllExport   __declspec( dllexport )

 class DllExport PostPersonalProfile
{
public:
	PostPersonalProfile() = default;
	
	PostPersonalProfile(uint64_t id_post,
	 const std::string& text, std::vector<std::shared_ptr<CommentServer>>comments, uint64_t likes, uint64_t dislikes,const std::string& date);

	virtual void PrintPost();
	
	void SetText(const std::string& text);
	void SetLikes(const uint64_t& likes);
	void SetDislikes(const uint64_t& dislikes);
	void SetIdPost(uint64_t id_post);
	void SetDate(const std::string& date);

	const std::string& GetPostText() const;
	uint64_t GetCommentsSize() const;
	std::vector<std::shared_ptr<CommentServer>> GetComments() const;
	uint64_t GetLikes() const;
	uint64_t GetDislikes() const;
	uint64_t GetIdPost() const;
	const std::string& GetDate() const;

private:
	uint64_t m_id_post;
	uint64_t m_id_user;
	std::string m_post;
	std::string m_date;
	std::vector<std::shared_ptr<CommentServer>> m_comments;
	uint64_t m_likes;
	uint64_t m_dislikes;

};