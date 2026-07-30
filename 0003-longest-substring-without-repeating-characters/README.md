# 0003-longest-substring-without-repeating-characters

## 📋 Problem Description
Given a string `s`, the task is to find the length of the **longest substring** within `s` that does not contain any duplicate characters. A substring is a contiguous sequence of characters within a string.

**Input:** A string `s`.
**Output:** An integer representing the length of the longest substring without duplicate characters.

## 🔍 Examples
```
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3. Note that "bca" and "cab" are also correct answers.
```

```
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
```

```
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3. Notice that the answer must be a substring; "pwke" is a subsequence and not a substring.
```

## 📌 Constraints
*   `0 <= s.length <= 10^5`
*   `s` consists of English letters, digits, symbols and spaces.

## 🤔 Understanding the Problem
The problem asks us to identify the longest possible contiguous segment of characters (a substring) within a given string `s` such that every character within that segment is unique. This means no character can appear more than once in the chosen substring. We need to return the length of this longest unique-character substring. The challenge lies in efficiently checking for duplicates and dynamically adjusting the substring boundaries to find the maximum length without resorting to brute-force checks of all possible substrings, which would be too slow.

## 💡 Core Idea
The core idea is to use a "sliding window" approach. We maintain a window of characters that are currently unique. As we expand this window by adding a new character from the right, if we encounter a character that is already present in our window, we must shrink the window from the left until the duplicate character is removed, ensuring the window always contains only unique characters.

## 🧠 Approach — Sliding Window
This problem is a classic example of the "Sliding Window" pattern. This pattern is highly effective for problems that involve finding the longest/shortest subarray, substring, or a contiguous segment that satisfies a specific condition. Here, the condition is "no repeating characters." We use two pointers, `left` and `right`, to define the current window. A hash set (specifically, `unordered_set` in C++) is employed to efficiently keep track of characters within the current window and to perform O(1) average-time checks for duplicates.

## 📝 Step-by-Step Algorithm
1.  Initialize two pointers, `left` to `0` (marking the start of the current window) and `right` to `0` (marking the end of the current window).
2.  Initialize an integer variable `ans` to `INT_MIN` (or `0`) to store the maximum length of a substring found so far.
3.  Create an empty `unordered_set<char>` named `st`. This set will store all unique characters currently present within our sliding window `[left, right-1]`.
4.  Iterate with the `right` pointer from `0` up to `s.length() - 1`:
    a.  For each character `s[right]`:
        i.  **Check for Duplicates**: While the character `s[right]` is already present in the `st` set (indicating a duplicate within the current window):
            *   Remove the character at `s[left]` from the `st` set.
            *   Increment the `left` pointer by one, effectively shrinking the window from its left side.
        ii. **Expand Window**: Once `s[right]` is no longer a duplicate (either it wasn't a duplicate initially, or we've shrunk the window enough to remove the previous instance of `s[right]`), add `s[right]` to the `st` set.
        iii. **Update Maximum Length**: Calculate the length of the current valid window: `right - left + 1`. Update `ans` to be the maximum of its current value and this new window length.
5.  After the `right` pointer has traversed the entire string, `ans` will hold the length of the longest substring without repeating characters.
6.  Finally, return `ans`. If the input string `s` was empty, `ans` would still be `INT_MIN` (if initialized that way), so return `0` in that specific case; otherwise, return `ans`.

## 💻 Solution
```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int left = 0; // 'left' pointer marks the start of the current window
        
        // 'ans' stores the maximum length found so far.
        // Initialized to INT_MIN to correctly handle the case of an empty string.
        // If s is empty, the loop won't run, ans remains INT_MIN, and the final
        // ternary operator will correctly return 0.
        int ans = INT_MIN; 
        
        // An unordered_set is used to keep track of characters within the current window.
        // It provides O(1) average time complexity for insertion, deletion, and lookup,
        // which is crucial for efficiency.
        unordered_set<char> st; 

        // 'right' pointer iterates through the string, expanding the window to the right
        for (int right = 0; right < s.length(); right++) {
            // If the character at 's[right]' is already in our set, it means we have a duplicate
            // within the current window [left, right-1].
            // We need to shrink the window from the 'left' until the duplicate is removed.
            while (st.count(s[right])) {
                // Remove the character at 's[left]' from the set
                st.erase(s[left]);
                // Move the 'left' pointer one step to the right, shrinking the window
                left++;
            }
            
            // Once 's[right]' is no longer a duplicate (either it wasn't a duplicate
            // initially, or we've shrunk the window enough), add it to the set.
            st.insert(s[right]);
            
            // Calculate the current window's length (right - left + 1)
            // and update 'ans' if this length is greater than the current maximum.
            ans = max(ans, right - left + 1);
        }
        
        // After iterating through the entire string, 'ans' holds the maximum length.
        // If the string 's' was empty, 'ans' would still be INT_MIN. In this case,
        // the problem expects 0, so we use a ternary operator to handle this edge case.
        return ans == INT_MIN ? 0 : ans;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Both the `left` and `right` pointers traverse the string `s` at most once. Each character is inserted into and removed from the `unordered_set` at most once. `unordered_set` operations (insert, erase, count) take O(1) time on average. |
| **Space** | O(min(N, A)) | In the worst case, the `unordered_set` stores all unique characters within the current window. `A` represents the size of the character set (e.g., 256 for ASCII characters, or 26 for lowercase English letters). The space used is bounded by either the number of unique characters in `s` or the total number of possible characters. |

## 🔗 Related Problems
- 76. Minimum Window Substring
- 424. Longest Repeating Character Replacement
- 1004. Max Consecutive Ones III