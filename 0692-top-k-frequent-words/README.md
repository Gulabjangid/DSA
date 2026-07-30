# 0692-top-k-frequent-words

## 📋 Problem Description
Given an array of strings `words` and an integer `k`, the task is to find the `k` most frequent strings. The result should be returned as a list of strings, sorted first by their frequency in descending order (highest frequency first). If two words have the same frequency, they should be sorted by their lexicographical order (alphabetical order) in ascending fashion.

The function `topKFrequent` receives:
*   `words`: A `vector` of strings.
*   `k`: An integer representing the number of most frequent words to return.

It must return:
*   A `vector` of strings containing the `k` most frequent words, sorted according to the specified criteria.

## 🔍 Examples
```
Input:  words = ["i","love","leetcode","i","love","coding"], k = 2
Output: ["i","love"]
Explanation: "i" appears 2 times, "love" appears 2 times, "leetcode" appears 1 time, "coding" appears 1 time.
The two most frequent words are "i" and "love".
They both have a frequency of 2. According to lexicographical order, "i" comes before "love".
```

```
Input:  words = ["the","day","is","sunny","the","the","the","sunny","is","is"], k = 4
Output: ["the","is","sunny","day"]
Explanation: Frequencies: "the": 4, "is": 3, "sunny": 2, "day": 1.
Sorted by frequency (descending): "the", "is", "sunny", "day".
All frequencies are distinct, so lexicographical order is not needed for ties here.
```

## 📌 Constraints
*   `1 <= words.length <= 500`
*   `1 <= words[i].length <= 10`
*   `words[i]` consists of lowercase English letters.
*   `k` is in the range `[1, The number of unique words[i]]`

## 🤔 Understanding the Problem
This problem asks us to identify the most common words from a given list and present them in a specific sorted order. The core challenge lies in accurately counting word frequencies and then applying a custom sorting logic: primary sort by frequency (descending) and secondary sort by alphabetical order (ascending) for ties. This means we can't just use a standard sort; we need a way to define our own comparison rules.

## 💡 Core Idea
The fundamental idea is to first count the occurrences of each unique word. Once we have these frequencies, we can then sort all unique words based on the given criteria (frequency first, then lexicographical order) and pick the top `k` entries.

## 🧠 Approach — Frequency Counting and Custom Sorting
This problem perfectly fits the "Frequency Counting and Custom Sorting" pattern. We need to count how many times each word appears, which is a classic use case for a hash map (or `unordered_map` in C++). After counting, we have pairs of (word, frequency). The problem's specific sorting requirements (descending frequency, then ascending lexicographical for ties) necessitate a custom comparison function when sorting these pairs. This pattern is effective because it breaks down the problem into two manageable steps: aggregation (counting) and ordering (sorting with custom rules).

## 📝 Step-by-Step Algorithm

1.  **Count Frequencies**:
    *   Initialize an `unordered_map` (hash map) where keys are strings (words) and values are integers (their frequencies).
    *   Iterate through the input `words` array. For each word encountered, increment its corresponding count in the hash map.

2.  **Transfer to a Sortable Structure**:
    *   Create a `vector` of `pair<string, int>`.
    *   Iterate through all key-value pairs in the hash map. For each `(word, frequency)` pair, add it to this vector. This converts the map's data into a structure that can be easily sorted.

3.  **Define Custom Comparison Logic**:
    *   Implement a custom comparison function (e.g., `cmp` in C++). This function will take two `pair<string, int>` objects and return `true` if the first should come before the second in the sorted order.
    *   Inside the comparison function:
        *   First, compare their frequencies: If `frequency_a` is greater than `frequency_b`, `a` should come before `b`.
        *   If frequencies are equal (`frequency_a == frequency_b`), then compare their words lexicographically: If `word_a` is lexicographically smaller than `word_b`, `a` should come before `b`.
        *   Otherwise, `a` should not come before `b`.

4.  **Sort the Words**:
    *   Use a standard sorting algorithm (like `std::sort` in C++) on the vector of `pair<string, int>`, passing the custom comparison function. This will arrange all unique words according to the problem's criteria.

