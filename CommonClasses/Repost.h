#pragma once
#include "Post.h"

#define DllExport   __declspec( dllexport )
class DllExport Repost :
    public Post
{
public:
    Repost() = default;
    Repost(uint64_t id_repost, uint64_t id_user_repost, std::string usernameUserRepost, std::string repostText, std::string timeOfRepost
    , uint64_t id_user, const std::string& usernameUserPost, uint64_t id_post, const std::string& text, std::vector<std::shared_ptr<CommentServer>> comments, uint64_t likes,
        uint64_t dislikes, const std::string& date);

    uint64_t GetIdRepost();
    uint64_t GetIdUserRepost();
    const std::string& GetUsernameRepost();
    const std::string& GetRepostText();
    const std::string& GetTimeOfRepost();
    void PrintPost();


private:
    uint64_t m_id_repost;
    uint64_t m_id_user_repost;
    std::string m_usernameUserRepost;
    std::string m_repostText;
    std::string m_timeOfRepost;
};

