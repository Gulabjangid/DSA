# 1721-swapping-nodes-in-a-linked-list

## 📋 Problem Description
You are given the `head` of a singly-linked list and an integer `k`.

Your task is to swap the *values* of two specific nodes:
1. The `k`-th node from the beginning of the list.
2. The `k`-th node from the end of the list.

The list is 1-indexed, meaning the first node is considered the 1st node, the second node is the 2nd, and so on. After performing the value swap, you must return the `head` of the modified linked list.

## 🔍 Examples
```
Input: head = [1,2,3,4,5], k = 2
Output: [1,4,3,2,5]
Explanation: The 2nd node from the beginning is 2. The 2nd node from the end is 4. Swapping their values results in [1,4,3,2,5].
```

```
Input: head = [7,9,6,6,7,8,3,0,9,5], k = 5
Output: [7,9,6,6,8,7,3,0,9,5]
Explanation: The 5th node from the beginning is 7. The 5th node from the end is 8. Swapping their values results in [7,9,6,6,8,7,3,0,9,5].
```

## 📌 Constraints
*   The number of nodes in the list is `n`.
*   `1 <= k <= n <= 10^5`
*   `0 <= Node.val <= 100`

## 🤔 Understanding the Problem
The problem asks us to identify two nodes in a linked list based on their position relative to the start and end, respectively, and then exchange their data values. The key challenge is efficiently finding the `k`-th node from the *end* of the list. Since linked lists are unidirectional, we cannot easily traverse backward. A naive approach would involve first finding the list's length, then calculating the index of the `k`-th node from the end, and finally performing a second traversal to reach it. We need a more efficient way to locate both target nodes.

## 💡 Core Idea
The core idea is to use a two-pointer technique to find the `k`-th node from the end of the linked list in a single pass, without needing to know the list's total length beforehand. Once both the `k`-th node from the beginning and the `k`-th node from the end are identified, we simply swap their `val` fields.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern, specifically a variation used for finding the Nth node from the end of a linked list.

This pattern fits because we need to find a node whose position is relative to the *end* of the list. By maintaining a fixed distance between two pointers, we can ensure that when the leading pointer reaches the end of the list, the trailing pointer will be at the desired position relative to the end. In this solution, one pointer (`first`) is used to directly locate the `k`-th node from the beginning. Another pair of pointers (`temp` and `second`) is then used to find the `k`-th node from the end. `temp` is advanced `k-1` steps ahead of `second`, and then both move simultaneously until `temp` reaches the end, at which point `second` will be at the `k`-th node from the end.

## 📝 Step-by-Step Algorithm
1.  **Find the `k`-th node from the beginning:**
    *   Initialize a pointer, `firstNode`, to the `head` of the linked list.
    *   Iterate `k-1` times, moving `firstNode` one step forward in each iteration. After this loop, `firstNode` will be pointing to the `k`-th node from the beginning of the list.

2.  **Prepare for finding the `k`-th node from the end:**
    *   Initialize another pointer, `tempPointer`, to the `head` of the linked list.
    *   Similar to `firstNode`, iterate `k-1` times, moving `tempPointer` one step forward. At this point, `tempPointer` is also at the `k`-th node from the beginning. This `tempPointer` will serve as our "fast" pointer to create the `k`-distance gap.
    *   Initialize a third pointer, `secondNode`, to the `head` of the linked list. This `secondNode` will be our "slow" pointer, which will eventually point to the `k`-th node from the end.

3.  **Find the `k`-th node from the end:**
    *   Now, simultaneously advance both `tempPointer` and `secondNode` one step at a time.
    *   Continue this process until `tempPointer` reaches the last node of the list (i.e., `tempPointer->next` becomes `NULL`).
    *   When `tempPointer` is at the last node, `secondNode` will be pointing to the `k`-th node from the end of the list. This is because `tempPointer` started `k-1` steps ahead of `secondNode`, and they maintained that relative distance throughout their simultaneous traversal.

4.  **Swap values:**
    *   Swap the `val` (value) fields of the nodes pointed to by `firstNode` and `secondNode`.

5.  **Return:**
    *   Return the original `head` of the linked list, as only node values were swapped, not the nodes themselves or their links.

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
    ListNode* swapNodes(ListNode* head, int k) {
        // Pointer to find the k-th node from the beginning.
        // It starts at the head.
        ListNode* first = head;

        // Move 'first' pointer k-1 steps forward.
        // After this loop, 'first' will point to the k-th node from the beginning.
        // Example: if k=1, loop doesn't run, 'first' stays at head (1st node).
        // if k=2, loop runs once, 'first' moves to head->next (2nd node).
        for (int i = 1; i < k; i++) {
            first = first->next;
        }

        // 'temp' pointer will be used as the leading pointer to find the k-th node from the end.
        // It also starts at the head.
        ListNode* temp = head;

        // Move 'temp' pointer k-1 steps forward.
        // At this point, 'temp' is also at the k-th node from the beginning.
        // This effectively creates a 'k-1' distance between 'temp' and 'second' (which is still at head).
        for (int i = 1; i < k; i++) {
            temp = temp->next;
        }

        // 'second' pointer will trail 'temp' to find the k-th node from the end.
        // It starts at the head.
        ListNode* second = head;

        // Now, move both 'temp' and 'second' simultaneously.
        // 'temp' will continue moving until it reaches the last node (its 'next' is NULL).
        // Since 'temp' started k-1 steps ahead of 'second', when 'temp' reaches the end,
        // 'second' will be exactly k-1 nodes behind 'temp', which means 'second' will be
        // at the k-th node from the end of the list.
        while (temp->next != NULL) {
            second = second->next; // 'second' moves one step
            temp = temp->next;     // 'temp' moves one step
        }

        // After the loop, 'first' points to the k-th node from the beginning,
        // and 'second' points to the k-th node from the end.
        // Swap their values.
        std::swap(first->val, second->val);

        // Return the head of the list. The structure of the list remains unchanged,
        // only the values within two nodes have been swapped.
        return head;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We traverse the list once to find `first` (up to `k` steps), then effectively once more to find `second` (where `temp` moves `k` steps and then `N-k` steps, and `second` moves `N-k` steps). In total, this is proportional to the number of nodes `N`. |
| **Space** | O(1) | We only use a constant number of extra pointers (`first`, `temp`, `second`) regardless of the list size. |

## 🔗 Related Problems
*   19. Remove Nth Node From End of List
*   876. Middle of the Linked List
*   61. Rotate List