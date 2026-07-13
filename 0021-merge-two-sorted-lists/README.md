# 0021-merge-two-sorted-lists

## 📋 Problem Description
You are given the heads of two singly linked lists, `list1` and `list2`, both of which are sorted in non-decreasing order. Your task is to merge these two lists into a single new sorted linked list. The new list should be formed by splicing together the nodes of the original two lists, meaning you should reuse the existing nodes rather than creating entirely new ones.

The function should return the head of the merged sorted linked list.

**Input:**
- `list1`: The head of the first sorted linked list.
- `list2`: The head of the second sorted linked list.

**Output:**
- The head of a new linked list that contains all nodes from `list1` and `list2`, sorted in non-decreasing order.

## 🔍 Examples
```
Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]
Explanation: The two lists are merged by picking the smaller head at each step.
             Initially, 1 (from list1) and 1 (from list2) are compared. Let's say we pick list1's 1.
             Then, 2 (from list1) and 1 (from list2) are compared. We pick list2's 1.
             This continues until all nodes are merged.
```

```
Input: list1 = [], list2 = []
Output: []
Explanation: Merging two empty lists results in an empty list.
```

```
Input: list1 = [], list2 = [0]
Output: [0]
Explanation: Merging an empty list with a list containing [0] results in [0].
```

## 📌 Constraints
* The number of nodes in both lists (`list1` and `list2`) is in the range `[0, 50]`.
* Node values are between `-100` and `100` (inclusive).
* Both `list1` and `list2` are guaranteed to be sorted in non-decreasing order.

## 🤔 Understanding the Problem
The problem asks us to combine two already sorted linked lists into a single, larger sorted linked list. The key challenge is to maintain the sorted order efficiently while correctly handling the pointers of the linked list nodes. We need to be careful with edge cases such as one or both lists being empty. Since the lists are already sorted, we can leverage this property to build the merged list without needing to sort it from scratch.

## 💡 Core Idea
Since both input lists are sorted, we can determine the first node of the merged list by simply comparing the values of the current heads of `list1` and `list2`. The node with the smaller value will be the head of the merged list. The rest of the merged list can then be formed by recursively merging the *remainder* of the chosen list with the *other* list.

## 🧠 Approach — Recursion
This problem is perfectly suited for a **recursive** approach.
The reason recursion fits so well here is that the problem exhibits optimal substructure and overlapping subproblems (though the subproblems aren't strictly overlapping in the DP sense, they are smaller instances of the same problem). To merge two lists, we make a decision about the current heads, and then the problem reduces to merging two smaller lists. The base cases for the recursion are when one of the lists becomes empty, at which point the non-empty list (or an empty list if both are empty) is simply appended.

## 📝 Step-by-Step Algorithm
1. **Base Cases:**
   - If `list1` is empty (i.e., `NULL`), it means there are no more nodes in `list1` to merge. In this case, the remaining `list2` (which might also be empty) is the result of the merge from this point onwards. So, return `list2`.
   - Similarly, if `list2` is empty, return `list1`.

2. **Recursive Step:**
   - Compare the values of the current head nodes of `list1` and `list2`.
   - **If `list1->val` is less than `list2->val`:**
     - This means `list1`'s current head node should come first in the merged list.
     - We set `list1->next` to the result of recursively merging `list1->next` (the rest of `list1`) with the entire `list2`.
     - Then, we return `list1` as the head of the merged sub-list.
   - **Else (if `list2->val` is less than or equal to `list1->val`):**
     - This means `list2`'s current head node should come first (or equally first).
     - We set `list2->next` to the result of recursively merging the entire `list1` with `list2->next` (the rest of `list2`).
     - Then, we return `list2` as the head of the merged sub-list.

This process continues until one of the base cases is hit, unwinding the recursion and building the merged list from the tail up to the head.

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
        // This also covers the case where both are empty (list2 would be NULL).
        if (list1 == NULL) {
            return list2;
        }
        // Base case 2: If list2 is empty, the merged list is just list1.
        if (list2 == NULL) {
            return list1;
        }

        // Recursive step: Compare the values of the current heads.
        // If list1's head value is less than or equal to list2's head value.
        // We choose list1's current node as the next node in the merged list.
        if (list1->val <= list2->val) {
            // The 'next' pointer of list1's current node will point to the
            // result of merging the rest of list1 (list1->next) with the entire list2.
            list1->next = mergeTwoLists(list1->next, list2);
            // Return list1's current node as the head of this merged sub-list.
            return list1;
        }
        // Else, list2's head value is smaller.
        // We choose list2's current node as the next node in the merged list.
        else {
            // The 'next' pointer of list2's current node will point to the
            // result of merging the entire list1 with the rest of list2 (list2->next).
            list2->next = mergeTwoLists(list1, list2->next);
            // Return list2's current node as the head of this merged sub-list.
            return list2;
        }
    }
};

```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N + M) | Each recursive call processes one node (either from `list1` or `list2`) and makes one recursive call. In total, every node from both lists is visited exactly once. `N` is the number of nodes in `list1`, `M` in `list2`. |
| **Space** | O(N + M) | Due to the recursive calls, the call stack will grow. In the worst case (e.g., merging `[1,2,3]` with `[4,5,6]` or `[1]` with `[2,3,4]`), the depth of the recursion stack can be equal to the total number of nodes in the merged list (`N + M`). |

## 🔗 Related Problems
- 23. Merge k Sorted Lists (An extension where you merge multiple sorted lists)
- 148. Sort List (Involves splitting a list and then merging sorted sub-lists, similar to merge sort)
- 86. Partition List (Another problem involving rearranging linked list nodes based on a condition)