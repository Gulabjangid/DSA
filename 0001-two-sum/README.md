# 0001-two-sum

## 📋 Problem Description
Given an array of integers `nums` and an integer `target`, the task is to find the indices of two numbers in the array such that their sum equals the `target`.

You are guaranteed that there will be exactly one valid solution, and you may not use the same element twice (meaning the two numbers must come from different positions in the array, even if their values are identical). The order in which you return the indices does not matter.

**Input:**
*   `nums`: An array of integers.
*   `target`: An integer representing the desired sum.

**Output:**
*   A `vector<int>` containing two 0-based indices `[index1, index2]` such that `nums[index1] + nums[index2] == target`.

## 🔍 Examples
```
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9 (2 + 7 = 9), we return [0, 1].
```

```
Input: nums = [3,2,4], target = 6
Output: [1,2]
Explanation: Because nums[1] + nums[2] == 6 (2 + 4 = 6), we return [1, 2].
```

```
Input: nums = [3,3], target = 6
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 6 (3 + 3 = 6), we return [0, 1].
```

## 📌 Constraints
*   `2 <= nums.length <= 10^4`
*   `-10^9 <= nums[i] <= 10^9`
*   `-10^9 <= target <= 10^9`
*   **Only one valid answer exists.**

## 🤔 Understanding the Problem
The problem asks us to find a pair of numbers within a given array that add up to a specific `target` value. The crucial part is that we need to return their *indices*, not the numbers themselves. The problem guarantees that such a pair always exists and is unique, simplifying the search as we don't need to handle cases with no solution or multiple solutions. We also cannot use the same element twice, meaning `nums[i]` and `nums[j]` must refer to distinct positions in the array (`i != j`).

## 💡 Core Idea
For each number `x` in the array, we need to quickly determine if its "complement" (`target - x`) exists among the numbers we've already processed. If it does, we've found our pair. A hash map (or dictionary) is an excellent data structure for this, as it allows for near-instantaneous lookups.

## 🧠 Approach — Hash Map (or Lookup Table)
This problem is a classic application of the **Hash Map** pattern. A hash map is used because it provides average O(1) time complexity for insertions and lookups. When iterating through the array, for each number `nums[i]`, we calculate the `complement` needed to reach the `target` (`target - nums[i]`). We then check if this `complement` already exists in our hash map. If it does, we've found our pair. If not, we add the current number `nums[i]` and its index `i` to the map, making it available as a potential complement for subsequent numbers.

## 📝 Step-by-Step Algorithm
1.  **Initialize a Hash Map**: Create an empty hash map (e.g., `std::unordered_map<int, int>` in C++). This map will store `(number, index)` pairs, where the key is a number from the `nums` array and its value is its 0-based index.
2.  **Iterate Through the Array**: Loop through the `nums` array from the first element (index 0) up to the last element. Let `i` be the current index.
3.  **Calculate Complement**: For the current number `nums[i]`, calculate the `complement` required to reach the `target`: `complement = target - nums[i]`.
4.  **Check in Map**: Look for this `complement` as a key in the hash map.
    *   **If `complement` is found**: This means we have previously encountered a number that, when added to `nums[i]`, sums up to `target`. The index of that previously encountered number is the value associated with `complement` in the map (`mp[complement]`). We have found our two indices: `mp[complement]` and the current index `i`. Return these two indices.
    *   **If `complement` is not found**: The current number `nums[i]` is not part of a pair with any number processed so far. However, `nums[i]` itself could be a complement for a number we encounter later in the array. Therefore, add `nums[i]` and its current index `i` to the hash map: `mp[nums[i]] = i`.
5.  **Return (Fallback)**: Since the problem guarantees exactly one solution, the algorithm will always find a pair and return within the loop. A final `return {}` statement is typically included for completeness, but it should never be reached.

## 💻 Solution
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // Create an unordered_map to store numbers and their indices.
        // The key will be the number itself, and the value will be its 0-based index.
        // This allows for O(1) average time complexity for lookups and insertions.
        unordered_map<int, int> mp;

        // Iterate through the input array 'nums' from the beginning to the end.
        for (int i = 0; i < nums.size(); i++) {
            // For the current number nums[i], calculate the 'complement'
            // that we would need to find to sum up to the 'target'.
            // If nums[i] + complement == target, then complement = target - nums[i].
            int complement = target - nums[i];

            // Check if this 'complement' already exists as a key in our map.
            // If mp.find(complement) != mp.end(), it means we have previously
            // encountered a number (stored in the map) that is the complement
            // to nums[i].
            if (mp.find(complement) != mp.end()) {
                // If found, we have identified the two numbers that sum to 'target'.
                // The index of the complement is mp[complement].
                // The index of the current number is i.
                // Return these two indices as a vector.
                return {mp[complement], i};
            }

            // If the complement was not found in the map, it means nums[i]
            // itself could be a complement for a number we encounter later in the array.
            // So, store nums[i] along with its current index 'i' in the map.
            // This makes nums[i] available for future lookups.
            mp[nums[i]] = i;
        }

        // According to the problem constraints, there is always exactly one solution,
        // so the function should always return within the loop.
        // This line is a safeguard for compilers and should theoretically not be reached.
        return {};
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the `nums` array once. Inside the loop, hash map operations (insertion and lookup) take average O(1) time. |
| **Space** | O(N) | In the worst case, we might store all N numbers and their indices in the hash map if no pair is found until the very end. |

## 🔗 Related Problems
*   15. 3Sum
*   18. 4Sum
*   167. Two Sum II - Input Array Is Sorted
*   217. Contains Duplicate