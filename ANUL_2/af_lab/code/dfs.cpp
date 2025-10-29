#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream fin("dfs.in");
ofstream out("dfs.out");
int n, m;
vector<int> viz;
void dfs(const vector<vector<int>> &al, int nod)
{
    viz[nod] = 1;
    for (auto to : al[nod])
    {
        if (!viz[to])
        {
            dfs(al, to);
        }
    }
}
int main()
{
    fin >> n >> m;

    vector<vector<int>> al(n + 1);
    viz.assign(n + 1, 0);

    for (int i = 0; i < m; i++)
    {
        int x, y;
        fin >> x >> y;
        al[x].push_back(y);
        al[y].push_back(x);
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!viz[i])
        {
            dfs(al, i);
            cnt += 1;
        }
    }
    out << cnt;
    return 0;
}
