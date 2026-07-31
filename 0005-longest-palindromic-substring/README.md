# 0005-longest-palindromic-substring

## 📋 Problem Description
Given a string `s`, the task is to find and return the longest substring within `s` that is a palindrome. A palindrome is a sequence of characters that reads the same forwards and backwards (e.g., "madam", "racecar"). The input `s` will consist only of digits and English letters.

## 🔍 Examples
```
Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer, but "bab" is chosen as one of the longest.
```

```
Input: s = "cbbd"
Output: "bb"
Explanation: "bb" is the longest palindromic substring.
```

## 📌 Constraints
*   `1 <= s.length <= 1000`
*   `s` consists of only digits and English letters.

## 🤔 Understanding the Problem
The problem asks us to identify the longest continuous sequence of characters within a given string `s` that forms a palindrome. This means we need to examine all possible substrings of `s`, check if each one is a palindrome, and keep track of the longest one we encounter. The challenge lies in doing this efficiently, as a naive approach of checking every substring for palindromicity would be too slow for strings up to 1000 characters long. Edge cases include very short strings (length 1 or 2), where the string itself might be the longest palindrome.

## 💡 Core Idea
The fundamental insight is that every palindrome expands outwards from a central point. This center can either be a single character (for odd-length palindromes like "aba") or two adjacent characters (for even-length palindromes like "abba").

## 🧠 Approach — Expand Around Center
This problem is efficiently solved using the "Expand Around Center" pattern. This pattern is particularly well-suited for problems involving palindromes because it leverages their inherent symmetry. The approach systematically considers every possible character and every possible pair of adjacent characters in the string as potential centers of a palindrome. From each potential center, it expands outwards in both directions, checking if the characters at the expanding pointers are equal. This process continues until the pointers go out of bounds or the characters no longer match, at which point the longest palindrome centered at that point has been found. By doing this for all possible centers, we guarantee that we will find the overall longest palindromic substring.

## 📝 Step-by-Step Algorithm
1.  **Initialization**:
    *   Initialize `maxLen` to 1 (the minimum possible length for a palindrome, as a single character is a palindrome).
    *   Initialize `start` to 0 (the starting index of the longest palindrome found so far).
    *   Get the length of the input string `s`, let's call it `n`.

2.  **Base Case Handling**:
    *   If `n` is 0 or 1, the string itself is the longest palindrome. Return `s`.

3.  **Iterate Through Potential Centers**:
    *   Loop through the string using an index `i` from `0` to `n-1`. For each `i`, we consider two types of centers:
        *   **Odd Length Palindromes**: Treat `s[i]` as the single center. Call a helper function `expand(s, i, i, start, maxLen)`.
        *   **Even Length Palindromes**: Treat the space between `s[i]` and `s[i+1]` as the center. Call a helper function `expand(s, i, i + 1, start, maxLen)`.

4.  **`expand` Helper Function Logic**:
    *   The `expand` function takes the string `s`, two pointers `left` and `right` (representing the initial center(s)), and references to `start` and `maxLen` (to update the global longest palindrome).
    *   It enters a `while` loop that continues as long as these conditions are met:
        *   `left` is within the string bounds (`left >= 0`).
        *   `right` is within the string bounds (`right < n`).
        *   The characters at `s[left]` and `s[right]` are equal (`s[left] == s[right]`).
    *   Inside the loop:
        *   Calculate the current palindrome's length: `currLen = right - left + 1`.
        *   If `currLen` is greater than `maxLen`:
            *   Update `maxLen` to `currLen`.
            *   Update `start` to `left` (as this is the new starting index of the longest palindrome).
        *   Decrement `left` by 1 (move inwards).
        *   Increment `right` by 1 (move outwards).

5.  **Return Result**:
    *   After the loop finishes iterating through all possible centers, `start` and `maxLen` will hold the starting index and length of the longest palindromic substring found.
    *   Use `s.substr(start, maxLen)` to extract and return the final substring.

## 💻 Solution
```cpp
class Solution {
public:
    // Helper function to expand outwards from a given center (left, right)
    // and update the global longest palindrome's start index and length.
    void expand(string &s, int left, int right, int &start, int &maxLen) {
        int n = s.size(); // Get the total length of the string for boundary checks

        // Continue expanding as long as:
        // 1. The left pointer is within string bounds (>= 0)
        // 2. The right pointer is within string bounds (< n)
        // 3. The characters at the left and right pointers match
        while (left >= 0 && right < n && s[left] == s[right]) {
            // Calculate the length of the current palindrome
            int currLen = right - left + 1;

            // If this palindrome is longer than the longest one found so far
            if (currLen > maxLen) {
                maxLen = currLen; // Update the maximum length
                start = left;     // Update the starting index of the longest palindrome
            }

            left--;  // Move the left pointer one step to the left (inwards)
            right++; // Move the right pointer one step to the right (outwards)
        }
    }

    string longestPalindrome(string s) {
        int n = s.size(); // Get the total length of the string

        // Base case: If the string has 0 or 1 character, it is already a palindrome.
        // Return the string itself.
        if (n <= 1)
            return s;

        int start = 0;    // This will store the starting index of the longest palindrome found
        int maxLen = 1;   // This will store the maximum length of a palindrome found.
                          // Initialize to 1 because a single character is always a palindrome.

        // Iterate through each character of the string.
        // Each character 'i' can be a potential center for a palindrome.
        for (int i = 0; i < n; i++) {
            // Case 1: Palindromes with odd length (e.g., "aba", "racecar")
            // The center is a single character at index 'i'.
            // We start expanding with left = i and right = i.
            expand(s, i, i, start, maxLen);

            // Case 2: Palindromes with even length (e.g., "bb", "abba")
            // The center is between two characters at indices 'i' and 'i+1'.
            // We start expanding with left = i and right = i + 1.
            expand(s, i, i + 1, start, maxLen);
        }

        // After checking all possible centers, 'start' and 'maxLen' hold the
        // information for the longest palindromic substring.
        // Use substr(start_index, length) to extract and return it.
        return s.substr(start, maxLen);
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N^2) | We iterate through `N` possible centers. For each center, the `expand` function can, in the worst case (e.g., "aaaaa"), expand up to `N/2` times. This results in `N * N/2` operations, which simplifies to O(N^2). |
| **Space** | O(1) | We only use a few constant extra variables (`start`, `maxLen`, `left`, `right`, `currLen`) to store state, regardless of the input string's size. |

## 🔗 Related Problems
- 647. Palindromic Substrings
- 516. Longest Palindromic Subsequence
- 131. Palindrome Partitioning