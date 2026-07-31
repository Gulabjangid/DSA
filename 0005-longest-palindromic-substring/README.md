# 0005-longest-palindromic-substring

## 📋 Problem Description
Given a string `s`, the task is to find and return the longest substring within `s` that is a palindrome. A palindrome is a sequence of characters that reads the same forwards and backward. If there are multiple palindromic substrings of the same maximum length, any one of them is a valid answer.

## 🔍 Examples
```
Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.
```

```
Input: s = "cbbd"
Output: "bb"
```

```
Input: s = "a"
Output: "a"
```

## 📌 Constraints
*   `1 <= s.length <= 1000`
*   `s` consists of only digits and English letters.

## 🤔 Understanding the Problem
The problem asks us to identify the longest contiguous sequence of characters within a given string `s` that exhibits palindromic properties. This means we need to examine various substrings, check if they are palindromes, and keep track of the longest one found. A single character is always a palindrome, which serves as a base case. The non-trivial aspect lies in efficiently checking all potential substrings without resorting to a brute-force approach that would be too slow for larger input strings.

## 💡 Core Idea
The fundamental insight is that every palindrome expands outwards from a central point. This center can either be a single character (for odd-length palindromes like "racecar") or the space between two identical characters (for even-length palindromes like "abba").

## 🧠 Approach — Expand Around Center
This problem is optimally solved using the "Expand Around Center" algorithmic pattern. This pattern is highly effective for palindrome-related problems because it leverages the inherent symmetry of palindromes. Instead of generating all possible substrings and then checking each for palindromicity (which would be inefficient), we can iterate through every possible "center" of a palindrome. From each center, we expand outwards, comparing characters symmetrically. This allows us to efficiently discover the longest palindrome centered at that specific point, significantly reducing redundant computations.

## 📝 Step-by-Step Algorithm
1.  **Initialization**:
    *   Initialize `start` to `0`, which will store the starting index of the longest palindromic substring found so far.
    *   Initialize `maxLen` to `1`, representing the length of the longest palindrome found so far (a single character is always a palindrome).
2.  **Base Case**: If the input string `s` has a length of 0 or 1, it is already a palindrome, so return `s` directly.
3.  **Iterate Through Potential Centers**: Loop through the string `s` using an index `i` from `0` to `n-1` (where `n` is the length of `s`). For each `i`, we consider two types of palindromes that could be centered at or around `i`:
    *   **Odd Length Palindromes**: Assume `s[i]` is the center character. Call a helper function `expand` with `left = i` and `right = i`.
    *   **Even Length Palindromes**: Assume the "center" is between `s[i]` and `s[i+1]`. Call the helper function `expand` with `left = i` and `right = i + 1`.
4.  **`expand` Helper Function**: This function takes the string `s`, two pointers `left` and `right` (representing the current boundaries of the potential palindrome), and references to `start` and `maxLen` to update them globally.
    *   It continues to expand outwards as long as three conditions are met:
        *   `left` is within the string bounds (`left >= 0`).
        *   `right` is within the string bounds (`right < n`).
        *   The characters at `s[left]` and `s[right]` are equal (`s[left] == s[right]`).
    *   Inside the loop:
        *   Calculate the `currLen` of the palindrome found so far: `right - left + 1`.
        *   If `currLen` is greater than `maxLen`, update `maxLen` to `currLen` and `start` to `left`.
        *   Decrement `left` by 1 and increment `right` by 1 to continue expanding.
5.  **Return Result**: After the loop finishes iterating through all possible centers, `start` and `maxLen` will hold the starting index and length of the longest palindromic substring. Use `s.substr(start, maxLen)` to extract and return this substring.

## 💻 Solution
```cpp
class Solution {
public:
    // Helper function to expand around a center and update the longest palindrome found
    // 's': The input string
    // 'left', 'right': Pointers defining the current center(s) to expand from
    // 'start': Reference to the global starting index of the longest palindrome
    // 'maxLen': Reference to the global maximum length of the longest palindrome
    void expand(string &s, int left, int right, int &start, int &maxLen) {
        int n = s.size(); // Get the length of the string for boundary checks

        // Expand outwards as long as characters match and pointers are within string bounds
        while (left >= 0 && right < n && s[left] == s[right]) {
            // Calculate the current length of the palindrome found
            int currLen = right - left + 1;

            // If this palindrome is longer than the current maximum length, update
            if (currLen > maxLen) {
                maxLen = currLen; // Update the maximum length found
                start = left;     // Update the starting index of this new longest palindrome
            }

            left--;  // Move the left pointer one step to the left (inwards)
            right++; // Move the right pointer one step to the right (outwards)
        }
    }

    // Main function to find the longest palindromic substring
    string longestPalindrome(string s) {
        int n = s.size(); // Get the length of the input string

        // Base case: If the string has 0 or 1 character, it is itself the longest palindrome
        if (n <= 1)
            return s;

        int start = 0;    // Initialize the starting index of the longest palindrome found
        int maxLen = 1;   // Initialize the maximum length (a single character is always a palindrome)

        // Iterate through each character of the string
        // Each character 'i' can be a potential center for a palindrome
        for (int i = 0; i < n; i++) {
            // Case 1: Handle palindromes with odd length (e.g., "aba", "racecar")
            // The center is a single character at index 'i'.
            // We start expanding from 'i' as both left and right pointers.
            expand(s, i, i, start, maxLen);

            // Case 2: Handle palindromes with even length (e.g., "abba", "noon")
            // The center is between two characters, 'i' and 'i+1'.
            // We start expanding from 'i' as left and 'i+1' as right.
            expand(s, i, i + 1, start, maxLen);
        }

        // After checking all possible centers, 'start' and 'maxLen' will hold
        // the details of the longest palindromic substring.
        // Use substr(start_index, length) to extract and return it.
        return s.substr(start, maxLen);
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N^2) | The algorithm iterates through `N` possible centers. For each center, the `expand` function can, in the worst case, traverse up to `N/2` characters in each direction, leading to an O(N) operation. Thus, `N * O(N)` results in O(N^2). |
| **Space** | O(1) | The solution uses only a few constant extra variables (`start`, `maxLen`, `left`, `right`, `currLen`) regardless of the input string's size. |

## 🔗 Related Problems
*   647. Palindromic Substrings
*   214. Shortest Palindrome
*   131. Palindrome Partitioning