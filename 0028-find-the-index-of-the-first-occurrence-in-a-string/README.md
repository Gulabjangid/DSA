# 0028-find-the-index-of-the-first-occurrence-in-a-string

## 📋 Problem Description
Given two strings, `haystack` and `needle`, the task is to find the index of the first occurrence of `needle` within `haystack`. If `needle` is not found anywhere in `haystack`, the function should return `-1`.

The function `strStr` receives two string arguments:
- `haystack`: The string to search within.
- `needle`: The string to search for.

It must return an integer representing the starting index of the first occurrence of `needle` in `haystack`, or `-1` if `needle` is not present.

## 🔍 Examples
```
Input:  haystack = "sadbutsad", needle = "sad"
Output: 0
Explanation: "sad" occurs at index 0 and 6. The first occurrence is at index 0, so we return 0.
```

```
Input:  haystack = "leetcode", needle = "leeto"
Output: -1
Explanation: "leeto" did not occur in "leetcode", so we return -1.
```

```
Input:  haystack = "aaaaa", needle = "bba"
Output: -1
Explanation: "bba" is not found in "aaaaa".
```

## 📌 Constraints
*   `1 <= haystack.length, needle.length <= 10^4`
*   `haystack` and `needle` consist of only lowercase English characters.

## 🤔 Understanding the Problem
The problem asks us to implement a basic string search function, similar to `indexOf` or `find` in many programming languages. We need to locate the very first position where the entire `needle` string appears consecutively as a substring within the `haystack` string. A key aspect is handling cases where the `needle` is not found, in which case `-1` should be returned. The constraints indicate that both strings will have at least one character and consist of lowercase English letters.

## 💡 Core Idea
The most straightforward approach is to iterate through every possible starting position in the `haystack` where the `needle` could potentially begin. For each position, we check if the substring of `haystack` starting at that position and having the same length as `needle` exactly matches `needle`.

## 🧠 Approach — Brute Force / Naive String Matching
This problem can be solved using a **Brute Force** or **Naive String Matching** approach. This pattern involves systematically checking all possible valid starting positions for the `needle` within the `haystack`. It's called "brute force" because it doesn't employ any advanced optimizations to skip comparisons; it simply tries every single possibility until a match is found or all possibilities are exhausted. This approach is suitable here because the problem constraints allow for a solution with polynomial time complexity, and the simplicity of the brute-force method makes it easy to implement and understand.

## 📝 Step-by-Step Algorithm
1.  **Get Lengths**: Determine the length of `needle` (let's call it `n`) and the length of `haystack` (let's call it `m`).
2.  **Iterate Through Haystack**: Start a loop that iterates through possible starting indices `i` for the `needle` in the `haystack`.
    *   The loop should start from `i = 0`.
    *   The loop should continue as long as `i` allows for the entire `needle` to fit within the remaining part of `haystack`. This means `i` can go up to `m - n`. For example, if `haystack` is "abcde" (length 5) and `needle` is "cde" (length 3), the last possible starting index `i` is `5 - 3 = 2`.
3.  **Extract Substring and Compare**: Inside the loop, for each starting index `i`:
    *   Extract a substring from `haystack` that starts at index `i` and has a length of `n` (the length of `needle`).
    *   Compare this extracted substring with the `needle`.
4.  **Found Match**: If the extracted substring is exactly equal to `needle`, then we have found the first occurrence. Return the current index `i`.
5.  **No Match**: If the loop completes without finding any match (i.e., no `return i` statement was executed), it means `needle` is not present in `haystack`. In this case, return `-1`.

## 💻 Solution
```cpp
class Solution {
public:
    int strStr(string haystack, string needle) {
        // Get the length of the needle string.
        // This will be used to determine the size of the substring to compare.
        int n = needle.size();
        
        // Get the length of the haystack string.
        // This helps in defining the bounds for our search.
        int m = haystack.size();
        
        // Iterate through all possible starting positions for the needle in the haystack.
        // The loop runs from index 0 up to (m - n).
        // For example, if haystack="abcde" (m=5) and needle="cde" (n=3),
        // the last possible starting index for needle is 5-3=2.
        // If i=0, we check "abc". If i=1, we check "bcd". If i=2, we check "cde".
        // If n > m, then m - n will be negative, and the loop condition (i <= m - n)
        // will immediately be false, correctly skipping the loop and returning -1.
        for (int i = 0; i <= m - n; i++) {
            // Extract a substring from haystack starting at the current index 'i'.
            // The length of this substring is 'n' (the length of the needle).
            // For example, if haystack="sadbutsad", i=0, n=3, then haystack.substr(0, 3) is "sad".
            // If this extracted substring is exactly equal to the needle,
            // we have found the first occurrence.
            if (haystack.substr(i, n) == needle) {
                // Return the current starting index 'i' where the match was found.
                return i;
            }
        }
        
        // If the loop finishes without finding any match, it means the needle
        // is not present anywhere in the haystack.
        return -1;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(m * n) | The outer loop runs `(m - n + 1)` times. In each iteration, `haystack.substr(i, n)` takes O(n) time to create a substring, and comparing it with `needle` takes another O(n) time. In the worst case, this leads to `(m - n + 1) * O(n)` operations, which simplifies to O(m * n). |
| **Space** | O(n) | In each iteration, `haystack.substr(i, n)` creates a temporary string of length `n` to perform the comparison. This temporary string consumes O(n) space. |

## 🔗 Related Problems
- 3. Longest Substring Without Repeating Characters
- 76. Minimum Window Substring
- 686. Repeated String Match