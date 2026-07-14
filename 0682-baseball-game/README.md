# 0682-baseball-game

## 📋 Problem Description
You are tasked with keeping score for a unique baseball game. You begin with an empty record of scores. You are provided with a list of strings, `operations`, where each string represents an action to be applied to the score record. There are four types of operations:

1.  **Integer `x`**: Record a new score of `x`.
2.  **`'+'`**: Record a new score that is the sum of the previous two valid scores.
3.  **`'D'`**: Record a new score that is double the previous valid score.
4.  **`'C'`**: Invalidate and remove the previous valid score from the record.

After processing all operations in the `operations` list, your goal is to return the total sum of all scores that remain on the record.

The problem guarantees that all intermediate calculations and the final answer will fit within a 32-bit integer. Additionally, operations like `'+'`, `'D'`, and `'C'` will always have enough preceding scores on the record to be valid.

## 🔍 Examples
```
Input:  operations = ["5","2","C","D","+"]
Output: 30
Explanation:
"5" - Add 5 to the record, record is now [5].
"2" - Add 2 to the record, record is now [5, 2].
"C" - Invalidate and remove the previous score (2), record is now [5].
"D" - Add 2 * 5 = 10 to the record, record is now [5, 10].
"+" - Add 5 + 10 = 15 to the record, record is now [5, 10, 15].
The total sum is 5 + 10 + 15 = 30.
```

```
Input:  operations = ["5","-2","4","C","D","9","+","+",""]
Output: 27
Explanation:
"5" - Add 5 to the record, record is now [5].
"-2" - Add -2 to the record, record is now [5, -2].
"4" - Add 4 to the record, record is now [5, -2, 4].
"C" - Invalidate and remove the previous score (4), record is now [5, -2].
"D" - Add 2 * -2 = -4 to the record, record is now [5, -2, -4].
"9" - Add 9 to the record, record is now [5, -2, -4, 9].
"+" - Add -4 + 9 = 5 to the record, record is now [5, -2, -4, 9, 5].
"+" - Add 9 + 5 = 14 to the record, record is now [5, -2, -4, 9, 5, 14].
The total sum is 5 + -2 + -4 + 9 + 5 + 14 = 27.
```

```
Input:  operations = ["1","C"]
Output: 0
Explanation:
"1" - Add 1 to the record, record is now [1].
"C" - Invalidate and remove the previous score (1), record is now [].
Since the record is empty, the total sum is 0.
```

## 📌 Constraints
*   `1 <= operations.length <= 1000`
*   `operations[i]` is `"C"`, `"D"`, `"+"`, or a string representing an integer in the range `[-3 * 10^4, 3 * 10^4]`.
*   For operation `"+"`, there will always be at least two previous scores on the record.
*   For operations `"C"` and `"D"`, there will always be at least one previous score on the record.

## 🤔 Understanding the Problem
The problem requires us to simulate a sequence of operations that dynamically modify a list of scores. The crucial aspect is that most operations (`+`, `D`, `C`) depend on the *most recently added* scores. This means we need a data structure that can efficiently add elements to the end, remove elements from the end, and peek at the last one or two elements. The final task is to sum all scores remaining in this dynamic record.

## 💡 Core Idea
The operations `'+'`, `'D'`, and `'C'` all refer to "previous scores" or "the previous score," indicating a Last-In, First-Out (LIFO) access pattern. A stack is the ideal data structure to manage this kind of dynamic record where only the most recent elements are relevant for operations.

## 🧠 Approach — Stack
A stack is a linear data structure that follows the Last-In, First-Out (LIFO) principle. This pattern is perfectly suited for this problem because operations like 'C' (invalidate previous score), 'D' (double previous score), and '+' (sum of previous two scores) all exclusively interact with the most recently added scores. A stack naturally provides `push` (add to top), `pop` (remove from top), and `top` (peek at top) operations, which directly map to the problem's requirements for managing the record of scores. By using a stack, we can ensure that "previous scores" are always readily available at the top of the stack.

