# 0008-string-to-integer-atoi

## 📋 Problem Description
The task is to implement the `myAtoi(string s)` function, which converts a given string `s` into a 32-bit signed integer. The conversion process must adhere to a specific set of rules:

1.  **Whitespace**: The function should first ignore any leading whitespace characters (' ') in the string.
2.  **Signedness**: After skipping whitespace, the next character determines the sign of the number. If it's `'-'`, the number is negative. If it's `'+'`, the number is positive. If neither `'-'` nor `'+'` is present, the number is assumed to be positive. The function should then advance past this sign character (if present).
3.  **Conversion**: The function then reads consecutive digit characters ('0' through '9') to form the integer. Reading stops when a non-digit character is encountered or the end of the string is reached. Leading zeros among the digits should be ignored (e.g., "042" becomes 42). If no digits are read after determining the sign (or after whitespace if no sign was present), the result is 0.
4.  **Rounding (Overflow Handling)**: The final integer must fit within the 32-bit signed integer range, which is `[-2^31, 2^31 - 1]`.
    *   If the calculated integer is less than `-2^31`, it should be "rounded" (clamped) to `-2^31` (which is `INT_MIN`).
    *   If the calculated integer is greater than `2^31 - 1`, it should be "rounded" (clamped) to `2^31 - 1` (which is `INT_MAX`).

The function should return the resulting 32-bit signed integer.

## 🔍 Examples
```
Input:  s = "42"
Output: 42
Explanation:
1. No leading whitespace.
2. No sign character, so assumed positive.
3. "42" is read as 42.
4. 42 is within the 32-bit integer range.
```

```
Input:  s = "   -042"
Output: -42
Explanation:
1. Leading whitespace "   " is ignored.
2. '-' is read, indicating a negative number.
3. "042" is read as 42 (leading zero ignored).
4. -42 is within the 32-bit integer range.
```

```
Input:  s = "words and 987"
Output: 0
Explanation:
1. No leading whitespace.
2. The first non-whitespace character 'w' is not a digit, '+' or '-'.
3. No valid number can be formed, so the result is 0.
```

```
Input:  s = "2147483647"
Output: 2147483647
Explanation:
1. No leading whitespace or sign.
2. "2147483647" is read.
3. This is exactly INT_MAX, so it's returned.
```

```
Input:  s = "-91283472332"
Output: -2147483648
Explanation:
1. No leading whitespace.
2. '-' is read, indicating a negative number.
3. "91283472332" is read.
4. The calculated value -91283472332 is less than INT_MIN (-2147483648), so it is clamped to INT_MIN.
```

## 📌 Constraints
*   `0 <= s.length <= 200`
*   `s` consists of English letters (lower-case and upper-case), digits (`0-9`), `' '`, `'+'`, `'-'`, and `'.'`.

## 🤔 Understanding the Problem
This problem asks us to implement a custom string-to-integer conversion function, mimicking the behavior of `atoi` in C/C++. It's not just about parsing digits; it requires careful handling of various edge cases: leading whitespace, an optional sign, non-digit characters terminating the number, and crucially, integer overflow for 32-bit signed integers. The main challenge lies in correctly implementing these rules in sequence and preventing intermediate calculations from exceeding standard integer limits before the final clamping.

## 💡 Core Idea
The core idea is to process the string character by character, maintaining a state (e.g., skipping whitespace, parsing sign, parsing digits) and building the integer incrementally. The critical part is to use a `long` type for the accumulating result to safely perform intermediate calculations and then check for potential 32-bit integer overflow *after* each digit is processed, clamping the result if it exceeds `INT_MAX` or falls below `INT_MIN`.

## 🧠 Approach — Simulation / State Machine
This problem is best solved using a **Simulation** or **State Machine** approach. We process the input string character by character, transitioning through different "states": initially skipping whitespace, then determining the sign, and finally accumulating digits. This pattern fits because the rules are sequential and depend on the current character and previously processed characters. We don't need complex data structures or recursive calls; a single pass with a few state variables is sufficient to simulate the specified `atoi` algorithm. The primary challenge is managing the integer overflow checks correctly at each step of digit accumulation.

## 📝 Step-by-Step Algorithm

1.  **Initialization**:
    *   Initialize an integer `i` to 0, which will serve as our current reading index in the string `s`.
    *   Get the length of the string `s` and store it in `n`.

