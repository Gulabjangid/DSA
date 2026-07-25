# 0022-generate-parentheses

## 📋 Problem Description
Given an integer `n`, representing `n` pairs of parentheses, the task is to write a function that generates all possible combinations of well-formed parentheses. A "well-formed" parentheses string means that:
1. Every opening parenthesis has a corresponding closing parenthesis.
2. The parentheses are properly nested (e.g., `(()())` is well-formed, but `)(` is not).
3. The total number of opening parentheses equals `n`, and the total number of closing parentheses also equals `n`.

The function should receive an integer `n` as input and return a `std::vector<std::string>` containing all unique well-formed parentheses combinations.

## 🔍 Examples
```
Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
Explanation: For n=3, there are 5 unique ways to form well-formed parentheses.

Input: n = 1
Output: ["()"]
Explanation: For n=1, only one pair of parentheses can be arranged as "()".
```

## 📌 Constraints
*   `1 <= n <= 8`

## 🤔 Understanding the Problem
The problem asks us to construct all valid sequences of `n` opening and `n` closing parentheses. The challenge lies in ensuring that each generated string adheres to the "well-formed" rules: the count of opening parentheses must always be greater than or equal to the count of closing parentheses at any point in the string, and the final counts must both equal `n`. This is non-trivial because simply generating all permutations of `n` '(' and `n` ')' characters would produce many invalid combinations (e.g., `())((` for `n=3`). We need a systematic way to build only valid strings.

## 💡 Core Idea
The core idea is to build the parentheses string incrementally, character by character, while maintaining counts of open and close parentheses used so far. At each step, we only add a character if it maintains the "well-formed" property, effectively pruning invalid paths early.

## 🧠 Approach — Backtracking
This problem is a classic example of **Backtracking**.
Backtracking is an algorithmic paradigm for finding all (or some) solutions to computational problems, notably constraint satisfaction problems, that incrementally builds candidates to the solutions, and abandons a candidate ("backtracks") as soon as it determines that the candidate cannot possibly be completed to a valid solution.

This pattern fits perfectly here because:
1.  **Exploration of all possibilities**: We need to generate *all* combinations, which suggests an exhaustive search.
2.  **Incremental construction**: We can build the parentheses string one character at a time.
3.  **Constraints for pruning**: At each step, we have clear rules (constraints) to check if adding an '(' or ')' would lead to a valid partial string or an invalid one. If it's invalid, we don't proceed further down that path, saving computation. This pruning is the essence of backtracking.
4.  **State management**: We need to keep track of the current string, the number of open parentheses used, and the number of close parentheses used to make decisions.

## 📝 Step-by-Step Algorithm
The solution uses a recursive helper function to implement the backtracking approach:

1.  **Initialization**:
    *   Create an empty `std::vector<std::string>` named `ans` to store all the valid combinations.
    *   Initialize an empty string `curr` which will be used to build each combination.
    *   Call a recursive helper function, say `solve(n, open_count, close_count, current_string)`, with initial values `n` (the total number of pairs), `0` for `open_count`, `0` for `close_count`, and the empty string `curr`.

2.  **Recursive Helper Function `solve(n, open_count, close_count, current_string)`**:
    *   **Base Case**:
        *   If the `current_string`'s length is equal to `2 * n` (meaning we have placed all `n` opening and `n` closing parentheses), then this `current_string` is a valid well-formed combination. Add it to the `ans` vector and return.

    *   **Recursive Step 1: Add an opening parenthesis '('**:
        *   If `open_count < n` (meaning we haven't used all `n` opening parentheses yet):
            *   Append '(' to `current_string`.
            *   Recursively call `solve(n, open_count + 1, close_count, current_string)`.
            *   **Backtrack**: After the recursive call returns, remove the last added '(' from `current_string`. This is crucial to explore other possibilities (e.g., if we added `((`, we want to try `(()` next, not just `(((`).

    *   **Recursive Step 2: Add a closing parenthesis ')'**:
        *   If `close_count < open_count` (meaning we haven't used all `n` closing parentheses yet, AND the number of closing parentheses is strictly less than the number of opening parentheses, ensuring well-formedness):
            *   Append ')' to `current_string`.
            *   Recursively call `solve(n, open_count, close_count + 1, current_string)`.
            *   **Backtrack**: After the recursive call returns, remove the last added ')' from `current_string`.

3.  **Return Value**:
    *   The `generateParenthesis` function simply initializes the process and returns the `ans` vector once all recursive calls have completed.

## 💻 Solution
```cpp
class Solution {
public:
    // This vector will store all the generated well-formed parenthesis strings.
    vector<string> ans;

    /**
     * Recursive helper function to generate well-formed parentheses.
     * @param n The total number of parenthesis pairs required.
     * @param open The current count of opening parentheses '(' used in 'curr'.
     * @param close The current count of closing parentheses ')' used in 'curr'.
     * @param curr The string being built incrementally. Passed by reference for efficiency.
     */
    void solve(int n, int open, int close, string &curr) {

        // Base case: If the current string length is 2*n, it means we have placed
        // all 'n' opening and 'n' closing parentheses. This is a complete,
        // well-formed string. Add it to our results.
        if (curr.length() == 2 * n) {
            ans.push_back(curr);
            return; // End this path of recursion
        }

        // Recursive Step 1: Try adding an opening parenthesis '('
        // We can add an opening parenthesis if we haven't used all 'n' available opening parentheses.
        if (open < n) {
            curr.push_back('('); // Add '(' to the current string
            solve(n, open + 1, close, curr); // Recurse with an incremented 'open' count
            curr.pop_back(); // Backtrack: Remove '(' to explore other possibilities
        }

        // Recursive Step 2: Try adding a closing parenthesis ')'
        // We can add a closing parenthesis if:
        // 1. We haven't used all 'n' available closing parentheses (implicitly handled by 'close < open').
        // 2. The number of closing parentheses is strictly less than the number of opening parentheses.
        //    This condition ensures that the parentheses remain well-formed at every step
        //    (e.g., we don't add ')' before a matching '(').
        if (close < open) {
            curr.push_back(')'); // Add ')' to the current string
            solve(n, open, close + 1, curr); // Recurse with an incremented 'close' count
            curr.pop_back(); // Backtrack: Remove ')' to explore other possibilities
        }
    }

    /**
     * Main function to generate all combinations of well-formed parentheses.
     * @param n The number of pairs of parentheses.
     * @return A vector of strings, each representing a well-formed parenthesis combination.
     */
    vector<string> generateParenthesis(int n) {
        string curr = ""; // Initialize an empty string for building combinations
        // Start the recursive process. Initially, no open or close parentheses are used.
        solve(n, 0, 0, curr);
        return ans; // Return the collected results
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O( (4^n) / sqrt(n) ) | The number of valid parenthesis sequences of length `2n` is given by the `n`-th Catalan number, `C_n`. `C_n` is approximately `(4^n) / (n^(3/2) * sqrt(pi))`. For each valid sequence, we perform `2n` operations (append/pop). Thus, the total time complexity is `O(C_n * 2n)`. |
| **Space** | O( (4^n) / sqrt(n) ) | The space complexity is dominated by the storage of the `ans` vector. It stores `C_n` strings, each of length `2n`. Additionally, the recursion stack depth can go up to `2n`. Therefore, the total space complexity is `O(C_n * 2n)`. |

## 🔗 Related Problems
- 17. Letter Combinations of a Phone Number
- 46. Permutations
- 77. Combinations
- 78. Subsets
- 51. N-Queens