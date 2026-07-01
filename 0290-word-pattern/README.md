# 0290-word-pattern

## 📋 Problem Description
Given a `pattern` string consisting of lowercase English letters and a string `s` consisting of lowercase English words separated by single spaces, determine if `s` follows the same `pattern`.

"Follows" implies a full match where there is a **bijection** between a letter in `pattern` and a non-empty word in `s`. Specifically, this means:
*   Each letter in `pattern` must map to exactly one unique word in `s`.
*   Each unique word in `s` must map to exactly one letter in `pattern`.
*   No two distinct letters in `pattern` can map to the same word, and no two distinct words in `s` can map to the same letter.

The function should return `true` if `s` follows the `pattern` according to these rules, and `false` otherwise.

## 🔍 Examples
```
Input:  pattern = "abba", s = "dog cat cat dog"
Output: true
Explanation:
The bijection can be established as:
'a' maps to "dog".
'b' maps to "cat".
This mapping is consistent throughout the pattern and words.
```

```
Input:  pattern = "abba", s = "dog cat cat fish"
Output: false
Explanation:
'a' maps to "dog", 'b' maps to "cat".
When the pattern reaches the last 'a', it expects "dog", but finds "fish". This violates the consistency.
```

```
Input:  pattern = "aaaa", s = "dog cat cat dog"
Output: false
Explanation:
'a' maps to "dog".
When the pattern reaches the second 'a', it expects "dog", but finds "cat". This violates the consistency.
Alternatively, if 'a' maps to "dog", then "cat" has no corresponding character, or if 'a' maps to "cat" at some point, it violates the unique word mapping. The core issue is that 'a' must map to a single unique word throughout.
```

## 📌 Constraints
*   `1 <= pattern.length <= 300`
*   `pattern` contains only lower-case English letters.
*   `1 <= s.length <= 3000`
*   `s` contains only lowercase English letters and spaces `' '`.
*   `s` does not contain any leading or trailing spaces.
*   All the words in `s` are separated by a single space.

## 🤔 Understanding the Problem
The problem asks us to check for a perfect one-to-one correspondence (a bijection) between characters in a `pattern` string and words in another string `s`. This means not only must each character consistently map to the same word, but also each word must consistently map back to the same character. It's a two-way street: if 'a' maps to "apple", then 'a' can *only* map to "apple", and "apple" can *only* map to 'a'. Any deviation or conflict in either direction makes the pattern invalid. An important edge case is ensuring the number of characters in the `pattern` exactly matches the number of words in `s`.

## 💡 Core Idea
To ensure a true bijection, we need to maintain and check mappings in *both* directions: from `pattern` characters to `s` words, and from `s` words back to `pattern` characters. Hash maps are ideal for efficiently storing and retrieving these mappings.

## 🧠 Approach — Hash Map / Two-Way Mapping
This problem is perfectly suited for using **Hash Maps** (or `unordered_map` in C++) to establish and verify a **two-way mapping**. We need two separate hash maps because a bijection requires consistency from character to word *and* from word to character. One map will store `char -> string` associations, ensuring that each character always maps to the same word. The second map will store `string -> char` associations, ensuring that each word always maps to the same character. By checking both maps simultaneously during iteration, we can guarantee the bijection property.

## 📝 Step-by-Step Algorithm
1.  **Parse the String `s`**:
    *   First, we need to break down the input string `s` into individual words. A `stringstream` is a convenient tool in C++ for this purpose.
    *   Extract each word from the `stringstream` and store them sequentially in a `vector<string>`.
2.  **Initial Length Check**:
    *   Compare the number of characters in the `pattern` string with the total number of words extracted from `s`.
    *   If `pattern.length()` is not equal to `words.size()`, a full match is impossible, so return `false` immediately.
3.  **Initialize Mapping Structures**:
    *   Create two hash maps:
        *   `unordered_map<char, string> char_to_word_map;`: This map will store mappings from a character in `pattern` to its corresponding word in `s`.
        *   `unordered_map<string, char> word_to_char_map;`: This map will store mappings from a word in `s` to its corresponding character in `pattern`.
