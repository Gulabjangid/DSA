# 0287-find-the-duplicate-number

## 📋 Problem Description
You are given an array of integers called `nums`. This array contains `n + 1` integers, and every integer in the array is guaranteed to be in the range `[1, n]` (inclusive).

The problem states that there is exactly one repeated number within `nums`. Your task is to find and return this repeated number.

**Important constraints:**
*   You must solve the problem without modifying the original array `nums`.
*   You must use only constant extra space (i.e., O(1) space complexity).

## 🔍 Examples
```
Input: nums = [1,3,4,2,2]
Output: 2
Explanation: The number 2 appears twice.
```
```
Input: nums = [3,1,3,4,2]
Output: 3
Explanation: The number 3 appears twice.
```
```
Input: nums = [3,3,3,3,3]
Output: 3
Explanation: The number 3 appears multiple times, but it is the only repeated number.
```

## 📌 Constraints
*   `1 <= n <= 10^5`
*   `nums.length == n + 1`
*   `1 <= nums[i] <= n`
*   All integers in `nums` appear only once, except for precisely one integer which appears two or more times.

## 🤔 Understanding the Problem
The problem presents a classic scenario where the "Pigeonhole Principle" is at play: if you have `n + 1` items (numbers) and they can only take `n` possible values (from `1` to `n`), then at least one value must be repeated. The challenge isn't just finding *any* duplicate, but doing so under strict conditions: no modifying the input array and using only constant extra space. The provided solution effectively finds the duplicate but uses extra space, which is a common first approach before tackling the more advanced space constraint.

## 💡 Core Idea
The most straightforward way to detect a duplicate in an array is to keep track of all numbers encountered so far. If we encounter a number that we've already seen, then that number must be the duplicate.

## 🧠 Approach — Hash Set / Frequency Counting
This solution utilizes a **Hash Set** (or `unordered_set` in C++) to efficiently track seen numbers. A hash set allows for average O(1) time complexity for insertion and lookup operations. This pattern is ideal for problems where you need to quickly check for the existence of an element or count frequencies without a fixed range or order. Here, it helps us identify the first number that has already been "seen" during our traversal.

## 📝 Step-by-Step Algorithm
1.  Initialize an empty hash set, which will store numbers we have encountered so far.
2.  Iterate through each number (`val`) in the input array `nums`.
3.  For each `val`, check if it is already present in the hash set.
    *   If `val` is found in the hash set, it means we have encountered this number before. Since the problem guarantees there's only one repeated number, this `val` is our duplicate. Return `val`.
    *   If `val` is not found in the hash set, it means this is the first time we're seeing this number. Add `val` to the hash set to mark it as seen.
4.  If the loop completes without finding a duplicate (which shouldn't happen based on the problem constraints), you could return a sentinel value like -1, though the problem guarantees a duplicate exists.

## 💻 Solution
```cpp
#include <vector>
#include <unordered_set> // Required for using unordered_set

class Solution {
public:
    int findDuplicate(std::vector<int>& nums) {
        // Create an unordered_set to store numbers we have encountered.
        // An unordered_set provides average O(1) time complexity for insertion and lookup.
        std::unordered_set<int> seenNumbers; 

        // Iterate through each number in the input array 'nums'.
        for (int val : nums) {
            // Check if the current number 'val' is already present in our 'seenNumbers' set.
            // 'find()' returns an iterator to the element if found, or 'end()' if not found.
            if (seenNumbers.find(val) != seenNumbers.end()) {
                // If 'val' is found, it means we have encountered this number before.
                // Since the problem guarantees only one repeated number, this 'val' is the duplicate.
                return val; 
            }
            // If 'val' is not found, it's a new number. Add it to the set.
            seenNumbers.insert(val);
        }

        // This line should theoretically not be reached because the problem guarantees
        // that a duplicate number always exists. It's a fallback in case of unexpected input.
        return -1; 
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the `nums` array once. Each `unordered_set` operation (insertion and lookup) takes O(1) time on average. In the worst case (due to hash collisions), these operations could degrade to O(N), but this is rare with good hash functions. |
| **Space** | O(N) | In the worst case, the `unordered_set` might need to store up to `N` distinct numbers (where `N` is `n`, the maximum value in the array). This means the space complexity is proportional to the number of elements, violating the problem's strict "constant extra space" requirement. |

## 🔗 Related Problems
*   217. Contains Duplicate
*   1. Two Sum
*   136. Single Number