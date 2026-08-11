# 0560-subarray-sum-equals-k

## 📋 Problem Description
Given an array of integers `nums` and an integer `k`, the task is to find and return the total number of contiguous non-empty subarrays within `nums` whose elements sum up to `k`.

The function `subarraySum` receives:
- `nums`: A `std::vector<int>` representing the array of integers.
- `k`: An `int` representing the target sum.

It must return:
- An `int` representing the total count of such subarrays.

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
Explanation: The subarray is [-1,1] (from index 1 to 2).
```

## 📌 Constraints
*   `1 <= nums.length <= 2 * 10^4`
*   `-1000 <= nums[i] <= 1000`
*   `-10^7 <= k <= 10^7`

## 🤔 Understanding the Problem
The problem asks us to count all contiguous subarrays that sum to a specific target `k`. A "subarray" means a sequence of elements that are adjacent in the original array. The key challenges here are that `nums` can contain negative numbers, and `k` can also be negative. This means a simple sliding window approach (which typically works well for positive numbers where sums are monotonic) won't work directly, as adding or removing elements might not consistently increase or decrease the sum. We need a more robust way to track sums.

## 💡 Core Idea
The core idea is to use prefix sums. If the sum of elements from index `i` to `j` (inclusive) is `k`, this can be expressed as `prefixSum[j] - prefixSum[i-1] = k`. Rearranging this, we get `prefixSum[i-1] = prefixSum[j] - k`. This means for every `prefixSum[j]` we encounter, we need to check how many times `prefixSum[j] - k` has appeared *before* index `j`.

## 🧠 Approach — Prefix Sums with Hash Map
This problem is efficiently solved using the **Prefix Sums with Hash Map** pattern.

This pattern is suitable because we are looking for subarray sums. A subarray sum `nums[i...j]` can be calculated as `prefixSum[j] - prefixSum[i-1]`. By iterating through the array and maintaining a running `current_sum` (which is essentially `prefixSum[j]`), we can determine if a `prefixSum[i-1]` exists such that `current_sum - prefixSum[i-1] = k`. A hash map allows us to store the frequencies of all prefix sums encountered so far, enabling O(1) average-time lookups for `prefixSum[i-1]`.

## 📝 Step-by-Step Algorithm
1.  Initialize an `unordered_map` (hash map) called `mp`. This map will store `(prefix_sum, frequency)` pairs, where `prefix_sum` is a sum encountered so far, and `frequency` is how many times that sum has occurred.
2.  Initialize `mp[0] = 1`. This is a crucial step. It handles the case where a subarray *starting from index 0* itself sums up to `k`. If `current_sum` becomes `k`, then `current_sum - k` is `0`. By having `mp[0] = 1`, we correctly count this subarray.
3.  Initialize `current_sum = 0`. This variable will keep track of the prefix sum up to the current element.
4.  Initialize `count = 0`. This variable will store the total number of subarrays found that sum to `k`.
5.  Iterate through each number `num` in the `nums` array (or using an index `i` from `0` to `nums.size() - 1`):
    a.  Add the current number `nums[i]` to `current_sum`.
    b.  Check if `mp` contains the key `current_sum - k`.
        *   If it does, it means there was a previous prefix sum (`prefixSum[i-1]`) such that `prefixSum[i-1] = current_sum - k`. This implies that the subarray from that previous point up to the current index `i` sums to `k`. Add the frequency of `mp[current_sum - k]` to `count`.
    c.  Increment the frequency of `current_sum` in the map: `mp[current_sum]++`. This records the current prefix sum for future calculations.
6.  After iterating through all elements, return `count`.

## 💻 Solution

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        // mp stores the frequency of each prefix sum encountered so far.
        // Key: prefix sum, Value: frequency of that prefix sum.
        unordered_map<int, int> mp;
        
        // Initialize the map with a prefix sum of 0 having a frequency of 1.
        // This is crucial for handling subarrays that start from index 0 and
        // whose sum equals 'k'. If current_sum itself equals 'k', then
        // current_sum - k will be 0, and mp[0] = 1 ensures this subarray is counted.
        mp[0] = 1;

        int current_sum = 0; // Stores the running prefix sum.
        int count = 0;       // Stores the total number of subarrays summing to 'k'.

        // Iterate through each number in the input array.
        for (int i = 0; i < nums.size(); i++) {
            // Update the current prefix sum.
            current_sum += nums[i];

            // Check if (current_sum - k) exists in the map.
            // If it exists, it means there was a previous prefix sum (let's call it 'prev_sum')
            // such that 'current_sum - prev_sum = k'.
            // This 'prev_sum' is exactly (current_sum - k).
            // The number of times 'prev_sum' appeared tells us how many subarrays
            // ending at the current index 'i' sum up to 'k'.
            if (mp.find(current_sum - k) != mp.end()) {
                count += mp[current_sum - k];
            }

            // Increment the frequency of the current prefix sum in the map.
            // This records the current_sum for future iterations.
            mp[current_sum]++;
        }

        // Return the total count of subarrays whose sum equals 'k'.
        return count;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the `nums` array once. Inside the loop, hash map operations (insertion and lookup) take O(1) time on average. |
| **Space** | O(N) | In the worst case, all prefix sums encountered could be distinct. The hash map would then store up to N entries, where N is the length of `nums`. |

## 🔗 Related Problems
- 523. Continuous Subarray Sum
- 525. Contiguous Array
- 1. Two Sum