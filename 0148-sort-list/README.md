# 0148-sort-list

## 📋 Problem Description
Given the `head` of a singly linked list, the task is to sort the list in ascending order and return the head of the sorted list.

The function receives:
- `head`: A pointer to the first node of the linked list.

The function must return:
- A pointer to the head of the sorted linked list.

## 🔍 Examples
**Example 1:**
```
Input: head = [4,2,1,3]
Output: [1,2,3,4]
```

**Example 2:**
```
Input: head = [-1,5,3,4,0]
Output: [-1,0,3,4,5]
```

**Example 3:**
```
Input: head = []
Output: []
```

## 📌 Constraints
- The number of nodes in the list is in the range `[0, 5 * 10^4]`.
- `-10^5 <= Node.val <= 10^5`

## 🤔 Understanding the Problem
The problem asks us to sort a linked list. Unlike arrays, linked lists do not allow for direct random access to elements, which makes many standard sorting algorithms (like quicksort or heapsort) less efficient or more complex to implement directly on the list structure. The challenge lies in efficiently rearranging nodes or their values while maintaining the linked list structure. The "Follow up" specifically asks for an `O(n log n)` time and `O(1)` space solution, indicating that a more advanced approach (like merge sort for linked lists) might be expected, but simpler solutions are also possible.

## 💡 Core Idea
The simplest way to sort data is often to transfer it to a data structure that is easy to sort (like an array or vector), use a highly optimized standard library sort function, and then transfer the sorted data back. This approach leverages the efficiency of built-in sorting for arrays.

## 🧠 Approach — Auxiliary Data Structure & Standard Sort
This solution uses an **Auxiliary Data Structure** (specifically, a `std::vector` in C++) combined with a **Standard Library Sort**. This pattern is suitable here because linked lists are cumbersome to sort in-place with many common algorithms. By extracting all node values into a vector, we gain the benefits of random access and can use `std::sort`, which is typically an introsort (a hybrid of quicksort, heapsort, and insertion sort) offering `O(N log N)` average-case time complexity. After sorting the values, we simply iterate through the linked list again and update each node's value with the corresponding sorted value from the vector.

## 📝 Step-by-Step Algorithm
1.  **Handle Empty List**: If the input `head` is `nullptr` (an empty list), return `nullptr` immediately as there's nothing to sort.
2.  **Extract Values**: Initialize an empty `std::vector<int>` named `ans`. Traverse the input linked list starting from `head`. For each node encountered, append its `val` to the `ans` vector.
3.  **Sort Values**: Once all values are extracted into `ans`, use the standard library sort function (`std::sort` in C++) to sort the elements of `ans` in ascending order.
4.  **Update Linked List**: Traverse the linked list again, starting from `head`. Simultaneously, iterate through the sorted `ans` vector. For each node in the linked list, update its `val` with the corresponding value from the `ans` vector.
5.  **Return Head**: After updating all node values, return the original `head` of the linked list, which now contains the sorted values.

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
    ListNode* sortList(ListNode* head) {
        // Step 1: Handle the edge case of an empty list.
        // If the list is empty, there's nothing to sort, so return head (which is nullptr).
        if (!head) {
            return head;
        }

        // Step 2: Create a vector to store all node values.
        std::vector<int> ans;
        // Use a temporary pointer to traverse the linked list.
        ListNode* temp = head;

        // Iterate through the linked list and push each node's value into the vector.
        while (temp) {
            ans.push_back(temp->val);
            temp = temp->next;
        }

        // Step 3: Sort the vector containing all node values.
        // std::sort uses an optimized hybrid algorithm (introsort) for efficient sorting.
        std::sort(ans.begin(), ans.end());

        // Step 4: Traverse the linked list again and update node values from the sorted vector.
        // Reset the temporary pointer to the head of the list.
        ListNode* temp2 = head;
        // Iterate through the sorted vector and the linked list simultaneously.
        for (int i = 0; i < ans.size(); i++) {
            // Update the current linked list node's value with the sorted value from the vector.
            temp2->val = ans[i];
            // Move to the next node in the linked list.
            temp2 = temp2->next;
        }

        // Step 5: Return the head of the linked list, which now contains the sorted values.
        return head;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N log N) | O(N) to traverse the list and copy values to the vector, O(N log N) for `std::sort` on N elements, and O(N) to traverse the list again and update values. The dominant factor is O(N log N). |
| **Space** | O(N) | An auxiliary `std::vector` is used to store all N node values, requiring O(N) space. |

## 🔗 Related Problems
- 21. Merge Two Sorted Lists
- 147. Insertion Sort List
- 23. Merge k Sorted Lists