#pragma once
#include"PostPersonalProfile.h"
#define DllExport   __declspec( dllexport )

class DllExport RepostPersonalProfile: public PostPersonalProfile
{public:
    RepostPersonalProfile() = default;
    RepostPersonalProfile(uint64_t id_post,
        const std::string& text, std::vector<std::shared_ptr<CommentServer>>comments, uint64_t likes, uint64_t dislikes, 
        const std::string& date,uint64_t id_repost, const std::string& repostText, const std::string& timeOfRepost);

    void SetRepostText(const std::string& repostText);
    void SetTimeOfRepost(const std::string& timeOfRepost);
    void SetIdRepost(uint64_t id_repost);

    uint64_t GetIdRepost() const;
    const std::string& GetRepostText() const;
    const std::string& GetTimeOfRepost() const;

private:
    uint64_t m_id_repost;
    std::string m_repostText;
    std::string m_timeOfRepost;
};

