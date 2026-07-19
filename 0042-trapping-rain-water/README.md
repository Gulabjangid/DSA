# 0042-trapping-rain-water

## 📋 Problem Description
You are given an array of `n` non-negative integers, `height`, which represents an elevation map. Each integer `height[i]` denotes the height of a bar, and each bar has a width of 1. Your task is to compute the total amount of water that can be trapped between these bars after it rains.

The function `trap` receives a `std::vector<int>& height` as input and must return an integer representing the total units of trapped rainwater.

## 🔍 Examples
```
Input:  height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The elevation map is shown in the problem description image. The black sections are the bars, and the blue sections represent the 6 units of trapped water.
```
```
Input:  height = [4,2,0,3,2,5]
Output: 9
Explanation:
- At index 1 (height 2), water trapped = min(4,5) - 2 = 2.
- At index 2 (height 0), water trapped = min(4,5) - 0 = 4.
- At index 3 (height 3), water trapped = min(4,5) - 3 = 1.
- At index 4 (height 2), water trapped = min(4,5) - 2 = 2.
Total = 2 + 4 + 1 + 2 = 9.
```
```
Input:  height = [2,0,2]
Output: 2
Explanation: At index 1 (height 0), water trapped = min(2,2) - 0 = 2.
```

## 📌 Constraints
*   `n == height.length`
*   `1 <= n <= 2 * 10^4`
*   `0 <= height[i] <= 10^5`

## 🤔 Understanding the Problem
The problem asks us to calculate the volume of water that can be held in the "valleys" formed by an elevation map. For any given bar at index `i`, the amount of water it can trap above itself depends on the height of the tallest bar to its left and the tallest bar to its right. Specifically, the water level at index `i` will be limited by the *minimum* of these two maximums. If this minimum is greater than `height[i]`, then `min(max_left, max_right) - height[i]` units of water are trapped at that position. The challenge is to efficiently find these maximums for every position and sum up the trapped water.

## 💡 Core Idea
The key insight is that for any bar, the amount of water it can trap is determined by the shorter of the tallest bar to its left and the tallest bar to its right. We can optimize this by using two pointers, one starting from the left and one from the right, and iteratively calculating trapped water based on the current maximums encountered from both sides.

## 🧠 Approach — Two Pointers
This problem is efficiently solved using the **Two Pointers** pattern. This pattern is suitable because we need to consider elements from both ends of the array to determine a local property (trapped water at a specific index). By maintaining two pointers, one moving from left to right and the other from right to left, we can simultaneously track the maximum height encountered so far from both directions. This allows us to make decisions about trapped water at the current pointer's position without needing to pre-compute full left-max and right-max arrays, leading to an optimal space complexity.

## 📝 Step-by-Step Algorithm
1.  **Initialization**:
    *   Get the size of the `height` array, `n`.
    *   Handle edge cases: If `n` is 0, 1, or 2, no water can be trapped, so return 0.
    *   Initialize `lmax` to the height of the first bar (`height[0]`). This will track the maximum height encountered from the left.
    *   Initialize `rmax` to the height of the last bar (`height[n-1]`). This will track the maximum height encountered from the right.
    *   Initialize `low` pointer to 1 (the second bar).
    *   Initialize `high` pointer to `n-2` (the second to last bar).
    *   Initialize `ans` (total trapped water) to 0.

2.  **Iterate with Two Pointers**:
    *   Continue the loop as long as `low` is less than or equal to `high`.
    *   Inside the loop, update `lmax` by taking the maximum of its current value and `height[low]`. This ensures `lmax` always holds the tallest bar seen from the left up to the current `low` position.
    *   Similarly, update `rmax` by taking the maximum of its current value and `height[high]`. This ensures `rmax` always holds the tallest bar seen from the right down to the current `high` position.

3.  **Decision and Calculation**:
    *   **Compare `lmax` and `rmax`**:
        *   If `lmax < rmax`: This means the water level at the `low` pointer's position is limited by `lmax`. We are guaranteed that there is a bar on the right side (at or beyond `high`) that is at least as tall as `rmax`, and thus taller than `lmax`. Therefore, the water trapped above `height[low]` is `lmax - height[low]`. Add this amount to `ans`. Then, increment `low` to move to the next bar from the left.
        *   If `rmax <= lmax`: This means the water level at the `high` pointer's position is limited by `rmax`. We are guaranteed that there is a bar on the left side (at or before `low`) that is at least as tall as `lmax`, and thus taller than or equal to `rmax`. Therefore, the water trapped above `height[high]` is `rmax - height[high]`. Add this amount to `ans`. Then, decrement `high` to move to the next bar from the right.

4.  **Return Result**:
    *   Once the loop finishes (when `low` crosses `high`), return the accumulated `ans`.

## 💻 Solution
```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        // Base case: If there are 0, 1, or 2 bars, no water can be trapped.
        if (n <= 2)
            return 0;

        // lmax: Tracks the maximum height encountered from the left side.
        // Initialized with the height of the first bar.
        int lmax = height[0];
        // rmax: Tracks the maximum height encountered from the right side.
        // Initialized with the height of the last bar.
        int rmax = height[n - 1];

        // low: Left pointer, starts from the second bar (index 1).
        int low = 1;
        // high: Right pointer, starts from the second to last bar (index n-2).
        int high = n - 2;

        // ans: Stores the total trapped water.
        int ans = 0;

        // Loop until the pointers cross each other.
        while (low <= high) {
            // Update lmax with the maximum height seen so far from the left,
            // including the current bar at 'low'.
            lmax = max(lmax, height[low]);
            // Update rmax with the maximum height seen so far from the right,
            // including the current bar at 'high'.
            rmax = max(rmax, height[high]);

            // Decision point: Which side is currently limiting the water level?
            if (lmax < rmax) {
                // If lmax is smaller, it means the water level at 'low' is limited by lmax.
                // We are guaranteed that there's a wall on the right (at least rmax tall)
                // that is taller than lmax. So, water trapped at 'low' is lmax - height[low].
                ans += lmax - height[low];
                // Move the left pointer to the right.
                low++;
            } else {
                // If rmax is smaller or equal, it means the water level at 'high' is limited by rmax.
                // We are guaranteed that there's a wall on the left (at least lmax tall)
                // that is taller than or equal to rmax. So, water trapped at 'high' is rmax - height[high].
                ans += rmax - height[high];
                // Move the right pointer to the left.
                high--;
            }
        }
        // Return the total accumulated trapped water.
        return ans;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(n) | The `low` and `high` pointers traverse the array from opposite ends, each visiting every element at most once. The loop runs `n-2` times, and operations inside the loop are constant time. |
| **Space** | O(1) | Only a few constant extra variables (`n`, `lmax`, `rmax`, `low`, `high`, `ans`) are used, regardless of the input array size. |

## 🔗 Related Problems
- 11. Container With Most Water
- 407. Trapping Rain Water II
- 420. Strong Password Checker (uses two pointers for different reasons, but good practice)