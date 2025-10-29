#include<iostream>

using namespace std;
class Node{
    int val;
    Node* next;
    public:
    Node(int v = 0, Node* next = nullptr): val(v), next(next){};
    ~Node(){};

    Node* get_next() {return next;}
    void set_next(Node* n) {next = n;}

    int get_value() {return val;}
};

class Stack{
    Node* tos;
    public:
    Stack(Node* tos = nullptr) : tos(tos){};
    ~Stack(){
        while(tos){
            Node* aux = tos;
            tos = tos->get_next();
            delete aux;
        }
    }
    void push(int x){
        Node* new_node = new Node(x);
        new_node->set_next(tos);
        tos = new_node;
    }
    void pop(){
        if (tos){

            Node* aux = tos;
            tos = tos->get_next();
            delete aux;
        }

    }
    void print(){
        while(tos){
            cout<<tos->get_value()<<" ";
            tos = tos->get_next();
        }
    }
    Node* get_tos() {return tos;}
};

class Heap{
    int size;
    int heap[1000];
    public:
    Heap(int size =0, int v[1000] = {}){
        size = 0;
        for (int i =0; i<1000;i++)
            heap[i] = v[i];    
        heapify();
    }
    ~Heap(){};

    void insert(int val){ heap[size] = val; heapifyUp(size); size++;}
    int extract(){
        int val = peek();
        heap[0] = heap[size-1];
        size-=1;
        heapifyDown(0);
        return val;
    }
    void heapifyUp(int i ){
        while( i > 0 ){
            int parent = (i-1)/2;
            if (heap[parent] < heap [i]){
                swap(heap[i], heap[parent]);
                i = parent;
            }else{
                break;
            }
        }
    }
    void heapifyDown(int i){

        while (2 * i + 1 < size) { // cât timp are cel puțin copilul stâng
            int left_child = 2 * i + 1;
            int right_child = 2 * i + 2;
            int largest = i;
            
            // Compar cu copilul stâng
            if (heap[left_child] > heap[largest]) {
                largest = left_child;
            }
            
            // Compar cu copilul drept (dacă există)
            if (right_child < size && heap[right_child] > heap[largest]) {
                largest = right_child;
            }
            
            // Dacă cel mai mare nu este i, fac swap
            if (largest != i) {
                swap(heap[i], heap[largest]);
                i = largest; // continuă de la copilul nou
            } else {
                break; // heap-ul este valid
            }
        }
    }
    void heapify(){
        int last_parent = (size-2)/2;
        for (int i = last_parent; i>=0; i--){
            heapifyDown(i);
        }
    }
    int peek(){ return heap[0];}
    
};

int main()
{
    Stack s;
    s.push(10);
    s.pop();
    s.pop();
    s.push(3);
    s.print();
    return 0;
}