4.  **Iterate and Validate Mappings**:
    *   Loop through the `pattern` string from `i = 0` up to `pattern.length() - 1`. In each iteration, we will consider `pattern[i]` and `words[i]`.
    *   Let `currentChar = pattern[i]` and `currentWord = words[i]`.
    *   **Check `char_to_word_map`**:
        *   If `currentChar` already exists as a key in `char_to_word_map`:
            *   Verify if its mapped value (`char_to_word_map[currentChar]`) is equal to `currentWord`.
            *   If they are *not* equal, it means `currentChar` was previously mapped to a different word. This violates the "each letter maps to exactly one unique word" rule. Return `false`.
        *   If `currentChar` does *not* exist in `char_to_word_map`:
            *   **Check `word_to_char_map`**: Before creating a new mapping, we must ensure `currentWord` isn't already mapped to a *different* character.
            *   If `currentWord` already exists as a key in `word_to_char_map`:
                *   This means `currentWord` was previously mapped to some other character. This violates the "each unique word maps to exactly one letter" rule. Return `false`.
            *   If `currentWord` does *not* exist in `word_to_char_map`:
                *   Both `currentChar` and `currentWord` are new to their respective maps. Establish the new mappings:
                    *   `char_to_word_map[currentChar] = currentWord;`
                    *   `word_to_char_map[currentWord] = currentChar;`
5.  **Return Result**:
    *   If the loop completes without returning `false` at any point, it means all characters and words followed the bijection rules. Return `true`.

## 💻 Solution
```cpp
#include <string>
#include <vector>
#include <sstream> // Required for stringstream to parse words
#include <unordered_map> // Required for unordered_map (hash maps)

class Solution {
public:
    bool wordPattern(string pattern, string s) {

        // Step 1: Parse the input string 's' into individual words.
        // stringstream allows treating a string like an input stream,
        // making it easy to extract words separated by spaces.
        stringstream ss(s);
        vector<string> words; // To store the extracted words
        string word;         // Temporary variable to hold each word

        // Extract words one by one until the stream is empty.
        // The '>>' operator extracts space-separated tokens.
        while(ss >> word) {
            words.push_back(word);
        }

        // Step 2: Initial Length Check.
        // If the number of characters in 'pattern' does not match the number of words in 's',
        // a bijection is impossible, so return false immediately.
        if(pattern.size() != words.size())
            return false;

        // Step 3: Initialize Mapping Structures.
        // We need two hash maps to ensure a bidirectional (one-to-one) mapping.
        // mp1: Maps a character from 'pattern' to a word from 's'.
        unordered_map<char, string> mp1;

        // mp2: Maps a word from 's' back to a character from 'pattern'.
        // This is crucial to ensure that no two different characters map to the same word,
        // and no two different words map to the same character.
        unordered_map<string, char> mp2;

        // Step 4: Iterate and Validate Mappings.
        // Loop through the pattern and words simultaneously using their indices.
        for(int i = 0; i < pattern.size(); i++) {

            char c = pattern[i];   // Current character from the pattern
            string w = words[i];   // Current word from the parsed string 's'

            // Check mp1 (char -> word mapping):
            // If 'c' is already in mp1, it means we've seen this character before.
            // We must ensure it maps to the exact same word 'w'.
            if(mp1.count(c) && mp1[c] != w) {
                return false; // Conflict: 'c' previously mapped to a different word.
            }

            // Check mp2 (word -> char mapping):
            // If 'w' is already in mp2, it means we've seen this word before.
            // We must ensure it maps to the exact same character 'c'.
            if(mp2.count(w) && mp2[w] != c) {
                return false; // Conflict: 'w' previously mapped to a different character.
            }

            // If no conflicts were found, establish or update the mappings.
            // If 'c' or 'w' were new, they are added. If they existed and were consistent,
            // this operation effectively does nothing (overwrites with same value).
            mp1[c] = w;
            mp2[w] = c;
        }

        // Step 5: Return Result.
        // If the loop completes without any conflicts, it means a valid bijection exists.
        return true;
    }
};

```

## ⏱️ Complexity Analysis
Let `L_p` be the length of the `pattern` string and `L_s` be the length of the string `s`. Let `N` be the number of words in `s`. Note that `N` will be equal to `L_p` if the initial length check passes.

| | Complexity | Reason |
|---|---|---|
| **Time** | O(L_s) | Parsing `s` into words takes O(L_s) time. The subsequent loop runs `N` (which is `L_p`) times. Inside the loop, hash map operations (insertion, lookup, comparison) take O(1) on average. In the worst case, string comparisons could take O(length of word), but the total length of all words is `L_s`. Thus, the dominant factor is the total length of `s` for parsing and word operations. |
| **Space** | O(L_s) | The `words` vector stores all `N` words, which in total can take up to O(L_s) space. Each hash map (`mp1` and `mp2`) stores at most `N` entries. In the worst case, if all words are unique and long, the total space for storing words within the maps can also be O(L_s). |

## 🔗 Related Problems
- 205. Isomorphic Strings
- 219. Contains Duplicate II
- 1. Two Sum