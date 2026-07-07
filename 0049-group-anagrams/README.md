# 0049-group-anagrams

## 📋 Problem Description
Given an array of strings `strs`, the task is to group all strings that are anagrams of each other together. Anagrams are words formed by rearranging the letters of another word. The order of the output groups and the order of strings within each group does not matter.

The function `groupAnagrams` receives a `vector<string>` named `strs` as input. It must return a `vector<vector<string>>`, where each inner vector contains a group of anagrams.

## 🔍 Examples
```
Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
Explanation:
- "bat" has no other anagrams in the input list.
- "nat" and "tan" are anagrams of each other.
- "ate", "eat", and "tea" are anagrams of each other.
The order of the inner lists and strings within them can vary.
```

```
Input: strs = [""]
Output: [[""]]
Explanation: An empty string is an anagram of itself.
```

```
Input: strs = ["a"]
Output: [["a"]]
Explanation: A single character string is an anagram of itself.
```

## 📌 Constraints
*   `1 <= strs.length <= 10^4`
*   `0 <= strs[i].length <= 100`
*   `strs[i]` consists of lowercase English letters.

## 🤔 Understanding the Problem
The problem asks us to categorize a given list of words into groups where each group contains words that are anagrams of each other. The core challenge is to efficiently determine if two strings are anagrams and then collect them into their respective groups. Two strings are anagrams if they contain the same characters with the same frequencies, regardless of their order. Edge cases include handling empty strings or single-character strings, which are considered anagrams of themselves.

## 💡 Core Idea
The fundamental insight is that all anagrams of a given word will have the exact same characters, just arranged differently. If we can transform each string into a "canonical" form that is identical for all its anagrams, we can use this canonical form as a unique identifier (a key) to group them together.

## 🧠 Approach — Hashing / Hash Map
This problem is a classic application of the **Hashing** pattern. We use a hash map (or dictionary) to store groups of anagrams. The "key" for our hash map will be the canonical representation of an anagram (e.g., a sorted version of the string), and the "value" will be a list of all original strings that produce that canonical key. This approach allows us to efficiently look up and append strings to their respective anagram groups in average O(1) time after the key is generated.

## 📝 Step-by-Step Algorithm
1.  **Initialize Hash Map**: Create an empty hash map (e.g., `unordered_map<string, vector<string>>` in C++). The keys will be strings representing the canonical form of an anagram, and the values will be vectors of strings containing all the original anagrams that map to that key.
2.  **Iterate Through Strings**: Loop through each string `str` in the input array `strs`.
3.  **Generate Canonical Key**: For each `str`, create a temporary copy of it. Sort the characters of this temporary string alphabetically. For example, if `str` is "eat", sorting its characters will result in "aet". If `str` is "tea" or "ate", sorting will also result in "aet". This sorted string becomes our unique "canonical key" for all its anagrams.
4.  **Group Anagrams**: Use this `key` to access the hash map. Add the *original* string `str` to the `vector<string>` associated with this `key` in the hash map. If the `key` does not yet exist in the map, a new entry will be created, and `str` will be the first element in its corresponding vector.
5.  **Collect Results**: After processing all strings in the input array, the hash map will contain all the grouped anagrams. Iterate through all the key-value pairs in the hash map.
6.  **Format Output**: For each pair, extract the `vector<string>` (which is the value part of the pair) and add it to a new `vector<vector<string>>` that will serve as the final result.
7.  **Return Result**: Return the collected `vector<vector<string>>`.

## 💻 Solution
```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // We use an unordered_map to store groups of anagrams.
        // The key will be the "canonical" form of an anagram (e.g., "aet" for "eat", "tea", "ate").
        // The value will be a vector of strings that are anagrams and share this canonical form.
        unordered_map<string, vector<string>> mp;

        // Iterate through each string in the input array.
        for (string str : strs) {
            // Create a temporary string to generate the key.
            string key = str;
            // Sort the characters of the temporary string.
            // For example, if str is "eat", key becomes "aet".
            // If str is "tea", key also becomes "aet".
            // This sorted string serves as a unique identifier for all its anagrams.
            sort(key.begin(), key.end());
            
            // Use the sorted string as the key to the map.
            // Add the original string 'str' to the vector associated with this key.
            // If the key doesn't exist, it will be created, and 'str' will be the first element.
            mp[key].push_back(str);
        }

        // Prepare the result vector, which will hold vectors of grouped anagrams.
        vector<vector<string>> result;
        // Iterate through all key-value pairs in the hash map.
        // Each 'pair.second' is a vector of strings (an anagram group).
        for (auto pair : mp) {
            // Add each group (vector of strings) to our result.
            result.push_back(pair.second);
        }
        
        // Return the final list of grouped anagrams.
        return result;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N * K log K) | We iterate through N strings. For each string of length K, we create a copy (O(K)) and sort it (O(K log K)). Hash map insertion/lookup takes O(K) on average due to string hashing/comparison, but sorting dominates. |
| **Space** | O(N * K) | In the worst case, all N strings are unique (no anagrams), so the hash map stores N entries. Each entry stores a key (sorted string of length K) and the original string (length K). |

## 🔗 Related Problems
- 242. Valid Anagram
- 249. Group Shifted Strings
- 1. Two Sum