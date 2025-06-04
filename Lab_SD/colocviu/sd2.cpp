#include<iostream>
#include <queue>
#include <cmath>
using namespace std;

int n,k,x;

class Comparator{
    public:

    bool operator()(int a, int b){
        return abs(a-x) < abs(b-x) || (abs(a-x) == abs(b-x) && a< b);
    };
};
priority_queue<int, vector<int>, Comparator> pq;
int main()
{
    cin>>n>>k>>x;
    for(int i =0; i<n; i++){
        int y;
        cin>>y;
        pq.push(y);
    }
    for (int i=0; i<k; i++){
        if (!pq.empty()){
            cout<<pq.top()<<" ";
            pq.pop();
        }
    }
    return 0;
}