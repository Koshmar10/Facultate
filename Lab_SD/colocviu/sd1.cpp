#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Node{
    string data;
    Node* urm;
    public:
    Node( string d = "", Node* urm=nullptr):data(d), urm(urm){}
    ~Node() {}
    string get_data() { return data;}
    void set_urm(Node* nod) {urm = nod;}
    Node* get_urm() const {return urm;}
 };
class Stack{
    Node* tos;
    public:
    Stack(Node* tos = nullptr): tos(tos) {};
    ~Stack(){
        while (tos){
            pop();
        }
    };
    
    Node* get_tos()  {return tos;}
    void push(string val){
        Node* new_node = new Node(val);
        new_node->set_urm(tos);
        tos = new_node;
    }
    void pop(){
        if (tos != nullptr){
            Node* aux = tos;
            tos = tos->get_urm();
            delete aux;
        }
    }
    void print(){
        auto head = tos;
            while(head){
                cout<<head->get_data()<<" ";
                head = head->get_urm();
            }
    }
};

int main() {
    int n;
    Stack s = Stack();
    cin>>n;
 
    for (int i=0; i <n; i++){
        string cmd, arg;
        cin>>cmd;
        if (cmd == "cd"){
            cin>>arg;
            if (arg != ".."){
                s.push(arg);
            }else{
                s.pop();
            }
        }
        if (cmd == "pwd"){
            if (auto x = s.get_tos())
            cout<<x->get_data()<<"\n";
            else 
            cout<<"/\n";
        }

    }
    
    
    return 0;
}
