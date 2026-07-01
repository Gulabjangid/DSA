# 0205-isomorphic-strings

## 📋 Problem Description
Given two strings, `s` and `t`, determine if they are isomorphic.

Two strings are considered isomorphic if the characters in `s` can be replaced to obtain `t` under the following rules:
1. All occurrences of a character in `s` must be replaced with the *same* character in `t`.
2. The order of characters must be preserved during replacement.
3. No two distinct characters in `s` may map to the same character in `t`. However, a character in `s` may map to itself in `t`.

The function should return `true` if `s` and `t` are isomorphic, and `false` otherwise.

## 🔍 Examples
```
Input:  s = "egg", t = "add"
Output: true
Explanation:
The strings s and t can be made identical by:
- Mapping 'e' to 'a'.
- Mapping 'g' to 'd'.
```
```
Input:  s = "foo", t = "bar"
Output: false
Explanation:
'f' maps to 'b', 'o' maps to 'a'. When the second 'o' is encountered, it tries to map to 'r'.
This violates the rule that 'o' must always map to the same character.
Alternatively, consider s = "f11", t = "b23". Here, '1' needs to map to '2' and '1' needs to map to '3', which is a conflict.
```
```
Input:  s = "paper", t = "title"
Output: true
Explanation:
'p' maps to 't', 'a' maps to 'i', 'e' maps to 'l', 'r' maps to 'e'. All mappings are consistent.
```

## 📌 Constraints
* `1 <= s.length <= 5 * 10^4`
* `t.length == s.length`
* `s` and `t` consist of any valid ASCII character.

## 🤔 Understanding the Problem
The problem asks us to check if there's a perfect one-to-one mapping between the characters of two strings, `s` and `t`, while maintaining their order. This means that if `s[i]` maps to `t[i]`, then every other occurrence of `s[i]` in `s` must also map to `t[i]`. Crucially, it also implies that no *other* character `s[j]` (where `s[j] != s[i]`) can map to `t[i]`. This "two-way" consistency is the key to determining isomorphism.

## 💡 Core Idea
To ensure a valid one-to-one character mapping, we need to track mappings in both directions: from `s` to `t` and from `t` back to `s`. If at any point we find a conflict in either direction (e.g., a character in `s` tries to map to two different characters in `t`, or two different characters in `s` try to map to the same character in `t`), the strings are not isomorphic.

## 🧠 Approach — Hash Map / Dictionary
This problem can be efficiently solved using **Hash Maps** (or dictionaries). Hash maps are ideal for storing key-value pairs and performing quick lookups, insertions, and updates. Here, we need to store character-to-character mappings.

We will use two hash maps:
1. One map (`s_to_t_map`) to store the mapping from characters in `s` to characters in `t`.
2. Another map (`t_to_s_map`) to store the reverse mapping, from characters in `t` to characters in `s`.

The `s_to_t_map` ensures that each character in `s` consistently maps to only one character in `t`. The `t_to_s_map` ensures that each character in `t` is mapped *from* only one character in `s`, thereby enforcing the "no two distinct characters may map to the same character" rule.

## 📝 Step-by-Step Algorithm
1. **Initialize Maps**: Create two empty hash maps:
   - `s_to_t_map`: Stores `char_from_s -> char_from_t` mappings.
   - `t_to_s_map`: Stores `char_from_t -> char_from_s` mappings.
2. **Iterate Through Strings**: Loop from `i = 0` to `s.length - 1` (since `s` and `t` have the same length).
3. **Get Current Characters**: In each iteration, let `c1 = s[i]` and `c2 = t[i]`.
4. **Check `s_to_t_map` Consistency**:
   - **If `c1` is already a key in `s_to_t_map`**: This means we've seen `c1` before and established a mapping. Check if the current mapping `s_to_t_map[c1]` is equal to `c2`. If `s_to_t_map[c1] != c2`, it means `c1` is trying to map to a *different* character `c2` than it did before. This is a violation of the isomorphism rules. Return `false`.
   - **If `c1` is NOT a key in `s_to_t_map`**: This is the first time we've seen `c1`. Establish its mapping: `s_to_t_map[c1] = c2`.
5. **Check `t_to_s_map` Consistency**:
   - **If `c2` is already a key in `t_to_s_map`**: This means `c2` has been a target character before, and we established a reverse mapping. Check if the current reverse mapping `t_to_s_map[c2]` is equal to `c1`. If `t_to_s_map[c2] != c1`, it means `c2` is trying to map back to a *different* character `c1` than it did before. This implies that two distinct characters from `s` are trying to map to the same character `c2` in `t`, which is a violation. Return `false`.
   - **If `c2` is NOT a key in `t_to_s_map`**: This is the first time `c2` has been a target. Establish its reverse mapping: `t_to_s_map[c2] = c1`.
6. **Return True**: If the loop completes without returning `false`, it means all character mappings were consistent in both directions. The strings are isomorphic, so return `true`.

## 💻 Solution
```cpp
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        // Two hash maps are used to store the character mappings.
        // st: maps characters from string s to characters in string t.
        // ts: maps characters from string t to characters in string s.
        // We need two maps to ensure a one-to-one correspondence:
        // 1. A character in 's' must always map to the same character in 't'.
        // 2. A character in 't' must always map back to the same character in 's' (meaning
        //    no two distinct characters in 's' can map to the same character in 't').
        unordered_map<char,char> st; // s_char -> t_char mapping
        unordered_map<char,char> ts; // t_char -> s_char mapping

        // Iterate through both strings simultaneously.
        // The problem constraints guarantee s.length == t.length.
        for(int i = 0; i < s.size(); i++){
            char c1 = s[i]; // Current character from string s
            char c2 = t[i]; // Current character from string t

            // --- Check mapping from s to t (st map) ---
            // If c1 has been seen before in s (i.e., it's already in our map):
            if(st.count(c1)){
                // Check if its previous mapping is consistent with the current c2.
                // If c1 previously mapped to something else (st[c1] != c2),
                // then it's not isomorphic because 'e' cannot map to 'a' and then later to 'b'.
                if(st[c1] != c2)
                    return false; // Conflict found: s[i] maps to different characters in t.
            } else {
                // If c1 is encountered for the first time, establish its mapping.
                st[c1] = c2;
            }

            // --- Check mapping from t to s (ts map) ---
            // This is crucial for the "no two characters may map to the same character" rule.
            // If c2 has been seen before as a target character in t (i.e., it's already in our map):
            if(ts.count(c2)){
                // Check if its previous mapping is consistent with the current c1.
                // If c2 previously mapped back to something else (ts[c2] != c1),
                // then it's not isomorphic. This means two different characters from 's'
                // (e.g., 'f' and 'o' in "foo") are trying to map to the same character in 't'
                // (e.g., 'b' in "bar"). This is a violation.
                if(ts[c2] != c1)
                    return false; // Conflict found: t[i] is mapped by different characters in s.
            } else {
                // If c2 is encountered for the first time as a target, establish its reverse mapping.
                ts[c2] = c1;
            }
        }

        // If the loop completes, all characters were mapped consistently without conflicts.
        return true;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the strings once. Hash map operations (insertion, lookup, count) take O(1) on average. `N` is the length of the strings. |
| **Space** | O(C) | In the worst case, all characters in `s` (and `t`) are unique, requiring up to `C` entries in each hash map, where `C` is the size of the character set (e.g., 256 for ASCII). |

## 🔗 Related Problems
- 242. Valid Anagram
- 290. Word Pattern
- 219. Contains Duplicate II