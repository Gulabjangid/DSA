# 0005-longest-palindromic-substring

## 📋 Problem Description
Given a string `s`, the task is to find and return the longest substring within `s` that is also a palindrome. A palindromic substring is a sequence of characters that reads the same forwards and backwards. If there are multiple palindromic substrings of the maximum length, any one of them is considered a valid answer.

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

## 📌 Constraints
*   `1 <= s.length <= 1000`
*   `s` consists of only digits and English letters.

## 🤔 Understanding the Problem
The problem asks us to identify the longest continuous sequence of characters within a given string `s` that exhibits palindromic properties. This means we need to examine various substrings, check if they are palindromes, and keep track of the longest one found. A key consideration is handling both odd-length palindromes (like "racecar") and even-length palindromes (like "madam"). Strings of length 1 are always palindromes, which is an important edge case. The challenge lies in efficiently checking all potential palindromic substrings without excessive redundant computations.

## 💡 Core Idea
The central insight is that every palindrome expands outwards from a "center." This center can be a single character (for odd-length palindromes) or two adjacent characters (for even-length palindromes). By iterating through all possible centers and expanding from them, we can efficiently find all palindromes and, consequently, the longest one.

## 🧠 Approach — Expand Around Center
This problem is optimally solved using the "Expand Around Center" pattern. This pattern is highly effective for palindrome-related problems because palindromes inherently possess a symmetrical structure. Instead of generating all possible substrings (which is O(N^2)) and then checking each for palindromic properties (O(N) for each check, leading to an O(N^3) naive solution), we can significantly optimize. The "Expand Around Center" approach iterates through every potential center point in the string. For each center, it expands outwards in both directions, comparing characters, until the palindrome property is broken or the string boundaries are reached. This method directly leverages the symmetrical nature of palindromes to find them efficiently.

## 📝 Step-by-Step Algorithm
1.  **Initialize Tracking Variables**: Declare `start` to store the starting index of the longest palindrome found so far, initialized to `0`. Declare `maxLen` to store the length of the longest palindrome, initialized to `1`.
2.  **Handle Base Cases**: If the input string `s` has a length of 0 or 1, it is already a palindrome. In this case, return `s` directly.
3.  **Iterate Through Potential Centers**: Loop through the string `s` using an index `i` from `0` to `n-1` (where `n` is the length of `s`). For each `i`, consider two scenarios for potential palindrome centers:
    *   **Odd Length Palindromes**: Assume `s[i]` is the center of an odd-length palindrome. Call a helper function (e.g., `expand`) with `left = i` and `right = i`.
    *   **Even Length Palindromes**: Assume the space between `s[i]` and `s[i+1]` is the center of an even-length palindrome. Call the `expand` helper function with `left = i` and `right = i + 1`.
4.  **`expand` Helper Function Logic**:
    *   This function takes the string `s`, two pointers `left` and `right` (representing the current expansion boundaries), and references to `start` and `maxLen` (to update the global longest palindrome).
    *   It enters a `while` loop that continues as long as:
        *   `left` is a valid index (greater than or equal to 0).
        *   `right` is a valid index (less than `n`).
        *   The characters at `s[left]` and `s[right]` are equal.
    *   Inside the loop:
        *   Calculate the `currLen` of the palindrome: `right - left + 1`.
        *   If `currLen` is greater than `maxLen`, update `maxLen` to `currLen` and `start` to `left`.
        *   Decrement `left` and increment `right` to continue expanding outwards.
5.  **Return Result**: After the loop finishes iterating through all possible centers, `start` and `maxLen` will correctly point to the beginning and length of the longest palindromic substring. Use `s.substr(start, maxLen)` to extract and return this substring.

## 💻 Solution
```cpp
class Solution {
public:
    // Helper function to expand around a center and update the longest palindrome found
    void expand(string &s, int left, int right, int &start, int &maxLen) {
        int n = s.size(); // Get the length of the string

        // Expand outwards as long as:
        // 1. 'left' pointer is within string bounds (>= 0)
        // 2. 'right' pointer is within string bounds (< n)
        // 3. Characters at 'left' and 'right' are equal (maintaining palindrome property)
        while (left >= 0 && right < n && s[left] == s[right]) {
            // Calculate the current length of the palindrome
            int currLen = right - left + 1;

            // If this palindrome is longer than the current longest, update maxLen and start
            if (currLen > maxLen) {
                maxLen = currLen; // Update maximum length
                start = left;     // Update starting index of the longest palindrome
            }

            left--;  // Move left pointer inwards
            right++; // Move right pointer outwards
        }
    }

    string longestPalindrome(string s) {
        int n = s.size(); // Get the length of the input string

        // Base case: if string has 0 or 1 character, it's already a palindrome
        if (n <= 1)
            return s;

        int start = 0;    // Stores the starting index of the longest palindrome found
        int maxLen = 1;   // Stores the maximum length of the longest palindrome found
                          // Initialized to 1 because a single character is always a palindrome

        // Iterate through each character of the string
        for (int i = 0; i < n; i++) {
            // Case 1: Palindromes with odd length (e.g., "aba", "racecar")
            // 'i' is the center character. Expand from s[i] itself.
            expand(s, i, i, start, maxLen);      

            // Case 2: Palindromes with even length (e.g., "abba", "noon")
            // 'i' and 'i+1' are the two center characters. Expand from s[i] and s[i+1].
            // We need to ensure i+1 is within bounds before calling expand.
            // The loop condition 'i < n' ensures i+1 won't go out of bounds for the last iteration.
            expand(s, i, i + 1, start, maxLen);  
        }

        // After checking all possible centers, extract the longest palindromic substring
        // using the stored 'start' index and 'maxLen'.
        return s.substr(start, maxLen);
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N^2) | We iterate through `N` possible center points. For each center, the `expand` function can, in the worst case (e.g., a string like "aaaaa"), traverse up to `N/2` characters in each direction. This results in `N` centers * `O(N)` expansion = `O(N^2)`. |
| **Space** | O(1) | The solution uses a constant amount of extra space for variables like `start`, `maxLen`, `left`, `right`, and `currLen`. No auxiliary data structures are created that scale with the input string's size. |

## 🔗 Related Problems
- 647. Palindromic Substrings
- 131. Palindrome Partitioning
- 516. Longest Palindromic Subsequence