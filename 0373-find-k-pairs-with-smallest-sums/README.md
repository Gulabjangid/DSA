# 0373-find-k-pairs-with-smallest-sums

## 📋 Problem Description
You are given two integer arrays, `nums1` and `nums2`, both sorted in non-decreasing order, and an integer `k`.
A pair `(u, v)` consists of one element `u` from `nums1` and one element `v` from `nums2`.
Your task is to find and return the `k` pairs `(u, v)` that have the smallest sums `u + v`.

The function should receive `nums1` (a sorted vector of integers), `nums2` (a sorted vector of integers), and `k` (an integer) as input. It must return a `vector<vector<int>>` containing the `k` pairs with the smallest sums.

## 🔍 Examples
```
Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
Output: [[1,2],[1,4],[1,6]]
Explanation: The sequence of all possible sums in increasing order is:
[1,2] sum=3
[1,4] sum=5
[1,6] sum=7
[7,2] sum=9
[7,4] sum=11
[11,2] sum=13
[7,6] sum=13
[11,4] sum=15
[11,6] sum=17
The first 3 pairs are [1,2], [1,4], [1,6].

Input: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
Output: [[1,1],[1,1]]
Explanation: The sequence of all possible sums in increasing order is:
[1,1] sum=2
[1,1] sum=2
[1,2] sum=3
[2,1] sum=3
[1,2] sum=3
[2,2] sum=4
[1,3] sum=4
[1,3] sum=4
[2,3] sum=5
The first 2 pairs are [1,1], [1,1].
```

## 📌 Constraints
*   `1 <= nums1.length, nums2.length <= 10^5`
*   `-10^9 <= nums1[i], nums2[i] <= 10^9`
*   `nums1` and `nums2` both are sorted in non-decreasing order.
*   `1 <= k <= 10^4`
*   `k <= nums1.length * nums2.length`

## 🤔 Understanding the Problem
The problem asks us to find the `k` pairs with the smallest sums from two given sorted arrays. Since both arrays are sorted, we know that smaller elements are at the beginning of each array. This implies that the smallest sums will generally be formed by combining smaller elements from `nums1` with smaller elements from `nums2`. The challenge is to efficiently explore these pairs without generating all `nums1.length * nums2.length` possible pairs, which could be up to `10^10` and too slow. We need a way to always pick the next smallest sum.

## 💡 Core Idea
Since we need to repeatedly find the *next smallest* sum among many candidates, a min-priority queue (min-heap) is an ideal data structure. We can use it to keep track of potential pairs, always extracting the one with the current smallest sum.

## 🧠 Approach — Min-Priority Queue (Heap)
This problem is a classic application of a min-priority queue, often categorized under "K-th Smallest Element" or "Merge K Sorted Lists" patterns. The reason this pattern fits is that we need to continuously retrieve the smallest sum from a dynamically growing set of candidate pairs. A min-priority queue allows us to efficiently extract the minimum element (`O(log N)` time) and add new candidates (`O(log N)` time), where `N` is the number of elements in the queue. By starting with the smallest possible sums and then exploring subsequent sums in a structured way, we can guarantee that we always find the globally smallest sum at each step.

## 📝 Step-by-Step Algorithm

1.  **Initialize Result and Priority Queue**:
    *   Create an empty vector of vectors, `ans`, to store the `k` smallest pairs.
    *   Create a min-priority queue, `pq`. Each element in `pq` will be a `vector<int>` of size 3: `[sum, index_in_nums1, index_in_nums2]`. The priority queue will order elements based on their `sum`.

2.  **Initial Population of Priority Queue**:
    *   Iterate through `nums1` from index `i = 0` up to `min(nums1.size(), k) - 1`.
    *   For each `nums1[i]`, the smallest possible sum it can form is with `nums2[0]`.
    *   Push `[nums1[i] + nums2[0], i, 0]` into the `pq`. We limit this initial population to `k` elements from `nums1` because we only need `k` pairs in total, and any `nums1[i]` beyond the `k`-th element (if `nums1.size()` is large) is unlikely to form one of the `k` smallest sums when paired with `nums2[0]`, compared to `nums1[0]` paired with some `nums2[j]`.

3.  **Extract K Smallest Pairs**:
    *   While `k > 0` and the `pq` is not empty:
        *   Extract the top element (the one with the smallest sum) from `pq`. Let this be `cur = [current_sum, i, j]`.
        *   Add the pair `(nums1[i], nums2[j])` to `ans`.
        *   Decrement `k`.
        *   **Explore Next Candidate**: If `j + 1` is a valid index in `nums2` (i.e., `j + 1 < nums2.size()`), it means we can form a new pair using `nums1[i]` with the next element in `nums2`. Push `[nums1[i] + nums2[j+1], i, j+1]` into the `pq`. This ensures that we explore all possible sums involving `nums1[i]` in increasing order of `nums2` elements.

4.  **Return Result**:
    *   After the loop finishes (either `k` pairs are found or `pq` becomes empty), return `ans`.

## 💻 Solution

```cpp
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2,
                                       int k) {

        vector<vector<int>> ans; // This will store our k smallest pairs.

        // Min-priority queue to store candidate pairs.
        // Each element in the PQ is a vector: {sum, index_in_nums1, index_in_nums2}.
        // 'greater<vector<int>>' makes it a min-heap based on the first element (sum).
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>>
            pq;

        // Initialize the priority queue with the first element of nums2
        // paired with elements from nums1.
        // We only need to consider up to 'k' elements from nums1 initially,
        // because we are looking for 'k' pairs. Any nums1[i] beyond k-th
        // will likely form a larger sum than what we can get from nums1[0]...nums1[k-1]
        // paired with nums2[0] or even nums2[1], etc.
        for (int i = 0; i < min((int)nums1.size(), k); i++) {
            // Push {sum, index_of_nums1_element, index_of_nums2_element}
            pq.push({nums1[i] + nums2[0], i, 0});
        }

        // Extract k smallest pairs from the priority queue.
        // The loop continues as long as we need more pairs (k > 0)
        // and there are still candidate pairs in the priority queue.
        while (k-- && !pq.empty()) {
            // Get the pair with the smallest sum from the top of the PQ.
            auto cur = pq.top();
            pq.pop(); // Remove it from the PQ.

            int i = cur[1]; // Index of the element from nums1.
            int j = cur[2]; // Index of the element from nums2.

            // Add the actual pair (nums1[i], nums2[j]) to our answer list.
            ans.push_back({nums1[i], nums2[j]});

            // If there's a next element in nums2 for the current nums1[i],
            // push the new candidate pair into the PQ.
            // This ensures we explore sums involving nums1[i] with larger elements from nums2.
            if (j + 1 < nums2.size()) {
                pq.push({nums1[i] + nums2[j + 1], i, j + 1});
            }
        }

        return ans; // Return the collected k smallest pairs.
    }
};
```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(k log(min(N1, k))) | We perform `min(N1, k)` initial insertions and then up to `k` extractions/insertions. Each priority queue operation takes `O(log P)` time, where `P` is the size of the priority queue. The maximum size of the priority queue is `min(N1, k)`. Since `k <= 10^4`, this is roughly `O(k log k)`. |
| **Space** | O(min(N1, k)) | The priority queue stores at most `min(nums1.size(), k)` elements. Each element is a small vector of 3 integers. Since `k <= 10^4`, this is `O(k)`. |
*N1* refers to `nums1.length`.

## 🔗 Related Problems
- 23. Merge K Sorted Lists
- 378. Kth Smallest Element in a Sorted Matrix
- 719. Find K-th Smallest Pair Distance