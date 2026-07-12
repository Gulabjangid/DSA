# 0445-add-two-numbers-ii

## 📋 Problem Description
You are given two non-empty linked lists, `l1` and `l2`, which represent two non-negative integers. The most significant digit of each number comes first (i.e., at the head of the list), and each node in the list contains a single digit. Your task is to add these two numbers and return their sum as a new linked list.

You can assume that the input numbers do not contain any leading zeros, with the sole exception of the number 0 itself.

The function receives two pointers to the head of the linked lists, `l1` and `l2`, and must return a pointer to the head of a new linked list representing the sum.

## 🔍 Examples
```
Input: l1 = [7,2,4,3], l2 = [5,6,4]
Output: [7,8,0,7]
Explanation: 7243 + 564 = 7807
```

```
Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [8,0,7]
Explanation: 243 + 564 = 807
```

```
Input: l1 = [0], l2 = [0]
Output: [0]
Explanation: 0 + 0 = 0
```

## 📌 Constraints
*   The number of nodes in each linked list is in the range `[1, 100]`.
*   `0 <= Node.val <= 9`
*   It is guaranteed that the list represents a number that does not have leading zeros, except for the number 0 itself.

## 🤔 Understanding the Problem
This problem asks us to add two numbers represented by linked lists. The key challenge here, unlike its sibling problem "Add Two Numbers" (Problem 2), is that the digits are stored in *most significant first* order. This means the head of the list contains the leftmost digit of the number. Standard arithmetic addition, however, proceeds from right to left (least significant digit first). We need a way to access the least significant digits first without actually reversing the input lists, as hinted by the follow-up question.

## 💡 Core Idea
To perform addition from the least significant digit to the most significant digit while the linked lists are structured in most-significant-first order, we need a mechanism to "reverse" the traversal conceptually. Stacks are ideal for this: by pushing all digits onto a stack, the least significant digit will be at the top, allowing us to pop and process them in the correct order for addition.

## 🧠 Approach — Stack
The chosen approach utilizes the **Stack** data structure. Stacks operate on a Last-In, First-Out (LIFO) principle. This property makes them perfect for this problem because if we push all digits of a linked list onto a stack, the first digit pushed (most significant) will be at the bottom, and the last digit pushed (least significant) will be at the top. When we pop elements, we retrieve them in reverse order of how they appeared in the linked list, effectively allowing us to process the numbers from their least significant digits first, just like manual addition.

## 📝 Step-by-Step Algorithm
1.  **Populate Stacks**:
    *   Create two empty stacks, `s1` and `s2`.
    *   Traverse the first linked list `l1`. For each node, push its `val` onto `s1`.
    *   Traverse the second linked list `l2`. For each node, push its `val` onto `s2`.
    *   After this step, the top of `s1` and `s2` will contain the least significant digits of `l1` and `l2` respectively.

2.  **Perform Addition**:
    *   Initialize a `carry` variable to `0`.
    *   Initialize a `result_head` pointer to `NULL`. This pointer will eventually point to the head of our sum linked list. We will build the result list by prepending new nodes.

3.  **Iterate and Add Digits**:
    *   Loop as long as `s1` is not empty, `s2` is not empty, or `carry` is not zero. This ensures all digits are processed and any final carry is handled.
    *   Inside the loop:
        *   Initialize a `sum` variable with the current `carry`.
        *   If `s1` is not empty, add `s1.top()` to `sum` and then pop from `s1`.
        *   If `s2` is not empty, add `s2.top()` to `sum` and then pop from `s2`.
        *   Create a new `ListNode` with the value `sum % 10`. This is the current digit of the sum.
        *   **Prepend to Result List**: Set the `next` pointer of this new node to `result_head`. Then, update `result_head` to point to this new node. This effectively builds the linked list in reverse order (least significant digit first), which means the final `result_head` will correctly point to the most significant digit.
        *   Update `carry` for the next iteration: `carry = sum / 10`.

4.  **Return Result**:
    *   Once the loop finishes, `result_head` will point to the head of the linked list representing the sum. Return `result_head`.

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // Use two stacks to store the digits of l1 and l2.
        // Stacks are chosen because they allow us to access the least significant
        // digits (rightmost) first, which is necessary for addition, even though
        // the linked lists are given in most significant digit first (leftmost) order.
        stack<int> s1, s2;

        // Populate stack s1 with digits from l1.
        // The first node's value (most significant) will be at the bottom,
        // and the last node's value (least significant) will be at the top.
        while (l1) {
            s1.push(l1->val);
            l1 = l1->next;
        }

        // Populate stack s2 with digits from l2, similarly.
        while (l2) {
            s2.push(l2->val);
            l2 = l2->next;
        }

        // Initialize carry for addition.
        int carry = 0;
        // 'head' will point to the head of our resulting linked list.
        // We will build the list by prepending nodes, so 'head' will always
        // point to the most recently added (and thus most significant) digit.
        ListNode* head = NULL;

        // Loop as long as there are digits in either stack or there's a carry.
        // This ensures all digits are processed and any final carry is added.
        while (!s1.empty() || !s2.empty() || carry) {
            // Start sum with the current carry.
            int sum = carry;

            // If s1 is not empty, add its top digit to sum and pop it.
            if (!s1.empty()) {
                sum += s1.top();
                s1.pop();
            }

            // If s2 is not empty, add its top digit to sum and pop it.
            if (!s2.empty()) {
                sum += s2.top();
                s2.pop();
            }

            // Create a new node for the current digit of the sum (sum % 10).
            ListNode* node = new ListNode(sum % 10);
            
            // Prepend the new node to the result list.
            // The 'node' becomes the new head, and its 'next' points to the
            // previous head (which was a more significant digit).
            node->next = head;
            head = node;

            // Calculate the new carry for the next iteration.
            carry = sum / 10;
        }
        // Return the head of the newly formed linked list, which represents the sum.
        return head;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N + M) | We traverse each linked list once to push elements onto stacks (O(N) for `l1`, O(M) for `l2` where N and M are their lengths). Then, we iterate at most `max(N, M) + 1` times (for potential final carry) to pop from stacks and create new nodes. Each stack operation and node creation is O(1). |
| **Space** | O(N + M) | We use two stacks to store all digits from `l1` and `l2`. In the worst case, `s1` stores N elements and `s2` stores M elements. The resulting linked list also takes O(max(N, M)) space, but this is considered output space and not usually counted towards auxiliary space complexity unless specified. |

## 🔗 Related Problems
*   2. Add Two Numbers
*   206. Reverse Linked List
*   739. Daily Temperatures