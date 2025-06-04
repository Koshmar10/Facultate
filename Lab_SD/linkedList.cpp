#include<iostream>
using namespace std;

class Node{
    private:
        int nodeValue;
        Node* next;
    public:
        Node(int nodeValue = 0, Node* next = NULL); 
        ~Node(){}; 
        int getNodeValue();
        Node* getNext();
        void setNext(Node* newNode);
};
Node::Node(int nodeValue, Node* next){
    this->nodeValue = nodeValue;
    this->next = next;
}
int Node::getNodeValue(){
    return this->nodeValue;
}
Node* Node::getNext(){
    return this->next;
}
void Node::setNext(Node* newNode){
    this->next = newNode;
}


class LinkedList{
    private:
        Node* head;
        Node* last;
    public:
    LinkedList();
    ~LinkedList();
    
    int getHead();
    int getLast();
    
    void setHead(Node *newHead);
    void setLast(Node *newLast);

    void appendFront(Node *newNode);
    void appendBack(Node *newNode);
    void insertElement(Node *newNode, int poz);
    
    void pop(int value);
    void printList();

};
LinkedList::LinkedList(){
    //cout<<"lista creata";
    this->head = NULL;
    this->last = NULL;
}
int LinkedList::getHead(){
    return this->head->getNodeValue();
}
int LinkedList::getLast(){
    return this->last->getNodeValue();
}
void LinkedList::setHead(Node* newHead){
    this->head = newHead;
    Node* curr=this->head;
    while(curr->getNext()){curr=curr->getNext();}
    this->last = curr;
}
void LinkedList::setLast(Node* newLast){
    this->last = newLast;
}
void LinkedList::appendBack(Node* newNode){
    if (!this->head){this->setHead(newNode); return;}
    this->last->setNext(newNode);
    this->last=newNode;
}
void LinkedList::appendFront(Node* newNode){
    if (!this->head){this->setHead(newNode); return;}
    newNode->setNext(this->head);
    this->setHead(newNode);
}
void LinkedList::insertElement(Node* newNode, int poz){
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
}
void LinkedList::pop(int value) {
    if (!this->head) return; // If the list is empty, do nothing

    Node* curr = this->head;
    Node* prev = NULL;

    while (curr && curr->getNodeValue() != value) {
        prev = curr;
        curr = curr->getNext();
    }

    if (!curr) return; // If the value is not found, do nothing

    if (curr == this->head) { // If the node to delete is the head
        this->head = this->head->getNext();
        delete curr;
        if (!this->head) this->last = NULL; // If the list becomes empty
    } else {
        prev->setNext(curr->getNext());
        if (curr == this->last) this->last = prev; // If the node to delete is the last node
        delete curr;
    }
}LinkedList::~LinkedList() {
    Node* curr = head;
    while (curr) {
        Node* next = curr->getNext();
        Node* x=curr;
        delete curr;
        curr = next;
    }
}

void LinkedList::printList() {
    Node* curr = this->head;
    while (curr){
        cout<<curr->getNodeValue()<<" ";
        curr = curr->getNext();
    }
    cout<<"\n";
}


int main()
{
    LinkedList myList = LinkedList();
    
    myList.appendBack(new Node(100, NULL));
    myList.appendFront(new Node(2000, NULL));
    myList.appendBack(new Node(1111, NULL));
    myList.insertElement(new Node(69, NULL), 4);
    myList.insertElement(new Node(69, NULL), 0);
    myList.insertElement(new Node(69, NULL), 100);
    
    myList.insertElement(new Node(100, NULL), 2);
    myList.pop(100);
    myList.printList();
    cout<<myList.getHead()<<" "<<myList.getLast()<<"\n";
    // myList.~LinkedList(); // Destructor will be called automatically
    
    return 0;
}