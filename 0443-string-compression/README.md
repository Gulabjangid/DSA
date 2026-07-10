# 0443-string-compression

## 📋 Problem Description
Given an array of characters `chars`, compress it using the following algorithm:

Start with an empty string `s`. For each group of consecutive repeating characters in `chars`:
*   If the group's length is `1`, append only the character to `s`.
*   Otherwise (if the group's length is greater than `1`), append the character followed by its length.

The compressed string `s` should not be returned directly. Instead, it must be stored **in the input character array `chars` itself**. Note that group lengths of 10 or longer will be split into multiple characters (e.g., '1' followed by '2' for a length of 12).

After modifying the input array in-place, return the new length of the array. Characters in the array beyond this returned length do not matter and should be ignored.

You must write an algorithm that uses only constant extra space (O(1)).

## 🔍 Examples
```
Input:  chars = ["a","a","b","b","c","c","c"]
Output: 6
Explanation: The groups are "aa", "bb", and "ccc". This compresses to "a2b2c3".
After modification, chars should be ["a","2","b","2","c","3",...] (remaining characters don't matter).
```

```
Input:  chars = ["a"]
Output: 1
Explanation: The only group is "a", which remains uncompressed since its length is 1.
After modification, chars should be ["a",...] (remaining characters don't matter).
```

```
Input:  chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
Output: 4
Explanation: The groups are "a" and "bbbbbbbbbbbb" (12 'b's). This compresses to "ab12".
After modification, chars should be ["a","b","1","2",...] (remaining characters don't matter).
```

## 📌 Constraints
*   `1 <= chars.length <= 2000`
*   `chars[i]` is a lowercase English letter, uppercase English letter, digit, or symbol.

## 🤔 Understanding the Problem
The problem asks us to compress an array of characters in a specific way: groups of repeating characters are replaced by the character itself and its count (if count > 1). The crucial part is that this compression must happen **in-place** within the original `chars` array, using only **constant extra space**. This means we can't create a new array or string of significant size to store the result. We also need to handle multi-digit counts correctly, converting numbers like 12 into characters '1' and '2'.

## 💡 Core Idea
The core idea is to use a **two-pointer approach**. One pointer (`read_ptr`) iterates through the original array to identify groups of repeating characters, and another pointer (`write_ptr`) writes the compressed characters back into the *same* array, effectively overwriting the original content.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern. This pattern is ideal when you need to process an array or list and modify it in-place, especially when the order of elements matters or when you need to maintain distinct read and write positions. Here, one pointer (`i`) is used to read through the original array and identify consecutive character groups, while another pointer (`idx`) is used to write the compressed characters into the same array. This allows us to perform the compression without allocating significant additional memory, satisfying the O(1) space constraint.

## 📝 Step-by-Step Algorithm
1.  Initialize a `write_ptr` (let's call it `idx`) to `0`. This pointer will track the current position where the next compressed character should be written in the `chars` array.
2.  Initialize a `read_ptr` (let's call it `i`) to `0`. This pointer will iterate through the original `chars` array to find groups.
3.  Iterate with the `read_ptr` (`i`) from the beginning of the array up to its end (`n = chars.size()`).
4.  Inside the loop, store the character at `chars[i]` in a temporary variable `current_char`.
5.  Initialize a `count` for `current_char` to `0`.
6.  Use an inner `while` loop: as long as `read_ptr` (`i`) is within bounds and `chars[i]` is equal to `current_char`, increment `count` and advance `read_ptr` (`i`). This inner loop effectively finds the end of the current group and counts its length.
7.  After the inner loop finishes, `count` holds the length of the group of `current_char`s.
8.  Write `current_char` to `chars[idx]`, then increment `idx`.
9.  If `count` is greater than `1`:
    a. Convert `count` to a string (e.g., `to_string(count)`).
    b. Iterate through each character (digit) of this string.
    c. For each digit character, write it to `chars[idx]`, then increment `idx`.
10. **Important Adjustment**: After the inner `while` loop, the `read_ptr` (`i`) has advanced one step *past* the end of the current group (it's either at the start of the next distinct group or past the end of the array). The outer `for` loop will then increment `i` again. To prevent skipping the first character of the next group, we must decrement `i` by `1` at the end of the outer loop's current iteration. This ensures that when the outer `for` loop's `i++` executes, `i` correctly points to the start of the next group.
11. After the outer `for` loop completes, `idx` will represent the new length of the compressed array.
12. Return `idx`. (The `chars.resize(idx)` line in the provided solution is optional for LeetCode's judging but good practice if you were to actually truncate the vector).

## 💻 Solution
```cpp
class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size(); // Get the total number of characters in the input array.
        int idx = 0;          // This is our 'write pointer'. It tracks where the next compressed character should be placed.

        // The 'i' pointer is our 'read pointer'. It iterates through the original array.
        for (int i = 0; i < n; i++) {
            char ch = chars[i]; // Store the current character we are looking to compress.
            int count = 0;      // Initialize count for the current group of repeating characters.

            // Inner loop to count consecutive occurrences of 'ch'.
            // It advances 'i' past all characters in the current group.
            while (i < n && chars[i] == ch) {
                count++; // Increment count for each occurrence.
                i++;     // Move 'i' to the next character.
            }

            // After the inner loop, 'i' has moved one step too far.
            // The outer loop's 'i++' will then correctly position it at the start of the next group.
            i--; 

            // Write the character itself to the compressed array.
            chars[idx++] = ch;

            // If the count is greater than 1, we need to append the count as digits.
            if (count > 1) {
                // Convert the integer count to a string (e.g., 12 becomes "12").
                string str = to_string(count);
                // Iterate through each character (digit) of the count string.
                for (char dig : str) {
                    // Write each digit character to the compressed array.
                    chars[idx++] = dig;
                }
            }
        }
        
        // The problem asks for the new length, which is 'idx'.
        // The following line is optional for LeetCode's judge but good practice
        // if you actually wanted to truncate the vector.
        // chars.resize(idx); 
        
        return idx; // Return the new length of the compressed array.
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The `read_ptr` (`i`) traverses the array once. The `write_ptr` (`idx`) also moves forward, writing characters. Each character from the original array is visited a constant number of times. The `to_string` conversion for counts takes `O(log10(count))` time, which is proportional to the number of digits. Since the total number of digits across all counts cannot exceed N, the overall time remains linear. |
| **Space** | O(1) | We modify the input array in-place and only use a few integer variables (`n`, `idx`, `i`, `count`) and a temporary string for `to_string` conversion. The space used by `to_string` is proportional to the number of digits in the count, which is very small (max 4 digits for N=2000) and not dependent on N in a way that violates constant space complexity for the algorithm's state. |

## 🔗 Related Problems
- 26. Remove Duplicates from Sorted Array
- 283. Move Zeroes
- 80. Remove Duplicates from Sorted Array II