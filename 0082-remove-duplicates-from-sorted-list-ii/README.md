# 0082-remove-duplicates-from-sorted-list-ii

## 📋 Problem Description
Given the `head` of a sorted linked list, the task is to delete all nodes that have duplicate numbers. This means if a number appears more than once in the list, *all* occurrences of that number must be removed. Only numbers that appear exactly once in the original list should remain. The resulting linked list must also be sorted.

The function receives a pointer to the `head` of the linked list as input. It must return a pointer to the `head` of the modified sorted linked list.

## 🔍 Examples
```
Input: head = [1,2,3,3,4,4,5]
Output: [1,2,5]
Explanation: Numbers 3 and 4 are duplicates. All occurrences of 3 and 4 are removed.
```

```
Input: head = [1,1,1,2,3]
Output: [2,3]
Explanation: Number 1 is a duplicate. All occurrences of 1 are removed.
```

## 📌 Constraints
*   The number of nodes in the list is in the range `[0, 300]`.
*   `-100 <= Node.val <= 100`
*   The list is guaranteed to be **sorted** in ascending order.

## 🤔 Understanding the Problem
This problem asks us to filter a sorted linked list, keeping only those numbers that are unique (appear exactly once) in the original list. The key distinction from similar problems (like "Remove Duplicates from Sorted List I") is that if a number is duplicated, *all* its instances must be removed, not just the subsequent ones. Edge cases include an empty list, a list with no duplicates, or a list where all elements are duplicates. The sorted nature of the list is a crucial hint, simplifying duplicate detection.

## 💡 Core Idea
Since the list is sorted, duplicate numbers will always appear consecutively. This allows us to identify a sequence of duplicates by comparing adjacent nodes. The core idea is to use two pointers to traverse the list: one to build the new list (pointing to the last *kept* node) and another to scan the original list, skipping entire blocks of duplicate values.

## 🧠 Approach — Iterative with Dummy Node and Two Pointers
This problem can be solved efficiently using an iterative approach with a **dummy node** and **two pointers**.
The dummy node simplifies handling edge cases, especially when the original head itself needs to be removed (e.g., if the first element is a duplicate).
One pointer (`prev`) will track the last node that is confirmed to be part of the result list (i.e., not a duplicate). The other pointer (`head`) will iterate through the original list, identifying and skipping duplicate sequences. This pattern is well-suited for linked list manipulations where elements might need to be removed or re-linked.

## 📝 Step-by-Step Algorithm

1.  **Initialize a Dummy Node**: Create a `dummy` node and set its `next` pointer to the original `head` of the list. This dummy node acts as a placeholder, making it easier to handle cases where the actual head of the list might be a duplicate and needs to be removed. The `dummy.next` will eventually point to the head of our new, de-duplicated list.

2.  **Initialize Pointers**:
    *   `prev`: A pointer initialized to the `dummy` node. This pointer will always point to the node *before* the current sequence we are examining, and it will be used to link to the first non-duplicate node found.
    *   `head`: A pointer initialized to the original `head` of the list. This pointer will traverse the list.

3.  **Traverse the List**: Loop while `head` is not `NULL`.

4.  **Detect Duplicate Sequence**: Inside the loop, check if the current `head` node is part of a duplicate sequence:
    *   This happens if `head->next` is not `NULL` AND `head->val` is equal to `head->next->val`.

5.  **Handle Duplicate Sequence**: If a duplicate sequence is detected:
    *   Store the value of the duplicate (`val = head->val`).
    *   Enter an inner loop: while `head` is not `NULL` AND `head->val` is equal to `val` (the duplicate value), keep advancing `head` to `head->next`. This effectively skips *all* nodes that have this duplicate value.
    *   After the inner loop, `head` will point to either `NULL` or the first node with a value different from the duplicate.
    *   Now, link `prev->next` directly to this new `head`. This action effectively removes the entire block of duplicate nodes from the list. **Crucially, `prev` does NOT move forward in this case**, as the node it was pointing to (or the sequence after it) was removed.

6.  **Handle Unique Node**: If `head` is NOT part of a duplicate sequence (i.e., `head->next` is `NULL` or `head->val` is different from `head->next->val`):
    *   This means `head` points to a unique node that should be kept.
    *   Advance `prev` to `head` (because `head` is a unique node and now becomes the last kept node).
    *   Advance `head` to `head->next` to continue scanning the list.

7.  **Return Result**: After the main loop finishes, `dummy.next` will point to the head of the new list containing only distinct numbers. Return `dummy.next`.

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
    ListNode* deleteDuplicates(ListNode* head) {
        // Create a dummy node. This simplifies handling cases where the original head
        // itself might be a duplicate and needs to be removed.
        // The dummy node's next pointer will eventually point to the head of our
        // modified list.
        ListNode dummy(0);
        dummy.next = head;

        // 'prev' pointer: points to the last node that is confirmed to be part of
        // the result list (i.e., not a duplicate).
        // Initially, 'prev' points to the dummy node.
        ListNode* prev = &dummy; 

        // 'head' pointer: iterates through the original list.
        while (head != NULL) {
            // Check if the current 'head' node is the start of a duplicate sequence.
            // This is true if 'head' has a next node AND 'head->val' is equal to 'head->next->val'.
            if (head->next && head->val == head->next->val) {
                // If it's a duplicate sequence, store the value of the duplicate.
                int val = head->val;

                // Skip all nodes that have this duplicate value.
                // The inner loop advances 'head' until it points to NULL or a node
                // with a different value.
                while (head != NULL && head->val == val) {
                    head = head->next;
                }

                // After skipping all duplicates, 'head' now points to the first
                // non-duplicate node (or NULL if all remaining nodes were duplicates).
                // Link 'prev->next' directly to this new 'head'.
                // This effectively removes the entire block of duplicate nodes from the list.
                // 'prev' does NOT move forward here because the node(s) it was pointing to
                // (or the sequence after it) were removed.
                prev->next = head; 
            } 
            else {
                // If 'head' is not part of a duplicate sequence (i.e., it's a unique node
                // that should be kept), then:
                // 1. Advance 'prev' to 'head', as 'head' is now the last kept node.
                prev = head;
                // 2. Advance 'head' to the next node to continue scanning.
                head = head->next;
            }
        }

        // The de-duplicated list starts after the dummy node.
        return dummy.next;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The `head` pointer traverses the list from start to end. Each node is visited at most twice (once by the outer `while` loop, and potentially once more by the inner `while` loop if it's part of a duplicate block). Since `head` always moves forward, the total operations are proportional to the number of nodes `N`. |
| **Space** | O(1) | We only use a few extra pointers (`dummy`, `prev`, `head`) and a temporary variable (`val`), which consume a constant amount of extra space regardless of the input list size. |

## 🔗 Related Problems
- 83. Remove Duplicates from Sorted List
- 21. Merge Two Sorted Lists
- 19. Remove Nth Node From End of List