#include<iostream>
#include "../include/Stack.hpp"
#include "../include/LinkedList.hpp"
using namespace std;
int main()
{
    Stack<string> s;
    s.push("salut");
    s.push("buna");
    s.push("hola");
    s.pop();
    s.print();
    cout<<s.getTos()->getValue()<<"\n";
    cout<<s.size();
    cout<<"\n";
    LinkedList<int> l;
    l.appendBack(2);
    l.appendBack(3);
    l.printList();

    return 0;
}