## 📝 Step-by-Step Algorithm
1.  Initialize an empty stack, let's call it `scoreStack`, to store the valid scores.
2.  Iterate through each string `op` in the input `operations` list:
    a.  **If `op` is `"C"`**:
        *   Remove the top element from `scoreStack`. This invalidates the most recent score. (Constraints guarantee the stack won't be empty).
    b.  **If `op` is `"D"`**:
        *   Retrieve the value of the top element from `scoreStack` (this is the previous score).
        *   Calculate double this value.
        *   Push the doubled value onto `scoreStack`. (Constraints guarantee the stack won't be empty).
    c.  **If `op` is `"+"`**:
        *   Retrieve the value of the top element from `scoreStack` (this is the most recent score) and store it in a temporary variable, say `firstPrev`.
        *   Remove `firstPrev` from `scoreStack`.
        *   Retrieve the value of the new top element from `scoreStack` (this is the second most recent score) and store it in `secondPrev`.
        *   Push `firstPrev` back onto `scoreStack` to restore the stack's state.
        *   Calculate the sum `firstPrev + secondPrev`.
        *   Push this sum onto `scoreStack`. (Constraints guarantee at least two scores are available).
    d.  **If `op` is an integer string**:
        *   Convert the string `op` to an integer.
        *   Push this integer onto `scoreStack`.
3.  After processing all operations, initialize a variable `totalSum` to 0.
4.  While `scoreStack` is not empty:
    *   Add the top element of `scoreStack` to `totalSum`.
    *   Remove the top element from `scoreStack`.
5.  Return `totalSum`.

## 💻 Solution
```cpp
#include <vector> // Required for std::vector
#include <string> // Required for std::string, std::stoi
#include <stack>  // Required for std::stack
#include <numeric> // Potentially for std::accumulate, but not used in this solution

class Solution {
public:
    int calPoints(std::vector<std::string>& operations) {
        // Use a stack to keep track of the scores.
        // A stack is suitable because operations like 'C', 'D', and '+'
        // always refer to the "previous" or "previous two" scores,
        // which aligns perfectly with a Last-In, First-Out (LIFO) structure.
        std::stack<int> s;
        
        // Iterate through each operation in the input list.
        for(int i = 0; i < operations.size(); i++){
            // Check the type of operation.
            if(operations[i] == "C"){
                // 'C': Invalidate the previous score.
                // This means removing the most recently added score from our record.
                // The problem constraints guarantee there's always at least one score
                // when 'C' is encountered, so s.pop() is safe.
                s.pop();
            }
            else if(operations[i] == "D"){
                // 'D': Record a new score that is double the previous score.
                // Get the top element (previous score) without removing it.
                // Constraints guarantee at least one score, so s.top() is safe.
                int previousScore = s.top();
                // Push double of the previous score onto the stack.
                s.push(2 * previousScore);
            }
            else if(operations[i] == "+"){
                // '+': Record a new score that is the sum of the previous two scores.
                // The problem constraints guarantee there are always at least two scores
                // when '+' is encountered.

                // 1. Get the most recent score.
                int firstPrevious = s.top();
                s.pop(); // Remove it temporarily to access the second previous.

                // 2. Get the second most recent score.
                int secondPrevious = s.top();
                
                // 3. Push the first previous score back onto the stack.
                // This restores the stack to its state before we popped 'firstPrevious'.
                // It's crucial because the problem implies the previous scores remain valid
                // after being used for the sum, they are not removed.
                s.push(firstPrevious);

                // 4. Calculate the sum and push it as the new score.
                s.push(firstPrevious + secondPrevious);
            }
            else{
                // If it's not 'C', 'D', or '+', it must be an integer string.
                // Convert the string to an integer using std::stoi and push it onto the stack.
                s.push(std::stoi(operations[i]));
            }
        }
        
        // After processing all operations, calculate the total sum of scores remaining in the record.
        int totalSum = 0;
        while(!s.empty()){
            // Add the top score to the total sum.
            totalSum += s.top();
            // Remove the score from the stack as we've processed it for the sum.
            s.pop();
        }
        
        // Return the final total sum.
        return totalSum;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the `operations` vector once. Each stack operation (`push`, `pop`, `top`) takes O(1) time. String to integer conversion (`stoi`) is effectively O(1) for small fixed-length strings. Finally, summing elements from the stack also takes O(N) in the worst case. |
| **Space** | O(N) | In the worst case, if all operations are additions (numbers, 'D', or '+'), the stack could store up to `N` scores. Each score is an integer. |

## 🔗 Related Problems
- 20. Valid Parentheses
- 150. Evaluate Reverse Polish Notation
- 739. Daily Temperatures