2.  **Skip Leading Whitespace**:
    *   Iterate `i` forward as long as `i` is less than `n` (within string bounds) and the character `s[i]` is a space (' '). This effectively skips all leading whitespace.

3.  **Determine Sign**:
    *   Initialize an integer `sign` to 1, assuming a positive number by default.
    *   If `i` is still less than `n` (meaning we haven't reached the end of the string after skipping whitespace):
        *   If `s[i]` is `'-'`, set `sign` to -1.
        *   If `s[i]` is `'+'`, `sign` remains 1.
        *   In either case (if `s[i]` was `'+'` or `'-'`), increment `i` to move past the sign character.

4.  **Read Digits and Handle Overflow**:
    *   Initialize a `long` variable `result` to 0. We use `long` to temporarily store the number as it's being built, preventing overflow during intermediate calculations before we check against `INT_MAX` and `INT_MIN`.
    *   Iterate `i` forward as long as `i` is less than `n` and the character `s[i]` is a digit ('0' through '9'):
        *   Convert the character `s[i]` to its integer value: `digit = s[i] - '0'`.
        *   Update `result`: `result = result * 10 + digit`. This appends the new digit to the number.
        *   **Overflow/Underflow Check**: After updating `result`, check if the number, when considering its `sign`, has exceeded the 32-bit integer range:
            *   If `sign * result` is greater than or equal to `INT_MAX` (the maximum 32-bit signed integer value), immediately return `INT_MAX`.
            *   If `sign * result` is less than or equal to `INT_MIN` (the minimum 32-bit signed integer value), immediately return `INT_MIN`.
        *   Increment `i` to move to the next character.

5.  **Return Final Result**:
    *   After the loop finishes (either because a non-digit character was found or the end of the string was reached), multiply the accumulated `result` by `sign` to apply the correct positive or negative sign.
    *   Return this final signed integer.

## 💻 Solution
```cpp
#include <string> // Required for string manipulation
#include <climits> // Required for INT_MAX and INT_MIN
#include <cctype> // Required for isdigit

class Solution {
public:
    int myAtoi(string s) {
        int i = 0; // Initialize an index to traverse the string
        int n = s.length(); // Get the length of the string

        // Step 1: Ignore any leading whitespace
        while (i < n && s[i] == ' ') {
            i++; // Move past the current whitespace character
        }

        // If we reached the end of the string (all whitespace or empty), return 0
        if (i == n) {
            return 0;
        }

        // Step 2: Determine the sign
        int sign = 1; // Default to positive
        if (s[i] == '+' || s[i] == '-') { // Check if the current character is a sign
            if (s[i] == '-') {
                sign = -1; // Set sign to negative if it's '-'
            }
            i++; // Move past the sign character
        }

        // Step 3: Read digits and handle potential overflow
        // Use long to store the result to prevent overflow during intermediate calculations
        // before checking against INT_MAX/INT_MIN.
        long result = 0; 
        while (i < n && isdigit(s[i])) { // Continue as long as we are within bounds and the character is a digit
            int digit = s[i] - '0'; // Convert character digit to its integer value (e.g., '5' -> 5)

            // Accumulate the number: multiply current result by 10 and add the new digit
            result = result * 10 + digit;

            // Step 4: Rounding (Overflow/Underflow check)
            // We check if the current 'result' (multiplied by 'sign') exceeds 32-bit integer limits.
            // Since 'result' is 'long', 'sign * result' will also be 'long' and won't overflow 'long'.
            // This allows us to safely compare against INT_MAX and INT_MIN.
            if (sign * result >= INT_MAX) {
                return INT_MAX; // If it exceeds INT_MAX, clamp to INT_MAX
            }
            if (sign * result <= INT_MIN) {
                return INT_MIN; // If it falls below INT_MIN, clamp to INT_MIN
            }
            
            i++; // Move to the next character
        }

        // After processing all digits, apply the determined sign and return the final integer
        // The result is guaranteed to be within 32-bit int range due to the checks above.
        return static_cast<int>(result * sign);
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the input string `s` once, where N is the length of `s`. Each character is visited at most a constant number of times (for whitespace, sign, and digits). |
| **Space** | O(1) | We use a few constant extra variables (`i`, `n`, `sign`, `result`, `digit`) regardless of the input string's length. |

## 🔗 Related Problems
- 151. Reverse Words in a String
- 415. Add Strings
- 6. Zigzag Conversion