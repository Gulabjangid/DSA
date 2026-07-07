# 0049-group-anagrams

## 📋 Problem Description
Given an array of strings `strs`, the task is to group all strings that are anagrams of each other. Anagrams are words or phrases formed by rearranging the letters of another, using all the original letters exactly once. The order of the output groups, as well as the order of strings within each group, does not matter.

**Input:** An array of strings, `strs`.
**Output:** A list of lists of strings, where each inner list contains a group of anagrams.

## 🔍 Examples
```
Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
Explanation:
- "bat" is unique and forms its own group.
- "nat" and "tan" are anagrams of each other.
- "ate", "eat", and "tea" are anagrams of each other.
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
The core of this problem is to identify strings that are anagrams of one another and then collect them into distinct groups. Two strings are anagrams if they contain the exact same characters with the exact same frequencies, just in a different order. The challenge lies in efficiently determining this relationship for potentially many strings, especially given that string lengths can vary and there can be up to 10,000 strings. Edge cases include empty strings and single-character strings, which are anagrams of themselves.

## 💡 Core Idea
The fundamental insight is that all anagrams of a given string will have the same characters, just arranged differently. If we can transform every string into a *canonical form* that is identical for all its anagrams but unique for non-anagrams, we can use this canonical form as a key to group them. Sorting the characters of a string provides such a canonical key. For example, "eat", "tea", and "ate" all become "aet" when sorted.

## 🧠 Approach — Hash Map (or Dictionary/Associative Array)
This problem is a classic application of a **Hash Map**. We can leverage the property that anagrams, when their characters are sorted, will result in identical strings. This sorted string can then serve as a unique identifier (a key) for that particular group of anagrams. We use a hash map where the keys are these sorted strings, and the values are lists of the original strings that produce that sorted key. This allows for efficient grouping because hash map lookups and insertions are, on average, very fast.

## 📝 Step-by-Step Algorithm
1.  **Initialize a Hash Map**: Create an empty hash map (e.g., `std::unordered_map<string, vector<string>>` in C++). The keys will be the sorted strings (our canonical representation for an anagram group), and the values will be vectors of original strings that belong to that anagram group.
2.  **Iterate Through Input Strings**: Loop through each string `str` in the given input array `strs`.
3.  **Generate Canonical Key**: For each `str`:
    a.  Create a temporary string, let's call it `key_str`, which is a copy of `str`.
    b.  Sort the characters of `key_str` alphabetically. For instance, if `str` is "eat", `key_str` becomes "aet". If `str` is "tea", `key_str` also becomes "aet".
4.  **Group Anagrams**: Use this `key_str` as the key to access the hash map. Add the original `str` to the vector of strings associated with `key_str` in the map. If `key_str` is not yet present in the map, a new entry will be created, and `str` will be its first element in the vector.
5.  **Collect Results**: After processing all strings in `strs`, the hash map will contain all the grouped anagrams.
6.  **Format Output**: Initialize an empty `vector<vector<string>>` to store the final result. Iterate through all the key-value pairs in the hash map. For each pair, extract the value (which is a `vector<string>` containing all anagrams for that key) and add it to the result list.
7.  **Return Result**: Return the `vector<vector<string>>` containing all the grouped anagrams.

## 💻 Solution
```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // Declare an unordered_map to store groups of anagrams.
        // The key will be the sorted version of a string (canonical representation of an anagram group).
        // The value will be a vector of strings that are anagrams and produce this key.
        unordered_map<string, vector<string>> mp;

        // Iterate through each string in the input vector 'strs'.
        for (string str : strs) {
            // Create a temporary string 'key' which will be the sorted version of 'str'.
            string key = str;
            // Sort the characters of 'key'. This is the crucial step:
            // All anagrams (e.g., "eat", "tea", "ate") will produce the exact same sorted 'key' ("aet").
            sort(key.begin(), key.end());
            
            // Use the sorted 'key' to access the map.
            // Add the original string 'str' to the vector associated with this 'key'.
            // If 'key' doesn't exist yet, the map will automatically create an entry for it
            // with an empty vector, and then push_back 'str' into it.
            mp[key].push_back(str);
        }

        // Initialize a vector of vectors of strings to store the final result.
        vector<vector<string>> result;
        // Iterate through all key-value pairs in the hash map.
        // Each 'pair' consists of a sorted string (key) and a vector of its anagrams (value).
        for (auto pair : mp) {
            // Add the vector of anagrams (which is the 'second' element of the pair) to our result.
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
| **Time** | O(N * K log K) | We iterate through N strings. For each string of length K, we sort it (O(K log K)) and perform a hash map operation (average O(K) for string hashing/comparison). The sorting dominates. |
| **Space** | O(N * K) | In the worst case, all N strings are unique (no anagrams), so the hash map stores N entries. Each entry stores a key (sorted string of length K) and an original string (length K). |

## 🔗 Related Problems
*   242. Valid Anagram
*   347. Top K Frequent Elements
*   451. Sort Characters By Frequency