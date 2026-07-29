# 0148-sort-list

## 📋 Problem Description
Given the `head` of a singly linked list, the task is to sort the list in ascending order and return the head of the sorted list.

The function receives a pointer to the `head` node of a linked list. It must return a pointer to the `head` of the same list, but with its nodes reordered such that their values are in non-decreasing order.

## 🔍 Examples
```
Input: head = [4,2,1,3]
Output: [1,2,3,4]
Explanation: The original list [4,2,1,3] is sorted to [1,2,3,4].

Input: head = [-1,5,3,4,0]
Output: [-1,0,3,4,5]
Explanation: The original list [-1,5,3,4,0] is sorted to [-1,0,3,4,5].

Input: head = []
Output: []
Explanation: An empty list remains an empty list after sorting.
```

## 📌 Constraints
*   The number of nodes in the list is in the range `[0, 5 * 10^4]`.
*   `-10^5 <= Node.val <= 10^5`

## 🤔 Understanding the Problem
The problem asks us to sort a linked list. Unlike arrays, linked lists do not allow for direct random access to elements, which makes many standard sorting algorithms (like QuickSort or HeapSort) less efficient or more complex to implement directly. We need to rearrange the nodes or their values such that they are in ascending order. An important edge case is an empty list, which should be returned as is. The problem also includes a "Follow up" asking for an `O(n log n)` time and `O(1)` space solution, which implies that a solution using auxiliary space might be simpler but not optimal in terms of space.

## 💡 Core Idea
The core idea behind this solution is to leverage the efficient sorting capabilities of standard library functions designed for arrays. We can extract all node values into a dynamic array (vector), sort this array, and then iterate through the original linked list, updating each node's value with the sorted values from the array.

## 🧠 Approach — Auxiliary Data Structure and Standard Library Sort
This approach uses an **Auxiliary Data Structure** (specifically, a `std::vector` in C++) combined with a **Standard Library Sort** function. This pattern is suitable when direct manipulation of the original data structure (like a linked list) for sorting is cumbersome or less efficient, but converting it to a more amenable structure (like an array) allows for simpler and often optimized sorting. Here, we convert the linked list to a vector, which allows us to use `std::sort` (an efficient comparison sort), and then map the sorted values back to the linked list.

## 📝 Step-by-Step Algorithm
1.  **Handle Empty List**: Check if the `head` of the list is `nullptr`. If it is, the list is empty, so return `head` immediately.
2.  **Extract Values**: Initialize an empty `std::vector<int>` to store the values from the linked list.
3.  **Traverse and Populate**: Iterate through the linked list starting from `head`. For each node encountered, add its `val` to the `std::vector`. Continue until the end of the list is reached.
4.  **Sort Values**: Use the standard library's sort function (`std::sort` in C++) to sort the `std::vector` in ascending order.
5.  **Update Linked List**: Reset a temporary pointer to the `head` of the original linked list.
6.  **Traverse and Update**: Iterate through the linked list again, using the temporary pointer. For each node, assign its `val` to the next value from the sorted `std::vector`. Increment the index for the vector and move the temporary pointer to the next node in the list.
7.  **Return Head**: After updating all node values, return the original `head` of the linked list, which now contains the sorted values.

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
        // If the list is empty, there's nothing to sort, so return it as is.
        if (head == nullptr) {
            return head;
        }

        // Step 2: Create an auxiliary data structure (vector) to store node values.
        vector<int> ans;

        // Step 3: Traverse the linked list and populate the vector with node values.
        ListNode* temp = head; // Use a temporary pointer to traverse the list
        while (temp) {         // Loop until the end of the list (temp becomes nullptr)
            ans.push_back(temp->val); // Add the current node's value to the vector
            temp = temp->next;         // Move to the next node
        }

        // Step 4: Sort the vector containing all node values.
        // std::sort uses an efficient algorithm (typically IntroSort, a hybrid)
        // which provides O(N log N) average time complexity.
        sort(ans.begin(), ans.end());

        // Step 5: Reset a temporary pointer to the head of the original linked list.
        ListNode* temp2 = head;

        // Step 6: Traverse the linked list again and update node values
        // with the sorted values from the vector.
        for (int i = 0; i < ans.size(); i++) {
            temp2->val = ans[i]; // Assign the sorted value from the vector to the current node
            temp2 = temp2->next; // Move to the next node in the linked list
        }

        // Step 7: Return the head of the linked list.
        // The list's nodes now contain the sorted values.
        return head;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N log N) | Traversing the list takes O(N). Sorting the vector takes O(N log N). Updating the list takes O(N). The dominant factor is sorting. |
| **Space** | O(N) | An auxiliary `std::vector` is used to store all N node values, requiring O(N) space. |

## 🔗 Related Problems
- 21. Merge Two Sorted Lists
- 147. Insertion Sort List
- 23. Merge k Sorted Lists