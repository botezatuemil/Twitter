#include "Repost.h"
#include <iostream>

Repost::Repost(uint64_t id_repost, uint64_t id_user_repost, std::string usernameUserRepost, std::string repostText,
    std::string timeOfRepost, uint64_t id_user, const std::string& usernameUserPost,uint64_t id_post, const std::string& text, std::vector<std::shared_ptr<CommentServer>> comments,
    uint64_t likes, uint64_t dislikes, const std::string& date)
    :m_id_repost(id_repost)
    , m_id_user_repost(id_user_repost)
    , m_usernameUserRepost(usernameUserRepost)
    , m_repostText(repostText)
    , m_timeOfRepost(timeOfRepost)
    , Post::Post(id_user,usernameUserPost,id_post, text, comments, likes, dislikes, date)
{
}

uint64_t Repost::GetIdRepost()
{
    return m_id_repost;
}

uint64_t Repost::GetIdUserRepost()
{
    return m_id_user_repost;
}

const std::string& Repost::GetUsernameRepost()
{
    return m_usernameUserRepost;
}

const std::string& Repost::GetRepostText() 
{
   return m_repostText;
}

const std::string& Repost::GetTimeOfRepost()
{
    return m_timeOfRepost;
}

void Repost::PrintPost()
{
    Post::PrintPost();
    std::cout << "[ID_REPOST]:" << m_id_repost << "\n";
    std::cout << "[ID_USER_REPOST]:" << m_id_user_repost << "\n";
    std::cout << "[USERNAME_REPOST]:" << m_usernameUserRepost << "\n";
    std::cout << "[REPOST_TEXT]:" << m_repostText << "\n";
    std::cout << "[TIME_REPOST]:" << m_timeOfRepost << "\n";
}
