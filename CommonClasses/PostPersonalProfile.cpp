#include "PostPersonalProfile.h"
#include<iostream>


PostPersonalProfile::PostPersonalProfile(uint64_t id_post, const std::string& text, std::vector<std::shared_ptr<CommentServer>> comments, 
	uint64_t likes, uint64_t dislikes, const std::string& date)

	:m_id_post(id_post)
	, m_post(text)
	, m_comments(comments)
	, m_likes(likes)
	, m_dislikes(dislikes)
	 ,m_date(date)
{}

void PostPersonalProfile::PrintPost()
{
	std::cout << "[ID_POST]:" << m_id_post<<"\n";
	std::cout << "[TEXT_POST]:" << m_post<<"\n";
	std::cout << "[LIKE_POST]:" << m_likes << "\n";
	std::cout << "[DISLIKE_POST]:" << m_dislikes << "\n";
	std::cout << "[DATE_POST]:" << m_date << "\n";
	std::cout << "\n";
	for (auto index : m_comments)
	{
		std::cout << "[ID_COMMENT]:" << index->GetIdComment() << "\n";
		std::cout << "[ID_USER_COMMENT]:" << index->GetIdUser() << "\n";
		std::cout << "[USERNAME_COMMENT]:" << index->GetUsername() << "\n";
		std::cout << "[TEXT_COMMENT]:" << index->GetComment() << "\n";
		std::cout << "[TIME_COMMENT]:" << index->GetTimeOfComment() << "\n\n";
	}


}



void PostPersonalProfile::SetText(const std::string& text)
{
	m_post = text;
}

void PostPersonalProfile::SetLikes(const uint64_t& likes)
{
	m_likes = likes;
}

void PostPersonalProfile::SetDislikes(const uint64_t& dislikes)
{
	m_dislikes = dislikes;
}

void PostPersonalProfile::SetIdPost(uint64_t id_post)
{
	m_id_post = id_post;
}

void PostPersonalProfile::SetDate(const std::string& date)
{
	m_date = date;
}


const std::string& PostPersonalProfile::GetPostText() const
{
	return this->m_post;
}

uint64_t PostPersonalProfile::GetCommentsSize() const
{
	return this->m_comments.size();
}

std::vector<std::shared_ptr<CommentServer>> PostPersonalProfile::GetComments() const
{
	return m_comments;
}



uint64_t PostPersonalProfile::GetLikes() const
{
	return this->m_likes;
}

uint64_t PostPersonalProfile::GetDislikes() const
{
	return this->m_dislikes;
}

uint64_t PostPersonalProfile::GetIdPost() const
{
	return m_id_post;
}

const std::string& PostPersonalProfile::GetDate() const
{
	return m_date;
}

