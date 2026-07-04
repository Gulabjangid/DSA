# 0324-wiggle-sort-ii

## 📋 Problem Description
Given an integer array `nums`, reorder its elements such that they form a "wiggle" sequence. A wiggle sequence satisfies the pattern `nums[0] < nums[1] > nums[2] < nums[3] > ...`. This means elements at even indices must be strictly smaller than their subsequent odd-indexed elements, and elements at odd indices must be strictly greater than their subsequent even-indexed elements.

You are guaranteed that a valid answer always exists for the given input array.

## 🔍 Examples
```
Input: nums = [1,5,1,1,6,4]
Output: [1,6,1,5,1,4]
Explanation: Another valid output is [1,4,1,5,1,6]. Both satisfy 1 < 6 > 1 < 5 > 1 < 4.
```

```
Input: nums = [1,3,2,2,3,1]
Output: [2,3,1,3,1,2]
Explanation: This output satisfies 2 < 3 > 1 < 3 > 1 < 2.
```

## 📌 Constraints
*   `1 <= nums.length <= 5 * 10^4`
*   `0 <= nums[i] <= 5000`
*   It is guaranteed that there will be an answer for the given input `nums`.

## 🤔 Understanding the Problem
The problem asks us to rearrange an array `nums` into a specific alternating pattern: `small < large > small < large ...`. The key challenge is to ensure the strict inequality (`<` and `>`) holds for all adjacent elements in the wiggle sequence. This can be tricky, especially when the array contains duplicate numbers, as we cannot simply sort and alternate. We need a strategy that carefully places elements to maintain the strict wiggle property.

## 💡 Core Idea
The core idea is to first sort the array to establish an order. Then, to achieve the `small < large > small < large ...` pattern, we can split the sorted array into two halves (smaller elements and larger elements) and interleave them. By taking elements from the *end* of each sorted half (i.e., the largest elements from the smaller half and the largest elements from the larger half) and placing them alternately, we maximize the difference between adjacent elements, which helps satisfy the strict inequality even with duplicates.

## 🧠 Approach — Sorting and Interleaving
This problem can be effectively solved using a **Sorting and Interleaving** approach.

1.  **Sorting:** We first sort the entire `nums` array. This gives us a non-decreasing sequence of all elements, which is a fundamental step to organize the numbers.
2.  **Partitioning:** After sorting, we conceptually split the array into two halves: a "smaller half" containing the smallest elements and a "larger half" containing the largest elements. For an array of length `n`, the smaller half will contain `ceil(n/2)` elements and the larger half will contain `floor(n/2)` elements.
3.  **Reversing Halves:** To ensure the strict wiggle property and handle duplicates effectively, we reverse both of these conceptual halves. This means the smaller half will now be in decreasing order (largest-to-smallest of the smaller elements), and the larger half will also be in decreasing order (largest-to-smallest of the larger elements).
4.  **Interleaving:** Finally, we construct the wiggle array by interleaving elements from these two reversed halves. We place elements from the (reversed) smaller half at even indices (`0, 2, 4, ...`) and elements from the (reversed) larger half at odd indices (`1, 3, 5, ...`). This pattern ensures that a relatively small number is followed by a relatively large number, then by another relatively small number, and so on, satisfying `small < large > small < large ...`.

This approach works because by sorting and then taking the largest available elements from each half, we create the maximum possible "gap" between adjacent elements, which is crucial for maintaining the strict inequality.

## 📝 Step-by-Step Algorithm

1.  **Sort the input array:** Use a standard sorting algorithm to sort `nums` in non-decreasing order.
2.  **Determine split point:** Calculate `mid = (n + 1) / 2`, where `n` is the size of `nums`. This `mid` index will divide the sorted array into two parts: the first `mid` elements form the "smaller half", and the remaining `n - mid` elements form the "larger half".
3.  **Create auxiliary arrays:**
    *   Create a temporary array `A` of size `mid`. Copy the first `mid` elements from the sorted `nums` into `A`.
    *   Create a temporary array `B` of size `n - mid`. Copy the remaining `n - mid` elements from the sorted `nums` into `B`.
4.  **Reverse auxiliary arrays:**
    *   Reverse the elements in array `A`.
    *   Reverse the elements in array `B`.
    *(This step is crucial: it ensures that when we pick elements from `A` and `B` sequentially, we are picking the largest available elements from each respective half first.)*
5.  **Interleave into original array:** Iterate from `i = 0` to `n - 1`:
    *   If `i` is an even index (`i % 2 == 0`), assign `nums[i]` the next available element from `A` (i.e., `A[a++]`).
    *   If `i` is an odd index (`i % 2 != 0`), assign `nums[i]` the next available element from `B` (i.e., `B[b++]`).
6.  The `nums` array will now contain the wiggle sorted sequence.

## 💻 Solution

```cpp
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();

        // Step 1: Sort the input array.
        // This arranges all elements in non-decreasing order.
        sort(nums.begin(), nums.end());

        // Step 2: Determine the split point for the two halves.
        // 'mid' will be the size of the first half (smaller elements).
        // For n=6, mid=(6+1)/2 = 3. A takes 3 elements, B takes 3 elements.
        // For n=5, mid=(5+1)/2 = 3. A takes 3 elements, B takes 2 elements.
        int mid = (n + 1) / 2;

        // Step 3: Create auxiliary arrays for the two halves.
        // A will store the 'smaller' half (or ceil(n/2) elements).
        // B will store the 'larger' half (or floor(n/2) elements).
        vector<int> A(mid);
        vector<int> B(n - mid);

        // Copy elements from sorted 'nums' into A and B.
        for (int i = 0; i < mid; i++) {
            A[i] = nums[i];
        }
        for (int i = mid; i < n; i++) {
            B[i - mid] = nums[i];
        }

        // Step 4: Reverse both auxiliary arrays.
        // This is crucial. It ensures that when we interleave,
        // we pick the largest elements from the 'smaller half' (A)
        // and the largest elements from the 'larger half' (B) first.
        // This maximizes the difference between adjacent elements,
        // helping to satisfy the strict inequality (e.g., 1 < 6 > 1 < 5).
        reverse(B.begin(), B.end()); // B now contains larger elements in descending order
        reverse(A.begin(), A.end()); // A now contains smaller elements in descending order

        // Step 5: Interleave elements back into the original 'nums' array.
        // We use 'a' and 'b' as pointers for arrays A and B respectively.
        int a = 0, b = 0;
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                // Place elements from the (reversed) smaller half at even indices.
                nums[i] = A[a++];
            } else {
                // Place elements from the (reversed) larger half at odd indices.
                nums[i] = B[b++];
            }
        }
        // 'nums' now holds the wiggle sorted sequence.
    }
};
```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N log N) | The dominant operation is sorting the `nums` array, which takes O(N log N) time. The subsequent operations (splitting into auxiliary arrays, reversing them, and interleaving) all take O(N) time. |
| **Space** | O(N) | Two auxiliary vectors, `A` and `B`, are created. In the worst case, each can hold up to N/2 elements, leading to O(N) additional space. |

## 🔗 Related Problems
- 280. Wiggle Sort (This is a simpler version allowing non-strict inequalities)
- 912. Sort an Array
- 75. Sort Colors