class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy(0);
        dummy.next = head;

        ListNode* prev = &dummy; // last node before duplicates

        while (head != NULL) {

            // detect duplicate sequence
            if (head->next && head->val == head->next->val) {

                int val = head->val;

                // skip all nodes with same value
                while (head != NULL && head->val == val) {
                    head = head->next;
                }

                prev->next = head; // remove entire block
            } 
            else {
                prev = head;
                head = head->next;
            }
        }

        return dummy.next;
    }
};