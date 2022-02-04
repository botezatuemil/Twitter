#include "SocialGraph.h"
#include <stack>

struct Graph {
	size_t size;
	std::unordered_set<int>* adjList;
};
static uint64_t id_user;

auto compare = [](std::shared_ptr<Post> p1, std::shared_ptr<Post> p2) {
	return SocialGraph::hashing(id_user, p1) > SocialGraph::hashing(id_user, p2);
};

static Graph* graph;
static std::priority_queue<std::shared_ptr<Post>, std::vector<std::shared_ptr<Post>>, decltype(compare)> feedPosts(compare);

void SocialGraph::createQueue(uint64_t id_user)
{
	uint16_t depth;
	std::vector<std::pair<uint64_t, uint16_t >> vectorOfUsers;

	
	AddInVectorOfUsers(vectorOfUsers,id_user);
}

void SocialGraph::AddInVectorOfUsers(std::vector<std::pair<uint64_t, uint16_t>> vectorOfUsers,uint64_t id_user)
{
	std::stack<int > stackOfUsers;
	stackOfUsers.emplace(id_user);
	while (stackOfUsers.empty() != 1)
	{
		uint64_t currentUser = stackOfUsers.top();
		stackOfUsers.pop();

	}
}

void SocialGraph::CreateGraph(const char* dir)
{
	std::vector<std::string> followTable;

	Graph* graph = new Graph;
	graph->size = UserBD::UserSize(dir) + 1;
	graph->adjList = new std::unordered_set<int>[graph->size];

	for (int i = 0; i < graph->size; ++i) {

		followTable = std::move(FollowingAndFollowerDB::SelectDataFollowingAndFollowerTable(dir, i));

		for (int j = 0; j < followTable.size(); ++j) {
			graph->adjList[i].insert(std::stoi(followTable[j]));
		}	
	}

	SetGraph(graph);
}

void SocialGraph::PrintGraph()
{

	for (int i = 0; i < graph->size; ++i) {

		std::cout << i << "->";

		for (auto itr = graph->adjList[i].begin(); itr != graph->adjList[i].end(); ++itr) {
			std::cout << *itr << " ";
		}
		std::cout << "\n";
	}
}

int SocialGraph::FindDistance(uint64_t id_user, uint64_t followers)
{
	int node, distance = 0, defaultState = INT_MAX;
	std::vector<int>visited;
	std::queue<std::pair<int, int>> q;

	visited.resize(graph->size);


	q.push(std::make_pair(id_user, distance));


	while (!q.empty()) {

		node = q.front().first;
		distance = q.front().second;

		q.pop();
		visited[node] = 1;

		if (node == followers) {
			return distance;
			break;
		}

		//if (node < graph->adjList->size())
		for (auto succ : graph->adjList[node]) {
			if (!visited[succ]) {
				q.push(std::make_pair(succ, distance + 1));
			}
		}
	}
	return defaultState;
}

void SocialGraph::SetGraph(struct Graph* other)
{
	graph = other;
}

Graph* SocialGraph::GetGraph()
{
	return graph;
}

std::vector<std::shared_ptr<Post>> SocialGraph::CreateFeedPosts()
{
	const char* dir = "./Twitter.db";
	std::vector<std::shared_ptr<Repost>>repost = std::move(RepostDB::ReturnVectorRepostSearch(dir));
	std::vector<std::shared_ptr<Post>>allPosts = std::move(PostDB::CreateVectorSearch(dir));
	std::vector<std::shared_ptr<Post>>posts;

	for (auto index : repost)
	{
		allPosts.emplace_back(std::move(index));
	}
	
	for (auto post : allPosts) {
		if (SocialGraph::FindDistance(id_user, post->GetIdUser()) != 0 && SocialGraph::FindDistance(id_user, post->GetIdUser()) != INT_MAX)
			feedPosts.push(post);
	}
	
	while (!feedPosts.empty()) {

		std::shared_ptr<Post>p = feedPosts.top();	
		posts.push_back(p);		
		feedPosts.pop();
	}

	return posts;
}

void SocialGraph::SetId(uint64_t id_userLogged)
{
	id_user = id_userLogged;
}

uint64_t SocialGraph::GetId()
{
	return uint64_t();
}

int SocialGraph::CalculateTime(const std::string& dateTime)
{
	struct std::tm tm = { 0 };
	std::istringstream ss1(dateTime);
	ss1 >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
	std::time_t time = mktime(&tm);

	std::chrono::system_clock::time_point then = std::chrono::system_clock::from_time_t(mktime(&tm));
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

	return std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch() - then.time_since_epoch()).count();
}

long long int SocialGraph::hashing(uint64_t id_user, std::shared_ptr<Post> p)
{	
	if (std::dynamic_pointer_cast<Repost>(p)) {
		auto cast = std::dynamic_pointer_cast<Repost>(p);
		return SocialGraph::FindDistance(id_user, cast->GetIdUserRepost()) + SocialGraph::CalculateTime(cast->GetTimeOfRepost());
	}
	return SocialGraph::FindDistance(id_user, p->GetIdUser()) + SocialGraph::CalculateTime(p->GetDate());
}




