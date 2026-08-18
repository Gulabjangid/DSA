# 0160-intersection-of-two-linked-lists

## 📋 Problem Description
Given the heads of two singly linked lists, `headA` and `headB`, the task is to find and return the node at which the two lists first intersect. If the two linked lists do not intersect at any point, the function should return `null`.

The problem guarantees that there are no cycles anywhere in the entire linked structure. It's important to note that the linked lists must retain their original structure after the function returns. The intersection is defined by *node reference* equality, meaning two nodes intersect if they are the exact same node object in memory, not just if they have the same value.

## 🔍 Examples
```
Input:  intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
Output: Intersected at '8'
Explanation: List A is 4 -> 1 -> 8 -> 4 -> 5. List B is 5 -> 6 -> 1 -> 8 -> 4 -> 5.
The node with value 8 is the first common node reference for both lists.
```

```
Input:  intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
Output: Intersected at '2'
Explanation: List A is 1 -> 9 -> 1 -> 2 -> 4. List B is 3 -> 2 -> 4.
The node with value 2 is the first common node reference.
```

```
Input:  intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
Output: No intersection
Explanation: List A is 2 -> 6 -> 4. List B is 1 -> 5. The two lists do not share any common node.
```

## 📌 Constraints
*   The number of nodes in `listA` (`m`) is between 1 and 3 * 10^4.
*   The number of nodes in `listB` (`n`) is between 1 and 3 * 10^4.
*   Node values (`Node.val`) are between 1 and 10^5.
*   `skipA` (nodes to skip in `listA` before intersection) is between 0 and `m`.
*   `skipB` (nodes to skip in `listB` before intersection) is between 0 and `n`.
*   `intersectVal` is 0 if `listA` and `listB` do not intersect.
*   If `listA` and `listB` intersect, `intersectVal` will be equal to `listA[skipA]` and `listB[skipB]`.

## 🤔 Understanding the Problem
The problem asks us to find the *exact same node object* where two linked lists merge. It's crucial to distinguish this from simply finding nodes with the same *value*. The lists might have different lengths before they merge, or they might not merge at all. The primary challenge is to efficiently locate this common node without knowing the lengths of the lists beforehand and ideally without using extra memory.

## 💡 Core Idea
The core idea is to use two pointers, one starting at the head of each list. When a pointer reaches the end of its current list, it is redirected to the head of the *other* list. This clever trick ensures that both pointers will eventually traverse the same total number of nodes, making it possible for them to meet at the intersection point (or at `NULL` if no intersection exists).

## 🧠 Approach — Two Pointers
This problem can be elegantly solved using the **Two Pointers** pattern. This pattern is particularly effective for linked list problems where you need to find a common point, detect cycles, or compare elements between two lists, especially when their lengths are unknown or different.

The reason this pattern fits here is that by having two pointers, `ptrA` and `ptrB`, traverse `listA` and `listB` respectively, and then "swapping" them to the other list's head once they reach the end of their current list, we effectively normalize the path lengths. If `listA` has length `L_A` and `listB` has length `L_B`, and they intersect `k` nodes from their tails, then `ptrA` will traverse `L_A` nodes, then `L_B` nodes. `ptrB` will traverse `L_B` nodes, then `L_A` nodes. Both pointers will have traversed `L_A + L_B` nodes in total. If an intersection exists, they will meet at the intersection node. If no intersection exists, they will both eventually become `NULL` simultaneously after traversing `L_A + L_B` nodes and meet at `NULL`.

## 📝 Step-by-Step Algorithm
1.  **Initialize Pointers**: Create two pointers, `ptrA` and `ptrB`. Initialize `ptrA` to `headA` and `ptrB` to `headB`.
2.  **Traverse and Re-route**: Enter a loop that continues as long as `ptrA` is not equal to `ptrB`.
    *   **Advance `ptrA`**: Move `ptrA` to its next node (`ptrA = ptrA->next`).
    *   **Handle End of List A**: If `ptrA` becomes `NULL` (meaning it has reached the end of `listA`), re-route it to `headB` (`ptrA = headB`).
    *   **Advance `ptrB`**: Move `ptrB` to its next node (`ptrB = ptrB->next`).
    *   **Handle End of List B**: If `ptrB` becomes `NULL` (meaning it has reached the end of `listB`), re-route it to `headA` (`ptrB = headA`).
3.  **Intersection or No Intersection**: The loop will terminate when `ptrA` and `ptrB` point to the same node.
    *   If the lists intersect, they will meet at the first common node.
    *   If the lists do not intersect, both pointers will eventually traverse both lists completely, become `NULL` at the same time, and meet at `NULL`.
4.  **Return Result**: Return `ptrA` (or `ptrB`, since they are guaranteed to be the same at this point).

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
        // These pointers will traverse the lists.
        ListNode* a = headA;
        ListNode* b = headB;

        // The loop continues as long as the two pointers are not pointing to the same node.
        // They will meet at the intersection point, or at NULL if no intersection exists.
        while (a != b) {
            // Move pointer 'a' to the next node.
            // If 'a' reaches the end of list A (becomes NULL),
            // re-route it to the head of list B.
            // This effectively makes 'a' traverse list A, then list B.
            a = (a == NULL) ? headB : a->next;

            // Move pointer 'b' to the next node.
            // If 'b' reaches the end of list B (becomes NULL),
            // re-route it to the head of list A.
            // This effectively makes 'b' traverse list B, then list A.
            b = (b == NULL) ? headA : b->next;
        }

        // When the loop terminates, 'a' and 'b' are pointing to the same node.
        // This node is the intersection point.
        // If there was no intersection, both 'a' and 'b' would have become NULL
        // at the same time after traversing both lists, and then they would meet at NULL.
        // In either case (intersection or no intersection), 'b' (or 'a') holds the correct result.
        return b; 
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(m + n) | In the worst case, each pointer traverses list A and then list B (or vice versa) once. The total path length for each pointer is `Length(A) + Length(B)`. |
| **Space** | O(1) | Only a constant number of pointers (`a`, `b`, `headA`, `headB`) are used, regardless of the sizes of the input lists. |

## 🔗 Related Problems
- 141. Linked List Cycle
- 142. Linked List Cycle II
- 876. Middle of the Linked List