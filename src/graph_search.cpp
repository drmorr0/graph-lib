// graph_search.cpp: David R. Morrison

#include "graph_search.h"

#include <algorithm>

using namespace std;

namespace graph
{

vector<int> shortestPath(const Graph& g, int source, int sink)
{
	multimap<int, int> queue;
	map<int, int> dist; map<int, int> prev;

	dist[source] = 0;

	for (auto i = g.begin(); i != g.end(); ++i)
	{
		if (i->first != source)
			dist[i->first] = g.order() + 1;
		prev[i->first] = -1;
		queue.insert(pair<int,int>(dist[i->first], i->first));
	}

	while (!queue.empty())
	{
		auto pos = queue.begin();
		int u = pos->second;
		int d = pos->first;
		queue.erase(pos);

		if (u == sink) break;

		vector<int> n = g.neighbors(u);
		for (size_t i = 0; i < n.size(); ++i)
		{
			if (d + 1 < dist[n[i]])
			{
				auto rng = queue.equal_range(dist[n[i]]);
				for (auto j = rng.first; j != rng.second; ++j)
				{
					if (j->second == n[i])
					{
						queue.erase(j);
						queue.insert(pair<int,int>(d + 1, n[i]));
						break;
					}
				}
				dist[n[i]] = d + 1;
				prev[n[i]] = u;
			}
		}
	}

	vector<int> path;
	if (prev[sink] == -1 && sink != source) return path;

	int curr = sink;
	while (curr != -1)
	{
		path.push_back(curr);
		curr = prev[curr];
	}

	reverse(path.begin(), path.end());
	return path;
}

};
