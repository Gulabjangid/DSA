# 0131-palindrome-partitioning

## 📋 Problem Description
Given a string `s`, the task is to find all possible ways to partition `s` such that every substring in the partition is a palindrome. The function should return a list of all such valid partitions.

**Input**: A string `s`.
**Output**: A list of lists of strings, where each inner list represents a valid palindrome partition of `s`.

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
The problem asks us to break down a given string into multiple smaller substrings, with the strict condition that *every single one* of these smaller substrings must be a palindrome. We need to find *all* possible ways to do this. For example, for "aab", we can partition it as ["a", "a", "b"] because "a", "a", and "b" are all palindromes. Another valid partition is ["aa", "b"] because "aa" and "b" are palindromes. The non-trivial aspect is that there can be multiple ways to partition the string, and we need to explore all of them. The small constraint on `s.length` (up to 16) suggests that an exponential time complexity solution might be acceptable.

## 💡 Core Idea
The core idea is to use a recursive backtracking approach. We iterate through all possible prefixes of the current string. If a prefix is a palindrome, we consider it as the first part of a partition, and then recursively try to partition the remaining suffix of the string.

## 🧠 Approach — Backtracking (Depth-First Search)
This problem is a classic example of a **Backtracking** algorithm, which is essentially a form of Depth-First Search (DFS) on a decision tree. We use backtracking because we need to explore all possible ways to partition the string. At each step, we make a decision (choose a prefix as a palindrome), explore the consequences of that decision recursively, and then "undo" the decision (backtrack) to explore other alternatives. This systematic exploration ensures that all valid partitions are found. The recursive calls build up a potential partition, and when the entire string is processed, a complete partition is added to the results.

## 📝 Step-by-Step Algorithm
1.  **Palindrome Check Helper**: Create a helper function, `ispal(string str)`, that takes a string and returns `true` if it's a palindrome, `false` otherwise. This can be done by comparing the string with its reversed version.

2.  **Main Backtracking Function**:
    *   Define a recursive function, let's call it `getallparts(string current_s, vector<string>& current_partition, vector<vector<string>>& all_partitions)`.
    *   **Base Case**: If `current_s` is empty (meaning we have successfully partitioned the entire original string), it means `current_partition` holds a valid set of palindrome substrings. Add a copy of `current_partition` to `all_partitions` and return.
    *   **Recursive Step**: Iterate through all possible lengths for the first substring of `current_s`. Let `i` go from `0` to `current_s.size() - 1`.
        *   Extract the prefix `part = current_s.substr(0, i+1)`.
        *   Check if `part` is a palindrome using the `ispal` helper function.
        *   If `part` is a palindrome:
            *   Add `part` to `current_partition`.
            *   Recursively call `getallparts` with the remaining suffix of the string (`current_s.substr(i+1)`), the updated `current_partition`, and `all_partitions`.
            *   **Backtrack**: After the recursive call returns, remove `part` from `current_partition` (using `pop_back()`). This is crucial to explore other possibilities where `part` might not be the first element of the partition.

3.  **Initial Call**: In the main `partition(string s)` function:
    *   Initialize an empty `vector<vector<string>> ans` to store all final partitions.
    *   Initialize an empty `vector<string> current_partition` to build a single partition during recursion.
    *   Call `getallparts(s, current_partition, ans)`.
    *   Return `ans`.

## 💻 Solution

```cpp
class Solution {
public:
    // Helper function to check if a given string is a palindrome.
    // A palindrome reads the same forwards and backwards.
    bool ispal(string s){
        // Create a copy of the string.
        string s2 = s;
        // Reverse the copied string.
        reverse(s2.begin(), s2.end());
        // Compare the original string with its reversed version.
        // If they are identical, the string is a palindrome.
        return s == s2;
    }

    // Recursive backtracking function to find all palindrome partitions.
    // s: The remaining part of the string to be partitioned.
    // partition: The current list of palindrome substrings forming a partition.
    // ans: The final list of all valid palindrome partitions found.
    void getallparts(string s, vector<string> &partition, vector<vector<string>> &ans){
        // Base case: If the remaining string 's' is empty,
        // it means we have successfully partitioned the entire original string.
        if(s.size() == 0){
            // Add the current partition (which is a complete and valid set of palindromes)
            // to our list of all answers.
            ans.push_back(partition);
            return; // End this recursive path.
        }

        // Iterate through all possible lengths for the first substring of 's'.
        // 'i' represents the end index of the current prefix (0-indexed).
        for(int i = 0; i < s.size(); i++){
            // Extract the prefix substring from 's' starting at index 0 and ending at 'i'.
            // The length of this substring will be (i + 1).
            string part = s.substr(0, i + 1);

            // Check if this extracted prefix 'part' is a palindrome.
            if(ispal(part)){
                // If 'part' is a palindrome, consider it as part of the current partition.
                partition.push_back(part);

                // Recursively call getallparts with the remaining suffix of the string.
                // The suffix starts from index (i + 1) of the current 's'.
                // This explores further partitions for the rest of the string.
                getallparts(s.substr(i + 1), partition, ans);

                // Backtrack: After the recursive call returns, remove 'part' from the current partition.
                // This is crucial to explore other possibilities where 'part' might not be
                // the first element of the partition, or where a different length prefix
                // is chosen for the current 's'.
                partition.pop_back();
            }
        }
    }

    // Main function to initiate the palindrome partitioning process.
    vector<vector<string>> partition(string s) {
        // 'ans' will store all the final palindrome partitions.
        vector<vector<string>> ans;
        // 'partition' will store the current partition being built during recursion.
        vector<string> partition;
        
        // Start the recursive backtracking process with the full input string 's'.
        getallparts(s, partition, ans);    
        
        // Return the collected list of all valid partitions.
        return ans;
    }
};

```

## ⏱️ Complexity Analysis
Let `N` be the length of the input string `s`.

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N^2 * 2^N) | The algorithm explores up to `2^(N-1)` possible partitions. At each step of the recursion (up to `N` depth), `substr` and `ispal` operations are performed. `substr` takes `O(N)` time to create a new string, and `ispal` takes `O(N)` time to check a substring of length `N`. In the worst case, these operations are performed for roughly `N` choices at each of the `2^N` nodes in the recursion tree. |
| **Space** | O(N * 2^N) | The space is dominated by storing the `ans` vector. In the worst case, there can be `2^(N-1)` distinct partitions. Each partition can contain up to `N` substrings, and the total length of characters in each partition is `N`. Thus, storing all results can take `O(N * 2^N)` space. Additionally, the recursion stack depth is `O(N)`, and the `partition` vector also takes `O(N)` space. |

*Note: The constraint `N <= 16` is a strong indicator that an exponential time complexity solution is expected and acceptable.*

## 🔗 Related Problems
- 17. Letter Combinations of a Phone Number (Backtracking)
- 78. Subsets (Backtracking)
- 40. Combination Sum II (Backtracking)