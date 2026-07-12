# 0013-roman-to-integer

## 📋 Problem Description
Roman numerals are a system of numerical notation used by the Romans. They are represented by seven different symbols: `I`, `V`, `X`, `L`, `C`, `D`, and `M`, each with a specific integer value:

| Symbol | Value |
| :----- | :---- |
| I      | 1     |
| V      | 5     |
| X      | 10    |
| L      | 50    |
| C      | 100   |
| D      | 500   |
| M      | 1000  |

Typically, Roman numerals are written with symbols of larger value preceding symbols of smaller value, and their values are added together (e.g., `II` = 1 + 1 = 2, `XII` = 10 + 1 + 1 = 12).

However, there's a special rule for six specific cases where a smaller value symbol placed before a larger value symbol indicates subtraction:
*   `I` before `V` (5) makes 4 (`IV`).
*   `I` before `X` (10) makes 9 (`IX`).
*   `X` before `L` (50) makes 40 (`XL`).
*   `X` before `C` (100) makes 90 (`XC`).
*   `C` before `D` (500) makes 400 (`CD`).
*   `C` before `M` (1000) makes 900 (`CM`).

Given a string `s` representing a valid Roman numeral, the task is to convert it to its corresponding integer value.

## 🔍 Examples
```
Input: s = "III"
Output: 3
Explanation: I = 1, I = 1, I = 1. Total = 1 + 1 + 1 = 3.
```

```
Input: s = "LVIII"
Output: 58
Explanation: L = 50, V = 5, III = 3. Total = 50 + 5 + 3 = 58.
```

```
Input: s = "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90, IV = 4. Total = 1000 + 900 + 90 + 4 = 1994.
```

## 📌 Constraints
*   `1 <= s.length <= 15`
*   `s` contains only the characters `('I', 'V', 'X', 'L', 'C', 'D', 'M')`.
*   It is guaranteed that `s` is a valid Roman numeral in the range `[1, 3999]`.

## 🤔 Understanding the Problem
The problem asks us to convert a Roman numeral string into its integer equivalent. The primary challenge lies in correctly handling the "subtractive" cases (like `IV` for 4 or `CM` for 900) where a smaller numeral precedes a larger one, indicating subtraction rather than addition. A simple left-to-right sum of individual character values would fail for these cases. We need a strategy that can differentiate between additive and subtractive combinations.

## 💡 Core Idea
The key insight is to process the Roman numeral string from right to left. By doing so, we can always compare the current character's value with the value of the character immediately to its right (which we would have already processed). If the current character's value is *less* than the previous character's value, it signifies a subtractive case; otherwise, it's an additive case.

## 🧠 Approach — Iteration / Greedy
This problem can be solved using an **Iterative** approach, specifically a **Greedy** strategy. We iterate through the Roman numeral string and make a locally optimal decision (add or subtract the current character's value) based on its relationship with the previously processed character. This greedy choice works because the rules for Roman numeral formation are well-defined and local (subtractive pairs are always two characters).

By iterating from right to left, we ensure that when we encounter a character, the character to its right (if any) has already been processed, and its value is known. This allows us to easily determine if the current character is part of a subtractive pair (e.g., `I` in `IV`) or an additive one (e.g., `I` in `VI`).

## 📝 Step-by-Step Algorithm
1.  **Create a Value Map**: Initialize a map (e.g., `unordered_map` in C++) that stores the integer value for each Roman numeral character (`I` -> 1, `V` -> 5, ..., `M` -> 1000).
2.  **Initialize Variables**:
    *   `total`: An integer variable initialized to `0` to store the final converted integer.
    *   `prev_value`: An integer variable initialized to `0` to store the integer value of the Roman numeral character processed in the *previous* iteration (i.e., the character to the right of the current one).
3.  **Iterate from Right to Left**: Loop through the input string `s` starting from the last character (index `s.length() - 1`) down to the first character (index `0`).
4.  **Get Current Character's Value**: In each iteration, retrieve the integer `current_value` for the character `s[i]` from the value map.
5.  **Apply Subtraction/Addition Logic**:
    *   **If `current_value < prev_value`**: This indicates a subtractive case (e.g., `I` appearing before `V` or `X`). Subtract `current_value` from `total`.
    *   **Else (`current_value >= prev_value`)**: This indicates an additive case (e.g., `V` appearing before `I`, or any character not part of a subtractive pair). Add `current_value` to `total`.
6.  **Update `prev_value`**: After processing the current character, update `prev_value` to `current_value` for the next iteration (when we move one character to the left).
7.  **Return Total**: After the loop completes, `total` will hold the final integer conversion of the Roman numeral. Return `total`.

## 💻 Solution
```cpp
#include <string>
#include <unordered_map> // Required for unordered_map

class Solution {
public:
    int romanToInt(string s) {
        // Define a static unordered_map to store Roman numeral character to integer value mappings.
        // 'static' ensures the map is initialized only once across all calls to romanToInt,
        // making subsequent calls faster as it avoids re-creating the map.
        static unordered_map<char, int> mp = {
            {'I', 1},   {'V', 5},   {'X', 10},
            {'L', 50},  {'C', 100}, {'D', 500},
            {'M', 1000}
        };

        // Initialize 'prev' to 0. This will store the value of the Roman numeral
        // character processed in the *previous* iteration (i.e., to the right).
        // Initialize 'total' to 0, which will accumulate the final integer value.
        int prev = 0, total = 0;

        // Iterate through the Roman numeral string from right to left.
        // This approach simplifies handling the subtractive cases (e.g., IV, IX).
        for (int i = s.length() - 1; i >= 0; i--) {
            // Get the integer value of the current Roman numeral character.
            int curr = mp[s[i]];

            // Compare the current character's value with the value of the character
            // immediately to its right (which was stored in 'prev').
            if (curr < prev) {
                // If the current value is less than the previous value (e.g., 'I' before 'V'),
                // it's a subtractive case. Subtract 'curr' from the total.
                total -= curr;
            } else {
                // Otherwise (current value is greater than or equal to previous),
                // it's an additive case. Add 'curr' to the total.
                total += curr;
            }

            // Update 'prev' to the current character's value for the next iteration
            // (when we move one character to the left).
            prev = curr;
        }

        // After iterating through the entire string, 'total' holds the converted integer.
        return total;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The algorithm iterates through the input string `s` exactly once, where N is the length of the string. Each character lookup in the `unordered_map` takes O(1) on average. |
| **Space** | O(1) | The `unordered_map` stores a fixed number of Roman numeral symbols (7). The variables `prev`, `total`, and `curr` consume constant space. The `static` keyword for the map further ensures it's not recreated per function call. |

## 🔗 Related Problems
- 12. Integer to Roman (The inverse problem: convert an integer to a Roman numeral)
- 8. String to Integer (atoi) (Another string parsing problem involving character-to-value conversion and specific rules)
- 273. Integer to English Words (Involves converting numbers to a string representation based on rules)