
# Twitter in C++

This was a project made in second year of university in a group of 4, for Modern C++ final grade.




## Features

#### 1. Client Server Architecture
- A text file was used to communicate between client and server with custom messages for commands
- The client opens the file and writes a formatted request, saves the file and close it.
- The server sees that the data changed, it process it and writes the response to an output file
- The commands are enum class

Code for writing in file from variable argument list in client

```c++
void ClientManagement::WriteInFileAction(T&& ...args)
{ 
	while (true)
	{
		std::ifstream fin("../Server/server.in");
		if (IsEmpty(fin) == true)
		{
			std::ofstream out("../Server/server.in");
			((out << std::forward<T>(args) << "\n"), ...);
			break;
		}
	}
}

```

Enum class for all commands
```c++
enum class Action
	{
		eRegister,
		eLogin,
		ePost,
		eUserSearch,
		eUserPostPersonal,
		eUserPostSend,
		eFollowAndFollowing,
		eFollowStats,
		eFollowOrUnfollow,
		eKeywordSearch,
		eLikeAndDislikeStats,
		eLikeOrDislikeMake,
		eComment,
		eFeed,
		eRepost
	};
```


#### 2. SQLite Database

All CRUD operations are functions that calls whenever an insert or deletion occurs.

- The functions work for every table because it receives an sql command from parameters
- An example of insertion is given below:

```c++

void DatabaseUtility::InsertData(const char* s, const std::string& sql, DatabaseUtility::Table table)
{
	sqlite3* DB;
	char* errorMessage;

	int exit = sqlite3_open(s, &DB);
	std::cout << sql;
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errorMessage);

	if (exit != SQLITE_OK) {
		Logger::Log(Logger::Level::eInfo, "Data in " + FromTableToString(table) + " not inserted");
		sqlite3_free(errorMessage);
	}
	else {
		Logger::Log(Logger::Level::eInfo, "Data in " + FromTableToString(table) + " inserted succesfully");
	}
}
```

#### 3. User search with Levenshtein distance

```c++
int UserBD::LevenshteinDistance(std::string searchedWord, std::string value)
{
	int sizeSearch = searchedWord.size() + 1;
	int sizeValue = value.size() + 1;

	std::vector<std::vector<int>> Lev(sizeSearch, std::vector<int>(sizeValue, 0));

	for (int i = 0; i < sizeSearch; i++) {
		for (int j = 0; j < sizeValue; j++) {
			if (i == 0)
				Lev[i][j] = j;
			else if (j == 0)
				Lev[i][j] = i;
			else {
				if (searchedWord[i - 1] == value[j - 1])
					Lev[i][j] = Lev[i - 1][j - 1];
				else
					Lev[i][j] = std::min(std::min(Lev[i][j - 1], Lev[i - 1][j - 1]), Lev[i - 1][j]) + 1;
			}
		}
	}
	return Lev[sizeSearch - 1][sizeValue - 1];
}
```

### 4. Keyword Search with Inverted Index

This was used to search in all posts by a key

- A look up table of unordered multimap with a string key and a shared pointer of Post model was used

```c++
std::unordered_multimap<std::string, std::shared_ptr<Post>> indexTable = std::move(PostDB::GetIndexTable());
```

### 5. Social Graph

A social graph is a graph that stores the friendship between multiple friends in a network.
The graph was used for feed to create a priority of posts considering how far a friend is in your list and the time of post
-  the graph contains an unordered set that represents an adjacency list
- calculates the distance between friends with a queue traversal
- calculates the time since the last post of any User
- the time and the number of followers will be used in a priority queue

```c++
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
```

```c++
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

		for (auto succ : graph->adjList[node]) {
			if (!visited[succ]) {
				q.push(std::make_pair(succ, distance + 1));
			}
		}
	}
	return defaultState;
}

```

#### 6. Logger

The logger is a DLL and was used for an easier debugging experience
- it writes a level of information represented by an enum class
- Writes the current timestamp and other data from it's variable argument list

```c++
enum class Level
	{
		eInfo,
		eError,
		eLogin,
		eLogout,
		eRegister
	};

template<class ... Args>
void log(Args&& ... params)
{
	Logger::Log(Logger::Level::Info, std::forward<Args>(params)...);
}
```


## Screenshots

#### Login
   
![login](https://user-images.githubusercontent.com/74835450/195375048-4afc5d10-b9de-43da-9618-98fd6ea4f1fc.png)

#### Menu
![menu](https://user-images.githubusercontent.com/74835450/195375090-f6a41a81-0cb4-4c55-86bc-dab371e7c6d1.png)

#### Feed 
![feed](https://user-images.githubusercontent.com/74835450/195375114-c6bbed54-0a75-415e-a1f9-df1526711676.png)

#### Make a tweet
![tweet](https://user-images.githubusercontent.com/74835450/195375168-37715a4a-29db-4fc3-a22e-d68d6949fa8c.png)

#### See other people profile
![see_other_profile](https://user-images.githubusercontent.com/74835450/195375196-b2d9e698-d4b8-4cab-815d-48200e38e75d.png)

#### Search user based on Levanshtain distance 
![user_search](https://user-images.githubusercontent.com/74835450/195375209-000ea3c7-f36d-43d7-84cd-9f8ae5b44e70.png)

#### Search a post by keyword search 
![keyword_search](https://user-images.githubusercontent.com/74835450/195375224-1bf3a62f-c113-474b-af26-7b6516b8f61f.png)


## Tech Stack

**Client:** Qt Widgets

**Server:** C++

**Database:** SQLite

