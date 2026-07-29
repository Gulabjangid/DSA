/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        // Step 1: Copy the value of the next node into this node
        node->val = node->next->val;
        
        // Step 2: Keep a temporary pointer to the next node to delete it later
        ListNode* temp = node->next;
        
        // Step 3: Link the current node to skip over the next node
        node->next = node->next->next;
        
        // Step 4: Free the memory of the duplicated node
        delete temp;
    }
};