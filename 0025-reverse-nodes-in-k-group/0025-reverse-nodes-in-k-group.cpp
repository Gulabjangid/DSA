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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* temp = head;
        int count  = 0;
        
        //check if k nodes exists
        while(count<k){
            if(temp==NULL)return head;
            temp=temp->next;
            count++;
        }

        //Recursively call for the rest of the linked list
        ListNode* prevNode=reverseKGroup(temp,k);

        //reverse the linked list
        temp=head;
        count=0;

        while(count<k){
            ListNode * next=temp->next;
            temp->next=prevNode;
            prevNode=temp;
            temp=next;
            count++;
        }

        return prevNode;
    }
};