5.  **Extract Top K Words**:
    *   Initialize an empty `vector` of strings to store the final answer.
    *   Iterate from `i = 0` up to `k-1` (or until the end of the sorted vector if it has fewer than `k` elements).
    *   For each `i`, take the word (the `first` element of the pair) from the `i`-th position in the sorted vector and add it to the answer vector.

6.  **Return Result**:
    *   Return the `vector` containing the `k` most frequent words.

## 💻 Solution

```cpp
#include <vector>     // Required for std::vector
#include <string>     // Required for std::string
#include <unordered_map> // Required for std::unordered_map
#include <algorithm>  // Required for std::sort
#include <utility>    // Required for std::pair

class Solution {
public:
    // Custom comparison function for sorting pairs of (word, frequency).
    // It defines the order: higher frequency first, then lexicographically smaller word first.
    static bool cmp(pair<string, int> &a, pair<string, int> &b) {
        // If frequencies are the same, sort by lexicographical order (ascending).
        if (a.second == b.second) {
            return a.first < b.first; // 'a' comes before 'b' if 'a' is alphabetically smaller
        }
        // Otherwise, sort by frequency in descending order (higher frequency first).
        return a.second > b.second; // 'a' comes before 'b' if 'a' has higher frequency
    }

    vector<string> topKFrequent(vector<string>& words, int k) {
        // Step 1: Count frequencies of each word using an unordered_map.
        // Keys are words (string), values are their counts (int).
        unordered_map<string, int> mp;
        for (string s : words) {
            mp[s]++; // Increment count for the current word
        }

        // Step 2: Transfer map entries into a vector of pairs.
        // This allows us to sort them easily.
        vector<pair<string, int>> v;
        for (pair<string, int> p : mp) {
            v.push_back(p); // Add each (word, frequency) pair to the vector
        }

        // Step 3 & 4: Sort the vector of pairs using our custom comparison function.
        // std::sort uses an efficient algorithm (typically IntroSort)
        // and applies our 'cmp' logic to determine the order.
        sort(v.begin(), v.end(), cmp);

        // Step 5: Extract the top k frequent words from the sorted vector.
        vector<string> ans;
        for (int i = 0; i < k; i++) {
            // Add the word (first element of the pair) to the result vector.
            ans.push_back(v[i].first);
        }

        // Step 6: Return the final list of top k frequent words.
        return ans;
    }
};
```

## ⏱️ Complexity Analysis

Let `N` be the total number of words in the input `words` array (`words.length`).
Let `L` be the maximum length of a word (`words[i].length`).
Let `U` be the number of unique words in the input array (`U <= N`).

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N * L + U * L * log U) | **1. Counting Frequencies:** Iterating `N` words, each `unordered_map` operation (hashing + insertion/update) takes O(L) on average. Total: O(N * L).<br>**2. Transfer to Vector:** Iterating `U` unique words, each `push_back` copies a string of length O(L). Total: O(U * L).<br>**3. Sorting:** Sorting `U` pairs. Each comparison in `cmp` takes O(L) in the worst case (string comparison). Sorting `U` elements takes O(U log U) comparisons. Total: O(U * L * log U).<br>**4. Extracting Top K:** Iterating `k` times, each `push_back` copies a string of length O(L). Total: O(k * L).<br>Combining these, the dominant term is O(N * L + U * L * log U). Since `U <= N`, this can be simplified to O(N * L + N * L * log N) which is O(N * L * log N). |
| **Space** | O(U * L) | **1. Hash Map:** Stores `U` unique words, each of max length `L`, plus an integer count. Total: O(U * L).<br>**2. Vector of Pairs:** Stores `U` pairs, each containing a string of max length `L` and an integer. Total: O(U * L).<br>**3. Result Vector:** Stores `k` strings, each of max length `L`. Total: O(k * L).<br>Since `k <= U`, the overall space is dominated by the hash map and vector of pairs, resulting in O(U * L). Since `U <= N`, this is O(N * L). |

## 🔗 Related Problems
- 347. Top K Frequent Elements
- 451. Sort Characters By Frequency
- 1338. Reduce Array Size to The Half