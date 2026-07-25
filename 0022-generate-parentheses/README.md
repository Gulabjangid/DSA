# 0022-generate-parentheses

## 📋 Problem Description
Given an integer `n`, representing `n` pairs of parentheses, the task is to write a function that generates all possible combinations of well-formed parentheses. A "well-formed" parentheses string means that every opening parenthesis has a corresponding closing parenthesis, and the parentheses are properly nested (e.g., `()` is well-formed, `)(` is not).

The function receives a single integer `n` as input.
It must return a `vector` of `string`s, where each string is a unique combination of `n` pairs of well-formed parentheses.

## 🔍 Examples
```
Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
Explanation: For n=3, there are 5 unique combinations of 3 pairs of well-formed parentheses.
```

```
Input: n = 1
Output: ["()"]
Explanation: For n=1, there is only 1 combination: one opening and one closing parenthesis.
```

## 📌 Constraints
*   `1 <= n <= 8`

## 🤔 Understanding the Problem
The problem asks us to generate all valid arrangements of `n` opening parentheses and `n` closing parentheses. The "well-formed" condition is crucial: at any point while building a string, the number of closing parentheses cannot exceed the number of opening parentheses, and the total count of opening parentheses must equal the total count of closing parentheses at the end. This problem is non-trivial because the order matters, and we need to explore all valid combinations without duplicates.

## 💡 Core Idea
The core idea is to use a recursive backtracking approach. We build the parenthesis string character by character, making choices at each step (either add an opening parenthesis or a closing parenthesis) and ensuring that these choices maintain the "well-formed" property.

## 🧠 Approach — Backtracking / Recursion
This problem is a classic example of **Backtracking** (which is a form of recursion). Backtracking is suitable here because we need to explore all possible combinations by making a sequence of choices. If a choice leads to an invalid state, we "backtrack" (undo the choice) and try another path. In this problem, we build a string incrementally, and at each step, we have options (add '(' or add ')') that are constrained by the rules of well-formed parentheses. When a valid string of the correct length is formed, we add it to our results.

## 📝 Step-by-Step Algorithm
1.  **Initialization**:
    *   Create an empty `vector<string>` called `ans` to store all the valid parenthesis combinations.
    *   Initialize an empty string `curr` to build each combination.
    *   Start the recursive helper function with `n` (total pairs), `open = 0` (count of open parentheses used so far), `close = 0` (count of close parentheses used so far), and the `curr` string.

2.  **Base Case**:
    *   In the recursive helper function, check if the length of `curr` string is equal to `2 * n` (meaning we have used all `n` open and `n` close parentheses).
    *   If it is, this `curr` string is a complete, well-formed combination. Add it to the `ans` vector and return.

3.  **Recursive Steps**:
    *   **Option 1: Add an opening parenthesis `(`**:
        *   We can add an opening parenthesis if the number of open parentheses used so far (`open`) is less than the total allowed `n`.
        *   If `open < n`, append `(` to `curr`.
        *   Recursively call the helper function with `n`, `open + 1`, `close`, and the modified `curr`.
        *   **Backtrack**: After the recursive call returns, remove the `(` from `curr` (using `pop_back()`) to explore other possibilities.

    *   **Option 2: Add a closing parenthesis `)`**:
        *   We can add a closing parenthesis if the number of closing parentheses used so far (`close`) is less than the number of opening parentheses used so far (`open`). This condition ensures that the parentheses remain well-formed at every step (we never have more `)` than `(`).
        *   If `close < open`, append `)` to `curr`.
        *   Recursively call the helper function with `n`, `open`, `close + 1`, and the modified `curr`.
        *   **Backtrack**: After the recursive call returns, remove the `)` from `curr` (using `pop_back()`) to explore other possibilities.

4.  **Return**: After the initial call to the helper function completes, the `ans` vector will contain all valid combinations, which is then returned by the `generateParenthesis` function.

## 💻 Solution
```cpp
class Solution {
public:
    // This vector will store all the generated well-formed parenthesis strings.
    vector<string> ans;

    // Recursive helper function to generate parenthesis combinations.
    // n: The total number of pairs of parentheses required.
    // open: The current count of opening parentheses '(' used in 'curr'.
    // close: The current count of closing parentheses ')' used in 'curr'.
    // curr: The string representing the current combination being built.
    void solve(int n, int open, int close, string &curr) {

        // Base case: If the current string 'curr' has reached the target length (2*n),
        // it means we have successfully formed a well-formed parenthesis combination.
        if (curr.length() == 2 * n) {
            ans.push_back(curr); // Add it to our results.
            return;              // Stop this recursive path.
        }

        // Recursive Step 1: Try adding an opening parenthesis '('.
        // We can add an opening parenthesis if we haven't used all 'n' allowed opening parentheses yet.
        if (open < n) {
            curr.push_back('('); // Add '(' to the current string.
            // Recursively call solve, incrementing the 'open' count.
            solve(n, open + 1, close, curr);
            curr.pop_back();     // Backtrack: Remove '(' to explore other possibilities.
        }

        // Recursive Step 2: Try adding a closing parenthesis ')'.
        // We can add a closing parenthesis only if the number of closing parentheses
        // is strictly less than the number of opening parentheses.
        // This ensures that the parentheses remain well-formed at every step
        // (i.e., we don't close a parenthesis that hasn't been opened).
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
        return ans; // Return the vector containing all generated combinations.
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(C_n * 2n) | There are C_n (the nth Catalan number) valid parenthesis sequences. Each sequence has a length of 2n. Generating each sequence involves O(2n) operations (appending/popping characters). C_n grows approximately as 4^n / (n^(3/2) * sqrt(pi)). |
| **Space** | O(C_n * 2n) | The `ans` vector stores C_n strings, each of length 2n. Additionally, the maximum depth of the recursion stack is 2n (for building a string of length 2n). |

## 🔗 Related Problems
- 17. Letter Combinations of a Phone Number
- 78. Subsets
- 46. Permutations