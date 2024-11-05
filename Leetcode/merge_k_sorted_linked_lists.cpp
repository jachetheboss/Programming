/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // remember to return a linked list!
        // Return the head of the linked list.
        // Keep temp head pointer variable.
        // I think as long as the ->val of each
        // of the pointers are sorted, it is fine
        if(lists.size() == 0){
            return nullptr;
        }
        priority_queue<int> min_heap; // default is max_heap, so negate all
                             // elements, functions the same as min_heap
        unordered_map<int, vector<int>> hm; // stores lists' indices
        for(int i = 0; i < lists.size(); ++i){
            if(lists[i] == nullptr){
                continue;
            }// else if not equal to nullptr
            if(hm.count(lists[i]->val) == false){ // guarantees min_heap
                                                // has no duplicate keys
                hm.insert({lists[i]->val, {i}});
                min_heap.push(-(lists[i]->val)); // negate
            }else{ // if true, hm contains key
                hm[lists[i]->val].push_back(i);
            }
        }
        if(min_heap.size() == 0){ // if all pointers are nullpointers
            return nullptr;
        }
        int index = hm[-(min_heap.top())].back();
        
        cout << "hm[1]" << '\n';
        cout << "smallest: " << -(min_heap.top()) << '\n';
        for(int i = 0; i < hm[-(min_heap.top())].size(); ++i){
            cout << hm[-(min_heap.top())][i] << ' ';
        }cout << "\n\n";
        
        ListNode* head = lists[index];
        cout << head->val << ' ';
        lists[index] = lists[index]->next; // a bunch of steps for a lookup. Could do all the steps once and then save in a temp variable for an even quicker O(1), smaller constant.
        // cout << lists[index]->val;
        cout << "size" << hm[-(min_heap.top())].size() << '\n';
        if(hm[-(min_heap.top())].size() == 1){ // only pointer with
                                              // particular value
            hm.erase(-(min_heap.top()));
            min_heap.pop();
        }else{
            hm[-(min_heap.top())].pop_back();
        }if(lists[index] != nullptr){
            if(hm.count(lists[index]->val) == false){
                hm.insert({lists[index]->val, {index}});
                min_heap.push(lists[index]->val);
            }else{
                hm[lists[index]->val].push_back(index);
            }
        }
        cout << "hello";
        ListNode* node = head;
        while(min_heap.size() != 0){
            // C++ bitwise operator precedence is SUPER IMPORTANT!
            // equality === is evaluated before bitwise &, so put
            // parenthesis around biwise AND expression first if want so!
            index = hm[-(min_heap.top())].back();
            int key = -(min_heap.top());
            cout << "hello";
            ListNode* next_node = lists[index];
            node->next = next_node;
            node = node->next;
            lists[index] = lists[index]->next;
            
            // cout << "hello";
            
            if(hm[key].size() == 1){
                hm.erase(key);
                min_heap.pop();
            }else{
                hm[key].pop_back();
            }if(lists[index] != nullptr){
                if(hm.count(lists[index]->val) == false){
                    hm.insert({lists[index]->val, {index}});
                    min_heap.push(lists[index]->val);
                }else{
                    hm[lists[index]->val].push_back(index);
                }
            }
            cout << node->val << ' ';
        }
        return head;
    }
};