# 0373-find-k-pairs-with-smallest-sums

## 📋 Problem Description
You are given two integer arrays, `nums1` and `nums2`, both sorted in non-decreasing order, and an integer `k`.

Your task is to find and return `k` pairs `(u, v)` such that `u` is an element from `nums1` and `v` is an element from `nums2`, and the sum `u + v` is among the smallest possible sums. The pairs should be returned in any order.

**Input:**
*   `nums1`: A sorted array of integers.
*   `nums2`: A sorted array of integers.
*   `k`: An integer representing the number of smallest sum pairs to find.

**Output:**
A list of `k` pairs `[u, v]` with the smallest sums.

## 🔍 Examples

```
Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
Output: [[1,2],[1,4],[1,6]]
Explanation: The sequence of all possible sums in increasing order would be:
[1,2] (sum=3), [1,4] (sum=5), [1,6] (sum=7), [7,2] (sum=9), [7,4] (sum=11), [11,2] (sum=13), [7,6] (sum=13), [11,4] (sum=15), [11,6] (sum=17).
The first 3 pairs are [1,2], [1,4], [1,6].
```

```
Input: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
Output: [[1,1],[1,1]]
Explanation: The sequence of all possible sums:
[1,1] (sum=2), [1,1] (sum=2), [1,2] (sum=3), [2,1] (sum=3), [1,2] (sum=3), [2,2] (sum=4), [1,3] (sum=4), [1,3] (sum=4), [2,3] (sum=5).
The first 2 pairs are [1,1], [1,1].
```

## 📌 Constraints
*   `1 <= nums1.length, nums2.length <= 10^5`
*   `-10^9 <= nums1[i], nums2[i] <= 10^9`
*   `nums1` and `nums2` both are sorted in non-decreasing order.
*   `1 <= k <= 10^4`
*   `k <= nums1.length * nums2.length` (ensuring `k` is always a valid number of pairs)

## 🤔 Understanding the Problem
The problem asks us to find `k` pairs with the smallest sums from two given sorted arrays. A naive approach of generating all `nums1.length * nums2.length` pairs, calculating their sums, sorting them, and then picking the top `k` would be too slow if the arrays are large (up to `10^5` elements each, leading to `10^{10}` pairs). We need a more efficient way to find the smallest `k` sums without generating all possible pairs. The fact that both arrays are sorted is a crucial hint, implying that smaller elements are at the beginning of each array.

## 💡 Core Idea
Since both arrays are sorted, the smallest sums will always involve elements from the beginning of `nums1` and `nums2`. We can use a min-priority queue to efficiently keep track of the *next smallest candidate sums* and extract them one by one until we have `k` pairs.

## 🧠 Approach — Min-Priority Queue (Min-Heap)
This problem is a classic "K-th smallest/largest" type problem, which is often efficiently solved using a min-priority queue (min-heap). The pattern fits because we need to repeatedly find the minimum sum among a set of available candidate pairs. By always extracting the smallest sum and then intelligently adding its "neighbors" (pairs with slightly larger sums) back into the priority queue, we can explore the search space efficiently without generating all possible pairs. This approach is similar to finding the K-th smallest element in a sorted matrix or merging K sorted lists.

## 📝 Step-by-Step Algorithm

1.  **Initialize Result and Priority Queue**:
    *   Create an empty vector of vectors, `ans`, to store the `k` smallest pairs.
    *   Create a min-priority queue, `pq`. Each element in `pq` will be a vector of three integers: `[sum, index_from_nums1, index_from_nums2]`. The priority queue will order elements based on their `sum` (the first element).

2.  **Initial Population of Priority Queue**:
    *   Iterate through `nums1` using an index `i`. For each `nums1[i]`, the smallest possible sum it can form is with `nums2[0]` (since `nums2` is sorted).
    *   Add the pair `(nums1[i], nums2[0])` along with their indices `(i, 0)` to the `pq`. Specifically, push `[nums1[i] + nums2[0], i, 0]` into `pq`.
    *   To optimize, we only need to consider up to `k` elements from `nums1` for this initial step, because we only need `k` pairs in total. If `nums1.size()` is less than `k`, we iterate through all of `nums1`. So, iterate `i` from `0` to `min(nums1.size(), k) - 1`.

3.  **Extract Smallest Pairs**:
    *   Loop `k` times, or until the `pq` becomes empty (whichever comes first):
        *   Extract the top element from `pq` (which has the smallest sum). Let this element be `cur = [current_sum, i, j]`.
        *   Add the actual pair `[nums1[i], nums2[j]]` to our `ans` list.
        *   Now, consider the "next" possible pair involving `nums1[i]`. Since `nums2` is sorted, the next smallest sum with `nums1[i]` would be `nums1[i] + nums2[j+1]`.
        *   If `j + 1` is a valid index within `nums2` (i.e., `j + 1 < nums2.size()`), push the new candidate `[nums1[i] + nums2[j+1], i, j+1]` into `pq`. This ensures we explore sums involving `nums1[i]` with progressively larger elements from `nums2`.

4.  **Return Result**:
    *   After the loop finishes, `ans` will contain the `k` pairs with the smallest sums. Return `ans`.

## 💻 Solution

```cpp
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2,
                                       int k) {

        vector<vector<int>> ans; // This will store our k smallest pairs.

        // A min-priority queue to store candidate pairs.
        // Each element in the PQ is a vector: {sum, index_in_nums1, index_in_nums2}.
        // 'greater<vector<int>>' makes it a min-priority queue based on the first element (sum).
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>>
            pq;

        // Initialize the priority queue.
        // For each element nums1[i], the smallest sum it can form is with nums2[0].
        // We add these initial candidates to the PQ.
        // We only need to consider up to 'k' elements from nums1 for initial candidates,
        // as we only need 'k' pairs in total.
        for (int i = 0; i < min((int)nums1.size(), k); i++) {
            // Push {sum, index_from_nums1, index_from_nums2}
            pq.push({nums1[i] + nums2[0], i, 0});
        }

        // Extract 'k' smallest pairs from the priority queue.
        // Loop while 'k' is greater than 0 and the PQ is not empty.
        while (k-- > 0 && !pq.empty()) {
            // Get the pair with the smallest sum from the top of the PQ.
            auto cur = pq.top();
            pq.pop(); // Remove it from the PQ.

            int i = cur[1]; // Index from nums1
            int j = cur[2]; // Index from nums2

            // Add the actual pair {nums1[i], nums2[j]} to our answer list.
            ans.push_back({nums1[i], nums2[j]});

            // Explore the next possible pair involving nums1[i].
            // Since nums2 is sorted, the next smallest sum with nums1[i] would be
            // nums1[i] + nums2[j+1].
            // If j+1 is a valid index in nums2, push this new candidate to the PQ.
            if (j + 1 < nums2.size()) {
                pq.push({nums1[i] + nums2[j + 1], i, j + 1});
            }
        }

        return ans; // Return the list of k smallest pairs.
    }
};

```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(k log k) | Initial population of PQ takes `min(N1, k)` pushes, each `O(log k)`. The main loop runs `k` times, each iteration involves one `pop` and at most one `push`, both `O(log k)`. Total: `O(min(N1, k) * log k + k * log k)`, which simplifies to `O(k log k)` because `min(N1, k)` is at most `k`. |
| **Space** | O(k) | The priority queue stores at most `k` elements. Each element is a small vector of 3 integers. The `ans` vector stores `k` pairs. |

## 🔗 Related Problems
- 23. Merge k Sorted Lists
- 378. Kth Smallest Element in a Sorted Matrix
- 719. Find K-th Smallest Pair Distance