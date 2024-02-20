#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"

bool BFS(Graph* graph, string option, int vertex, ofstream *fout);
bool DFS(Graph* graph, string option,  int vertex, ofstream *fout);
bool KWANGWOON(Graph* graph, int vertex, ofstream* fout);
bool Kruskal(Graph* graph, ofstream* fout);
bool Dijkstra(Graph* graph, string option, int vertex, ofstream* fout);    //Dijkstra
bool Bellmanford(Graph* graph, string option, int s_vertex, int e_vertex, ofstream* fout); //Bellman - Ford
bool FLOYD(Graph* graph, string option, ofstream* fout);   //FLoyd

#endif
