#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int heap[100000], heap_size=0;
int peek(){return heap[0];}
void hup(int nod){
    int parent = (nod-1) /2;
    while(parent > 0){
        parent = (nod-1) /2;
        if (heap[parent] > heap[nod]){
            swap(heap[parent], heap[nod]);
            nod = parent;
        }else{
            break;
        }
    }   

}
void hdown(int nod){
    while(2 * nod +1 < heap_size){
        int lc= 2 * nod +1;
        int rc = 2 * nod +2;
        int largest = nod;

        if (heap[lc] < heap [largest]){
            largest = lc;
        }
        if (rc < heap_size && heap[rc] < heap[largest]){
            largest = rc;
        }

        if (nod != largest){
            swap(heap[nod], heap[largest]);
            nod = largest;
        }else{
            break;
        }
    }
};
void insert(int nod){
    heap[heap_size] = nod;
    heap_size+=1;
    hup(heap_size-1);
}
int extract(){
    int val = heap[0];
    heap[0] = heap[heap_size-1];
    heap_size--;
    hdown(0);
    return val;
}


void build(){
    int last_parent = (heap_size-2) / 2;
    for(int i = last_parent; i>=0; i--){
        hdown(i);
    }
}
int main() {
    int n;
    cin>>n;
    for(int i = 0 ; i< n; i ++){
        int x;
        cin>>heap[i];
        heap_size++;
    }

    build();
    int steps = 0;
    while (heap_size > 1){
        int first = 0, second = 0;
        if(heap_size > 0) {
            first = extract();
        }
        if(heap_size > 0) {
            second = extract();
        }
        steps += first + second;
        insert(first + second);
    }
    /*
    while(!pq.empty()){
        cout<<pq.top()<<" ";
        pq.pop();
    }
    */
   cout<<steps;
}
