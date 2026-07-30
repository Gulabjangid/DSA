# 0692-top-k-frequent-words

## 📋 Problem Description
Given an array of strings `words` and an integer `k`, the task is to find the `k` most frequent strings. The result should be returned as a list of strings.

The output must be sorted according to two criteria:
1.  **Primary Sort**: By frequency, from highest to lowest.
2.  **Secondary Sort**: If two words have the same frequency, they should be sorted in lexicographical (alphabetical) order, from smallest to largest.

The function `topKFrequent` receives `words` (a `vector<string>`) and `k` (an `int`) as input, and it must return a `vector<string>` containing the `k` most frequent words, sorted as specified.

## 🔍 Examples
```
Input: words = ["i","love","leetcode","i","love","coding"], k = 2
Output: ["i","love"]
Explanation: "i" appears 2 times, "love" appears 2 times, "leetcode" appears 1 time, "coding" appears 1 time.
The two most frequent are "i" and "love". Since they have the same frequency (2), they are sorted lexicographically: "i" comes before "love".

Input: words = ["the","day","is","sunny","the","the","the","sunny","is","is"], k = 4
Output: ["the","is","sunny","day"]
Explanation:
"the": 4 times
"is": 3 times
"sunny": 2 times
"day": 1 time
The four most frequent words are "the", "is", "sunny", and "day", sorted by frequency descending.
```

## 📌 Constraints
*   `1 <= words.length <= 500`
*   `1 <= words[i].length <= 10`
*   `words[i]` consists of lowercase English letters.
*   `k` is in the range `[1, The number of unique words[i]]`

## 🤔 Understanding the Problem
This problem asks us to identify the most frequently occurring words in a given list and then return a specific number (`k`) of them. The key challenge lies in the sorting requirements: not only do we need to sort by frequency (descending), but we also need a secondary sort by lexicographical order (ascending) for words with identical frequencies. This means a simple frequency count followed by a standard sort won't work directly; we need a custom sorting mechanism.

## 💡 Core Idea
The core idea is to first count the occurrences of each word, then store these word-frequency pairs in a structure that can be sorted using a custom comparison function that incorporates both frequency and lexicographical order, and finally extract the top `k` elements.

## 🧠 Approach — Sorting with Custom Comparator
This problem can be effectively solved using a **Sorting with Custom Comparator** approach.
First, we need to determine the frequency of each word. A hash map (like `unordered_map` in C++) is ideal for this, as it allows efficient counting of occurrences for each unique string. Once we have all word-frequency pairs, we can transfer them into a sortable data structure, such as a `vector` of pairs. The crucial step is then to sort this vector using a custom comparison function. This function will implement the specific sorting rules: higher frequency first, and for ties, lexicographically smaller word first. After sorting, the first `k` elements in the vector will be our answer.

## 📝 Step-by-Step Algorithm
1.  **Count Frequencies**: Initialize an `unordered_map` (hash map) where keys are strings (words) and values are integers (their frequencies). Iterate through the input `words` array. For each word, increment its count in the map.
2.  **Transfer to Sortable Structure**: Create a `vector` of `pair<string, int>`. Iterate through the `unordered_map` and add each word-frequency pair into this vector. This converts the map's contents into a structure that can be easily sorted.
3.  **Define Custom Comparator**: Implement a static comparison function (e.g., `cmp`) that takes two `pair<string, int>` objects.
    *   If the frequencies (`second` element of the pair) are equal, compare the words (`first` element of the pair) lexicographically. Return `true` if the first word is lexicographically smaller than the second word (for ascending order).
    *   If the frequencies are not equal, compare the frequencies. Return `true` if the first pair's frequency is greater than the second pair's frequency (for descending order).
4.  **Sort**: Use `std::sort` to sort the `vector` of pairs, passing the custom comparator function. This will arrange all word-frequency pairs according to the specified rules.
5.  **Extract Top K**: Create a new `vector<string>` to store the final answer. Iterate from `i = 0` to `k-1` (or until the end of the sorted vector if it has fewer than `k` unique words). For each iteration, add the word (the `first` element of the pair) from the sorted vector to the answer vector.
6.  **Return Result**: Return the `vector<string>` containing the top `k` frequent words.

## 💻 Solution
```cpp
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm> // Required for std::sort
#include <utility>   // Required for std::pair

class Solution {
public:
    // Custom comparison function for sorting pairs of (word, frequency).
    // This function defines the sorting order:
    // 1. Higher frequency first.
    // 2. If frequencies are equal, lexicographically smaller word first.
    static bool cmp(pair<string, int> &a, pair<string, int> &b) {
        // If frequencies are the same, sort by word lexicographically (ascending).
        if (a.second == b.second) {
            return a.first < b.first; // 'a' comes before 'b' if 'a' is lexicographically smaller
        }
        // Otherwise, sort by frequency (descending).
        return a.second > b.second;   // 'a' comes before 'b' if 'a' has higher frequency
    }

    vector<string> topKFrequent(vector<string>& words, int k) {
        // Step 1: Count frequencies of each word using an unordered_map.
        // Keys are words (string), values are their counts (int).
        unordered_map<string, int> mp;
        for (string s : words) {
            mp[s]++; // Increment count for the current word
        }

        // Step 2: Transfer word-frequency pairs from the map to a vector.
        // This vector will then be sorted.
        vector<pair<string, int>> v;
        for (pair<string, int> p : mp) {
            v.push_back(p);
        }

        // Step 3: Sort the vector using the custom comparison function 'cmp'.
        // This arranges the pairs according to the problem's sorting criteria.
        sort(v.begin(), v.end(), cmp);

        // Step 4: Extract the top 'k' words from the sorted vector.
        vector<string> ans;
        for (int i = 0; i < k; i++) {
            // Add the word (first element of the pair) to the result vector.
            ans.push_back(v[i].first);
        }

        // Step 5: Return the vector containing the top 'k' frequent words.
        return ans;
    }
};

```

## ⏱️ Complexity Analysis
Let `N` be the number of words in the input array (`words.length`), `L` be the maximum length of a word (`words[i].length`), and `U` be the number of unique words in the input array (`U <= N`).

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N * L + U log U * L) | **1. Counting Frequencies:** Iterating `N` words. Hashing and insertion/access for each word takes O(L) on average (due to string operations). Total: O(N * L). <br> **2. Transfer to Vector:** Iterating `U` unique words and copying them. Total: O(U * L). <br> **3. Sorting:** `std::sort` on `U` elements takes O(U log U) comparisons. Each comparison (`cmp` function) involves O(1) for integer comparison and O(L) for string comparison in the worst case. Total: O(U log U * L). <br> **4. Extracting Top K:** Iterating `K` times and copying strings. Total: O(K * L). <br> Overall, the dominant term is O(U log U * L), which can be approximated as O(N log N * L) in the worst case where all words are unique. |
| **Space** | O(U * L) | **1. `unordered_map`:** Stores up to `U` unique words, each of length `L`. Total: O(U * L). <br> **2. `vector<pair>`:** Stores `U` pairs, each containing a string of length `L`. Total: O(U * L). <br> **3. `ans` vector:** Stores `K` strings, each of length `L`. Total: O(K * L). <br> Since `K <= U`, the overall space is dominated by O(U * L), which can be approximated as O(N * L) in the worst case. |

## 🔗 Related Problems
-   347. Top K Frequent Elements
-   215. Kth Largest Element in an Array
-   703. Kth Largest Element in a Stream