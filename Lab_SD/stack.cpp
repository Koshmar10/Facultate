#include <iostream>
#include <vector>

using namespace std;
class Node{
    private:
        string nodeValue;
        Node* next;
    public:
        Node(string nodeValue = "", Node* next = NULL); 
        ~Node(){}; 
        string getNodeValue();
        Node* getNext();
        void setNext(Node* newNode);
};
Node::Node(string nodeValue, Node* next){
    this->nodeValue = nodeValue;
    this->next = next;
}
string Node::getNodeValue(){
    return this->nodeValue;
}
Node* Node::getNext(){
    return this->next;
}
void Node::setNext(Node* newNode){
    this->next = newNode;
}


class Stack{
    private:
        Node* head;
        Node* last;
    public:
    Stack();
    ~Stack();
    
    string getHead();
    string getLast();
    
    void setHead(Node *newHead);
    void setLast(Node *newLast);

    void appendFront(Node *newNode);
    void appendBack(Node *newNode);
    void insertElement(Node *newNode, int poz);
    
    void pop(int value);
    void printList();

};
Stack::Stack(){
    //cout<<"lista creata";
    this->head = NULL;
    this->last = NULL;
}
string Stack::getHead(){
    return this->head->getNodeValue();
}
string Stack::getLast(){
    return this->last->getNodeValue();
}
void Stack::setHead(Node* newHead){
    this->head = newHead;
    Node* curr=this->head;
    while(curr->getNext()){curr=curr->getNext();}
    this->last = curr;
}
void Stack::setLast(Node* newLast){
    this->last = newLast;
}
void Stack::appendBack(Node* newNode){
    if (!this->head){this->setHead(newNode); return;}
    this->last->setNext(newNode);
    this->last=newNode;
}
void Stack::appendFront(Node* newNode){
    if (!this->head){this->setHead(newNode); return;}
    newNode->setNext(this->head);
    this->setHead(newNode);
}
void Stack::insertElement(Node* newNode, int poz){
    if (poz == 0){
        this->appendFront(newNode);
        return;
    }
    Node* curr = this->head;
    Node* prev = nullptr;
    while (curr && poz != 0){
        prev = curr;
        curr = curr->getNext();
        poz--;
    }
    if (!curr && poz != 0){ this->appendBack(newNode); return;} // if position is out of bounds
    newNode->setNext(curr);
    if (prev) {
        prev->setNext(newNode);
    }
    if (!curr) {
        this->last = newNode;
    }
}/*
void Stack::pop() {
    if (!this->head) return; // If the list is empty, do nothing
    Node* current = this->head;
    while( current->getNext()->getNext()){
        current = current->getNext();
    }
    this->last = current;
    current=this->head;
    while( current->getNext()){
        current = current->getNext();
    }
    delete current;
    
    
}
*/
   Stack::~Stack() {
    Node* curr = head;
    while (curr) {
        Node* next = curr->getNext();
        Node* x=curr;
        delete curr;
        curr = next;
    }
}

void Stack::printList() {
    Node* curr = this->head;
    while (curr){
        cout<<curr->getNodeValue()<<" ";
        curr = curr->getNext();
    }
    cout<<"\n";
}

int main(){

    vector<int> stack;
    vector<int> values = {10, 7, 8, 9, 11, 2, 3, 5, 1, 10, 7, 6};
    int n = values.size();
    for(int i= n-1; i>=0; i --){
        values[i]=-1;
        while(!stack.empty() && values[stack.back()]<=values[i]){
            stack.pop_back();
        }
        
    }
    
    for (auto i :values){
        cout<<i<<" ";
    }
    cout<<"\n";

    return 0;
}