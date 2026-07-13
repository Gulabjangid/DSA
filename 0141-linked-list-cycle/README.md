# 0141-linked-list-cycle

## 📋 Problem Description
Given the `head` of a singly-linked list, determine if the linked list contains a cycle. A cycle exists in a linked list if there is a node in the list that can be reached again by continuously following the `next` pointer.

The problem statement mentions an internal `pos` variable, which denotes the 0-indexed position of the node where the tail's `next` pointer is connected to form a cycle. However, `pos` is **not** provided as an input parameter to the function.

Your task is to implement a function `hasCycle` that takes the `head` of a linked list as input and returns `true` if a cycle is present, and `false` otherwise.

## 🔍 Examples
```
Input: head = [3,2,0,-4], pos = 1
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).
```

```
Input: head = [1,2], pos = 0
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 0th node.
```

```
Input: head = [1], pos = -1
Output: false
Explanation: There is no cycle in the linked list.
```

## 📌 Constraints
*   The number of nodes in the list is in the range `[0, 10^4]`.
*   `-10^5 <= Node.val <= 10^5`
*   `pos` is `-1` or a valid index in the linked-list. (Note: `pos` is for test case description, not a function parameter).

## 🤔 Understanding the Problem
The problem asks us to detect if a given singly-linked list forms a loop. This means that somewhere in the list, a node's `next` pointer points back to an earlier node, rather than eventually leading to `NULL`. The challenge is to identify this cycle without modifying the list structure and ideally using minimal extra memory. Edge cases include an empty list (0 nodes) or a list with only one node, neither of which can form a cycle.

## 💡 Core Idea
The fundamental insight is that if two pointers traverse a cyclic linked list at different speeds, they are guaranteed to eventually meet if a cycle exists. If there's no cycle, the faster pointer will simply reach the end of the list (NULL).

## 🧠 Approach — Two Pointers (Floyd's Cycle-Finding Algorithm)
This problem is a classic application of the Two Pointers pattern, specifically Floyd's Cycle-Finding Algorithm, often referred to as the "tortoise and hare" algorithm. This pattern is highly effective for linked list problems where you need to compare relative positions or detect patterns within the list without using extra space. By having one pointer (`fast`) move twice as fast as the other (`slow`), we create a scenario where if a cycle exists, the faster pointer will inevitably "lap" the slower pointer, causing them to meet at some point within the cycle. If no cycle exists, the `fast` pointer will always reach the end of the list (NULL) before it can ever meet the `slow` pointer.

## 📝 Step-by-Step Algorithm
1.  Initialize two pointers, `slow` and `fast`, both pointing to the `head` of the linked list.
2.  Begin a loop that continues as long as `fast` is not `NULL` and `fast->next` is not `NULL`. These conditions are crucial because the `fast` pointer needs to move two steps, so we must ensure both the current node and the next node exist.
3.  Inside the loop, advance the `slow` pointer by one step: `slow = slow->next`.
4.  Advance the `fast` pointer by two steps: `fast = fast->next->next`.
5.  After moving both pointers, check if `slow` and `fast` are now pointing to the exact same node. If `fast == slow`, it signifies that they have met, confirming the presence of a cycle. In this case, immediately return `true`.
6.  If the loop terminates (because `fast` or `fast->next` became `NULL`), it means the `fast` pointer reached the end of the list, and no cycle was detected. In this scenario, return `false`.

## 💻 Solution
```cpp
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
    bool hasCycle(ListNode *head) {
        // Initialize two pointers, 'slow' and 'fast', both starting at the head.
        // The 'slow' pointer will move one step at a time.
        // The 'fast' pointer will move two steps at a time.
        ListNode *slow = head;
        ListNode *fast = head;

        // Loop as long as 'fast' and 'fast->next' are not NULL.
        // This ensures 'fast' can always make two steps without dereferencing a NULL pointer.
        // If 'fast' or 'fast->next' becomes NULL, it means we've reached the end of the list
        // or the node before the end, indicating no cycle.
        while (fast != NULL && fast->next != NULL) {
            // Move 'slow' pointer one step forward.
            slow = slow->next;
            // Move 'fast' pointer two steps forward.
            fast = fast->next->next;

            // If 'fast' and 'slow' pointers meet, a cycle is detected.
            // This happens because if there's a cycle, the faster pointer will eventually
            // "lap" the slower pointer within the cycle.
            if (fast == slow) {
                return true; // Cycle found
            }
        }

        // If the loop completes, it means 'fast' reached the end of the list (or one node before),
        // and the pointers never met. Therefore, no cycle exists.
        return false; // No cycle found
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | In the worst case (no cycle or a very long cycle), the fast pointer traverses the entire list, and the slow pointer traverses at most half of it. Each step is constant time. |
| **Space** | O(1) | We only use a constant number of extra pointers (`slow` and `fast`), regardless of the list's size. |

## 🔗 Related Problems
- 142. Linked List Cycle II
- 287. Find the Duplicate Number
- 234. Palindrome Linked List