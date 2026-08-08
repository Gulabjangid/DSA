# 2119-a-number-after-a-double-reversal

## 📋 Problem Description
You are given an integer `num`.
**Reversing** an integer means to reverse all its digits. For example, reversing `2021` gives `1202`. An important rule is that leading zeros are not retained after reversal; for instance, reversing `12300` gives `321`.

Your task is to perform two reversals:
1. Reverse `num` to get `reversed1`.
2. Then, reverse `reversed1` to get `reversed2`.

You must return `true` if `reversed2` is equal to the original `num`. Otherwise, return `false`.

## 🔍 Examples
```
Input: num = 526
Output: true
Explanation: Reverse 526 to get 625. Then reverse 625 to get 526. Since 526 equals the original num, return true.
```

```
Input: num = 1800
Output: false
Explanation: Reverse 1800 to get 81. Then reverse 81 to get 18. Since 18 does not equal the original num (1800), return false.
```

```
Input: num = 0
Output: true
Explanation: Reverse 0 to get 0. Then reverse 0 to get 0. Since 0 equals the original num, return true.
```

## 📌 Constraints
*   `0 <= num <= 10^6`

## 🤔 Understanding the Problem
The problem asks us to determine if an integer remains the same after being reversed twice. The crucial detail is how reversal handles trailing zeros: they are *lost*. For example, `12300` becomes `321`. This means if a number ends in one or more zeros, its first reversal will effectively "chop off" those zeros. Consequently, the second reversal will operate on a number that is already missing those trailing zeros, making it impossible to restore the original number unless the original number was `0`. The only exception is `num = 0`, where `0` reversed is `0`, and `0` reversed again is `0`, so `0 == 0` is true.

## 💡 Core Idea
The core idea is that a number `num` will be equal to `reversed2` if and only if `num` does not end in `0`, *unless* `num` itself is `0`. If `num` ends in `0` (e.g., `1230`), its first reversal (`reversed1`) will be `321`. Reversing `321` again (`reversed2`) yields `123`, which is not equal to `1230`. If `num` does not end in `0` (e.g., `123`), its first reversal (`reversed1`) is `321`. Reversing `321` again (`reversed2`) yields `123`, which is equal to `num`. The special case `num = 0` correctly returns `true`.

## 🧠 Approach — Direct Simulation / Mathematical Observation
This problem can be solved by either directly simulating the two reversal steps as described, or by leveraging the mathematical observation about trailing zeros. The provided solution uses the direct simulation approach. This pattern fits because the problem explicitly defines a process (two reversals) and asks for a result based on that process. Since the input `num` is relatively small (up to `10^6`), simulating the digit-by-digit reversal is very efficient and straightforward.

## 📝 Step-by-Step Algorithm

1.  **Handle the special case for `num = 0`**: If the input `num` is `0`, it will always return `true` because `0` reversed is `0`, and `0` reversed again is `0`. `0 == 0` is true.

2.  **First Reversal (`num` to `reversed1`)**:
    *   Initialize a variable, say `reversed1`, to `0`.
    *   Create a temporary copy of the original `num` to work with, as we'll modify it.
    *   While the temporary number is not `0`:
        *   Extract the last digit of the temporary number using the modulo operator (`% 10`).
        *   Append this digit to `reversed1` by multiplying `reversed1` by `10` and adding the extracted digit.
        *   Remove the last digit from the temporary number by integer division (`/ 10`).
    *   After the loop, `reversed1` will hold the first reversed value.

3.  **Second Reversal (`reversed1` to `reversed2`)**:
    *   Initialize a variable, say `reversed2`, to `0`.
    *   Create a temporary copy of `reversed1` to work with.
    *   While the temporary `reversed1` is not `0`:
        *   Extract the last digit of the temporary `reversed1` using the modulo operator (`% 10`).
        *   Append this digit to `reversed2` by multiplying `reversed2` by `10` and adding the extracted digit.
        *   Remove the last digit from the temporary `reversed1` by integer division (`/ 10`).
    *   After the loop, `reversed2` will hold the second reversed value.

4.  **Comparison**:
    *   Compare `reversed2` with the original `num`.
    *   If they are equal, return `true`.
    *   Otherwise, return `false`.

*(Note: The provided solution handles `num = 0` implicitly within the loops, as `0 % 10` is `0` and `0 / 10` is `0`, leading to `rev = 0` and `drev = 0`, correctly returning `true`.)*

## 💻 Solution
```cpp
class Solution {
public:
    bool isSameAfterReversals(int num) {
        // Store the original number for comparison later.
        int original_num = num;

        // --- First Reversal: num -> reversed1 ---
        int reversed1 = 0;
        // We use a temporary variable 'num' for the first reversal
        // to avoid modifying 'original_num' prematurely.
        while (num != 0) {
            // Get the last digit of 'num'.
            int digit = num % 10;
            // Append the digit to 'reversed1'.
            // Multiply by 10 to shift existing digits left, then add the new digit.
            reversed1 = reversed1 * 10 + digit;
            // Remove the last digit from 'num'.
            num = num / 10;
        }

        // --- Second Reversal: reversed1 -> reversed2 ---
        int reversed2 = 0;
        // We use 'reversed1' for the second reversal.
        while (reversed1 != 0) {
            // Get the last digit of 'reversed1'.
            int digit = reversed1 % 10;
            // Append the digit to 'reversed2'.
            reversed2 = reversed2 * 10 + digit;
            // Remove the last digit from 'reversed1'.
            reversed1 = reversed1 / 10;
        }

        // --- Comparison ---
        // Check if the number after two reversals is equal to the original number.
        if (reversed2 == original_num) {
            return true;
        }
        return false;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(log N) | The number of digits in `num` is proportional to log base 10 of `num`. Each `while` loop iterates once for each digit. Since `num <= 10^6`, it has at most 7 digits. The operations are constant time per digit. |
| **Space** | O(1) | Only a few integer variables (`original_num`, `reversed1`, `reversed2`, `digit`) are used, regardless of the input `num`'s magnitude. |

## 🔗 Related Problems
- 7. Reverse Integer
- 9. Palindrome Number
- 258. Add Digits