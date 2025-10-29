#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

vector<vector<int>> al;
vector<int> viz;
int n, m;
ifstream fin("grarb.in");
ofstream fout("grarb.out");
int dfs(int nod)
{
    viz[nod] = 1;
    int cnt = 1;
    for (auto v : al[nod])
    {
        if (!viz[v])
            cnt += dfs(v);
    }
    return cnt;
}
int main()
{
    fin >> n >> m;
    al.assign(n + 1, {});
    viz.assign(n + 1, 0);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        fin >> x >> y;
        al[x].push_back(y);
        al[y].push_back(x);
    }
    int cc = 0;
    int n_edges = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!viz[i])
        {
            n_edges += dfs(i) - 1;
            cc += 1;
        }
    }
    fout << m - n_edges << "\n" << cc - 1;
    return 0;
}