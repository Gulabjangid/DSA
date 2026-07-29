# 0237-delete-node-in-a-linked-list

## 📋 Problem Description
You are given a singly-linked list and a specific `node` within that list. Your task is to delete this `node`.

A crucial constraint is that you will **not be given access to the `head`** of the linked list. You are only provided with a pointer to the `node` that needs to be deleted.

Additionally, it's guaranteed that:
*   All values in the linked list are unique.
*   The given `node` to be deleted is **not the last node** in the linked list.

"Deleting" the node means:
1.  The value of the given `node` should no longer exist in the linked list.
2.  The total number of nodes in the linked list should decrease by one.
3.  The relative order of all nodes before the deleted `node` must remain the same.
4.  The relative order of all nodes after the deleted `node` must remain the same.

Your function `deleteNode` receives a pointer to the `ListNode` that needs to be deleted and modifies the linked list in place. It does not return any value.

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
*   `-1000 <= Node.val <= 1000`
*   The value of each node in the list is **unique**.
*   The `node` to be deleted is **in the list** and is **not a tail** node.

## 🤔 Understanding the Problem
The core challenge of this problem lies in the constraint that we are **not given access to the `head`** of the linked list. In a typical linked list deletion scenario, to remove a node `X`, we would need to find the node *before* `X` (let's call it `P`), and then update `P->next = X->next`. However, without the `head` pointer, we cannot traverse the list to find `P`. We only have a pointer to `X` itself. This means we cannot directly modify the `next` pointer of `X`'s predecessor. We need an alternative strategy to achieve the deletion effect.

## 💡 Core Idea
Since we cannot access the node *before* the target `node` to update its `next` pointer, the only way to "delete" the given `node` is to effectively replace its content with the content of its *successor*, and then delete the successor node instead. This makes the given `node` logically disappear from the list.

## 🧠 Approach — Direct Node Overwriting
This problem is solved using a technique of "Direct Node Overwriting" or "Value Swapping and Pointer Re-linking". This pattern is specific to linked list problems where you are given a pointer to the node to be deleted but *not* its predecessor or the head of the list. It fits this problem perfectly because the constraints (no head access, and the guarantee that the node is *not* a tail node) force us to manipulate the given node and its successor. By copying the successor's data into the current node and then bypassing/deleting the successor, we effectively remove the current node's logical presence without needing its predecessor.

## 📝 Step-by-Step Algorithm
1.  **Access Successor's Value**: Get the value from the `node`'s immediate successor (`node->next`).
2.  **Overwrite Current Node**: Copy this value into the `node` itself (`node->val = node->next->val`). This effectively "replaces" the `node`'s original value with the value of the node it's supposed to replace.
3.  **Store Successor Pointer**: Create a temporary pointer (`temp`) and assign it the address of the `node`'s immediate successor (`node->next`). This `temp` pointer now points to the node that we will logically "delete" from the list and free from memory.
4.  **Bypass Successor**: Update the `node`'s `next` pointer to point to the successor of its original successor (`node->next = node->next->next`). This step effectively removes the original successor from the linked list sequence, as the current `node` now points directly to what was previously the *next-next* node.
5.  **Deallocate Memory**: Deallocate the memory occupied by the node pointed to by `temp` (the original successor) to prevent memory leaks.

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
        // Step 1: Copy the value of the next node into the current node.
        // Since we cannot access the previous node to update its 'next' pointer,
        // we effectively "overwrite" the current node's data with its successor's data.
        // This makes the current node logically take on the identity of its successor.
        node->val = node->next->val;
        
        // Step 2: Keep a temporary pointer to the next node.
        // This 'temp' pointer now points to the node that originally held the value
        // we just copied. This is the node we want to physically remove from memory.
        ListNode* temp = node->next;
        
        // Step 3: Link the current node to skip over the 'temp' node.
        // The current node's 'next' pointer is updated to point to what was
        // originally the 'next-next' node. This effectively removes 'temp'
        // from the linked list sequence.
        node->next = node->next->next;
        
        // Step 4: Free the memory of the duplicated node (the original successor).
        // It's important to deallocate memory to prevent memory leaks.
        // 'temp' points to the node that is no longer part of the list's logical structure.
        delete temp;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(1) | The solution involves a constant number of operations: one value assignment, two pointer assignments, and one memory deallocation. These operations do not depend on the size of the linked list. |
| **Space** | O(1) | We only use a single temporary pointer (`temp`) to store the address of the node to be deallocated. No additional data structures are created that scale with the input size. |

## 🔗 Related Problems
- 19. Remove Nth Node From End of List
- 203. Remove Linked List Elements
- 21. Merge Two Sorted Lists