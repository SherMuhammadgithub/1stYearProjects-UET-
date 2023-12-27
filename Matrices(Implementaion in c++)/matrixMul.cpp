#include <iostream>
using namespace std;
#define MAX_SIZE 100
void printMatrix(int finalResult[MAX_SIZE][MAX_SIZE], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << finalResult[i][j] << " ";
        }
        cout << endl;
    }
}
void multiplyMatrix(int matrix1[MAX_SIZE][MAX_SIZE], int rows1, int cols1, int matrix2[MAX_SIZE][MAX_SIZE], int rows2, int cols2)
{
    int finalResult[MAX_SIZE][MAX_SIZE] = {0};
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            for (int k = 0; k < cols1; k++)
            {
                finalResult[i][j] += matrix1[i][k] * matrix2[k][j]; // i = 0; j = 1
            }
        }
    }
    printMatrix(finalResult, rows1, cols2);
}
main()
{
    int rows1 = 3;
    int cols1 = 4;
    int rows2 = 4;
    int cols2 = 3;
    int matrix1[MAX_SIZE][MAX_SIZE] = {
        {1, 2, 3, 4},
        {1, 2, 1, 3},
        {1, 1, 1, 1}};
    int matrix2[MAX_SIZE][MAX_SIZE] = {
        {3, 1, 2},
        {1, 2, 4},
        {1, 6, 7},
        {1, 6, 1}};
    cout << "Matrix 1" << endl;
    printMatrix(matrix1, rows1, cols1);
    cout << "Matrix 2" << endl;
    printMatrix(matrix2, rows2, cols2);
    cout << "Multiplied Matrix is: " << endl;
    multiplyMatrix(matrix1, rows1, cols1, matrix2, rows2, cols2);
}