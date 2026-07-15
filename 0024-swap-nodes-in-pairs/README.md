# 0024-swap-nodes-in-pairs

## 📋 Problem Description
Given the `head` of a singly-linked list, the task is to swap every two adjacent nodes and return the head of the modified list. The solution must not modify the values within the nodes; instead, only the nodes themselves (their `next` pointers) should be changed.

**Input:** A pointer to the `head` of a singly-linked list.
**Output:** A pointer to the `head` of the linked list after swapping every two adjacent nodes.

## 🔍 Examples
```
Input: head = [1,2,3,4]
Output: [2,1,4,3]
Explanation: The first pair (1,2) swaps to (2,1). The second pair (3,4) swaps to (4,3).

Input: head = []
Output: []
Explanation: An empty list remains empty.

Input: head = [1]
Output: [1]
Explanation: A list with a single node has no pairs to swap, so it remains unchanged.

Input: head = [1,2,3]
Output: [2,1,3]
Explanation: The first pair (1,2) swaps to (2,1). Node 3 remains as it is not part of a pair.
```

## 📌 Constraints
*   The number of nodes in the list is in the range `[0, 100]`.
*   `0 <= Node.val <= 100`

## 🤔 Understanding the Problem
The problem asks us to rearrange a linked list by swapping adjacent pairs of nodes. For instance, `(A -> B -> C -> D)` should become `(B -> A -> D -> C)`. A crucial constraint is that we cannot simply swap the `val` fields; we must manipulate the `next` pointers to physically reorder the nodes. Edge cases include an empty list, a list with a single node (where no swaps are possible), and a list with an odd number of nodes (where the last node remains in its original position).

## 💡 Core Idea
The problem can be solved by recursively processing the linked list in segments of `k` nodes (where `k=2` for pairs). For each segment, we first determine the head of the *next* segment by making a recursive call, and then we reverse the current `k`-node segment, connecting its tail to the head of the next segment.

## 🧠 Approach — Recursion with K-Group Reversal
This problem is a specific instance of the "Reverse Nodes in K-Group" pattern, with `k=2`. The solution leverages recursion by:
1.  Identifying the `k`-th node (or checking if `k` nodes exist).
2.  Making a recursive call to handle the subproblem starting from the `(k+1)`-th node. This call returns the new head of the processed sublist.
3.  Then, iteratively reversing the current `k` nodes.
4.  Connecting the original `head` (which becomes the tail of the reversed `k`-group) to the result of the recursive call.
5.  Returning the new head of the reversed `k`-group. This recursive decomposition allows for elegant manipulation of linked list segments.

## 📝 Step-by-Step Algorithm
1.  **Define `k`**: Set `k = 2` since we need to swap every *two* adjacent nodes.
2.  **Check for Base Cases / Insufficient Nodes**:
    *   Initialize a temporary pointer, `temp`, to the current `head`.
    *   Iterate `k` times, moving `temp` forward.
    *   If `temp` becomes `NULL` at any point during this iteration (meaning there are fewer than `k` nodes remaining), then there's nothing to swap in this segment. Return the current `head` as is.
3.  **Recursive Call**:
    *   If there are at least `k` nodes, `temp` will now point to the `(k+1)`-th node (the node immediately after the current `k`-group).
    *   Make a recursive call `swapPairs(temp)`. This call will handle swapping pairs in the rest of the list starting from the `(k+1)`-th node. Store its result (the new head of the recursively processed sublist) in a pointer, say `prev`.
4.  **Reverse Current `k`-Group**:
    *   Reset `temp` back to the original `head` of the current `k`-group.
    *   Initialize a `count` to 0.
    *   Loop `k` times:
        *   Store the `next` node of `temp` (i.e., `temp->next`) in a temporary pointer, `next_node`, to avoid losing the reference to the rest of the original list.
        *   Set `temp->next = prev`. This is the crucial step:
            *   For the first node of the `k`-group, it connects to the result of the recursive call (`prev` from step 3).
            *   For subsequent nodes in the `k`-group, it connects to the *previously processed* node within the current `k`-group, effectively reversing the links.
        *   Update `prev = temp`. `prev` now points to the node that was just processed, which will become the new "next" for the subsequent node in the reversal.
        *   Move `temp = next_node` to advance to the next node in the original list.
        *   Increment `count`.
5.  **Return New Head**: After the loop, `prev` will point to the `k`-th node of the original group (which is now the new head of this swapped `k`-group). Return `prev`.

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
    ListNode* swapPairs(ListNode* head) {
        // Define k, the number of nodes in each group to be processed/reversed.
        // For this problem, we swap pairs, so k = 2.
        int k = 2;

        // --- Step 1: Check if there are at least 'k' nodes remaining ---
        // Use a temporary pointer to traverse 'k' steps from the current head.
        ListNode* temp = head;
        int count = 0;

        while (count < k) {
            // If we encounter NULL before completing 'k' steps,
            // it means there are fewer than 'k' nodes.
            // In this case, we cannot form a complete pair/group,
            // so we return the head as is (no changes needed for this segment).
            if (temp == NULL) {
                return head;
            }
            temp = temp->next; // Move to the next node
            count++;           // Increment count
        }

        // --- Step 2: Recursive Call ---
        // If we reached here, it means there are at least 'k' nodes.
        // 'temp' now points to the (k+1)-th node (the node *after* the current k-group).
        // Recursively call swapPairs on the rest of the list starting from 'temp'.
        // 'prev' will store the new head of the sublist that has been recursively processed and swapped.
        ListNode* prev = swapPairs(temp);

        // --- Step 3: Reverse the current 'k' nodes and connect them ---
        // Reset 'temp' back to the original 'head' of the current k-group.
        temp = head;
        count = 0; // Reset count for the reversal loop.

        // Iterate 'k' times to reverse the links for the current k-group.
        while (count < k) {
            // Store the next node in the original list to avoid losing it.
            ListNode* next_node = temp->next;

            // This is the core reversal step:
            // The current node's 'next' pointer is set to 'prev'.
            // - For the first node of the group (e.g., '1' in [1,2,3,4]),
            //   its 'next' will point to the result of the recursive call (which is the new head of [4,3]).
            // - For subsequent nodes in the group (e.g., '2' in [1,2,3,4]),
            //   its 'next' will point to the node that was just processed ('1'),
            //   effectively building the reversed segment.
            temp->next = prev;

            // 'prev' is updated to the current node. This makes 'temp' the new 'head'
            // of the reversed segment being built so far.
            prev = temp;

            // Move 'temp' to the next node in the original list.
            temp = next_node;
            count++;
        }

        // --- Step 4: Return the new head of the current k-group ---
        // After the loop, 'prev' will point to the k-th node of the original group
        // (e.g., '2' in [1,2]), which is now the new head of this swapped k-group.
        return prev;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each node in the linked list is visited and processed a constant number of times (once in the initial `k`-step check, and once in the `k`-step reversal loop). Therefore, the time complexity is directly proportional to the number of nodes, N. |
| **Space** | O(N) | Due to the recursive calls, the call stack will grow. In the worst case, for a list of N nodes, there will be approximately N/2 recursive calls (one for each pair). Each call adds a frame to the stack. Thus, the space complexity is proportional to the number of nodes, N. |

## 🔗 Related Problems
- 206. Reverse Linked List
- 25. Reverse Nodes in k-Group
- 19. Remove Nth Node From End of List