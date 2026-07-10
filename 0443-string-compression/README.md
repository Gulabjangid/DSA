# 0443-string-compression

## 📋 Problem Description
You are given an array of characters `chars`. Your task is to compress this array using a specific algorithm and modify the input array in-place.

The compression algorithm works as follows:
1.  Initialize an empty conceptual string `s`.
2.  Iterate through the `chars` array, identifying groups of **consecutive repeating characters**.
3.  For each group:
    *   If the group's length is `1`, append only the character itself to `s`.
    *   If the group's length is greater than `1`, append the character followed by its length to `s`.
4.  The compressed string `s` should not be returned directly. Instead, its contents must be stored back into the original `chars` array, starting from the beginning.
5.  Note that if a group's length is `10` or longer (e.g., `12`), its digits will be split into multiple characters (e.g., `'1'`, `'2'`) in the `chars` array.
6.  After modifying the input array `chars` in-place, you must return the new total length of the compressed array. Any characters in `chars` beyond this new length are irrelevant and should be ignored.

The algorithm must use only constant extra space.

## 🔍 Examples
```
Input:  chars = ["a","a","b","b","c","c","c"]
Output: 6
Explanation: The groups are "aa", "bb", and "ccc". This compresses to "a2b2c3".
After modifying the input array in-place, the first 6 characters of chars should be ["a","2","b","2","c","3"].
```
```
Input:  chars = ["a"]
Output: 1
Explanation: The only group is "a", which remains uncompressed since it is a single character.
After modifying the input array in-place, the first character of chars should be ["a"].
```
```
Input:  chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
Output: 4
Explanation: The groups are "a" and "bbbbbbbbbbbb". This compresses to "ab12".
After modifying the input array in-place, the first 4 characters of chars should be ["a","b","1","2"].
```

## 📌 Constraints
*   `1 <= chars.length <= 2000`
*   `chars[i]` is a lowercase English letter, uppercase English letter, digit, or symbol.

## 🤔 Understanding the Problem
This problem asks us to perform a run-length encoding on a character array, but with a crucial twist: the compression must happen *in-place* within the original array, and we are restricted to using only *constant extra space*. This means we cannot create a new array to store the result and then copy it back. We also need to pay attention to how multi-digit counts (like `12` for twelve 'b's) are represented as individual characters (`'1'`, `'2'`) in the compressed output.

## 💡 Core Idea
The core idea is to use two pointers: one to read through the original array and identify character groups, and another to write the compressed characters into the same array from the beginning. This allows for in-place modification without needing additional significant memory.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern, specifically a "read" and "write" pointer approach. This pattern is highly effective for problems that require modifying an array in-place while maintaining constant extra space. One pointer (`i` in our solution) iterates through the original array to *read* elements and identify groups. The other pointer (`idx` in our solution) is used to *write* the processed (compressed) elements back into the same array, starting from the beginning. This way, we overwrite the old, uncompressed data with the new, compressed data as we go, ensuring constant space complexity.

## 📝 Step-by-Step Algorithm
1.  Initialize a `write_idx` (let's call it `idx`) to `0`. This pointer will keep track of the current position where the next compressed character should be written in the `chars` array. It will also ultimately represent the new length of the compressed array.
2.  Initialize a `read_idx` (let's call it `i`) to `0`. This pointer will iterate through the original `chars` array from left to right to identify character groups.
3.  Start a main loop that continues as long as `read_idx` is less than the total length of the `chars` array (`n`):
    a.  Store the character at `chars[read_idx]` in a temporary variable, say `current_char`. This is the character whose consecutive group we are about to count.
    b.  Initialize a `count` for `current_char` to `0`.
    c.  Start an inner loop: while `read_idx` is less than `n` AND the character at `chars[read_idx]` is equal to `current_char`:
        i.  Increment `count`.
        ii. Increment `read_idx` to move to the next character in the original array.
    d.  After this inner loop finishes, `read_idx` will be pointing to the first character of the *next* distinct group (or beyond the end of the array). `current_char` and `count` now hold the character and length of the group just processed.
    e.  Write `current_char` to `chars[idx]`.
    f.  Increment `idx` to prepare for the next character to be written.
    g.  If `count` is greater than `1` (meaning the group needs its length appended):
        i.  Convert the integer `count` into its string representation (e.g., `12` becomes the string `"12"`).
        ii. Iterate through each character (digit) of this string.
        iii. Write each digit character to `chars[idx]`.
        iv. Increment `idx` after writing each digit.
4.  Once the main loop completes, `idx` will contain the final length of the compressed array. Return `idx`.

## 💻 Solution
```cpp
class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size(); // Get the total number of characters in the input array.
        int idx = 0;          // This 'idx' pointer will track where to write the compressed characters.
                              // It also serves as the final length of the compressed array.

        // The 'i' pointer will iterate through the original array to read character groups.
        // It advances by the length of each group.
        for (int i = 0; i < n;) {
            char ch = chars[i]; // Store the current character we are processing (e.g., 'a').
            int count = 0;      // Initialize count for the current group of repeating characters.

            // Inner loop to count consecutive occurrences of 'ch'.
            // 'i' advances through the group, effectively "consuming" it.
            while (i < n && chars[i] == ch) {
                count++; // Increment count for each occurrence.
                i++;     // Move to the next character in the original array.
            }
            // After this loop, 'i' points to the first character of the next group
            // or has reached the end of the array.
            // 'ch' and 'count' now represent the group just processed (e.g., 'a', 3 for "aaa").

            // Write the character itself to the compressed array at 'idx'.
            chars[idx++] = ch;

            // If the count is greater than 1, we need to append the count as digits.
            if (count > 1) {
                // Convert the integer count to a string.
                // E.g., if count is 12, str becomes "12".
                string str = to_string(count);
                
                // Iterate through each character (digit) of the count string.
                for (char dig : str) {
                    // Write each digit to the compressed array.
                    // E.g., for "12", first '1' is written, then '2'.
                    chars[idx++] = dig;
                }
            }
        }
        // 'idx' now holds the total number of characters in the compressed array.
        return idx;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The outer loop iterates through the `chars` array using `i`. The inner `while` loop also advances `i`. Crucially, `i` never decrements and each character in the input array is visited and processed a constant number of times across both loops. The `to_string` conversion and writing digits takes `O(log10(C))` time for a count `C`, which is very small (max 4 digits for `N=2000`) and effectively constant in the context of `N` operations. |
| **Space** | O(1) | We modify the input array in-place and use only a few constant extra variables (`n`, `idx`, `i`, `ch`, `count`). The temporary `string str` created by `to_string(count)` has a maximum length of 4 characters (for `count = 2000`), which is considered constant extra space. |

## 🔗 Related Problems
- 26. Remove Duplicates from Sorted Array
- 283. Move Zeroes
- 80. Remove Duplicates from Sorted Array II