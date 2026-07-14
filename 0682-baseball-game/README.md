# 0682-baseball-game

## 📋 Problem Description
You are tasked with keeping score for a baseball game with unusual rules. You begin with an empty record of scores. You are given a list of strings, `operations`, where each string represents an operation to apply to the record.

There are four types of operations:
1.  **An integer `x`**: Record a new score of `x`.
2.  **`'+'`**: Record a new score that is the sum of the previous two scores on the record.
3.  **`'D'`**: Record a new score that is double the previous score on the record.
4.  **`'C'`**: Invalidate the previous score, removing it from the record.

After applying all operations in the given order, you must return the total sum of all scores currently on the record.

The problem guarantees that all intermediate calculations and the final answer will fit within a 32-bit integer. Additionally, operations `'+'`, `'C'`, and `'D'` will always be valid, meaning there will be enough previous scores on the record for them to execute.

## 🔍 Examples
```
Input:  ops = ["5","2","C","D","+"]
Output: 30
Explanation:
"5" - Add 5 to the record, record is now [5].
"2" - Add 2 to the record, record is now [5, 2].
"C" - Invalidate and remove the previous score, record is now [5].
"D" - Add 2 * 5 = 10 to the record, record is now [5, 10].
"+" - Add 5 + 10 = 15 to the record, record is now [5, 10, 15].
The total sum is 5 + 10 + 15 = 30.

Input:  ops = ["5","-2","4","C","D","9","+","+",""]
Output: 27
Explanation:
"5" - Add 5 to the record, record is now [5].
"-2" - Add -2 to the record, record is now [5, -2].
"4" - Add 4 to the record, record is now [5, -2, 4].
"C" - Invalidate and remove the previous score, record is now [5, -2].
"D" - Add 2 * -2 = -4 to the record, record is now [5, -2, -4].
"9" - Add 9 to the record, record is now [5, -2, -4, 9].
"+" - Add -4 + 9 = 5 to the record, record is now [5, -2, -4, 9, 5].
"+" - Add 9 + 5 = 14 to the record, record is now [5, -2, -4, 9, 5, 14].
The total sum is 5 + -2 + -4 + 9 + 5 + 14 = 27.
```

## 📌 Constraints
*   `1 <= operations.length <= 1000`
*   `operations[i]` is `"C"`, `"D"`, `"+"`, or a string representing an integer in the range `[-3 * 10^4, 3 * 10^4]`.
*   For operation `"+"`, there will always be at least two previous scores on the record.
*   For operations `"C"` and `"D"`, there will always be at least one previous score on the record.
*   The answer and all intermediate calculations fit in a 32-bit integer.

## 🤔 Understanding the Problem
The problem asks us to simulate a sequence of operations that modify a dynamic list of scores. The crucial aspect is that most operations (`C`, `D`, `+`) refer to the "previous" or "last" scores. For example, `'C'` removes the most recent score, `'D'` doubles the most recent score, and `'+'` sums the two most recent scores. We need to keep track of these scores in the correct order and then sum them up at the end. The challenge lies in efficiently accessing and modifying the "previous" elements.

## 💡 Core Idea
The operations `C`, `D`, and `+` all depend on the *most recently added* scores. This "last-in, first-out" (LIFO) behavior is a strong indicator that a stack data structure would be ideal for maintaining the record of scores.

## 🧠 Approach — Stack
A stack is a perfect fit for this problem because it naturally supports the "last-in, first-out" (LIFO) principle. Operations like adding a new score (`push`), removing the last score (`pop`), peeking at the last score (`top`), and even accessing the second-to-last score (by temporarily popping the top, peeking, then pushing back) are all efficient stack operations. This allows us to easily manage the dynamic record of scores as described by the problem rules, ensuring that "previous" always refers to the element most recently added to the stack.

