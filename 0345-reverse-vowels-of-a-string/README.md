# 0345-reverse-vowels-of-a-string

## 📋 Problem Description
Given a string `s`, the task is to reverse only the vowel characters within the string and return the modified string. All other characters (consonants, special characters) must remain in their original positions. The vowels are defined as 'a', 'e', 'i', 'o', 'u', and they can appear in both lowercase and uppercase forms.

The function receives a single string `s` as input and must return the string `s` with its vowels reversed.

## 🔍 Examples
```
Input: s = "IceCreAm"
Output: "AceCreIm"
Explanation: The vowels in "IceCreAm" are 'I', 'e', 'e', 'A'. When reversed, they become 'A', 'e', 'e', 'I'. So, 'I' (at index 0) swaps with 'A' (at index 7). The 'e's remain in their relative positions.

Input: s = "leetcode"
Output: "leotcede"
Explanation: The vowels in "leetcode" are 'e', 'e', 'o', 'e'. When reversed, they become 'e', 'o', 'e', 'e'. The 'e' at index 1 swaps with the 'e' at index 7. The 'e' at index 2 swaps with the 'o' at index 4.
```

## 📌 Constraints
*   `1 <= s.length <= 3 * 10^5`
*   `s` consists of printable ASCII characters.

## 🤔 Understanding the Problem
The problem asks us to perform a specific type of in-place modification on a string: reversing only a subset of its characters (vowels) while preserving the positions of all other characters. This means we need a way to identify vowels efficiently and then swap them from the ends towards the center of the string. The key challenge is to correctly handle cases where one or both characters at the current pointers are not vowels, ensuring only actual vowels are considered for swapping.

## 💡 Core Idea
The core idea is to use two pointers, one starting from the beginning and one from the end of the string. These pointers will move towards each other, searching for vowels. Once two vowels are found (one from the left, one from the right), they are swapped, effectively reversing their positions relative to other vowels.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern. This pattern is highly effective when you need to process elements from both ends of a data structure (like a string or array) simultaneously, often for tasks involving searching for pairs, reversing, or partitioning. In this specific problem, we use two pointers to efficiently locate the next vowel from the left and the next vowel from the right. This allows us to swap them in place and achieve the desired reversal of only the vowels in a single pass through the string.

## 📝 Step-by-Step Algorithm
1.  **Helper Function `isVowel`**: Define a helper function, `isVowel(char ch)`, that takes a character `ch` as input. This function should return `true` if `ch` is any of 'a', 'e', 'i', 'o', 'u' (case-insensitive), and `false` otherwise.
2.  **Initialize Pointers**: Initialize two integer pointers: `l` (left pointer) to `0` (the beginning of the string) and `r` (right pointer) to `s.length() - 1` (the end of the string).
3.  **Iterate and Swap**: Enter a `while` loop that continues as long as `l` is less than `r`.
    a.  **Check Both Pointers**: Inside the loop, check the characters at `s[l]` and `s[r]` using the `isVowel` helper function.
    b.  **Case 1: Both are Vowels**: If both `s[l]` and `s[r]` are vowels:
        i.  Swap `s[l]` and `s[r]`.
        ii. Increment `l` (move left pointer to the right).
        iii. Decrement `r` (move right pointer to the left).
    c.  **Case 2: Left is Not a Vowel**: If `s[l]` is not a vowel, but `s[r]` is a vowel:
        i.  Increment `l` (move left pointer to the right) to find the next potential vowel. The right pointer `r` stays put, as `s[r]` is already a vowel candidate.
    d.  **Case 3: Right is Not a Vowel**: If `s[l]` is a vowel, but `s[r]` is not a vowel:
        i.  Decrement `r` (move right pointer to the left) to find the next potential vowel. The left pointer `l` stays put, as `s[l]` is already a vowel candidate.
    e.  **Case 4: Neither is a Vowel**: If neither `s[l]` nor `s[r]` are vowels (both are consonants or other characters):
        i.  Increment `l` and decrement `r` (move both pointers inwards) as these characters are not involved in the vowel reversal.
4.  **Return Result**: Once the `while` loop terminates (when `l` is no longer less than `r`), all vowel pairs have been found and swapped. Return the modified string `s`.

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
        // Initialize two pointers: 'l' for the left end and 'r' for the right end.
        int l = 0;
        int r = s.length() - 1;

        // Continue swapping as long as the left pointer is before the right pointer.
        while (l < r) {
            // Case 1: Both characters at 'l' and 'r' are vowels.
            if (isVowel(s[l]) && isVowel(s[r])) {
                // Swap the vowels.
                swap(s[l], s[r]);
                // Move both pointers inwards to find the next pair.
                l++;
                r--;
            }
            // Case 2: The character at 'l' is NOT a vowel, but 'r' IS a vowel.
            else if (!isVowel(s[l]) && isVowel(s[r])) {
                // Only move the left pointer inwards, as 'r' is already a vowel candidate.
                l++;
            }
            // Case 3: The character at 'l' IS a vowel, but 'r' is NOT a vowel.
            else if (isVowel(s[l]) && !isVowel(s[r])) {
                // Only move the right pointer inwards, as 'l' is already a vowel candidate.
                r--;
            }
            // Case 4: Neither character at 'l' nor 'r' is a vowel (both are consonants or non-vowels).
            else { // This covers the case where (!isVowel(s[l]) && !isVowel(s[r]))
                // Move both pointers inwards, as neither are vowels to be swapped.
                l++;
                r--;
            }
        }
        // After the loop, all vowels have been reversed in place.
        return s;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The two pointers `l` and `r` traverse the string from opposite ends. In the worst case, each character is visited and checked for being a vowel at most once. The `swap` operation is O(1). Therefore, the total time complexity is linear with respect to the length of the string `N`. |
| **Space** | O(1) | The solution modifies the input string in-place. No additional data structures are used that scale with the input size. The `isVowel` helper function uses constant extra space. |

## 🔗 Related Problems
- 125. Valid Palindrome
- 344. Reverse String
- 11. Container With Most Water