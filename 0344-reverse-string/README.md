# 0344-reverse-string

## 📋 Problem Description
Write a function that takes an array of characters, `s`, representing a string, and reverses the string in-place. This means you must modify the input array directly without allocating extra space for another array. The solution must use `O(1)` extra memory.

The function signature will typically be `void reverseString(vector<char>& s)`.

## 🔍 Examples
**Example 1:**
```
Input:  s = ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]
```

**Example 2:**
```
Input:  s = ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]
```

## 📌 Constraints
*   `1 <= s.length <= 10^5`
*   `s[i]` is a printable ASCII character.

## 🤔 Understanding the Problem
The problem asks us to reverse the order of characters within a given string, which is provided as a `vector<char>`. The crucial part is the requirement to perform this operation "in-place" and with "O(1) extra memory". This means we cannot create a new string or array to store the reversed characters and then copy them back. Instead, we must manipulate the existing `vector<char>` directly, using only a constant amount of additional memory (e.g., a few variables). This constraint makes simple approaches like creating a reversed copy invalid.

## 💡 Core Idea
To reverse a string in-place, we can swap characters from the opposite ends of the string. The first character swaps with the last, the second with the second-to-last, and so on, until we reach the middle of the string.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern.
The Two Pointers pattern is ideal here because we need to simultaneously track and manipulate two distinct positions within the array: one from the beginning and one from the end. By moving these pointers towards each other, we can efficiently process pairs of elements that need to be swapped to achieve the reversal, without needing to store intermediate results or use extra space.

## 📝 Step-by-Step Algorithm
1.  Initialize a `left` pointer to point to the first character of the array (index 0).
2.  Initialize a `right` pointer to point to the last character of the array (index `s.size() - 1`).
3.  Start a loop that continues as long as the `left` pointer is less than the `right` pointer. This condition ensures that we only process unique pairs of characters and stop when the pointers meet or cross, indicating that the string has been fully reversed.
4.  Inside the loop, swap the character at the `left` pointer's position (`s[left]`) with the character at the `right` pointer's position (`s[right]`).
5.  After swapping, increment the `left` pointer by one to move it one step towards the center of the array.
6.  Decrement the `right` pointer by one to move it one step towards the center of the array.
7.  Once the loop terminates (when `left >= right`), the array `s` will contain the reversed string, and the function finishes.

## 💻 Solution
```cpp
class Solution {
public:
    void reverseString(vector<char>& s) {
        // Initialize a 'left' pointer at the beginning of the character array.
        // This pointer will move from left to right.
        int left = 0;
        
        // Initialize a 'right' pointer at the end of the character array.
        // s.size() returns the number of elements, so s.size() - 1 is the last valid index.
        // This pointer will move from right to left.
        int right = s.size() - 1;

        // Continue swapping characters as long as the 'left' pointer is before the 'right' pointer.
        // This condition ensures that we process each pair of characters from opposite ends exactly once.
        // When left >= right, all necessary swaps have been made (or it's an odd-length string
        // and the middle character doesn't need swapping, or the string is empty/single character).
        while (left < right) {
            // Swap the character at the 'left' pointer's position with the character at the 'right' pointer's position.
            // C++'s std::swap efficiently exchanges the values of two variables.
            std::swap(s[left], s[right]);

            // Move the 'left' pointer one step to the right (towards the center).
            left++;
            // Move the 'right' pointer one step to the left (towards the center).
            right--;
        }
        // The function is void, meaning it doesn't return a value. The input vector 's'
        // is modified in-place, which is the problem requirement.
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The algorithm iterates through approximately half of the string's length (N/2 swaps). Each swap operation takes constant time. Therefore, the total time complexity is linear with respect to the string's length. |
| **Space** | O(1) | We only use a constant number of extra variables (`left`, `right`) regardless of the input string's size. No additional data structures are allocated that scale with the input. |

## 🔗 Related Problems
*   125. Valid Palindrome
*   167. Two Sum II - Input Array Is Sorted
*   345. Reverse Vowels of a String