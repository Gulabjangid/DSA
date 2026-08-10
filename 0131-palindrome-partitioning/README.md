# 0131-palindrome-partitioning

## 📋 Problem Description
Given a string `s`, the task is to find all possible ways to partition `s` such that every substring in each partition is a palindrome. The function should return a list of all such valid partitions.

**Input:** A string `s`.
**Output:** A list of lists of strings, where each inner list represents a valid palindrome partition of `s`.

## 🔍 Examples
```
Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]
Explanation:
The string "aab" can be partitioned in two ways where all parts are palindromes:
1. ["a", "a", "b"] - "a" is a palindrome, "a" is a palindrome, "b" is a palindrome.
2. ["aa", "b"] - "aa" is a palindrome, "b" is a palindrome.

Input: s = "a"
Output: [["a"]]
Explanation:
The string "a" can only be partitioned as ["a"], which is a palindrome.
```

## 📌 Constraints
*   `1 <= s.length <= 16`
*   `s` contains only lowercase English letters.

## 🤔 Understanding the Problem
The problem asks us to break down a given string into smaller pieces (substrings), with the strict condition that *every single piece* must itself be a palindrome. We need to find *all* possible ways to do this. This is a combinatorial problem, as we are exploring different ways to split the string. The small constraint on `s.length` (up to 16) suggests that an exponential time complexity solution might be acceptable.

## 💡 Core Idea
The core idea is to use a recursive backtracking approach. We iterate through all possible prefixes of the current string. If a prefix is a palindrome, we consider it as the first part of a partition, and then recursively solve the problem for the remaining suffix of the string.

## 🧠 Approach — Backtracking (Depth-First Search)
This problem is a classic example of **Backtracking**, which is essentially a form of Depth-First Search (DFS) on a decision tree. We use backtracking because we need to explore all possible ways to partition the string. At each step, we make a choice (which prefix to take as a palindrome), explore the consequences of that choice recursively, and then "undo" the choice (backtrack) to explore other alternatives. This systematic exploration ensures we find all valid partitions.

## 📝 Step-by-Step Algorithm

1.  **Helper Function for Palindrome Check:**
    *   Create a helper function, `ispal(string str)`, that takes a string `str` and returns `true` if `str` is a palindrome, `false` otherwise. This can be done by comparing `str` with its reversed version.

2.  **Main Backtracking Function (`getallparts`):**
    *   This function will be recursive and take the current remaining string `s`, the current `partition` (a vector of strings representing the parts found so far), and the `ans` (a vector of vectors of strings to store all final valid partitions).
    *   **Base Case:** If the current string `s` is empty (meaning we have successfully partitioned the entire original string), add the current `partition` to the `ans` list and return.
    *   **Recursive Step:**
        *   Iterate from `i = 0` to `s.size() - 1`. This `i` represents the end index of a potential prefix substring.
        *   Extract the `part` substring from `s` starting at index 0 and ending at index `i` (i.e., `s.substr(0, i+1)`).
        *   Check if `part` is a palindrome using the `ispal` helper function.
        *   If `part` *is* a palindrome:
            *   Add `part` to the current `partition`.
            *   Recursively call `getallparts` with the *remaining* part of the string (`s.substr(i+1)`), the updated `partition`, and `ans`.
            *   **Backtrack:** After the recursive call returns, remove `part` from the current `partition` (using `pop_back()`). This is crucial to explore other possibilities where `part` is not chosen as the first element, or a different first element is chosen.

3.  **Main `partition` Function:**
    *   Initialize an empty `vector<vector<string>> ans` to store all final partitions.
    *   Initialize an empty `vector<string> partition` to store the current partition being built.
    *   Call the `getallparts` backtracking function with the original input string `s`, the empty `partition`, and `ans`.
    *   Return `ans`.

## 💻 Solution

```cpp
class Solution {
public:
    // Helper function to check if a given string is a palindrome.
    // A palindrome reads the same forwards and backwards.
    bool ispal(string s){
        string s2 = s; // Create a copy of the string
        reverse(s2.begin(), s2.end()); // Reverse the copy
        return s == s2; // Compare the original with the reversed copy
    }

    // Recursive backtracking function to find all palindrome partitions.
    // 's' is the remaining part of the string to be partitioned.
    // 'partition' is the current list of palindrome substrings found so far for the current path.
    // 'ans' is the final list of all valid palindrome partitions.
    void getallparts(string s, vector<string> &partition, vector<vector<string>> &ans){
        // Base case: If the remaining string 's' is empty,
        // it means we have successfully partitioned the entire original string.
        if(s.size() == 0){
            ans.push_back(partition); // Add the current valid partition to the results.
            return; // End this recursive path.
        }

        // Iterate through all possible prefixes of the current string 's'.
        // 'i' represents the end index of the current prefix (0-indexed).
        for(int i = 0; i < s.size(); i++){
            // Extract the prefix substring from index 0 up to 'i' (inclusive).
            // s.substr(0, i+1) gets a substring of length (i+1).
            string part = s.substr(0, i + 1);

            // Check if the extracted 'part' is a palindrome.
            if(ispal(part)){
                // If 'part' is a palindrome, include it in the current partition.
                partition.push_back(part);

                // Recursively call getallparts for the remaining suffix of the string.
                // s.substr(i+1) gets the string starting from index (i+1) to the end.
                getallparts(s.substr(i + 1), partition, ans);

                // Backtrack: Remove the last added 'part' from the current partition.
                // This allows us to explore other choices for the current position
                // (e.g., taking a longer or different palindrome as the first part).
                partition.pop_back();
            }
        }
    }

    // Main function to initiate the palindrome partitioning process.
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans; // Stores all final palindrome partitions.
        vector<string> partition;   // Stores the current partition being built during recursion.

        // Start the backtracking process from the beginning of the string 's'.
        getallparts(s, partition, ans);    
        return ans; // Return all found partitions.
    }
};
```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N * 2^N) or O(N^2 * 2^N) | In the worst case, there can be `2^(N-1)` ways to partition a string of length `N`. For each partition, we perform `N` palindrome checks (roughly), and each check takes `O(N)` time for string reversal and comparison. The `substr` operations also take `O(N)`. This leads to `O(N^2 * 2^N)`. Given `N <= 16`, `2^16` is ~65k, so `16^2 * 2^16` is feasible. |
| **Space** | O(N * 2^N) | The recursion stack depth is `O(N)`. The `partition` vector stores at most `N` substrings, total length `N`. The `ans` vector stores all valid partitions. In the worst case (e.g., `s = "aaaa..."`), there can be `2^(N-1)` partitions, each containing up to `N` substrings. The total characters stored in `ans` can be `O(N * 2^N)`. Temporary strings created by `substr` also contribute `O(N)` at any given time. |

*Note: The time complexity can be optimized to `O(N^2 + N * 2^N)` by pre-computing all palindrome substrings using dynamic programming in `O(N^2)` time, making `ispal` an `O(1)` lookup.*

## 🔗 Related Problems
*   17. Letter Combinations of a Phone Number (Backtracking)
*   40. Combination Sum II (Backtracking)
*   90. Subsets II (Backtracking)
*   139. Word Break (Dynamic Programming, can be solved with DFS/Backtracking + Memoization)