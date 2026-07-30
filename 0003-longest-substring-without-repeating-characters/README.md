# 0003-longest-substring-without-repeating-characters

## 📋 Problem Description
Given a string `s`, the task is to find the length of the longest substring within `s` that does not contain any repeating characters. A substring is a contiguous sequence of characters within a string.

The function `lengthOfLongestSubstring` receives a string `s` as input and must return an integer representing the length of this longest substring.

## 🔍 Examples
```
Input: s = "abcabcbb"
Output: 3
Explanation: The longest substring without repeating characters is "abc", with a length of 3. Other valid substrings like "bca" and "cab" also have length 3.

Input: s = "bbbbb"
Output: 1
Explanation: The longest substring without repeating characters is "b", with a length of 1.

Input: s = "pwwkew"
Output: 3
Explanation: The longest substring without repeating characters is "wke", with a length of 3. Note that "pwke" is a subsequence, not a substring, as 'p' and 'w' are not contiguous in "wke".
```

## 📌 Constraints
*   `0 <= s.length <= 10^5`
*   `s` consists of English letters, digits, symbols, and spaces.

## 🤔 Understanding the Problem
The problem asks us to identify the longest possible sequence of characters that are all unique, with the crucial condition that this sequence must be a *substring* (meaning its characters must appear consecutively in the original string). This is non-trivial because a naive approach of checking every possible substring for uniqueness would be too slow for longer strings. We need an efficient way to expand and contract our search for unique character sequences. Edge cases include an empty string, a string with all identical characters, or a string with all unique characters.

## 💡 Core Idea
The core idea is to use a "sliding window" approach. We maintain a window of characters that are currently unique. We expand this window by moving its right boundary. If we encounter a character that is already inside our window, it means our current window is no longer valid. To fix this, we shrink the window from its left boundary until the duplicate character is removed, ensuring all characters within the window are unique again.

## 🧠 Approach — Sliding Window
This problem is a classic application of the **Sliding Window** pattern. This pattern is ideal for problems that involve finding the longest or shortest subarray/substring that satisfies a certain condition. Here, the condition is "no repeating characters".

We use two pointers, `left` and `right`, to define the boundaries of our current window `[left, right]`. An `unordered_set` (hash set) is used to efficiently keep track of characters currently within this window. This allows for O(1) average time complexity for checking if a character exists, adding a character, or removing a character. The `right` pointer expands the window, adding new characters. If a duplicate is found, the `left` pointer contracts the window, removing characters until the duplicate is resolved. This ensures that at any point, the characters within `[left, right]` are unique.

## 📝 Step-by-Step Algorithm
1.  Initialize two pointers, `left` to 0 (start of the window) and `right` to 0 (end of the window).
2.  Initialize `max_length` to 0, which will store the length of the longest substring found so far.
3.  Create an empty `unordered_set` (or hash set) called `char_set` to store the characters currently within our sliding window `[left, right]`.
4.  Iterate with the `right` pointer from the beginning of the string to its end:
    a.  For each character `s[right]`:
        i.  **Check for duplicates**: While the `char_set` already contains `s[right]` (meaning we've found a duplicate within our current window):
            *   Remove the character at `s[left]` from `char_set`.
            *   Increment the `left` pointer by one, effectively shrinking the window from the left.
        ii. **Add current character**: Once `s[right]` is guaranteed to be unique within the current window (after potentially shrinking the window), add `s[right]` to `char_set`.
        iii. **Update maximum length**: Calculate the current window's length (`right - left + 1`). Update `max_length` if this current length is greater than the previously recorded `max_length`.
5.  After the `right` pointer has traversed the entire string, `max_length` will hold the length of the longest substring without repeating characters. Return `max_length`.

## 💻 Solution
```cpp
#include <string>
#include <unordered_set>
#include <algorithm> // Required for std::max
#include <limits>    // Required for INT_MIN

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // 'left' pointer marks the start of the current window.
        int left = 0;
        
        // 'ans' stores the maximum length found so far.
        // Initialized to INT_MIN to handle the edge case of an empty string correctly,
        // where the result should be 0.
        int ans = std::numeric_limits<int>::min(); 
        
        // 'st' (unordered_set) stores characters currently within the sliding window [left, right].
        // It allows for O(1) average time complexity for insertion, deletion, and lookup.
        std::unordered_set<char> st;
        
        // 'right' pointer expands the window to the right.
        for (int right = 0; right < s.length(); right++) {
            // If the character at s[right] is already in our set, it means we have a duplicate.
            // We need to shrink the window from the 'left' until the duplicate is removed.
            while (st.count(s[right])) {
                // Remove the character at the 'left' pointer from the set.
                st.erase(s[left]);
                // Move the 'left' pointer one step to the right.
                left++;
            }
            
            // Now that s[right] is guaranteed to be unique within the current window [left, right],
            // add it to the set.
            st.insert(s[right]);
            
            // Calculate the current window's length (right - left + 1)
            // and update 'ans' if it's greater than the current maximum.
            ans = std::max(ans, right - left + 1);
        }
        
        // If the string was empty, 'ans' would still be INT_MIN. In this case, return 0.
        // Otherwise, return the calculated maximum length.
        return ans == std::numeric_limits<int>::min() ? 0 : ans;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Both the `left` and `right` pointers traverse the string at most once. Each character is inserted into and removed from the `unordered_set` at most once. `unordered_set` operations (insert, count, erase) take O(1) time on average. |
| **Space** | O(min(N, A)) | In the worst case, the `unordered_set` stores all unique characters in the string. `N` is the length of the string, and `A` is the size of the character set (e.g., 128 for ASCII, 256 for extended ASCII). The maximum number of characters stored in the set will be the smaller of `N` and `A`. |

## 🔗 Related Problems
*   76. Minimum Window Substring
*   424. Longest Repeating Character Replacement
*   904. Fruit Into Baskets