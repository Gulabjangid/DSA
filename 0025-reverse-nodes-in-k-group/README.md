# 0025-reverse-nodes-in-k-group

## 📋 Problem Description
Given the `head` of a singly linked list and a positive integer `k`, the task is to reverse the nodes of the list `k` at a time. The modified list should then be returned.

The integer `k` is guaranteed to be a positive value and will always be less than or equal to the total number of nodes in the linked list.

If, at the end of the list, the number of remaining nodes is not a multiple of `k` (i.e., fewer than `k` nodes are left), those left-out nodes should remain in their original order and not be reversed.

It is a strict requirement that you may not alter the `val` attributes of the nodes; only the `next` pointers of the nodes themselves may be changed to achieve the reversal.

## 🔍 Examples
```
Input: head = [1,2,3,4,5], k = 2
Output: [2,1,4,3,5]
Explanation:
The list is [1,2,3,4,5] and k=2.
First group: [1,2] -> reversed to [2,1].
Second group: [3,4] -> reversed to [4,3].
Remaining: [5] -> remains [5] as it's less than k.
Connecting them: [2,1] -> [4,3] -> [5] results in [2,1,4,3,5].
```

```
Input: head = [1,2,3,4,5], k = 3
Output: [3,2,1,4,5]
Explanation:
The list is [1,2,3,4,5] and k=3.
First group: [1,2,3] -> reversed to [3,2,1].
Remaining: [4,5] -> remains [4,5] as it's less than k.
Connecting them: [3,2,1] -> [4,5] results in [3,2,1,4,5].
```

## 📌 Constraints
*   The number of nodes in the list is `n`.
*   `1 <= k <= n <= 5000`
*   `0 <= Node.val <= 1000`
*   Follow-up: Can you solve the problem in `O(1)` extra memory space?

## 🤔 Understanding the Problem
This problem asks us to reverse segments of a linked list, where each segment (or "group") must contain exactly `k` nodes. After reversing a group, we need to correctly link it to the next group. A crucial detail is how to handle the tail of the list: if the very last segment has fewer than `k` nodes, it should not be reversed and must remain in its original order. The constraint about not altering node values means we must exclusively manipulate the `next` pointers to rearrange the list structure.

## 💡 Core Idea
The problem exhibits optimal substructure and overlapping subproblems, making it suitable for a recursive approach. The core idea is to break the problem into two parts: first, reverse the initial `k` nodes, and second, recursively solve the problem for the rest of the list. The result of the recursive call then needs to be correctly linked to the end of the first reversed `k`-group.

## 🧠 Approach — Recursion with Linked List Reversal
This problem is a classic application of **Recursion** combined with **Linked List Manipulation**. Recursion is highly suitable because the problem can be naturally decomposed: reversing `k` nodes and then reversing the *rest* of the list `k` at a time is essentially the same problem applied to a smaller sublist. The base case for the recursion is when there are fewer than `k` nodes remaining in the current segment, in which case we simply return the current `head` without modification. Within each recursive step, we perform a standard **Linked List Reversal** on the current `k` nodes, carefully managing the `next` pointers to connect the newly reversed group to the result of the subsequent recursive call.

## 📝 Step-by-Step Algorithm
1.  **Check for Sufficient Nodes**: Start by traversing `k` nodes from the current `head`. Use a temporary pointer (e.g., `temp`) and a counter. If `temp` becomes `NULL` before the counter reaches `k`, it means there are fewer than `k` nodes remaining in this segment. In this scenario, this segment should not be reversed, so we simply return the current `head` as is.
2.  **Identify Next Group's Head**: If `k` nodes are available, `temp` will now point to the `(k+1)`-th node (the node immediately following the current `k`-group). This `(k+1)`-th node will be the `head` of the *next* `k`-group (or the start of the unreversed tail if fewer than `k` nodes follow).
3.  **Recursive Call**: Make a recursive call to `reverseKGroup` with `temp` (the `(k+1)`-th node) and `k`. This recursive call will handle the reversal of all subsequent `k`-groups and return the new `head` of that fully processed tail segment. Let's store this result in a pointer, say `prevNode` (because this will eventually become the `next` pointer of the *last* node of our *current* `k`-group after it's reversed).
4.  **Reverse Current Group**: Now, we need to reverse the *first* `k` nodes starting from the original `head`. This is a standard iterative linked list reversal process:
    *   Initialize `current` to `head`.
    *   Initialize `prev` to `prevNode` (the result from the recursive call). This is crucial: the `next` of the *first* node in our current group (which will become the *last* node after reversal) should point to the head of the *next* processed segment.
    *   Iterate `k` times:
        *   Store `current->next` in a temporary pointer (e.g., `next_node`) to avoid losing the rest of the list.
        *   Set `current->next = prev`. This reverses the pointer.
        *   Move `prev` to `current` (the node that was just processed becomes the new `prev` for the next iteration).
        *   Move `current` to `next_node` (to continue processing the original list).
5.  **Return New Head**: After the loop completes, `prev` will be pointing to the new head of the just-reversed `k`-group (which was originally the `k`-th node). Return `prev`.

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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* temp = head; // Use temp to traverse and check for k nodes
        int count = 0;
        
        // Step 1: Check if k nodes exist from the current head.
        // We need to find the (k+1)-th node, which will be the head of the next group.
        while (count < k) {
            if (temp == NULL) {
                // If we don't have k nodes remaining (i.e., less than k nodes),
                // this segment should not be reversed. Return the head as is.
                return head;
            }
            temp = temp->next; // Move to the next node
            count++;           // Increment count
        }

        // Step 2: Recursively call for the rest of the linked list.
        // At this point, 'temp' points to the (k+1)-th node (or NULL if the list
        // had exactly k nodes). This recursive call will reverse the subsequent
        // k-groups and return the new head of that fully processed segment.
        // This new head will become the 'next' pointer of the last node of our
        // current k-group after it's reversed.
        ListNode* prevNode = reverseKGroup(temp, k);

        // Step 3: Reverse the current k nodes.
        // 'head' is the start of our current k-group (e.g., node 1 in [1,2,3,4,5] with k=2).
        // 'prevNode' is the new head of the rest of the list (e.g., [4,3,5] for k=2,
        // or [4,5] for k=3 after the recursive call).
        
        ListNode* current = head; // 'current' will iterate through the k nodes to be reversed
        count = 0; // Reset count for the reversal loop

        while (count < k) {
            ListNode* next_node = current->next; // Store the next node before modifying current->next
            current->next = prevNode;            // Point current node's next to the previously reversed part
                                                 // (or the result of the recursive call).
                                                 // For the first node in the group, this links it to the rest of the list.
            prevNode = current;                  // Move prevNode to current. 'current' is now the new 'previous'
                                                 // for the next iteration's reversal.
            current = next_node;                 // Move current to the next node in the original list.
            count++;                             // Increment count for the current group reversal.
        }

        // Step 4: After the loop, 'prevNode' will be pointing to the new head of the
        // just-reversed k-group (e.g., node 2 in [2,1,...] for k=2).
        // This is the new head of the segment that was passed into this function call.
        return prevNode;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each node in the linked list is visited a constant number of times: once to check for `k` nodes, and once more to reverse its `next` pointer. `N` is the total number of nodes. |
| **Space** | O(N/k) | The solution uses recursion, and the depth of the recursion stack is proportional to the number of `k`-groups in the list. In the worst case (e.g., `k=1`), this can be `O(N)`. |

## 🔗 Related Problems
- 206. Reverse Linked List
- 92. Reverse Linked List II
- 24. Swap Nodes in Pairs