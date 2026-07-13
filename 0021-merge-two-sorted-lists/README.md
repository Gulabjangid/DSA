# 0021-merge-two-sorted-lists

## 📋 Problem Description
You are given the heads of two singly linked lists, `list1` and `list2`, both of which are already sorted in non-decreasing order. Your task is to merge these two lists into a single new sorted linked list. The new list should be formed by splicing together the nodes of the original two lists, meaning you should reuse the existing nodes rather than creating entirely new ones. Finally, you must return the head of this newly merged sorted linked list.

## 🔍 Examples
```
Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]
Explanation: We compare the heads of list1 (1) and list2 (1). We pick one '1', then compare the next elements. This process continues until all nodes are merged.

Input: list1 = [], list2 = []
Output: []
Explanation: Both input lists are empty, so the merged list is also empty.

Input: list1 = [], list2 = [0]
Output: [0]
Explanation: One list is empty, so the merged list is simply the non-empty list.
```

## 📌 Constraints
*   The number of nodes in both lists (`list1` and `list2`) is in the range `[0, 50]`.
*   The value of each node (`Node.val`) is between `-100` and `100`, inclusive.
*   Both `list1` and `list2` are guaranteed to be sorted in non-decreasing order.

## 🤔 Understanding the Problem
The problem asks us to combine two already sorted linked lists into a single, larger sorted linked list. The key challenge is to maintain the sorted order efficiently while linking the nodes. We need to handle edge cases where one or both lists might be empty. Since we're "splicing together" nodes, we should manipulate the `next` pointers of the existing nodes rather than creating new `ListNode` objects for each value.

## 💡 Core Idea
Since both input lists are already sorted, we can determine the first node of the merged list by simply comparing the values of the current heads of `list1` and `list2`. The node with the smaller value will be the head of the merged list. The rest of the merged list will then be formed by recursively merging the *remaining* part of the chosen list with the *entire* other list.

## 🧠 Approach — Recursion
This problem is a classic example where **Recursion** provides an elegant and concise solution. Recursion is suitable here because the problem can be broken down into smaller, identical subproblems: merging two sorted lists. The base cases are simple (when one list is empty), and the recursive step involves solving a smaller version of the same problem. By repeatedly picking the smaller head and recursively merging the tails, we build up the final sorted list.

## 📝 Step-by-Step Algorithm
1.  **Base Cases:**
    *   If `list1` is empty (i.e., `NULL`), it means there are no more nodes in `list1` to consider. The merged list from this point onwards will simply be `list2`. So, return `list2`.
    *   Similarly, if `list2` is empty (i.e., `NULL`), return `list1`.

2.  **Recursive Step:**
    *   Compare the values of the current head nodes: `list1->val` and `list2->val`.
    *   **If `list1->val` is less than `list2->val`:**
        *   This means `list1`'s current head node should come first in the merged list.
        *   Set `list1->next` to the result of recursively merging `list1->next` (the rest of `list1`) with the entire `list2`.
        *   Return `list1` as the head of this sub-merged list.
    *   **If `list2->val` is less than or equal to `list1->val`:**
        *   This means `list2`'s current head node should come first (or can be chosen first if values are equal).
        *   Set `list2->next` to the result of recursively merging the entire `list1` with `list2->next` (the rest of `list2`).
        *   Return `list2` as the head of this sub-merged list.

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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // Base case 1: If list1 is empty, the merged list is just list2.
        // This also handles the case where both are empty (list1 is NULL, returns list2 which is also NULL).
        if (list1 == NULL) {
            return list2;
        }
        // Base case 2: If list2 is empty, the merged list is just list1.
        if (list2 == NULL) {
            return list1;
        }

        // Recursive step: Compare the current nodes and decide which one comes first.
        // If list1's value is greater than or equal to list2's value,
        // list2's current node should be the head of the merged list.
        if (list1->val >= list2->val) {
            // Set the 'next' pointer of list2's current node to the result of
            // merging list1 (the entire remaining list1) with the rest of list2 (list2->next).
            list2->next = mergeTwoLists(list1, list2->next);
            // Return list2's current node as the head of this sub-merged list.
            return list2;
        }
        // Otherwise (if list1's value is strictly less than list2's value),
        // list1's current node should be the head of the merged list.
        else {
            // Set the 'next' pointer of list1's current node to the result of
            // merging the rest of list1 (list1->next) with list2 (the entire remaining list2).
            list1->next = mergeTwoLists(list1->next, list2);
            // Return list1's current node as the head of this sub-merged list.
            return list1;
        }
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N + M) | Each node from `list1` (N nodes) and `list2` (M nodes) is visited and processed exactly once. |
| **Space** | O(N + M) | In the worst case (e.g., elements strictly alternate, or one list is much longer), the recursion depth can go up to N + M, consuming stack space. |

## 🔗 Related Problems
*   23. Merge k Sorted Lists
*   88. Merge Sorted Array
*   148. Sort List