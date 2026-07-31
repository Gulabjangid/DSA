# 0005-longest-palindromic-substring

## 📋 Problem Description
Given a string `s`, the task is to find and return the longest substring within `s` that is a palindrome. A palindrome is a string that reads the same forwards and backwards (e.g., "racecar", "madam"). A substring is a contiguous sequence of characters within a string.

The function `longestPalindrome` receives a single string `s` as input and must return a string representing the longest palindromic substring found in `s`. If there are multiple palindromic substrings of the same maximum length, any one of them is considered a valid answer.

## 🔍 Examples
```
Input:  s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer, as it has the same length.

Input:  s = "cbbd"
Output: "bb"

Input:  s = "a"
Output: "a"
Explanation: A single character string is a palindrome.

Input:  s = "ac"
Output: "a"
Explanation: "a" and "c" are palindromes of length 1.
```

## 📌 Constraints
*   `1 <= s.length <= 1000`
*   `s` consists of only digits and English letters.

## 🤔 Understanding the Problem
The problem asks us to identify the longest sequence of characters within a given string that reads the same forwards and backwards. This is non-trivial because a string can have many substrings, and we need to check each one for the palindrome property and keep track of the longest one found. Edge cases include very short strings (length 1 or 2) and strings where the entire string is a palindrome.

## 💡 Core Idea
The core idea is that every palindrome has a "center". A palindrome can either have an odd length (with a single character center, like "aba") or an even length (with two identical characters as its center, like "abba"). We can iterate through every possible center and expand outwards to find the longest palindrome centered there.

## 🧠 Approach — Expand Around Center
This problem is efficiently solved using the **Expand Around Center** approach. This pattern is suitable because palindromes inherently possess a symmetrical structure around a central point (or two points for even length). Instead of generating all substrings and checking each for palindromicity (which would be very inefficient), we leverage this symmetry. We iterate through each character in the string, treating it first as the center of a potential odd-length palindrome, and then as the left character of a potential two-character center for an even-length palindrome. From these centers, we expand outwards, comparing characters, until the palindrome property breaks or we reach the string boundaries.

## 📝 Step-by-Step Algorithm

1.  **Initialization**:
    *   Initialize `start` to `0` and `maxLen` to `1`. These variables will store the starting index and length of the longest palindrome found so far.
    *   Handle base cases: If the string `s` has length 0 or 1, it is already a palindrome, so return `s`.

2.  **Iterate Through Possible Centers**:
    *   Loop through each character of the string `s` using an index `i` from `0` to `n-1` (where `n` is the length of `s`). Each `i` will serve as a potential center for a palindrome.

3.  **Expand for Odd Length Palindromes**:
    *   For each `i`, consider it as the center of an odd-length palindrome. Set `left = i` and `right = i`.
    *   Call a helper function (e.g., `expand`) to expand outwards from this center.

4.  **Expand for Even Length Palindromes**:
    *   For each `i`, consider it as the left character of a two-character center for an even-length palindrome. Set `left = i` and `right = i + 1`.
    *   Call the same helper function (`expand`) to expand outwards from this center.

5.  **Helper Function `expand(string &s, int left, int right, int &start, int &maxLen)`**:
    *   This function takes the string `s`, current `left` and `right` pointers, and references to `start` and `maxLen` (to update them globally).
    *   While `left` is within string bounds (`left >= 0`), `right` is within string bounds (`right < n`), and `s[left]` equals `s[right]`:
        *   Calculate the current palindrome's length: `currLen = right - left + 1`.
        *   If `currLen` is greater than `maxLen`:
            *   Update `maxLen` to `currLen`.
            *   Update `start` to `left`.
        *   Decrement `left` and increment `right` to continue expanding outwards.

6.  **Return Result**:
    *   After iterating through all possible centers, `start` and `maxLen` will hold the details of the longest palindromic substring.
    *   Return the substring of `s` starting at `start` with length `maxLen` using `s.substr(start, maxLen)`.

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
            int currLen = right - left + 1; // Calculate current palindrome length

            // If the current palindrome is longer than the maximum found so far
            if (currLen > maxLen) {
                maxLen = currLen; // Update maxLen
                start = left;     // Update the starting index of the longest palindrome
            }

            left--;  // Move left pointer inwards
            right++; // Move right pointer outwards
        }
    }

    string longestPalindrome(string s) {
        int n = s.size(); // Get the length of the input string

        // Base case: If string has 0 or 1 character, it's already a palindrome
        if (n <= 1)
            return s;

        int start = 0;    // Stores the starting index of the longest palindrome
        int maxLen = 1;   // Stores the maximum length of the longest palindrome
                          // Initialized to 1 because a single character is always a palindrome

        // Iterate through each character of the string
        for (int i = 0; i < n; i++) {
            // Case 1: Odd length palindromes
            // Treat 'i' as the single center character (e.g., "a" in "bab")
            expand(s, i, i, start, maxLen);

            // Case 2: Even length palindromes
            // Treat 'i' and 'i+1' as the two center characters (e.g., "bb" in "cbbd")
            // Only proceed if i+1 is within bounds
            expand(s, i, i + 1, start, maxLen);
        }

        // After checking all possible centers, 'start' and 'maxLen'
        // will hold the details of the longest palindromic substring.
        // Use substr(start_index, length) to extract it.
        return s.substr(start, maxLen);
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N^2) | The algorithm iterates through each character of the string (N iterations). For each character, it calls the `expand` function twice. In the worst case (e.g., "aaaaa" or "abccba"), the `expand` function might traverse almost the entire string (N/2 comparisons). Thus, the total time complexity is N * O(N) = O(N^2). |
| **Space** | O(1) | The algorithm uses a few constant extra variables (`start`, `maxLen`, `left`, `right`, `n`) regardless of the input string's size. No additional data structures are allocated that scale with N. |

## 🔗 Related Problems
- 647. Palindromic Substrings
- 9. Palindrome Number
- 132. Palindrome Partitioning II