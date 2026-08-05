# 0019-remove-nth-node-from-end-of-list

## 📋 Problem Description
Given the `head` of a singly linked list, the task is to remove the `n`-th node from the *end* of the list and return the head of the modified list.

The function receives two inputs:
1.  `head`: A pointer to the first node of the linked list.
2.  `n`: An integer representing the position of the node to be removed, counting from the end of the list (1-indexed).

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
The problem asks us to delete a node from a linked list, but the twist is that the node's position is given relative to the *end* of the list, not the beginning. In a singly linked list, we can only traverse forward. This makes finding the `n`-th node from the end non-trivial, as we don't know the list's total length without a full traversal. A common edge case to consider is when the node to be removed is the head of the list itself.

## 💡 Core Idea
The key insight is to use two pointers that maintain a fixed distance `n` between them. By advancing one pointer `n` steps ahead, and then moving both pointers simultaneously, when the leading pointer reaches the end of the list, the trailing pointer will be positioned just before the node that needs to be removed.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern, specifically the "fast and slow" or "two-pointer with a gap" variation. This pattern is ideal for linked list problems where you need to find a node relative to another node's position or relative to the end of the list, often in a single pass. Here, we use two pointers, `fast` and `slow`, to establish a gap of `n` nodes. This allows us to determine the position of the `n`-th node from the end without first calculating the total length of the list, thus achieving a solution in a single pass.

## 📝 Step-by-Step Algorithm

1.  **Initialize Pointers**: Create two pointers, `slow` and `fast`, and initialize both to point to the `head` of the linked list.

2.  **Advance Fast Pointer**: Move the `fast` pointer `n` steps forward. This establishes a gap of `n` nodes between `slow` and `fast`.
    *   For `i` from `0` to `n-1`, update `fast = fast->next`.

3.  **Handle Edge Case (Removing Head)**: After advancing `fast`, check if `fast` has become `nullptr`. If `fast` is `nullptr`, it means the original list had exactly `n` nodes, and thus the `n`-th node from the end is the `head` itself. In this scenario, we need to remove the head, so return `head->next`.

4.  **Move Both Pointers Simultaneously**: Now, move both `slow` and `fast` pointers one step at a time until the `fast` pointer reaches the end of the list. The condition for `fast` reaching the end is `fast->next == nullptr`.
    *   While `fast->next` is not `nullptr`:
        *   Update `slow = slow->next`.
        *   Update `fast = fast->next`.

5.  **Remove the Node**: Once the loop finishes, `fast` is at the last node of the list. Because `fast` was initially `n` steps ahead of `slow`, `slow` is now pointing to the node *just before* the `n`-th node from the end. To remove the `n`-th node from the end (which is `slow->next`), update `slow->next` to point to `slow->next->next`. This effectively bypasses and removes the target node.

6.  **Return Head**: Return the original `head` of the list (which might have been modified if the head was removed in step 3, but the logic handles that by returning `head->next` earlier).

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
        // 'slow' will eventually point to the node *before* the one to be removed.
        // 'fast' will be 'n' steps ahead of 'slow'.
        ListNode* slow = head;
        ListNode* fast = head;

        // Move the 'fast' pointer 'n' steps forward.
        // This creates a gap of 'n' nodes between 'slow' and 'fast'.
        for (int i = 0; i < n; i++) {
            fast = fast->next;
        }

        // Edge case: If 'fast' is now nullptr, it means the original list had exactly 'n' nodes.
        // In this situation, the 'n'-th node from the end is the head itself.
        // We need to remove the head, so we return the next node as the new head.
        if (fast == nullptr) {
            return head->next;
        }

        // Move both 'slow' and 'fast' pointers one step at a time
        // until 'fast' reaches the end of the list (i.e., fast->next is nullptr).
        // When this loop finishes, 'fast' will be at the last node,
        // and 'slow' will be at the node *before* the one we want to remove.
        while (fast->next != NULL) {
            slow = slow->next;
            fast = fast->next;
        }

        // 'slow' is now pointing to the node immediately preceding the node to be removed.
        // The node to be removed is 'slow->next'.
        // To remove it, we bypass it by making 'slow->next' point to 'slow->next->next'.
        // This effectively unlinks the target node from the list.
        slow->next = slow->next->next;

        // Return the original head of the list.
        // If the head was removed in the edge case, the new head was already returned.
        // Otherwise, the head remains the same.
        return head;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(L) | The `fast` pointer traverses the list once (first `n` steps, then `L-n` steps). The `slow` pointer traverses `L-n` steps. Overall, each node is visited a constant number of times. `L` is the number of nodes in the list. |
| **Space** | O(1) | Only a constant number of extra pointers (`slow`, `fast`) are used, regardless of the list's size. |

## 🔗 Related Problems
- 141. Linked List Cycle
- 142. Linked List Cycle II
- 876. Middle of the Linked List