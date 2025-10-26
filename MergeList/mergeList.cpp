#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummyhead;
        ListNode* curr = &dummyhead;
    
        while(list1 != nullptr && list2 != nullptr) {
            int x = 0;
            if(list1 -> val < list2 -> val) {
                x = list1 -> val;
                list1 = list1 -> next;
            }
            else{
                x = list2 -> val;
                list2 = list2 -> next;
            }

            ListNode node(x);
            curr -> next = &node;
            curr = curr -> next;
        }

        return dummyhead.next;
    }
};


int main() {
    Solution s;
    vector<int> h = {0,1,0,2,1,0,1,3,2,1,2,1};
    
    cout << "trapped water: " << s.trap(h);

    return 0;
}