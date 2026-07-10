# 0443-string-compression

## 📋 Problem Description
You are given an array of characters, `chars`. Your task is to compress this array in-place according to a specific algorithm.

The compression process works as follows:
For every group of consecutive, identical characters in the input array:
1.  If the group consists of only one character, append just that character to the compressed result.
2.  If the group consists of two or more characters, append the character itself, followed by its count. For example, "aaa" becomes "a3". If the count is 10 or more (e.g., 12), the digits of the count should be appended individually (e.g., "bbbbbbbbbbbb" becomes "b12", which means 'b', '1', '2').

The compressed result should not be returned as a new string or array. Instead, it must be stored directly back into the original `chars` array, overwriting its contents from the beginning. After modifying the array, the function should return the new length of the compressed array. Any characters in `chars` beyond this new length are irrelevant and can be ignored.

A critical constraint is that your algorithm must use only constant extra space.

## 🔍 Examples
```
Input:  chars = ["a","a","b","b","c","c","c"]
Output: 6
Explanation: The groups are "aa", "bb", and "ccc".
"aa" compresses to "a2".
"bb" compresses to "b2".
"ccc" compresses to "c3".
The compressed string is "a2b2c3". After in-place modification, the array becomes ["a","2","b","2","c","3"].

Input:  chars = ["a"]
Output: 1
Explanation: The only group is "a", which has a length of 1. It remains "a".
The compressed string is "a". After in-place modification, the array remains ["a"].

Input:  chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
Output: 4
Explanation: The groups are "a" and "bbbbbbbbbbbb" (12 'b's).
"a" compresses to "a".
"bbbbbbbbbbbb" compresses to "b12".
The compressed string is "ab12". After in-place modification, the array becomes ["a","b","1","2"].
```

## 📌 Constraints
*   `1 <= chars.length <= 2000`
*   `chars[i]` is a lowercase English letter, uppercase English letter, digit, or symbol.

## 🤔 Understanding the Problem
The problem asks us to perform run-length encoding on an array of characters, but with a twist: the compression must happen directly within the input array (`in-place`), and we are restricted to using only a constant amount of additional memory. This means we cannot create a new array to build the result and then copy it back. We also need to be careful when a character count is a multi-digit number (e.g., 12), as each digit must be stored as a separate character in the array.

## 💡 Core Idea
The core idea is to use two pointers: one to read through the original array to identify groups of repeating characters, and another to write the compressed characters back into the *same* array from the beginning. This allows us to overwrite elements that have already been processed or are no longer needed, ensuring constant extra space.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern, specifically a "read and write" pointer approach. This pattern is ideal when you need to modify an array in-place and the new elements might occupy less space than the original, or when you need to process elements and store results in a compact form within the same data structure. Here, one pointer (`i`) iterates through the input array to identify groups of identical characters (the "read" pointer), while another pointer (`idx`) tracks where the next compressed character should be written in the array (the "write" pointer). This allows us to overwrite elements that have already been processed or are no longer needed, ensuring constant extra space.

## 📝 Step-by-Step Algorithm
1.  Initialize a `write_idx` (let's call it `idx`) to `0`. This pointer will keep track of the current position in the `chars` array where the next compressed character should be written. It will also ultimately represent the new length of the compressed array.
2.  Initialize a `read_idx` (let's call it `i`) to `0`. This pointer will iterate through the `chars` array to find groups of repeating characters.
3.  Start a main loop that continues as long as `read_idx` is less than the total length of the `chars` array (`n`).
    a.  Store the character at `chars[read_idx]` in a variable, say `current_char`. This marks the beginning of a new group.
    b.  Initialize a `count` for `current_char` to `0`.
    c.  Enter an inner loop to count consecutive occurrences of `current_char`:
        i.  While `read_idx` is within the array bounds (`read_idx < n`) AND the character at `chars[read_idx]` is equal to `current_char`:
            *   Increment `count`.
            *   Increment `read_idx` to move to the next character.
    d.  After the inner loop finishes, `read_idx` will be pointing to the first character of the *next* group, or beyond the end of the array. The `count` variable now holds the length of the `current_char` group.
    e.  Write `current_char` to `chars[write_idx]`.
    f.  Increment `write_idx` to prepare for the next character.
    g.  If `count` is greater than `1` (meaning the group needs its count appended):
        i.  Convert the integer `count` into its string representation (e.g., `to_string(count)` in C++).
        ii. Iterate through each character (digit) of this count string.
        iii. Write each digit character to `chars[write_idx]`.
        iv. Increment `write_idx` after writing each digit.
4.  Once the main loop finishes, all characters have been processed and compressed. The `write_idx` now holds the final length of the compressed array. Return `write_idx`.

## 💻 Solution
```cpp
class Solution {
public:
    int compress(vector<char>& chars) {
        // Get the total number of characters in the input array.
        int n = chars.size();
        
        // 'idx' is our write pointer. It tracks where the next compressed character
        // should be written in the 'chars' array. It also ultimately represents
        // the new length of the compressed array.
        int idx = 0;
        
        // 'i' is our read pointer. It iterates through the original 'chars' array
        // to find groups of consecutive repeating characters.
        // The loop continues as long as 'i' is within the bounds of the array.
        for (int i = 0; i < n;) {
            // Store the current character we are processing. This is the start of a new group.
            char ch = chars[i];
            
            // Initialize a counter for the current character's consecutive occurrences.
            int count = 0;
            
            // Inner loop to count how many times 'ch' repeats consecutively.
            // It advances 'i' past all occurrences of 'ch' in the current group.
            while (i < n && chars[i] == ch) {
                count++; // Increment count for each occurrence
                i++;     // Move read pointer to the next character
            }
            
            // After counting, write the character itself to the compressed array
            // at the position indicated by 'idx'.
            chars[idx++] = ch; // Write 'ch' at 'idx' and then increment 'idx'
            
            // If the character appeared more than once, we need to append its count.
            if (count > 1) {
                // Convert the integer count to a string.
                // For example, if count is 12, str will be "12".
                string str = to_string(count);
                
                // Iterate through each character (digit) in the count string.
                // For "12", this loop will run for '1' then for '2'.
                for (char dig : str) {
                    // Write each digit character to the compressed array.
                    chars[idx++] = dig; // Write 'dig' at 'idx' and then increment 'idx'
                }
            }
        }
        // After processing all characters, 'idx' holds the final length of the
        // compressed array. Return this length.
        return idx;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The outer loop iterates through the input array using the `read_idx` (`i`). The inner `while` loop also advances `read_idx`. Crucially, `read_idx` only moves forward and visits each character in the input array at most once. Therefore, the total number of operations is proportional to the number of characters, N. |
| **Space** | O(1) | The algorithm modifies the input array in-place. It uses only a few integer variables (`n`, `idx`, `i`, `count`) and a small temporary string for `to_string(count)`. The maximum number of digits for `count` (given `N <= 2000`) is 4 (for 1000-1999), which is a constant amount of space, not dependent on N in a way that grows arbitrarily large. Thus, it satisfies the constant extra space requirement. |

## 🔗 Related Problems
- 26. Remove Duplicates from Sorted Array
- 283. Move Zeroes
- 80. Remove Duplicates from Sorted Array II