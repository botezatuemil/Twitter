#include "Post.h"
#include <iostream>

Post::Post(uint64_t id_user, const std::string& usernameUserPost,uint64_t id_post, const std::string& text, std::vector<std::shared_ptr<CommentServer>> comments, uint64_t likes, uint64_t dislikes, const std::string& date)

	:m_id_user(id_user)
	,m_usernameUserPost(usernameUserPost)
	,PostPersonalProfile::PostPersonalProfile(id_post,text,comments,likes,dislikes,date)
	
{
}

void Post::SetIdUser(uint64_t id_user)
{
	m_id_user = id_user;
}

uint64_t Post::GetIdUser() const
{
	return m_id_user;
}

void Post::PrintPost()
{
	PostPersonalProfile::PrintPost();
	std::cout << "[ID_USER_POST]:" << m_id_user << "\n";
	std::cout << "[USERNAME_POST]:" << m_usernameUserPost << "\n";
}

void Post::SettUsernameUserPost(const std::string& usernameUserPost)
{
	this->m_usernameUserPost = usernameUserPost;
}

const std::string& Post::GetUsernameUserPost() const
{
	return m_usernameUserPost;
}
