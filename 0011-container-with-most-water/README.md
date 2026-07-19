# 0011-container-with-most-water

## 📋 Problem Description
You are given an integer array `height` of length `n`. This array represents `n` vertical lines. For each index `i`, a line is drawn from coordinate `(i, 0)` to `(i, height[i])`.

The goal is to find two of these lines that, along with the x-axis, can form a container. This container should be able to hold the maximum possible amount of water. You are not allowed to slant the container, meaning the lines must remain vertical.

The function `maxArea` receives one argument:
- `height`: An array of integers, where `height[i]` is the height of the `i`-th line.

It must return:
- An integer representing the maximum amount of water that can be stored in a container formed by any two lines.

## 🔍 Examples
```
Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The lines are represented by the array [1,8,6,2,5,4,8,3,7]. The maximum area of water (blue section in the problem image) the container can contain is 49. This is formed by lines at index 1 (height 8) and index 8 (height 7). The width is 8-1=7, and the effective height is min(8,7)=7. Area = 7*7 = 49.

Input: height = [1,1]
Output: 1
Explanation: With lines of height 1 at index 0 and index 1, the width is 1-0=1 and the effective height is min(1,1)=1. Area = 1*1 = 1.
```

## 📌 Constraints
*   `n == height.length`
*   `2 <= n <= 10^5`
*   `0 <= height[i] <= 10^4`

## 🤔 Understanding the Problem
The problem asks us to find the pair of vertical lines that enclose the largest area when considering the x-axis as the base. The area of a container formed by two lines at indices `i` and `j` (where `i < j`) is determined by the shorter of the two lines' heights multiplied by the distance between them. That is, `Area = min(height[i], height[j]) * (j - i)`. The challenge is to efficiently find the optimal pair among all possible `n * (n-1) / 2` combinations, as a brute-force approach would be too slow for `n` up to `10^5`.

## 💡 Core Idea
The area of a container is limited by its shorter side and its width. To maximize the area, we want to find a balance between these two factors. The key insight is that if we have two pointers at the extreme ends of the array, moving the pointer corresponding to the *shorter* line inwards has the potential to increase the area. This is because moving the taller line inwards will definitely decrease the width, and the height is still limited by the shorter line, thus guaranteeing a smaller or equal area. Moving the shorter line, however, might find a taller line, potentially increasing the effective height and thus the area, even with a reduced width.

## 🧠 Approach — Two Pointers
This problem is efficiently solved using the **Two Pointers** pattern. This pattern is suitable here because we are looking for an optimal pair of elements (lines) within an array, and we can make decisions to narrow down the search space by moving pointers from both ends towards the center. The decision to move one pointer over the other is based on a local greedy choice that helps us progress towards the global optimum.

## 📝 Step-by-Step Algorithm
1.  Initialize two pointers, `left` at the beginning of the `height` array (index 0) and `right` at the end of the `height` array (index `n-1`).
2.  Initialize a variable `max_water` to 0, which will store the maximum area found so far.
3.  Enter a loop that continues as long as the `left` pointer is less than the `right` pointer.
    a.  Calculate the `current_height` of the container. This is determined by the shorter of the two lines pointed to by `left` and `right`: `min(height[left], height[right])`.
    b.  Calculate the `width` of the container. This is simply the distance between the two pointers: `right - left`.
    c.  Calculate the `current_area` using the formula: `current_height * width`.
    d.  Update `max_water` if the `current_area` is greater than the `max_water` found so far: `max_water = max(max_water, current_area)`.
    e.  Now, decide which pointer to move:
        i.  If `height[left]` is less than `height[right]`, it means the `left` line is currently limiting the container's height. To potentially find a taller container, we must try to find a taller line on the left side. So, increment `left` by one.
        ii. Otherwise (if `height[right]` is less than or equal to `height[left]`), the `right` line is limiting the height. We try to find a taller line on the right side by decrementing `right` by one.
4.  Once the loop finishes (when `left` meets or crosses `right`), return `max_water`.

## 💻 Solution
```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        // Initialize the left pointer to the beginning of the array.
        int left = 0;
        // Initialize the right pointer to the end of the array.
        int right = height.size() - 1;

        // Initialize maxwater to store the maximum area found so far.
        int maxwater = 0;

        // Continue as long as the left pointer is to the left of the right pointer.
        while (left < right) {
            // Calculate the effective height of the container.
            // It's limited by the shorter of the two lines.
            int mheight = min(height[left], height[right]);
            
            // Calculate the width of the container.
            // This is the distance between the two lines.
            int width = right - left;
            
            // Calculate the current area and update maxwater if it's larger.
            maxwater = max(maxwater, mheight * width);
            
            // Decision to move pointers:
            // If the left line is shorter, moving it might find a taller line
            // and potentially increase the container's height.
            // Moving the right pointer in this case would only decrease width
            // without improving height, leading to a smaller area.
            if (height[left] < height[right]) {
                left++; // Move the left pointer to the right.
            } 
            // If the right line is shorter (or equal height),
            // moving it might find a taller line.
            else {
                right--; // Move the right pointer to the left.
            }
        }
        // Return the maximum water found.
        return maxwater;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The `left` and `right` pointers start at opposite ends and move towards each other, performing a constant amount of work in each step. In the worst case, they will meet after `N` steps. |
| **Space** | O(1) | Only a few constant-space variables (`left`, `right`, `maxwater`, `mheight`, `width`) are used, regardless of the input array size. |

## 🔗 Related Problems
- 167. Two Sum II - Input Array Is Sorted
- 42. Trapping Rain Water
- 283. Move Zeroes