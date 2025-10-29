#include<iostream>
#include<stack>
#include <vector>
using namespace std;
 struct ListNode {
         int val;
         ListNode *next;
         ListNode() : val(0), next(nullptr) {}
         ListNode(int x) : val(x), next(nullptr) {}
         ListNode(int x, ListNode *next) : val(x), next(next) {}
     };
int main()
{
    ListNode* head = new ListNode(2);
    head->next = new ListNode(1);
    head->next->next = new ListNode(5);
    auto curr = head;
    int n = 0;
    while(curr){
        n+=1;
        curr = curr->next;
    }
    vector<int> rez(n, 0);
    stack<pair<int, int>> s;
    curr = head;
    int i =0;
    while(curr){
        if (s.empty())
            s.push({curr->val, i});
        else{
            while(!s.empty() && curr->val >= s.top().first){
                if (curr->val == s.top().first)
                rez[s.top().second] = 0;
                else
                rez[s.top().second] = curr->val;
                s.pop();
            }
            s.push({curr->val, i});            

        }
        curr= curr->next;
        i++;
    }
    
    for (int i =0; i<n; i++){
        cout<<rez[i]<<" ";
    }
    return 0;
}