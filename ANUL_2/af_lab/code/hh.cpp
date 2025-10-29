#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream fin("hh.in");

bool is_constructable(int degree_count, vector<int> degrees)
{
    cout << "num of d: " << degree_count << "\n";
    vector<pair<int, int>> new_deg;

    for (int i = 0; i < degrees.size(); i++)
    {
        new_deg.push_back({degrees[i], i});
    }
    sort(new_deg.begin(), new_deg.end(), greater<>());
    int sum = 0;
    for (int i = 0; i < new_deg.size(); i++)
    {
        sum += new_deg[i].first;
        cout << new_deg[i].first << "-" << new_deg[i].second << "  ";
    }
    if (sum % 2 != 0)
    {
        return false
    }
    vector<pair<int, int>> muchii;
    while(v[i])
    cout << "\n";

    return true;
};
int main()
{
    int n, degree_count, degree; // number of degree seq
    fin >> n;
    for (int i = 0; i < n; i++)
    {
        fin >> degree_count;
        vector<int> degrees;
        for (int i = 0; i < degree_count; i++)
        {
            fin >> degree;
            degrees.push_back(degree);
        }
        is_constructable(degree_count, degrees);
    }
    return 0;
}
