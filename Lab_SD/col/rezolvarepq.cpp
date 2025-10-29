#include<iostream>
#include<queue>
using namespace std;
int main()
{
    int n;
    cin>>n;
    priority_queue<int, vector<int>, greater<int>>pq;
    for(int i = 0 ; i< n; i ++){
        int x;
        cin>>x;
        pq.push(x);
    }
    int steps = 0;
    while (pq.size() > 1){
        int first = 0, second = 0;
        if(!pq.empty()) {
            first = pq.top();
            pq.pop();
        }
        if(!pq.empty()) {
            second = pq.top();
            pq.pop();
        }
        steps += first + second;
        pq.push(first + second);
    }
    /*
    while(!pq.empty()){
        cout<<pq.top()<<" ";
        pq.pop();
    }
    */
   cout <<steps;


    return 0;
}