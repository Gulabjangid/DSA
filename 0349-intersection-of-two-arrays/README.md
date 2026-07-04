# 0349-intersection-of-two-arrays

## 📋 Problem Description
Given two integer arrays, `nums1` and `nums2`, the task is to find their intersection. The intersection consists of elements that are present in both arrays. Each element in the resulting array must be unique, and the order of elements in the output does not matter.

The function `intersection` receives two `std::vector<int>` objects, `nums1` and `nums2`, and must return a `std::vector<int>` containing the unique common elements.

## 🔍 Examples
```
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2]
Explanation: The number 2 is present in both arrays. Even though it appears multiple times, the result must contain only unique elements.

Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [9,4]
Explanation: Both 9 and 4 are present in both arrays. [4,9] is also an accepted output as order does not matter.
```

## 📌 Constraints
*   `1 <= nums1.length, nums2.length <= 1000`
*   `0 <= nums1[i], nums2[i] <= 1000`

## 🤔 Understanding the Problem
The core of this problem is to identify common elements between two lists of numbers. The key constraints are that the output must contain only *unique* elements, and the *order* of elements in the output doesn't matter. This means we don't need to worry about how many times an element appears in the input arrays, only whether it's present at least once in both. The order-agnostic nature of the output suggests that data structures that don't maintain order (like sets) might be suitable.

## 💡 Core Idea
The most efficient way to check for the presence of an element and to store unique elements is by using a hash set (also known as an `unordered_set` in C++). Hash sets provide average O(1) time complexity for insertion and lookup operations.

## 🧠 Approach — Hash Set / Hashing
This problem is a classic application of the **Hash Set** pattern. Hash sets are ideal for this problem because they inherently store only unique elements and offer extremely fast average-case performance for checking if an element exists within the set. By first populating a hash set with all unique elements from one array, we can then iterate through the second array and for each element, quickly determine if it's present in the first array's hash set. Any element found in both is part of the intersection.

## 📝 Step-by-Step Algorithm
1.  **Initialize `set1`**: Create an empty hash set (e.g., `std::unordered_set<int>`) named `set1`.
2.  **Populate `set1`**: Iterate through all elements in `nums1`. For each element, insert it into `set1`. This ensures `set1` contains all unique numbers from `nums1`.
3.  **Initialize `resultSet`**: Create another empty hash set named `resultSet`. This set will store the unique elements that are found in the intersection.
4.  **Find Intersection**: Iterate through all elements in `nums2`. For each number `n` in `nums2`:
    a.  Check if `n` exists in `set1` using a lookup operation (e.g., `set1.count(n)` or `set1.find(n)`).
    b.  If `n` is found in `set1`, it means `n` is present in both `nums1` and `nums2`. Insert `n` into `resultSet`. Since `resultSet` is a hash set, it will automatically handle any duplicate insertions, ensuring the final result contains only unique elements.
5.  **Convert to Vector**: Finally, convert the elements from `resultSet` into a `std::vector<int>` and return this vector. This can be done efficiently by constructing a new vector using the iterators of the hash set.

## 💻 Solution
```cpp
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        // Step 1 & 2: Create a hash set (unordered_set) from nums1.
        // This constructor efficiently inserts all unique elements from nums1
        // into s1. This allows for O(1) average time complexity lookups later
        // and automatically handles uniqueness for elements from nums1.
        unordered_set<int> s1(nums1.begin(), nums1.end());

        // Step 3: Initialize another hash set to store the intersection elements.
        // Using a hash set here ensures that the final result contains only unique elements,
        // as required by the problem, and also prevents duplicate insertions.
        unordered_set<int> ans;

        // Step 4: Iterate through nums2.
        for (int n : nums2) {
            // Step 4a & 4b: For each number 'n' in nums2, check if it exists in s1.
            // s1.count(n) returns 1 if n is found, 0 otherwise.
            // This lookup operation takes O(1) time on average.
            if (s1.count(n)) {
                // If 'n' is found in s1, it means 'n' is present in both nums1 and nums2.
                // Insert 'n' into our 'ans' hash set.
                // If 'n' was already inserted, the hash set will simply ignore the duplicate insertion,
                // maintaining the uniqueness requirement. This insertion also takes O(1) on average.
                ans.insert(n);
            }
        }

        // Step 5: Convert the elements from the 'ans' hash set into a vector<int>
        // and return it. The constructor `vector<int>(ans.begin(), ans.end())`
        // efficiently copies all elements from the hash set into a new vector.
        return vector<int>(ans.begin(), ans.end());
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(M + N) | Creating `s1` takes O(M) on average. Iterating `nums2` and performing lookups/insertions takes O(N) on average. M and N are lengths of `nums1` and `nums2` respectively. |
| **Space** | O(M + K) | `s1` stores up to M unique elements from `nums1`. `ans` stores up to K unique intersection elements, where K <= min(M, N). This simplifies to O(M) as K <= M. |

## 🔗 Related Problems
- 350. Intersection of Two Arrays II
- 217. Contains Duplicate
- 219. Contains Duplicate II