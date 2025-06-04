#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream in("in.txt");

int parent(int poz) { return (poz - 1) / 2; }

int left(int poz) { return 2 * poz + 1; }

int right(int poz) { return 2 * poz + 2; }



void heapifyUp(pair<int, int> h[], int n, int poz) {
    int p = parent(poz);

    if (p >= 0 && h[poz].first < h[p].first) {
        swap(h[poz], h[p]);
        heapifyUp(h, n, p);
    }
}

void push(pair<int, int> h[], int &n, pair<int, int> val) {
    h[n] = val;
    n++;
    heapifyUp(h, n, n - 1);
}

void heapifyDown(pair<int, int> h[], int n, int poz) {
    int minIndex = poz;
    int l = left(poz);
    int r = right(poz);

    if (l < n && h[minIndex].first > h[l].first) {
        minIndex = l;
    }
    if (r < n && h[minIndex].first > h[r].first) {
        minIndex = r;
    }
    if (minIndex != poz) {
        swap(h[poz], h[minIndex]);
        heapifyDown(h, n, minIndex);
    }
}
pair<int, int> extractMin(pair<int, int> h[], int &n) {
    pair<int, int> val = h[0];
    swap(h[0], h[n - 1]);
    n -= 1;
    heapifyDown(h, n, 0);
    return val;
}
void buildheap(pair<int, int> h[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) { // Start from the last non-leaf node
        heapifyDown(h, n, i);
    }
}

int main() {
    int n, k, mcnt=0;
    pair<int, int> minHeap[20];
    in >> k;
    vector<pair<vector<int>, int>> arraysToMerge;
    vector<int> mergedArray;
    for (int i = 0; i < k; i++) {
        vector<int> v;
        in >> n;
        int nc = n;
        while (nc) {
            int tmp;
            in >> tmp;
            v.push_back(tmp);
            nc--;
        }
        if (!v.empty()) {
            mcnt+=n;
            pair<vector<int>, int> x = {v, n};
            arraysToMerge.push_back(x);
            for (auto i : x.first) {
                cout << i << " ";
            }
            cout << "\n";
            cout << x.second << "\n";
        }
    }
    int i = 0;
    for (auto v: arraysToMerge){
        minHeap[i] = {v.first[0], i};
        i++;
    }
    // Example heap with pairs
    buildheap(minHeap, k);
    for (int i = 0; i < k; i++) {
        cout << "(" << minHeap[i].first << ", " << minHeap[i].second << ") ";
    }
    cout << "\n";
    for(int i =0; i<mcnt; i++){
        pair<int,int> valueToBeAded;
        valueToBeAded = extractMin(minHeap, k);
        mergedArray.push_back(valueToBeAded.first);
        pair<int,int>nextElement;
        if (arraysToMerge[valueToBeAded.second].second > 1) {
            int currentIndex = arraysToMerge[valueToBeAded.second].first.size() - arraysToMerge[valueToBeAded.second].second;
            nextElement = {arraysToMerge[valueToBeAded.second].first[currentIndex + 1], valueToBeAded.second};
            arraysToMerge[valueToBeAded.second].second--;
            push(minHeap, k, nextElement);
        }
    }
    for (auto val : mergedArray) {
        cout << val << " ";
    }
    cout << "\n";

    return 0;
}