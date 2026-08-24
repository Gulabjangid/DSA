# 0349-intersection-of-two-arrays

## 📋 Problem Description
Given two integer arrays, `nums1` and `nums2`, the task is to find their intersection. The intersection consists of all elements that are present in both arrays. Each element in the resulting array must be unique, and the order of elements in the output does not matter.

The function receives two `std::vector<int>` objects, `nums1` and `nums2`, as input. It must return a `std::vector<int>` containing the unique common elements.

## 🔍 Examples
```
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2]
```

```
Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [9,4]
Explanation: [4,9] is also accepted, as the order does not matter.
```

## 📌 Constraints
*   `1 <= nums1.length, nums2.length <= 1000`
*   `0 <= nums1[i], nums2[i] <= 1000`

## 🤔 Understanding the Problem
The core of this problem is to identify numbers that exist in *both* input arrays. The key requirements are that the final result must contain only *unique* numbers, and the order of these numbers in the output array is not important. This means if a number appears multiple times in `nums1` and `nums2`, it should only appear once in our intersection result. We need an efficient way to check for the presence of elements and automatically handle duplicates.

## 💡 Core Idea
The most efficient way to handle uniqueness and perform fast lookups (checking if an element exists) is to use a hash set (like `std::unordered_set` in C++). Hash sets provide average O(1) time complexity for insertion and lookup operations, which is crucial for performance when dealing with potentially large arrays.

## 🧠 Approach — Hashing / Hash Set
This problem is an excellent candidate for a Hashing approach, specifically utilizing hash sets. Hash sets are data structures that store unique elements and allow for very fast (average O(1) time) operations such as adding an element or checking if an element already exists. This fits the problem perfectly because we need to:
1.  Efficiently store all unique elements from one array.
2.  Efficiently check if elements from the second array are present in the first array's unique set.
3.  Ensure that the final collection of common elements also contains only unique values, which a hash set naturally provides.

## 📝 Step-by-Step Algorithm
1.  **Populate First Set**: Create an empty hash set (let's call it `set1`). Iterate through `nums1` and insert each element into `set1`. This will store all unique elements from `nums1` and allow for quick lookups.
2.  **Initialize Result Set**: Create another empty hash set (let's call it `resultSet`). This set will store the unique elements that are found in the intersection.
3.  **Find Intersection**: Iterate through each element in `nums2`.
    *   For each element from `nums2`, check if it exists in `set1`.
    *   If the element *does* exist in `set1`, it means this element is present in both `nums1` and `nums2`. Add this element to `resultSet`. Since `resultSet` is also a hash set, it will automatically ensure that only unique intersection elements are stored.
4.  **Convert to Vector**: Finally, convert the `resultSet` into a `std::vector<int>` (as required by the function's return type) and return it.

## 💻 Solution
```cpp
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        // Step 1: Create a hash set 's1' and populate it with all unique elements from nums1.
        // Using a constructor that takes iterators (nums1.begin(), nums1.end()) efficiently
        // inserts all elements from nums1 into s1, automatically handling uniqueness.
        // This allows for O(1) average-time lookups later.
        unordered_set<int> s1(nums1.begin(), nums1.end());

        // Step 2: Create another hash set 'ans' to store the unique elements of the intersection.
        // Using a set here automatically handles the uniqueness requirement for the final result.
        unordered_set<int> ans;

        // Step 3: Iterate through each number in nums2.
        for (int num : nums2) {
            // For each number from nums2, check if it exists in s1.
            // 's1.count(num)' returns 1 if 'num' is found in s1, and 0 otherwise.
            // This lookup operation takes O(1) time on average.
            if (s1.count(num)) {
                // If 'num' is found in s1, it means this number is present in both nums1 and nums2.
                // Add it to our 'ans' set. If 'num' is already in 'ans', the set won't add it again,
                // thus maintaining the uniqueness of the intersection elements.
                // This insertion also takes O(1) time on average.
                ans.insert(num);
            }
        }
        
        // Step 4: Convert the 'ans' hash set into a vector<int> as required by the function signature.
        // This creates a new vector by copying elements from the 'ans' set.
        // The order of elements in the resulting vector is not guaranteed, but that's acceptable
        // per the problem statement.
        return vector<int>(ans.begin(), ans.end());
    }
};
```

## ⏱️ Complexity Analysis
Let M be the length of `nums1` and N be the length of `nums2`.

| | Complexity | Reason |
|---|---|---|
| **Time** | O(M + N) | Populating `s1` with elements from `nums1` takes O(M) on average. Iterating through `nums2` (N elements) and performing O(1) average-time lookups in `s1` and O(1) average-time insertions into `ans` takes O(N) on average. The final conversion from `ans` to `vector` takes O(k) where k is the size of the intersection (k <= min(M, N)). Thus, total time is O(M + N). |
| **Space** | O(M + N) | `s1` stores up to M unique elements from `nums1`. `ans` stores up to min(M, N) unique elements from the intersection. In the worst case (e.g., all elements are distinct and different), `s1` could store M elements and `ans` could store N elements (if `nums2` has elements not in `nums1` but also distinct), leading to O(M + N) space. |

## 🔗 Related Problems
- 350. Intersection of Two Arrays II
- 217. Contains Duplicate
- 128. Longest Consecutive Sequence