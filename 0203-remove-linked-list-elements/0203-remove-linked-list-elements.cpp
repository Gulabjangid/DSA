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
    ListNode* removeElements(ListNode* head, int value) {

        // Step 1: remove from beginning
        while (head != NULL && head->val == value) {
            head = head->next;
        }

        ListNode* curr=head;

        while(curr!=NULL && curr->next!=NULL){
            if(curr->next->val==value){
                curr->next=curr->next->next;
            }
            else{
                curr=curr->next;
            }

        }
        return head;
    }
};