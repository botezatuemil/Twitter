#include "RepostPersonalProfile.h"

RepostPersonalProfile::RepostPersonalProfile(uint64_t id_post, const std::string& text, std::vector<std::shared_ptr<CommentServer>> comments,
	uint64_t likes, uint64_t dislikes, const std::string& date, uint64_t id_repost,
	const std::string& repostText, const std::string& timeOfRepost)

	:PostPersonalProfile(id_post, text, comments, likes, dislikes, date)
	, m_id_repost(id_repost)
	, m_repostText(repostText)
	, m_timeOfRepost(timeOfRepost)
{
}

void RepostPersonalProfile::SetRepostText(const std::string& repostText)
{
	m_repostText = repostText;
}

void RepostPersonalProfile::SetTimeOfRepost(const std::string& timeOfRepost)
{
	m_timeOfRepost = timeOfRepost;
}

void RepostPersonalProfile::SetIdRepost(uint64_t id_repost)
{
	m_id_repost = id_repost;
}

uint64_t RepostPersonalProfile::GetIdRepost() const
{
	return m_id_repost;
}

const std::string& RepostPersonalProfile::GetRepostText() const
{
	return m_repostText;
}

const std::string& RepostPersonalProfile::GetTimeOfRepost() const
{
	return m_timeOfRepost;
}
