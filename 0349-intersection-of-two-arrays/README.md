# 0349-intersection-of-two-arrays

## 📋 Problem Description
Given two integer arrays, `nums1` and `nums2`, the task is to find their intersection. The intersection consists of all elements that are common to both arrays. Each element in the resulting array must be unique, and the order of elements in the result does not matter.

The function `intersection` receives two integer arrays, `nums1` and `nums2`, as input. It must return a `std::vector<int>` containing the unique elements found in the intersection of the two input arrays.

## 🔍 Examples
```
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2]
Explanation: The number 2 is present in both arrays. Even though it appears multiple times in nums1 and nums2, it should only be listed once in the output because only unique elements are required.
```

```
Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [9,4]
Explanation: Both 9 and 4 are present in nums1 and nums2. The order [4,9] is also accepted.
```

## 📌 Constraints
*   `1 <= nums1.length, nums2.length <= 1000`
*   `0 <= nums1[i], nums2[i] <= 1000`

## 🤔 Understanding the Problem
The problem asks us to identify all numbers that are present in *both* of the given input arrays. The key requirements are that the final result must contain only *unique* elements, and the order in which these elements appear in the output array does not matter. This means if a number `X` appears in both `nums1` and `nums2`, it should be included in our result exactly once, regardless of how many times it appears in the input arrays. This uniqueness requirement is a strong hint towards using data structures that inherently handle unique values.

## 💡 Core Idea
The most efficient way to find common unique elements and handle uniqueness automatically is to use a hash set (or `unordered_set` in C++). Hash sets provide average O(1) time complexity for insertion and lookup operations, making them ideal for quickly checking if an element exists in a collection and for storing only distinct values.

## 🧠 Approach — Hash Set / Hashing
This problem is a classic application of the **Hash Set** (or Hashing) pattern. Hash sets are perfect for this scenario because they offer two critical advantages:
1.  **Efficient Lookups**: We can check if an element exists in a hash set in average O(1) time. This is crucial for quickly determining if an element from one array is present in the other.
2.  **Automatic Uniqueness**: Hash sets, by definition, only store unique elements. Any attempt to insert a duplicate element will be ignored, which perfectly aligns with the problem's requirement for a unique intersection.
By leveraging these properties, we can efficiently build a set of unique elements from one array and then iterate through the second array, adding any common elements to a result set.

## 📝 Step-by-Step Algorithm
1.  **Initialize `set1`**: Create an empty hash set (e.g., `std::unordered_set<int>`) named `set1`.
2.  **Populate `set1`**: Iterate through each number in `nums1`. For every number encountered, insert it into `set1`. After this step, `set1` will contain all unique elements from `nums1`.
3.  **Initialize `resultSet`**: Create another empty hash set (e.g., `std::unordered_set<int>`) named `resultSet`. This set will store the unique elements that are found in the intersection.
4.  **Find Intersection**: Iterate through each number in `nums2`.
    a.  For each number `num` from `nums2`, check if `num` exists in `set1` (using `set1.count(num)` or `set1.find(num)`).
    b.  If `num` is found in `set1`, it means `num` is present in both `nums1` and `nums2`. Insert `num` into `resultSet`. Since `resultSet` is a hash set, it will automatically ensure that only unique common elements are stored.
5.  **Convert to Vector**: Finally, convert the `resultSet` into a `std::vector<int>` (as the problem requires a vector return type) and return this vector.

## 💻 Solution
```cpp
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        // Step 1 & 2: Create an unordered_set (hash set) from nums1.
        // This efficiently stores all unique elements of nums1.
        // The constructor `unordered_set<int>(nums1.begin(), nums1.end())`
        // populates the set with unique elements from nums1 in O(N1) average time.
        unordered_set<int> s1(nums1.begin(), nums1.end());

        // Step 3: Create another unordered_set to store the unique
        // elements found in the intersection. This set will automatically
        // handle the uniqueness requirement for the final result.
        unordered_set<int> ans;

        // Step 4: Iterate through each number in nums2.
        for (int num : nums2) {
            // Step 4a: Check if the current number from nums2 exists in s1.
            // `s1.count(num)` returns 1 if num is present, 0 otherwise.
            // This is an O(1) average-time operation.
            if (s1.count(num)) {
                // Step 4b: If the number is found in s1, it means it's common to both arrays.
                // Insert it into our 'ans' set. If 'num' is already in 'ans',
                // the set won't add a duplicate, maintaining uniqueness.
                ans.insert(num);
            }
        }
        
        // Step 5: The problem requires returning a vector<int>.
        // Convert the 'ans' unordered_set into a vector using its range constructor
        // and return it. This conversion takes O(K) time, where K is the size of 'ans'.
        return vector<int>(ans.begin(), ans.end());
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N1 + N2) | Creating `s1` from `nums1` takes O(N1) on average. Iterating through `nums2` (N2 elements) and performing `s1.count()` and `ans.insert()` operations each take O(1) on average, totaling O(N2). Converting the final set to a vector takes O(K) where K is the size of the intersection. Thus, the total average time complexity is O(N1 + N2). |
| **Space** | O(N1 + N2) | `s1` stores up to N1 unique elements from `nums1`. `ans` stores up to min(N1, N2) unique elements (the intersection). In the worst case, if all elements in `nums1` are unique and all elements in `nums2` are unique and distinct from `nums1`, the space would be proportional to N1 + N2. Given the constraint that `nums1[i], nums2[i] <= 1000`, the maximum number of unique elements is 1001, so space is also bounded by O(MaxVal) where MaxVal is the range of values. |

## 🔗 Related Problems
- 350. Intersection of Two Arrays II
- 217. Contains Duplicate
- 771. Jewels and Stones