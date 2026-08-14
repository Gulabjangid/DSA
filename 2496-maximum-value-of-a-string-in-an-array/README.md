# 2496-maximum-value-of-a-string-in-an-array

## 📋 Problem Description
You are given an array of alphanumeric strings, `strs`.
The **value** of a string is defined based on its content:
*   If the string consists **only** of digits, its value is its numeric representation in base 10.
*   Otherwise (if it contains at least one letter), its value is its length.

Your task is to return the **maximum value** among all strings in the given array `strs`.

**Input:** A `vector<string>` named `strs`.
**Output:** An `int` representing the maximum calculated value.

## 🔍 Examples
```
Input:  strs = ["alic3","bob","3","4","00000"]
Output: 5
Explanation: 
- "alic3" contains letters and digits, so its value is its length, 5.
- "bob" contains only letters, so its value is its length, 3.
- "3" contains only digits, so its value is its numeric equivalent, 3.
- "4" contains only digits, so its value is its numeric equivalent, 4.
- "00000" contains only digits, so its value is its numeric equivalent, 0.
The maximum value among 5, 3, 3, 4, 0 is 5.
```

```
Input:  strs = ["1","01","001","0001"]
Output: 1
Explanation: 
- "1" consists only of digits, value is 1.
- "01" consists only of digits, value is 1.
- "001" consists only of digits, value is 1.
- "0001" consists only of digits, value is 1.
The maximum value is 1.
```

## 📌 Constraints
*   `1 <= strs.length <= 100`
*   `1 <= strs[i].length <= 9`
*   `strs[i]` consists of only lowercase English letters and digits.

## 🤔 Understanding the Problem
The problem asks us to iterate through a list of strings and, for each string, determine its "value" based on a specific rule. The core challenge is correctly applying this rule: checking if a string is purely numeric or contains letters, and then calculating either its numeric value or its length. Finally, we need to keep track of the largest value encountered across all strings. It's a straightforward application of conditional logic and string processing.

## 💡 Core Idea
The central idea is to process each string individually according to the given rules: first determine if it's purely numeric, then calculate its value, and finally update a running maximum.

## 🧠 Approach — Iterative Scan
This problem can be solved using an **Iterative Scan** approach. This pattern involves iterating through each element of an array or list and performing a specific operation or check on each element. It fits this problem perfectly because we need to examine every string in the `strs` array, apply a set of rules to calculate its value, and then compare this value against a running maximum. There's no complex data structure or advanced algorithm required; a simple loop suffices to process all inputs sequentially.

## 📝 Step-by-Step Algorithm
1.  Initialize an integer variable, `maximumValue`, to `0`. This variable will store the highest value found so far.
2.  Iterate through each string `s` in the input array `strs`.
3.  For each string `s`:
    a.  Initialize a boolean variable, `isPurelyNumeric`, to `true`. This flag will help us determine if the string consists only of digits.
    b.  Iterate through each character `c` in the current string `s`.
    c.  Inside this inner loop, check if the character `c` is *not* a digit (e.g., using `!isdigit(c)` in C++).
    d.  If a non-digit character is found, set `isPurelyNumeric` to `false` and immediately break out of this inner loop (no need to check further characters in this string, as we already know it's not purely numeric).
    e.  After checking all characters in `s` (or breaking early):
        i.  If `isPurelyNumeric` is still `true`, it means the string `s` consists only of digits. Convert `s` to an integer (e.g., using `stoi(s)` in C++). This integer is the string's value.
        ii. If `isPurelyNumeric` is `false`, it means the string `s` contains at least one letter. Its value is its length (e.g., `s.length()` in C++).
    f.  Compare the calculated value for the current string with `maximumValue`. Update `maximumValue` to be the larger of the two.
4.  After iterating through all strings in `strs`, return the final `maximumValue`.

## 💻 Solution
```cpp
#include <vector> // Required for std::vector
#include <string> // Required for std::string
#include <algorithm> // Required for std::max
#include <cctype> // Required for isdigit

class Solution {
public:
    int maximumValue(std::vector<std::string>& strs) {
        // Initialize 'ans' to 0. This variable will store the maximum value found
        // across all strings. Since values are non-negative (length >= 1, numeric >= 0),
        // 0 is a safe starting point.
        int ans = 0;

        // Iterate through each string in the input vector 'strs'.
        // 's' will be a copy of the current string from 'strs'.
        for (std::string s : strs) {
            // Initialize a boolean flag to true. We assume the string is purely numeric
            // until we find a non-digit character.
            bool isPurelyNumeric = true;

            // Iterate through each character 'c' in the current string 's'.
            for (char c : s) {
                // Check if the current character 'c' is NOT a digit.
                if (!std::isdigit(c)) {
                    // If a non-digit character is found, the string is not purely numeric.
                    isPurelyNumeric = false;
                    // No need to check further characters in this string, so break the inner loop.
                    break;
                }
            }

            // Declare an integer variable to store the calculated value for the current string.
            int currentValue;

            // Based on whether the string was purely numeric or not, calculate its value.
            if (isPurelyNumeric) {
                // If the string consists only of digits, convert it to an integer.
                // std::stoi converts a string to an integer.
                currentValue = std::stoi(s);
            } else {
                // If the string contains letters, its value is its length.
                currentValue = s.length();
            }

            // Update 'ans' to be the maximum of its current value and the 'currentValue'
            // calculated for the string 's'.
            ans = std::max(ans, currentValue);
        }

        // After processing all strings, return the overall maximum value found.
        return ans;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N * L) | The outer loop runs `N` times (for each string). The inner loop iterates up to `L` characters for each string, and `stoi` also takes `O(L)` time. `N` is `strs.length`, `L` is `strs[i].length`. |
| **Space** | O(L) | We use a few constant space variables (`ans`, `isPurelyNumeric`, `currentValue`). The string `s` in the range-based for loop creates a temporary copy of the string, which takes `O(L)` space for the longest string. If we consider auxiliary space *excluding* temporary copies, it's O(1). |

## 🔗 Related Problems
- 1108. Defanging an IP Address
- 1678. Goal Parser Interpretation
- 2011. Final Value of Variable After Performing Operations