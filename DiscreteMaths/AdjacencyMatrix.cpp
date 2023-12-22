#include <iostream>
using namespace std;
void printMatrix(int[][4]);
// vertics {0,1,2,3}
main()
{
    int vertices = 4;
    cout << "No. of Vertices are: " << vertices << endl;
    int matrix[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << "Enter the adjacency of " << i << " with " << j << " or 0 if not: ";
            cin >> matrix[i][j];
        }
        cout << endl;
    }
    cout << "The Adjacency Matrix is: " << endl;
    printMatrix(matrix);
}
void printMatrix(int matrix[][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
