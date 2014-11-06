#ifndef GRAPH_LAYOUT_H
#define GRAPH_LAYOUT_H
/*
 * graph_layout.h: David R. Morrison, Oct. 2013
 *
 * Contains different functions and algorithms for computing drawings of various types of graphs.
 * Right now I just have algorithms for trees, perhaps eventually more complicated graphs will be
 * supported.  Some algorithms here are from the Handbook of Graph Drawing and Visualization (2013),
 * ed. Tamassia.
 */


#include <map>
#include <utility>

typedef std::map<int, std::pair<int, int>> GraphLayout;

namespace graph
{
	class Graph;

	// The level-based recursive approach described in HGDV; this function assumes that the graph is
	// a tree, and that the root of the tree has node id 0.  For simplicity, it also assumes that
	// the graph is directed (so that arcs point from parent to child).  Undefined behavior results
	// if these assumptions are violated.
	GraphLayout layoutTreeLevel(const Graph& g, int rootX, int rootY, int radius, 
			int vSpace, int hSpace);

}; // namespace graph

#endif // GRAPH_LAYOUT_H


