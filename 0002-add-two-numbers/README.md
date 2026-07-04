# 0002-add-two-numbers

## 📋 Problem Description
You are given two **non-empty** singly linked lists, `l1` and `l2`, where each list represents a non-negative integer. The digits are stored in **reverse order**, and each of their nodes contains a single digit. Your task is to add these two numbers and return the sum as a new linked list, also with its digits stored in reverse order.

You may assume that the two numbers do not contain any leading zeros, except for the number 0 itself.

## 🔍 Examples
```
Input:  l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: The input lists represent 342 and 465 respectively. Their sum is 807, which is represented by [7,0,8].
```

```
Input:  l1 = [0], l2 = [0]
Output: [0]
Explanation: 0 + 0 = 0.
```

```
Input:  l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]
Explanation: The input lists represent 9,999,999 and 9,999. Their sum is 10,009,998, which is represented by [8,9,9,9,0,0,0,1].
```

## 📌 Constraints
*   The number of nodes in each linked list is in the range `[1, 100]`.
*   `0 <= Node.val <= 9`.
*   It is guaranteed that the list represents a number that does not have leading zeros (except for the number 0 itself).

## 🤔 Understanding the Problem
This problem asks us to simulate the process of adding two numbers manually, similar to how we perform addition in elementary school. The key difference is that the numbers are provided as linked lists, with their digits stored in reverse order. This reverse order is actually convenient, as the head of each list represents the least significant digit (units place), allowing us to start addition from the beginning of the lists without needing to reverse them first. We need to handle the concept of "carry-over" when the sum of digits at a particular position exceeds 9, and also correctly manage cases where the two input lists have different lengths.

## 💡 Core Idea
The core idea is to traverse both linked lists simultaneously, adding the corresponding digits from each list along with any `carry` from the previous digit addition. A new linked list is constructed node by node to store the sum's digits.

## 🧠 Approach — Iterative Simulation / Linked List Traversal
This problem is best solved using an iterative simulation approach combined with linked list traversal. We iterate through both linked lists from head to tail, mimicking the manual process of adding numbers column by column. This pattern is suitable because we need to process elements sequentially, and the result is also a linked list built element by element. We maintain a `carry` variable to propagate any overflow from one digit position to the next, which is a fundamental aspect of addition. The use of a dummy head node simplifies the creation and return of the new linked list, especially when dealing with the first node.

## 📝 Step-by-Step Algorithm
1.  **Initialize Result List:** Create a `dummy` head node for the resulting linked list. This node will not hold a digit of the sum but serves as a convenient starting point.
2.  **Initialize Pointers and Carry:**
    *   Initialize a `tail` pointer to point to the `dummy` node. This `tail` pointer will always point to the last node of our sum list, allowing us to easily append new nodes.
    *   Initialize an integer variable `carry` to `0`. This will store any carry-over digit from the previous sum.
3.  **Iterate and Add:** Start a `while` loop that continues as long as any of these conditions are true:
    *   There are still digits remaining in `l1` (i.e., `l1` is not `nullptr`).
    *   There are still digits remaining in `l2` (i.e., `l2` is not `nullptr`).
    *   There is a `carry` remaining from a previous addition (i.e., `carry > 0`).
4.  **Calculate Current Sum:** Inside the loop, initialize a `current_sum` variable with the value of `carry`.
5.  **Add Digits from `l1`:** If `l1` is not `nullptr`:
    *   Add `l1->val` to `current_sum`.
    *   Move `l1` to its next node: `l1 = l1->next`.
6.  **Add Digits from `l2`:** If `l2` is not `nullptr`:
    *   Add `l2->val` to `current_sum`.
    *   Move `l2` to its next node: `l2 = l2->next`.
7.  **Update Carry:** Calculate the new `carry` for the next iteration: `carry = current_sum / 10`.
8.  **Create New Node:** Create a new `ListNode` with the value `current_sum % 10` (this is the digit for the current position in the sum).
9.  **Append Node:** Append this new node to the result list: `tail->next = new_node`.
10. **Advance Tail:** Move the `tail` pointer to the newly added node: `tail = tail->next`.
11. **Return Result:** After the loop finishes, return `dummy.next`. This skips the initial dummy node and returns the actual head of the sum linked list.

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
        // This simplifies appending the first node and handling an empty result,
        // as we can always append to dummy.next.
        ListNode dummy(0);  
        
        // Initialize carry to 0. This will store any carry-over from digit addition.
        int carry = 0;
        
        // 'tail' pointer will always point to the last node of our new sum list.
        // Initially, it points to the dummy node. New nodes will be appended via tail->next.
        ListNode* tail = &dummy;
        
        // Loop continues as long as there are digits in either list (l1 or l2)
        // or a carry remains from a previous addition.
        // This handles lists of different lengths and a potential final carry.
        while (l1 || l2 || carry) {
            // Initialize sum for the current digit position with the current carry.
            int sum = carry;
            
            // If l1 has a current digit, add its value to sum and move l1 to the next node.
            if (l1) {
                sum += l1->val;
                l1 = l1->next;
            }
            
            // If l2 has a current digit, add its value to sum and move l2 to the next node.
            if (l2) {
                sum += l2->val;
                l2 = l2->next;
            }
            
            // Calculate the new carry for the next iteration.
            // For example, if sum is 17, carry becomes 1 (17 / 10 = 1).
            carry = sum / 10;
            
            // Create a new node with the current digit of the sum (sum % 10).
            // For example, if sum is 17, the digit for this position is 7 (17 % 10 = 7).
            tail->next = new ListNode(sum % 10);
            
            // Move the tail pointer to the newly added node,
            // so the next node will be appended after it.
            tail = tail->next; 
        }
        
        // The actual result list starts from dummy.next, as dummy itself is just a placeholder.
        // This handles cases where the sum is 0 (dummy.next will be nullptr) or any other sum.
        return dummy.next;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(max(N, M)) | We iterate through both linked lists once. N and M are the lengths of `l1` and `l2` respectively. The loop runs for at most `max(N, M) + 1` iterations (the `+1` accounts for a potential final carry). |
| **Space** | O(max(N, M)) | A new linked list is created to store the sum. In the worst case (e.g., adding 999 + 1), the resulting list can have `max(N, M) + 1` nodes. |

## 🔗 Related Problems
- 67. Add Binary
- 445. Add Two Numbers II
- 206. Reverse Linked List