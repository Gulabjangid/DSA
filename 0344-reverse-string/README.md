# 0344-reverse-string

## 📋 Problem Description
You are tasked with writing a function that takes a string as input, represented as an array of characters. Your goal is to reverse this string. The crucial requirement is that you must modify the input array directly (in-place) and use only a constant amount of extra memory (O(1) space complexity).

The function `reverseString` receives a `vector<char>& s` (a reference to a vector of characters) and should modify `s` such that its characters are in reverse order. It does not need to return anything explicitly, as the modification happens directly on the input vector.

## 🔍 Examples
```
Input:  s = ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]

Input:  s = ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]
```

## 📌 Constraints
*   `1 <= s.length <= 10^5`
*   `s[i]` is a printable ASCII character.

## 🤔 Understanding the Problem
The problem asks us to reverse the order of characters in a given string, which is provided as a character array. The main challenge isn't just reversing the string, but doing so *in-place* and with *O(1) extra memory*. This means we cannot create a new string or array to store the reversed characters and then copy it back. We must manipulate the existing character array directly, using only a few temporary variables. This constraint is common in competitive programming to test understanding of efficient memory usage.

## 💡 Core Idea
The most intuitive way to reverse a sequence in-place is to swap elements from opposite ends of the sequence until the middle is reached.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern. This pattern is ideal when you need to process elements from both ends of a sequence (like an array or string) simultaneously, often moving towards the center, or when you need to maintain two distinct positions within a sequence. It fits this problem perfectly because reversing a string involves pairing the first character with the last, the second with the second-to-last, and so on, and swapping them. The two pointers help us keep track of these corresponding positions efficiently.

## 📝 Step-by-Step Algorithm
1.  Initialize two pointers: `left` at the beginning of the character array (index 0) and `right` at the end of the character array (index `s.size() - 1`).
2.  Enter a loop that continues as long as the `left` pointer is less than the `right` pointer. This ensures we process pairs of characters without overwriting already swapped characters or swapping an element with itself.
3.  Inside the loop, swap the characters at the `left` pointer's position and the `right` pointer's position.
4.  After each swap, move the `left` pointer one step to the right (`left++`) and the `right` pointer one step to the left (`right--`). This brings the pointers closer to the center of the array.
5.  Once the loop terminates (when `left` is no longer less than `right`), the entire string will be reversed in-place.

*Note: The provided solution uses `std::reverse`, which is a C++ standard library function that internally implements this very two-pointer swapping logic for random-access iterators.*

## 💻 Solution
```cpp
#include <vector> // Required for std::vector
#include <algorithm> // Required for std::reverse and std::swap

class Solution {
public:
    void reverseString(std::vector<char>& s) {
        // The problem asks for an in-place reversal with O(1) extra memory.
        // C++'s Standard Library provides a highly optimized function for this: std::reverse.
        // It works by taking two iterators (pointers to the beginning and end of the range)
        // and swaps elements from opposite ends until the range is reversed.
        // This operation is inherently O(N) time complexity and O(1) space complexity.
        std::reverse(s.begin(), s.end());

        // Alternatively, one could implement the two-pointer approach manually,
        // which std::reverse essentially does under the hood for random-access iterators.
        // This commented-out code demonstrates that manual implementation:

        /*
        int left = 0; // Pointer starting from the beginning of the string
        int right = s.size() - 1; // Pointer starting from the end of the string

        // Continue swapping as long as the left pointer is before the right pointer.
        // When left >= right, all necessary swaps have been performed.
        while (left < right) {
            // Swap the characters at the left and right pointers
            std::swap(s[left], s[right]);

            // Move the left pointer one step to the right
            left++;
            // Move the right pointer one step to the left
            right--;
        }
        */
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The `std::reverse` function (or the manual two-pointer approach) iterates through approximately half of the N characters in the string, performing a constant number of operations (swaps) for each pair. |
| **Space** | O(1) | The reversal is done in-place. Only a constant amount of extra memory is used for variables (like iterators or the `left`/`right` pointers and a temporary variable for swapping). |

## 🔗 Related Problems
- 125. Valid Palindrome
- 345. Reverse Vowels of a String
- 167. Two Sum II - Input Array Is Sorted