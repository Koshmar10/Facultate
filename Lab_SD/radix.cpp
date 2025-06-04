#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

vector<int> v= {60,31,2142, 152, 132};

queue<int> bk[10];

int main()
{
    int max_cifre = v[0];
    for(auto el : v){
        max_cifre=(max_cifre, el);
    }
    int cnt = 0;
    while (max_cifre!=0)
    {
        cnt +=1;
        max_cifre/=10;
    }
    cnt+=1;
    int p=1;
    for (int i =1; i <= cnt; i++)
    {
        cout<<i<<"\n";
        for(auto elem : v){
            int c = (elem / p) %10;
            bk[c].push(elem); 
        }
        p*=10;
        int j=0;
        for (auto& q : bk){
            while(!q.empty()){
                int elem = q.front();
                //cout<<elem<<" ";
                q.pop();
                v[j] = elem;
                j+=1;
            }
            //cout<<"\n";
        }
        
        
    }
    for (auto i: v){
        cout<<i<<" ";
    }
    return 0;
}