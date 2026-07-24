# 0442-find-all-duplicates-in-an-array

## 📋 Problem Description
Given an integer array `nums` of length `n`. All integers in `nums` are guaranteed to be within the range `[1, n]`, and each integer appears at most twice. The task is to find and return an array containing all integers that appear exactly twice.

The algorithm must run in `O(n)` time complexity and use only `O(1)` auxiliary space, excluding the space needed to store the output array.

## 🔍 Examples
```
Input: nums = [4,3,2,7,8,2,3,1]
Output: [2,3]
Explanation: The numbers 2 and 3 each appear twice in the input array.
```
```
Input: nums = [1,1,2]
Output: [1]
Explanation: The number 1 appears twice in the input array.
```
```
Input: nums = [1]
Output: []
Explanation: No number appears twice in the input array.
```

## 📌 Constraints
*   `n == nums.length`
*   `1 <= n <= 10^5`
*   `1 <= nums[i] <= n`
*   Each element in `nums` appears **once** or **twice**.

## 🤔 Understanding the Problem
The problem asks us to identify all numbers that appear exactly two times within a given array. A crucial piece of information is that all numbers are positive and fall within the range `[1, n]`, where `n` is the length of the array. This specific range often hints at solutions that can use the array indices themselves for tracking, potentially allowing for `O(1)` auxiliary space. The problem explicitly states a requirement for `O(n)` time and `O(1)` auxiliary space (excluding the output array), making it a non-trivial challenge to meet both constraints simultaneously without modifying the input array or using clever index-based tricks. The provided solution prioritizes `O(n)` time complexity using a common data structure.

## 💡 Core Idea
The core idea of the provided solution is to use a hash set to efficiently keep track of numbers that have been encountered. By checking if a number is already in the set before adding it, we can determine if it's a duplicate.

## 🧠 Approach — Hash Set / Frequency Counting
This problem can be solved using a Hash Set (specifically, `unordered_set` in C++). This pattern is suitable because we need to efficiently check if an element has been seen before. A hash set provides average `O(1)` time complexity for insertion and lookup operations. By iterating through the array and adding each number to the set, we can quickly determine if a number is a duplicate: if `num` is already in the set, it means we've seen it once before, and this current encounter makes it the second time.

## 📝 Step-by-Step Algorithm
1.  Initialize an empty `unordered_set` called `visited`. This set will store all unique numbers encountered so far.
2.  Initialize an empty `vector` called `ans`. This vector will store the numbers that are found to be duplicates.
3.  Iterate through each `num` in the input array `nums`:
    a.  For the current `num`, check if it is already present in the `visited` set using `visited.count(num)`.
    b.  If `num` is found in `visited`, it means this is the second time we are seeing this number. Therefore, `num` is a duplicate. Add `num` to the `ans` vector.
    c.  After checking for duplication, add the current `num` to the `visited` set. This marks it as an encountered number for subsequent iterations.
4.  After the loop finishes iterating through all numbers in `nums`, the `ans` vector will contain all the integers that appeared twice. Return `ans`.

## 💻 Solution
```cpp
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        // Initialize an unordered_set to keep track of numbers we have encountered.
        // This data structure provides average O(1) time complexity for insertion and lookup,
        // making it efficient for checking if an element has been seen before.
        unordered_set<int> visited;
        
        // Initialize a vector to store the duplicate numbers found.
        // This will be our final output.
        vector<int> ans;
        
        // Iterate through each number in the input array 'nums'.
        // This loop processes each element exactly once.
        for(int num : nums) {
            // Check if the current number 'num' is already present in the 'visited' set.
            // If 'visited.count(num)' returns true, it means 'num' has been seen before.
            // Since each number appears at most twice, this must be its second occurrence.
            if (visited.count(num)) {
                // If it's a duplicate, add it to our 'ans' vector.
                ans.push_back(num);
            }
            // Regardless of whether it was a duplicate or not, add the current number 'num'
            // to the 'visited' set. This marks it as seen for any future iterations.
            visited.insert(num);
        }
        
        // After iterating through all numbers, return the 'ans' vector
        // containing all numbers that appeared exactly twice.
        return ans;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each number in `nums` is processed exactly once. Hash set operations (`insert`, `count`) take O(1) time on average. |
| **Space** | O(N) | In the worst case, the `visited` hash set stores up to N distinct elements (e.g., if all numbers are unique or appear once before a duplicate). This solution does not meet the problem's strict `O(1)` auxiliary space requirement. |

## 🔗 Related Problems
- 217. Contains Duplicate
- 219. Contains Duplicate II
- 287. Find the Duplicate Number