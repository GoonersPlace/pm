#include <stdio.h>
#include "Graph.h"
//khởi tạo ra ma trận kề
void InitGraph(Graph &G, int n)
{
    G.n = n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            G.A[i][j] = 0;
        }
    }
}
void OutputGraph(Graph G)
{
    printf("Adjacency Matrix:\n\n");

    for (int i = 0; i < G.n; i++)
    {
        for (int j = 0; j < G.n; j++)
        {
            printf("%d ", G.A[i][j]);
        }

        printf("\n");
    }
}
