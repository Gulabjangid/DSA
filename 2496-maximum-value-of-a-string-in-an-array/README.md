# 2496-maximum-value-of-a-string-in-an-array

## 📋 Problem Description
You are given an array of alphanumeric strings, `strs`. The "value" of each string is determined by specific rules:
1.  If a string consists **only** of digits (e.g., "123", "007"), its value is its numeric representation in base 10.
2.  If a string contains **any** non-digit characters (e.g., "alic3", "bob"), its value is simply its length.

Your task is to find and return the maximum value among all strings in the given array `strs`.

## 🔍 Examples
```
Input: strs = ["alic3","bob","3","4","00000"]
Output: 5
Explanation: 
- "alic3" contains letters and digits, so its value is its length, which is 5.
- "bob" contains only letters, so its value is its length, which is 3.
- "3" contains only digits, so its value is its numeric equivalent, which is 3.
- "4" contains only digits, so its value is its numeric equivalent, which is 4.
- "00000" contains only digits, so its value is its numeric equivalent, which is 0.
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
Each string has a value of 1. The maximum value is 1.
```

## 📌 Constraints
*   `1 <= strs.length <= 100`
*   `1 <= strs[i].length <= 9`
*   `strs[i]` consists of only lowercase English letters and digits.

## 🤔 Understanding the Problem
The problem asks us to process an array of strings, where each string's "value" is calculated based on whether it's purely numeric or contains letters. We then need to find the largest of these calculated values. The core challenge is correctly identifying if a string is composed *only* of digits and then applying the appropriate value calculation (numeric conversion vs. length). We must handle cases like leading zeros in numeric strings (e.g., "00000" evaluates to 0, not 5).

## 💡 Core Idea
The core idea is to iterate through each string in the input array, apply the two distinct value calculation rules based on its content (digit-only vs. mixed characters), and keep track of the maximum value encountered during this process.

## 🧠 Approach — Iterative Processing / Direct Simulation
This problem can be solved using a direct iterative processing approach, often referred to as simulation. The problem statement provides clear, unambiguous rules for determining the value of each string. We simply need to simulate this process: iterate through the array of strings, and for each string, apply the specified logic to determine its value. There are no complex data structures or advanced algorithms required, just a straightforward application of the rules. This pattern fits perfectly because the task is to perform a specific operation on each element of a collection and aggregate a result (the maximum).

## 📝 Step-by-Step Algorithm
1.  Initialize an integer variable, `maxValue`, to `0`. This variable will store the highest value found across all strings.
2.  Start a loop that iterates through each string `s` in the input array `strs`.
3.  Inside this loop, for the current string `s`:
    a.  Initialize a boolean flag, `isDigitOnly`, to `true`. This flag will help us determine if the string consists exclusively of digits.
    b.  Start an inner loop that iterates through each character `c` within the current string `s`.
    c.  For each character `c`, check if it is *not* a digit. Most programming languages provide a built-in function like `isdigit()` for this.
    d.  If a character `c` is found that is *not* a digit, set `isDigitOnly` to `false` and immediately `break` out of this inner character loop. There's no need to check further characters in `s` because we already know it's not purely numeric.
    e.  After the inner loop finishes (either by checking all characters or by breaking early):
        i.  If `isDigitOnly` is still `true`, it means the string `s` consists entirely of digits. Convert `s` to its integer equivalent (e.g., using `stoi()` in C++). Store this result in a temporary variable, `currentValue`.
        ii. If `isDigitOnly` is `false`, it means the string `s` contains at least one letter. Its value is its length. Get the length of `s` (e.g., using `s.length()` in C++). Store this result in `currentValue`.
    f.  Compare `currentValue` with `maxValue`. Update `maxValue` to be the larger of the two.
4.  After the outer loop has processed all strings in `strs`, return the final `maxValue`.

## 💻 Solution

```cpp
class Solution {
public:
    int maximumValue(vector<string>& strs) {
        int ans = 0; // Initialize 'ans' to store the maximum value found so far.
                     // Since string lengths are at least 1 and numeric values are non-negative,
                     // 0 is a safe starting point for the maximum.

        // Iterate through each string in the input vector 'strs'.
        for (string s : strs) {
            bool digitOnly = true; // Flag to check if the current string 's' consists only of digits.
                                   // We assume it's digit-only initially and will set to false if a non-digit is found.

            // Iterate through each character in the current string 's'.
            for (char c : s) {
                // Check if the character is NOT a digit using the isdigit() function.
                if (!isdigit(c)) {
                    digitOnly = false; // If a non-digit character is found, set the flag to false.
                    break;             // No need to check further characters in this string;
                                       // its value will be its length, regardless of other characters.
                }
            }

            int currentValue; // Variable to store the calculated value for the current string 's'.

            // Based on whether the string was determined to be digit-only or not, calculate its value.
            if (digitOnly) {
                // If 's' consists only of digits, convert it to an integer.
                // stoi() is a standard library function to convert a string to an integer.
                currentValue = stoi(s); 
            } else {
                // If 's' contains any non-digit characters, its value is its length.
                // .length() returns the number of characters in the string.
                currentValue = s.length(); 
            }

            // Update 'ans' with the maximum of its current value and the 'currentValue' of string 's'.
            // This ensures 'ans' always holds the highest value encountered so far.
            ans = max(ans, currentValue);
        }

        return ans; // Return the overall maximum value found across all strings in the input array.
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N * L) | The outer loop runs `N` times (for each string). The inner loop iterates up to `L` characters for each string. The `stoi` operation also takes `O(L)` time in the worst case. |
| **Space** | O(1) | We only use a few constant-size variables (`ans`, `digitOnly`, `currentValue`) that do not scale with the input size. |
*   `N` is the number of strings in the input array `strs` (`strs.length`).
*   `L` is the maximum possible length of any string in `strs` (`strs[i].length`).

## 🔗 Related Problems
- 125. Valid Palindrome
- 412. Fizz Buzz
- 1678. Goal Parser Interpretation