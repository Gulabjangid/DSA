# 1910-remove-all-occurrences-of-a-substring

## 📋 Problem Description
Given two strings, `s` and `part`, the task is to repeatedly remove all occurrences of the substring `part` from `s`. The removal operation must always target the **leftmost** occurrence of `part` in `s`. This process continues until `s` no longer contains any occurrences of `part`. The function should return the final string `s` after all such removals have been completed.

**Input:**
*   `s`: The main string from which occurrences of `part` are to be removed.
*   `part`: The substring to be removed.

**Output:**
*   The modified string `s` after all occurrences of `part` have been removed according to the specified rule.

## 🔍 Examples
```
Input: s = "daabcbaabcbc", part = "abc"
Output: "dab"
Explanation:
1. s = "da_abc_baabcbc", remove "abc" at index 2. s becomes "dabaabcbc".
2. s = "daba_abc_bc", remove "abc" at index 4. s becomes "dababc".
3. s = "dab_abc_", remove "abc" at index 3. s becomes "dab".
Now "dab" contains no "abc".
```

```
Input: s = "axxxxyyyyb", part = "xy"
Output: "ab"
Explanation:
1. s = "axxx_xy_yyyb", remove "xy" at index 4. s becomes "axxxyyyb".
2. s = "axx_xy_yyb", remove "xy" at index 3. s becomes "axxyyb".
3. s = "ax_xy_yb", remove "xy" at index 2. s becomes "axyb".
4. s = "a_xy_b", remove "xy" at index 1. s becomes "ab".
Now "ab" contains no "xy".
```

## 📌 Constraints
*   `1 <= s.length <= 1000`
*   `1 <= part.length <= 1000`
*   `s` and `part` consist of lowercase English letters.

## 🤔 Understanding the Problem
The problem asks us to simulate a specific string manipulation process. The key aspects are:
1.  **Repeated Removal**: We must continue removing `part` until no occurrences are left. This implies a loop.
2.  **Leftmost Occurrence**: In each step, if multiple `part` substrings exist, we *must* remove the one that starts earliest in `s`.
3.  **Dynamic String**: Removing a substring changes `s`, potentially creating new occurrences of `part` or shifting existing ones. For example, if `s = "ababa"` and `part = "aba"`, removing the first "aba" at index 0 leaves "ba". If we removed the "aba" at index 2, it would leave "ab". The "leftmost" rule is crucial.

The non-trivial aspect is that string modifications can be expensive, and the number of operations might be large. We need an efficient way to find and remove substrings repeatedly.

## 💡 Core Idea
The most straightforward approach is to directly simulate the process described: repeatedly find the leftmost occurrence of `part` and remove it. This continues until `part` is no longer found in the string `s`.

## 🧠 Approach — Direct Simulation
This problem can be solved using a **Direct Simulation** approach. This pattern is suitable when the problem statement explicitly describes a sequence of operations to be performed until a certain condition is met. Here, we are told to "perform the following operation on `s` until all occurrences of the substring `part` are removed." The operation itself is simple: find the leftmost `part` and remove it. Modern string libraries often provide efficient built-in functions for finding and removing substrings, making direct simulation a viable and often optimal strategy for problems with these constraints.

## 📝 Step-by-Step Algorithm
1.  Initialize a variable, say `part_length`, with the length of the `part` string. This will be used for the removal operation.
2.  Enter a loop that continues as long as `part` can be found within the string `s`.
    a.  Inside the loop, search for the first (leftmost) occurrence of `part` in `s`. Store its starting index, say `found_index`.
    b.  If `part` is not found (i.e., `found_index` indicates "not found"), exit the loop.
    c.  If `part` is found, remove the substring `part` from `s` starting at `found_index` and extending for `part_length` characters.
3.  Once the loop terminates (meaning `part` is no longer present in `s`), return the modified string `s`.

## 💻 Solution
```cpp
class Solution {
public:
    string removeOccurrences(string s, string part) {
        // Get the length of the 'part' string. This will be used for the erase operation.
        int part_length = part.size();

        // Continue looping as long as 'part' can be found within 's'.
        // string::npos is a special value indicating that the substring was not found.
        while (s.find(part) != string::npos) {
            // Find the starting index of the first (leftmost) occurrence of 'part' in 's'.
            // string::find returns the starting index if found, or string::npos otherwise.
            int found_index = s.find(part);

            // Erase 'part_length' characters from 's' starting at 'found_index'.
            // This modifies 's' in-place.
            s.erase(found_index, part_length);
        }

        // After the loop finishes, 's' no longer contains any occurrences of 'part'.
        // Return the final modified string.
        return s;
    }
};
```

## ⏱️ Complexity Analysis
Let `N` be the initial length of string `s` and `M` be the length of string `part`.

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N^2) | In the worst case, `s.find(part)` can take O(N*M) time (using a naive search, which `std::string::find` might use in worst-case scenarios). `s.erase(pos, len)` takes O(N) time as it shifts characters. The loop can run up to N/M times (e.g., `s = "abcabcabc", part = "abc"`). Summing the costs over all iterations: total `find` operations sum to O(N^2) and total `erase` operations sum to O(N^2/M). The dominant factor is O(N^2). |
| **Space** | O(1) | The solution modifies the input string `s` in-place. No additional data structures are used that scale with the input size. (Note: `std::string` operations might involve internal reallocations, but this is an implementation detail for managing the string's buffer, not auxiliary space for the algorithm itself.) |

## 🔗 Related Problems
*   28. Find the Index of the First Occurrence in a String
*   1047. Remove All Adjacent Duplicates In String
*   1249. Minimum Remove to Make Valid Parentheses