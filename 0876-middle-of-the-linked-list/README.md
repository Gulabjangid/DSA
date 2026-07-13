# 0876-middle-of-the-linked-list

## 📋 Problem Description
Given the `head` of a singly linked list, the task is to find and return the middle node of that list. If the list contains an even number of nodes, there will be two nodes that could be considered "middle". In such cases, the problem specifies that we should return the **second** of these two middle nodes. The returned node should be the starting point of the rest of the list.

**Input:** A pointer to the `head` of a singly linked list.
**Output:** A pointer to the middle node of the linked list.

## 🔍 Examples
```
Input: head = [1,2,3,4,5]
Output: [3,4,5]
Explanation: The list has 5 nodes. Node 3 is the middle node.
```

```
Input: head = [1,2,3,4,5,6]
Output: [4,5,6]
Explanation: The list has 6 nodes. Nodes 3 and 4 are the middle nodes. As per the problem statement, we return the second middle node, which is node 4.
```

## 📌 Constraints
*   The number of nodes in the list is in the range `[1, 100]`.
*   `1 <= Node.val <= 100`

## 🤔 Understanding the Problem
The problem asks us to locate the central element in a singly linked list. Unlike arrays, linked lists don't allow direct access to elements by index, meaning we typically need to traverse them from the beginning. The key nuance is how to define "middle" for lists with an even number of elements: we must return the second of the two central nodes. This implies that if a list has `N` nodes, we want the node at index `floor(N/2)` (0-indexed) or `ceil(N/2)` (1-indexed).

## 💡 Core Idea
The most efficient way to find the middle of a linked list in a single pass without knowing its length beforehand is to use the **fast and slow pointer** technique. By having one pointer move twice as fast as the other, the slow pointer will naturally be at the middle when the fast pointer reaches the end.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern, specifically the "fast and slow pointers" variant. This pattern is particularly well-suited for linked list problems where you need to find a relative position (like the middle) or detect cycles, as it allows you to achieve this in a single traversal without needing to store the entire list or its length. By maintaining a constant speed ratio between the two pointers, their relative positions provide useful information about the list's structure.

## 📝 Step-by-Step Algorithm
1.  **Initialize Pointers:** Create two pointers, `slow` and `fast`, and set both of them to point to the `head` of the linked list.
2.  **Traverse the List:** Begin a loop that continues as long as `fast` is not `NULL` and `fast->next` is not `NULL`. This condition ensures that `fast` can always make two steps forward without encountering a `NULL` pointer prematurely.
3.  **Move Pointers:** Inside the loop:
    *   Move the `slow` pointer one step forward: `slow = slow->next`.
    *   Move the `fast` pointer two steps forward: `fast = fast->next->next`.
4.  **Return Middle Node:** When the loop terminates, the `fast` pointer will have reached the end of the list (or `fast->next` will be `NULL`, meaning it's one step away from the end). At this point, the `slow` pointer will be positioned exactly at the middle node of the linked list, satisfying the problem's conditions (returning the second middle node for even-length lists).
5.  Return the `slow` pointer.

## 💻 Solution
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        // Initialize two pointers, 'slow' and 'fast', both starting at the head.
        // The 'slow' pointer will move one step at a time.
        // The 'fast' pointer will move two steps at a time.
        ListNode* slow = head;
        ListNode* fast = head;

        // Iterate through the list using the fast and slow pointers.
        // The loop continues as long as 'fast' is not NULL and 'fast->next' is not NULL.
        // This ensures 'fast' can always move two steps forward.
        // When 'fast' reaches the end (or one step before the end), 'slow' will be at the middle.
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;         // Move slow pointer one step
            fast = fast->next->next;   // Move fast pointer two steps
        }

        // When the loop finishes:
        // - If the list has an odd number of nodes, 'fast' will be at the last node,
        //   and 'slow' will be at the exact middle node.
        // - If the list has an even number of nodes, 'fast' will be NULL,
        //   and 'slow' will be at the second of the two middle nodes (as required by the problem).
        return slow; // Return the middle node found by the slow pointer.
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The `fast` pointer traverses the entire list (or nearly the entire list), and the `slow` pointer traverses half the list. This constitutes a single pass through the linked list, where N is the number of nodes. |
| **Space** | O(1) | We only use a constant amount of extra space to store the two pointers (`slow` and `fast`), regardless of the input list's size. |

## 🔗 Related Problems
*   141. Linked List Cycle
*   142. Linked List Cycle II
*   234. Palindrome Linked List