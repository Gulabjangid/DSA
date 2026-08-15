# 1796-second-largest-digit-in-a-string

## 📋 Problem Description
Given an alphanumeric string `s`, the task is to find and return the **second largest** numerical digit that appears in `s`. An alphanumeric string consists of lowercase English letters and digits. If there is no second largest digit (e.g., the string contains fewer than two distinct digits), the function should return -1.

**Input**: An alphanumeric string `s`.
**Output**: An integer representing the second largest distinct digit, or -1 if it doesn't exist.

## 🔍 Examples
```
Input: s = "dfa12321afd"
Output: 2
Explanation: The digits that appear in s are [1, 2, 3]. The largest digit is 3, and the second largest is 2.
```

```
Input: s = "abc1111"
Output: -1
Explanation: The only digit that appears in s is [1]. Since there is only one distinct digit, there is no second largest digit.
```

```
Input: s = "00000"
Output: -1
Explanation: The only digit that appears in s is [0]. There is no second largest digit.
```

## 📌 Constraints
*   `1 <= s.length <= 500`
*   `s` consists of only lowercase English letters and digits.

## 🤔 Understanding the Problem
The problem asks us to extract all unique digits from a given string and then find the second largest among them. It's crucial to note that we are looking for the "second largest *distinct*" digit. This means if a digit appears multiple times, it's only counted once for the purpose of determining uniqueness and order. Edge cases include strings with no digits, strings with only one distinct digit, or strings where all digits are the same. In all these scenarios, the result should be -1.

## 💡 Core Idea
The core idea is to iterate through the string once, keeping track of the largest digit found so far and the second largest distinct digit found so far, updating them as new digits are encountered.

## 🧠 Approach — Two-Variable Tracking (Single Pass)
This problem can be efficiently solved using a "Two-Variable Tracking" approach within a single pass. We maintain two variables: one to store the largest digit encountered (`frist`) and another for the second largest distinct digit encountered (`second`). As we iterate through each character of the string, we first check if it's a digit. If it is, we compare it against our current `frist` and `second` values. The logic ensures that `frist` always holds the absolute largest digit, and `second` holds the largest digit that is strictly smaller than `frist`. This pattern is ideal because we only need to keep track of a fixed, small number of values (the top two) at any given time, avoiding the need for more complex data structures like sets or sorted lists.

## 📝 Step-by-Step Algorithm
1.  Initialize two integer variables, `frist` and `second`, both to -1. `frist` will store the largest digit found, and `second` will store the second largest distinct digit found. Initializing to -1 ensures that any valid digit (0-9) will be greater than these initial values.
2.  Iterate through each character `c` in the input string `s` from beginning to end.
3.  For each character `c`:
    a.  Check if `c` is a numerical digit (i.e., between '0' and '9'). If it's not a digit (it's a letter), skip this character and move to the next one.
    b.  If `c` is a digit, convert it from its character representation to its integer value. For example, `'5'` becomes `5`. Let's call this integer value `val`.
    c.  Compare `val` with `frist`:
        i.  If `val` is strictly greater than `frist`: This means we've found a new largest digit. The current `frist` value now becomes the `second` largest, and `val` becomes the new `frist`. So, first set `second = frist`, then set `frist = val`.
        ii. Else if `val` is strictly greater than `second` AND `val` is not equal to `frist`: This condition handles cases where `val` is not the absolute largest, but it is larger than our current `second` and is also a distinct digit from `frist`. In this scenario, `val` becomes the new `second` largest digit. So, set `second = val`.
        iii. If neither of the above conditions is met (i.e., `val` is less than or equal to `second`, or `val` is equal to `frist` but not greater than it), `val` does not affect our `frist` or `second` values, so we do nothing.
4.  After the loop finishes iterating through all characters in the string, the value stored in `second` will be the second largest distinct digit. Return `second`. If no second largest distinct digit was found (e.g., the string contained no digits or only one distinct digit), `second` will correctly remain -1.

## 💻 Solution
```cpp
class Solution {
public:
    int secondHighest(string s) {
        // Initialize 'frist' to store the largest digit found so far.
        // Initialize 'second' to store the second largest digit found so far.
        // Both are initialized to -1, indicating no digits have been found yet.
        // Using -1 ensures that any valid digit (0-9) will be greater than these initial values.
        int frist = -1;
        int second = -1;

        // Iterate through each character in the input string 's'.
        for (char c : s) {
            // Check if the current character 'c' is a digit using the standard library function.
            if (isdigit(c)) {
                // Convert the character digit to its integer value.
                // Subtracting '0' from a digit character ('0' through '9')
                // yields its corresponding integer value (0 through 9).
                int val = c - '0';

                // Case 1: The current digit 'val' is strictly greater than the current largest digit ('frist').
                // This means we've found a new absolute largest digit.
                if (val > frist) {
                    // The old 'frist' (which was the largest) now becomes the 'second' largest.
                    second = frist;
                    // The current 'val' becomes the new 'frist' (largest).
                    frist = val;
                }
                // Case 2: The current digit 'val' is not greater than 'frist',
                // but it might be greater than 'second' AND it must be distinct from 'frist'.
                // The condition 'val != frist' is crucial to ensure we only consider distinct digits
                // for the 'second' largest, preventing 'second' from being equal to 'frist'.
                else if (val > second && val != frist) {
                    // The current 'val' becomes the new 'second' largest.
                    second = val;
                }
                // If 'val' is less than or equal to 'second', or equal to 'frist' (and not greater than 'frist'),
                // it does not affect 'frist' or 'second', so we do nothing and continue to the next character.
            }
        }
        // After iterating through the entire string, 'second' holds the second largest distinct digit.
        // If no second largest digit was found (e.g., fewer than two distinct digits were present),
        // 'second' will correctly remain -1 as per its initial value.
        return second;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the input string `s` exactly once. `N` is the length of the string. Each character processing takes constant time. |
| **Space** | O(1) | We only use a constant amount of extra space for a few integer variables (`frist`, `second`) regardless of the input string's size. |

## 🔗 Related Problems
*   215. Kth Largest Element in an Array
*   164. Maximum Gap
*   1752. Check if Array Is Sorted and Rotated