# 0003-longest-substring-without-repeating-characters

## 📋 Problem Description
Given a string `s`, the task is to find the length of the **longest substring** within `s` that does not contain any duplicate characters. A substring is a contiguous sequence of characters within a string.

The function `lengthOfLongestSubstring` receives a string `s` as input and must return an integer representing the length of this longest substring.

## 🔍 Examples
```
Input:  s = "abcabcbb"
Output: 3
Explanation: The longest substring without repeating characters is "abc", with a length of 3. Other valid answers include "bca" and "cab".
```

```
Input:  s = "bbbbb"
Output: 1
Explanation: The longest substring without repeating characters is "b", with a length of 1.
```

```
Input:  s = "pwwkew"
Output: 3
Explanation: The longest substring without repeating characters is "wke", with a length of 3. Note that "pwke" is a subsequence, not a substring, because 'p' and 'w' are not contiguous in "wke".
```

## 📌 Constraints
*   `0 <= s.length <= 5 * 10^4`
*   `s` consists of English letters, digits, symbols, and spaces.

## 🤔 Understanding the Problem
The problem asks us to find the maximum length of a contiguous segment of characters in the given string `s` such that all characters within that segment are unique. This means we're looking for a "window" within the string where no character appears more than once, and we want the largest such window. Edge cases include an empty string (length 0), a string with all identical characters (length 1), or a string with all unique characters (length `s.length()`). The key challenge is efficiently checking for duplicates and expanding/shrinking the window.

## 💡 Core Idea
The core idea is to use a "sliding window" approach. We maintain a window `[left, right]` that represents the current substring being examined. We expand this window by moving the `right` pointer. If we encounter a duplicate character within the window, we shrink the window from the `left` until the duplicate is removed, ensuring the window always contains only unique characters.

## 🧠 Approach — Sliding Window
This problem is a classic application of the **Sliding Window** pattern. This pattern is ideal for problems that involve finding the longest/shortest subarray, substring, or a range that satisfies a certain condition.

The Sliding Window pattern fits this problem perfectly because:
1.  We are looking for a "longest substring" (a contiguous range).
2.  The condition ("without duplicate characters") can be efficiently checked and maintained as the window slides.
3.  As we expand the window, we can quickly determine if the condition is violated. If it is, we can shrink the window from the other end until the condition is met again, avoiding redundant checks on already processed characters. This makes the solution highly efficient.

## 📝 Step-by-Step Algorithm

1.  **Initialization**:
    *   Initialize `left` (the left pointer of the window) to `0`.
    *   Initialize `max_length` (to store the maximum length found so far) to `0`. If the string is empty, `max_length` should remain `0`. A common practice is to initialize it to `INT_MIN` and then check for `INT_MIN` at the end to return `0` for an empty string, or simply `0` if we handle the empty string case upfront.
    *   Create an `unordered_set<char>` named `char_set`. This set will store all unique characters currently present within our sliding window `[left, right]`. `unordered_set` provides average O(1) time complexity for insertion, deletion, and lookup.

2.  **Iterate with `right` pointer**:
    *   Loop with a `right` pointer from `0` to `s.length() - 1`. The `right` pointer expands the window.

3.  **Handle Duplicates (Shrink Window)**:
    *   Inside the loop, before adding `s[right]` to `char_set`, check if `s[right]` is already present in `char_set`.
    *   If `s[right]` *is* in `char_set` (meaning we've found a duplicate within the current window `[left, right-1]`):
        *   Enter a `while` loop:
            *   Remove the character at `s[left]` from `char_set`.
            *   Increment `left` by `1`.
            *   Continue this `while` loop until `s[right]` is no longer in `char_set`. This effectively shrinks the window from the left until the duplicate character at `s[right]` is no longer part of the window.

4.  **Add Current Character and Update Max Length**:
    *   Once the `while` loop finishes (or if `s[right]` was not a duplicate to begin with), `s[right]` is now unique within the current window `[left, right-1]`.
    *   Add `s[right]` to `char_set`.
    *   Calculate the current length of the window: `current_length = right - left + 1`.
    *   Update `max_length = max(max_length, current_length)`.

5.  **Return Result**:
    *   After the `for` loop finishes iterating through all characters, `max_length` will hold the length of the longest substring without repeating characters.
    *   Return `max_length`. If the string `s` was empty, `max_length` would have been initialized to `0` and correctly returned. If initialized to `INT_MIN`, return `0` if `max_length` is still `INT_MIN`, otherwise `max_length`.

## 💻 Solution
```cpp
#include <string>
#include <unordered_set>
#include <algorithm> // For std::max
#include <limits>    // For INT_MIN

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // Initialize the left pointer of the sliding window.
        int left = 0;
        
        // Initialize the maximum length found so far.
        // Using INT_MIN handles the edge case of an empty string correctly
        // when combined with the final ternary check.
        int ans = std::numeric_limits<int>::min(); 
        
        // An unordered_set to store characters currently within the sliding window [left, right].
        // This allows for O(1) average time complexity for insertion, deletion, and lookup.
        std::unordered_set<char> st;
        
        // Iterate with the right pointer to expand the window.
        for (int right = 0; right < s.length(); right++) {
            // If the character at s[right] is already in our set, it means we have a duplicate
            // within the current window [left, right-1].
            while (st.count(s[right])) {
                // To resolve the duplicate, we shrink the window from the left.
                // Remove the character at s[left] from the set.
                st.erase(s[left]);
                // Move the left pointer one step to the right.
                left++;
            }
            
            // Now that s[right] is guaranteed to be unique within the window [left, right],
            // add it to our set.
            st.insert(s[right]);
            
            // Calculate the current length of the window (right - left + 1)
            // and update the maximum length found so far.
            ans = std::max(ans, right - left + 1);
        }
        
        // If the string was empty, 'ans' would still be INT_MIN. In this case, the length is 0.
        // Otherwise, return the calculated maximum length.
        return ans == std::numeric_limits<int>::min() ? 0 : ans;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Both `left` and `right` pointers traverse the string `s` at most once. Each character is inserted into and removed from the `unordered_set` at most once. `unordered_set` operations (insert, erase, count) take O(1) time on average. |
| **Space** | O(min(N, M)) | The `unordered_set` stores characters from the current window. In the worst case, it stores all unique characters in the string. `M` is the size of the character set (e.g., 128 for ASCII, 256 for extended ASCII). The space used will be at most `N` (if all characters are unique) or `M` (if `N > M`), whichever is smaller. |

## 🔗 Related Problems
- 424. Longest Repeating Character Replacement
- 567. Permutation in String
- 76. Minimum Window Substring