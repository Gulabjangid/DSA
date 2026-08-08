# 2119-a-number-after-a-double-reversal

## 📋 Problem Description
You are given an integer `num`.
The operation of "reversing" an integer means to reverse all its digits. For example, reversing `2021` yields `1202`. A crucial detail is that leading zeros are not retained after reversal; for instance, reversing `12300` results in `321`.

Your task is to perform a "double reversal" on the given `num`:
1. Reverse `num` to obtain `reversed1`.
2. Reverse `reversed1` to obtain `reversed2`.

You must return `true` if `reversed2` is equal to the original `num`. Otherwise, return `false`.

## 🔍 Examples
```
Input: num = 526
Output: true
Explanation: Reverse 526 to get 625. Then reverse 625 to get 526. Since 526 equals the original num, return true.

Input: num = 1800
Output: false
Explanation: Reverse 1800 to get 81. Then reverse 81 to get 18. Since 18 does not equal the original num (1800), return false.

Input: num = 0
Output: true
Explanation: Reverse 0 to get 0. Then reverse 0 to get 0. Since 0 equals the original num, return true.
```

## 📌 Constraints
*   `0 <= num <= 10^6`

## 🤔 Understanding the Problem
The problem asks us to simulate a specific two-step reversal process on an integer and then check if the final result matches the initial number. The key to understanding this problem lies in how integer reversal handles trailing zeros. If an integer (other than `0` itself) ends with one or more zeros, these zeros will effectively be "lost" during the first reversal because they become leading zeros in the reversed number and are not retained. For example, `12300` becomes `321`. When `321` is reversed again, it becomes `123`, which is not equal to `12300`. This loss of information due to trailing zeros is the primary reason why `reversed2` might not equal `num`.

## 💡 Core Idea
The core idea revolves around understanding how integer reversal handles trailing zeros. When an integer `num` (that is not `0`) ends with one or more zeros, its first reversal (`reversed1`) will effectively drop these trailing zeros because they become leading zeros in `reversed1` and are not retained. Consequently, the second reversal (`reversed2`) cannot recover these lost zeros, making `reversed2` different from `num`. If `num` does not end in zero, or if `num` is `0`, then all digits are preserved through both reversals, and `reversed2` will equal `num`.

## 🧠 Approach — Direct Simulation
This problem can be solved using a **Direct Simulation** approach. The problem explicitly defines a two-step process: reverse `num` to get `reversed1`, then reverse `reversed1` to get `reversed2`. The most straightforward way to solve this is to implement these two reversal steps exactly as described and then compare the final `reversed2` with the original `num`. This approach naturally handles the special case of trailing zeros because the standard integer reversal algorithm (extracting digits with modulo and rebuilding with multiplication) inherently drops leading zeros (which were trailing zeros in the original number).

## 📝 Step-by-Step Algorithm
1.  **Store Original Number**: Create a variable, say `original_num`, and store the initial value of `num` in it. This is crucial for the final comparison.
2.  **First Reversal (num -> reversed1)**:
    *   Initialize a variable `reversed1` to `0`.
    *   Start a loop that continues as long as `num` is not `0`.
        *   Extract the last digit of `num` using the modulo operator: `digit = num % 10`.
        *   Append this `digit` to `reversed1`: `reversed1 = reversed1 * 10 + digit`. This effectively shifts existing digits in `reversed1` one place to the left and adds the new digit.
        *   Remove the last digit from `num` by integer division: `num = num / 10`.
3.  **Second Reversal (reversed1 -> reversed2)**:
    *   Initialize a variable `reversed2` to `0`.
    *   Start a loop that continues as long as `reversed1` is not `0`.
        *   Extract the last digit of `reversed1`: `digit = reversed1 % 10`.
        *   Append this `digit` to `reversed2`: `reversed2 = reversed2 * 10 + digit`.
        *   Remove the last digit from `reversed1`: `reversed1 = reversed1 / 10`.
4.  **Compare and Return**: After both reversals are complete, compare `reversed2` with `original_num`.
    *   If `reversed2` is equal to `original_num`, return `true`.
    *   Otherwise, return `false`.

## 💻 Solution
```cpp
class Solution {
public:
    bool isSameAfterReversals(int num) {
        // Handle the special case for num = 0.
        // Reversing 0 gives 0, reversing 0 again gives 0.
        // So, 0 == 0, which is true.
        if (num == 0) {
            return true;
        }

        // Store the original number for final comparison.
        // The 'num' variable will be modified during the first reversal.
        int original_num = num;

        // --- First Reversal: num -> reversed1 ---
        int reversed1 = 0; // Initialize variable to store the first reversed number.
        int temp_num = num; // Use a temporary variable to perform the first reversal
                            // so that 'num' can be used for the second reversal's input if needed,
                            // although in this specific solution, 'num' is consumed.
                            // A better practice is to use 'original_num' for comparison.

        // Loop to extract digits from temp_num (which is initially 'num')
        // and build reversed1.
        while (temp_num != 0) {
            int digit = temp_num % 10; // Get the last digit of temp_num.
            reversed1 = reversed1 * 10 + digit; // Append the digit to reversed1.
                                                // E.g., if reversed1=0, digit=6 -> reversed1=6
                                                // if reversed1=6, digit=2 -> reversed1=62
            temp_num = temp_num / 10; // Remove the last digit from temp_num.
        }

        // --- Second Reversal: reversed1 -> reversed2 ---
        int reversed2 = 0; // Initialize variable to store the second reversed number.
        int temp_reversed1 = reversed1; // Use a temporary variable for the second reversal.

        // Loop to extract digits from temp_reversed1 and build reversed2.
        while (temp_reversed1 != 0) {
            int digit = temp_reversed1 % 10; // Get the last digit of temp_reversed1.
            reversed2 = reversed2 * 10 + digit; // Append the digit to reversed2.
            temp_reversed1 = temp_reversed1 / 10; // Remove the last digit from temp_reversed1.
        }

        // --- Final Comparison ---
        // Check if the doubly reversed number is equal to the original number.
        if (reversed2 == original_num) {
            return true;
        }
        return false;

        // A more concise observation-based solution:
        // return num == 0 || num % 10 != 0;
        // This works because:
        // 1. If num is 0, it's true.
        // 2. If num is not 0 AND does not end in 0 (num % 10 != 0), then no trailing zeros are lost,
        //    so reversed2 will equal num.
        // 3. If num is not 0 AND ends in 0 (num % 10 == 0), then trailing zeros are lost in the first reversal,
        //    so reversed2 will NOT equal num.
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(log N) | The number of operations (digit extractions and appends) is proportional to the number of digits in `num`. The number of digits in `num` is `log10(num) + 1`. Since we perform two such reversals, the total time complexity is still dominated by the number of digits, hence O(log N). |
| **Space** | O(1) | We only use a fixed number of integer variables (`original_num`, `reversed1`, `reversed2`, `temp_num`, `temp_reversed1`, `digit`) regardless of the input `num`'s magnitude. |

## 🔗 Related Problems
- 7. Reverse Integer
- 9. Palindrome Number
- 258. Add Digits