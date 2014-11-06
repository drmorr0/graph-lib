// graph_layout.cpp: David R. Morrison
// Implementations of various graph drawing algorithms

#include "graph.h"
#include "graph_layout.h"

#include <list>
#include <map>

using namespace std;

namespace graph
{

struct Point { int x, y; };
struct SubtreeBlock { int width, rootX; };

namespace params { int vSpace, hSpace, radius; };

SubtreeBlock computeSubtreeLayout(const Graph& g, int rId, map<int, Point>& relVertexPos) 
{
	vector<int> n = g.neighbors(rId);

	// Base case -- we have no children, so our span is just the width of the single node
	if (n.size() == 0) return { 2 * params::radius, params::radius };

	// Loop through all the neighbors and recursively compute a layout for them
	int width = 0;
	for (int i = 0; i < n.size(); ++i)
	{
		int child = n[i];
		SubtreeBlock block = computeSubtreeLayout(g, child, relVertexPos);

		// The x-coordinate is just the position of the root in the sub-block plus the width
		// of the current block
		relVertexPos[child].x = (width + block.rootX);
		relVertexPos[child].y = params::vSpace;

		// Increase the width of the current block; if this isn't the last subtree, add in spacing
		width += block.width;
		if (i != n.size() - 1) width += params::hSpace;
	}

	// Always place the root halfway across the block, then normalize the x-coordinates to be
	// relative to the root position
	int rootX = width / 2;
	for (int i = 0; i < n.size(); ++i)
		relVertexPos[n[i]].x -= rootX;

	return { width, rootX };
}

GraphLayout layoutTreeLevel(const Graph& g, int rootX, int rootY, int radius, int vSpace, int hSpace)
{
	// Initialize a map of vertex positions relative to the vertex's parent; i.e.,
	// relVertexPos[i].x is the position of vertex i relative to the parent of i
	map<int, Point> relVertexPos;

	params::hSpace = hSpace;
	params::vSpace = vSpace;
	params::radius = radius;

	// Compute the subtree layout in terms of relative vertex positions
	computeSubtreeLayout(g, 0, relVertexPos);

	// Translate relative positions into absolute positions using breadth-first search
	list<int> queue{0};
	GraphLayout layout;
	layout[0].first = rootX;
	layout[0].second = rootY;
	while (!queue.empty())
	{
		int currNode = queue.front(); queue.pop_front();
		vector<int> n = g.neighbors(currNode);
		for (int i = 0; i < n.size(); ++i)
		{
			int child = n[i];
			layout[child].first = layout[currNode].first + relVertexPos[child].x;
			layout[child].second = layout[currNode].second + relVertexPos[child].y;
			queue.push_back(child);
		}
	}

	return layout;
}

}; // namespace graph





