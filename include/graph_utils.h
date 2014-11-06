/*
 * graph_utils.h: David R. Morrison, Sept. 2013
 *
 * Utility functions for the graph class
 */

#include <vector>

namespace graph
{

class Graph;

double density(const Graph& g);
bool testIndSet(const Graph& g, const std::vector<int>& set);
bool testClique(const Graph& g, const std::vector<int>& set);
Graph complement(const Graph& g);
std::vector<int> getReachable(const Graph& g, const std::vector<int>& start);

}; // namespace graph

