#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

/* Open input/output files inside main to avoid global initialization order issues */

vector<int> dist;
vector<int> viz;
vector<vector<int>> al;
int n, m, s;
void bfs(int nod_start)
{
    queue<int> q;
    viz[nod_start] = 1;
    dist[nod_start] = 0;
    q.push(nod_start);
    while (!q.empty())
    {
        int current_nod = q.front();
        q.pop();
        for (auto v : al[current_nod])
        {
            if (!viz[v])
            {
                viz[v] = 1;
                dist[v] = dist[current_nod] + 1;
                q.push(v);
            }
        }
    }
}

int main()
{
    ifstream in("./data/bfs.in");
    ofstream out("./data/bfs.out");

    in >> n >> m >> s;
    al.assign(n + 1, {});
    dist.assign(n + 1, -1);
    viz.assign(n + 1, 0);

    for (int i = 0; i < m; i++)
    {
        int x, y;
        in >> x >> y;
        al[x].push_back(y);
    }

    bfs(s);

    for (int i = 1; i <= n; i++)
    {
        out << dist[i] << " ";
    }
    out << "\n";
    return 0;
}