# 0541-reverse-string-ii

## 📋 Problem Description
Given a string `s` and an integer `k`, you are tasked with reversing specific segments of the string. The rule is to reverse the first `k` characters for every block of `2k` characters, starting from the beginning of the string.

There are two special conditions to consider for the characters remaining at the end of the string:
1.  If there are fewer than `k` characters left, you should reverse all of them.
2.  If there are fewer than `2k` but at least `k` characters left, you should reverse only the first `k` of these remaining characters, and leave the rest unchanged.

The function should return the modified string after applying these reversal rules.

## 🔍 Examples
```
Input: s = "abcdefg", k = 2
Output: "bacdfeg"
Explanation:
1. The string is "abcdefg", k = 2.
2. First 2k (4) characters are "abcd". Reverse the first k (2) characters "ab" to "ba". String becomes "bacdefg".
3. The next block of 2k characters would start at index 4. The remaining string is "efg" (length 3).
4. Since 3 is less than 2k (4) but greater than or equal to k (2), we reverse the first k (2) characters of "efg", which are "ef", to "fe".
5. The string becomes "bacdfeg".

Input: s = "abcd", k = 2
Output: "bacd"
Explanation:
1. The string is "abcd", k = 2.
2. First 2k (4) characters are "abcd". Reverse the first k (2) characters "ab" to "ba". String becomes "bacd".
3. No characters left to process.

Input: s = "abc", k = 4
Output: "cba"
Explanation:
1. The string is "abc", k = 4.
2. The string length (3) is less than k (4). According to the rule, if there are fewer than k characters left, reverse all of them.
3. Reverse "abc" to "cba".
```

## 📌 Constraints
*   `1 <= s.length <= 10^4`
*   `s` consists of only lowercase English letters.
*   `1 <= k <= 10^4`

## 🤔 Understanding the Problem
This problem asks us to perform a specific pattern of in-place string reversal. It's not a simple reversal of the entire string or fixed-size blocks. The core challenge lies in correctly identifying the segments to be reversed within each `2k` block and meticulously handling the edge cases at the end of the string where fewer than `2k` characters might remain. The rules for these remaining characters are distinct, requiring careful boundary management to ensure the correct `k` characters (or fewer) are reversed.

## 💡 Core Idea
The core idea is to iterate through the string in fixed steps of `2k` characters. For each such block, we determine the exact substring that needs to be reversed (which is at most `k` characters long) and then apply a standard two-pointer in-place reversal to that specific substring.

## 🧠 Approach — Iteration with Two Pointers
The algorithm uses an **Iteration** pattern to traverse the string in chunks, combined with the **Two Pointers** pattern for in-place substring reversal.

This approach fits the problem well because:
1.  **Iteration**: The problem explicitly states "for every `2k` characters," which naturally suggests iterating through the string with a step size of `2k`. This allows us to process the string block by block.
2.  **Two Pointers**: Within each block, we need to reverse a specific segment (up to `k` characters). The Two Pointers technique is the most efficient way to reverse a substring in-place. One pointer starts at the beginning of the segment, and the other at the end, swapping characters as they move towards each other until the segment is fully reversed. This avoids creating new strings and minimizes memory usage.

## 📝 Step-by-Step Algorithm
1.  **Get String Length**: First, determine the total length of the input string `s` and store it in a variable, say `n`.
2.  **Iterate in Blocks**: Start a `for` loop that iterates through the string. The loop variable `i` will represent the starting index of each `2k` character block. Increment `i` by `2 * k` in each step of the loop.
3.  **Define Reversal Segment**: Inside the loop, for the current block starting at index `i`:
    *   Initialize a `left` pointer to `i`. This marks the beginning of the segment to be reversed.
    *   Calculate the potential `right` pointer for the segment to be reversed. This would ideally be `i + k - 1` (to reverse the first `k` characters).
    *   However, we must ensure `right` does not go beyond the end of the string. So, the actual `right` pointer should be `min(i + k - 1, n - 1)`. This `min` operation is crucial as it correctly handles all edge cases:
        *   If `i + k - 1` is within string bounds, it reverses exactly `k` characters.
        *   If `i + k - 1` goes beyond `n - 1` (meaning fewer than `k` characters are left), `right` becomes `n - 1`, effectively reversing all remaining characters.
        *   If there are between `k` and `2k` characters left, `i + k - 1` will be within bounds, and `right` will be `i + k - 1`, reversing only the first `k` characters as required.
4.  **Perform In-Place Reversal**: Use a `while` loop with the `left` and `right` pointers to reverse the substring `s[left...right]`:
    *   While `left` is less than `right`:
        *   Swap the character at `s[left]` with the character at `s[right]`.
        *   Increment `left` by 1.
        *   Decrement `right` by 1.
5.  **Return Result**: After the main `for` loop completes, all necessary reversals will have been performed. Return the modified string `s`.

## 💻 Solution
```cpp
class Solution {
public:
    string reverseStr(string s, int k) {
        int n = s.length(); // Get the total length of the string.

        // Iterate through the string in chunks of 2k characters.
        // 'i' represents the starting index of each 2k block.
        // We increment 'i' by '2 * k' in each step to move to the next block.
        for (int i = 0; i < n; i += 2 * k) {
            // 'left' pointer marks the beginning of the segment to be reversed.
            // This is always 'i' for the current block.
            int left = i;

            // 'right' pointer marks the end of the segment to be reversed.
            // This should ideally be 'i + k - 1' (the end of the first 'k' characters in the 2k block).
            // However, we must ensure 'right' does not exceed the string's bounds (n - 1).
            // Using min(i + k - 1, n - 1) correctly handles all edge cases:
            // 1. If 'i + k - 1' is within bounds, it sets 'right' to 'i + k - 1',
            //    reversing exactly the first 'k' characters of the current block.
            // 2. If 'i + k - 1' goes beyond 'n - 1' (meaning fewer than 'k' characters are left
            //    from the current 'i' to the end of the string), it sets 'right' to 'n - 1',
            //    effectively reversing all remaining characters.
            // 3. If there are between 'k' and '2k' characters left, 'i + k - 1' will be
            //    within bounds, and 'right' will be 'i + k - 1', reversing only the first 'k'
            //    characters as per the problem statement.
            int right = min(i + k - 1, n - 1);

            // Perform in-place reversal of the substring from 'left' to 'right'.
            // This is a standard two-pointer swap mechanism.
            while (left < right) {
                swap(s[left], s[right]); // Swap characters at 'left' and 'right'
                left++;                  // Move 'left' pointer one step to the right
                right--;                 // Move 'right' pointer one step to the left
            }
        }
        
        // Return the modified string after all necessary reversals are complete.
        return s;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The `for` loop iterates through the string, effectively visiting each character once. The inner `while` loop (for swapping) processes characters within a `k`-length segment, and each character is involved in a swap at most once across all iterations. |
| **Space** | O(1) | The solution modifies the input string in-place and uses only a few constant extra variables for pointers and string length. No additional data structures are allocated proportional to the input size. |

## 🔗 Related Problems
- 344. Reverse String
- 151. Reverse Words in a String
- 796. Rotate String