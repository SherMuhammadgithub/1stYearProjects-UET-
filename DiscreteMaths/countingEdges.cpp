#include <iostream>

using namespace std;

// Function to extract edges and count occurrences
bool checkEdge(int i, int j, int edgeCountr[], int edgeCountc[], int edgeCounter)
{
    for (int k = 0; k < edgeCounter; ++k)
    {
        if ((edgeCountr[k] == i && edgeCountc[k] == j) || (edgeCountr[k] == j && edgeCountc[k] == i))
        {
            return false;
        }
    }
    return true;
}
int edgeListFromAdjacencyMatrix(int adjMatrix[][4], int numVertices, int edges)
{
    int edgeCounter = 0;
    int edgeCountr[10], edgeCountc[10];
    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = 0; j < numVertices; ++j)
        {
            if (adjMatrix[i][j] != 0)
            {
                if (checkEdge(i, j, edgeCountr, edgeCountc, edgeCounter))
                {
                    edges += adjMatrix[i][j];
                    cout << "Edge " << edgeCounter + 1 << " - "
                         << " occurs " << adjMatrix[i][j] << " times" << endl;
                    edgeCountr[edgeCounter] = i;
                    edgeCountc[edgeCounter] = j;
                    edgeCounter++;
                    break;
                }
            }
        }
    }
    return edges;
}

int main()
{
    // Example adjacency matrix
    int adjacencyMatrix[4][4] = {
        {0, 0, 0, 4},
        {0, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}};
    int edgeCount = 0;
    int toatlEdges = edgeListFromAdjacencyMatrix(adjacencyMatrix, 4, edgeCount);
    cout << "Total edges are: " << toatlEdges << endl;
    return 0;
}