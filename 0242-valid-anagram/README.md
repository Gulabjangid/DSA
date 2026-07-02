# 0242-valid-anagram

## 📋 Problem Description
Given two strings, `s` and `t`, determine if `t` is an anagram of `s`.
An anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.
The function should return `true` if `t` is an anagram of `s`, and `false` otherwise.

## 🔍 Examples
```
Input:  s = "anagram", t = "nagaram"
Output: true
Explanation: "nagaram" is formed by rearranging the letters of "anagram".

Input:  s = "rat", t = "car"
Output: false
Explanation: The letters in "rat" and "car" are different.

Input:  s = "listen", t = "silent"
Output: true
Explanation: "silent" is a rearrangement of "listen".
```

## 📌 Constraints
*   `1 <= s.length, t.length <= 5 * 10^4`
*   `s` and `t` consist of lowercase English letters.

## 🤔 Understanding the Problem
The problem asks us to check if two given strings are anagrams of each other. This means they must contain the exact same characters with the exact same frequencies, just possibly in a different order. A crucial observation is that if the lengths of the strings differ, they cannot be anagrams. Since the strings only contain lowercase English letters, we can leverage this limited character set for an efficient solution.

## 💡 Core Idea
The fundamental idea is that two strings are anagrams if and only if they have the same character counts for every character. We can count the occurrences of each character in one string and then verify if the second string matches those counts.

## 🧠 Approach — Frequency Counting / Array as Frequency Map
This pattern is ideal because the problem boils down to comparing the *composition* of two strings rather than their exact order. By counting character frequencies, we abstract away the order and focus solely on whether the same set of characters (with the same multiplicities) exists in both strings. An array can serve as an extremely efficient frequency map for a small, fixed character set like lowercase English letters (26 characters).

## 📝 Step-by-Step Algorithm
1.  **Initial Length Check**: First, compare the lengths of string `s` and string `t`. If they are not equal, return `false` immediately, because anagrams must always have the same number of characters.
2.  **Initialize Frequency Array**: Create an integer array (or vector in C++) of size 26, initialized with all zeros. This array will store the frequency of each lowercase English letter ('a' through 'z'). `count[0]` will correspond to 'a', `count[1]` to 'b', and so on, up to `count[25]` for 'z'.
3.  **Count Characters in `s`**: Iterate through each character `c` in the first string `s`. For each character, increment its corresponding count in the frequency array. For example, if `c` is 'a', `count[0]` is incremented; if `c` is 'b', `count[1]` is incremented, using `c - 'a'` as the index.
4.  **Decrement and Verify Characters in `t`**: Iterate through each character `c` in the second string `t`. For each character:
    *   Decrement its corresponding count in the frequency array.
    *   Immediately check if the count for `c` has become negative. If `count[c - 'a'] < 0`, it means `t` contains more occurrences of character `c` than `s` did. In this scenario, `t` cannot be an anagram of `s`, so return `false`.
5.  **Final Check**: If the loop for `t` completes without any count becoming negative, it implies that `t` used up characters that were present in `s` and didn't introduce any extra characters. Since we already confirmed that `s` and `t` have the same length, all character counts in our frequency array must now be exactly zero. Therefore, `s` and `t` are anagrams, and we can return `true`.

## 💻 Solution
```cpp
#include <string>
#include <vector>
#include <numeric> // For std::accumulate if needed, but not in this solution

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
        // Each element is initialized to 0.
        // count[0] will store frequency of 'a', count[1] for 'b', and so on.
        std::vector<int> count(26, 0);

        // First pass: Iterate through string 's' and increment counts.
        // For each character 'c' in 's', we map it to an index (0-25)
        // by subtracting the ASCII value of 'a'.
        for (char c : s) {
            count[c - 'a']++;
        }

        // Second pass: Iterate through string 't' and decrement counts.
        // For each character 'c' in 't', we decrement its corresponding count.
        for (char c : t) {
            count[c - 'a']--;

            // Immediate check: If a count becomes negative, it means 't' has
            // more of this character than 's' did. Thus, they cannot be anagrams.
            // We can return false early without processing the rest of 't'.
            if (count[c - 'a'] < 0) {
                return false;
            }
        }

        // If we reach here, it means:
        // 1. Both strings had the same length (checked initially).
        // 2. 't' did not contain any character more times than 's' did.
        // Since lengths are equal, and 't' didn't have excess characters,
        // all counts in the 'count' array must now be exactly zero.
        // This implies 's' and 't' have the exact same character frequencies.
        return true;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through string `s` once (O(N)) and string `t` once (O(N)). The length check is O(1). Overall, it's O(N + M), where N and M are lengths of `s` and `t`. Since anagrams must have equal length, this simplifies to O(N). |
| **Space** | O(1) | We use a fixed-size array of 26 integers to store character frequencies, regardless of the input string lengths. |

## 🔗 Related Problems
- 49. Group Anagrams
- 383. Ransom Note
- 2423. Remove Letter To Equalize Frequency