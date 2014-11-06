#ifndef GRAPH_SEARCH_H
#define GRAPH_SEARCH_H

/* 
 * graph_search.h: David R. Morrison, 2014
 *
 * Functions for searching in a graph (shortest path, etc)
 *
 */

#include "graph.h"
#include <vector>

namespace graph
{

// An implementation of Dijkstra's shortest path algorithm from source to sink in an 
// unweighted graph g
std::vector<int> shortestPath(const Graph& g, int source, int sink);

};

#endif // GRAPH_SEARCH_H
