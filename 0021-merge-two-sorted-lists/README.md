# 0021-merge-two-sorted-lists

## 📋 Problem Description
You are given the heads of two singly linked lists, `list1` and `list2`, both of which are sorted in non-decreasing order. Your task is to merge these two lists into a single new sorted linked list. The new list should be formed by splicing together the nodes of the original two lists. You need to return the head of this newly merged sorted linked list.

**Input:**
*   `list1`: The head of the first sorted linked list.
*   `list2`: The head of the second sorted linked list.

**Output:**
*   The head of the merged, sorted linked list.

## 🔍 Examples
```
Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]
Explanation: The nodes from both lists are combined and reordered to maintain sorted order.
```

```
Input: list1 = [], list2 = []
Output: []
Explanation: Both input lists are empty, so the merged list is also empty.
```

```
Input: list1 = [], list2 = [0]
Output: [0]
Explanation: One list is empty, the other contains a single node. The merged list is simply the non-empty list.
```

## 📌 Constraints
*   The number of nodes in both lists (`list1` and `list2`) is in the range `[0, 50]`.
*   `-100 <= Node.val <= 100`
*   Both `list1` and `list2` are sorted in **non-decreasing** order.

## 🤔 Understanding the Problem
The problem asks us to combine two already sorted linked lists into a single, larger sorted linked list. The key here is that the input lists are *already sorted*, which is a crucial property we must leverage. We don't need to create new nodes; instead, we should rearrange the `next` pointers of the existing nodes to form the new merged list. We also need to handle edge cases where one or both lists might be empty.

## 💡 Core Idea
Since both lists are sorted, at any point, the smallest available node must be either the head of `list1` or the head of `list2`. We can pick the smaller of the two, make it the next node in our merged list, and then recursively solve the problem for the rest of the lists.

## 🧠 Approach — Recursion
This problem is perfectly suited for a **Recursive** approach. Recursion works well here because the problem can be broken down into smaller, identical subproblems: merging the *rest* of the lists after picking one node. The base cases are simple (when one list becomes empty), and the recursive step involves comparing the heads and making a choice. This pattern is often referred to as a "divide and conquer" strategy where the "conquer" step is trivial (just picking one node) and the "divide" step is the recursive call.

## 📝 Step-by-Step Algorithm

1.  **Base Cases:**
    *   If `list1` is empty (i.e., `NULL`), it means there are no more nodes to take from `list1`. The remaining merged list is simply `list2`. Return `list2`.
    *   Similarly, if `list2` is empty (i.e., `NULL`), return `list1`.

2.  **Recursive Step:**
    *   Compare the values of the current head nodes: `list1->val` and `list2->val`.
    *   **If `list1->val` is less than or equal to `list2->val`:**
        *   This means `list1->val` should be the next node in our merged list.
        *   Set `list1->next` to the result of recursively merging the *rest of `list1`* (`list1->next`) with the *entire `list2`*.
        *   Return `list1` as the head of the current merged sublist.
    *   **Else (if `list2->val` is less than `list1->val`):**
        *   This means `list2->val` should be the next node in our merged list.
        *   Set `list2->next` to the result of recursively merging the *entire `list1`* with the *rest of `list2`* (`list2->next`).
        *   Return `list2` as the head of the current merged sublist.

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
        // Base case: If either list is empty, the merged list is the other list.
        // If both are empty, it returns NULL (e.g., list1 is NULL, so it returns list2 which is also NULL).
        if (list1 == NULL) {
            return list2;
        }
        if (list2 == NULL) {
            return list1;
        }

        // Recursive step: Compare the current head nodes and decide which one comes first.
        if (list1->val <= list2->val) {
            // If list1's current node is smaller or equal, it should be the head of the merged list.
            // Recursively merge the rest of list1 (list1->next) with the entire list2.
            // The result of this recursive call becomes the next node of list1's current head.
            list1->next = mergeTwoLists(list1->next, list2);
            // Return list1's current head as the head of the merged sub-list.
            return list1;
        } else {
            // If list2's current node is smaller, it should be the head of the merged list.
            // Recursively merge the entire list1 with the rest of list2 (list2->next).
            // The result of this recursive call becomes the next node of list2's current head.
            list2->next = mergeTwoLists(list1, list2->next);
            // Return list2's current head as the head of the merged sub-list.
            return list2;
        }
    }
};

```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N + M) | Each node from `list1` (N nodes) and `list2` (M nodes) is visited and processed exactly once during the recursive calls. |
| **Space** | O(N + M) | In the worst case, the recursion depth can go up to N + M (e.g., if elements alternate between lists, or one list is much longer than the other), leading to N + M stack frames. |

## 🔗 Related Problems
*   23. Merge k Sorted Lists
*   148. Sort List
*   206. Reverse Linked List