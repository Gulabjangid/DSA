# 0022-generate-parentheses

## 📋 Problem Description
Given an integer `n`, representing `n` pairs of parentheses, the task is to generate all possible combinations of well-formed parentheses. A "well-formed" parenthesis string means that:
1. Every opening parenthesis has a corresponding closing parenthesis.
2. The parentheses are properly nested (e.g., `(()())` is well-formed, but `)(` is not).

The function should receive an integer `n` as input and return a `vector` of strings, where each string is a unique well-formed combination of `n` pairs of parentheses.

## 🔍 Examples
```
Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
Explanation: For n=3, there are 5 unique ways to form well-formed parentheses using 3 opening and 3 closing parentheses.

Input: n = 1
Output: ["()"]
Explanation: For n=1, there is only 1 way to form well-formed parentheses using 1 opening and 1 closing parenthesis.
```

## 📌 Constraints
*   `1 <= n <= 8`

## 🤔 Understanding the Problem
The problem asks us to find all distinct sequences of `n` opening and `n` closing parentheses such that the sequence is "well-formed". This means that at any point while reading the string from left to right, the count of opening parentheses must be greater than or equal to the count of closing parentheses, and the total count of opening parentheses must equal the total count of closing parentheses at the end. The non-trivial aspect is systematically generating all such combinations without duplicates and ensuring correctness.

## 💡 Core Idea
The core idea is to use a recursive backtracking approach. We build the parenthesis string character by character, making decisions at each step: either add an opening parenthesis or a closing parenthesis. We prune invalid paths early by enforcing the well-formedness rules during construction.

## 🧠 Approach — Backtracking / Recursion
This problem is a classic example of **Backtracking** (which is a form of recursion). Backtracking is suitable here because we need to explore all possible combinations (a search space) and build a solution step-by-step. At each step, we make a choice (add '(' or ')'), and if that choice leads to an invalid state, we "backtrack" (undo the choice) and try another option. This systematic exploration ensures we find all valid solutions without redundant computations or duplicates. The constraints on `n` (up to 8) also suggest that an exponential time complexity (typical for backtracking) will be acceptable.

## 📝 Step-by-Step Algorithm

1.  **Initialize**: Create an empty `vector<string>` called `ans` to store all the valid parenthesis combinations.
2.  **Recursive Helper Function**: Define a recursive helper function, let's call it `solve`, which takes the following parameters:
    *   `n`: The total number of parenthesis pairs required.
    *   `open`: The current count of opening parentheses added to the string.
    *   `close`: The current count of closing parentheses added to the string.
    *   `curr`: The current string being built (passed by reference to allow modifications).

3.  **Base Case**: Inside `solve`:
    *   If the length of `curr` becomes `2 * n` (meaning we have added `n` opening and `n` closing parentheses), it implies we have successfully formed a complete string. Add `curr` to the `ans` vector and return.

4.  **Recursive Steps (Choices and Pruning)**:
    *   **Option 1: Add an opening parenthesis `(`**:
        *   We can add an opening parenthesis if the current count of `open` parentheses is less than `n` (we haven't used all `n` opening parentheses yet).
        *   If `open < n`, append `(` to `curr`.
        *   Recursively call `solve(n, open + 1, close, curr)` to explore this path.
        *   **Backtrack**: After the recursive call returns, remove the `(` from `curr` (using `pop_back()`) to undo the choice and allow exploration of other paths.

    *   **Option 2: Add a closing parenthesis `)`**:
        *   We can add a closing parenthesis if the current count of `close` parentheses is less than the current count of `open` parentheses. This condition `close < open` is crucial for ensuring well-formedness: a closing parenthesis can only be added if there's an unmatched opening parenthesis available.
        *   If `close < open`, append `)` to `curr`.
        *   Recursively call `solve(n, open, close + 1, curr)` to explore this path.
        *   **Backtrack**: After the recursive call returns, remove the `)` from `curr` (using `pop_back()`) to undo the choice.

5.  **Initial Call**: In the main `generateParenthesis` function, initialize an empty string `curr = ""`. Then, call the `solve` helper function with `solve(n, 0, 0, curr)` to start the process.

6.  **Return Result**: Finally, return the `ans` vector containing all generated well-formed parenthesis strings.

## 💻 Solution
```cpp
class Solution {
public:
    // This vector will store all the valid combinations of parentheses.
    vector<string> ans;

    // Recursive helper function to generate well-formed parentheses.
    // n: Total number of parenthesis pairs required.
    // open: Current count of opening parentheses added to 'curr'.
    // close: Current count of closing parentheses added to 'curr'.
    // curr: The string being built, passed by reference to allow modifications.
    void solve(int n, int open, int close, string &curr) {

        // Base Case: If the current string length equals 2 * n,
        // it means we have successfully added 'n' opening and 'n' closing parentheses.
        // This string is a complete, well-formed combination.
        if (curr.length() == 2 * n) {
            ans.push_back(curr); // Add it to our results.
            return;              // Stop this recursive path.
        }

        // Option 1: Try adding an opening parenthesis '('
        // We can add an opening parenthesis if we haven't used all 'n' opening parentheses yet.
        if (open < n) {
            curr.push_back('('); // Add '(' to the current string.
            // Recursively call solve, incrementing the 'open' count.
            solve(n, open + 1, close, curr);
            curr.pop_back();     // Backtrack: Remove '(' to explore other possibilities.
        }

        // Option 2: Try adding a closing parenthesis ')'
        // We can add a closing parenthesis only if the number of closing parentheses
        // is less than the number of opening parentheses. This ensures well-formedness
        // (i.e., we don't close a parenthesis that hasn't been opened yet).
        if (close < open) {
            curr.push_back(')'); // Add ')' to the current string.
            // Recursively call solve, incrementing the 'close' count.
            solve(n, open, close + 1, curr);
            curr.pop_back();     // Backtrack: Remove ')' to explore other possibilities.
        }
    }

    // Main function to initiate the generation process.
    vector<string> generateParenthesis(int n) {
        string curr = ""; // Initialize an empty string to start building combinations.
        // Start the recursive process with 0 open and 0 close parentheses.
        solve(n, 0, 0, curr);
        return ans; // Return the collected valid combinations.
    }
};

```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O( (4^n) / (n * sqrt(n)) ) or O(C_n * 2n) | The number of valid parenthesis sequences of length `2n` is given by the `n`-th Catalan number, `C_n = (1/(n+1)) * (2n choose n)`. The algorithm generates all `C_n` sequences. For each sequence, building it involves `2n` character appends/removals. So, the total time is proportional to `C_n * 2n`. `C_n` grows exponentially, roughly as `4^n / (n^(3/2))`. |
| **Space** | O( (4^n) / (n * sqrt(n)) * 2n ) | The space complexity is dominated by storing the `C_n` result strings, each of length `2n`. Additionally, the recursion stack depth can go up to `2n`, contributing `O(2n)` space. |

## 🔗 Related Problems
- 17. Letter Combinations of a Phone Number
- 78. Subsets
- 46. Permutations