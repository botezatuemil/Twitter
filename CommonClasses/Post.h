#pragma once
#include "PostPersonalProfile.h"

#define DllExport   __declspec( dllexport )
class DllExport Post :
    public PostPersonalProfile
{
public:
    Post(uint64_t id_user, const std::string& usernameUserPost,uint64_t id_post, const std::string& text, std::vector<std::shared_ptr<CommentServer>>
        comments, uint64_t likes, uint64_t dislikes, const std::string& date);
    Post() = default;
    void SetIdUser(uint64_t id_user);
    uint64_t GetIdUser() const;
    virtual void PrintPost();
    void SettUsernameUserPost(const std::string& usernameUserPost);
    const std::string& GetUsernameUserPost() const;
 private:
    uint64_t m_id_user;
    std::string m_usernameUserPost;
};

