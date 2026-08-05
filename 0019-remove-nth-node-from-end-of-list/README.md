# 0019-remove-nth-node-from-end-of-list

## 📋 Problem Description
Given the `head` of a singly linked list, the task is to remove the `n`-th node from the *end* of the list and return the `head` of the modified list.

The function `removeNthFromEnd` receives two arguments:
*   `head`: A pointer to the first node of the linked list.
*   `n`: An integer representing the position of the node to be removed, counting from the end of the list (1-indexed).

It must return a pointer to the `head` of the modified linked list after the specified node has been removed.

## 🔍 Examples
```
Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]
Explanation: The 2nd node from the end is 4. After removing it, the list becomes 1->2->3->5.
```

```
Input: head = [1], n = 1
Output: []
Explanation: The 1st node from the end is 1 (the head). After removing it, the list is empty.
```

```
Input: head = [1,2], n = 1
Output: [1]
Explanation: The 1st node from the end is 2. After removing it, the list becomes 1.
```

## 📌 Constraints
*   The number of nodes in the list (`sz`) is between 1 and 30.
*   Node values (`Node.val`) are between 0 and 100.
*   `n` is between 1 and `sz`. This guarantees that `n` will always be a valid position within the list, and we won't be asked to remove a non-existent node.

## 🤔 Understanding the Problem
The problem asks us to delete a specific node from a linked list, but its position is given relative to the *end* of the list, not the beginning. This makes it tricky because linked lists are inherently forward-traversal structures; we cannot easily go backward to find a node from the end. A straightforward approach might involve two passes: one to determine the total length of the list, and a second pass to find and remove the `(length - n + 1)`-th node from the beginning. However, the problem's "Follow up" explicitly asks for a one-pass solution, which hints at a more clever approach. An important edge case to consider is when the node to be removed is the head of the list itself.

## 💡 Core Idea
To remove the Nth node from the end in a single pass, we can use two pointers, `slow` and `fast`. By maintaining a fixed gap of `n` nodes between `fast` and `slow`, when `fast` reaches the end of the list, `slow` will naturally be positioned just before the node we need to remove.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern, specifically the "fast and slow" pointer variant. This pattern is ideal for linked list problems where you need to find a node relative to another node's position or the end of the list, often in a single pass. Here, we use two pointers to create a "window" of `n` nodes. By moving the `fast` pointer `n` steps ahead initially, we establish this window. Then, both pointers move simultaneously. When the `fast` pointer reaches the end of the list, the `slow` pointer will be at the correct position to perform the deletion.

## 📝 Step-by-Step Algorithm
1.  **Initialize Pointers**: Create two pointers, `slow` and `fast`, and initialize both to point to the `head` of the linked list.
2.  **Establish Gap**: Move the `fast` pointer `n` steps forward. This creates a gap of `n` nodes between `slow` and `fast`.
    *   For example, if `n=2`, `fast` will move two steps ahead.
3.  **Handle Head Removal Edge Case**: After moving `fast`, check if `fast` is `NULL`. If `fast` is `NULL`, it means the original list had exactly `n` nodes, and thus the `n`-th node from the end is the `head` itself. In this special case, the new head will be `head->next`, so return `head->next`.
4.  **Advance Both Pointers**: If `fast` is not `NULL`, proceed to move both `slow` and `fast` pointers simultaneously, one step at a time. Continue this process until `fast->next` becomes `NULL`.
    *   When `fast->next` is `NULL`, it signifies that `fast` is currently at the last node of the list. Due to the initial `n`-step head start, `slow` will now be pointing to the node *just before* the `n`-th node from the end.
5.  **Perform Deletion**: At this point, `slow` is pointing to the node that precedes the target node to be removed. The target node is `slow->next`. To remove `slow->next`, update `slow->next` to point to `slow->next->next`. This effectively bypasses the target node, removing it from the list.
6.  **Return Head**: Return the original `head` of the list. If the head itself was removed, this was handled in Step 3. Otherwise, the head remains the same.

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
        // The 'slow' pointer will eventually stop at the node *before* the one to be removed.
        // The 'fast' pointer will be 'n' steps ahead of 'slow'.
        ListNode* slow = head;
        ListNode* fast = head;

        // Step 1: Move the 'fast' pointer 'n' steps ahead of 'slow'.
        // This creates a gap of 'n' nodes between 'slow' and 'fast'.
        // For example, if n=2, fast will move two steps ahead.
        for (int i = 0; i < n; i++) {
            fast = fast->next;
        }

        // Step 2: Handle the edge case where the node to be removed is the head itself.
        // This occurs if 'fast' becomes NULL after moving 'n' steps.
        // For example, if the list is [1,2,3] and n=3, 'fast' moves 3 steps and becomes NULL.
        // In this scenario, the 3rd node from the end is '1' (the head).
        if (fast == NULL) {
            // If 'fast' is NULL, it means the original head needs to be removed.
            // The new head will be the node that was originally 'head->next'.
            return head->next;
        }

        // Step 3: Move both 'slow' and 'fast' pointers simultaneously, one step at a time.
        // Continue this until 'fast' reaches the end of the list (i.e., 'fast->next' is NULL).
        // When 'fast->next' is NULL, 'fast' is at the last node.
        // Because 'fast' was initially 'n' steps ahead, 'slow' will now be at the node
        // *just before* the 'n'-th node from the end.
        while (fast->next != NULL) {
            fast = fast->next;
            slow = slow->next;
        }
        
        // Step 4: 'slow' is now pointing to the node *before* the target node to be removed.
        // The target node is 'slow->next'.
        // To remove 'slow->next', we update 'slow->next' to point to 'slow->next->next'.
        // This effectively bypasses the target node, removing it from the list.
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
| **Time** | O(L) | The algorithm iterates through the linked list at most twice (once for the `fast` pointer to move `n` steps, then both pointers move until `fast` reaches the end). In the worst case, `fast` traverses the entire list, and `slow` traverses `(L-n)` nodes. This is equivalent to a single pass over the list, where `L` is the number of nodes. |
| **Space** | O(1) | The algorithm uses a constant amount of extra space for the two pointers (`slow` and `fast`), regardless of the list's size. |

## 🔗 Related Problems
- 141. Linked List Cycle
- 142. Linked List Cycle II
- 876. Middle of the Linked List