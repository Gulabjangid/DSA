# 0345-reverse-vowels-of-a-string

## 📋 Problem Description
Given a string `s`, the task is to reverse only the vowels present in the string. All other characters (consonants and non-alphabetic characters) must remain in their original positions. The vowels are defined as 'a', 'e', 'i', 'o', 'u', and they can appear in both lowercase and uppercase forms. The function should return the modified string.

## 🔍 Examples
```
Input:  s = "IceCreAm"
Output: "AceCreIm"
Explanation: The vowels in "IceCreAm" are ['I', 'e', 'e', 'A']. Reversing them gives ['A', 'e', 'e', 'I'].
             So, 'I' at index 0 becomes 'A', 'e' at index 2 stays 'e', 'e' at index 4 stays 'e', and 'A' at index 6 becomes 'I'.

Input:  s = "leetcode"
Output: "leotcede"
Explanation: The vowels in "leetcode" are ['e', 'e', 'o', 'e']. Reversing them gives ['e', 'o', 'e', 'e'].
             The first 'e' at index 1 swaps with the last 'e' at index 7. The 'e' at index 2 swaps with 'o' at index 4.
```

## 📌 Constraints
*   `1 <= s.length <= 3 * 10^5`
*   `s` consists of printable ASCII characters.

## 🤔 Understanding the Problem
The core of this problem is to identify vowels within a string and then reverse their order while keeping all non-vowel characters fixed. This isn't a simple string reversal; it's a conditional reversal. We need an efficient way to find vowels from both ends of the string and swap them, moving inwards until all relevant vowels have been processed. The case-insensitivity of vowels ('a'/'A', 'e'/'E', etc.) is a crucial detail to handle.

## 💡 Core Idea
The key insight is that we only care about the relative order of vowels. We can use two pointers, one starting from the beginning and one from the end, to find vowels. Once two vowels are found, one from each end, they are swapped, and the pointers move inward. This ensures that vowels are reversed in place.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern. This pattern is ideal when you need to process elements from both ends of a data structure (like an array or string) simultaneously, often moving towards the center. In this specific problem, we use two pointers because we want to reverse elements (vowels) by pairing them up from opposite ends of the string. The left pointer searches for the next vowel from the beginning, and the right pointer searches for the next vowel from the end. When both pointers land on vowels, we swap them, effectively reversing their positions relative to other vowels.

## 📝 Step-by-Step Algorithm

1.  **Helper Function `isVowel`**: Create a helper function, `isVowel(char ch)`, that takes a character `ch` as input. This function should return `true` if `ch` is any of 'a', 'e', 'i', 'o', 'u' (lowercase) or 'A', 'E', 'I', 'O', 'U' (uppercase), and `false` otherwise.

2.  **Initialize Pointers**: In the main `reverseVowels` function, initialize two integer pointers:
    *   `left` to `0` (pointing to the first character of the string).
    *   `right` to `s.length() - 1` (pointing to the last character of the string).

3.  **Iterate and Swap**: Enter a `while` loop that continues as long as `left` is less than `right`. Inside this loop:
    *   **Check `s[left]`**: If `s[left]` is *not* a vowel (using the `isVowel` helper), increment `left` by 1. This moves the left pointer past the current non-vowel character, searching for the next vowel.
    *   **Check `s[right]`**: Else if `s[right]` is *not* a vowel, decrement `right` by 1. This moves the right pointer past the current non-vowel character, searching for the next vowel.
    *   **Both are Vowels**: If both `s[left]` and `s[right]` *are* vowels, it means we've found a pair of vowels to swap.
        *   Swap the characters `s[left]` and `s[right]`.
        *   Increment `left` by 1.
        *   Decrement `right` by 1.
        *   This moves both pointers inward, continuing the search for the next pair of vowels.

4.  **Return Result**: Once the `while` loop terminates (when `left` becomes greater than or equal to `right`), all vowel pairs will have been swapped. Return the modified string `s`.

## 💻 Solution
```cpp
class Solution {
public:
    // Helper function to check if a character is a vowel (case-insensitive)
    bool isVowel(char ch) {
        return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
                ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U');
    }

    string reverseVowels(string s) {
        // Initialize two pointers: 'l' for left, 'r' for right
        int l = 0;
        int r = s.length() - 1;

        // Loop as long as the left pointer is before the right pointer
        while (l < r) {
            // Case 1: Both characters at 'l' and 'r' are vowels
            if (isVowel(s[l]) && isVowel(s[r])) {
                // Swap the vowels
                swap(s[l], s[r]);
                // Move both pointers inward
                l++;
                r--;
            } 
            // Case 2: Character at 'l' is NOT a vowel, but character at 'r' IS a vowel
            else if (!isVowel(s[l]) && isVowel(s[r])) {
                // Move 'l' pointer to the right to find the next vowel
                l++;
            } 
            // Case 3: Character at 'l' IS a vowel, but character at 'r' is NOT a vowel
            else if (isVowel(s[l]) && !isVowel(s[r])) {
                // Move 'r' pointer to the left to find the next vowel
                r--;
            } 
            // Case 4: Neither character at 'l' nor 'r' are vowels
            else { // (!isVowel(s[l]) && !isVowel(s[r]))
                // Move both pointers inward, skipping non-vowels
                l++;
                r--;
            }
        }
        // Return the modified string
        return s;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The two pointers `l` and `r` traverse the string from opposite ends, meeting in the middle. Each character is visited and checked for being a vowel at most a constant number of times. Swapping takes O(1). |
| **Space** | O(N) | The input string `s` is passed by value in C++, meaning a copy of the string is created. This copy takes O(N) space. The auxiliary space used by the algorithm itself (pointers, temporary swap variable) is O(1). |

## 🔗 Related Problems
-   344. Reverse String
-   125. Valid Palindrome
-   11. Container With Most Water