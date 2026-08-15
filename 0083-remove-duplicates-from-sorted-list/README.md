# 0083-remove-duplicates-from-sorted-list

## 📋 Problem Description
Given the `head` of a sorted singly-linked list, the task is to remove all duplicate nodes such that each unique element appears only once. The resulting list must also be sorted. The function should return the head of the modified linked list.

## 🔍 Examples
```
Input: head = [1,1,2]
Output: [1,2]
Explanation: The second '1' is a duplicate of the first '1'. After removal, only unique elements remain.
```

```
Input: head = [1,1,2,3,3]
Output: [1,2,3]
Explanation: The second '1' is a duplicate, and the second '3' is a duplicate. Both are removed.
```

```
Input: head = []
Output: []
Explanation: An empty list has no duplicates and remains empty.
```

## 📌 Constraints
*   The number of nodes in the list is in the range `[0, 300]`.
*   `-100 <= Node.val <= 100`
*   The list is guaranteed to be **sorted** in ascending order.

## 🤔 Understanding the Problem
The problem requires us to modify a given sorted linked list in-place to ensure that every value appears only once. Since the list is sorted, all duplicate values will always be adjacent to each other. The main challenge is to correctly manipulate the `next` pointers of the `ListNode` objects to effectively "delete" duplicate nodes without breaking the list's structure or losing subsequent unique elements. We also need to handle edge cases like an empty list or a list with a single node.

## 💡 Core Idea
The crucial observation is that because the linked list is sorted, any duplicate values will always be found immediately next to each other. This allows us to traverse the list with a single pointer and compare each node's value with its immediate successor.

## 🧠 Approach — Iterative Traversal
This problem can be efficiently solved using an iterative traversal approach with a single pointer. We iterate through the linked list, maintaining a `current` pointer. Because the list is sorted, if `current->val` is equal to `current->next->val`, we know `current->next` is a duplicate. In such a case, we can simply bypass the duplicate node by setting `current->next` to `current->next->next`, effectively removing the duplicate from the list. If the values are different, it means `current->next` is a unique element, so we advance `current` to `current->next` to continue the process. This method modifies the list in-place, requiring no additional data structures.

## 📝 Step-by-Step Algorithm
1.  **Handle Edge Cases**: First, check if the input `head` is `NULL` (an empty list). If it is, return `NULL` immediately, as there's nothing to process or remove.
2.  **Initialize Pointer**: Create a pointer, let's call it `temp`, and initialize it to `head`. This pointer will be used to traverse the list and make necessary modifications.
3.  **Traverse the List**: Begin a loop that continues as long as `temp` is not `NULL` and `temp->next` is not `NULL`. This condition ensures that we always have at least two nodes to compare (`temp` and `temp->next`).
4.  **Check for Duplicates**: Inside the loop, compare the value of the `temp` node (`temp->val`) with the value of its immediate successor node (`temp->next->val`).
    *   **If `temp->val == temp->next->val`**: A duplicate is found. The node `temp->next` is a duplicate of `temp`. To remove `temp->next`, update `temp->next` to point to `temp->next->next`. This effectively skips over the duplicate node, removing it from the list. It's important *not* to advance `temp` in this case, because the *new* `temp->next` (which was `temp->next->next`) might also be a duplicate of the current `temp->val`. We need to re-check `temp` against its new successor.
    *   **If `temp->val != temp->next->val`**: No duplicate is found between `temp` and `temp->next`. This means `temp->next` is a unique element. In this situation, we can safely advance `temp` to `temp->next` to move to the next distinct element in the list and continue the comparison process.
5.  **Return Head**: After the loop finishes (which happens when `temp` reaches the end of the list or `temp->next` becomes `NULL`), all duplicates will have been removed. Return the original `head` of the list, which now points to the beginning of the de-duplicated list.

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
        // Initialize a pointer 'temp' to the head of the list.
        // This pointer will be used to traverse the list and make modifications.
        ListNode* temp = head;

        // Handle the edge case where the list is empty.
        // If head is NULL, there are no nodes, so no duplicates to remove.
        // Return NULL directly.
        if (head == NULL) {
            return NULL;
        }

        // Iterate through the list as long as 'temp' is not NULL
        // and 'temp' has a next node. We need 'temp->next' to exist
        // to be able to compare 'temp->val' with 'temp->next->val'
        // and potentially modify 'temp->next'.
        while (temp != NULL && temp->next != NULL) {
            // Check if the current node's value is equal to the next node's value.
            if (temp->next->val == temp->val) {
                // If they are equal, it means 'temp->next' is a duplicate.
                // To remove the duplicate, we bypass 'temp->next' by making
                // 'temp->next' point to 'temp->next->next'.
                // This effectively "deletes" the duplicate node from the list.
                //
                // We do NOT advance 'temp' here, because the new 'temp->next'
                // (which was 'temp->next->next') might also be a duplicate
                // of the current 'temp->val'. For example, if we have [1,1,1,2],
                // when temp is at the first '1', temp->next is the second '1'.
                // We set temp->next to the third '1'. Now, temp is still at the first '1',
                // and temp->next is the third '1'. We need to re-check this new pair.
                temp->next = temp->next->next;
            } else {
                // If the values are different, it means 'temp->next' is a unique element.
                // So, we can safely advance 'temp' to the next node to continue checking.
                temp = temp->next;
            }
        }

        // After the loop finishes, all duplicates have been removed.
        // Return the original head of the list, which now points to the
        // de-duplicated list.
        return head;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The algorithm iterates through the linked list once. In the worst case, each node is visited and compared a constant number of times. |
| **Space** | O(1) | The algorithm uses a constant amount of extra space for a single pointer (`temp`), regardless of the input list's size. |

## 🔗 Related Problems
- 21. Merge Two Sorted Lists
- 19. Remove Nth Node From End of List
- 203. Remove Linked List Elements