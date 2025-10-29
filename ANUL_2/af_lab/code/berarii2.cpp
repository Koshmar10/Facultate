#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

vector<int> viz;
vector<vector<int>> al;

int n, m, p;

ifstream in("berarii2.in");
ofstream out("berarii2.out");

void bfs(int start)
{
    queue<int> q;
    viz[start] = 1;
    q.push(start);
    while (!q.empty())
    {
        int nod_current = q.front();
        q.pop();

        for (auto i : al[nod_current])
        {
            if (!viz[i])
            {
                viz[i] = 1;
                q.push(i);
            }
        }
    }
}

int main()
{
    in >> n >> m >> p;
    al.assign(n + 1, {});
    viz.assign(n + 1, 0);
    vector<int> berarii;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        in >> x >> y;
        al[y].push_back(x);
    }
    for (int i = 0; i < p; i++)
    {
        int x;
        in >> x;
        berarii.push_back(x);
    }
    for (auto berarie : berarii)
    {
        bfs(berarie);
    }
    int count = 0;
    vector<int> neviz;
    for (int i = 1; i <= n; i++)
    {
        if (!viz[i])
        {
            count += 1;
            neviz.push_back(i);
        }
    }
    out << count << "\n";
    for (auto j : neviz)
    {
        out << j << "\n";
    }
    return 0;
}
