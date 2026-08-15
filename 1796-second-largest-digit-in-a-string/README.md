# 1796-second-largest-digit-in-a-string

## 📋 Problem Description
Given an alphanumeric string `s`, the task is to find and return the **second largest** numerical digit that appears in `s`. An alphanumeric string consists of lowercase English letters and digits. If there is no second largest digit (e.g., if there are fewer than two distinct digits), the function should return -1.

The function receives:
- `s`: An alphanumeric string.

The function must return:
- An integer representing the second largest distinct digit in `s`, or -1 if it does not exist.

## 🔍 Examples
```
Input: s = "dfa12321afd"
Output: 2
Explanation: The digits that appear in s are [1, 2, 3]. The largest digit is 3, and the second largest distinct digit is 2.
```

```
Input: s = "abc1111"
Output: -1
Explanation: The digits that appear in s are [1]. Since there is only one distinct digit, there is no second largest digit.
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
The problem asks us to identify the second largest *distinct* numerical digit within a given string. This means we need to ignore letters and also treat multiple occurrences of the same digit as a single instance when determining distinct values. Key edge cases include strings with no digits, or strings with only one unique digit, where the answer should be -1.

## 💡 Core Idea
The core idea is to iterate through the string once, keeping track of the largest and second largest distinct digits encountered so far without needing to store all digits or sort them.

## 🧠 Approach — Single-Pass Tracking
This problem can be efficiently solved using a **Single-Pass Tracking** approach. This pattern is suitable because we only need to maintain a small, constant amount of state (the largest and second largest digits) as we process the input string sequentially. We don't need to store all digits in a separate data structure or perform any sorting, which would be less efficient. A single pass is sufficient to find both the largest and second largest values by carefully updating our tracked variables whenever a new digit is encountered.

## 📝 Step-by-Step Algorithm
1.  Initialize two integer variables:
    *   `frist` (to store the largest distinct digit found so far) to -1.
    *   `second` (to store the second largest distinct digit found so far) to -1.
    These initial values signify that no digits have been processed yet.
2.  Iterate through each character `c` in the input string `s` from beginning to end.
3.  For each character `c`:
    a.  Check if `c` is a numerical digit (using a function like `isdigit()`).
    b.  If `c` is a digit:
        i.  Convert the character `c` to its integer value `val` (e.g., `'5'` becomes `5`) by subtracting the ASCII value of `'0'`.
        ii. Compare `val` with `frist`:
            *   **If `val` is greater than `frist`**: This means we've found a new largest digit. The current `frist` value now becomes the `second` largest, and `val` becomes the new `frist`.
            *   **Else if `val` is greater than `second` AND `val` is not equal to `frist`**: This means `val` is not the absolute largest, but it's larger than the current `second` largest, and it's a distinct digit from the current `frist`. In this case, `val` becomes the new `second`.
4.  After iterating through all characters in the string, the value stored in `second` will represent the second largest distinct digit found. Return `second`.

## 💻 Solution
```cpp
class Solution {
public:
    int secondHighest(string s) {
        // Initialize 'frist' to store the largest digit found so far.
        // Initialize 'second' to store the second largest digit found so far.
        // -1 indicates no digit has been found yet for that position.
        int frist = -1;
        int second = -1;

        // Iterate through each character in the input string 's'.
        for (char c : s) {
            // Check if the current character 'c' is a digit.
            if (isdigit(c)) {
                // Convert the character digit to its integer value.
                // For example, '5' - '0' results in integer 5.
                int val = c - '0';

                // Case 1: 'val' is greater than the current largest digit ('frist').
                // This means 'val' is the new largest.
                if (val > frist) {
                    // The old 'frist' now becomes the 'second' largest.
                    second = frist;
                    // 'val' becomes the new 'frist'.
                    frist = val;
                } 
                // Case 2: 'val' is not greater than 'frist', but it might be greater than 'second'.
                // Also, ensure 'val' is distinct from 'frist' to find the *second distinct* largest.
                else if (val > second && val != frist) {
                    // 'val' is the new 'second' largest digit.
                    second = val;
                }
                // If 'val' is less than or equal to 'second', or equal to 'frist' (and not greater than 'second'),
                // it doesn't affect 'frist' or 'second', so we do nothing.
            }
        }
        // After checking all characters, 'second' holds the second largest distinct digit.
        // If no second largest was found (e.g., only one distinct digit or no digits), it remains -1.
        return second;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The algorithm iterates through the input string `s` exactly once. Each character processing (checking if it's a digit, converting, and comparing/assigning) takes constant time. N is the length of the string. |
| **Space** | O(1) | The algorithm uses a fixed number of variables (`frist`, `second`, `c`, `val`) regardless of the input string's size. No additional data structures are allocated that scale with N. |

## 🔗 Related Problems
- 414. Third Maximum Number
- 215. Kth Largest Element in an Array
- 164. Maximum Gap