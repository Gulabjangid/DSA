# 1796-second-largest-digit-in-a-string

## 📋 Problem Description
Given an alphanumeric string `s`, the task is to find and return the second largest unique numerical digit that appears in `s`. An alphanumeric string consists of lowercase English letters and digits. If no such digit exists (e.g., the string contains fewer than two unique digits), the function should return `-1`.

The function `secondHighest` takes a string `s` as input and must return an integer representing the second largest digit, or `-1`.

## 🔍 Examples
```
Input: s = "dfa12321afd"
Output: 2
Explanation: The digits that appear in s are [1, 2, 3]. The unique digits are [1, 2, 3]. The largest is 3, and the second largest is 2.

Input: s = "abc1111"
Output: -1
Explanation: The digits that appear in s are [1]. There is only one unique digit, so there is no second largest digit.

Input: s = "abc"
Output: -1
Explanation: The string contains no digits.
```

## 📌 Constraints
*   `1 <= s.length <= 500`
*   `s` consists of only lowercase English letters and digits.

## 🤔 Understanding the Problem
The problem asks us to identify all unique digits present within a given alphanumeric string and then determine the second largest among them. It's crucial to consider only *unique* digits. For example, if the digits encountered are `[1, 1, 2, 3]`, the unique digits are `[1, 2, 3]`, and the second largest is `2`. Edge cases are important: if the string contains no digits, or only one unique digit (e.g., "abc111"), the answer should be `-1`. The challenge lies in efficiently tracking the largest and second largest digits without storing all digits in a separate data structure.

## 💡 Core Idea
The core idea is to iterate through the string once, keeping track of the largest and second largest unique digits encountered so far using two variables. This allows us to find the required digit in a single pass without needing to store all digits or sort them.

## 🧠 Approach — Single Pass with Two Variables
This pattern is suitable because we only need to maintain information about the top two largest unique digits at any given point. As we iterate through the string, we can update our `largest` and `second` variables based on the current digit. This approach avoids the overhead of storing all digits in a collection (like a set or vector) and then processing them, making the solution very efficient in terms of both time and space complexity. It's a greedy approach where we always try to update our `largest` and `second` candidates with the best possible values found so far.

## 📝 Step-by-Step Algorithm
1.  Initialize two integer variables: `largest` and `second`. Both should be set to `-1`. These variables will store the largest and second largest unique digits found in the string, respectively. Using `-1` is appropriate because digits are non-negative (0-9), and it also serves as the default return value if no second largest digit is found.
2.  Iterate through each character `c` in the input string `s` from beginning to end.
3.  For each character `c` encountered:
    a.  Check if `c` is a numerical digit. This can be done using a function like `isdigit(c)` or by checking if `c` is within the range `'0'` to `'9'`.
    b.  If `c` is indeed a digit:
        i.   Convert the character `c` to its integer value. For example, `int digit = c - '0';`.
        ii.  Compare this `digit` with the current `largest` value:
            *   **If `digit` is greater than `largest`**: This means we've found a new largest digit. The current `largest` value now becomes the new `second` largest, and the `digit` we just found becomes the new `largest`.
            *   **Else if `digit` is greater than `second` AND `digit` is NOT equal to `largest`**: This means we've found a new second largest digit. The `digit` we just found becomes the new `second`. The condition `digit != largest` is crucial here to ensure that we only consider *unique* digits for the second largest position. If `digit` were equal to `largest`, it would not be a *new* second largest unique digit.
4.  After iterating through all characters in the string, the value stored in the `second` variable will be the second largest unique digit found, or `-1` if no such digit exists. Return `second`.

## 💻 Solution
```cpp
class Solution {
public:
    int secondHighest(string s) {
        // Initialize 'second' and 'largest' to -1.
        // -1 is used because digits are 0-9, so -1 indicates no digit found yet,
        // and it's also the required return value if no second largest exists.
        int second = -1;
        int largest = -1;

        // Iterate through each character in the input string 's'.
        for (char c : s) {
            // Check if the current character 'c' is a digit.
            if (isdigit(c)) {
                // Convert the character digit to its integer value.
                // For example, '1' - '0' gives 1.
                int digit = c - '0';

                // Case 1: Current digit is greater than the current largest.
                // This means we found a new largest digit.
                if (digit > largest) {
                    // The old 'largest' now becomes the 'second' largest.
                    second = largest;
                    // The current 'digit' becomes the new 'largest'.
                    largest = digit;
                }
                // Case 2: Current digit is not the largest, but it might be the second largest.
                // It must be greater than 'second' AND not equal to 'largest'
                // (to ensure we only consider unique digits for 'second').
                else if (digit > second && digit != largest) {
                    // The current 'digit' becomes the new 'second' largest.
                    second = digit;
                }
                // If digit <= second, or digit == largest (and not > largest),
                // it doesn't change our 'second' or 'largest' values, so we do nothing.
            }
        }
        // After checking all characters, 'second' holds the second largest unique digit,
        // or -1 if none was found.
        return second;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the string `s` exactly once, where N is the length of the string. Each character is processed in constant time. |
| **Space** | O(1) | We only use a few constant extra variables (`largest`, `second`, `c`, `digit`) regardless of the input string's size. |

## 🔗 Related Problems
- 215. Kth Largest Element in an Array
- 164. Maximum Gap
- 1752. Check if Array Is Sorted and Rotated