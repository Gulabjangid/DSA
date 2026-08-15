# 1796-second-largest-digit-in-a-string

## 📋 Problem Description
Given an alphanumeric string `s`, the task is to find and return the **second largest** numerical digit that appears in `s`. An alphanumeric string consists of lowercase English letters and digits. If there is no second largest digit (e.g., fewer than two distinct digits are present in the string), the function should return `-1`.

**Input:** A string `s` consisting of lowercase English letters and digits.
**Output:** An integer representing the second largest distinct digit, or `-1` if it doesn't exist.

## 🔍 Examples
```
Input: s = "dfa12321afd"
Output: 2
Explanation: The digits that appear in s are [1, 2, 3]. The largest digit is 3, and the second largest distinct digit is 2.
```

```
Input: s = "abc1111"
Output: -1
Explanation: The digits that appear in s are [1]. There is only one distinct digit, so there is no second largest digit.
```

```
Input: s = "0000"
Output: -1
Explanation: The digits that appear in s are [0]. Only one distinct digit, so no second largest.
```

## 📌 Constraints
*   `1 <= s.length <= 500`
*   `s` consists of only lowercase English letters and digits.

## 🤔 Understanding the Problem
The problem asks us to identify the second largest *distinct* digit within a given string. This means we need to ignore any non-digit characters and also handle duplicate digits correctly (e.g., in "1223", the digits are 1, 2, 3, and the second largest is 2, not another 2). A crucial edge case is when there are fewer than two distinct digits in the string (e.g., "abc", "111", "9"). In such scenarios, we should return -1. The problem is non-trivial because we need an efficient way to keep track of the largest and second largest digits without necessarily storing all digits or sorting them.

## 💡 Core Idea
The core idea is to iterate through the string once, maintaining two variables: one for the largest digit found so far (`frist`) and another for the second largest digit found so far (`second`). As we encounter new digits, we update these two variables carefully to ensure they always hold the correct largest and second largest *distinct* digits.

## 🧠 Approach — Single-Pass Tracking
This problem can be efficiently solved using a **Single-Pass Tracking** approach. This pattern is suitable because we only need to maintain a small, constant amount of state (the two largest digits) as we process the input sequentially. We don't need to store all digits in a data structure like an array or set, nor do we need to sort them, which would be less efficient. By carefully updating our `frist` and `second` variables in a single pass, we can determine the answer with optimal time complexity.

## 📝 Step-by-Step Algorithm
1.  Initialize two integer variables, `frist` and `second`, both to `-1`. `frist` will store the largest digit encountered, and `second` will store the second largest distinct digit encountered. Initializing them to `-1` serves as a sentinel value, indicating no digits have been found yet.
2.  Iterate through each character `c` in the input string `s` from beginning to end.
3.  For each character `c`:
    a.  Check if `c` is a numerical digit. This can be done using a function like `isdigit(c)` or by checking if `c` is between '0' and '9'.
    b.  If `c` is a digit, convert it to its integer value `val` (e.g., `val = c - '0'`).
    c.  Compare `val` with `frist` and `second`:
        i.  **If `val` is greater than `frist`**: This means we've found a new largest digit.
            *   The current `frist` value now becomes the new `second` largest.
            *   `val` becomes the new `frist` (largest).
        ii. **Else if `val` is greater than `second` AND `val` is NOT equal to `frist`**: This means `val` is not the largest digit, but it is larger than our current `second` largest, and it's a distinct digit from `frist`.
            *   `val` becomes the new `second` largest.
        iii. If `val` is less than or equal to `second`, or if `val` is equal to `frist` (meaning it's a duplicate of the largest), we do nothing, as it doesn't affect our `frist` or `second` values.
4.  After iterating through all characters in the string, the value stored in `second` will be the second largest distinct digit. If no second largest digit was found (e.g., the string contained fewer than two distinct digits), `second` will still be `-1`.
5.  Return the value of `second`.

## 💻 Solution
```cpp
class Solution {
public:
    int secondHighest(string s) {
        // Initialize 'frist' to store the largest digit found so far.
        // Initialize 'second' to store the second largest digit found so far.
        // Both are initialized to -1, indicating no digits have been found yet.
        // Using -1 is convenient because digits are 0-9, so -1 will always be smaller.
        int frist = -1;
        int second = -1;

        // Iterate through each character in the input string 's'.
        for (char c : s) {
            // Check if the current character 'c' is a digit.
            // isdigit() is a standard library function that returns true if c is a digit.
            if (isdigit(c)) {
                // Convert the character digit to its integer value.
                // For example, '0' - '0' = 0, '1' - '0' = 1, ..., '9' - '0' = 9.
                int val = c - '0';

                // Case 1: The current digit 'val' is strictly greater than the current largest digit ('frist').
                // This means 'val' is a new maximum.
                if (val > frist) {
                    // The old 'frist' value now becomes the new 'second' largest.
                    // This correctly demotes the previous largest.
                    second = frist;
                    // 'val' becomes the new 'frist' (largest).
                    frist = val;
                }
                // Case 2: The current digit 'val' is not the largest (i.e., val <= frist),
                // but it might be the second largest.
                // We also need to ensure 'val' is not equal to 'frist' to find distinct digits.
                // If val == frist, it's a duplicate of the largest, so it cannot be the second largest distinct digit.
                else if (val > second && val != frist) {
                    // 'val' is greater than the current 'second' and is distinct from 'frist',
                    // so 'val' becomes the new 'second' largest digit.
                    second = val;
                }
                // If val <= second, or val == frist, it doesn't change our 'frist' or 'second' values.
                // In these cases, 'val' is either too small to be the second largest, or it's a duplicate of the largest.
            }
        }
        // After checking all characters, 'second' will hold the second largest distinct digit.
        // If no second largest digit was found (e.g., only one distinct digit or no digits at all),
        // 'second' will remain -1, which is the required output for such cases.
        return second;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the input string `s` exactly once. For each character, we perform a constant number of operations (checking if it's a digit, converting to int, and a few comparisons/assignments). N is the length of the string. |
| **Space** | O(1) | We only use a few fixed-size variables (`frist`, `second`, `c`, `val`) regardless of the input string's length. No additional data structures are used that scale with input size. |

## 🔗 Related Problems
*   215. Kth Largest Element in an Array
*   703. Kth Largest Element in a Stream
*   414. Third Maximum Number