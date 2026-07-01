# 0383-ransom-note

## 📋 Problem Description
Given two strings, `ransomNote` and `magazine`, determine if `ransomNote` can be constructed by using the letters from `magazine`. The crucial rule is that each letter in `magazine` can only be used once.

The function `canConstruct` should return `true` if `ransomNote` can be formed, and `false` otherwise. Both input strings consist only of lowercase English letters.

## 🔍 Examples
```
Input: ransomNote = "a", magazine = "b"
Output: false
Explanation: The magazine "b" does not contain the letter 'a' needed for the ransom note.
```
```
Input: ransomNote = "aa", magazine = "ab"
Output: false
Explanation: The magazine "ab" only has one 'a', but the ransom note "aa" requires two 'a's.
```
```
Input: ransomNote = "aa", magazine = "aab"
Output: true
Explanation: The magazine "aab" has two 'a's and one 'b'. The ransom note "aa" can be constructed using the two 'a's.
```

## 📌 Constraints
*   `1 <= ransomNote.length, magazine.length <= 10^5`
*   `ransomNote` and `magazine` consist of lowercase English letters.

## 🤔 Understanding the Problem
The problem asks us to verify if all characters required by `ransomNote` are available in `magazine`, taking into account their quantities. The key constraint is that each character from `magazine` can be used at most once. This means we need to count the occurrences of each character in `magazine` and then check if `ransomNote` can be formed without exceeding those counts. If `ransomNote` demands more of any specific character than `magazine` provides, then it cannot be constructed.

## 💡 Core Idea
The core idea is to count the frequency of each character available in the `magazine` and then iterate through the `ransomNote`, decrementing the counts. If at any point a character's count drops below zero, it means we don't have enough of that character.

## 🧠 Approach — Frequency Counting (Array as Hash Map)
This problem is perfectly suited for a **Frequency Counting** approach. Since the constraints specify that both strings consist only of lowercase English letters, there are only 26 possible characters ('a' through 'z'). We can efficiently use a fixed-size array of 26 integers to store the counts of each character, effectively using it as a hash map where the index `c - 'a'` maps to the character `c`. This pattern is ideal because we need to quickly tally character occurrences and then perform constant-time lookups and updates for each character.

## 📝 Step-by-Step Algorithm
1.  **Initialize Frequency Array**: Create an integer array of size 26 (e.g., `int count[26]`), and initialize all its elements to zero. Each index `i` in this array will correspond to the `i`-th lowercase English letter (e.g., index 0 for 'a', index 1 for 'b', ..., index 25 for 'z').
2.  **Count Magazine Characters**: Iterate through each character `c` in the `magazine` string. For each character, increment its corresponding count in the frequency array. For example, if `c` is 'a', increment `count[0]`. If `c` is 'b', increment `count[1]`, and so on. This step builds a complete tally of all characters available in the `magazine`.
3.  **Check Ransom Note Characters**: Iterate through each character `c` in the `ransomNote` string.
    a.  For each character `c`, decrement its corresponding count in the frequency array. This simulates "using up" a character from the `magazine`.
    b.  After decrementing, check if the count for `c` has become negative (i.e., `count[c - 'a'] < 0`). If it has, it means `ransomNote` requires more of this character than what was available in `magazine`. In this scenario, `ransomNote` cannot be constructed, so immediately return `false`.
4.  **Return True**: If the loop for `ransomNote` completes without any character count dropping below zero, it means all characters required by `ransomNote` were available in sufficient quantities in `magazine`. Therefore, return `true`.

## 💻 Solution
```cpp
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        // Create an array to store the frequency of each lowercase English letter.
        // There are 26 lowercase letters ('a' through 'z').
        // Initialize all counts to 0.
        int count[26] = {0};

        // Step 2: Populate the frequency array with characters from the magazine.
        // This tells us how many of each character are available.
        for (char c : magazine) {
            // 'c - 'a'' converts a character (e.g., 'a') into an integer index (e.g., 0).
            // 'b' becomes 1, 'c' becomes 2, etc.
            count[c - 'a']++;
        }

        // Step 3: Iterate through the ransomNote to check if it can be constructed.
        for (char c : ransomNote) {
            // Decrement the count for the current character needed by ransomNote.
            // This simulates using one instance of the character from the magazine.
            count[c - 'a']--;

            // Step 3b: If the count for this character drops below zero,
            // it means we don't have enough of this character in the magazine
            // to fulfill the ransomNote's requirement.
            // Therefore, ransomNote cannot be constructed.
            if (count[c - 'a'] < 0) {
                return false; // Immediately return false as it's impossible.
            }
        }

        // Step 4: If we successfully iterated through all characters in ransomNote
        // without any count dropping below zero, it means all required characters
        // were available in sufficient quantities.
        return true;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(M + N) | We iterate through the `magazine` string once (M characters) and then through the `ransomNote` string once (N characters). Each character operation (increment/decrement) is O(1). |
| **Space** | O(1) | We use a fixed-size array of 26 integers to store character counts. This space is constant and does not depend on the length of the input strings. |
(Where M is the length of `magazine` and N is the length of `ransomNote`).

## 🔗 Related Problems
*   242. Valid Anagram
*   387. First Unique Character in a String
*   451. Sort Characters By Frequency