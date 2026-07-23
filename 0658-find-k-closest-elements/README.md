# 0658-find-k-closest-elements

## 📋 Problem Description
Given a **sorted** integer array `arr`, two integers `k` and `x`, the task is to find and return the `k` closest integers to `x` from the array. The final result must also be sorted in ascending order.

The definition of "closer" is as follows:
*   An integer `a` is closer to `x` than an integer `b` if the absolute difference `|a - x|` is strictly less than `|b - x|`.
*   If the absolute differences are equal (`|a - x| == |b - x|`), then `a` is considered closer than `b` if `a` itself is smaller than `b` (`a < b`).

The function `findClosestElements` takes the sorted integer array `arr`, an integer `k`, and an integer `x` as input. It should return a `vector<int>` containing the `k` closest elements to `x`, sorted in ascending order.

## 🔍 Examples
```
Input: arr = [1,2,3,4,5], k = 4, x = 3
Output: [1,2,3,4]
Explanation:
|1-3|=2, |2-3|=1, |3-3|=0, |4-3|=1, |5-3|=2
Sorted by closeness: [3 (dist 0), 2 (dist 1), 4 (dist 1), 1 (dist 2), 5 (dist 2)]
The 4 closest are 3, 2, 4, 1. Sorted: [1,2,3,4].
```

```
Input: arr = [1,1,2,3,4,5], k = 4, x = -1
Output: [1,1,2,3]
Explanation:
|1-(-1)|=2, |1-(-1)|=2, |2-(-1)|=3, |3-(-1)|=4, |4-(-1)|=5, |5-(-1)|=6
Sorted by closeness: [1 (dist 2), 1 (dist 2), 2 (dist 3), 3 (dist 4), 4 (dist 5), 5 (dist 6)]
Note the tie-breaking rule: if distances are equal, the smaller number comes first.
The 4 closest are 1, 1, 2, 3. Sorted: [1,1,2,3].
```

## 📌 Constraints
*   `1 <= k <= arr.length`
*   `1 <= arr.length <= 10^4`
*   `arr` is sorted in **ascending** order.
*   `-10^4 <= arr[i], x <= 10^4`

## 🤔 Understanding the Problem
The problem asks us to select a specific number (`k`) of elements from a given sorted array that are "nearest" to a target value `x`. The key challenge is understanding the precise definition of "closeness," which involves both the absolute difference and a tie-breaking rule based on the element's value itself. The final result must also be sorted, which might require an additional sorting step if the initial selection process doesn't guarantee it. The fact that the input array `arr` is sorted is a hint, but this particular solution doesn't directly leverage it for optimization beyond the final output sorting.

## 💡 Core Idea
The core idea of this solution is to transform each element into a representation that explicitly captures its "closeness" to `x`. By pairing each number with its distance to `x`, we can then sort all these pairs based on the problem's closeness criteria. Once sorted, the first `k` pairs will directly correspond to the `k` closest elements.

## 🧠 Approach — Custom Sorting
This problem is effectively solved using a "Custom Sorting" approach. This pattern is ideal when the standard sorting order (e.g., numerical ascending) doesn't match the specific criteria required by the problem. Here, we need to sort elements primarily by their absolute distance to `x`, and secondarily by their value if distances are equal. By creating a temporary data structure (like a vector of pairs or vectors) where each entry stores `{distance_to_x, original_element_value}`, we can leverage standard library sorting functions. These functions, by default, sort such structures based on the first element, then the second for ties, which perfectly aligns with our custom closeness definition. This allows us to easily identify and extract the `k` closest elements after a single sort operation.

## 📝 Step-by-Step Algorithm
1.  **Initialize a temporary storage**: Create an empty `vector` of `vector<int>` (or `pair<int, int>`), let's call it `elements_with_distance`. Each inner `vector` will store two integers: `{absolute_distance_to_x, original_element_value}`.
2.  **Calculate distances for all elements**: Iterate through each `number` in the input array `arr`:
    a.  Calculate the absolute difference between `number` and `x`: `distance = abs(number - x)`.
    b.  Create a temporary `vector<int>` containing `{distance, number}`.
    c.  Add this temporary `vector` to `elements_with_distance`.
3.  **Sort by closeness**: Sort the `elements_with_distance` vector. The default sorting behavior for `std::vector<std::vector<int>>` (or `std::vector<std::pair<int, int>>`) in C++ will sort based on the first element (distance) in ascending order. If two first elements are equal, it will then sort based on the second element (original value) in ascending order. This precisely matches the problem's definition of "closer".
4.  **Extract the `k` closest elements**: Initialize an empty `vector<int>` called `output`.
5.  Iterate `k` times, from `i = 0` to `k-1`:
    a.  Take the `i`-th element from the sorted `elements_with_distance` vector.
    b.  Extract its original value (which is the second element, `elements_with_distance[i][1]`).
    c.  Add this value to the `output` vector.
6.  **Sort the final output**: The problem requires the final result to be sorted in ascending order. While `elements_with_distance` is sorted by closeness, the `k` extracted elements might not be in strictly ascending order if there were ties in distance (e.g., `x=3`, `k=2`, `arr=[1,5]`, both are distance 2, but `1` comes before `5`). Therefore, sort the `output` vector.
7.  **Return the result**: Return the `output` vector.

## 💻 Solution
```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        // Step 1 & 2: Initialize a temporary vector to store pairs of {distance, element_value}.
        // Iterate through the input array to calculate the absolute distance of each element from x.
        // Store these pairs.
        vector<vector<int>> ans; // Each inner vector will be {distance, original_value}
        for (int i = 0; i < arr.size(); i++) {
            int distance = abs(x - arr[i]); // Calculate absolute distance
            ans.push_back({distance, arr[i]}); // Store as {distance, value}
        }

        // Step 3: Sort the 'ans' vector.
        // By default, std::sort on a vector of vectors (or pairs) sorts primarily by the first element,
        // and then by the second element for tie-breaking.
        // This perfectly matches the problem's definition of "closer":
        // 1. Smaller absolute distance first.
        // 2. If distances are equal, smaller element value first.
        sort(ans.begin(), ans.end());

        // Step 4 & 5: Initialize 'output' vector and extract the k closest elements.
        // The first 'k' elements in the sorted 'ans' vector are the k closest.
        vector<int> output;
        for (int i = 0; i < k; i++) {
            output.push_back(ans[i][1]); // Add the original element value (second part of the pair)
        }

        // Step 6: Sort the 'output' vector.
        // The problem requires the final result to be sorted in ascending order.
        // While 'ans' is sorted by closeness, picking the elements might not preserve
        // their original ascending order if distances were equal (e.g., [4,2] vs [2,4]).
        sort(output.begin(), output.end());
        
        // Step 7: Return the final sorted list of k closest elements.
        return output;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N log N) | O(N) to build `ans` vector, O(N log N) to sort `ans` (where N is `arr.length`), O(k) to extract `k` elements, and O(k log k) to sort `output`. The dominant factor is O(N log N). |
| **Space** | O(N) | O(N) for the `ans` vector to store `N` pairs of `{distance, value}`, and O(k) for the `output` vector. The dominant factor is O(N). |

## 🔗 Related Problems
- 973. K Closest Points to Origin
- 373. Find K Pairs with Smallest Sums
- 215. Kth Largest Element in an Array