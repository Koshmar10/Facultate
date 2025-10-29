#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

ifstream fin("listavecini.in");
ofstream fout("listavecini.out");

int main()
{
    vector<pair<int, vector<int>>> adj_list;

    int n, x, y;
    fin >> n;
    while (fin >> x >> y)
    {

        bool x_exists = false;
        bool y_exists = false;
        for (auto &item : adj_list)
        { // <-- by reference
            if (x == item.first)
            {
                x_exists = true;

                bool y_exists = false;
                for (auto &v : item.second)
                {
                    if (v == y)
                    {
                        y_exists = true;
                                        }
                }

                if (!y_exists)
                    item.second.push_back(y);
                // <-- stop searching
            }
            x_exists = false;
            y_exists = false;
            if (y == item.first)
            {
                y_exists = true;

                bool x_exists = false;
                for (auto &v : item.second)
                {
                    if (v == x)
                    {
                        x_exists = true;
                        break;
                    }
                }

                if (!x_exists)
                    item.second.push_back(x);
            }
        }

        if (!x_exists)
        {
            adj_list.push_back({x, {y}}); // create x with first neighbor y
        }
    }

    // Output (use fout since you opened it)
    for (auto &p : adj_list)
    {
        sort(p.second.begin(), p.second.end());
        fout << p.second.size();

        for (auto &v : p.second)
            fout << ' ' << v;
        fout << '\n';
    }
    return 0;
}