## 📝 Step-by-Step Algorithm
1.  **Initialize a Stack**: Create an empty stack (e.g., `std::stack<int>` in C++) to store the scores. This stack will represent our dynamic record of scores.
2.  **Process Operations**: Iterate through each string `op` in the input `operations` vector.
    *   **If `op` is `"C"`**: This means "invalidate the previous score". Pop the top element from the stack.
    *   **If `op` is `"D"`**: This means "record a new score that is double the previous score". Get the top element of the stack (the previous score), multiply it by 2, and push the result onto the stack.
    *   **If `op` is `"+"`**: This means "record a new score that is the sum of the previous two scores".
        *   Get the top element of the stack (this is the most recent score). Store it in a temporary variable (e.g., `score1`).
        *   Pop `score1` from the stack.
        *   Get the new top element of the stack (this is the second most recent score). Store it in another temporary variable (e.g., `score2`).
        *   Push `score1` back onto the stack (we only temporarily removed it to access `score2`).
        *   Push the sum `(score1 + score2)` onto the stack as the new score.
    *   **If `op` is an integer string**: This means "record a new score of `x`". Convert the string `op` to an integer (e.g., using `std::stoi` in C++) and push this integer onto the stack.
3.  **Calculate Total Sum**: After processing all operations, the stack contains all the valid scores. Initialize a variable `totalSum` to 0. While the stack is not empty, pop each element, add it to `totalSum`, and continue until the stack is empty.
4.  **Return Result**: Return the final `totalSum`.

## 💻 Solution

```cpp
#include <vector> // Required for std::vector
#include <string> // Required for std::string, std::stoi
#include <stack>  // Required for std::stack
#include <numeric> // Required for std::accumulate (though not used in this specific solution, good for general sum)

class Solution {
public:
    int calPoints(std::vector<std::string>& operations) {
        // Use a stack to keep track of the scores.
        // A stack is ideal because operations like 'C', 'D', and '+'
        // always refer to the most recently added scores (LIFO - Last-In, First-Out).
        std::stack<int> s;
        
        // Iterate through each operation in the input list.
        for(int i = 0; i < operations.size(); ++i){ // Using ++i for minor optimization
            // Check the type of operation.
            if(operations[i] == "C"){
                // 'C' operation: Invalidate the previous score.
                // This means removing the top element from the stack.
                // Constraints guarantee there's always at least one score for 'C'.
                s.pop();
            }
            else if(operations[i] == "D"){
                // 'D' operation: Record a new score that is double the previous score.
                // Get the previous score (top of the stack), double it, and push it back.
                // Constraints guarantee there's always at least one score for 'D'.
                s.push(2 * s.top());
            }
            else if(operations[i] == "+"){
                // '+' operation: Record a new score that is the sum of the previous two scores.
                // We need the top two elements.
                // Constraints guarantee there are always at least two scores for '+'.
                
                // 1. Get the most recent score (first previous score).
                int first = s.top();
                s.pop(); // Temporarily remove it to access the second previous score.
                
                // 2. Get the second most recent score (second previous score).
                int second = s.top();
                
                // 3. Push the 'first' score back onto the stack.
                // This restores the stack to its state before we temporarily removed 'first'.
                s.push(first);
                
                // 4. Push the sum of 'first' and 'second' as the new score.
                s.push(first + second);
            }
            else{
                // If it's not 'C', 'D', or '+', it must be an integer string.
                // Convert the string to an integer and push it onto the stack.
                s.push(std::stoi(operations[i]));
            }
        }
        
        // After processing all operations, calculate the total sum of scores remaining in the record.
        int ans = 0;
        while(!s.empty()){
            // Pop each score from the stack and add it to the total sum.
            ans += s.top();
            s.pop();
        }
        
        // Return the final total sum.
        return ans;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the `operations` vector once. Each stack operation (push, pop, top) takes O(1) time. String to integer conversion (`stoi`) also takes time proportional to the length of the number string, but since numbers are bounded and string length is small, it's effectively O(1) for practical purposes. Finally, summing elements from the stack takes O(N) in the worst case (if all operations added numbers). Thus, the total time complexity is linear with respect to the number of operations. |
| **Space** | O(N) | In the worst case, if all operations are additions of numbers or `D`/`+` operations, the stack could store up to N elements (where N is the number of operations). For example, if all operations are just adding numbers, the stack will grow to size N. |

## 🔗 Related Problems
- 20. Valid Parentheses
- 150. Evaluate Reverse Polish Notation
- 739. Daily Temperatures