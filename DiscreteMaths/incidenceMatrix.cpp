#include <iostream>
using namespace std;
#define V 3
void printIncidentMatrix(int incidentMatrix[][V])
{
    cout << "\t(0)\t(1)\t(2)" << endl
         << endl;
    for (int i = 0; i < V; i++)
    {
        cout << "(" << i << ")";
        for (int j = 0; j < V; j++)
        {
            cout << "\t" << incidentMatrix[i][j];
        }
        cout << endl;
    }
}
main()
{
    int incidentMatrix[V][V];
    int count = 0, input;
    for (int i = 0; i < V; i++)
    {
        for (int j = i + 1; j < V; j++)
        {
            cout << "Enter 1 if the vertex " << i + 1 << " is adjacent to vertex " << j + 1 << " else 0: ";
            cin >> input;
            if (input == 1)
            {
                for (int k = 0; k < V; k++)
                {
                    if (k == i || k == j)
                    {
                        incidentMatrix[count][k] = 1;
                    }
                    else
                    {
                        incidentMatrix[count][k] = 0;
                    }
                }
                count++;
                cout << "It is edge number " << count << endl;
            }
        }
    }
    cout << "The Incident Matrix is: " << endl;
    printIncidentMatrix(incidentMatrix);
} // namespace std;
