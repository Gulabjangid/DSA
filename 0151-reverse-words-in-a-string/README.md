# 0151-reverse-words-in-a-string

## 📋 Problem Description
Given an input string `s`, the task is to reverse the order of the words within it.

A "word" is defined as a sequence of non-space characters. Words in the input string `s` will be separated by at least one space.

The function must return a new string where the words are in reverse order, concatenated by a single space. It's important to handle various formatting issues:
*   The input string `s` may contain leading or trailing spaces.
*   There might be multiple spaces between words.
*   The returned string should only have a single space separating words and must not include any extra leading or trailing spaces.

The input string `s` will consist of English letters (upper-case and lower-case), digits, and spaces. It is guaranteed to contain at least one word.

## 🔍 Examples
```
Input: s = "the sky is blue"
Output: "blue is sky the"

Input: s = "  hello world  "
Output: "world hello"
Explanation: Your reversed string should not contain leading or trailing spaces.

Input: s = "a good   example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.
```

## 📌 Constraints
*   `1 <= s.length <= 10^4`
*   `s` contains English letters (upper-case and lower-case), digits, and spaces `' '`.
*   There is **at least one** word in `s`.

## 🤔 Understanding the Problem
This problem asks us to reorder words in a sentence, not just reverse the entire string character by character. The main challenges lie in correctly identifying words amidst varying numbers of spaces, and then formatting the output string to have exactly one space between words, with no leading or trailing spaces. A simple string reversal would reverse characters, not words, and wouldn't handle the space normalization requirements.

## 💡 Core Idea
The core idea behind the provided solution is a two-pass reversal strategy. First, reverse the entire string to bring the words into their correct *relative* reversed order (though each word's characters will also be reversed). Then, iterate through this globally reversed string, identify each individual word, reverse its characters back to their original orientation, and append it to a result string while carefully managing spaces.

## 🧠 Approach — String Manipulation / Two-Pass Reversal
This problem is effectively solved using a **String Manipulation** approach, specifically a **Two-Pass Reversal** technique. This pattern is particularly suitable here because we need to reverse the order of logical units (words) within a string while also cleaning up its structure (removing extra spaces).

The two-pass reversal works by first performing a global reversal on the entire string. This places the words in their final reversed order, but with their internal characters also reversed. For example, "the sky" becomes "yks eht". In the second pass, we iterate through this globally reversed string, identify each "word" (which is currently character-reversed), reverse its characters back to their original form (e.g., "yks" becomes "sky"), and then append it to our result string. This method elegantly handles the word reordering and simplifies the process of extracting and cleaning up words.

## 📝 Step-by-Step Algorithm
1.  **Reverse the entire input string `s`**: This initial step reverses the order of all characters in the string. For example, "the sky is blue" becomes "eulb si yks eht". This effectively puts the words in their final reversed order, but each word's characters are also reversed.
2.  **Initialize an empty string `ans`**: This string will store our final, correctly formatted result.
3.  **Iterate through the modified string `s`**: Use an index `i` to traverse `s` from beginning to end.
4.  **Skip leading spaces for the current segment**: Inside the loop, advance `i` past any consecutive space characters. This handles leading spaces in the globally reversed string and multiple spaces between words.
5.  **Extract a word**: If a non-space character is found (meaning we are at the start of a word):
    *   Initialize an empty temporary string `word`.
    *   Append characters from `s[i]` to `word` until a space is encountered or the end of `s` is reached. Increment `i` as characters are added.
6.  **Reverse the extracted word**: Once a `word` has been fully extracted (e.g., "eulb"), reverse its characters (e.g., "eulb" becomes "blue").
7.  **Append to result string `ans`**:
    *   If the `word` is not empty (i.e., we actually extracted characters, not just skipped spaces):
        *   If `ans` already contains words (i.e., `ans.length() > 0`), append a single space character to `ans` first. This ensures words are separated by exactly one space.
        *   Append the now-correctly-oriented `word` to `ans`.
8.  **Continue iteration**: Repeat steps 4-7 until the index `i` has traversed the entire string `s`.
9.  **Return `ans`**: The `ans` string now contains the words in reverse order, separated by single spaces, with no leading or trailing spaces.

## 💻 Solution

```cpp
class Solution {
public:
    string reverseWords(string s) {
        // Step 1: Reverse the entire input string.
        // Example: "the sky is blue" becomes "eulb si yks eht"
        // This puts words in reverse order, but each word's characters are also reversed.
        reverse(s.begin(), s.end());
        
        // Step 2: Initialize an empty string to build the result.
        string ans;

        // Step 3: Iterate through the globally reversed string.
        for (int i = 0; i < s.length(); ) { // 'i' is managed inside the loop
            // Step 4: Skip any leading spaces for the current segment.
            // This handles original leading/trailing spaces and multiple spaces between words.
            while (i < s.length() && s[i] == ' ') {
                i++;
            }

            // If we reached the end of the string after skipping spaces, break.
            if (i == s.length()) {
                break;
            }

            // Step 5: Extract a word.
            string word = "";
            while (i < s.length() && s[i] != ' ') {
                word += s[i];
                i++;
            }

            // Step 6: Reverse the extracted word.
            // Example: "eulb" becomes "blue"
            reverse(word.begin(), word.end());

            // Step 7: Append to result string 'ans'.
            // Only append if a valid word was found (not just a sequence of spaces).
            if (word.length() > 0) {
                // If 'ans' already has words, add a single space separator.
                if (ans.length() > 0) {
                    ans += ' ';
                }
                // Append the correctly oriented word.
                ans += word;
            }
            // The outer loop's 'i' is already advanced by the inner while loops.
        }
        
        // Step 9: Return the final result string.
        return ans;
    }
};

```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The initial `reverse` operation takes O(N). The subsequent loop iterates through the string once, and each character is processed (appended to `word`, reversed, appended to `ans`) a constant number of times in total. String appends are amortized O(1) for single characters and O(L) for string `word` of length `L`, summing up to O(N) overall. |
| **Space** | O(N) | An additional string `ans` is created to store the result, which can be up to the length of the input string `s`. The temporary `word` string also takes up space, but its maximum length is `N` and it's reused. |

## 🔗 Related Problems
- 186. Reverse Words in a String II
- 557. Reverse Words in a String III
- 344. Reverse String