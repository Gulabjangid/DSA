# 0442-find-all-duplicates-in-an-array

## 📋 Problem Description
Given an integer array `nums` of length `n`, where all the integers are guaranteed to be in the range `[1, n]`. Each integer in `nums` appears either once or twice. The goal is to identify and return an array containing all the integers that appear exactly twice.

The solution must adhere to specific performance requirements: it must run in `O(n)` time complexity and use only `O(1)` auxiliary space (excluding the space required for the output array itself).

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
Explanation: No numbers appear twice in the input array.
```

## 📌 Constraints
*   `n == nums.length`
*   `1 <= n <= 10^5`
*   `1 <= nums[i] <= n`
*   Each element in `nums` appears **once** or **twice**.

## 🤔 Understanding the Problem
The problem asks us to find all numbers that are present exactly two times in a given array. A crucial piece of information is that all numbers are positive and fall within the range `[1, n]`, where `n` is the length of the array. This specific range often suggests solutions that might leverage array indices for tracking. The most challenging aspect is the strict requirement for `O(n)` time and `O(1)` auxiliary space. This means we cannot use additional data structures like hash sets or frequency arrays that grow with `n` to store visited elements, as these would typically consume `O(n)` space. The provided solution, while correct in logic, does not meet the `O(1)` auxiliary space constraint.

## 💡 Core Idea
The core idea behind the provided solution is to use a hash set to efficiently keep track of numbers encountered so far. As we iterate through the array, if a number is already present in our hash set, it signifies that we have seen it once before, making the current encounter its second appearance (a duplicate).

## 🧠 Approach — Hashing / Hash Set
This solution employs the Hashing pattern, specifically using a hash set (`unordered_set` in C++). This pattern is highly effective when the primary operations needed are fast lookups (checking if an element exists) and insertions (adding an element). For this problem, we iterate through each number in the input array. For each number, we check if it's already in our `visited` hash set. If it is, we've found a duplicate. Regardless, we then add the current number to the `visited` set to mark it as seen. This approach provides average `O(1)` time complexity for these operations, leading to an overall `O(n)` time complexity for the algorithm.

## 📝 Step-by-Step Algorithm
1.  Initialize an empty `unordered_set` named `visited`. This set will store all unique numbers encountered as we iterate through the input array.
2.  Initialize an empty `vector` named `ans`. This vector will store the numbers that are identified as duplicates.
3.  Iterate through each `num` in the input array `nums` from beginning to end:
    a.  For the current `num`, check if it is already present in the `visited` set using the `count()` method.
    b.  If `visited.count(num)` returns `true` (meaning `num` is already in the set), it indicates that this is the second time we are encountering `num`. Therefore, `num` is a duplicate. Add `num` to the `ans` vector.
    c.  After checking for duplication, add the current `num` to the `visited` set using the `insert()` method. This ensures that if we encounter `num` again later, we will correctly identify it as a duplicate.
4.  Once the iteration through all numbers in `nums` is complete, return the `ans` vector, which now contains all the integers that appeared twice.

## 💻 Solution
```cpp
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        // Initialize an unordered_set to keep track of numbers we have encountered.
        // An unordered_set provides O(1) average time complexity for insertion and lookup,
        // which is crucial for achieving O(n) overall time complexity.
        unordered_set<int> visited;
        
        // Initialize a vector to store the duplicate numbers found.
        // This will be our final output.
        vector<int> ans;
        
        // Iterate through each number in the input array 'nums'.
        // This loop runs 'n' times, where 'n' is the length of 'nums'.
        for(int num : nums){
            // Check if the current number 'num' is already present in the 'visited' set.
            // If 'visited.count(num)' returns true, it means we have seen this number before.
            // Since each number appears at most twice, this second encounter confirms it's a duplicate.
            if (visited.count(num)){
                // Add the duplicate number to our 'ans' vector.
                ans.push_back(num);
            }
            // After checking for duplication, add the current number 'num' to the 'visited' set.
            // This marks it as encountered for any subsequent checks.
            visited.insert(num);
        }
        
        // Return the vector containing all numbers that appeared twice.
        return ans;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(n) | Each number in the input array `nums` is processed exactly once. Hash set operations (insertion and lookup using `count()`) take O(1) time on average. |
| **Space** | O(n) | In the worst-case scenario (e.g., all numbers are unique), the `visited` hash set will store `n` distinct elements, requiring O(n) auxiliary space. This does not meet the problem's strict O(1) auxiliary space requirement. |

## 🔗 Related Problems
- 217. Contains Duplicate
- 219. Contains Duplicate II
- 287. Find the Duplicate Number