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
