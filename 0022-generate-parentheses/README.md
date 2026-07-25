# 0022-generate-parentheses

## 📋 Problem Description
Given an integer `n`, representing `n` pairs of parentheses, the task is to write a function that generates all possible combinations of well-formed parentheses. A string of parentheses is considered "well-formed" if:
1. Every opening parenthesis has a corresponding closing parenthesis.
2. The parentheses are properly nested (e.g., `(()())` is well-formed, but `)(` or `(()` are not).

The function should receive an integer `n` as input and return a `vector<string>` containing all unique well-formed parenthesis combinations.

## 🔍 Examples
```
Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
Explanation: For n=3, there are 5 unique well-formed parenthesis combinations.

Input: n = 1
Output: ["()"]
Explanation: For n=1, there is only 1 unique well-formed parenthesis combination.
```

## 📌 Constraints
*   `1 <= n <= 8`

## 🤔 Understanding the Problem
The problem asks us to construct all valid sequences of `n` opening parentheses and `n` closing parentheses. The key challenge is ensuring that the generated sequences are "well-formed," meaning that at any point while reading the string from left to right, the count of opening parentheses must be greater than or equal to the count of closing parentheses, and the total count of opening parentheses must equal the total count of closing parentheses at the end. This is a classic combinatorial problem where we need to explore all possibilities while adhering to specific rules.

## 💡 Core Idea
The core idea is to use **backtracking** (a form of recursion) to build the parenthesis strings character by character. We maintain counts of open and close parentheses used so far and only add a character if it maintains the "well-formed" property.

## 🧠 Approach — Backtracking / Recursion
This problem is a perfect candidate for a **Backtracking** approach. Backtracking is an algorithmic paradigm for finding all (or some) solutions to computational problems, notably constraint satisfaction problems, that incrementally builds candidates to the solutions, and abandons a candidate ("backtracks") as soon as it determines that the candidate cannot possibly be completed to a valid solution.

Here's why it fits:
1.  **Building incrementally**: We construct the parenthesis string one character at a time.
2.  **Exploring possibilities**: At each step, we have two choices: add an opening parenthesis `(` or a closing parenthesis `)`.
3.  **Constraints**: We need to ensure the string remains well-formed. This means we can only add `(` if we haven't used all `n` opening parentheses yet, and we can only add `)` if the number of `)` already added is less than the number of `(` already added (to prevent `)(` scenarios).
4.  **Base Case**: A valid string is formed when its length becomes `2 * n` (meaning `n` open and `n` close parentheses have been used).

## 📝 Step-by-Step Algorithm

1.  **Initialize**:
    *   Create an empty `vector<string>` called `ans` to store all valid parenthesis combinations.
    *   Create an empty string `curr` to build the current parenthesis sequence.
    *   Define a recursive helper function, say `solve(n, open, close, curr)`, where:
        *   `n`: The total number of parenthesis pairs required.
        *   `open`: The count of opening parentheses `(` currently in `curr`.
        *   `close`: The count of closing parentheses `)` currently in `curr`.
        *   `curr`: The string being built.

2.  **Base Case**:
    *   If the length of `curr` becomes `2 * n` (meaning we have placed `n` opening and `n` closing parentheses), then `curr` is a complete, well-formed string. Add `curr` to the `ans` vector and return.

3.  **Recursive Steps**:
    *   **Option 1: Add an opening parenthesis `(`**
        *   If the number of `open` parentheses used so far is less than `n` (meaning we still have opening parentheses available to place):
            *   Append `(` to `curr`.
            *   Recursively call `solve(n, open + 1, close, curr)`.
            *   **Backtrack**: Remove the last character `(` from `curr` to explore other possibilities (this is crucial for backtracking).

    *   **Option 2: Add a closing parenthesis `)`**
        *   If the number of `close` parentheses used so far is less than the number of `open` parentheses used so far (this ensures that we don't place a `)` before a corresponding `(` and maintain well-formedness):
            *   Append `)` to `curr`.
            *   Recursively call `solve(n, open, close + 1, curr)`.
            *   **Backtrack**: Remove the last character `)` from `curr`.

4.  **Initial Call**:
    *   From the `generateParenthesis` function, initiate the backtracking process by calling `solve(n, 0, 0, curr)`.
    *   Finally, return the `ans` vector.

## 💻 Solution
```cpp
class Solution {
public:
    // This vector will store all the generated well-formed parenthesis strings.
    vector<string> ans;

    // Recursive helper function to generate parenthesis combinations.
    // n: The total number of pairs of parentheses.
    // open: The current count of '(' characters added to 'curr'.
    // close: The current count of ')' characters added to 'curr'.
    // curr: The string being built incrementally.
    void solve(int n, int open, int close, string &curr) {

        // Base case: If the current string 'curr' has reached the total required length (2 * n),
        // it means we have successfully placed 'n' open and 'n' close parentheses.
        // This string is a valid well-formed combination.
        if (curr.length() == 2 * n) {
            ans.push_back(curr); // Add it to our results.
            return;              // Stop this path of recursion.
        }

        // Recursive Step 1: Try adding an opening parenthesis '('
        // We can add an opening parenthesis if we haven't used all 'n' available opening parentheses yet.
        if (open < n) {
            curr.push_back('(');          // Add '(' to the current string.
            solve(n, open + 1, close, curr); // Recurse with an incremented 'open' count.
            curr.pop_back();              // Backtrack: Remove '(' to explore other possibilities.
                                          // This is crucial for trying different combinations.
        }

        // Recursive Step 2: Try adding a closing parenthesis ')'
        // We can add a closing parenthesis only if the number of closing parentheses
        // is less than the number of opening parentheses. This ensures well-formedness
        // (i.e., we don't have ')' before a matching '(').
        if (close < open) {
            curr.push_back(')');          // Add ')' to the current string.
            solve(n, open, close + 1, curr); // Recurse with an incremented 'close' count.
            curr.pop_back();              // Backtrack: Remove ')' to explore other possibilities.
        }
    }

    // Main function to generate all combinations of well-formed parentheses.
    vector<string> generateParenthesis(int n) {
        string curr = ""; // Initialize an empty string to start building combinations.
        // Start the recursive process. Initially, no parentheses are used (open=0, close=0).
        solve(n, 0, 0, curr);
        return ans; // Return the vector containing all generated strings.
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O( (4^n) / sqrt(n) ) | The number of valid parenthesis sequences is given by the `n`-th Catalan number, `C_n = (1/(n+1)) * (2n choose n)`, which grows roughly as `4^n / (n^(3/2))`. For each valid sequence, we build a string of length `2n`. The total number of nodes in the recursion tree is proportional to `C_n * 2n`. |
| **Space** | O( (4^n) / sqrt(n) ) | The space complexity is dominated by storing the `C_n` valid strings, each of length `2n`. Additionally, the recursion stack depth goes up to `2n`. |

## 🔗 Related Problems
- 46. Permutations
- 78. Subsets
- 216. Combination Sum III