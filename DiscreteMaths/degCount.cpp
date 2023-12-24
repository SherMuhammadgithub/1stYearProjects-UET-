#include <iostream>
using namespace std;
// vertices {0,1,2,3}
void printMatrix(int[][4]);
main()
{
    int adjMatrix[4][4] = {
        {0, 1, 1, 0},
        {1, 0, 0, 1},
        {2, 0, 0, 1},
        {0, 1, 1, 0}};
    cout << "Adjacency Matrix: " << endl;
    printMatrix(adjMatrix);
    // counting degree
    int degree = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (adjMatrix[i][j] != 0)
                degree += adjMatrix[i][j];
        }
        cout << "The Degree of " << i << " is: " << degree << endl;
        degree = 0; // reseting degree after one count
    }
}
void printMatrix(int matrix[][4])
{
    cout << "\t(0)\t(1)\t(2)\t(3)" << endl
         << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << "(" << i << ")";
        for (int j = 0; j < 4; j++)
        {
            cout << "\t" << matrix[i][j];
        }
        cout << endl;
    }
}
