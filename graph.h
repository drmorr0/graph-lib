#ifndef GRAPH_H
#define GRAPH_H
/*
 * graph.h: David R. Morrison, Sept. 2013
 *
 * Class that encompasses all of the graph data for the graph visualization software; the graph
 * class can read from a variety of different file types, or from an adjacency matrix or adjacency
 * list.
 */

#include "util.h"

#include <vector>
#include <memory>
#include <string>
#include <map>

namespace drm
{
using std::vector;
using std::string;
using std::unique_ptr;
using std::map;

enum GraphType { SimpleUndirected, SimpleDirected };
enum FileType { DIMACS, DOT, JSON_Tree };
enum BranchDir { Up, Down };

class Graph
{

public:
	
	struct VertexData
	{
		// Information about the vertex
		string name;
	};

	typedef deep_ptr<VertexData, false> VertexDataPtr;

	// Constructors, assignment operator, destructor
	Graph(GraphType type = SimpleUndirected);
	Graph(const Graph& g);
	Graph& operator=(Graph g);
	void swap(Graph& g) { using std::swap; swap(theImpl, g.theImpl); }
	~Graph();

	// Graph modification
	void addVertex(int u);
	void addEdge(int u, int v);
	void delVertex(int u);
	void delEdge(int u, int v);
	void setSource(int s);
	void setSink(int t);
	void setType(GraphType t);

	// Global graph properties
	int order() const;
	int size() const;
	bool isDirected() const;
	bool isSimple() const;
	bool isWeighted() const;
	GraphType type() const;

	// Vertex properties
	vector<int> neighbors(int u) const;
	int degree(int u) const;
	int outdegree(int u) const;
	int indegree(int u) const;
	int source() const;
	int sink() const;
	VertexDataPtr const vertexData(int u);

	// Edge properties
	bool hasEdge(int u, int v) const;

private:
	class Impl;
	//unique_ptr<Impl> theImpl;
	Impl* theImpl;

public:
	// Iterators
	typedef map<int, vector<int>>::const_iterator graph_iterator;
	graph_iterator begin() const;
	graph_iterator end() const;
};


}; // namespace drm

#endif // GRAPH_H
