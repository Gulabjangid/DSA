# 0019-remove-nth-node-from-end-of-list

## 📋 Problem Description
Given the `head` of a singly linked list and an integer `n`, the task is to remove the `n`-th node from the *end* of the list and return the `head` of the modified list.

The function receives two arguments:
- `head`: A pointer to the first node of the linked list.
- `n`: An integer representing the position from the end of the list of the node to be removed.

It must return a `ListNode*` representing the head of the modified linked list.

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
*   The number of nodes in the list (`sz`) is between 1 and 30.
*   `0 <= Node.val <= 100`
*   `1 <= n <= sz`

## 🤔 Understanding the Problem
The core challenge here is to remove a node based on its position from the *end* of a singly linked list. Unlike arrays, linked lists don't allow direct access to elements by index, and we can only traverse them in one direction (forward). A naive approach might involve two passes: one to count the total number of nodes, and another to find the `(total_nodes - n)`-th node from the beginning and remove it. The problem's "Follow up" explicitly asks for a solution that accomplishes this in a single pass, which is the non-trivial aspect. We also need to consider the edge case where the node to be removed is the head of the list itself.

## 💡 Core Idea
To remove the `n`-th node from the end in a single pass, we can use two pointers that maintain a fixed distance of `n` nodes between them. When the faster pointer reaches the end of the list, the slower pointer will be positioned exactly at the node *just before* the one we need to remove.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern, specifically the "fast and slow pointer" variant. This pattern is particularly effective for linked list problems where you need to find a node relative to another node or the end of the list without knowing the total length beforehand. By initializing two pointers and moving one `n` steps ahead of the other, we create a fixed gap. As both pointers then traverse the rest of the list simultaneously, the `slow` pointer will naturally align itself to the correct position for removal when the `fast` pointer reaches the end.

## 📝 Step-by-Step Algorithm
1.  **Initialize Pointers**: Create two pointers, `slow` and `fast`, and set both to point to the `head` of the linked list.
2.  **Create Gap**: Move the `fast` pointer `n` steps forward. This establishes a gap of `n` nodes between `slow` and `fast`.
3.  **Handle Head Removal Edge Case**: After moving `fast` `n` steps, check if `fast` is now `nullptr`. If it is, it means the original list had exactly `n` nodes, and thus the `n`-th node from the end is the `head` itself. In this scenario, the new head should be `head->next`. Return `head->next`.
4.  **Traverse Simultaneously**: If `fast` is not `nullptr`, proceed to move both `slow` and `fast` pointers one step at a time, simultaneously. Continue this process until `fast->next` becomes `nullptr`. This condition signifies that `fast` has reached the very last node of the list.
5.  **Position for Removal**: When `fast->next` is `nullptr`, the `slow` pointer will be positioned at the node *immediately preceding* the `n`-th node from the end. The node to be removed is `slow->next`.
6.  **Perform Removal**: To remove the target node (`slow->next`), update the `next` pointer of the `slow` node. Set `slow->next = slow->next->next`. This effectively bypasses the target node, removing it from the list.
7.  **Return Head**: Finally, return the original `head` of the list. This `head` might have been modified in step 3 if the head itself was removed, or it remains the same if an intermediate node was removed.

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
        // This establishes the required 'n' node gap.
        for (int i = 0; i < n; i++) {
            fast = fast->next;
        }

        // Step 2: Handle the edge case where the 'n'-th node from the end is the head itself.
        // If 'fast' is now NULL, it means we moved 'n' steps and reached the end,
        // implying the list had exactly 'n' nodes, and we need to remove the first one.
        if (fast == NULL) {
            // The new head will be the second node (or NULL if the list had only one node).
            return head->next;
        }

        // Step 3: Move both 'slow' and 'fast' pointers simultaneously
        // until 'fast' reaches the last node of the list.
        // We stop when 'fast->next' is NULL, meaning 'fast' is at the last node.
        // At this point, 'slow' will be pointing to the node *just before* the
        // node we need to remove.
        while (fast->next != NULL) {
            fast = fast->next; // Move fast pointer
            slow = slow->next; // Move slow pointer
        }
        
        // Step 4: 'slow' is now at the node *before* the target node to be removed.
        // The target node is 'slow->next'.
        // To remove it, we bypass it by making 'slow->next' point to 'slow->next->next'.
        // This effectively removes the node 'slow->next' from the list.
        slow->next = slow->next->next;

        // Step 5: Return the original head of the list, which might have been modified
        // if the head itself was removed (handled in Step 2) or if an intermediate node was removed.
        return head;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(L) | The algorithm involves a single pass through the linked list. The `fast` pointer moves `n` steps, and then both `fast` and `slow` pointers move together for `L-n` steps. In total, we traverse the list approximately `L` times. |
| **Space** | O(1) | We only use a constant amount of extra space for the `slow` and `fast` pointers, regardless of the list's length. |

## 🔗 Related Problems
- 141. Linked List Cycle
- 142. Linked List Cycle II
- 876. Middle of the Linked List