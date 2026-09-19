#ifndef GRAPH_H
#define GRAPH_H

#define MAX 100

struct Graph
{
    int n;
    int A[MAX][MAX];
};

void InitGraph(Graph &G, int n);

void AddEdge(Graph &G, int u, int v);

void OutputGraph(Graph G);

void BuildGraph(Graph &G, int n);
#endif
