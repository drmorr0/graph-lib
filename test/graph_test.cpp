
// Testing functions for graph class

#include "graph.h"
#include "graph_utils.h"
#include "graph_order.h"
#include "graph_search.h"

#include <vector>
#include <string>

#include <unittest++/UnitTest++.h>

using namespace std;
using namespace graph;

Graph* g1;
Graph* g2;

// Make a new (empty) undirected graph and add some edges and vertices.
TEST(UndirectedGraphConstruction)
{
	g1 = new Graph(SimpleUndirected);

	g1->addEdge(1, 2);
	g1->addEdge(1, 3);
	g1->addEdge(1, 2);
	g1->addEdge(2, 3);
	g1->addEdge(1, 4);
	g1->addVertex(7);

	CHECK(g1->order() == 5);
	CHECK(g1->size() == 4);
	CHECK(density(*g1) == 4.0 / 10);
	CHECK((g1->neighbors(1) == vector<int>{ 2, 3, 4 }));
	CHECK((g1->neighbors(2) == vector<int>{ 1, 3 }));
	CHECK((g1->neighbors(3) == vector<int>{ 1, 2 }));
	CHECK((g1->neighbors(4) == vector<int>{ 1 }));
	CHECK(g1->neighbors(7) == vector<int>());
	CHECK(g1->degree(1) == 3);
	CHECK(g1->indegree(1) == 3);
	CHECK(g1->outdegree(1) == 3);
}

TEST(ShortestPath)
{
	CHECK((shortestPath(*g1, 4, 3) == vector<int> { 4, 1, 3 }));
	CHECK((shortestPath(*g1, 3, 3) == vector<int>{ 3 }));
	CHECK(shortestPath(*g1, 7, 3) == vector<int>());
}

TEST(UndirectedGraphComplement)
{
	Graph gc1 = complement(*g1);
	CHECK((gc1.neighbors(1) == vector<int>{ 7 }));
	CHECK((gc1.neighbors(2) == vector<int>{ 4, 7 }));
	CHECK((gc1.neighbors(3) == vector<int>{ 4, 7 }));
	CHECK((gc1.neighbors(4) == vector<int>{ 2, 3, 7 }));
	CHECK((gc1.neighbors(7) == vector<int>{ 1, 2, 3, 4 }));
}

TEST(DirectedGraphConstruction)
{
	g2 = new Graph(SimpleDirected);

	g2->addEdge(1, 2);
	g2->addEdge(1, 3);
	g2->addEdge(1, 2);
	g2->addEdge(2, 3);
	g2->addEdge(3, 2);
	g2->addEdge(1, 4);
	g2->addVertex(7);
	g2->addEdge(7, 4);

	CHECK(g2->order() == 5);
	CHECK(g2->size() == 6);
	CHECK(density(*g2) == 6.0 / 20);
	CHECK((g2->neighbors(1) == vector<int>{ 2, 3, 4 }));
	CHECK((g2->neighbors(2) == vector<int>{ 3 }));
	CHECK((g2->neighbors(3) == vector<int>{ 2 }));
	CHECK(g2->neighbors(4) == vector<int>());
	CHECK((g2->neighbors(7) == vector<int>{ 4 }));
	CHECK(g2->degree(3) == 1);
	CHECK(g2->indegree(4) == 2);
	CHECK(g2->outdegree(4) == 0);
}

TEST(DirectedGraphComplement)
{	
	Graph gc2 = complement(*g2);

	CHECK((gc2.neighbors(1) == vector<int>{ 7 }));
	CHECK((gc2.neighbors(2) == vector<int>{ 1, 4, 7 }));
	CHECK((gc2.neighbors(3) == vector<int>{ 1, 4, 7 }));
	CHECK((gc2.neighbors(4) == vector<int>{ 1, 2, 3, 7 }));
	CHECK((gc2.neighbors(7) == vector<int>{ 1, 2, 3 }));
}

TEST(IndependentSets)
{
	vector<int> set1{7, 4, 2};
	vector<int> set2{7, 3};
	vector<int> set3{1, 4, 7};

	CHECK(testIndSet(*g1, set1));
	CHECK(testIndSet(*g1, set2));
	CHECK(!testIndSet(*g1, set3));
}

TEST(Cliques)
{
	vector<int> set1{1, 4, 3};
	vector<int> set2{1, 2, 3};

	CHECK(!testClique(*g1, set1));
	CHECK(testClique(*g1, set2));
}

TEST(VertexOrderings)
{
	Graph gc1 = complement(*g1);

	CHECK((identityVertexOrder(gc1) == vector<int>{1, 2, 3, 4, 7}));
	CHECK((degreeListVertexOrder(gc1) == vector<int>{7, 4, 2, 3, 1}));
	CHECK((degreeSequence(gc1) == vector<int>{4, 3, 2, 2, 1}));
}

TEST(VertexOrderings2)
{
	CHECK((identityVertexOrder(*g2) == vector<int>{1, 2, 3, 4, 7}));
	CHECK((outdegreeListVertexOrder(*g2) == vector<int>{1, 2, 3, 7, 4}));
	CHECK((indegreeListVertexOrder(*g2) == vector<int>{2, 3, 4, 1, 7}));
	CHECK((outdegreeSequence(*g2) == vector<int>{3, 1, 1, 1, 0}));
	CHECK((indegreeSequence(*g2) == vector<int>{2, 2, 2, 0, 0}));
}

TEST(DeleteVertexAndEdgeUndirected)
{
	g1->delEdge(1, 2);
	g1->delEdge(1, 2);
	g1->delVertex(4);
	g1->delVertex(8);

	CHECK(g1->order() == 4);
	CHECK(g1->size() == 2);
	CHECK(density(*g1) == 2.0 / 6);
	CHECK((g1->neighbors(1) == vector<int>{ 3 }));
	CHECK((g1->neighbors(2) == vector<int>{ 3 }));
	CHECK((g1->neighbors(3) == vector<int>{ 1, 2 }));
	CHECK(g1->neighbors(4) == vector<int>());
	CHECK(g1->neighbors(7) == vector<int>());
}

TEST(DeleteVertexAndEdgeDirected)
{
	g2->delEdge(3, 2);
	g2->delEdge(3, 2);
	g2->delVertex(4);

	CHECK(g2->order() == 4);
	CHECK(g2->size() == 3);
	CHECK(density(*g2) == 3.0 / 12);
	CHECK((g2->neighbors(1) == vector<int>{ 2, 3 }));
	CHECK((g2->neighbors(2) == vector<int>{ 3 }));
	CHECK(g2->neighbors(3) == vector<int>());
	CHECK(g2->neighbors(4) == vector<int>());
	CHECK(g2->neighbors(7) == vector<int>());
}

TEST(CopyAssignment)
{
	Graph gCopy(*g1);
	gCopy.addEdge(1, 2);

	Graph gAssign = *g1;
	gAssign.addEdge(7, 3);

	CHECK(gCopy.hasEdge(1, 2));
	CHECK(gCopy.hasEdge(2, 3));
	CHECK(gCopy.hasEdge(1, 3));
	CHECK(!g1->hasEdge(1, 2));
	CHECK(gAssign.hasEdge(7, 3));
	CHECK(gAssign.hasEdge(3, 2));
	CHECK(gAssign.hasEdge(3, 1));
	CHECK(!g1->hasEdge(7, 3));
}


TEST(Destruction)
{
	// Succeeds if both graphs are successfully deleted
	delete g1;
	delete g2;
}

int main(int argc, char* argv[])
{
	return UnitTest::RunAllTests();
	return 0;
}



