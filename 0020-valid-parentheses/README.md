# 0020-valid-parentheses

## 📋 Problem Description
Given a string `s` consisting only of the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is considered valid if it satisfies the following three conditions:
1.  **Matching Types**: Every open bracket must be closed by the *same type* of bracket. For example, '(' must be closed by ')', not ']' or '}'.
2.  **Correct Order**: Open brackets must be closed in the *correct order*. For instance, `([)]` is invalid because the `(` is closed by `)` before the `[` is closed by `]`.
3.  **Correspondence**: Every close bracket must have a corresponding open bracket of the same type.

The function should return `true` if the string is valid, and `false` otherwise.

## 🔍 Examples
```
Input:  s = "()"
Output: true
Explanation: The opening parenthesis is correctly closed by a matching closing parenthesis.
```

```
Input:  s = "()[]{}"
Output: true
Explanation: All opening brackets are correctly closed by their matching types in the correct order.
```

```
Input:  s = "(]"
Output: false
Explanation: The open bracket '(' is not closed by the same type of bracket; it's closed by ']'.
```

```
Input:  s = "([)]"
Output: false
Explanation: The open bracket '[' is closed by ')' before the open bracket '(' is closed by ']'. The order is incorrect.
```

## 📌 Constraints
*   `1 <= s.length <= 10^4`
*   `s` consists of parentheses only `'()[]{}'`.

## 🤔 Understanding the Problem
This problem asks us to validate the structure of a string composed solely of various types of parentheses. It's not enough to simply count opening and closing brackets; their nesting and sequence are crucial. We need to ensure that every opening bracket has a corresponding closing bracket of the *same type*, and that these pairs are properly nested, meaning the most recently opened bracket must be the first one closed.

## 💡 Core Idea
The core idea is that when an opening bracket is encountered, its corresponding closing bracket must appear *later*, and any brackets opened *after* it must be closed *before* it. This Last-In, First-Out (LIFO) behavior is a classic indicator for using a Stack data structure.

## 🧠 Approach — Stack
A Stack is the ideal data structure for solving this problem because it perfectly models the Last-In, First-Out (LIFO) nature of correctly matched parentheses. When we encounter an opening bracket, we push it onto the stack, signifying that we expect to see its corresponding closing bracket later. When a closing bracket is encountered, we check if the most recently opened (top of the stack) bracket is its matching pair. If they match, they form a valid pair, and we pop the opening bracket from the stack. If they don't match, or if the stack is empty, the string is invalid.

## 📝 Step-by-Step Algorithm
1.  **Initialize Stack**: Create an empty stack of characters. This stack will store all encountered opening brackets that are yet to be closed.
2.  **Iterate Through String**: Go through each character `c` in the input string `s` from left to right.
3.  **Handle Opening Brackets**: If `c` is an opening bracket ('(', '{', or '['), push it onto the stack. This signifies that we've opened a bracket and are waiting for its corresponding closing bracket.
4.  **Handle Closing Brackets**: If `c` is a closing bracket (')', '}', or ']'):
    *   **Check for Empty Stack**: First, check if the stack is empty. If it is, it means we've encountered a closing bracket without any corresponding open bracket. This makes the string invalid, so immediately return `false`.
    *   **Check for Match**: If the stack is not empty, look at the character at the top of the stack (without removing it). This character represents the most recently opened, unclosed bracket.
        *   If `c` is ')' and the stack top is '(', they form a valid pair. Pop the top element from the stack.
        *   If `c` is ']' and the stack top is '[', they form a valid pair. Pop the top element from the stack.
        *   If `c` is '}' and the stack top is '{', they form a valid pair. Pop the top element from the stack.
    *   **Handle Mismatch**: If `c` is a closing bracket but it does not match the type of the opening bracket at the stack top (e.g., `c` is ')' but stack top is '['), then the brackets are mismatched or out of order. The string is invalid, so immediately return `false`.
5.  **Final Check**: After processing all characters in the string:
    *   If the stack is empty, it means every opening bracket found its corresponding closing bracket in the correct order. The string is valid, so return `true`.
    *   If the stack is not empty, it means there are one or more unmatched opening brackets left (e.g., `"{["`). The string is invalid, so return `false`.

## 💻 Solution

```cpp
#include <string> // Required for std::string
#include <stack>  // Required for std::stack

class Solution {
public:
    bool isValid(std::string s_input) { // Renamed parameter to avoid shadowing std::string
        // Declare a stack locally within the function.
        // This ensures that the stack is fresh for each call to isValid,
        // preventing state from previous calls from affecting current results.
        std::stack<char> s; 
        
        // Iterate through each character in the input string
        for (int i = 0; i < s_input.length(); i++) {
            char current_char = s_input[i];

            // If the current character is an opening bracket, push it onto the stack.
            // These are the brackets we expect to close later.
            if (current_char == '(' || current_char == '{' || current_char == '[') {
                s.push(current_char);
            } 
            // If the current character is a closing bracket
            else {
                // If the stack is empty, it means we encountered a closing bracket
                // without any corresponding open bracket. This is an invalid scenario.
                if (s.empty()) {
                    return false;
                }

                // Check if the current closing bracket matches the top of the stack.
                // The stack's top element is the most recently opened, unmatched bracket.
                // We check for type match: '(' with ')', '[' with ']', '{' with '}'.
                if ((s.top() == '(' && current_char == ')') ||
                    (s.top() == '[' && current_char == ']') ||
                    (s.top() == '{' && current_char == '}')) {
                    // If they match, it means the pair is valid and correctly ordered.
                    // Pop the opening bracket from the stack as it has now been closed.
                    s.pop();
                } 
                // If the current closing bracket does not match the type of the
                // opening bracket at the stack's top, then the parentheses are
                // mismatched or out of order (e.g., '([)]'). This is invalid.
                else {
                    return false;
                }
            }
        }

        // After iterating through the entire string:
        // If the stack is empty, it means all opening brackets found their
        // corresponding closing brackets in the correct order. The string is valid.
        // If the stack is not empty, it means there are unmatched opening brackets left
        // (e.g., "({"). The string is invalid.
        return s.empty();
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the input string once. Each character is processed with constant-time stack operations (push, pop, top, empty). N is the length of the string. |
| **Space** | O(N) | In the worst-case scenario (e.g., a string like "(((((" or "((()))"), all opening brackets might be pushed onto the stack. The maximum size of the stack can be N/2, which is proportional to N. |

## 🔗 Related Problems
- 150. Evaluate Reverse Polish Notation
- 739. Daily Temperatures
- 496. Next Greater Element I