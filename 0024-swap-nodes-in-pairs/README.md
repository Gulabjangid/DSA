# 0024-swap-nodes-in-pairs

## 📋 Problem Description
Given the `head` of a singly linked list, the task is to swap every two adjacent nodes and return the head of the modified list. The problem explicitly states that you must solve it without modifying the values within the nodes; only the nodes themselves (their `next` pointers) may be changed.

The function `swapPairs` receives a `ListNode* head` as input, representing the head of the linked list. It must return a `ListNode*`, which is the head of the linked list after all adjacent pairs have been swapped.

## 🔍 Examples
```
Input: head = [1,2,3,4]
Output: [2,1,4,3]
Explanation: The pair (1,2) is swapped to (2,1), and (3,4) is swapped to (4,3).

Input: head = []
Output: []
Explanation: An empty list remains empty.

Input: head = [1]
Output: [1]
Explanation: A list with a single node has no pairs to swap.

Input: head = [1,2,3]
Output: [2,1,3]
Explanation: The pair (1,2) is swapped to (2,1). Node 3 remains in its position as it doesn't have a pair.
```

## 📌 Constraints
*   The number of nodes in the list is in the range `[0, 100]`.
*   `0 <= Node.val <= 100`

## 🤔 Understanding the Problem
The problem asks us to rearrange a linked list by swapping nodes in groups of two. This means if we have `A -> B -> C -> D`, it should become `B -> A -> D -> C`. A crucial detail is that we cannot change node values; we must manipulate the `next` pointers. Edge cases include an empty list, a list with a single node (no pairs to swap), and a list with an odd number of nodes (the last node remains in place). The core challenge lies in correctly updating pointers to perform the swaps and link the swapped segments together.

## 💡 Core Idea
The problem can be broken down into smaller, identical subproblems: swapping the first pair of nodes and then recursively solving the problem for the rest of the list. The key is to correctly link the swapped pair to the result of the recursive call.

## 🧠 Approach — Recursion
This problem is well-suited for a recursive approach. We can define the problem for a linked list as "swap pairs in this list and return the new head." If the list has at least two nodes, we can swap the first two, then recursively call the same function on the rest of the list (starting from the third node). The result of this recursive call (the head of the swapped sublist) is then linked to the first node of our current swapped pair. This pattern naturally handles the linking of segments and base cases (empty list or single node).

## 📝 Step-by-Step Algorithm
1.  **Base Case Check**:
    *   Initialize a temporary pointer, `temp`, to the current `head` of the list segment we are considering.
    *   Iterate `k=2` times (for pairs) using `temp` to check if there are at least two nodes in the current segment.
    *   If `temp` becomes `NULL` at any point during this check (meaning there are fewer than `k` nodes), it implies no pair can be formed. In this scenario, return the original `head` of this segment as no swapping is needed.

2.  **Recursive Call**:
    *   If `k` nodes were found, `temp` now points to the `(k+1)`-th node (or `NULL` if the list ends exactly after `k` nodes).
    *   Make a recursive call to `swapPairs` with this `temp` as the new `head`. This call will handle swapping pairs in the remainder of the list and return the new head of that *already swapped* sublist. Store this result in a `prev` pointer.

3.  **Reverse Current `k` Nodes (Swap the Pair)**:
    *   Reset `temp` back to the original `head` of the current `k`-node segment (the first node of the pair).
    *   Iterate `k=2` times to reverse this current pair:
        *   Store the `next` node of `temp` in a temporary variable `next_node` to avoid losing the reference.
        *   Set `temp->next` to `prev`. This links the current node (`temp`) to the `prev` pointer, which holds either the result of the recursive call (the head of the swapped subsequent list) or the previously processed node within the current `k`-segment reversal.
        *   Update `prev` to `temp`. `prev` now points to the head of the *growing* reversed segment (e.g., after processing `1`, `prev` becomes `1`).
        *   Move `temp` to `next_node` to continue processing the next node in the original list.

4.  **Return New Head**:
    *   After the loop, `prev` will point to the new head of the `k`-node segment that has just been reversed (e.g., for `1->2`, `prev` will be `2`). Return `prev`.

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
        // 'temp' will be used to traverse the list and find the k-th node.
        ListNode* temp = head;
        // 'k' is fixed to 2 for swapping pairs.
        int k = 2;

        int count = 0;
        // Step 1: Check if there are at least 'k' nodes remaining in the current segment.
        // This loop advances 'temp' to the (k+1)-th node (or NULL if fewer than k nodes).
        while (count < k) {
            // If 'temp' becomes NULL before 'k' nodes are counted,
            // it means there aren't enough nodes to form a full pair.
            if (temp == NULL) {
                // In this case, no swapping is needed for this segment,
                // so return the original head of this segment.
                return head;
            }
            temp = temp->next; // Move 'temp' to the next node.
            count++;           // Increment count of nodes found.
        }

        // At this point:
        // - 'head' points to the first node of the current 'k' segment.
        // - 'temp' points to the (k+1)-th node (or NULL if list ends exactly after k nodes).

        // Step 2: Recursively call swapPairs for the rest of the list,
        // starting from the (k+1)-th node ('temp').
        // 'prev' will store the new head of the *already swapped* sublist
        // that follows the current 'k' nodes.
        ListNode* prev = swapPairs(temp);

        // Step 3: Reverse the current 'k' nodes (which is a pair for k=2).
        // 'temp' is reset to the beginning of the current 'k' segment ('head').
        temp = head;
        count = 0; // Reset count for the reversal loop.

        // This loop performs the reversal of the current 'k' nodes.
        while (count < k) {
            // Store the next node before modifying 'temp->next'.
            ListNode* next_node = temp->next;
            // Link the current node ('temp') to 'prev'.
            // 'prev' initially holds the result of the recursive call (swapped tail),
            // and then progressively becomes the head of the *growing* reversed segment.
            temp->next = prev;
            // Move 'prev' to the current node ('temp').
            // 'prev' now points to the new head of the reversed segment being built.
            prev = temp;
            // Move 'temp' to the next node in the original list.
            temp = next_node;
            count++; // Increment count.
        }
        // After this loop, 'prev' will be the new head of the reversed 'k' segment.
        // For k=2, if head was 1->2, after this loop, prev will be 2, and the segment is 2->1.
        // The 1->next would be linked to the result of the recursive call.

        // Step 4: Return the new head of the reversed 'k' segment.
        return prev;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each node in the linked list is visited a constant number of times: once in the initial `while` loop to check for `k` nodes, once as part of a recursive call, and once in the second `while` loop to perform the reversal. Since `k` is a constant (2), these operations are constant per node. |
| **Space** | O(N) | The recursive calls consume stack space. In the worst case, for a list of N nodes, there will be approximately N/k recursive calls on the stack. Since `k` is a constant (2), the depth of the recursion stack is proportional to N, leading to O(N) space complexity. |

## 🔗 Related Problems
- 25. Reverse Nodes in k-Group
- 206. Reverse Linked List
- 92. Reverse Linked List II