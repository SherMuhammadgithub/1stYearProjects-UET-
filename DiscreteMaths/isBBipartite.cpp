#include <iostream>

using namespace std;

const int MAX_VERTICES = 100; // Assuming a maximum number of vertices

bool isBipartiteUtil(int current, int color, int graph[][MAX_VERTICES], int colors[], int numVertices)
{
    colors[current] = color; // 0
    for (int neighbor = 0; neighbor < numVertices; ++neighbor)
    {
        if (graph[current][neighbor] == 1)
        { // Assuming 1 represents an edge
            if (colors[neighbor] == -1)
            {
                if (!isBipartiteUtil(neighbor, 1 - color, graph, colors, numVertices))
                {
                    return false;
                }
            }
            else if (colors[neighbor] == color)
            {
                return false; // Two adjacent vertices have the same color, not bipartite
            }
        }
    }
    return true;
}

bool isBipartite(int graph[][MAX_VERTICES], int numVertices)
{
    int colors[MAX_VERTICES];
    fill_n(colors, MAX_VERTICES, -1); // Initialize color array with -1 (uncolored)

    for (int start = 0; start < numVertices; ++start)
    {
        if (colors[start] == -1 && !isBipartiteUtil(start, 0, graph, colors, numVertices))
        {
            return false; // If any connected component is not bipartite, the whole graph is not bipartite
        }
    }

    return true; // All connected components are bipartite
}

int main()
{
    // Example: Edges of a graph
    int graph[][MAX_VERTICES] = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}};

    // Number of vertices
    int numVertices = 4;

    // Check if the graph is bipartite
    if (isBipartite(graph, numVertices))
    {
        cout << "The graph is bipartite." << endl;
    }
    else
    {
        cout << "The graph is not bipartite." << endl;
    }
    return 0;
}
