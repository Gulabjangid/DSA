# 0002-add-two-numbers

## 📋 Problem Description
You are given two non-empty linked lists, `l1` and `l2`, where each represents a non-negative integer. The digits are stored in reverse order, meaning the least significant digit is at the head of the list. Each node in the linked list contains a single digit. Your task is to add these two numbers and return their sum as a new linked list, also with digits stored in reverse order.

You can assume that the input numbers do not contain any leading zeros, except for the number 0 itself.

**Input:**
*   `l1`: A pointer to the head of the first linked list.
*   `l2`: A pointer to the head of the second linked list.

**Output:**
*   A pointer to the head of a new linked list representing the sum of the two input numbers.

## 🔍 Examples
```
Input:  l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: The number represented by l1 is 342. The number represented by l2 is 465. Their sum is 342 + 465 = 807. The output linked list [7,0,8] represents 807 in reverse order.
```

```
Input:  l1 = [0], l2 = [0]
Output: [0]
Explanation: 0 + 0 = 0.
```

```
Input:  l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]
Explanation: The number represented by l1 is 9,999,999. The number represented by l2 is 9,999. Their sum is 9,999,999 + 9,999 = 10,009,998. The output linked list [8,9,9,9,0,0,0,1] represents 10,009,998 in reverse order.
```

## 📌 Constraints
*   The number of nodes in each linked list (`l1` and `l2`) is in the range `[1, 100]`.
*   Each node's value (`Node.val`) is between `0` and `9` inclusive.
*   It is guaranteed that the lists represent numbers that do not have leading zeros, except for the number 0 itself.

## 🤔 Understanding the Problem
This problem asks us to simulate the process of adding two numbers manually, just like we learned in elementary school. The key twist is that the numbers are represented as linked lists, and their digits are stored in reverse order. This reverse order is actually quite convenient, as it means the least significant digits (ones place) are at the head of the lists, allowing us to start addition from right to left (which is left to right in the linked list traversal). We need to handle carries generated during addition and ensure the resulting sum is also represented as a linked list in reverse order. Edge cases include lists of different lengths and sums that result in an extra carry digit at the very end.

## 💡 Core Idea
The core idea is to perform digit-by-digit addition, starting from the least significant digits (the heads of the linked lists), and propagate any carry to the next higher place value. This process continues until all digits from both numbers have been processed and any final carry has been accounted for.

## 🧠 Approach — Linked List Traversal / Simulation
This problem is best solved using a **Linked List Traversal** and **Simulation** approach.
This pattern fits because we are given two linked lists and need to construct a new linked list based on their values. We iterate through both input lists simultaneously, node by node, simulating the arithmetic operation of addition. Since the digits are in reverse order, we can directly add corresponding nodes' values and handle carries, moving from the head (least significant digit) towards the tail (most significant digit). This direct simulation naturally builds the result linked list in the correct reverse order.

## 📝 Step-by-Step Algorithm

1.  **Initialize:**
    *   Create a `dummy` head node for the result linked list. This helps simplify the logic for adding the first node, as we won't need special handling for an empty list.
    *   Initialize a `tail` pointer to point to the `dummy` node. This `tail` pointer will always point to the last node added to our result list, allowing us to easily append new nodes.
    *   Initialize an integer `carry` to `0`. This variable will store any carry-over from the sum of digits.

2.  **Iterate and Add:**
    *   Start a loop that continues as long as there are still digits in `l1`, or still digits in `l2`, or there is a `carry` value remaining. This ensures we process all digits and any final carry.
    *   Inside the loop:
        *   Initialize a `sum` variable with the current `carry` value.
        *   **Process `l1`:** If `l1` is not `nullptr` (meaning there are still digits in the first number):
            *   Add `l1->val` to `sum`.
            *   Move `l1` to its next node (`l1 = l1->next`).
        *   **Process `l2`:** If `l2` is not `nullptr` (meaning there are still digits in the second number):
            *   Add `l2->val` to `sum`.
            *   Move `l2` to its next node (`l2 = l2->next`).
        *   **Calculate New Carry:** Update `carry` by dividing `sum` by 10 (`carry = sum / 10`). This gives us the carry-over to the next place value.
        *   **Create New Node:** Create a new `ListNode` whose value is `sum % 10`. This is the digit for the current place value (the remainder after taking out the carry).
        *   **Append to Result List:** Attach this new node to the `next` of the current `tail` node (`tail->next = newNode`).
        *   **Advance Tail:** Move the `tail` pointer to this newly added node (`tail = tail->next`).

3.  **Return Result:**
    *   Once the loop finishes, the `dummy` node's `next` pointer will point to the head of the actual sum linked list. Return `dummy.next`.

## 💻 Solution
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x, next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // Create a dummy head node for the result linked list.
        // This simplifies appending the first node and avoids special null checks.
        ListNode dummy(0);  
        
        // Initialize carry to 0. This will store any carry-over from digit addition.
        int carry = 0;
        
        // Initialize a 'tail' pointer to the dummy node.
        // 'tail' will always point to the last node added to our result list,
        // allowing us to easily append new nodes.
        ListNode* tail = &dummy;
        
        // Loop continues as long as there are digits in either l1 or l2,
        // or if there's a remaining carry from previous additions.
        while (l1 || l2 || carry) {
            // Start the sum for the current place value with the existing carry.
            int sum = carry;
            
            // If l1 still has nodes, add its current digit to the sum.
            if (l1) {
                sum += l1->val;
                // Move to the next digit in l1.
                l1 = l1->next;
            }
            
            // If l2 still has nodes, add its current digit to the sum.
            if (l2) {
                sum += l2->val;
                // Move to the next digit in l2.
                l2 = l2->next;
            }
            
            // Calculate the new carry for the next place value.
            // For example, if sum is 17, carry becomes 1.
            carry = sum / 10;
            
            // Create a new node for the result list.
            // The value of this node is the current digit (sum % 10).
            // For example, if sum is 17, the digit is 7.
            tail->next = new ListNode(sum % 10);
            
            // Move the 'tail' pointer to the newly created node,
            // so the next digit can be appended after it.
            tail = tail->next; 
        }
        
        // The actual result list starts from the node after the dummy head.
        // Return dummy.next.
        return dummy.next;
    }
};
```

## ⏱️ Complexity Analysis
Let `N` be the number of nodes in `l1` and `M` be the number of nodes in `l2`.

| | Complexity | Reason |
|---|---|---|
| **Time** | O(max(N, M)) | We iterate through both linked lists at most once. The loop runs for a number of iterations equal to the length of the longer list, plus potentially one more iteration if there's a final carry. Each iteration involves constant time operations. |
| **Space** | O(max(N, M)) | We create a new linked list to store the sum. In the worst case, the sum can have `max(N, M) + 1` digits (e.g., 99 + 1 = 100). Thus, the space required for the new list is proportional to the length of the longer input list. |

## 🔗 Related Problems
- 21. Merge Two Sorted Lists
- 445. Add Two Numbers II
- 67. Add Binary