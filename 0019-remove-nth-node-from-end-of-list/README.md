# 0019-remove-nth-node-from-end-of-list

## 📋 Problem Description
Given the `head` of a singly linked list, the task is to remove the `n`-th node from the *end* of the list and return the head of the modified linked list.

The function receives two inputs:
1.  `head`: A pointer to the first node of the linked list.
2.  `n`: An integer representing the position from the end of the list of the node to be removed (1-indexed).

It must return a `ListNode*`, which is the head of the linked list after the specified node has been removed.

## 🔍 Examples
```
Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]
Explanation: The 2nd node from the end is 4. After removing it, the list becomes [1,2,3,5].
```

```
Input: head = [1], n = 1
Output: []
Explanation: The 1st node from the end is 1. After removing it, the list is empty.
```

```
Input: head = [1,2], n = 1
Output: [1]
Explanation: The 1st node from the end is 2. After removing it, the list becomes [1].
```

## 📌 Constraints
*   The number of nodes in the list is `sz`.
*   `1 <= sz <= 30`
*   `0 <= Node.val <= 100`
*   `1 <= n <= sz`

## 🤔 Understanding the Problem
The problem asks us to delete a node based on its position *from the end* of a linked list. This is non-trivial because linked lists are inherently forward-directional; we can easily find the *n*-th node from the beginning by traversing `n-1` steps, but finding the *n*-th node from the end requires knowing the total length or using a clever trick. An important edge case to consider is when the node to be removed is the head of the list itself (e.g., if `n` is equal to the total number of nodes).

## 💡 Core Idea
The key insight is to use two pointers, one "fast" and one "slow", maintaining a fixed gap of `n` nodes between them. When the fast pointer reaches the end of the list, the slow pointer will naturally be positioned just before the node that needs to be removed.

## 🧠 Approach — Two Pointers
This problem is perfectly suited for the **Two Pointers** pattern. We use two pointers, `slow` and `fast`, both initially pointing to the head of the list. The `fast` pointer is first advanced `n` steps. This creates a gap of `n` nodes between `slow` and `fast`. Then, both pointers move forward one step at a time until the `fast` pointer reaches the end of the list (i.e., `fast->next` is `NULL`). At this point, because of the `n`-node gap, the `slow` pointer will be exactly at the node *before* the one we need to remove. This allows us to perform the deletion by updating `slow->next`.

## 📝 Step-by-Step Algorithm

1.  **Initialize Pointers**: Create two pointers, `slow` and `fast`, and set both to point to the `head` of the linked list.

2.  **Advance Fast Pointer**: Move the `fast` pointer `n` steps forward. This establishes a gap of `n` nodes between `slow` and `fast`.
    *   For `i` from `0` to `n-1`, update `fast = fast->next`.

3.  **Handle Edge Case (Removing Head)**: After advancing `fast`, if `fast` is now `nullptr`, it means the original list had exactly `n` nodes. Since `n` is the `n`-th node from the end, this implies we need to remove the head of the list.
    *   In this case, return `head->next` as the new head.

4.  **Move Both Pointers**: If the head is not being removed, continue moving both `slow` and `fast` pointers one step at a time until the `fast` pointer reaches the end of the list. The condition for this is `fast->next != NULL`.
    *   While `fast->next` is not `NULL`:
        *   Update `slow = slow->next`.
        *   Update `fast = fast->next`.

5.  **Remove Node**: Once the loop finishes, the `fast` pointer is at the last node of the list. Due to the `n`-node gap, the `slow` pointer is now pointing to the node *immediately preceding* the `n`-th node from the end (the node to be removed).
    *   To remove `slow->next`, update `slow->next = slow->next->next`. This effectively bypasses the node `slow->next` and removes it from the list.

6.  **Return Head**: Return the original `head` of the list. (Note: If the head was removed, step 3 already handled returning `head->next`).

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

        // Step 1: Move the 'fast' pointer 'n' steps ahead.
        // After this loop, 'fast' will be 'n' nodes ahead of 'slow'.
        for (int i = 0; i < n; i++) {
            fast = fast->next;
        }

        // Step 2: Handle the edge case where the 'n'-th node from the end is the head itself.
        // This occurs if 'fast' becomes nullptr after moving 'n' steps.
        // For example, if list is [1,2,3] and n=3, fast moves 3 steps and becomes nullptr.
        // In this scenario, we need to remove the original head.
        if (fast == nullptr) {
            // The new head will be the second node (head->next).
            return head->next;
        }

        // Step 3: Move both 'slow' and 'fast' pointers simultaneously until 'fast' reaches the end of the list.
        // The loop continues as long as 'fast->next' is not nullptr, meaning 'fast' is not yet the last node.
        // When 'fast->next' becomes nullptr, 'fast' is at the last node.
        // At this point, 'slow' will be at the node *just before* the node to be removed.
        while (fast->next != NULL) {
            slow = slow->next; // Move 'slow' one step forward.
            fast = fast->next; // Move 'fast' one step forward.
        }

        // Step 4: 'slow' is now pointing to the node *before* the 'n'-th node from the end.
        // 'slow->next' is the node to be removed.
        // 'slow->next->next' is the node *after* the one to be removed.
        // To remove 'slow->next', we bypass it by linking 'slow' directly to 'slow->next->next'.
        slow->next = slow->next->next;

        // Step 5: Return the original head of the list.
        // If the head was removed, it was handled in Step 2. Otherwise, the head remains the same.
        return head;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(L) | The fast pointer traverses the list once (first `n` steps, then `L-n` steps with slow). Total operations proportional to list length `L`. |
| **Space** | O(1) | Only a constant number of extra pointers (`slow`, `fast`) are used, regardless of the list size. |

## 🔗 Related Problems
*   141. Linked List Cycle
*   876. Middle of the Linked List
*   234. Palindrome Linked List