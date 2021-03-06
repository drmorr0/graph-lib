// graph_io.cpp: David R. Morrison, Oct. 2013
// Implementation for graph input/output functions

#include "graph.h"
#include "graph_io.h"
#include "graph_utils.h"
#include "util.h"

#include <fstream>

using namespace std;

namespace graph
{

// Read in a graph from a DIMACS .col file
Graph readDIMACS(const char* filename)
{
	ifstream input(filename);
	if (!input) throw ERROR << "Unable to open file " << filename << " for reading.";
	string nextLine;

	// Read from file
	Graph g;
	while (input.good())
	{
		getline(input, nextLine);
		if (nextLine.empty()) continue;

		int node1, node2;
		char type;

		stringstream lineStr(nextLine);
		lineStr >> type;
		if (type == 'a' || type == 'e')
		{
			if (type == 'a') g.setType(SimpleDirected);
			lineStr >> node1 >> node2;
			g.addEdge(node1, node2);
			if (type == 'e') g.addEdge(node2, node1);
		}
	}

	return g;
}

/* Printing functions */
void print(const Graph& g) 
{
    for (auto i = g.begin(); i != g.end(); ++i)
    {
        printf("%d: ", i->first);
        for (int j = 0; j < i->second.size(); ++j)
            printf("%d ", i->second[j]);
        printf("\n");
    }
}

void printShort(const Graph& g) 
{
    printf("Number of nodes: %d\n", g.order());
    printf("Number of arcs: %d\n", g.size());
    printf("Density: %0.2f\n", density(g));
}



};  // namespace graph


