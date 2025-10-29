#include <queue>
#include <vector>
#include <fstream>

using namespace std;

ifstream cin("data/testaf4.in");
ofstream cout("data/testaf4.out");

int n, m, q;
vector<vector<int>> al;
vector<int> dist;
vector<int> viz;
void bfs(int nod)
{
    queue<int> que;
    viz[nod] = 1;
    dist[nod] = 0;
    que.push(nod);
    while (!que.empty())
    {
        int curr = que.front();
        que.pop();
        for (auto v : al[curr])
        {
            if (!viz[v])
            {
                viz[v] = 1;
                dist[v] = dist[curr] + 1;
                que.push(v);
            }
        }
    }
}
bool has_improved(int nod, vector<int> d, int target)
{
    queue<int> q;
    q.push(nod);
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        for (int v : al[cur])
        {
            if (d[v] > d[cur] + 1)
            {
                d[v] = d[cur] + 1;
                q.push(v);
            }
        }
    }
    return d[n] < target;
}
int main()
{

    cin >> n >> m;
    al.assign(n + 1, {});
    viz.assign(n + 1, 0);
    dist.assign(n + 1, -1);

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        al[x].push_back(y);
        al[y].push_back(x);
    }
    bfs(1);
    // for (auto elem : dist)
    // {
    //     cout << elem << " ";
    // }
    cout << "\n";
    cin >> q;
    int count = 0;
    vector<int> indexes;
    for (int i = 1; i <= q; i++)
    {
        int x, y;
        cin >> x >> y;
        if (min(dist[x], dist[y]) + 1 < max(dist[x], dist[y]))
        {
            vector<int> new_dist = dist;
            bool ok = false;
            if (new_dist[x] > new_dist[y])
            {
                new_dist[x] = new_dist[y] + 1;
                ok = has_improved(x, new_dist, new_dist[n]);
            }
            else
            {
                new_dist[y] = new_dist[x] + 1;
                ok = has_improved(y, new_dist, new_dist[n]);
            }
            if (ok)
            {
                count += 1;
                indexes.push_back(i);
            }
        }
    }
    cout << count << "\n";
    for (auto i : indexes)
    {
        cout << i << " ";
    }
    return 0;
}
