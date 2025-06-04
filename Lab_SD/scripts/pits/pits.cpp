#include<iostream>
using namespace std;

#include<fstream>

ifstream in("in.txt");

int main()
{
    int n, nums[1000];
    in>>n;
    for (int i =0; i <n; i++){
        in>>nums[i];
    }
    
    return 0;
}