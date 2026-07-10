# 0443-string-compression

## 📋 Problem Description
Given an array of characters `chars`, compress it using a specific algorithm. The compression process involves iterating through groups of consecutive repeating characters:
1. If a group consists of a single character (length 1), append only that character to the compressed result.
2. If a group consists of multiple identical characters (length > 1), append the character itself, followed by its count. Note that counts 10 or greater should be represented by multiple characters (e.g., 12 becomes '1', '2').

The compressed string should not be returned as a new string. Instead, it must be stored directly within the input character array `chars` itself (in-place modification). After modifying the array, the function should return the new total length of the compressed array. Characters in the array beyond this returned length are irrelevant.

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
Explanation: The groups are "a" and "bbbbbbbbbbbb" (12 'b's). This compresses to "ab12".
After modifying the input array in-place, the first 4 characters of chars should be ["a","b","1","2"].
```

## 📌 Constraints
*   `1 <= chars.length <= 2000`
*   `chars[i]` is a lowercase English letter, uppercase English letter, digit, or symbol.

## 🤔 Understanding the Problem
The problem asks us to compress an array of characters by replacing consecutive repeating characters with the character itself followed by its count (if the count is greater than 1). The critical part is that this compression must happen *in-place* within the original `chars` array, using only *constant extra space*. This means we cannot create a new array to store the compressed result and then copy it back. We need to manage reading from one part of the array and writing to another, potentially overlapping, part of the same array.

## 💡 Core Idea
The core idea is to use two pointers: one to read through the original array and identify character groups, and another to write the compressed characters back into the *beginning* of the same array. This allows for in-place modification without needing additional memory proportional to the input size.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern. This pattern is particularly well-suited for problems that require in-place modification of an array or list, especially when elements need to be rearranged or filtered. Here, one pointer (`i`) acts as a "read" pointer, scanning the original array to identify groups of characters. The other pointer (`idx`) acts as a "write" pointer, indicating where the next compressed character (or digit of a count) should be placed in the array. By carefully managing these two pointers, we can overwrite the original data with the compressed data without losing necessary information or using significant extra space.

## 📝 Step-by-Step Algorithm
1.  Initialize two integer pointers:
    *   `idx = 0`: This will be our "write" pointer, indicating the next available position in the `chars` array to write a compressed character. It will also ultimately represent the new length of the compressed array.
    *   `i = 0`: This will be our "read" pointer, used to iterate through the original `chars` array.
2.  Get the total length of the input array, `n = chars.size()`.
3.  Start a main loop that continues as long as `i < n` (meaning we haven't read all characters from the original array).
    a.  Inside this loop, store the character at the current read pointer `chars[i]` into a temporary variable, say `ch`. This `ch` is the character for which we will count consecutive occurrences.
    b.  Initialize a `count` variable to 0.
    c.  Start an inner `while` loop: As long as `i < n` and `chars[i]` is equal to `ch`, increment `count` and advance the read pointer `i` to the next character. This inner loop effectively finds the end of the current group of repeating characters and counts their occurrences.
    d.  After the inner loop finishes, `ch` holds the character of the group, and `count` holds its frequency.
    e.  First, write the character `ch` itself to the `chars` array at the `idx` position. Then, increment `idx` to point to the next available write position.
    f.  If `count` is greater than 1 (meaning the character appeared more than once and its count needs to be appended):
        i.  Convert the integer `count` into its string representation (e.g., `12` becomes `"12"`).
        ii. Iterate through each character (digit) in this string.
        iii. For each digit character, write it to the `chars` array at the `idx` position. Then, increment `idx` to point to the next available write position.
4.  Once the main loop finishes, the `idx` pointer will hold the final length of the compressed array. Return `idx`.

## 💻 Solution
```cpp
class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size(); // Get the total number of characters in the input array.
        int idx = 0;          // This pointer 'idx' will track the current position to write to in the 'chars' array.
                              // It also ultimately represents the length of the compressed array.

        // The main loop iterates through the input array using 'i' as the read pointer.
        // 'i' advances by the length of each character group.
        for (int i = 0; i < n;) {
            char ch = chars[i]; // Store the current character we are observing for a group.
            int count = 0;      // Initialize a counter for the current character's consecutive occurrences.

            // Inner loop to count consecutive repeating characters.
            // It advances 'i' past all characters in the current group.
            while (i < n && chars[i] == ch) {
                count++; // Increment count for each occurrence.
                i++;     // Move the read pointer 'i' to the next character.
            }

            // After the inner loop, 'ch' is the character and 'count' is its frequency.

            // First, write the character itself to the compressed array.
            chars[idx++] = ch; // Write 'ch' to the position 'idx' and then increment 'idx'.

            // If the character appeared more than once, append its count.
            if (count > 1) {
                // Convert the integer count to a string.
                // For example, if count is 12, str will be "12".
                string str = to_string(count);

                // Iterate through each digit of the count string.
                // For example, for "12", it will process '1' then '2'.
                for (char dig : str) {
                    // Write each digit character to the compressed array.
                    chars[idx++] = dig; // Write 'dig' to position 'idx' and then increment 'idx'.
                }
            }
        }
        // 'idx' now holds the total number of characters written to the array,
        // which is the new length of the compressed array.
        return idx;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The outer loop iterates through the array with `i`, and the inner `while` loop also advances `i`. Each character in the input array `chars` is visited by `i` at most once. The `to_string` conversion and writing digits take `O(log10(count))` time, which is negligible compared to `N` for practical `N` values (e.g., `log10(2000)` is about 3.3). |
| **Space** | O(1) | We modify the input array in-place. A few integer variables are used, and a temporary `string` for `to_string(count)` is created. The maximum length of this string is very small (e.g., 4 characters for `count = 2000`), which is considered constant space relative to the input size `N`. |

## 🔗 Related Problems
-   26. Remove Duplicates from Sorted Array
-   283. Move Zeroes
-   80. Remove Duplicates from Sorted Array II