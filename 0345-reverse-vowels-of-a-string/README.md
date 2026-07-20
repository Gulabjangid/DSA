# 0345-reverse-vowels-of-a-string

## 📋 Problem Description
Given a string `s`, the task is to reverse only the vowels present in the string. All other characters (consonants, spaces, symbols, etc.) must remain in their original positions.

The vowels are defined as 'a', 'e', 'i', 'o', and 'u'. They can appear in both lowercase and uppercase forms and should be treated as vowels regardless of case.

The function should receive a string `s` as input and return the modified string with its vowels reversed.

## 🔍 Examples
```
Input:  s = "IceCreAm"
Output: "AceCreIm"
Explanation: The vowels in "IceCreAm" are ['I', 'e', 'e', 'A']. Reversing them gives ['A', 'e', 'e', 'I'].
             So, 'I' becomes 'A', the first 'e' stays 'e', the second 'e' stays 'e', and 'A' becomes 'I'.
```
```
Input:  s = "leetcode"
Output: "leotcede"
Explanation: The vowels in "leetcode" are ['e', 'e', 'o', 'e']. Reversing them gives ['e', 'o', 'e', 'e'].
             The first 'e' stays 'e', the second 'e' becomes 'o', 'o' becomes 'e', and the last 'e' stays 'e'.
```
```
Input:  s = "hello"
Output: "holle"
Explanation: The vowels in "hello" are ['e', 'o']. Reversing them gives ['o', 'e'].
```

## 📌 Constraints
*   `1 <= s.length <= 3 * 10^5`
*   `s` consists of printable ASCII characters.

## 🤔 Understanding the Problem
The problem asks us to perform an in-place modification of a string where only specific characters (vowels) are reversed, while all other characters maintain their original relative and absolute positions. The key challenge is efficiently identifying vowels, considering both lowercase and uppercase, and then swapping them without disturbing non-vowel characters.

## 💡 Core Idea
The most efficient way to reverse elements within a sequence while preserving the positions of other elements is to use two pointers, one starting from each end of the sequence, moving towards the center.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern. We initialize two pointers, one at the beginning (`l`) and one at the end (`r`) of the string. The goal is to find a vowel at `l` and a vowel at `r`, then swap them. If a pointer encounters a non-vowel, it simply moves inward until it finds a vowel. This approach allows us to reverse the vowels in-place with optimal time complexity, as we only iterate through the string once.

## 📝 Step-by-Step Algorithm
1.  **Helper Function `isVowel`**: Define a helper function, `isVowel(char ch)`, that takes a character `ch` and returns `true` if `ch` is a vowel (case-insensitive: 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'), and `false` otherwise.
2.  **Initialize Pointers**: Initialize two integer pointers: `l` to `0` (the index of the first character of the string) and `r` to `s.length() - 1` (the index of the last character of the string).
3.  **Iterate and Swap**: Start a `while` loop that continues as long as `l` is less than `r`. Inside the loop:
    a.  **Check Left Character**: Use the `isVowel` helper function to check if the character at `s[l]` is a vowel.
    b.  **Check Right Character**: Use the `isVowel` helper function to check if the character at `s[r]` is a vowel.
    c.  **Both are Vowels**: If both `s[l]` and `s[r]` are vowels, swap these two characters. After swapping, increment `l` and decrement `r` to move both pointers inward.
    d.  **Left is Not Vowel**: If `s[l]` is not a vowel but `s[r]` is a vowel, it means `s[l]` should be skipped. Increment `l` to find the next potential vowel from the left. `r` remains in place.
    e.  **Right is Not Vowel**: If `s[l]` is a vowel but `s[r]` is not a vowel, it means `s[r]` should be skipped. Decrement `r` to find the next potential vowel from the right. `l` remains in place.
    f.  **Neither are Vowels**: If neither `s[l]` nor `s[r]` are vowels, both should be skipped. Increment `l` and decrement `r` to move both pointers inward.
4.  **Return Result**: Once the `while` loop terminates (when `l` becomes greater than or equal to `r`), all vowels will have been reversed. Return the modified string `s`.

## 💻 Solution
```cpp
class Solution {
public:
    // Helper function to check if a character is a vowel (case-insensitive).
    bool isVowel(char ch) {
        // Check for both lowercase and uppercase vowels.
        return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
                ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U');
    }

    string reverseVowels(string s) {
        // Initialize two pointers: 'l' for the left end and 'r' for the right end of the string.
        int l = 0;
        int r = s.length() - 1;

        // Continue swapping as long as the left pointer is before the right pointer.
        while (l < r) {
            // Case 1: Both characters at 'l' and 'r' are vowels.
            if (isVowel(s[l]) && isVowel(s[r])) {
                // Swap the vowels.
                swap(s[l], s[r]);
                // Move both pointers inward to find the next pair of vowels.
                l++;
                r--;
            }
            // Case 2: The character at 'l' is NOT a vowel, but the character at 'r' IS a vowel.
            // We need to find the next vowel from the left.
            else if (!isVowel(s[l]) && isVowel(s[r])) {
                l++; // Move left pointer inward, 'r' stays put as s[r] is a potential swap candidate.
            }
            // Case 3: The character at 'l' IS a vowel, but the character at 'r' is NOT a vowel.
            // We need to find the next vowel from the right.
            else if (isVowel(s[l]) && !isVowel(s[r])) {
                r--; // Move right pointer inward, 'l' stays put as s[l] is a potential swap candidate.
            }
            // Case 4: Neither character at 'l' nor 'r' are vowels.
            // Skip both non-vowels by moving both pointers inward.
            else { // This covers the case: (!isVowel(s[l]) && !isVowel(s[r]))
                l++;
                r--;
            }
        }
        // Return the modified string with vowels reversed.
        return s;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The two pointers `l` and `r` traverse the string at most once, performing constant time operations (vowel check, swap) at each step. |
| **Space** | O(1) | The solution modifies the input string in-place and uses only a few constant-space variables for pointers and the helper function. |

## 🔗 Related Problems
-   125. Valid Palindrome
-   167. Two Sum II - Input Array Is Sorted
-   922. Sort Array By Parity II