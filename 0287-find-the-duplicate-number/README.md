# 0287-find-the-duplicate-number

## 📋 Problem Description
You are given an array of integers `nums` that contains `n + 1` integers. All these integers are guaranteed to be in the range `[1, n]` inclusive. The problem states that there is exactly one repeated number within `nums`. Your task is to find and return this repeated number.

Crucially, you must solve this problem without modifying the original array `nums` and using only constant extra space.

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
Explanation: The number 3 is the only number, and it is repeated multiple times.
```

## 📌 Constraints
*   `1 <= n <= 10^5`
*   `nums.length == n + 1`
*   `1 <= nums[i] <= n`
*   All integers in `nums` appear only once, except for precisely one integer which appears two or more times.

## 🤔 Understanding the Problem
The core of this problem is to identify a single number that appears more than once in a given array. The array has a specific structure: `n+1` numbers, all within the range `[1, n]`. This setup is important because it guarantees, by the Pigeonhole Principle, that at least one number *must* be duplicated. The main challenge lies in the strict constraints: we cannot modify the input array, and ideally, we should use only constant extra space. The provided solution offers a straightforward way to find the duplicate, though it uses linear extra space, not constant.

## 💡 Core Idea
The fundamental idea behind the provided solution is to keep track of every number encountered so far. If we come across a number that we have already seen, then that number must be the duplicate we are looking for.

## 🧠 Approach — Hash Set / Frequency Counting
This approach utilizes a hash set (specifically `unordered_set` in C++) to efficiently store and check for the presence of elements. A hash set is ideal for this scenario because it allows for average O(1) time complexity for both inserting new elements and checking if an element already exists. We iterate through the array, adding each number to the hash set. If we attempt to add a number that is already in the set, we've found our duplicate.

## 📝 Step-by-Step Algorithm
1.  Initialize an empty hash set (e.g., `unordered_set<int> seenNumbers`). This set will store all unique numbers encountered during our traversal of the `nums` array.
2.  Begin iterating through each number (`val`) in the input array `nums` from the beginning to the end.
3.  For each `val` encountered:
    a.  Check if `val` is already present in the `seenNumbers` hash set. This is done using the `find()` method of the hash set.
    b.  If `val` is found in `seenNumbers` (meaning `seenNumbers.find(val)` does not return `seenNumbers.end()`), it implies that this is the second (or more) time we've seen this number. Therefore, `val` is the repeated number. Return `val` immediately.
    c.  If `val` is not found in `seenNumbers`, it means this is the first time we've encountered this number. Insert `val` into the `seenNumbers` hash set to mark it as seen for future checks.
4.  If the loop completes without returning a value (which should not happen given the problem's guarantee that a duplicate always exists), return -1 as a fallback.

## 💻 Solution
```cpp
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        // Initialize an unordered_set to store numbers encountered so far.
        // An unordered_set provides average O(1) time complexity for insertion and lookup,
        // making it efficient for checking duplicates.
        unordered_set<int> seenNumbers; 

        // Iterate through each number in the input array 'nums'.
        // The range-based for loop simplifies iteration.
        for (int val : nums) {
            // Check if the current number 'val' is already present in our 'seenNumbers' set.
            // 'seenNumbers.find(val)' returns an iterator to 'val' if found,
            // otherwise it returns 'seenNumbers.end()'.
            if (seenNumbers.find(val) != seenNumbers.end()) {
                // If 'val' is found, it means we have encountered this number before.
                // This 'val' is the duplicate number we are looking for.
                // Return it immediately as we only need to find one.
                return val;
            }
            // If 'val' is not found in the set, it means this is the first time we're seeing it.
            // Insert 'val' into the set to mark it as encountered.
            seenNumbers.insert(val);
        }

        // This line should theoretically not be reached given the problem constraints.
        // The problem guarantees that exactly one duplicate exists and will be found
        // within the loop. It's included as a safeguard for completeness.
        return -1; 
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through all `N+1` elements of the `nums` array exactly once. For each element, the `unordered_set::find` and `unordered_set::insert` operations take an average of O(1) time. In the worst case (hash collisions), these operations could degrade to O(N), but on average, they are constant time. |
| **Space** | O(N) | In the worst-case scenario (e.g., the duplicate is the last element, or all elements before the duplicate are unique), we might insert up to `N` unique numbers into the `unordered_set`. This requires space proportional to `N`, where `N` is the range of numbers (and approximately the array size). Note: The problem statement asks for a constant extra space solution, which this hash set approach does not meet. |

## 🔗 Related Problems
- 217. Contains Duplicate
- 1. Two Sum
- 136. Single Number