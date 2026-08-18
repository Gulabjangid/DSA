# 0160-intersection-of-two-linked-lists

## 📋 Problem Description
Given the heads of two singly linked lists, `headA` and `headB`, the goal is to find and return the node at which the two lists first intersect. If the two linked lists do not share any common node, the function should return `null`.

An intersection implies that from a certain node onwards, both lists point to the exact same sequence of nodes, meaning they share the same memory references. The problem guarantees that there are no cycles anywhere in the entire linked structure. Additionally, the original structure of both linked lists must remain unchanged after the function completes its execution.

The function receives two `ListNode*` pointers, `headA` and `headB`, representing the heads of the two lists, and must return a `ListNode*` pointer to the intersecting node, or `NULL` if no intersection exists.

## 🔍 Examples
```
Input:  intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
Output: Intersected at '8'
Explanation:
List A: 4 -> 1 -> (8 -> 4 -> 5)
List B: 5 -> 6 -> 1 -> (8 -> 4 -> 5)
The node with value 8 is the first common node reference. From this node onwards, both lists share the same tail.
```

```
Input:  intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
Output: Intersected at '2'
Explanation:
List A: 1 -> 9 -> 1 -> (2 -> 4)
List B: 3 -> (2 -> 4)
The node with value 2 is the first common node reference.
```

```
Input:  intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
Output: No intersection
Explanation:
List A: 2 -> 6 -> 4
List B: 1 -> 5
The two lists do not share any common nodes.
```

## 📌 Constraints
*   The number of nodes in `listA` (`m`) is between 1 and 3 * 10^4.
*   The number of nodes in `listB` (`n`) is between 1 and 3 * 10^4.
*   Node values (`Node.val`) are between 1 and 10^5.
*   `skipA` (number of nodes to skip in `listA` before intersection) is between 0 and `m`.
*   `skipB` (number of nodes to skip in `listB` before intersection) is between 0 and `n`.
*   `intersectVal` is 0 if `listA` and `listB` do not intersect.
*   If `listA` and `listB` intersect, `intersectVal` will be equal to `listA[skipA]` and `listB[skipB]`.

## 🤔 Understanding the Problem
The problem asks us to find the *first common node reference* between two singly linked lists. This is crucial: we're not looking for nodes with the same *value*, but rather the exact same node object in memory. The lists can have different lengths before they potentially merge. If they don't merge, we should return `null`. The challenge lies in efficiently finding this common point without knowing the lengths of the lists beforehand and without using extra space proportional to the list sizes.

## 💡 Core Idea
The core idea is to use two pointers, one starting at the head of each list. When a pointer reaches the end of its current list, it is redirected to the head of the *other* list. This clever trick ensures that both pointers will travel the exact same total distance before they either meet at the intersection point or both become `NULL` simultaneously (if there's no intersection).

## 🧠 Approach — Two Pointers
This problem is perfectly suited for the **Two Pointers** pattern. This pattern is highly effective for linked list problems, especially when dealing with unknown lengths or needing to find a meeting point or common element.

The reason this pattern fits here is that by having two pointers, `ptrA` and `ptrB`, traverse `listA` and `listB` respectively, and then "swapping" their starting points (redirecting `ptrA` to `headB` when it finishes `listA`, and `ptrB` to `headA` when it finishes `listB`), we effectively eliminate the problem of differing list lengths. Both pointers will eventually traverse `lengthA + lengthB` nodes. If an intersection exists, they will meet at the intersection point. If no intersection exists, they will both reach `NULL` simultaneously after traversing the combined length and meet there.

## 📝 Step-by-Step Algorithm
1.  **Initialize Pointers**: Create two pointers, `ptrA` and `ptrB`. Initialize `ptrA` to `headA` and `ptrB` to `headB`.
2.  **Traverse and Redirect**: Start a loop that continues as long as `ptrA` is not equal to `ptrB`.
    *   Inside the loop, for `ptrA`:
        *   If `ptrA` is currently `NULL` (meaning it has reached the end of `listA`), redirect it to `headB`.
        *   Otherwise, advance `ptrA` to its next node (`ptrA = ptrA->next`).
    *   Similarly, for `ptrB`:
        *   If `ptrB` is currently `NULL` (meaning it has reached the end of `listB`), redirect it to `headA`.
        *   Otherwise, advance `ptrB` to its next node (`ptrB = ptrB->next`).
3.  **Meeting Point**: The loop will terminate when `ptrA` and `ptrB` become equal. At this point, they will be pointing to:
    *   The first common node (the intersection point), if an intersection exists.
    *   `NULL`, if no intersection exists (both pointers will have traversed both lists and ended up at `NULL` simultaneously).
4.  **Return Result**: Return either `ptrA` or `ptrB` (since they are equal at this point). This will be the intersection node or `NULL`.

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
        // Initialize two pointers, 'a' starting at headA and 'b' starting at headB.
        // These pointers will traverse their respective lists.
        ListNode* a = headA;
        ListNode* b = headB;

        // The core idea is to make both pointers travel the same total distance.
        // If they intersect, they will meet at the intersection node.
        // If they don't intersect, they will both become NULL simultaneously after
        // traversing the combined length of both lists, and meet at NULL.
        //
        // Let L_A be the length of list A, L_B be the length of list B.
        // Let C be the length of the common part (intersection).
        // The unique part of A is L_A - C.
        // The unique part of B is L_B - C.
        //
        // When pointer 'a' finishes list A (traverses L_A nodes), it moves to headB.
        // When pointer 'b' finishes list B (traverses L_B nodes), it moves to headA.
        //
        // Path for 'a': (L_A - C) + C (first pass on A) + (L_B - C) (second pass on B's unique part)
        // Path for 'b': (L_B - C) + C (first pass on B) + (L_A - C) (second pass on A's unique part)
        //
        // Both pointers will travel a total distance of (L_A - C) + C + (L_B - C)
        // before they meet at the intersection node.
        // If there's no intersection (C=0), they will both become NULL after traversing
        // L_A + L_B distance and meet at NULL.
        while (a != b) {
            // If pointer 'a' reaches the end of list A (becomes NULL),
            // redirect it to the head of list B.
            // Otherwise, move it to the next node in list A.
            a = (a == NULL) ? headB : a->next;

            // If pointer 'b' reaches the end of list B (becomes NULL),
            // redirect it to the head of list A.
            // Otherwise, move it to the next node in list B.
            b = (b == NULL) ? headA : b->next;
        }

        // When the loop terminates, 'a' and 'b' are pointing to the same node.
        // This node is either the intersection point or NULL (if no intersection).
        return b; // We can return either 'a' or 'b' as they are guaranteed to be equal.
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(m + n) | In the worst case, each pointer traverses its own list once and then the other list once before they meet. The total number of steps is proportional to the sum of the lengths of the two lists (`m + n`). |
| **Space** | O(1) | Only a constant number of extra pointers (`a`, `b`) are used, regardless of the size of the input linked lists. |

## 🔗 Related Problems
*   141. Linked List Cycle
*   142. Linked List Cycle II
*   876. Middle of the Linked List