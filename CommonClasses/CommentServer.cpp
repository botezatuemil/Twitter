#include "CommentServer.h"

CommentServer::CommentServer(uint64_t id_comment, uint64_t id_user, const std::string & comment, const std::string & timeOfComment, const std::string& usernameCom)
    :m_id_comment(id_comment)
    ,m_id_user(id_user)
    ,m_comment(comment)
    ,m_timeOfComment(timeOfComment)
    ,m_usernameCom(usernameCom)
{}


const std::string& CommentServer::GetComment() const
{
    return m_comment;
}

const std::string& CommentServer::GetTimeOfComment() const
{
    return m_timeOfComment;
}

const uint64_t CommentServer::GetIdComment() const
{
    return m_id_comment;
}

const uint64_t CommentServer::GetIdUser() const
{
    return m_id_user;
}

const uint64_t CommentServer::GetIdPost() const
{
    return m_id_post;
}

const std::string& CommentServer::GetUsername() const
{
    return m_usernameCom;
}

void CommentServer::SetComment(const std::string& comment)
{
    this->m_comment = comment;
}