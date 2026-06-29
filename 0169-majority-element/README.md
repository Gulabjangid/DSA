# 0169-majority-element

## 📋 Problem Description
Given an array `nums` of size `n`, the task is to find and return the *majority element*.

The majority element is defined as the element that appears strictly more than `⌊n / 2⌋` times (i.e., more than half the total number of elements). It is guaranteed that such a majority element always exists within the given array.

**Input:** An integer array `nums`.
**Output:** The integer that is the majority element.

## 🔍 Examples
```
Input: nums = [3,2,3]
Output: 3
Explanation: The array has 3 elements. ⌊3 / 2⌋ = 1. The majority element must appear more than 1 time. '3' appears 2 times, which is more than 1.
```
```
Input: nums = [2,2,1,1,1,2,2]
Output: 2
Explanation: The array has 7 elements. ⌊7 / 2⌋ = 3. The majority element must appear more than 3 times. '2' appears 4 times, which is more than 3.
```

## 📌 Constraints
*   `n == nums.length`
*   `1 <= n <= 5 * 10^4`
*   `-10^9 <= nums[i] <= 10^9`
*   The input is generated such that a majority element will always exist in the array.

## 🤔 Understanding the Problem
The problem asks us to identify a specific element in an array: the one that occurs more than half the time. This is a classic problem because while a simple approach might involve counting all elements (e.g., using a hash map), the "more than half" guarantee allows for a much more efficient solution. The non-trivial aspect is finding this element in linear time and constant space, without storing all counts.

## 💡 Core Idea
The core idea is based on the observation that if an element appears more than `n/2` times, its frequency is so high that it can "outvote" or "cancel out" all other elements combined. We can leverage this by maintaining a `candidate` element and a `count`, incrementing the count if we see the candidate, and decrementing it otherwise. If the count drops to zero, we pick a new candidate.

## 🧠 Approach — Boyer-Moore Voting Algorithm
This problem is perfectly suited for the **Boyer-Moore Voting Algorithm**. This pattern is ideal when you need to find an element that appears a majority of times (i.e., more than `n/k` times for some `k`, typically `k=2` or `k=3`). The algorithm works by pairing up elements that are different and effectively canceling them out. Because the majority element appears more than half the time, it will always be the one remaining after all possible cancellations.

## 📝 Step-by-Step Algorithm
1.  Initialize two variables: `count` to 0 and `candidate` to an arbitrary value (it will be updated on the first iteration if `count` is 0).
2.  Iterate through each number (`num`) in the input array `nums`:
    a.  If `count` is currently 0, it means our previous candidate has been "canceled out" or we are starting fresh. In this case, set the current `num` as the new `candidate`.
    b.  If the current `num` is equal to the `candidate`, increment `count`.
    c.  If the current `num` is different from the `candidate`, decrement `count`.
3.  After iterating through all numbers in the array, the `candidate` variable will hold the majority element. Return this `candidate`.

## 💻 Solution
```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0;          // Initialize a counter for the current candidate
        int candidate = 0;      // Initialize the candidate element

        // Iterate through each number in the input array 'nums'
        for (int num : nums) {
            // If the count is 0, it means the previous candidate has been "canceled out"
            // or we are just starting. So, we pick the current number as a new candidate.
            if (count == 0) {
                candiadate = num;
            }

            // If the current number matches the candidate, increment the count.
            // This means the candidate is "winning" the vote.
            if (num == candiadate) {
                count++;
            }
            // If the current number does not match the candidate, decrement the count.
            // This means the candidate is "losing" a vote to a different element.
            else {
                count--;
            }
        }
        // After iterating through all elements, the 'candidate' variable will hold
        // the majority element because it's guaranteed to exist and will outlast
        // all other elements due to its frequency (> n/2).
        return candiadate;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(n) | The algorithm iterates through the array `nums` exactly once. Each operation inside the loop (comparison, assignment, increment/decrement) takes constant time. |
| **Space** | O(1) | The algorithm uses a fixed number of variables (`count`, `candidate`) regardless of the input array size `n`. No additional data structures are used. |

## 🔗 Related Problems
*   229. Majority Element II
*   347. Top K Frequent Elements