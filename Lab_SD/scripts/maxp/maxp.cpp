#include<iostream>
using namespace std;
#include <fstream>
#include "../../include/Stack.hpp"

ifstream in("in.txt");

int main()
{
    Stack<int> s;
    int n, nums[1000];
    in>>n;
    for(int i=0; i<n; i++){
        in>>nums[i];
    }
    

    return 0;
}