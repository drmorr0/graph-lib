#ifndef GRAPH_IO_H
#define GRAPH_IO_H
/*
 * graph_io.h: David R. Morrison
 *
 * Functions for input and output for Graphs
 */

namespace graph
{

class Graph;

Graph readDIMACS(const char* filename);
void print(const Graph& g);
void printShort(const Graph& g);

}; // namespace graph

#endif // GRAPH_IO_H

