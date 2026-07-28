# 0344-reverse-string

## 📋 Problem Description
Write a function that takes a character array, representing a string, and reverses it. The modification must be done directly on the input array (in-place) and should use only a constant amount of extra memory (O(1) space complexity).

**Input**: A `vector<char>& s`, which is a reference to a character array.
**Output**: The function should not return anything. Instead, it should modify the input `s` directly to contain the reversed string.

## 🔍 Examples
```
Input:  s = ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]
Explanation: The original string "hello" is reversed to "olleh".
```

```
Input:  s = ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]
Explanation: The original string "Hannah" is reversed to "hannaH".
```

## 📌 Constraints
*   `1 <= s.length <= 10^5`
*   `s[i]` is a printable ASCII character.

## 🤔 Understanding the Problem
The problem asks us to reverse a given string, which is provided as a character array. The crucial part is the requirement to perform this reversal "in-place" and with "O(1) extra memory". This means we cannot create a new array to store the reversed string and then copy it back. Instead, we must modify the existing character array directly, using only a fixed, minimal amount of additional storage (like a few variables for pointers or temporary storage for a swap). This makes it a classic problem for demonstrating efficient in-place array manipulation.

## 💡 Core Idea
To reverse a string in-place, we can swap characters from the beginning with characters from the end, progressively moving towards the center of the string until all necessary swaps have been made.

## 🧠 Approach — Two Pointers
This problem is perfectly suited for the **Two Pointers** pattern. This pattern involves using two pointers (or indices) that traverse a data structure (like an array or string) from different positions, often towards each other or in the same direction, to achieve a specific goal. In this case, one pointer starts at the beginning of the string, and the other starts at the end. They move towards the middle, swapping the characters they point to. This approach is ideal for in-place modifications where elements at opposite ends need to interact, and it naturally satisfies the O(1) extra space constraint.

## 📝 Step-by-Step Algorithm
1.  **Initialize Pointers**: Create two integer pointers, `left` and `right`.
    *   Set `left` to `0`, pointing to the first character of the string.
    *   Set `right` to `s.size() - 1`, pointing to the last character of the string.
2.  **Iterate and Swap**: Begin a loop that continues as long as `left` is less than `right`. This condition ensures that we only process distinct pairs of characters and stop when the pointers meet or cross in the middle.
3.  **Perform Swap**: Inside the loop, swap the characters at the positions pointed to by `left` and `right`. That is, `s[left]` is swapped with `s[right]`.
4.  **Move Pointers**: After each swap:
    *   Increment `left` by 1, moving it one step to the right.
    *   Decrement `right` by 1, moving it one step to the left.
5.  **Termination**: The loop terminates when `left` is no longer less than `right`. At this point, all characters will have been swapped with their counterparts from the opposite end, and the string `s` will be fully reversed.

## 💻 Solution
```cpp
class Solution {
public:
    void reverseString(vector<char>& s) {
        // Initialize a pointer 'left' to the beginning of the character array.
        // This pointer will move from left to right.
        int left = 0;

        // Initialize a pointer 'right' to the end of the character array.
        // This pointer will move from right to left.
        int right = s.size() - 1;

        // Continue swapping characters as long as the 'left' pointer is
        // to the left of the 'right' pointer. This ensures we process
        // each pair of characters exactly once and stop when the middle
        // is reached (for odd length strings) or crossed (for even length strings).
        while (left < right) {
            // Swap the character at the 'left' pointer's position with
            // the character at the 'right' pointer's position.
            // For example, in ["h","e","l","l","o"], first swap 'h' and 'o'.
            std::swap(s[left], s[right]); // Using std::swap for clarity and robustness

            // Move the 'left' pointer one step to the right, towards the center.
            left++;

            // Move the 'right' pointer one step to the left, towards the center.
            right--;
        }
        // After the loop, the string 's' will be reversed in-place.
        // No explicit return is needed as the input vector 's' is modified by reference.
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through approximately half of the string's elements (N/2 swaps), performing a constant number of operations (swap, increment, decrement) for each pair. |
| **Space** | O(1) | We only use a few integer variables (`left`, `right`) for pointers, regardless of the input string's size. No additional data structures are allocated proportional to the input size. |

## 🔗 Related Problems
- 125. Valid Palindrome
- 345. Reverse Vowels of a String
- 11. Container With Most Water