#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<vector<int>> vect;
vector<vector<bool>> u;

void DFS(int i, int j)
{
    if (i>=0 && j>=0 && i < vect.size() && j < vect[0].size() && !u[i][j] && vect[i][j] == 1)
    {
        u[i][j] = true;
        DFS(i - 1, j);
        DFS(i, j - 1);
        DFS(i + 1, j);
        DFS(i, j + 1);
    }
}


int main() 
{
    int N, M, count = 0;
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        vector<int> tmp;
        vector<bool> tmpU;
        for (int j = 0; j < M; j++)
        {
            int a;
            cin >> a;
            tmp.push_back(a);
            tmpU.push_back(false);
        }
        vect.push_back(tmp);
        u.push_back(tmpU);
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (vect[i][j] == 1 && !u[i][j])
            {
                count++;
                DFS(i, j);
            }
        }
    }
    cout << count;
    return 0;
}