# 0203-remove-linked-list-elements

## 📋 Problem Description
Given the `head` of a singly linked list and an integer `val`, the task is to remove all nodes from the linked list whose `Node.val` is equal to `val`. After removing all such nodes, the function should return the head of the modified linked list.

The function receives:
*   `head`: A pointer to the first node of the linked list.
*   `val`: An integer value to be removed from the list.

The function must return:
*   A `ListNode*` representing the head of the new, modified linked list.

## 🔍 Examples
```
Input: head = [1,2,6,3,4,5,6], val = 6
Output: [1,2,3,4,5]
Explanation: All nodes with value 6 are removed.
```

```
Input: head = [], val = 1
Output: []
Explanation: The input list is empty, so the output is also an empty list.
```

```
Input: head = [7,7,7,7], val = 7
Output: []
Explanation: All nodes have the value 7, so the entire list is removed, resulting in an empty list.
```

## 📌 Constraints
*   The number of nodes in the list is in the range `[0, 10^4]`.
*   `1 <= Node.val <= 50`
*   `0 <= val <= 50`

## 🤔 Understanding the Problem
The problem asks us to filter a linked list, keeping only nodes whose values do not match a given `val`. This is non-trivial because removing a node in a linked list involves changing the `next` pointer of the *previous* node to bypass the current node. Special care must be taken if the head node itself needs to be removed, or if multiple consecutive nodes need to be removed. An empty list or a list where all nodes match `val` are important edge cases.

## 💡 Core Idea
The core idea is to iterate through the linked list and, for each node, check if its *next* node's value matches `val`. If it does, we "skip" the next node by re-pointing the current node's `next` pointer to the node *after* the one being removed. A separate initial pass is needed to handle cases where the head node itself (or multiple initial nodes) matches `val`.

## 🧠 Approach — Iterative Traversal with Two Pointers (Implicit)
This problem can be solved using an iterative traversal approach, which implicitly uses a form of two pointers (a `current` pointer and effectively looking at `current->next`). This pattern fits because we need to modify the structure of a linked list by changing `next` pointers. By maintaining a pointer to the *previous* valid node, we can easily bypass any node that needs to be removed. The key is to always operate on `temp->next` rather than `temp` itself when considering removal, as we need the `temp` node to modify its `next` pointer.

## 📝 Step-by-Step Algorithm
1.  **Handle initial matching nodes**: First, iterate from the `head` of the list. As long as the `head` is not `NULL` and its value is equal to `val`, advance the `head` pointer to `head->next`. This effectively removes all leading nodes that match `val` and updates the true start of the list.
2.  **Initialize a traversal pointer**: Create a temporary pointer, let's call it `temp`, and initialize it to the (potentially new) `head` of the list. This `temp` pointer will be used to traverse the rest of the list.
3.  **Traverse and remove**: While `temp` is not `NULL` and `temp->next` is not `NULL`:
    *   Check if the value of the node *after* `temp` (i.e., `temp->next->val`) is equal to `val`.
    *   If `temp->next->val` *is* equal to `val`:
        *   Remove the `temp->next` node by updating `temp->next` to point to `temp->next->next`. This effectively skips over the node that needs to be removed. Note that `temp` itself does not advance in this case, as the *new* `temp->next` might also need to be removed.
    *   If `temp->next->val` *is not* equal to `val`:
        *   Advance `temp` to `temp->next`. This moves `temp` to the next node in the list, as the current `temp->next` node is valid and should be kept.
4.  **Return the new head**: After the loop finishes, return the final `head` pointer. This will be the head of the modified linked list.

## 💻 Solution
```cpp
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

        // Step 1: Handle initial nodes that match 'value'.
        // This loop continues as long as the head is not NULL
        // and the head's value matches the 'value' to be removed.
        // It effectively moves the 'head' pointer past all leading nodes
        // that need to be removed.
        while(head != NULL && head->val == value){
            head = head->next;
        }

        // Step 2: Initialize a temporary pointer for traversal.
        // 'temp' will traverse the list starting from the (potentially new) head.
        ListNode* temp = head;

        // Step 3: Traverse the rest of the list and remove matching nodes.
        // The loop continues as long as 'temp' is not NULL (meaning we haven't reached the end)
        // and 'temp->next' is not NULL (meaning there's at least one node ahead to check).
        while(temp != NULL && temp->next != NULL){
            // Check if the next node's value matches the 'value' to be removed.
            if(temp->next->val == value){
                // If it matches, remove 'temp->next' by bypassing it.
                // 'temp->next' is updated to point to the node after 'temp->next'.
                // Effectively, temp->next is now temp->next->next.
                // 'temp' itself does not advance here because the new 'temp->next'
                // might also need to be removed (e.g., [1,6,6,2], val=6).
                temp->next = temp->next->next;
            }
            else{
                // If the next node's value does not match 'value',
                // it means 'temp->next' is a valid node that should be kept.
                // So, we advance 'temp' to the next node to continue traversal.
                temp = temp->next;
            }
        }
        
        // Step 4: Return the (possibly updated) head of the modified list.
        return head;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The algorithm iterates through the linked list once. In the worst case, every node is visited. |
| **Space** | O(1) | Only a few extra pointers (`head`, `temp`) are used, regardless of the input list size. |

## 🔗 Related Problems
- 206. Reverse Linked List
- 83. Remove Duplicates from Sorted List
- 19. Remove Nth Node From End of List