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
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {

        ListNode* slow=head;
        ListNode* fast=head;

        // Move fast n steps ahead
        for (int i = 0; i < n; i++) {
            fast = fast->next;
        }
        // If removing the head
        if (fast == NULL) {
            return head->next;
        }
        // Traverse just before it ends
        while(fast->next!=NULL){
            fast=fast->next;
            slow=slow->next;
        }
        
        // found the element and skips the next and joins the previous element to next ka next
        slow->next=slow->next->next;

        return head;
    }
};