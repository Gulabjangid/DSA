# 0237-delete-node-in-a-linked-list

## 📋 Problem Description
The problem asks us to delete a specific `node` from a singly-linked list. We are given a pointer directly to the `node` that needs to be deleted. Crucially, we are **not given access to the `head`** of the linked list.

All values in the linked list are guaranteed to be unique. It is also guaranteed that the given `node` to be deleted is **not the last node** in the linked list.

The definition of "deleting" the node means:
*   The value of the given node should no longer exist in the linked list.
*   The total number of nodes in the linked list should decrease by one.
*   The relative order of all nodes before the deleted node must remain the same.
*   The relative order of all nodes after the deleted node must remain the same.

The function `deleteNode` receives a `ListNode* node` (a pointer to the node to be deleted) and modifies the linked list in place. It does not return any value.

## 🔍 Examples
```
Input: head = [4,5,1,9], node = 5
Output: [4,1,9]
Explanation: You are given the second node with value 5. After calling the function, the linked list becomes 4 -> 1 -> 9.
```

```
Input: head = [4,5,1,9], node = 1
Output: [4,5,9]
Explanation: You are given the third node with value 1. After calling the function, the linked list becomes 4 -> 5 -> 9.
```

## 📌 Constraints
*   The number of nodes in the given list is in the range `[2, 1000]`.
*   `-1000 <= Node.val <= 1000`.
*   The value of each node in the list is **unique**.
*   The `node` to be deleted is **in the list** and is **not a tail node**.

## 🤔 Understanding the Problem
This problem presents a unique challenge in linked list manipulation. In a typical singly-linked list deletion scenario, to remove a node, you need a pointer to its *predecessor* so you can update the predecessor's `next` pointer to bypass the node being deleted. However, here we are only given a pointer to the `node` itself, and crucially, **not the `head` of the list**. This means we cannot traverse from the beginning to find the node *before* the one we want to delete. The problem becomes non-trivial because we cannot directly modify the `next` pointer of the node that points to our target node.

## 💡 Core Idea
Since we cannot modify the `next` pointer of the *previous* node (because we don't have access to it), the only way to effectively "delete" the given `node` is to overwrite its content with the content of its *successor*, and then delete the successor node. This makes the given `node` conceptually disappear by replacing its data with the next node's data, and then physically removing the next node.

## 🧠 Approach — Linked List In-Place Deletion Trick
This problem requires a specific trick for linked list manipulation due to the constraint that we are only given the node to be deleted and *not* the head of the list. This prevents us from traversing the list to find the node *preceding* the target node, which is the standard way to delete a node by updating the `next` pointer of its predecessor. The trick involves effectively "shifting" the values from the next node backwards into the current node, and then deleting the next node, thereby achieving the desired deletion without needing the head. This is an in-place modification technique.

## 📝 Step-by-Step Algorithm
1.  **Copy Value**: Take the value (`val`) from the node *immediately following* the given `node` (i.e., `node->next`) and copy this value into the `val` field of the given `node`. At this point, the given `node` effectively holds the value that was originally in `node->next`.
2.  **Store Next Node**: Create a temporary pointer (e.g., `temp`) and make it point to `node->next`. This `temp` pointer now points to the node that we conceptually "moved" into the current `node` and which we will physically remove from the list.
3.  **Bypass Next Node**: Update the `next` pointer of the given `node` (which now contains the copied value) to point to the node *after* the one `temp` is pointing to (i.e., `node->next->next`). This effectively removes the original `node->next` from the linked list's chain, as `node` now directly links to the node after `temp`.
4.  **Delete Memory**: Free the memory occupied by the node pointed to by the temporary pointer (`temp`). This ensures that the number of nodes in the list decreases by one and prevents memory leaks.

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
    void deleteNode(ListNode* node) {
        // The core idea is to overwrite the current node's value with the next node's value,
        // and then delete the next node. This effectively "deletes" the current node
        // without needing access to its predecessor (which we don't have).
        // This approach is valid because the problem guarantees 'node' is not the tail.
        
        // Step 1: Copy the value of the next node into the current node.
        // For example, if list is 4->5->1->9 and 'node' is 5,
        // 'node->next' is 1. We copy 1 into 'node->val'.
        // Conceptually, the list becomes 4->1(old 5)->1(old 1)->9.
        node->val = node->next->val;
        
        // Step 2: Keep a temporary pointer to the next node.
        // This is the node that we conceptually "moved" its value from,
        // and it's the node we will physically remove from the list and memory.
        // In our example, 'temp' now points to the node that originally held value 1.
        ListNode* temp = node->next;
        
        // Step 3: Link the current node to skip over the 'temp' node.
        // The 'next' pointer of the current 'node' (which now holds the copied value)
        // should point to the node *after* 'temp'.
        // In our example, 'node' (which now has value 1) will point to '9'.
        // The list effectively becomes 4->1->9. The node 'temp' (original 1) is bypassed.
        node->next = node->next->next; // This is equivalent to node->next = temp->next;
        
        // Step 4: Free the memory of the duplicated node (the one 'temp' points to).
        // This ensures that the number of nodes in the list decreases by one and prevents memory leaks.
        // The node that originally held value 1 is now deallocated.
        delete temp;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(1) | The solution performs a constant number of operations: a value copy, two pointer assignments, and one memory deallocation. These operations do not depend on the size of the linked list. |
| **Space** | O(1) | The solution uses a single temporary pointer variable (`temp`), which consumes a constant amount of memory regardless of the linked list's size. |

## 🔗 Related Problems
- 19. Remove Nth Node From End of List
- 203. Remove Linked List Elements
- 83. Remove Duplicates from Sorted List