# 2496-maximum-value-of-a-string-in-an-array

## 📋 Problem Description
You are given an array of alphanumeric strings, `strs`.
The "value" of an alphanumeric string is defined by two rules:
1.  If the string consists *only* of digits (0-9), its value is its numeric representation in base 10.
2.  Otherwise (if it contains any non-digit characters, such as letters), its value is its length.

Your task is to find and return the maximum value among all strings in the given array `strs`.

**Input:** An array of strings, `strs`.
**Output:** An integer representing the maximum calculated value.

## 🔍 Examples
```
Input: strs = ["alic3","bob","3","4","00000"]
Output: 5
Explanation:
- "alic3" contains letters and digits, so its value is its length, 5.
- "bob" contains only letters, so its value is its length, 3.
- "3" contains only digits, so its value is its numeric equivalent, 3.
- "4" contains only digits, so its value is its numeric equivalent, 4.
- "00000" contains only digits, so its value is its numeric equivalent, 0.
The maximum value among [5, 3, 3, 4, 0] is 5.
```

```
Input: strs = ["1","01","001","0001"]
Output: 1
Explanation:
- "1" consists only of digits, value is 1.
- "01" consists only of digits, value is 1.
- "001" consists only of digits, value is 1.
- "0001" consists only of digits, value is 1.
The maximum value among [1, 1, 1, 1] is 1.
```

## 📌 Constraints
*   `1 <= strs.length <= 100`
*   `1 <= strs[i].length <= 9`
*   `strs[i]` consists of only lowercase English letters and digits.

## 🤔 Understanding the Problem
The problem asks us to process a list of strings, each of which can be either purely numeric or contain a mix of letters and digits. For each string, we need to apply a specific rule to determine its "value." The core task is to correctly identify whether a string is purely numeric or not, then apply the corresponding value calculation (numeric conversion or length), and finally keep track of the largest value encountered across all strings. The small constraints on string length and array size suggest that a straightforward approach will be efficient enough.

## 💡 Core Idea
The core idea is to iterate through each string in the input array, determine if it consists solely of digits, calculate its value based on the defined rules, and continuously update a running maximum value.

## 🧠 Approach — Iterative Simulation
This problem can be solved using a direct iterative simulation approach. We simply follow the rules given in the problem statement step-by-step for each string. There are no complex data structures or advanced algorithms required, as the constraints on string length and array size are small, allowing for a straightforward traversal and calculation. For each string, we first determine its type (all digits or mixed) by iterating through its characters, then apply the corresponding value calculation, and finally compare it with the current maximum.

## 📝 Step-by-Step Algorithm
1.  Initialize an integer variable `maxValue` to 0. This variable will store the maximum value found among all strings processed so far.
2.  Begin a loop that iterates through each string `s` in the input array `strs`.
    a.  Inside this loop, for the current string `s`, initialize a boolean flag `isNumeric` to `true`. This flag will help us determine if the string consists only of digits.
    b.  Start another inner loop that iterates through each character `c` in the current string `s`.
        i.  For each character `c`, check if it is *not* a digit. A utility function like `isdigit(c)` can be used for this.
        ii. If `c` is found to be a non-digit character, set `isNumeric` to `false` and immediately `break` out of this inner character loop. There's no need to check further characters in `s` because we already know it's not purely numeric.
    c.  After the inner loop finishes (either by checking all characters or by breaking early):
        i.  If `isNumeric` is still `true`, it means the string `s` consists only of digits. Its value is its numeric representation. Convert `s` to an integer (e.g., using `std::stoi(s)` in C++) and store it in a temporary `currentValue` variable.
        ii. If `isNumeric` is `false`, it means the string `s` contains at least one non-digit character. Its value is its length. Get the length of `s` (e.g., `s.length()`) and store it in `currentValue`.
    d.  Compare `currentValue` with `maxValue`. Update `maxValue` to be the larger of the two (i.e., `maxValue = max(maxValue, currentValue)`).
3.  After the outer loop has finished processing all strings in `strs`, return the final `maxValue`.

## 💻 Solution

```cpp
#include <vector> // Required for std::vector
#include <string> // Required for std::string, std::stoi
#include <algorithm> // Required for std::max
#include <cctype> // Required for isdigit

class Solution {
public:
    int maximumValue(std::vector<std::string>& strs) {
        int ans = 0; // Initialize 'ans' to 0, which will store the maximum value found.
                     // Since string lengths are at least 1 and numeric values are non-negative, 0 is a safe starting point.

        // Iterate through each string in the input vector 'strs'.
        for (std::string s : strs) {
            bool digitOnly = true; // Flag to track if the current string 's' consists only of digits.
                                   // Assume it's digit-only initially.

            // Iterate through each character of the current string 's'.
            for (char c : s) {
                // Check if the character 'c' is NOT a digit.
                if (!std::isdigit(c)) {
                    digitOnly = false; // If a non-digit character is found, set the flag to false.
                    break;             // No need to check further characters in this string; it's not digit-only.
                }
            }

            int currentValue; // Variable to store the calculated value for the current string 's'.

            // Determine the value based on whether the string was digit-only or not.
            if (digitOnly) {
                // If the string consists only of digits, convert it to an integer.
                // std::stoi converts a string to an integer.
                currentValue = std::stoi(s);
            } else {
                // If the string contains non-digit characters, its value is its length.
                currentValue = s.length();
            }

            // Update 'ans' with the maximum value found so far.
            // std::max returns the larger of the two arguments.
            ans = std::max(ans, currentValue);
        }

        return ans; // Return the overall maximum value.
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N * L) | The outer loop iterates `N` times (where `N` is `strs.length`). Inside, we iterate through each character of a string `s` (up to `L` characters, where `L` is `strs[i].length`) to check if it's numeric. If numeric, `std::stoi` also takes `O(L)` time. Thus, each string takes `O(L)` time, leading to `N * O(L)` total. |
| **Space** | O(1) | We only use a few constant-size variables (`ans`, `digitOnly`, `currentValue`) regardless of the input size. No additional data structures are created that scale with `N` or `L`. |

## 🔗 Related Problems
- 2000. Reverse Prefix of Word
- 2108. Find First Palindromic String in the Array
- 2418. Sort the People