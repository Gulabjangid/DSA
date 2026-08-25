# 0217-contains-duplicate

## 📋 Problem Description
Given an integer array `nums`, the task is to determine if any value appears at least twice within the array.
The function `containsDuplicate` receives an integer array `nums` as input.
It should return `true` if there is at least one number that appears two or more times in the array.
It should return `false` if every element in the array is distinct (i.e., each number appears only once).

## 🔍 Examples
```
Input: nums = [1,2,3,1]
Output: true
Explanation: The element 1 occurs at indices 0 and 3, meaning it appears at least twice.
```

```
Input: nums = [1,2,3,4]
Output: false
Explanation: All elements (1, 2, 3, 4) are distinct; none appear more than once.
```

```
Input: nums = [1,1,1,3,3,4,3,2,4,2]
Output: true
Explanation: Elements like 1, 3, 4, and 2 all appear multiple times.
```

## 📌 Constraints
*   `1 <= nums.length <= 10^5`
*   `-10^9 <= nums[i] <= 10^9`

## 🤔 Understanding the Problem
The problem asks us to efficiently detect if any number in a given array is repeated. We don't need to count occurrences or identify *which* numbers are duplicates, just whether *any* duplicate exists. The array can contain up to 100,000 elements, and the values themselves can be very large positive or negative integers. This implies that solutions with quadratic time complexity (like comparing every pair of elements) would be too slow, and approaches relying on value ranges (like a boolean array for presence) might not work due to the vast range of possible integer values.

## 💡 Core Idea
The most efficient way to check if an element has been seen before is to store encountered elements in a data structure that allows for fast lookups. If we try to add an element that is already present, or if a lookup for an element returns true, we've found a duplicate.

## 🧠 Approach — Hash Set / Hash Table
This problem is a classic application of a **Hash Set** (also known as a Hash Table or `unordered_set` in C++). A hash set is a data structure that stores unique elements and provides average O(1) time complexity for insertion and lookup operations. This makes it perfectly suited for checking if an element has been "seen" before. By iterating through the array and attempting to add each element to the hash set, we can quickly determine if an element is a duplicate by checking if it already exists in the set before insertion.

## 📝 Step-by-Step Algorithm
1.  Initialize an empty hash set (e.g., `unordered_set<int> seen;`). This set will store all unique numbers encountered so far.
2.  Iterate through each number in the input array `nums` from the beginning to the end.
3.  For each number `current_num` encountered during the iteration:
    a.  Check if `current_num` is already present in the `seen` hash set.
    b.  If `current_num` is found in `seen`, it means we have encountered this number before. Since the problem asks if *any* value appears at least twice, we have found a duplicate. Immediately return `true`.
    c.  If `current_num` is *not* found in `seen`, it means this is the first time we are seeing this particular number. Add `current_num` to the `seen` hash set to mark it as encountered.
4.  If the loop completes without finding any duplicates (i.e., without returning `true`), it means all elements in the array are distinct. In this case, return `false`.

## 💻 Solution
```cpp
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        // Create an unordered_set to store numbers we have encountered so far.
        // An unordered_set provides average O(1) time complexity for insertion and lookup,
        // making it very efficient for checking element presence.
        unordered_set<int> seen;

        // Iterate through each number in the input array 'nums'.
        // We use a traditional for loop to access elements by index, though a range-based
        // for loop (for (int num : nums)) would also work.
        for(int i = 0; i < nums.size(); ++i) {
            // Check if the current number (nums[i]) is already present in our 'seen' set.
            // 'seen.find(nums[i])' returns an iterator to the element if it's found.
            // If the element is not found, it returns 'seen.end()'.
            if (seen.find(nums[i]) != seen.end()) {
                // If nums[i] is found in 'seen', it means we've encountered this number before.
                // This indicates that a duplicate exists in the array.
                // We can immediately return true as soon as the first duplicate is found.
                return true;
            }
            // If nums[i] was not found in 'seen', it's a unique number we're seeing for the first time.
            // Add it to the 'seen' set so that if we encounter it again later, we can detect it as a duplicate.
            seen.insert(nums[i]);
        }

        // If the loop completes without finding any duplicates (i.e., without returning true),
        // it means all elements in the array are distinct.
        // In this case, we return false.
        return false;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | Each element in the array is processed exactly once. Hash set operations (insertion and lookup) take O(1) time on average. In the worst case (due to hash collisions), these operations could degrade to O(N), but this is rare with good hash functions. |
| **Space** | O(N) | In the worst-case scenario, all elements in the input array are distinct. The hash set would then store all N unique elements, requiring O(N) space. |

## 🔗 Related Problems
- 3. Longest Substring Without Repeating Characters
- 128. Longest Consecutive Sequence
- 219. Contains Duplicate II