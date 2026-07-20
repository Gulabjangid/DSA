# 0345-reverse-vowels-of-a-string

## 📋 Problem Description
Given a string `s`, the task is to reverse only the vowels present in the string and return the modified string. All other characters (consonants and non-alphabetic characters) should remain in their original positions.

The vowels to consider are 'a', 'e', 'i', 'o', 'u', and their uppercase counterparts 'A', 'E', 'I', 'O', 'U'. Vowels can appear multiple times in the string.

The function receives a single string `s` as input and must return the string with its vowels reversed.

## 🔍 Examples
```
Input:  s = "IceCreAm"
Output: "AceCreIm"
Explanation: The vowels in "IceCreAm" are ['I', 'e', 'e', 'A']. Reversing them gives ['A', 'e', 'e', 'I'].
             So, 'I' becomes 'A', first 'e' stays 'e', second 'e' stays 'e', and 'A' becomes 'I'.

Input:  s = "leetcode"
Output: "leotcede"
Explanation: The vowels in "leetcode" are ['e', 'e', 'o', 'e']. Reversing them gives ['e', 'o', 'e', 'e'].
             So, first 'e' stays 'e', second 'e' becomes 'o', 'o' becomes 'e', and last 'e' stays 'e'.
```

## 📌 Constraints
*   `1 <= s.length <= 3 * 10^5`
*   `s` consists of printable ASCII characters.

## 🤔 Understanding the Problem
The problem asks us to perform an in-place modification of a string where only specific characters (vowels) are reversed, while the positions and values of all other characters remain unchanged. This means we need a way to identify vowels efficiently and then swap them from the outer ends inwards. A key aspect is handling both lowercase and uppercase vowels correctly. The problem is non-trivial because we cannot simply reverse the entire string; we must selectively reverse only a subset of its characters.

## 💡 Core Idea
The most efficient way to reverse specific elements within a sequence while preserving the relative order of others is to use the Two Pointers technique. We can use one pointer starting from the beginning and another from the end, moving them towards each other, and swapping only when both pointers land on vowels.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern. This pattern is highly effective for problems that involve processing elements from both ends of a sequence, especially when performing in-place modifications or searching for pairs that satisfy a certain condition. Here, we want to swap vowels, effectively reversing their order while maintaining the relative order of consonants. Two pointers allow us to efficiently find the next vowel from the left and the next vowel from the right, swap them, and continue this process until the pointers meet or cross, ensuring an optimal traversal of the string.

## 📝 Step-by-Step Algorithm
1.  **Helper Function `isVowel`**: Create a helper function, `isVowel(char ch)`, that takes a character `ch` as input. It should return `true` if `ch` is any of 'a', 'e', 'i', 'o', 'u' (lowercase) or 'A', 'E', 'I', 'O', 'U' (uppercase), and `false` otherwise.
2.  **Initialize Pointers**: Initialize two integer pointers:
    *   `l` (left pointer) to `0` (the beginning of the string).
    *   `r` (right pointer) to `s.length() - 1` (the end of the string).
3.  **Iterate and Swap**: Enter a `while` loop that continues as long as `l < r`.
    *   **Case 1: Both `s[l]` and `s[r]` are vowels**:
        *   If `isVowel(s[l])` is `true` AND `isVowel(s[r])` is `true`:
            *   Swap the characters `s[l]` and `s[r]`.
            *   Increment `l` by 1.
            *   Decrement `r` by 1.
    *   **Case 2: `s[l]` is not a vowel, `s[r]` is a vowel**:
        *   If `isVowel(s[l])` is `false` AND `isVowel(s[r])` is `true`:
            *   Increment `l` by 1 (move past the non-vowel on the left).
    *   **Case 3: `s[l]` is a vowel, `s[r]` is not a vowel**:
        *   If `isVowel(s[l])` is `true` AND `isVowel(s[r])` is `false`:
            *   Decrement `r` by 1 (move past the non-vowel on the right).
    *   **Case 4: Neither `s[l]` nor `s[r]` are vowels**:
        *   If `isVowel(s[l])` is `false` AND `isVowel(s[r])` is `false`:
            *   Increment `l` by 1.
            *   Decrement `r` by 1.
4.  **Return Result**: Once the `while` loop terminates (when `l >= r`), all necessary swaps have been performed. Return the modified string `s`.

## 💻 Solution
```cpp
class Solution {
public:
    // Helper function to check if a character is a vowel (case-insensitive)
    bool isVowel(char ch) {
        // Check for lowercase vowels
        // Check for uppercase vowels
        return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || 
                ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U');
    }

    string reverseVowels(string s) {
        // Initialize two pointers: 'l' for the left end and 'r' for the right end
        int l = 0;
        int r = s.length() - 1;

        // Continue swapping as long as the left pointer is before the right pointer
        while (l < r) {
            // Case 1: Both characters at 'l' and 'r' are vowels
            if (isVowel(s[l]) && isVowel(s[r])) {
                // Swap the vowels
                swap(s[l], s[r]);
                // Move both pointers inwards
                l++;
                r--;
            } 
            // Case 2: Character at 'l' is NOT a vowel, but character at 'r' IS a vowel
            else if (!isVowel(s[l]) && isVowel(s[r])) {
                // Only move the left pointer inwards, as 's[l]' is not a vowel
                l++;
            } 
            // Case 3: Character at 'l' IS a vowel, but character at 'r' is NOT a vowel
            else if (isVowel(s[l]) && !isVowel(s[r])) {
                // Only move the right pointer inwards, as 's[r]' is not a vowel
                r--;
            } 
            // Case 4: Neither character at 'l' nor 'r' are vowels
            else { // (!isVowel(s[l]) && !isVowel(s[r]))
                // Move both pointers inwards, as neither are vowels to be swapped
                l++;
                r--;
            }
        }
        // Return the modified string with vowels reversed
        return s;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | In the worst case, both pointers traverse the entire string once. Each character is visited and checked for being a vowel at most a constant number of times. |
| **Space** | O(1) | The solution modifies the input string in-place and uses only a few constant-space variables for pointers and the helper function. |

## 🔗 Related Problems
- 11. Container With Most Water
- 167. Two Sum II - Input Array Is Sorted
- 925. Long Pressed Name