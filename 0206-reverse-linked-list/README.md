# 0206-reverse-linked-list

## 📋 Problem Description
Given the `head` of a singly linked list, the task is to reverse the order of its nodes. After reversing, the function should return the `head` of the newly reversed list.

A singly linked list is a linear data structure where each node contains a value and a pointer (or reference) to the next node in the sequence. The last node's pointer typically points to `nullptr` (or `NULL`).

Input: The `head` of a singly linked list.
Output: The `head` of the reversed singly linked list.

## 🔍 Examples
Example 1:
```
Input: head = [1,2,3,4,5]
Output: [5,4,3,2,1]
```

Example 2:
```
Input: head = [1,2]
Output: [2,1]
```

Example 3:
```
Input: head = []
Output: []
```

## 📌 Constraints
*   The number of nodes in the list is in the range `[0, 5000]`.
*   `-5000 <= Node.val <= 5000`

## 🤔 Understanding the Problem
The problem asks us to change the direction of all `next` pointers in a singly linked list. For instance, if we have `A -> B -> C`, after reversal, we want `A <- B <- C`, which effectively means `C` becomes the new head and points to `B`, `B` points to `A`, and `A` points to `NULL`. This is non-trivial because in a singly linked list, we can only move forward. If we change a node's `next` pointer to point backward, we lose the reference to the rest of the original list unless we save it first. Edge cases to consider include an empty list or a list with a single node; in both scenarios, the list remains unchanged after reversal.

## 💡 Core Idea
The core idea is to iterate through the linked list, and for each node, change its `next` pointer to point to the *previous* node. To safely achieve this without losing access to the rest of the list, we must temporarily store the *next* node in the original sequence before modifying the current node's `next` pointer.

## 🧠 Approach — Iterative Pointer Manipulation
This problem is a classic example of iterative pointer manipulation in linked lists. We use this pattern because we need to traverse the list sequentially and modify the `next` pointers of each node. By maintaining three pointers (`prev`, `curr`, and `next`), we can safely reverse the links one by one without losing track of the rest of the list (by saving `curr->next` in `next`) or the already reversed portion (by updating `prev`). This approach processes each node exactly once, making it efficient.

## 📝 Step-by-Step Algorithm
1.  Initialize three pointers:
    *   `prev`: This pointer will keep track of the node that was just processed and whose `next` pointer has already been reversed. Initially, there's no previous node, so set `prev = NULL`.
    *   `curr`: This pointer points to the current node being processed. Initialize `curr = head`.
    *   `next`: This is a temporary pointer that will store the `next` node of `curr` *before* `curr->next` is modified. This is crucial to maintain access to the rest of the original list.
2.  Start a loop that continues as long as `curr` is not `NULL`. This means we iterate until we have processed all nodes in the original list.
3.  Inside the loop, for each `curr` node:
    a.  **Save the next node:** Store the `next` node of `curr` in the `next` temporary pointer: `next = curr->next`. This preserves the link to the un-reversed part of the list.
    b.  **Reverse the link:** Change the `next` pointer of the `curr` node to point to the `prev` node: `curr->next = prev`. This effectively reverses the direction of the link for the current node.
    c.  **Move `prev` forward:** Update `prev` to `curr`. The current node (`curr`) now becomes the "previous" node for the next iteration, as it's now part of the reversed segment.
    d.  **Move `curr` forward:** Update `curr` to `next`. Advance `curr` to the next node in the original list (which we saved in the `next` temporary pointer).
4.  Once the loop finishes, `curr` will be `NULL` (indicating we've reached the end of the original list). At this point, `prev` will be pointing to the last node of the original list, which is now the new head of the completely reversed list.
5.  Return `prev`.

## 💻 Solution
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x, next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // 'prev' will point to the previously processed node.
        // Initially, there is no previous node, so it's NULL.
        // This pointer will eventually become the new head of the reversed list.
        ListNode* prev = NULL;

        // 'next' (used as a temporary variable) will store the next node in the original list
        // before we change 'curr->next'. This is crucial to not lose the rest of the list.
        ListNode* next = NULL;

        // 'curr' points to the current node we are processing.
        // We start from the head of the original list.
        ListNode* curr = head;

        // Iterate through the list until 'curr' becomes NULL,
        // meaning we have processed all nodes.
        while (curr != NULL) {
            // 1. Store the next node in the original list.
            // This is crucial to not lose the rest of the list after reversing curr->next.
            next = curr->next;

            // 2. Reverse the current node's 'next' pointer.
            // Make it point to the 'prev' node.
            // Example: If list is 1->2->3, and curr is 2, prev is 1.
            // curr->next (2->3) becomes curr->next (2->1).
            curr->next = prev;

            // 3. Move 'prev' one step forward.
            // The current node 'curr' now becomes the 'prev' node for the next iteration.
            // Example: prev (1) becomes prev (2).
            prev = curr;

            // 4. Move 'curr' one step forward.
            // Advance 'curr' to the node that was originally next in the list (saved in 'next').
            // Example: curr (2) becomes curr (3).
            curr = next;
        }

        // When the loop finishes, 'curr' is NULL (we've gone past the end of the original list).
        // 'prev' will be pointing to the last node of the original list,
        // which is now the new head of the reversed list.
        return prev;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the linked list once, visiting each of the N nodes exactly one time to reverse its pointer. |
| **Space** | O(1) | We only use a few constant extra pointers (`prev`, `next`, `curr`) regardless of the list's size. No additional data structures are allocated that scale with N. |

## 🔗 Related Problems
- 21. Merge Two Sorted Lists
- 141. Linked List Cycle
- 234. Palindrome Linked List