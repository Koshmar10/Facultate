#include<iostream>
using namespace std;

#include  "../include/Stack.hpp"
#include "../include/LinkedList.hpp"

int main()
{
    int n, x;
    Stack<pair<int, int>> st;
    LinkedList<int> list;

    list.appendBack(2);
    list.appendBack(7);
    list.appendBack(4);
    list.appendBack(3);
    list.appendBack(5);
    /*
    cin >> n;
    while (n){
        cin >> x;
        list.appendBack(x);
        n--;
    }
    */
    int ngns[100] = {0}; // Initialize all elements to 0
    auto current = list.getHead();
    int i = 0;

    while (current) {
        if (!st.getTos()) {
            st.push({current->getValue(), i});
        } else if (st.getTos()->getValue().first >= current->getValue()) {
            st.push({current->getValue(), i});
        } else {
            while (!st.isEmpty() && current->getValue() > st.getTos()->getValue().first) {
                ngns[st.getTos()->getValue().second] = current->getValue();
                st.pop();
            }
        }
        current = current->getNext();
        i++;
    }

    while (!st.isEmpty()) {
        ngns[st.getTos()->getValue().second] = 0; // No greater element, set to 0
        st.pop();
    }

    // Print the results
    for (int i = 0; i < 5; i++) {
        cout << ngns[i] << " ";
    }
    cout << "\n";
    list.printList();

    return 0;
}