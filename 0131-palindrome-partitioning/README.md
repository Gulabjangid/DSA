# 0131-palindrome-partitioning

## 📋 Problem Description
Given a string `s`, the task is to find all possible ways to partition `s` such that every substring in the partition is a palindrome. A palindrome is a string that reads the same forwards and backwards (e.g., "racecar", "madam"). The function should return a list of all such valid partitions, where each partition itself is a list of strings.

**Input:** A string `s`.
**Output:** A `vector<vector<string>>` representing all possible palindrome partitions.

## 🔍 Examples
```
Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]
Explanation:
- "a", "a", "b" are all palindromes.
- "aa", "b" are all palindromes.
```

```
Input: s = "a"
Output: [["a"]]
Explanation:
- "a" is a palindrome.
```

## 📌 Constraints
*   `1 <= s.length <= 16`
*   `s` contains only lowercase English letters.

## 🤔 Understanding the Problem
The problem asks us to break down a given string into multiple smaller strings (a partition), with the strict condition that *every single one* of these smaller strings must be a palindrome. We need to find *all* such possible ways to partition the string. This is non-trivial because there can be many ways to partition a string, and for each partition, we must verify the palindrome property for all its parts. The small constraint on string length (`N <= 16`) hints that an exponential time complexity solution might be acceptable.

## 💡 Core Idea
The core idea is to explore all possible ways to partition the string by trying every possible prefix as the first part of a partition. If a prefix is a palindrome, we include it in our current partition and then recursively solve the problem for the remaining suffix of the string.

## 🧠 Approach — Backtracking (Depth-First Search)
This problem is a classic candidate for **Backtracking**, which is essentially a form of Depth-First Search (DFS). We use backtracking because we need to explore all possible combinations of partitions. At each step, we make a choice (picking a prefix as a palindrome), explore all consequences of that choice recursively, and then "undo" the choice (backtrack) to try other alternatives. This systematic exploration ensures we find all valid partitions without redundant computations or missing any possibilities.

## 📝 Step-by-Step Algorithm
1.  **Helper Function `ispal(string s)`:**
    *   This function takes a string `s` and checks if it's a palindrome.
    *   It creates a reversed copy of `s` and compares it with the original `s`.
    *   Returns `true` if they are identical, `false` otherwise.

2.  **Recursive Backtracking Function `getallparts(string s, vector<string> &current_partition, vector<vector<string>> &all_partitions)`:**
    *   **Base Case:** If the input string `s` is empty (`s.size() == 0`), it means we have successfully partitioned the entire original string into palindromes. In this case, add the `current_partition` (which holds the palindromic parts found so far) to `all_partitions` and return.
    *   **Recursive Step:** Iterate through all possible lengths for the first part of the current string `s`. Let `i` go from `0` to `s.size() - 1`.
        *   Extract a `part` from `s` starting from index `0` up to `i` (i.e., `s.substr(0, i+1)`).
        *   Check if this `part` is a palindrome using the `ispal` helper function.
        *   **If `part` is a palindrome:**
            *   Add `part` to `current_partition`.
            *   Recursively call `getallparts` with the *remaining* string (`s.substr(i+1)`), the updated `current_partition`, and `all_partitions`.
            *   **Backtrack:** After the recursive call returns, remove `part` from `current_partition` using `pop_back()`. This is crucial to explore other possibilities where `part` is not chosen as the first segment.

3.  **Main Function `partition(string s)`:**
    *   Initialize an empty `vector<vector<string>> ans` to store all final palindrome partitions.
    *   Initialize an empty `vector<string> current_partition` to store the parts of the partition being built in the current recursive path.
    *   Call the `getallparts` recursive function with the original string `s`, `current_partition`, and `ans`.
    *   Return `ans`.

## 💻 Solution

```cpp
class Solution {
public:
    // Helper function to check if a given string is a palindrome
    bool ispal(string s){
        string s2 = s; // Create a copy of the string
        reverse(s2.begin(), s2.end()); // Reverse the copy
        return s == s2; // Compare original with reversed copy
    }

    // Recursive backtracking function to find all palindrome partitions
    // s: The remaining string to partition
    // partition: The current list of palindrome parts found for the current path
    // ans: The final list of all valid palindrome partitions
    void getallparts(string s, vector<string> &partition, vector<vector<string>> &ans){
        // Base case: If the string 's' is empty, it means we have successfully
        // partitioned the entire original string into palindromes.
        if(s.size() == 0){
            ans.push_back(partition); // Add the current valid partition to the results
            return; // Backtrack
        }

        // Iterate through all possible prefixes of the current string 's'
        // 'i' represents the end index of the current prefix (0-indexed)
        for(int i = 0; i < s.size(); i++){
            // Extract the prefix substring from index 0 up to 'i' (inclusive)
            string part = s.substr(0, i + 1);

            // Check if this extracted 'part' is a palindrome
            if(ispal(part)){
                // If 'part' is a palindrome:
                partition.push_back(part); // Add it to our current partition list

                // Recursively call getallparts for the remaining suffix of the string
                // The remaining string starts from index 'i+1'
                getallparts(s.substr(i + 1), partition, ans);

                // Backtrack: Remove the 'part' from the current partition list.
                // This is crucial to explore other possibilities where 'part' is not chosen
                // or where a different partition is formed for the remaining string.
                partition.pop_back();
            }
        } 
    }

    // Main function to initiate the palindrome partitioning process
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans; // Stores all final palindrome partitions
        vector<string> current_partition; // Stores the current partition being built
        
        // Start the recursive backtracking process
        getallparts(s, current_partition, ans);    
        
        return ans; // Return all found partitions
    }
};
```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N * 2^N) or O(N^2 * 2^N) | In the worst case, there can be `2^(N-1)` ways to partition a string of length `N`. For each partition, we might perform `N` palindrome checks. Each `ispal` check takes `O(N)` time, and `s.substr` also takes `O(N)`. Thus, roughly `O(N)` work per recursive call, and `2^N` calls in the worst case, leading to `O(N * 2^N)` if `s.substr` is the dominant factor, or `O(N^2 * 2^N)` if considering both `s.substr` and `ispal` operations at each step. Given `N <= 16`, `16^2 * 2^16` is approximately `1.6 * 10^7`, which is feasible. |
| **Space** | O(N * 2^N) | The recursion depth can go up to `N`. The `current_partition` vector can store up to `N` strings, each of length up to `N`, contributing `O(N^2)` space for one path. The `ans` vector stores all valid partitions. In the worst case (e.g., "aaaa..."), there can be `2^(N-1)` distinct partitions. Each partition can contain up to `N` strings, and each string can be up to `N` characters long. Thus, the total space for `ans` can be `O(N * 2^N)`. |

*Note: The time complexity can be optimized to `O(N * 2^N)` by pre-computing all palindromic substrings using dynamic programming in `O(N^2)` time, making `ispal` an `O(1)` lookup. However, the `s.substr` operations still contribute `O(N)` to each step.*

## 🔗 Related Problems
- 132. Palindrome Partitioning II
- 40. Combination Sum II
- 78. Subsets