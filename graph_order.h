/*
 * graph_order.h: David R. Morrison, Sept. 2013
 *
 * Vertex-ordering functions for the Graph class
 */

#include <vector>

namespace graph
{

	std::vector<int> identityVertexOrder(const Graph& g);
	std::vector<int> randomVertexOrder(const Graph& g);
	std::vector<int> degreeListVertexOrder(const Graph& g);
	std::vector<int> outdegreeListVertexOrder(const Graph& g);
	std::vector<int> indegreeListVertexOrder(const Graph& g);
	std::vector<int> degreeSequence(const Graph& g);
	std::vector<int> outdegreeSequence(const Graph& g);
	std::vector<int> indegreeSequence(const Graph& g);

}; // namespace graph



