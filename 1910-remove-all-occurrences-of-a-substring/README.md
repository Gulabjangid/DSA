# 1910-remove-all-occurrences-of-a-substring

## 📋 Problem Description
You are given two strings, `s` and `part`. Your task is to repeatedly perform an operation on `s` until all occurrences of the substring `part` have been removed. The operation is as follows:
1. Find the **leftmost** occurrence of `part` within `s`.
2. Remove this occurrence of `part` from `s`.

You must return the final string `s` after all occurrences of `part` have been removed.

A substring is defined as a contiguous sequence of characters within a string.

**Input:**
*   `s`: The main string from which occurrences of `part` are to be removed.
*   `part`: The substring to be removed.

**Output:**
*   A string, which is `s` after all specified operations have been completed.

## 🔍 Examples
```
Input: s = "daabcbaabcbc", part = "abc"
Output: "dab"
Explanation: The following operations are done:
- s = "da_abc_baabcbc", remove "abc" starting at index 2, so s becomes "dabaabcbc".
- s = "daba_abc_bc", remove "abc" starting at index 4, so s becomes "dababc".
- s = "dab_abc_", remove "abc" starting at index 3, so s becomes "dab".
Now s has no occurrences of "abc".
```

```
Input: s = "axxxxyyyyb", part = "xy"
Output: "ab"
Explanation: The following operations are done:
- s = "axxx_xy_yyyb", remove "xy" starting at index 4, so s becomes "axxxyyyb".
- s = "axx_xy_yyb", remove "xy" starting at index 3, so s becomes "axxyyb".
- s = "ax_xy_yb", remove "xy" starting at index 2, so s becomes "axyb".
- s = "a_xy_b", remove "xy" starting at index 1, so s becomes "ab".
Now s has no occurrences of "xy".
```

## 📌 Constraints
*   `1 <= s.length <= 1000`
*   `1 <= part.length <= 1000`
*   `s` and `part` consist of lowercase English letters.

## 🤔 Understanding the Problem
The problem asks us to repeatedly find and remove the *leftmost* occurrence of a given `part` substring from a main string `s`. This process continues until `part` can no longer be found in `s`. The key challenge is that removing a substring can potentially create new occurrences of `part` that weren't there before, or shift existing ones. For example, if `s = "ababa"` and `part = "aba"`, removing the first "aba" leaves "ba". If `s = "abccba"` and `part = "bc"`, removing "bc" leaves "acba". The "leftmost" rule is crucial for deterministic behavior.

## 💡 Core Idea
The most straightforward approach is to directly simulate the process described: repeatedly search for the `part` substring and remove it. The problem statement explicitly defines the operation, and we can use built-in string functions to perform these steps efficiently.

## 🧠 Approach — Simulation / Direct String Manipulation
This problem can be solved using a **Simulation** approach, which directly mimics the operations described in the problem statement. We repeatedly perform the "find leftmost occurrence and remove it" step until no more occurrences are found. This pattern fits because the problem's rules are simple and can be directly translated into common string manipulation functions. There's no complex state to manage or optimization required beyond the basic operations.

## 📝 Step-by-Step Algorithm
1.  Get the length of the `part` string, let's call it `part_len`. This will be useful for the removal step.
2.  Start a loop that continues indefinitely (or until a condition is met to break it).
3.  Inside the loop, search for the first (leftmost) occurrence of `part` within the current `s` string.
    *   If `part` is found, get its starting index.
    *   If `part` is *not* found, it means all occurrences have been removed. Exit the loop.
4.  If `part` was found at a certain index, remove `part_len` characters from `s` starting at that index. This modifies `s` in place.
5.  After removing `part`, the loop restarts, and the process repeats with the modified `s`.
6.  Once the loop terminates (because `part` is no longer found), return the final `s`.

## 💻 Solution
```cpp
class Solution {
public:
    string removeOccurrences(string s, string part) {
        // Get the length of the 'part' string. This will be used
        // when erasing 'part' from 's'.
        int part_len = part.size();

        // The loop continues as long as 'part' can be found in 's'.
        // string::npos is a special value indicating that the substring was not found.
        while (s.find(part) != string::npos) {
            // Find the starting index of the leftmost occurrence of 'part' in 's'.
            // string::find returns the index of the first character of the found substring.
            int found_pos = s.find(part);

            // Erase 'part_len' characters from 's' starting at 'found_pos'.
            // string::erase(index, count) removes 'count' characters starting at 'index'.
            s.erase(found_pos, part_len);
            
            // The loop will then re-evaluate the condition (s.find(part) != string::npos)
            // with the modified string 's'. This ensures that if removing 'part' creates
            // a new leftmost 'part' (e.g., "ababa", remove "aba" -> "ba"), it will be
            // found and removed in the next iteration.
        }

        // Once the loop finishes, it means no more occurrences of 'part' are found in 's'.
        // Return the final modified string 's'.
        return s;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N^2) | Let `N` be the initial length of `s` and `M` be the length of `part`. <br> The `while` loop runs `k` times, where `k` is the total number of `part` occurrences removed. In the worst case, `k` can be `O(N)` (e.g., `s = "aaaaa"`, `part = "a"`). <br> Inside the loop: `s.find(part)` takes `O(L_s * M)` in the worst case (where `L_s` is the current length of `s`). `s.erase(pos, M)` takes `O(L_s)` time as characters need to be shifted. <br> Summing these costs over `k` iterations, where `L_s` can be up to `N`, results in a total time complexity of `O(k * (N * M + N))`. <br> Given `k` can be `O(N/M)` (e.g., `s = "abcabc..."`, `part = "abc"`) or `O(N)` (e.g., `s = "aaaaa"`, `part = "a"`), the dominant term becomes `O(N^2)`. For `N=1000`, `N^2 = 10^6`, which is acceptable. |
| **Space** | O(N) | The solution modifies the input string `s` in place. No additional data structures are created that scale significantly with the input size beyond the string `s` itself, which occupies `O(N)` space. |

## 🔗 Related Problems
*   [1047. Remove All Adjacent Duplicates In String](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string)
*   [1209. Remove All Adjacent Duplicates in String II](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii)
*   [686. Repeated String Match](https://leetcode.com/problems/repeated-string-match)