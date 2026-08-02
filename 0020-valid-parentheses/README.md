# 0020-valid-parentheses

## 📋 Problem Description
Given a string `s` consisting only of the characters `'('`, `')'`, `'{'`, `'}'`, `'['`, and `']'`, determine if the input string is "valid".

An input string is considered valid if it satisfies the following three conditions:
1.  **Matching Types**: Every open bracket must be closed by the same type of bracket. For example, `'('` must be closed by `')'`, not `']'` or `'}'`.
2.  **Correct Order**: Open brackets must be closed in the correct order. For instance, `([)]` is invalid because the `(` is closed by `)` before the `[` is closed by `]`.
3.  **Correspondence**: Every close bracket must have a corresponding open bracket of the same type.

The function should return `true` if the string is valid, and `false` otherwise.

## 🔍 Examples
```
Input:  s = "()"
Output: true
Explanation: The single pair of parentheses is correctly matched and ordered.
```

```
Input:  s = "(]"
Output: false
Explanation: An opening parenthesis '(' is closed by a square bracket ']', which is a mismatch in type.
```

```
Input:  s = "([)]"
Output: false
Explanation: Although all brackets have corresponding types, the order is incorrect. The '(' is closed by ')' before the '[' is closed by ']'.
```

## 📌 Constraints
*   `1 <= s.length <= 10^4`
*   `s` consists only of parentheses characters: `'('`, `')'`, `'{'`, `'}'`, `'['`, `']'`.

## 🤔 Understanding the Problem
This problem asks us to validate the structure of a string composed solely of various types of brackets. It's not just about counting matching pairs; the crucial aspect is the *order* and *nesting* of these brackets. A valid string implies that every opening bracket has a corresponding closing bracket of the same type, and they are closed in the correct sequence, respecting the nesting hierarchy. This means the most recently opened bracket must be the first one to be closed.

## 💡 Core Idea
The key insight is that when we encounter an opening bracket, we expect its corresponding closing bracket to appear *later*. When we encounter a closing bracket, it must match the *most recently opened* and *still unclosed* bracket. This "last-in, first-out" (LIFO) behavior is a classic indicator for using a stack data structure.

## 🧠 Approach — Stack
The algorithm pattern used here is a **Stack**.
A stack is a perfect fit for this problem because it naturally handles the "last-in, first-out" requirement for matching parentheses. When we encounter an opening bracket, we push it onto the stack, essentially marking it as "awaiting closure." When we encounter a closing bracket, we need to check if it correctly closes the *most recently opened* bracket. The stack's `top()` operation allows us to inspect this most recent opening bracket, and `pop()` allows us to remove it once it's successfully matched, simulating its closure.

## 📝 Step-by-Step Algorithm
1.  **Initialize an empty stack**: Create a stack (e.g., `std::stack<char>` in C++) to store opening brackets.
2.  **Iterate through the string**: Process each character `c` in the input string `s` from left to right.
3.  **Handle opening brackets**: If `c` is an opening bracket (`(`, `{`, or `[`):
    *   Push `c` onto the stack. This signifies that we've encountered an open bracket that needs to be closed later.
4.  **Handle closing brackets**: If `c` is a closing bracket (`)`, `}`, or `]`):
    *   **Check for empty stack**: First, check if the stack is empty. If it is, it means we've found a closing bracket without any corresponding open bracket. In this case, the string is invalid, so immediately return `false`.
    *   **Check for match**: If the stack is not empty, look at the character at the `top()` of the stack (this is the most recently opened, unclosed bracket).
        *   If `c` is `)` and `s.top()` is `(`, they form a valid pair.
        *   If `c` is `]` and `s.top()` is `[`, they form a valid pair.
        *   If `c` is `}` and `s.top()` is `{`, they form a valid pair.
        *   If any of these conditions are met, pop the top element from the stack. This signifies that the opening bracket has found its match and is now closed.
    *   **Handle mismatch**: If `c` does not match the `s.top()` character (e.g., `s.top()` is `(` but `c` is `]` or `}`), it means there's a type mismatch or incorrect order. The string is invalid, so immediately return `false`.
5.  **Final check**: After iterating through all characters in the string:
    *   If the stack is empty, it means every opening bracket found its corresponding closing bracket in the correct order. The string is valid, so return `true`.
    *   If the stack is not empty, it means there are one or more opening brackets that were never closed. The string is invalid, so return `false`.

## 💻 Solution
```cpp
#include <string> // Required for std::string
#include <stack>  // Required for std::stack

class Solution {
public:
    // Declare a stack as a member variable of the class.
    // This stack will be used to keep track of open brackets encountered so far.
    // Note: If the Solution object were reused across multiple test cases without re-initialization,
    // this stack would retain its state. For typical LeetCode execution, a new Solution object
    // is often created per test case, or the stack is cleared implicitly.
    // Declaring it inside the isValid function would ensure it's always fresh.
    std::stack<char> s;

    bool isValid(std::string input_string) { // Renamed parameter from 'string' to 'input_string' for clarity
                                             // to avoid conflict with std::string type name in comments.
                                             // The original code used 'string' as the parameter name.
        // Iterate through each character in the input string.
        for (int i = 0; i < input_string.length(); i++) {
            // If the current character is an opening bracket, push it onto the stack.
            // This marks it as an unclosed bracket that we expect to see closed later.
            if (input_string[i] == '(' || input_string[i] == '{' || input_string[i] == '[') {
                s.push(input_string[i]);
            }
            // If the current character is a closing bracket.
            else {
                // First, check if the stack is empty.
                // If it is, we've encountered a closing bracket without any corresponding
                // open bracket to match it. This makes the string invalid.
                if (s.empty()) { // Using s.empty() is equivalent to s.size() == 0
                    return false;
                }

                // If the stack is not empty, check if the current closing bracket
                // matches the most recently opened bracket (which is at the top of the stack).
                if ((s.top() == '(' && input_string[i] == ')') || // Check for '()' pair
                    (s.top() == '[' && input_string[i] == ']') || // Check for '[]' pair
                    (s.top() == '{' && input_string[i] == '}')) { // Check for '{}' pair
                    // If they match, pop the opening bracket from the stack.
                    // This signifies that the opening bracket has been successfully closed.
                    s.pop();
                }
                // If the closing bracket does not match the top of the stack,
                // it means there's either a type mismatch (e.g., '{]') or incorrect order.
                // In either case, the string is invalid.
                else {
                    return false;
                }
            }
        }

        // After iterating through the entire string, perform a final check.
        // If the stack is empty, it means all opening brackets found their
        // corresponding closing brackets and were popped. The string is valid.
        // If the stack is not empty, it means there are unclosed opening brackets
        // remaining on the stack. The string is invalid.
        return s.empty(); // Using s.empty() is equivalent to s.size() == 0
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the input string once. Each stack operation (push, pop, top, empty) takes O(1) time. |
| **Space** | O(N) | In the worst-case scenario (e.g., a string like `(((((((((`), the stack could store all N opening brackets. |

## 🔗 Related Problems
-   22. Generate Parentheses
-   150. Evaluate Reverse Polish Notation
-   71. Simplify Path