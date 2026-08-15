# 1796-second-largest-digit-in-a-string

## 📋 Problem Description
Given an alphanumeric string `s`, the task is to find and return the **second largest** distinct numerical digit that appears in `s`. An alphanumeric string consists of lowercase English letters and digits (0-9). If there is no second largest distinct digit (e.g., the string contains fewer than two distinct digits), the function should return -1.

The function receives one input:
*   `s`: A string consisting of lowercase English letters and digits.

The function must return:
*   An integer representing the second largest distinct digit, or -1 if it does not exist.

## 🔍 Examples
```
Input: s = "dfa12321afd"
Output: 2
Explanation: The digits that appear in s are [1, 2, 3]. The distinct digits are [1, 2, 3]. The largest is 3, and the second largest is 2.

Input: s = "abc1111"
Output: -1
Explanation: The only digit that appears in s is [1]. Since there is only one distinct digit, there is no second largest digit.

Input: s = "000"
Output: -1
Explanation: The only digit that appears in s is [0]. Since there is only one distinct digit, there is no second largest digit.
```

## 📌 Constraints
*   `1 <= s.length <= 500`
*   `s` consists of only lowercase English letters and digits.

## 🤔 Understanding the Problem
The problem asks us to extract all numerical digits from a given string and then find the second largest among these digits. A crucial detail is that we need the "second largest *distinct*" digit. This means if a digit appears multiple times (e.g., '2' in "1223"), it only counts as one unique digit. We must also handle edge cases where there are no digits, or only one distinct digit, in which case we should return -1. The string can contain both letters and digits, so we need to filter out the letters.

## 💡 Core Idea
The core idea is to iterate through the string once, keeping track of the largest and second largest *distinct* digits encountered so far using two variables. This allows us to find the desired digits without storing all digits in a separate collection or sorting them.

## 🧠 Approach — Single Pass Iteration
This problem can be efficiently solved using a **Single Pass Iteration** approach. This pattern is suitable because we need to examine each character of the string to identify digits and determine their relative magnitudes. By iterating through the string just once, we can maintain two variables that continuously track the largest and second largest distinct digits found up to the current point. This avoids the overhead of collecting all digits into a data structure (like a set or vector) and then processing them, leading to an optimal time complexity.

## 📝 Step-by-Step Algorithm
1.  Initialize two integer variables: `frist` and `second`. Set both to -1.
    *   `frist` will store the largest distinct digit found so far.
    *   `second` will store the second largest distinct digit found so far.
    *   Initializing them to -1 ensures that any valid digit (0-9) will be greater than these initial values, allowing for correct updates. It also serves as the default return value if no second largest digit is found.
2.  Iterate through each character `c` in the input string `s` from beginning to end.
3.  For each character `c`:
    a.  Check if `c` is a numerical digit. Most languages provide a utility function like `isdigit(c)` for this.
    b.  If `c` is a digit:
        i.   Convert the character `c` to its integer value. For example, in C++, `c - '0'` converts '0' to 0, '1' to 1, etc. Let's call this integer value `val`.
        ii.  Compare `val` with `frist`:
            *   If `val` is strictly greater than `frist`: This means we've found a new largest digit. The current `frist` value now becomes the `second` largest, and `val` becomes the new `frist`.
            *   Else (if `val` is not greater than `frist`): Check if `val` is strictly greater than `second` AND `val` is NOT equal to `frist`. This condition ensures that `val` is a new second largest digit (it's smaller than `frist` but larger than `second`, and it's distinct from `frist`). If this condition is true, update `second` to `val`.
            *   If `val` is equal to `frist`, or smaller than `second`, or equal to `second`, no update is needed for `frist` or `second` in these specific conditions.
4.  After the loop finishes iterating through all characters in the string, the `second` variable will hold the second largest distinct digit found. If no second largest digit was found (e.g., the string contained no digits, or only one distinct digit), `second` will still be -1.
5.  Return the value of `second`.

## 💻 Solution
```cpp
class Solution {
public:
    int secondHighest(string s) {
        // Initialize 'frist' to store the largest digit found so far.
        // Initialize 'second' to store the second largest digit found so far.
        // Both are initialized to -1. This value is smaller than any possible digit (0-9),
        // ensuring that the first digit encountered will correctly update 'frist'.
        // It also serves as the default return value if no second largest digit exists.
        int frist = -1;
        int second = -1;

        // Iterate through each character in the input string 's'.
        for (char c : s) {
            // Check if the current character 'c' is a digit.
            // The isdigit() function returns true if c is a decimal digit character.
            if (isdigit(c)) {
                // Convert the character digit to its integer value.
                // For example, '5' - '0' results in the integer 5.
                int val = c - '0';

                // Case 1: The current digit 'val' is strictly greater than the current largest digit ('frist').
                // This means we have found a new largest digit.
                if (val > frist) {
                    // The previous 'frist' (which was the largest) now becomes the new 'second' largest.
                    second = frist;
                    // 'val' becomes the new 'frist' (largest).
                    frist = val;
                }
                // Case 2: 'val' is not greater than 'frist', but it might be the new second largest.
                // This condition checks two things:
                // 1. 'val' is strictly greater than the current 'second'.
                // 2. 'val' is NOT equal to 'frist'. This is crucial to ensure we only consider distinct digits.
                //    If 'val' was equal to 'frist', it's a duplicate of the largest digit, not a new second largest.
                else if (val > second && val != frist) {
                    // If both conditions are met, 'val' is the new second largest digit.
                    second = val;
                }
                // If 'val' is equal to 'frist', or smaller than 'second', or equal to 'second',
                // no update is needed for 'frist' or 'second' in these specific conditions.
            }
        }
        // After iterating through the entire string, 'second' will hold the second largest
        // distinct digit found. If no second largest digit was found (e.g., the string
        // contained fewer than two distinct digits), 'second' will still be -1.
        return second;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the input string `s` exactly once. `N` is the length of the string. Each character processing takes constant time. |
| **Space** | O(1) | We use a constant amount of extra space for the `frist` and `second` integer variables, regardless of the input string's length. |

## 🔗 Related Problems
- 414. Third Maximum Number
- 215. Kth Largest Element in an Array