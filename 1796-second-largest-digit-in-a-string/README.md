# 1796-second-largest-digit-in-a-string

## 📋 Problem Description
Given an alphanumeric string `s`, the task is to find and return the **second largest** numerical digit that appears in the string. An alphanumeric string consists of lowercase English letters and digits. If there is no second largest unique digit (e.g., fewer than two unique digits are present), the function should return -1.

**Input:** A string `s` consisting of lowercase English letters and digits.
**Output:** An integer representing the second largest unique digit, or -1 if it doesn't exist.

## 🔍 Examples
```
Input: s = "dfa12321afd"
Output: 2
Explanation: The digits that appear in s are [1, 2, 3]. The largest is 3, and the second largest is 2.
```

```
Input: s = "abc1111"
Output: -1
Explanation: The only digit that appears in s is [1]. There is no second largest digit.
```

```
Input: s = "000"
Output: -1
Explanation: The only digit that appears in s is [0]. There is no second largest digit.
```

## 📌 Constraints
*   `1 <= s.length <= 500`
*   `s` consists of only lowercase English letters and digits.

## 🤔 Understanding the Problem
The problem asks us to identify the second largest *unique* digit within a given string. This means we need to filter out non-digit characters and also handle duplicate digits correctly (e.g., if '9' appears multiple times, it's still just the largest digit once). A crucial edge case is when there are fewer than two unique digits in the string (e.g., "abc", "111", "a1b"), in which case we must return -1. We are looking for the second largest *value*, not necessarily the second largest *occurrence*.

## 💡 Core Idea
The most efficient way to find the largest and second largest elements is to iterate through the data once, keeping track of the two largest unique values encountered so far using two separate variables.

## 🧠 Approach — Two-Variable Tracking (Single Pass)
This problem can be solved using a "Two-Variable Tracking" approach, which is a specific form of a single-pass iteration. We iterate through the input string just once. During this single pass, we maintain two variables: one for the largest digit found so far (`frist`) and another for the second largest digit found so far (`second`). This pattern is highly efficient because it avoids the need to store all digits in a separate data structure (like a set or vector) and then sort or process them further. It directly updates the required values as new digits are encountered, making it suitable for problems where only a few top elements are needed.

## 📝 Step-by-Step Algorithm
1.  Initialize two integer variables: `frist` and `second`. Both should be set to -1. `frist` will store the largest digit found, and `second` will store the second largest digit found. Initializing them to -1 correctly handles cases where no digits or only one unique digit are present.
2.  Iterate through each character `c` in the input string `s` from beginning to end.
3.  For each character `c`:
    a.  Check if `c` is a numerical digit (i.e., between '0' and '9').
    b.  If `c` is a digit:
        i.  Convert the character `c` into its integer value `val` (e.g., by subtracting `'0'` from `c`).
        ii. Compare `val` with `frist`:
            *   If `val` is strictly greater than `frist`: This means we've found a new largest digit. The current `frist` value now becomes the new `second`, and `val` becomes the new `frist`.
            *   Else (if `val` is not greater than `frist`):
                *   Check if `val` is strictly greater than `second` AND `val` is not equal to `frist`. This condition ensures that `val` is a unique digit (not equal to the largest) and is larger than the current second largest. If both conditions are true, then `val` becomes the new `second`.
4.  After the loop finishes iterating through all characters in the string, the `second` variable will hold the second largest unique digit found. If no second largest digit was found (e.g., the string contained no digits, or only one unique digit), `second` will remain -1.
5.  Return the value of `second`.

## 💻 Solution
```cpp
class Solution {
public:
    int secondHighest(string s) {
        // Initialize 'frist' to store the largest digit found so far.
        // Initialize 'second' to store the second largest digit found so far.
        // Both are initialized to -1, indicating no digits have been found yet.
        // Using -1 is crucial because digits are 0-9, so -1 acts as a sentinel
        // value that any valid digit will be greater than.
        int frist = -1;
        int second = -1;

        // Iterate through each character in the input string 's'.
        // This is a single pass through the string.
        for (char c : s) {
            // Check if the current character 'c' is a digit.
            // isdigit() is a standard library function that returns true if c is a decimal digit.
            if (isdigit(c)) {
                // Convert the character digit to its integer value.
                // For example, '1' - '0' results in integer 1.
                int val = c - '0';

                // Case 1: If 'val' is strictly greater than the current largest digit ('frist').
                // This means we've found a new largest digit.
                if (val > frist) {
                    // The old 'frist' (which was the largest) now becomes the new 'second' largest.
                    second = frist;
                    // 'val' becomes the new largest digit.
                    frist = val;
                }
                // Case 2: If 'val' is not greater than 'frist' (meaning val <= frist),
                // but it is strictly greater than 'second',
                // AND 'val' is not equal to 'frist' (to ensure we track unique digits).
                // This means 'val' is smaller than 'frist' but larger than 'second',
                // making it the new second largest unique digit.
                else if (val > second && val != frist) {
                    // 'val' becomes the new second largest digit.
                    second = val;
                }
                // If 'val' is less than or equal to 'second', or equal to 'frist' (and not greater than 'frist'),
                // it doesn't affect 'frist' or 'second', so we do nothing and continue to the next character.
            }
        }
        // After iterating through the entire string, 'second' holds the second largest unique digit.
        // If no second largest digit was found (e.g., fewer than two unique digits), 'second' will remain -1.
        return second;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The algorithm iterates through the input string `s` exactly once. `N` is the length of the string. Each character processing takes constant time. |
| **Space** | O(1) | The algorithm uses a fixed number of variables (`frist`, `second`, `c`, `val`) regardless of the input string's size. No additional data structures are used that scale with input size. |

## 🔗 Related Problems
*   215. Kth Largest Element in an Array
*   164. Maximum Gap
*   1752. Check if Array Is Sorted and Rotated