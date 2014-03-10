#ifndef GRAPH_H
#define GRAPH_H
/*
 * graph.h: David R. Morrison, Sept. 2013
 *
 * Class that encompasses all of the graph data for the graph visualization software; the graph
 * class can read from a variety of different file types, or from an adjacency matrix or adjacency
 * list.
 */

#include <vector>
#include <memory>
#include <string>
#include <map>

namespace graph
{

enum GraphType { SimpleUndirected, SimpleDirected };

struct VertexData
{
	// Information about the vertex
	std::string name;

	// Positioning information
	int x, y;
	int radius;

	virtual VertexData* clone() { return new VertexData(*this); }
	virtual ~VertexData() { }
};

class Graph
{

public:

	// Constructors, assignment operator, destructor
	Graph(GraphType type = SimpleUndirected);
	Graph(const Graph& g);
	Graph& operator=(Graph g);
	void swap(Graph& g) { using std::swap; swap(theImpl, g.theImpl); }
	~Graph();

	void addVertex(int u);
	void addEdge(int u, int v);
	void delVertex(int u);
	void delEdge(int u, int v);
	bool hasEdge(int u, int v) const;

	VertexData* const setVertexData(int u, VertexData* data);
	VertexData* const vertexData(int u);

	// Global graph properties
	int order() const;
	int size() const;
	bool isDirected() const;
	bool isSimple() const;
	bool isWeighted() const;

	void setType(GraphType t);
	GraphType type() const;

	// Vertex properties
	std::vector<int> neighbors(int u) const;
	int degree(int u) const;
	int outdegree(int u) const;
	int indegree(int u) const;

	void setSource(int s);
	void setSink(int t);
	int source() const;
	int sink() const;


private:
	class Impl;
	//std::unique_ptr<Impl> theImpl;
	Impl* theImpl;

public:
	// Iterators
	typedef std::map<int, std::vector<int>>::const_iterator graph_iterator;
	graph_iterator begin() const;
	graph_iterator end() const;
};


}; // namespace graph 

#endif // GRAPH_H
