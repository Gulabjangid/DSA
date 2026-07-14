# 0203-remove-linked-list-elements

## 📋 Problem Description
Given the `head` of a singly linked list and an integer `val`, the task is to remove all nodes from the linked list that have a value equal to `val`. After removing all such nodes, the function should return the `head` of the modified linked list.

**Input**:
*   `head`: A pointer to the first node of the linked list.
*   `val`: An integer representing the value to be removed from the list.

**Output**:
*   A pointer to the `head` of the new, modified linked list.

## 🔍 Examples
```
Input: head = [1,2,6,3,4,5,6], val = 6
Output: [1,2,3,4,5]
Explanation: All nodes with value 6 are removed from the list.
```

```
Input: head = [], val = 1
Output: []
Explanation: The input list is empty, so the output is also an empty list.
```

```
Input: head = [7,7,7,7], val = 7
Output: []
Explanation: All nodes in the list have the value 7, which is the value to be removed. Therefore, all nodes are removed, resulting in an empty list.
```

## 📌 Constraints
*   The number of nodes in the list is in the range `[0, 10^4]`.
*   `1 <= Node.val <= 50`
*   `0 <= val <= 50`

## 🤔 Understanding the Problem
The problem requires us to modify a linked list by deleting all nodes that contain a specific target value. This involves carefully manipulating pointers. A key challenge is that deleting a node requires updating the `next` pointer of its *predecessor*. Special attention must be paid to edge cases such as when the head node itself needs to be removed, when multiple consecutive nodes need to be removed, or when the entire list becomes empty after deletions.

## 💡 Core Idea
The core idea is to iterate through the linked list and, for each node, decide whether to keep it or remove it. Since deleting a node requires access to its preceding node, we can use a pointer that always points to the *last kept node* (or the node *before* the one we are currently evaluating for removal). We also need to handle the head of the list as a special case, as it has no predecessor.

## 🧠 Approach — Iterative Traversal
This problem is best solved using an **Iterative Traversal** approach. We traverse the linked list from beginning to end, examining each node. This pattern is suitable because we need to inspect every element and potentially modify the list structure based on a condition. By maintaining a pointer to the *current* node (which acts as the predecessor for the *next* node), we can efficiently update `next` pointers to bypass and remove unwanted nodes.

## 📝 Step-by-Step Algorithm

1.  **Handle Initial Head Nodes**:
    *   First, address the scenario where the `head` node (or several initial nodes) itself needs to be removed.
    *   Continuously advance the `head` pointer to `head->next` as long as `head` is not `NULL` and `head->val` is equal to the `val` to be removed.
    *   After this step, `head` will either point to the first node that *should not* be removed, or it will be `NULL` if the entire list was empty or all initial nodes were removed.

2.  **Initialize Current Pointer for Traversal**:
    *   Set a `curr` pointer to the (potentially new) `head`. This `curr` pointer will be used to traverse the rest of the list. It will always point to the node *before* the one we are currently checking for removal, allowing us to modify its `next` pointer.

3.  **Iterate and Remove Remaining Nodes**:
    *   Start a loop that continues as long as `curr` is not `NULL` (meaning we haven't reached the end of the list) AND `curr->next` is not `NULL` (meaning there's at least one node after `curr` to check).
    *   Inside the loop, check the value of `curr->next`:
        *   **If `curr->next->val` is equal to `val`**:
            *   This means the node `curr->next` needs to be removed.
            *   Update `curr->next` to point to `curr->next->next`. This effectively bypasses `curr->next`, removing it from the list.
            *   **Crucially, do NOT advance `curr`** in this case. The new `curr->next` (which was `curr->next->next`) might also have the `val` and needs to be checked immediately.
        *   **If `curr->next->val` is NOT equal to `val`**:
            *   This means `curr->next` should be kept.
            *   Safely advance `curr` to `curr->next` to move to the next node in the list.

4.  **Return Modified Head**:
    *   After the loop finishes, the `head` pointer (which might have been updated in step 1) will correctly point to the beginning of the modified list. Return this `head`.

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
    ListNode* removeElements(ListNode* head, int value) {

        // Step 1: Handle cases where the head node(s) themselves need to be removed.
        // We repeatedly advance the head pointer as long as it's not NULL
        // and its value matches the 'value' to be removed.
        // This handles scenarios like:
        // - head = [7,7,7,7], value = 7 (all nodes removed, head becomes NULL)
        // - head = [6,1,2], value = 6 (head becomes [1,2])
        while (head != NULL && head->val == value) {
            head = head->next; // Move head to the next node
        }

        // After the above loop, 'head' now points to the first node
        // that should NOT be removed, or it's NULL if the list is empty
        // or all initial nodes were removed.

        // Initialize a 'curr' pointer to traverse the rest of the list.
        // 'curr' will always point to the node *before* the one we are checking
        // for removal, allowing us to modify its 'next' pointer.
        ListNode* curr = head;

        // Step 2: Traverse the rest of the list to remove elements.
        // We need to check 'curr->next' because we modify 'curr->next' to remove a node.
        // The loop continues as long as 'curr' is not NULL (meaning there are nodes to process)
        // and 'curr->next' is not NULL (meaning there's at least one node after 'curr' to check).
        while (curr != NULL && curr->next != NULL) {
            // Check if the next node's value matches the 'value' to be removed.
            if (curr->next->val == value) {
                // If it matches, we need to remove 'curr->next'.
                // We do this by making 'curr->next' point to 'curr->next->next',
                // effectively bypassing and "deleting" the node 'curr->next'.
                curr->next = curr->next->next;
                // IMPORTANT: Do NOT advance 'curr' here.
                // The new 'curr->next' might also have the 'value' and needs to be checked.
                // For example, if list is [1,6,6,2] and value is 6,
                // after removing the first 6, list becomes [1,6,2].
                // 'curr' is still at 1, and 'curr->next' is now the second 6, which also needs removal.
            } else {
                // If the next node's value does not match, it means this node should be kept.
                // So, we safely advance 'curr' to the next node.
                curr = curr->next;
            }
        }

        // After processing the entire list, 'head' will point to the new head
        // of the modified list (which could be NULL if all elements were removed).
        return head;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the linked list once. Each node is visited and processed a constant number of times (either skipped or its predecessor's `next` pointer is updated). |
| **Space** | O(1) | We only use a few extra pointers (`head`, `curr`) which consume a constant amount of space, regardless of the number of nodes in the list. |

## 🔗 Related Problems
*   206. Reverse Linked List
*   21. Merge Two Sorted Lists
*   83. Remove Duplicates from Sorted List