# 0344-reverse-string

## 📋 Problem Description
Write a function that takes an array of characters, `s`, as input and reverses the string represented by this array. The modification must be performed directly on the input array (in-place) and should use only a constant amount of extra memory (O(1) extra memory).

The function signature will typically be `void reverseString(vector<char>& s)` in C++, meaning it modifies the input array directly and does not return a new one.

## 🔍 Examples
```
Input:  s = ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]

Input:  s = ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]
```

## 📌 Constraints
*   `1 <= s.length <= 10^5`
*   `s[i]` is a printable ASCII character.

## 🤔 Understanding the Problem
The problem asks us to reverse the order of characters in a given array. The critical aspect is the requirement to do this "in-place" with "O(1) extra memory." This means we cannot create a new array to store the reversed string and then copy it back. Instead, we must manipulate the existing array directly, using only a fixed number of variables regardless of the input size. This rules out solutions that involve creating a temporary copy of the string or using auxiliary data structures that grow with the input size.

## 💡 Core Idea
To reverse a sequence in-place with minimal memory, the most intuitive approach is to swap elements from the beginning with corresponding elements from the end, progressively moving towards the center of the sequence.

## 🧠 Approach — Two Pointers
This problem is a classic application of the **Two Pointers** pattern. This pattern is ideal when you need to process elements from both ends of a sequence (like an array or string) simultaneously, or when you need to maintain a "window" of elements. For reversing a string, we can use one pointer starting at the beginning and another at the end. By repeatedly swapping the characters pointed to by these two pointers and then moving them towards each other, we can efficiently reverse the entire string without using extra space.

## 📝 Step-by-Step Algorithm
1.  Initialize a pointer, let's call it `left`, to the index of the first character in the array (index 0).
2.  Initialize another pointer, let's call it `right`, to the index of the last character in the array (index `s.size() - 1`).
3.  Enter a loop that continues as long as the `left` pointer is less than the `right` pointer. This condition ensures we only process unique pairs of characters and stop when the pointers meet or cross (meaning the string is fully reversed).
4.  Inside the loop:
    a.  Swap the character at the `left` pointer's position (`s[left]`) with the character at the `right` pointer's position (`s[right]`).
    b.  Increment the `left` pointer by one to move it towards the center.
    c.  Decrement the `right` pointer by one to move it towards the center.
5.  Once the loop terminates (when `left >= right`), the array `s` will contain the reversed string.

## 💻 Solution
```cpp
class Solution {
public:
    void reverseString(vector<char>& s) {
        
        // Initialize a 'left' pointer at the beginning of the character array.
        // This pointer will move towards the right.
        int left = 0;
        // Initialize a 'right' pointer at the end of the character array.
        // This pointer will move towards the left.
        int right = s.size() - 1;

        // Continue swapping characters as long as the left pointer is before the right pointer.
        // This ensures we process each unique pair of characters from the ends towards the center.
        // When left >= right, it means all necessary swaps have been made, or the string
        // has an odd length and the middle character doesn't need to be swapped.
        while (left < right) {
            // Swap the character at the left pointer's position with the character
            // at the right pointer's position. This is the core operation for reversing.
            std::swap(s[left], s[right]);
            
            // Move the left pointer one step to the right.
            left++;
            // Move the right pointer one step to the left.
            right--;
        }
        // After the loop finishes, the 's' vector now contains the reversed string in-place.
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The algorithm iterates through approximately half of the array elements (N/2 swaps), performing a constant number of operations (swap, increment, decrement) for each pair. This is directly proportional to the length of the string, N. |
| **Space** | O(1) | We only use a fixed number of extra variables (`left`, `right`) regardless of the input string's size. No additional data structures are allocated that scale with the input size. |

## 🔗 Related Problems
*   11. Container With Most Water
*   167. Two Sum II - Input Array Is Sorted
*   345. Reverse Vowels of a String
*   977. Squares of a Sorted Array