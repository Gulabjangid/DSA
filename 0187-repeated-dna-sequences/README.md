# 0187-repeated-dna-sequences

## 📋 Problem Description
You are given a string `s` that represents a DNA sequence. DNA sequences are composed of four types of nucleotides: 'A', 'C', 'G', and 'T'. Your task is to find all 10-letter-long sequences (substrings) within this DNA molecule that occur more than once. The order in which you return these repeated sequences does not matter.

The function should accept a single string `s` as input and return a `vector<string>` containing all unique 10-letter sequences that appear at least twice.

## 🔍 Examples
```
Input:  s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
Output: ["AAAAACCCCC","CCCCCAAAAA"]
Explanation: "AAAAACCCCC" appears twice (at index 0 and index 10). "CCCCCAAAAA" appears twice (at index 5 and index 15).

Input:  s = "AAAAAAAAAAAAA"
Output: ["AAAAAAAAAA"]
Explanation: "AAAAAAAAAA" appears multiple times (at index 0, 1, 2, 3). We only need to list it once in the output.

Input:  s = "ACGTACGTACGT"
Output: []
Explanation: No 10-letter sequence appears more than once.
```

## 📌 Constraints
*   `1 <= s.length <= 10^5`
*   `s[i]` is either `'A'`, `'C'`, `'G'`, or `'T'`.

## 🤔 Understanding the Problem
The problem asks us to identify specific substrings of a fixed length (10 characters) that are duplicates within a larger DNA sequence. We need to find *all* such unique 10-letter substrings that appear at least twice. This means we'll need a way to efficiently extract all possible 10-letter substrings and then count their occurrences or simply track if they've been seen before. An important edge case is when the input string `s` is shorter than 10 characters, in which case no 10-letter sequences can be formed.

## 💡 Core Idea
To efficiently find repeated 10-letter sequences, we can use a sliding window approach to generate all possible substrings of length 10, combined with hash sets to keep track of which sequences have been seen and which ones are confirmed duplicates.

## 🧠 Approach — Sliding Window + Hash Set
This problem is a classic candidate for the **Sliding Window** pattern combined with **Hash Sets**. A sliding window is perfect here because we need to examine all contiguous substrings of a fixed length (10). By "sliding" a window of size 10 across the input string, we can generate each 10-letter sequence exactly once. Hash sets (like `unordered_set` in C++) are ideal for storing and quickly checking the presence of these substrings. They offer average O(1) time complexity for insertion and lookup, which is crucial for performance when dealing with potentially many substrings. We'll use one hash set to record every unique 10-letter sequence encountered, and another to collect only those sequences that have been identified as repeated.

## 📝 Step-by-Step Algorithm
1.  **Initialize Data Structures**:
    *   Create an empty `unordered_set<string>` called `seen_sequences`. This set will store every unique 10-letter sequence we encounter during our traversal.
    *   Create an empty `unordered_set<string>` called `repeated_sequences`. This set will store the 10-letter sequences that have been found to occur more than once. Using a set here automatically ensures that the final output contains only unique repeated sequences.

2.  **Handle Edge Case**:
    *   Check if the length of the input string `s` is less than 10. If it is, no 10-letter sequences can be formed, so return an empty `vector<string>`.

3.  **Slide the Window**:
    *   Iterate through the input string `s` using a loop. The loop variable `i` will represent the starting index of our 10-letter window.
    *   The loop should run from `i = 0` up to `s.length() - 10`. This ensures that `s.substr(i, 10)` always extracts a valid 10-character substring without going out of bounds.

4.  **Extract and Check Substring**:
    *   Inside the loop, for each `i`, extract the current 10-letter substring starting at `i` using `s.substr(i, 10)`. Let's call this `current_window`.
    *   Check if `current_window` is already present in the `seen_sequences` set:
        *   If `current_window` *is found* in `seen_sequences`, it means we have encountered this sequence before. Therefore, it is a repeated sequence. Add this `current_window` to the `repeated_sequences` set.
        *   If `current_window` *is not found* in `seen_sequences`, it means this is the first time we are seeing this particular sequence. Add this `current_window` to the `seen_sequences` set.

5.  **Return Result**:
    *   After the loop finishes, all 10-letter sequences will have been processed. The `repeated_sequences` set now contains all unique 10-letter sequences that occurred more than once.
    *   Convert the `repeated_sequences` set into a `vector<string>` and return it.

## 💻 Solution
```cpp
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        // 'seen_sequences' will store all unique 10-letter DNA sequences encountered so far.
        // We use an unordered_set for O(1) average time complexity for insertion and lookup,
        // which is crucial for performance.
        unordered_set<string> seen_sequences;
        
        // 'repeated_sequences' will store the sequences that have been found to occur more than once.
        // Using an unordered_set here automatically handles uniqueness for the final output,
        // as we only want to list each repeated sequence once.
        unordered_set<string> repeated_sequences;

        // Edge case: If the string length is less than 10, no 10-letter sequences can be formed.
        // In this scenario, we should return an empty vector.
        if (s.length() < 10) {
            return {};
        }

        // Iterate through the string 's' using a sliding window of length 10.
        // The loop runs from index 0 up to `s.length() - 10`.
        // This ensures that `s.substr(i, 10)` always extracts a valid 10-character substring.
        for (int i = 0; i <= s.length() - 10; ++i) {
            // Extract the current 10-letter substring (the "window").
            // `s.substr(i, 10)` creates a new string starting at index 'i' with a length of 10.
            string current_window = s.substr(i, 10);

            // Check if this 'current_window' has been seen before.
            // `seen_sequences.find(current_window)` returns an iterator to the element if found,
            // or `seen_sequences.end()` if not found.
            if (seen_sequences.find(current_window) != seen_sequences.end()) {
                // If it's found in 'seen_sequences', it means we've encountered this
                // sequence at least once before. Therefore, it is a repeated sequence.
                // Add it to our 'repeated_sequences' set. If it's already there,
                // the set will simply ignore the duplicate insertion.
                repeated_sequences.insert(current_window);
            } else {
                // If it's not found in 'seen_sequences', this is the first time
                // we are encountering this sequence. Add it to 'seen_sequences'
                // so we can detect future repetitions.
                seen_sequences.insert(current_window);
            }
        }

        // Convert the 'repeated_sequences' set into a `vector<string>` for the final return.
        // The `vector` constructor `vector<string>(begin_iterator, end_iterator)`
        // efficiently populates the vector with elements from the set.
        return vector<string>(repeated_sequences.begin(), repeated_sequences.end());
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N * L) | The loop runs `N - L + 1` times (approximately `N` times). Inside the loop, `s.substr(i, 10)` takes O(L) time, and `unordered_set` operations (find, insert) on strings of length L take O(L) time on average due to string hashing and comparison. N is `s.length()`, L is 10. |
| **Space** | O(N * L) | In the worst case, all `N - L + 1` substrings could be unique and stored in `seen_sequences`. Each substring has length L. The `repeated_sequences` set also stores substrings of length L. Thus, the total space is proportional to the number of unique L-length substrings multiplied by L. |

*Note: Since L=10 is a constant, the complexity is often simplified to O(N) for both time and space in competitive programming contexts, assuming string operations are constant time. However, it's more precise to include L as it reflects the actual work involved in string manipulation.*

## 🔗 Related Problems
- 3. Longest Substring Without Repeating Characters
- 219. Contains Duplicate II
- 76. Minimum Window Substring