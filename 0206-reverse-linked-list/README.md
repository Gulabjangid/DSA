# 0206-reverse-linked-list

## 📋 Problem Description
Given the `head` of a singly linked list, the task is to reverse the order of its nodes. This means that if the original list was `A -> B -> C`, the reversed list should be `C -> B -> A`. The function should return the `head` of the newly reversed list.

**Input:** The `head` of a singly linked list.
**Output:** The `head` of the reversed singly linked list.

## 🔍 Examples
```
Input: head = [1,2,3,4,5]
Output: [5,4,3,2,1]
Explanation: The original list 1->2->3->4->5 is reversed to 5->4->3->2->1.
```

```
Input: head = [1,2]
Output: [2,1]
Explanation: The original list 1->2 is reversed to 2->1.
```

```
Input: head = []
Output: []
Explanation: An empty list remains an empty list after reversal.
```

## 📌 Constraints
*   The number of nodes in the list is in the range `[0, 5000]`.
*   `-5000 <= Node.val <= 5000`

## 🤔 Understanding the Problem
The core of this problem is to change the direction of the `next` pointers for each node in a singly linked list. Instead of `A -> B`, we want `A <- B`. This is non-trivial because simply changing `curr->next` to point to the `previous` node would cause us to lose the reference to the *next* node in the original sequence. We need a strategy to keep track of the original "next" node before modifying the current node's `next` pointer. Edge cases include an empty list (where `head` is `NULL`) and a list with only one node.

## 💡 Core Idea
The key insight is to traverse the list node by node, and for each node, redirect its `next` pointer to point to the *previous* node. To do this safely without losing track of the rest of the list, we need to maintain three pointers: one for the `previous` node, one for the `current` node being processed, and one to temporarily store the `next` node in the original list.

## 🧠 Approach — Iterative Pointer Manipulation
This problem is best solved using an **Iterative Pointer Manipulation** approach. This pattern is fundamental for in-place modifications of linked lists. It fits this problem perfectly because we need to re-wire the `next` pointers of each node without using additional data structures (like an array to store all nodes) that would consume extra space proportional to the list's length. By carefully managing three pointers, we can reverse the links one by one as we traverse the list, achieving an O(1) space complexity.

## 📝 Step-by-Step Algorithm
1.  **Initialize Pointers**:
    *   `prev`: A pointer initialized to `NULL`. This pointer will eventually become the new head of the reversed list. It represents the portion of the list that has already been reversed.
    *   `curr`: A pointer initialized to `head`. This pointer will iterate through the original list, pointing to the node currently being processed.
    *   `next_node_temp`: A temporary pointer initialized to `NULL`. This will be used to store the reference to the next node in the *original* list before `curr->next` is modified.

2.  **Traverse the List**: Start a loop that continues as long as `curr` is not `NULL` (meaning we haven't reached the end of the original list).

3.  **Inside the Loop (for each `curr` node)**:
    *   **Save Next Node**: Store the `curr->next` value into `next_node_temp`. This is crucial because `curr->next` is about to be changed, and we need to know where to move `curr` next.
    *   **Reverse Link**: Change `curr->next` to point to `prev`. This is the actual reversal step for the current node.
    *   **Advance `prev`**: Move `prev` forward to `curr`. The node that was just processed (`curr`) now becomes the "previous" node for the next iteration.
    *   **Advance `curr`**: Move `curr` forward to `next_node_temp`. This moves `curr` to the next node in the original list that needs to be processed.

4.  **Return New Head**: Once the loop finishes (when `curr` becomes `NULL`), `prev` will be pointing to the last node of the original list, which is now the first node (head) of the reversed list. Return `prev`.

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
    ListNode* reverseList(ListNode* head) {
        // Initialize three pointers:
        // 'curr' will iterate through the original list.
        // 'prev' will build up the reversed list, starting as NULL (new tail).
        // 'next_node_temp' will temporarily store the next node in the original list
        // before 'curr->next' is modified.
        ListNode* curr = head;
        ListNode* prev = NULL;
        ListNode* next_node_temp = NULL;

        // Iterate through the list until 'curr' becomes NULL,
        // indicating we've processed all nodes.
        while (curr != NULL) {
            // 1. Store the next node in the original list.
            // This is essential to not lose the rest of the list after
            // we change curr->next.
            next_node_temp = curr->next;

            // 2. Reverse the current node's pointer.
            // Make 'curr->next' point to 'prev'.
            // For the first node, prev is NULL, making it the new tail.
            curr->next = prev;

            // 3. Move 'prev' one step forward.
            // 'prev' now points to the node that was just reversed.
            // This node will become the 'previous' for the next iteration.
            prev = curr;

            // 4. Move 'curr' one step forward.
            // 'curr' now points to the next node in the original list
            // that needs to be processed.
            curr = next_node_temp;
        }

        // After the loop, 'curr' is NULL (end of original list).
        // 'prev' is pointing to the last node that was processed,
        // which is now the new head of the reversed list.
        return prev;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the linked list once, visiting each of the N nodes exactly one time. |
| **Space** | O(1) | We only use a constant number of extra pointers (`prev`, `curr`, `next_node_temp`), regardless of the list's size. |

## 🔗 Related Problems
*   21. Merge Two Sorted Lists
*   141. Linked List Cycle
*   83. Remove Duplicates from Sorted List