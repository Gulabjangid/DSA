# 0019-remove-nth-node-from-end-of-list

## 📋 Problem Description
Given the `head` of a singly linked list, the task is to remove the `n`-th node from the *end* of the list and return the head of the modified list.

The function receives two inputs:
1.  `head`: A pointer to the first node of the linked list.
2.  `n`: An integer representing the position of the node to be removed, counting from the end of the list (1-indexed).

It must return a pointer to the head of the linked list after the specified node has been removed.

## 🔍 Examples
```
Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]
Explanation: The 2nd node from the end is 4. After removing it, the list becomes [1,2,3,5].
```

```
Input: head = [1], n = 1
Output: []
Explanation: The 1st node from the end is 1. After removing it, the list becomes empty.
```

```
Input: head = [1,2], n = 1
Output: [1]
Explanation: The 1st node from the end is 2. After removing it, the list becomes [1].
```

## 📌 Constraints
*   The number of nodes in the list (`sz`) is between 1 and 30, inclusive.
*   The value of each node (`Node.val`) is between 0 and 100, inclusive.
*   `n` is between 1 and `sz`, inclusive.

## 🤔 Understanding the Problem
The problem asks us to delete a specific node from a linked list, but its position is given relative to the *end* of the list, not the beginning. This means we can't simply traverse `n` nodes from the start and delete, because we don't know the total length of the list beforehand. A naive approach would involve two passes: one to find the length, and another to find the `(length - n + 1)`-th node from the beginning and delete it. The follow-up question specifically asks if this can be done in one pass, which suggests a more clever approach is needed. An important edge case is when the node to be removed is the head of the list itself.

## 💡 Core Idea
The key insight is to use two pointers that maintain a fixed distance between them. If the distance between a `fast` pointer and a `slow` pointer is `n`, then when the `fast` pointer reaches the end of the list, the `slow` pointer will be positioned just before the `n`-th node from the end. This allows for deletion in a single pass.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern, specifically the "fast and slow" variant.
This pattern fits perfectly because we need to find a node whose position is defined relative to the end of the list, without knowing the list's total length in advance. By maintaining a gap of `n` nodes between a `fast` pointer and a `slow` pointer, we can ensure that when the `fast` pointer reaches the end, the `slow` pointer is correctly positioned to facilitate the removal of the target node. This avoids the need for a preliminary pass to calculate the list's length, thus achieving a single-pass solution.

## 📝 Step-by-Step Algorithm
1.  **Initialize Pointers**: Create two pointers, `slow` and `fast`, and initialize both to point to the `head` of the linked list.
2.  **Advance Fast Pointer**: Move the `fast` pointer `n` steps forward. This establishes a gap of `n` nodes between `slow` and `fast`.
    *   For example, if `n=2`, `fast` will move two steps ahead.
3.  **Handle Head Removal Edge Case**: After advancing `fast`, check if `fast` has become `nullptr`. If it has, it means the `n`-th node from the end is actually the `head` of the list. In this scenario, the node to be removed is the current `head`. Return `head->next` (the new head of the list).
4.  **Move Both Pointers**: If the head is not being removed, now move both `slow` and `fast` pointers one step at a time, simultaneously, until the `fast` pointer reaches the last node of the list (i.e., `fast->next` is `nullptr`).
5.  **Position for Deletion**: When `fast->next` is `nullptr`, the `fast` pointer is at the last node. Due to the `n`-node gap maintained, the `slow` pointer will now be pointing to the node *immediately preceding* the `n`-th node from the end. This is the perfect position to perform the deletion.
6.  **Perform Deletion**: Update the `next` pointer of the `slow` node to skip the target node. Specifically, set `slow->next = slow->next->next;`. This effectively removes the `n`-th node from the end from the list.
7.  **Return Head**: Return the original `head` of the list, which might have changed if the head itself was removed (handled in step 3) or remained the same.

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // Initialize two pointers, 'slow' and 'fast', both starting at the head.
        // These pointers will maintain a gap of 'n' nodes between them.
        ListNode* slow = head;
        ListNode* fast = head;

        // Move the 'fast' pointer 'n' steps ahead.
        // After this loop, 'fast' will be 'n' nodes ahead of 'slow'.
        for (int i = 0; i < n; i++) {
            fast = fast->next;
        }

        // Edge case: If 'fast' is nullptr after moving 'n' steps,
        // it means the 'n'-th node from the end is the head itself.
        // For example, if list is [1,2,3] and n=3, fast will point to nullptr after 3 steps.
        // In this case, we need to remove the head, so the new head is head->next.
        if (fast == nullptr) {
            return head->next;
        }

        // Now, move both 'slow' and 'fast' pointers one step at a time
        // until 'fast' reaches the last node of the list.
        // 'fast->next != NULL' ensures 'fast' stops at the last node,
        // not past it (i.e., 'fast' is the last node, 'fast->next' is nullptr).
        // When 'fast' is at the last node, 'slow' will be at the node
        // immediately preceding the node to be removed.
        while (fast->next != NULL) {
            slow = slow->next;
            fast = fast->next;
        }

        // At this point, 'slow' is pointing to the node *before* the node
        // that needs to be removed.
        // The node to be removed is 'slow->next'.
        // To remove it, we bypass it by setting 'slow->next' to 'slow->next->next'.
        slow->next = slow->next->next;

        // Return the original head of the list.
        // It remains the head unless the head itself was removed (handled above).
        return head;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(L) | The algorithm iterates through the linked list once. The `fast` pointer traverses the list, and `slow` follows. In the worst case, `fast` traverses the entire list of length `L`. |
| **Space** | O(1) | The algorithm uses a constant amount of extra space for the `slow` and `fast` pointers, regardless of the list's size. |

## 🔗 Related Problems
- 141. Linked List Cycle
- 142. Linked List Cycle II
- 876. Middle of the Linked List