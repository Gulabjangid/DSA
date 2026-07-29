# 0237-delete-node-in-a-linked-list

## 📋 Problem Description
You are given a node `node` from a singly-linked list. Your task is to delete this given `node` from the list.

Crucially, you will **not** be given access to the `head` of the linked list. This means you cannot traverse the list from the beginning to find the node's predecessor.

You are guaranteed that:
*   The values in the linked list are unique.
*   The given `node` to be deleted is **not** the last node (tail) of the linked list.

"Deleting" the node means:
1.  The value of the given `node` should no longer exist in the list.
2.  The total number of nodes in the list should decrease by one.
3.  The relative order of nodes before the deleted node must remain the same.
4.  The relative order of nodes after the deleted node must remain the same.

The function `deleteNode` receives a pointer to the `ListNode` to be deleted and does not return anything (it modifies the list in-place).

## 🔍 Examples
```
Input:  head = [4,5,1,9], node = 5 (the node with value 5)
Output: [4,1,9]
Explanation: The node with value 5 is deleted. The list becomes 4 -> 1 -> 9.
```

```
Input:  head = [4,5,1,9], node = 1 (the node with value 1)
Output: [4,5,9]
Explanation: The node with value 1 is deleted. The list becomes 4 -> 5 -> 9.
```

## 📌 Constraints
*   The number of nodes in the given list is in the range `[2, 1000]`.
*   `-1000 <= Node.val <= 1000`
*   The value of each node in the list is **unique**.
*   The `node` to be deleted is **in the list** and is **not a tail** node.

## 🤔 Understanding the Problem
This problem presents a classic linked list manipulation challenge with a twist: we're given direct access to the node to be deleted, but *not* to the head of the list. In a singly linked list, deleting a node usually requires knowing its *predecessor* so that the predecessor's `next` pointer can be updated to skip the node being deleted. Since we don't have access to the head, we cannot find the predecessor by traversing from the beginning. The problem's constraints (unique values, not a tail node) are crucial hints.

## 💡 Core Idea
Since we cannot modify the `next` pointer of the *previous* node, the only way to "delete" the given `node` is to effectively overwrite its data with the data of its *successor*, and then delete the successor node instead. This makes the current node "disappear" conceptually by taking on the identity of its successor.

## 🧠 Approach — Linked List Manipulation
This problem is a specific case of **Linked List Manipulation**. The pattern fits because we are directly modifying the structure of a linked list by changing `val` and `next` pointers. We use this approach because the problem constraints explicitly prevent the standard way of deleting a node (which involves finding its predecessor). By overwriting the current node with its successor's data and then deleting the successor, we achieve the effect of deleting the current node without needing its predecessor. The guarantee that the node is *not* the tail is essential, as it ensures `node->next` always exists.

## 📝 Step-by-Step Algorithm
1.  **Copy Value**: Take the value from the node immediately following the given `node` (i.e., `node->next->val`) and copy it into the `val` field of the `node` to be deleted. This effectively makes the current `node` "become" its successor in terms of value.
2.  **Store Successor**: Create a temporary pointer, `temp`, and make it point to the node immediately following the given `node` (i.e., `node->next`). This is the node we will actually remove from memory.
3.  **Bypass Successor**: Update the `next` pointer of the given `node` to point to the node *after* its successor (i.e., `node->next->next`). This effectively removes the successor node from the linked list's chain.
4.  **Delete Successor**: Free the memory occupied by the `temp` node (which was the original successor). This completes the deletion, ensuring the number of nodes decreases by one and memory is managed.

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
        // Step 1: Copy the value of the next node into this node.
        // Since we cannot access the previous node to change its 'next' pointer,
        // we effectively "overwrite" the current node with the data of its successor.
        // This makes the current node conceptually disappear by taking on the identity
        // of the node after it.
        node->val = node->next->val;
        
        // Step 2: Keep a temporary pointer to the next node.
        // This is the node that originally held the value we just copied.
        // We need to store a pointer to it so we can delete it from memory later.
        ListNode* temp = node->next;
        
        // Step 3: Link the current node to skip over the next node.
        // The current node's 'next' pointer is now updated to point to the node
        // that was originally *after* 'node->next'. This effectively removes
        // 'node->next' from the linked list chain.
        node->next = node->next->next;
        
        // Step 4: Free the memory of the duplicated node (the original 'node->next').
        // This step is crucial for memory management, ensuring that the node
        // is truly "deleted" and memory is reclaimed.
        delete temp;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(1) | The solution involves a fixed number of pointer manipulations and value assignments, regardless of the list's size. |
| **Space** | O(1) | Only a single temporary pointer (`temp`) is used, requiring constant extra space. |

## 🔗 Related Problems
- 19. Remove Nth Node From End of List
- 203. Remove Linked List Elements
- 83. Remove Duplicates from Sorted List