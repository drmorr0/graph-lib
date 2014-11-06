#ifndef GRAPH_IMPL_H
#define GRAPH_IMPL_H
/*
 * graph_impl.h: David R. Morrison, Sept. 2013
 *
 * Implementation class for Graph objects
 */

#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <map>

namespace std
{
template<>
void swap<graph::Graph>(graph::Graph& a, graph::Graph& b) { a.swap(b); }
}

using namespace std;

namespace graph
{

class Graph::Impl
{
public:
	
	Impl(GraphType type);
	~Impl();

	void addVertex(int u);
	void addEdge(int u, int v);
	void delVertex(int u);
	void delEdge(int u, int v);
	bool hasVertex(int u) const; 
	bool hasEdge(int u, int v) const; 

	VertexData* setVertexData(int u, VertexData* data);
	VertexData* vertexData(int u) const; 

	int order() const { return mAdjList.size(); }
	int size() const { return mNumEdges; }
	bool isDirected() const { return mType == SimpleDirected; }
	bool isSimple() const { return true; /* TODO */ }
	bool isWeighted() const { return false; /* TODO */ }

	void setType(GraphType t) { mType = t; }
	GraphType type() const { return mType; }

	vector<int> neighbors(int u) const;
	int degree(int u) const; 
	int outdegree(int u) const { return degree(u); }
	int indegree(int u) const;

	void setSource(int s) { mSource = s; }
	void setSink(int t) { mSink = t; }
	int source() const { return mSource; }
	int sink() const { return mSink; }

private:

	// Should never assign Graph::Impl
	Impl& operator=(const Impl& other);

	// Graph structure
	GraphType mType;
	map<int, vector<int>> mAdjList;
	map<int, vector<int>> mRevAdjList;
	map<int, VertexData*> mVertexData;

	int mSource, mSink;
	int mNumEdges;

	// NOTE: If more members added, make sure to update copy constructor

public:
	// Iterators
    graph_iterator begin() const { return mAdjList.cbegin(); }
    graph_iterator end() const { return mAdjList.cend(); }

	// Copy constructor -- update when new members added
	Impl(const Impl& other);
};

}; // namespace graph

#endif // GRAPH_IMPL_H
