# 0151-reverse-words-in-a-string

## 📋 Problem Description
Given an input string `s`, the task is to reverse the order of its words. A "word" is defined as a sequence of non-space characters. Words in the input string `s` will be separated by at least one space. The function must return a new string where the words are in reverse order, concatenated by a single space. It's important to handle various whitespace scenarios: the returned string should not contain leading or trailing spaces, and multiple spaces between words in the input should be reduced to a single space in the output.

## 🔍 Examples
```
Input: s = "the sky is blue"
Output: "blue is sky the"

Input: s = "  hello world  "
Output: "world hello"
Explanation: Leading and trailing spaces are removed.

Input: s = "a good   example"
Output: "example good a"
Explanation: Multiple spaces between words are reduced to a single space.
```

## 📌 Constraints
*   `1 <= s.length <= 10^4`
*   `s` contains English letters (upper-case and lower-case), digits, and spaces `' '`.
*   There is at least one word in `s`.

## 🤔 Understanding the Problem
The problem asks us to reorder the words in a given sentence. The core challenge isn't just reversing the sequence of words, but also meticulously handling whitespace. We need to ensure that regardless of how many spaces appear at the beginning, end, or between words in the input, the output string is perfectly formatted: no leading/trailing spaces, and exactly one space separating each word. This means we can't simply split the string by space and reverse; we need a robust way to normalize the spacing.

## 💡 Core Idea
A clever trick for reversing the order of elements (like words in a sentence) while preserving the internal structure of each element is a two-step reversal: first, reverse the entire sequence, and then reverse each individual element back to its original orientation. This effectively reverses their *order* within the sequence.

## 🧠 Approach — String Manipulation
This problem is a classic example of string manipulation. The chosen approach leverages the two-step reversal strategy. First, reversing the entire input string places the words in their correct reverse *order*, but each word itself is spelled backward. Second, by iterating through this globally reversed string, we can identify individual words and reverse them back to their original spelling. This process naturally handles the removal of extra spaces by only appending words and single spaces as needed to a new result string.

## 📝 Step-by-Step Algorithm
1.  **Reverse the Entire String**: First, reverse the entire input string `s`. After this step, the words will be in the correct reverse order, but each word will be spelled backward (e.g., "the sky is blue" becomes "eulb si yks eht").
2.  **Initialize Result String**: Create an empty string, let's call it `ans`, which will store our final reversed sentence.
3.  **Iterate and Extract Words**: Traverse the now-reversed string `s` from left to right using an index `i`.
    *   **Skip Spaces**: At each position `i`, first skip any consecutive space characters. Increment `i` past all spaces until a non-space character is found or the end of the string is reached.
    *   **Extract Word**: If a non-space character is found, it marks the beginning of a word. Start building a temporary `word` string by appending characters from `s[i]` until a space is encountered or the end of `s` is reached. Increment `i` as characters are added to `word`.
    *   **Reverse Individual Word**: Once a `word` has been extracted (e.g., "eulb"), reverse this `word` to restore its original spelling (e.g., "blue").
    *   **Append to Result**: If the `word` is not empty (meaning a valid word was found):
        *   If `ans` already contains words (i.e., `ans.length() > 0`), append a single space `' '` to `ans` first. This ensures words are separated by exactly one space.
        *   Then, append the correctly spelled `word` to `ans`.
4.  **Return Result**: After iterating through the entire string `s`, the `ans` string will contain all words in reverse order, correctly spelled, and separated by single spaces. Return `ans`.

## 💻 Solution
```cpp
class Solution {
public:
    string reverseWords(string s) {
        // Step 1: Reverse the entire input string.
        // This is a crucial first step. It puts the words in the correct reverse order
        // relative to each other, but each word itself will be spelled backward.
        // Example: "the sky is blue" becomes "eulb si yks eht"
        reverse(s.begin(), s.end());

        string ans; // Initialize an empty string to build our final result.

        // Step 2: Iterate through the globally reversed string to process words.
        // We use 'i' to traverse the string 's'.
        for (int i = 0; i < s.length(); ) {
            // Step 2a: Skip any leading spaces for the current word.
            // This handles multiple spaces between words, as well as any leading/trailing
            // spaces that might have been present in the original input string 's'.
            while (i < s.length() && s[i] == ' ') {
                i++;
            }

            // If we've reached the end of the string after skipping spaces,
            // it means there are no more words to process, so we break.
            if (i == s.length()) {
                break;
            }

            // Step 2b: Extract the current word.
            // We build a temporary 'word' string by collecting non-space characters.
            string word = "";
            while (i < s.length() && s[i] != ' ') {
                word += s[i];
                i++; // Move to the next character
            }

            // Step 2c: Reverse the extracted word.
            // Since the entire string 's' was reversed initially, each extracted 'word'
            // is currently spelled backward. We reverse it to restore its original spelling.
            // Example: If 'word' was "eulb", it becomes "blue".
            reverse(word.begin(), word.end());

            // Step 2d: Append the processed word to the result string 'ans'.
            // We need to ensure words are separated by a single space and no extra spaces
            // are added at the beginning.
            if (word.length() > 0) { // Only append if a valid word was actually found.
                if (ans.length() > 0) { // If 'ans' already contains words, add a space first.
                    ans += ' ';
                }
                ans += word; // Append the correctly spelled word.
            }
        }
        return ans; // Return the final string with words in reverse order and proper spacing.
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Reversing the entire string `s` takes O(N) time. The subsequent loop iterates through `s` once. Inside the loop, characters are appended to `word` and then to `ans`. Each character from the original string is processed a constant number of times (once for global reverse, once for word extraction, once for word reverse, once for appending to `ans`). String concatenations in C++ can sometimes be O(length of string), but amortized over building the entire `ans` string, the total time complexity remains linear, O(N), where N is the length of `s`. |
| **Space** | O(N) | An additional string `ans` is created to store the result, which in the worst case can be the same length as the input string `s`. The temporary `word` string also uses space, but its maximum size is the length of the longest word, and the total characters copied into `word` across all iterations sum up to O(N). Therefore, the overall space complexity is O(N). |

## 🔗 Related Problems
- 186. Reverse Words in a String II (This is the follow-up problem asking for an in-place solution with O(1) extra space.)
- 557. Reverse Words in a String III
- 344. Reverse String