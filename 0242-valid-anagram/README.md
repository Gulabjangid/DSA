# 0242-valid-anagram

## 📋 Problem Description
Given two strings, `s` and `t`, determine if `t` is an anagram of `s`.

An anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once. This means that two strings are anagrams if they contain the exact same characters with the exact same frequencies.

The function should return `true` if `t` is an anagram of `s`, and `false` otherwise.

## 🔍 Examples
```
Input:  s = "anagram", t = "nagaram"
Output: true
Explanation: "nagaram" is formed by rearranging the letters of "anagram".
```

```
Input:  s = "rat", t = "car"
Output: false
Explanation: The characters are different; 'r' and 't' in "rat" are not the same as 'c' and 'a' in "car".
```

## 📌 Constraints
*   `1 <= s.length, t.length <= 5 * 10^4`
*   `s` and `t` consist of lowercase English letters.

## 🤔 Understanding the Problem
The problem asks us to verify if two given strings are anagrams of each other. The core idea of an anagram is that the two strings must contain the exact same characters, and each character must appear the same number of times in both strings. A crucial initial check is that anagrams must always have the same length. If their lengths differ, they cannot be anagrams. The constraints specify that inputs will only contain lowercase English letters, which simplifies character handling.

## 💡 Core Idea
Two strings are anagrams if and only if they have the same length and the same character counts for every character. We can efficiently track these counts using a frequency map (or an array for fixed character sets).

## 🧠 Approach — Frequency Counting (using an array as a hash map)
This problem is a classic application of the **Frequency Counting** pattern. This pattern is ideal when you need to keep track of the occurrences of elements (like characters in a string) within a given range. Since the problem states that `s` and `t` consist only of lowercase English letters, there are only 26 possible characters ('a' through 'z'). This allows us to use a fixed-size array (of size 26) as an efficient frequency map, where each index corresponds to a specific letter (e.g., index 0 for 'a', index 1 for 'b', etc.). We can iterate through the first string to build up character counts, and then iterate through the second string to "consume" those counts, checking for mismatches along the way.

## 📝 Step-by-Step Algorithm
1.  **Initial Length Check:** First, compare the lengths of string `s` and string `t`. If `s.length()` is not equal to `t.length()`, then `t` cannot be an anagram of `s`. In this case, immediately return `false`.
2.  **Initialize Frequency Counter:** Create an integer array (or vector in C++) of size 26, initialized with all zeros. This array will store the frequency of each lowercase English letter. `count[0]` will correspond to 'a', `count[1]` to 'b', and so on, up to `count[25]` for 'z'.
3.  **Process String `s`:** Iterate through each character `c` in string `s`:
    *   Increment the count for that character in the frequency array. For example, if `c` is 'a', increment `count[0]`. This can be done by `count[c - 'a']++`.
4.  **Process String `t` and Verify:** Iterate through each character `c` in string `t`:
    *   Decrement the count for that character in the frequency array. For example, if `c` is 'a', decrement `count[0]`. This can be done by `count[c - 'a']--`.
    *   After decrementing, immediately check if the count for `c` has become negative. If `count[c - 'a'] < 0`, it means string `t` contains more occurrences of character `c` than string `s` did. Therefore, `t` cannot be an anagram of `s`. In this case, immediately return `false`.
5.  **Final Result:** If the algorithm completes both loops without returning `false`, it means that all characters in `t` were successfully matched and "consumed" from the counts established by `s`, and no count ever dropped below zero. Since we already confirmed that `s` and `t` have the same length, this implies all character counts must now be exactly zero, confirming that `t` is an anagram of `s`. Return `true`.

## 💻 Solution
```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        // Critical Edge Case: If lengths are different, they cannot be anagrams.
        // Anagrams must always have the same number of characters.
        if (s.length() != t.length()) {
            return false;
        }

        // Initialize a frequency array for lowercase English letters.
        // There are 26 possible lowercase letters ('a' through 'z').
        // Each index will store the count for a specific letter:
        // count[0] for 'a', count[1] for 'b', ..., count[25] for 'z'.
        vector<int> count(26, 0);

        // First pass: Iterate through string 's' to build character frequencies.
        // For each character 'c' in 's', increment its corresponding count.
        for (char c : s) {
            // 'c - 'a'' converts a character to its 0-25 index.
            // e.g., 'a' - 'a' = 0, 'b' - 'a' = 1, etc.
            count[c - 'a']++;
        }

        // Second pass: Iterate through string 't' to check against frequencies.
        // For each character 'c' in 't', decrement its corresponding count.
        for (char c : t) {
            count[c - 'a']--;

            // If a count drops below zero, it means 't' has more of this character
            // than 's' did, or 's' didn't have this character at all.
            // In either case, they cannot be anagrams.
            if (count[c - 'a'] < 0) {
                return false;
            }
        }

        // If we reach here, it means all characters in 't' were found in 's'
        // with sufficient counts, and no count ever went negative.
        // Since we already checked for equal lengths, this implies all counts
        // must now be exactly zero, meaning 't' is an anagram of 's'.
        return true;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through string `s` once (O(N)) and string `t` once (O(N)). Since anagrams have the same length, N is the length of either string. |
| **Space** | O(1) | We use a fixed-size array of 26 integers to store character frequencies. This space is constant, regardless of the input string length. |

## 🔗 Related Problems
*   383. Ransom Note
*   49. Group Anagrams
*   76. Minimum Window Substring