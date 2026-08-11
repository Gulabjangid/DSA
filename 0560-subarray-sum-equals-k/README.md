# 0560-subarray-sum-equals-k

## 📋 Problem Description
Given an array of integers `nums` and an integer `k`, the task is to find and return the total number of contiguous non-empty subarrays within `nums` whose elements sum up to `k`.

The function `subarraySum` receives two arguments:
1.  `nums`: A `vector<int>` representing the array of integers.
2.  `k`: An `int` representing the target sum.

It must return an `int` which is the count of such subarrays.

## 🔍 Examples
```
Input: nums = [1,1,1], k = 2
Output: 2
Explanation: The two subarrays are [1,1] (from index 0 to 1) and [1,1] (from index 1 to 2).
```
```
Input: nums = [1,2,3], k = 3
Output: 2
Explanation: The two subarrays are [1,2] (from index 0 to 1) and [3] (from index 2 to 2).
```
```
Input: nums = [-1,-1,1], k = 0
Output: 1
Explanation: The subarray [-1,1] (from index 1 to 2) sums to 0.
```

## 📌 Constraints
*   `1 <= nums.length <= 2 * 10^4`
*   `-1000 <= nums[i] <= 1000`
*   `-10^7 <= k <= 10^7`

## 🤔 Understanding the Problem
The problem asks us to count all possible contiguous segments (subarrays) within a given array `nums` that add up to a specific target value `k`. A subarray must be non-empty. The challenge lies in efficiently checking all possible subarrays, as a naive approach of checking every start and end point would be too slow for larger arrays. We need a way to quickly determine if a subarray sum equals `k` without re-calculating sums repeatedly.

## 💡 Core Idea
The core idea is to use **prefix sums**. If we know the sum of elements from the beginning of the array up to a certain index `j` (let's call it `current_sum`), and we are looking for a subarray `nums[i...j]` that sums to `k`, then the sum of elements from index `0` to `i-1` must be `current_sum - k`. By storing the frequencies of all prefix sums encountered so far in a hash map, we can efficiently check if `current_sum - k` has appeared before.

## 🧠 Approach — Prefix Sums with Hash Map
This problem is best solved using the **Prefix Sums with Hash Map** pattern.
This pattern is ideal when we need to find subarrays or ranges that satisfy a certain sum condition. By maintaining a running sum (prefix sum) and storing its occurrences in a hash map, we can transform the problem of finding `sum(nums[i...j]) == k` into `prefix_sum[j] - prefix_sum[i-1] == k`. This can be rewritten as `prefix_sum[i-1] == prefix_sum[j] - k`. The hash map allows us to quickly look up how many times a required `prefix_sum[i-1]` has occurred, thus counting the valid subarrays ending at `j`.

## 📝 Step-by-Step Algorithm
1.  Initialize a counter `count` to `0`. This will store the total number of subarrays that sum to `k`.
2.  Initialize a variable `current_sum` to `0`. This will keep track of the prefix sum as we iterate through the array.
3.  Create an `unordered_map` (hash map) called `mp`. This map will store the frequency of each prefix sum encountered so far. The key will be the prefix sum, and the value will be its frequency.
4.  **Crucially**, add an entry `mp[0] = 1` to the hash map. This handles the edge case where a subarray starting from index 0 itself sums to `k`. If `current_sum` becomes `k`, then `current_sum - k` is `0`, and `mp[0]` correctly indicates that there's one way to achieve a sum of `0` before the current element (by taking an empty prefix, which allows the current `current_sum` to be a valid subarray sum).
5.  Iterate through each number `num` in the `nums` array:
    a.  Add the current `num` to `current_sum`.
    b.  Check if `mp` contains the key `current_sum - k`. If it does, it means that there have been `mp[current_sum - k]` previous prefix sums that, when subtracted from the `current_sum`, result in `k`. Each of these occurrences signifies a valid subarray ending at the current position. Add `mp[current_sum - k]` to `count`.
    c.  Increment the frequency of the `current_sum` in the hash map: `mp[current_sum]++`.
6.  After iterating through all numbers, return `count`.

## 💻 Solution
```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        // mp stores the frequency of prefix sums encountered so far.
        // Key: prefix sum, Value: frequency of that prefix sum.
        unordered_map<int, int> mp;
        
        // Initialize the map with {0: 1}. This is crucial.
        // It handles cases where a subarray starting from index 0 itself sums to 'k'.
        // For example, if nums = [3], k = 3.
        // When sum becomes 3, we look for (sum - k) = (3 - 3) = 0.
        // If mp[0] is 1, it correctly counts [3] as a valid subarray.
        mp[0] = 1;   

        int sum = 0; // This variable will store the current prefix sum.
        int count = 0; // This variable will store the total count of subarrays summing to k.

        // Iterate through each number in the input array.
        for (int i = 0; i < nums.size(); i++) {
            // Update the current prefix sum.
            sum += nums[i];

            // We are looking for a subarray nums[j...i] such that its sum is k.
            // This means prefix_sum[i] - prefix_sum[j-1] = k.
            // Rearranging, prefix_sum[j-1] = prefix_sum[i] - k.
            // So, we check if (sum - k) exists in our map.
            if (mp.find(sum - k) != mp.end()) {
                // If (sum - k) exists, it means there are mp[sum - k] subarrays
                // that end at the current index 'i' and sum up to 'k'.
                // Add their frequency to our total count.
                count += mp[sum - k];
            }

            // Increment the frequency of the current prefix sum in the map.
            // This prepares for future iterations where this 'sum' might be needed
            // as a 'sum - k' value.
            mp[sum]++;
        }

        // Return the total count of subarrays summing to k.
        return count;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the `nums` array once. Inside the loop, hash map operations (insertion `mp[sum]++` and lookup `mp.find(sum - k)`) take O(1) on average. |
| **Space** | O(N) | In the worst case, all prefix sums encountered could be distinct, leading to the hash map storing up to N entries. |

## 🔗 Related Problems
*   974. Subarray Sums Divisible by K
*   523. Continuous Subarray Sum
*   1. Two Sum (uses a hash map for efficient lookups, similar to how `sum - k` is looked up here)