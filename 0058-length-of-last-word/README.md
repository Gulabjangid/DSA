# 0058-length-of-last-word

## 📋 Problem Description
Given a string `s` that consists of words and spaces, the task is to return the length of the last word in the string. A "word" is defined as a maximal contiguous substring made up entirely of non-space characters.

The function `lengthOfLastWord` receives a single string `s` as input and must return an integer representing the length of the last word found in `s`.

## 🔍 Examples
```
Input: s = "Hello World"
Output: 5
Explanation: The last word is "World" with length 5.
```

```
Input: s = "   fly me   to   the moon  "
Output: 4
Explanation: The last word is "moon" with length 4.
```

```
Input: s = "luffy is still joyboy"
Output: 6
Explanation: The last word is "joyboy" with length 6.
```

## 📌 Constraints
*   `1 <= s.length <= 10^4`
*   `s` consists of only English letters and spaces `' '`.
*   There will be at least one word in `s`.

## 🤔 Understanding the Problem
The problem asks us to find the length of the final sequence of non-space characters in a given string. The main challenge lies in correctly identifying the "last word" when the string might contain leading spaces, trailing spaces, or multiple spaces between words. We need to ensure that any trailing spaces are ignored and only the characters of the actual last word are counted.

## 💡 Core Idea
The most straightforward way to find the "last" word and its length, especially when dealing with trailing spaces, is to process the string from right to left. By doing so, we immediately encounter the characters of the last word. The provided solution cleverly achieves this by first reversing the entire string, which transforms the problem into finding the length of the *first* word in the now-reversed string.

## 🧠 Approach — Reverse and Linear Scan
This problem can be efficiently solved using a "Reverse and Linear Scan" approach. By reversing the entire input string, the "last word" from the original string effectively becomes the "first word" in the reversed string. This transformation simplifies the logic for handling trailing spaces, as they now become leading spaces in the reversed string, which are easily skipped. A single linear scan from the beginning of the reversed string can then easily count characters until the first space or the end of the string is encountered, giving us the length of the desired word.

## 📝 Step-by-Step Algorithm
1.  **Reverse the String**: First, reverse the entire input string `s`. For example, if `s` was `"   fly me   to   the moon  "`, after reversing it becomes `"  noom eht   ot   em ylf   "`. The characters of the original last word ("moon") are now at the beginning of the string (as "noom").
2.  **Initialize Counter**: Create an integer variable `count` and initialize it to 0. This variable will store the length of the last word.
3.  **Linear Scan**: Iterate through the reversed string from its beginning (index 0) up to its end.
4.  **Character Processing**: For each character `s[i]` in the reversed string:
    *   **If `s[i]` is a space (`' '`)**:
        *   Check if `count` is currently greater than 0. If it is, it means we have just finished counting the characters of the last word (which is now the first word in the reversed string). Since we've found the end of this word, we can stop and `break` out of the loop.
        *   If `count` is 0, it means we are currently encountering leading spaces in the reversed string (which were originally trailing spaces in the original string). These should be ignored, so `continue` to the next character without incrementing `count`.
    *   **If `s[i]` is not a space**:
        *   This character is part of the word we are tracking. Increment `count` by 1.
5.  **Return Result**: After the loop finishes (either by breaking or by reaching the end of the string), the `count` variable will hold the length of the last word. Return `count`.

## 💻 Solution
```cpp
class Solution {
public:
    int lengthOfLastWord(string s) {
       // Step 1: Reverse the entire input string.
       // This makes the original "last word" appear at the beginning of the string.
       // Example: "Hello World" becomes "dlroW olleH"
       // Example: "   fly me   to   the moon  " becomes "  noom eht   ot   em ylf   "
       reverse(s.begin(),s.end());
       
       // Step 2: Initialize a counter for the length of the word.
       int count = 0;

       // Step 3: Iterate through the reversed string from the beginning.
       for(int i = 0; i < s.length(); i++) {
        
        // Step 4a: If the current character is a space.
        if(s[i] == ' '){
            // If 'count' is greater than 0, it means we have already started counting
            // characters of a word and now we've hit a space. This signifies the end
            // of the first word in the reversed string (which is the last word in the original).
            if(count > 0){
                break; // We found the length of the last word, so stop.
            }
            // If 'count' is 0, it means we are encountering leading spaces (originally trailing spaces).
            // We should just skip them and continue to the next character.
            continue;
        }
        // Step 4b: If the current character is not a space.
        // It means this character is part of the word we are looking for.
        count++; // Increment the word length counter.
      }
        // Step 5: Return the accumulated count, which is the length of the last word.
        return count;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Reversing the string takes O(N) time, where N is the length of the string. The subsequent linear scan also takes at most O(N) time. |
| **Space** | O(1) | The `std::reverse` function typically modifies the string in-place, requiring only a constant amount of auxiliary space for variables like `count` and loop iterators. |

## 🔗 Related Problems
*   151. Reverse Words in a String
*   434. Number of Segments in a String
*   186. Reverse Words in a String II (Premium)