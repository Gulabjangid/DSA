# 0876-middle-of-the-linked-list

## 📋 Problem Description
Given the `head` of a singly linked list, the task is to find and return its middle node.

If the linked list has an odd number of nodes, there is a single middle node. For example, in a list `[1, 2, 3, 4, 5]`, node `3` is the middle node.

If the linked list has an even number of nodes, there are two middle nodes. In this scenario, the problem specifies that we must return the **second** of these two middle nodes. For example, in a list `[1, 2, 3, 4, 5, 6]`, nodes `3` and `4` are the middle nodes, and we should return node `4`.

The function `middleNode` receives a `ListNode* head` (the head of the linked list) as input and must return a `ListNode*` pointing to the identified middle node.

## 🔍 Examples
```
Input: head = [1,2,3,4,5]
Output: [3,4,5]
Explanation: The list has 5 nodes. Node 3 is the middle node. The output shows the sublist starting from node 3.
```

```
Input: head = [1,2,3,4,5,6]
Output: [4,5,6]
Explanation: The list has 6 nodes. Nodes 3 and 4 are the middle nodes. As per the problem statement, we return the second middle node, which is node 4. The output shows the sublist starting from node 4.
```

```
Input: head = [1]
Output: [1]
Explanation: The list has 1 node. Node 1 is the middle node.
```

## 📌 Constraints
*   The number of nodes in the list is in the range `[1, 100]`.
*   `1 <= Node.val <= 100`

## 🤔 Understanding the Problem
The problem asks us to locate the middle element of a singly linked list. Unlike arrays, linked lists do not allow direct access to elements by index. We must traverse the list from the `head`. A key detail is how to handle lists with an even number of nodes: we need to return the *second* of the two middle nodes. This implies that if a list has `N` nodes, and `N` is even, we want the node at index `N/2` (0-indexed). If `N` is odd, we want the node at index `N/2` (integer division). For example, for `N=5`, `5/2 = 2` (index 2, which is the 3rd node). For `N=6`, `6/2 = 3` (index 3, which is the 4th node). The challenge is to achieve this efficiently without first iterating through the entire list to count its length.

## 💡 Core Idea
The core idea to solve this problem efficiently is to use two pointers that traverse the linked list at different speeds. One pointer moves one step at a time, while the other moves two steps at a time.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern, specifically the "fast and slow" pointer variant. This pattern is exceptionally useful for linked list problems where you need to find a node relative to the end of the list, detect cycles, or find a node at a certain fraction of the list's length without knowing the total length beforehand.

The "fast and slow" pointer approach works perfectly here because by moving one pointer twice as fast as the other, when the faster pointer reaches the end of the list, the slower pointer will naturally be positioned at the middle. This avoids the need for a two-pass approach (first pass to count nodes, second pass to find the middle) and solves the problem in a single traversal. The specific conditions for the fast pointer's movement and termination ensure that the slow pointer correctly lands on the desired middle node, even for even-length lists where the second middle node is required.

## 📝 Step-by-Step Algorithm
1.  **Initialize Pointers**: Create two pointers, `slow` and `fast`, and initialize both to point to the `head` of the linked list.
2.  **Traverse the List**: Start a loop that continues as long as `fast` is not `NULL` and `fast->next` is not `NULL`.
    *   The condition `fast != NULL` ensures that `fast` itself is a valid node.
    *   The condition `fast->next != NULL` ensures that `fast` can take at least one more step, allowing `fast->next->next` to be accessed safely.
3.  **Move Pointers**: Inside the loop:
    *   Move the `slow` pointer one step forward: `slow = slow->next`.
    *   Move the `fast` pointer two steps forward: `fast = fast->next->next`.
4.  **Return Middle Node**: Once the loop terminates, the `slow` pointer will be positioned at the middle node of the linked list (or the second middle node if the list has an even number of elements). Return the `slow` pointer.

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
    ListNode* middleNode(ListNode* head) {
        // Initialize two pointers, 'slow' and 'fast', both starting at the head of the list.
        // The 'slow' pointer will move one step at a time.
        // The 'fast' pointer will move two steps at a time.
        ListNode* slow = head;
        ListNode* fast = head;

        // Traverse the list with both pointers.
        // The loop continues as long as 'fast' is not NULL and 'fast->next' is not NULL.
        // This condition ensures that 'fast' can always take two steps.
        //
        // Let's trace how this handles odd vs. even length lists:
        //
        // Case 1: Odd length list (e.g., 1 -> 2 -> 3 -> 4 -> 5 -> NULL)
        // Initial: slow=1, fast=1
        // Iter 1:  slow=2, fast=3
        // Iter 2:  slow=3, fast=5
        // Loop condition (fast != NULL && fast->next != NULL): fast=5 (not NULL), fast->next=NULL (is NULL).
        // Condition (fast->next != NULL) fails. Loop terminates.
        // 'slow' is at 3, which is the middle node.
        //
        // Case 2: Even length list (e.g., 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> NULL)
        // Initial: slow=1, fast=1
        // Iter 1:  slow=2, fast=3
        // Iter 2:  slow=3, fast=5
        // Iter 3:  slow=4, fast=NULL (fast moved from 5 to 6, then to NULL)
        // Loop condition (fast != NULL && fast->next != NULL): fast=NULL (is NULL).
        // Condition (fast != NULL) fails. Loop terminates.
        // 'slow' is at 4, which is the second middle node (as required by the problem).
        //
        // This logic correctly places 'slow' at the desired middle node for both cases.
        while (fast != NULL && fast->next != NULL) {
            // Move 'slow' one step forward.
            slow = slow->next;
            // Move 'fast' two steps forward.
            fast = fast->next->next;
        }

        // When the loop terminates, 'slow' correctly points to the desired middle node.
        return slow;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The fast pointer traverses the entire list (N nodes), and the slow pointer traverses approximately half the list (N/2 nodes). Both operations are proportional to N. |
| **Space** | O(1) | Only a constant number of extra pointers (`slow`, `fast`) are used, regardless of the input list's size. |

## 🔗 Related Problems
- 141. Linked List Cycle
- 142. Linked List Cycle II
- 19. Remove Nth Node From End of List