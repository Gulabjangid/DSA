# 0278-first-bad-version

## 📋 Problem Description
You are a product manager overseeing the development of a new product. Unfortunately, a recent version of the product has introduced a bug, causing it to fail quality checks. A critical property of this issue is that if a specific version is bad, all subsequent versions developed after it will also be bad.

Given a total of `n` versions, labeled from `1` to `n`, your task is to identify the very first version that is bad. This "first bad version" is the root cause, and all versions following it are consequently bad.

To assist you, an API function `bool isBadVersion(version)` is provided. This API takes a version number as input and returns `true` if that version is bad, and `false` otherwise. Your implementation should find the first bad version while minimizing the total number of calls made to the `isBadVersion` API.

The function you need to implement is `firstBadVersion(n)`, which takes the total number of versions `n` as input and must return an integer representing the first bad version.

## 🔍 Examples
```
Input: n = 5, bad = 4
Output: 4
Explanation:
isBadVersion(3) -> false (Version 3 is good)
isBadVersion(5) -> true  (Version 5 is bad)
isBadVersion(4) -> true  (Version 4 is bad)
Given this, version 4 is the first bad version.
```

```
Input: n = 1, bad = 1
Output: 1
Explanation:
isBadVersion(1) -> true (Version 1 is bad)
Given this, version 1 is the first bad version.
```

## 📌 Constraints
*   `1 <= bad <= n <= 2^31 - 1`

## 🤔 Understanding the Problem
The problem asks us to find the smallest version number `v` such that `isBadVersion(v)` returns `true`. The crucial piece of information is that if `isBadVersion(k)` is `true`, then `isBadVersion(k+1)`, `isBadVersion(k+2)`, ..., `isBadVersion(n)` will also be `true`. Conversely, if `isBadVersion(k)` is `false`, then `isBadVersion(k-1)`, `isBadVersion(k-2)`, ..., `isBadVersion(1)` will also be `false`. This establishes a monotonic property: there's a point where versions switch from being all good to all bad. A naive linear scan from version 1 to `n` would work but could make up to `n` API calls, which is too slow for `n` up to `2^31 - 1`.

## 💡 Core Idea
The problem exhibits a monotonic property: versions transition from "good" to "bad" at a specific point. This sorted-like behavior (false, false, ..., false, true, true, ..., true) is a classic indicator that a binary search algorithm can be applied to efficiently find the transition point.

## 🧠 Approach — Binary Search
This problem is a perfect candidate for **Binary Search**. The reason it fits so well is due to the inherent monotonic property of the versions: all versions before the first bad version are good, and all versions from the first bad version onwards are bad. This creates a "sorted" sequence of `isBadVersion` results (false, false, ..., false, true, true, ..., true). Binary search excels at finding a specific element or a boundary in such sorted or monotonically changing sequences, allowing us to drastically reduce the number of API calls needed.

## 📝 Step-by-Step Algorithm
1.  Initialize two pointers, `left` and `right`, to define the current search range. `left` starts at `1` (the first possible version) and `right` starts at `n` (the last possible version).
2.  Enter a `while` loop that continues as long as `left` is less than `right`. This condition ensures there's at least a two-element range to consider.
3.  Inside the loop, calculate the `mid` version. To prevent potential integer overflow when `left` and `right` are very large, use the formula `mid = left + (right - left) / 2` instead of `(left + right) / 2`.
4.  Call the `isBadVersion(mid)` API to check the status of the `mid` version.
5.  **If `isBadVersion(mid)` returns `true`**: This means `mid` is a bad version. Since we are looking for the *first* bad version, `mid` *could* be the first bad version, or an even earlier version might be. Therefore, we narrow our search to the left half, including `mid` itself. Update `right = mid`.
6.  **If `isBadVersion(mid)` returns `false`**: This means `mid` is a good version. Since all versions before `mid` are also good, the first bad version *must* be somewhere after `mid`. We narrow our search to the right half. Update `left = mid + 1`.
7.  When the `while` loop terminates, `left` will be equal to `right`. At this point, `left` (or `right`) will point to the first bad version. This is because our binary search strategy continuously shrinks the search space while maintaining the invariant that the first bad version is always within the `[left, right]` range, eventually converging `left` to the smallest bad version.
8.  Return `left`.

## 💻 Solution

```cpp
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        // Initialize 'left' pointer to the first possible version (1).
        // This represents the start of our search range.
        int left = 1;
        
        // Initialize 'right' pointer to the last possible version (n).
        // This represents the end of our search range.
        int right = n;
       
        // We use a binary search approach to find the first bad version.
        // The loop continues as long as 'left' is less than 'right'.
        // This condition implies there's still a range of at least two versions to check.
        // The goal is to converge 'left' and 'right' to the first bad version.
        while (left < right) {
            // Calculate the middle version.
            // Using `left + (right - left) / 2` prevents potential integer overflow
            // that `(left + right) / 2` might cause if `left + right` is very large.
            int mid = left + (right - left) / 2;
            
            // Check if the 'mid' version is bad using the provided API.
            if (isBadVersion(mid)) {
                // If 'mid' is a bad version, it means the first bad version
                // could be 'mid' itself, or it could be an earlier version.
                // So, we narrow our search to the left half, including 'mid'.
                // We set 'right = mid' because 'mid' is a potential answer.
                right = mid;
            } else {
                // If 'mid' is NOT a bad version (it's good), then the first bad version
                // must be somewhere AFTER 'mid'.
                // So, we narrow our search to the right half, starting from 'mid + 1'.
                // We set 'left = mid + 1' because 'mid' is definitely good.
                left = mid + 1;
            }
        }
        
        // When the loop terminates, 'left' will be equal to 'right'.
        // At this point, 'left' (or 'right') points to the first bad version.
        // This is because our binary search strategy always maintains the invariant
        // that the first bad version is within the [left, right] range,
        // and 'left' will converge to the smallest version that satisfies isBadVersion(version) == true.
        return left;
    }
};
```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(log n) | Binary search halves the search space in each iteration. The number of `isBadVersion` API calls is logarithmic with respect to `n`. |
| **Space** | O(1) | The algorithm uses a constant amount of extra space for variables like `left`, `right`, and `mid`, regardless of the input `n`. |

## 🔗 Related Problems
- 35. Search Insert Position
- 34. Find First and Last Position of Element in Sorted Array
- 69. Sqrt(x)