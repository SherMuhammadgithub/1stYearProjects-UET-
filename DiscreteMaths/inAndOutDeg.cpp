#include <iostream>
using namespace std;
#define ROWS 5
#define COLS 2
const int MAX_VERTICES = 100;

void calculateDegrees(const int edges[][2], int inDegree[], int outDegree[])
{
    // Initialize degrees
    for (int i = 0; i < ROWS; ++i)
    {
        outDegree[edges[i][0]]++; // 1 out = 1 // 1 out = 1 // 2 out = 1 // 3 out = 1 // 4 out = 1
        inDegree[edges[i][1]]++;  //  2 in = 1 //  3 in = 1 //  3 in = 2 //  1 in = 1 //  2 in = 2
    }
}

int main()
{
    int edges[ROWS][COLS] = {{1, 2},  // edge from vertex 1 to vertex 2
                             {1, 3},  // edge from vertex 1 to vertex 3
                             {2, 3},  // edge from vertex 2 to vertex 3
                             {3, 1},  // edge from vertex 3 to vertex 1
                             {4, 2}}; // edge from vertex 4 to vertex 2
    // Initialize in-degree and out-degree arrays
    int inDegree[MAX_VERTICES] = {0};
    int outDegree[MAX_VERTICES] = {0};

    // Calculate in-degree and out-degree
    calculateDegrees(edges, inDegree, outDegree);

    // Print in-degree and out-degree for each vertex
    for (int vertex = 1; vertex <= 4; ++vertex)
    {
        cout << "Vertex " << vertex << ": In-Degree = " << inDegree[vertex]
             << ", Out-Degree = " << outDegree[vertex] << endl;
    }

    return 0;
}