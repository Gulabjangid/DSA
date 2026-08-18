# 0160-intersection-of-two-linked-lists

## 📋 Problem Description
Given the heads of two singly linked lists, `headA` and `headB`, the task is to find and return the node at which the two lists begin to intersect. If the two linked lists do not intersect at all, the function should return `null`.

It's guaranteed that there are no cycles anywhere in the entire linked structure. The original structure of the linked lists must remain unchanged after the function returns.

**Input:**
*   `headA`: A pointer to the head of the first singly linked list.
*   `headB`: A pointer to the head of the second singly linked list.

**Output:**
*   A pointer to the `ListNode` where the two lists intersect.
*   `null` if no intersection exists.

## 🔍 Examples

**Example 1:**
```
Input:  intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
Output: Intersected at '8'
Explanation:
List A: 4 -> 1 -> 8 -> 4 -> 5
List B: 5 -> 6 -> 1 -> 8 -> 4 -> 5
The lists intersect at the node with value 8. Node '4' and '1' in listA are unique to A. Nodes '5', '6', '1' in listB are unique to B. The node with value '8' is the same physical node in memory for both lists.
```

**Example 2:**
```
Input:  intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
Output: Intersected at '2'
Explanation:
List A: 1 -> 9 -> 1 -> 2 -> 4
List B: 3 -> 2 -> 4
The lists intersect at the node with value 2.
```

**Example 3:**
```
Input:  intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
Output: No intersection
Explanation:
List A: 2 -> 6 -> 4
List B: 1 -> 5
The two lists do not intersect, so return null.
```

## 📌 Constraints
*   The number of nodes in `listA` (`m`) is between 1 and `3 * 10^4`.
*   The number of nodes in `listB` (`n`) is between 1 and `3 * 10^4`.
*   `1 <= Node.val <= 10^5`
*   `0 <= skipA <= m` (number of nodes to skip in `listA` to reach intersection)
*   `0 <= skipB <= n` (number of nodes to skip in `listB` to reach intersection)
*   `intersectVal` is `0` if `listA` and `listB` do not intersect.
*   `intersectVal == listA[skipA] == listB[skipB]` if `listA` and `listB` intersect.

## 🤔 Understanding the Problem
The problem asks us to find the *first common node* (by reference, not just value) between two singly linked lists. This means that from the point of intersection onwards, both lists share the exact same sequence of nodes. The challenge arises because the lists can have different lengths before they potentially merge. We need an efficient way to align their traversal such that we can detect this common node. The "no cycles" constraint simplifies things, as we don't have to worry about infinite loops within a single list.

## 💡 Core Idea
The core idea is to use two pointers, one for each list, and make them traverse the *same total distance*. If they ever point to the same node, that's the intersection. If they reach the end of their current list, they "switch" to the head of the *other* list.

## 🧠 Approach — Two Pointers
This problem is perfectly suited for the **Two Pointers** pattern. We use two pointers, `a` and `b`, initialized to `headA` and `headB` respectively. The key insight is that if both pointers traverse `Length(ListA) + Length(ListB)` nodes, they will either meet at the intersection point or both end up at `NULL` simultaneously if there's no intersection. By switching a pointer to the other list's head once it reaches the end of its own list, we effectively equalize the total path length traversed by both pointers before their potential meeting point.

## 📝 Step-by-Step Algorithm
1.  Initialize two pointers, `a` and `b`, to `headA` and `headB` respectively.
2.  Enter a loop that continues as long as `a` and `b` are not pointing to the same node.
3.  Inside the loop:
    *   Advance pointer `a` to its next node (`a = a->next`).
    *   If `a` becomes `NULL` (meaning it reached the end of `listA`), re-route it to `headB` (`a = headB`). This ensures `a` continues traversing.
    *   Similarly, advance pointer `b` to its next node (`b = b->next`).
    *   If `b` becomes `NULL` (meaning it reached the end of `listB`), re-route it to `headA` (`b = headA`). This ensures `b` continues traversing.
4.  The loop terminates when `a` and `b` point to the same node. This node is either the intersection point or `NULL` (if no intersection exists, both pointers will eventually become `NULL` simultaneously after traversing `Length(ListA) + Length(ListB)` nodes).
5.  Return the node pointed to by `b` (or `a`, since they are now the same).

## 💻 Solution

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        // Initialize two pointers, one for each list.
        // If an intersection exists, these pointers will eventually meet.
        ListNode* a = headA;
        ListNode* b = headB;

        // Loop until the two pointers meet.
        // They will meet either at the intersection node or at NULL if no intersection.
        while (a != b) {
            // Move pointer 'a' to the next node.
            // If 'a' reaches the end of listA (becomes NULL),
            // re-route it to the head of listB.
            // This effectively makes 'a' traverse listA then listB.
            a = (a == NULL) ? headB : a->next;
            
            // Move pointer 'b' to the next node.
            // If 'b' reaches the end of listB (becomes NULL),
            // re-route it to the head of listA.
            // This effectively makes 'b' traverse listB then listA.
            b = (b == NULL) ? headA : b->next;
        }

        // When the loop terminates, 'a' and 'b' are pointing to the same node.
        // This node is either the intersection point or NULL (if no intersection).
        // Return either 'a' or 'b' (they are identical at this point).
        return b;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(m + n) | In the worst case, each pointer traverses listA once and listB once. The total number of steps is proportional to the sum of the lengths of the two lists. |
| **Space** | O(1) | Only a constant number of extra pointers (two) are used, regardless of the input list sizes. |

## 🔗 Related Problems
- 141. Linked List Cycle
- 142. Linked List Cycle II
- 21. Merge Two Sorted Lists