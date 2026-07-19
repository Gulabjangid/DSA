# 0011-container-with-most-water

## 📋 Problem Description
You are given an integer array `height` of length `n`. This array represents `n` vertical lines. For each index `i`, a line is drawn from `(i, 0)` to `(i, height[i])`.

Your task is to find two of these lines that, together with the x-axis, form a container capable of holding the maximum amount of water. You must return this maximum amount of water.

It's important to note that the container cannot be slanted; the water level will always be limited by the shorter of the two chosen lines.

## 🔍 Examples
```
Input:  height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The lines are represented by the array. The maximum area of water (blue section in the problem image) is 49, achieved by lines at index 1 (height 8) and index 8 (height 7). The width is 8-1=7, and the height is min(8,7)=7, so area = 7*7 = 49.

Input:  height = [1,1]
Output: 1
Explanation: With lines of height 1 at index 0 and index 1, the width is 1-0=1, and the height is min(1,1)=1, so area = 1*1 = 1.
```

## 📌 Constraints
*   `n == height.length`
*   `2 <= n <= 10^5`
*   `0 <= height[i] <= 10^4`

## 🤔 Understanding the Problem
The problem asks us to find two vertical lines from a given set such that the area they enclose with the x-axis is maximized. The area of a container formed by two lines at indices `i` and `j` (where `i < j`) is determined by the `min(height[i], height[j]) * (j - i)`. The challenge lies in efficiently finding the optimal pair of lines, as a brute-force check of all possible pairs would be too slow for the given constraints.

## 💡 Core Idea
The core idea is that the area of a container is limited by its shorter side and its width. To maximize the area, we want to maximize both. By starting with the widest possible container and iteratively reducing the width, we can strategically discard non-optimal configurations. The key insight is that if we have two lines, moving the pointer of the *shorter* line inwards has the potential to find a taller line, which might increase the container's height and thus its area, even with a reduced width. Moving the pointer of the *taller* line inwards would only guarantee a reduced width and either the same or a reduced height (if the other line was shorter), making it less likely to find a larger area.

## 🧠 Approach — Two Pointers
This problem is efficiently solved using the **Two Pointers** pattern.

This pattern is suitable because we are looking for an optimal pair of elements (lines) within a sequence, and the decision to move one pointer or the other can prune the search space effectively. By starting with the widest possible container (pointers at both ends of the array) and moving inwards, we ensure that we are always considering the maximum possible width for the current pair of lines. The strategic decision to move the pointer of the shorter line allows us to explore configurations that might yield a greater height, which is crucial for finding the maximum area when the width is decreasing.

## 📝 Step-by-Step Algorithm
1.  Initialize two pointers: `left` at the beginning of the `height` array (index 0) and `right` at the end of the array (index `n-1`).
2.  Initialize a variable `max_water` to 0, which will store the maximum area found so far.
3.  Enter a loop that continues as long as the `left` pointer is less than the `right` pointer.
    a.  Calculate the `current_height` of the container. This is determined by the shorter of the two lines pointed to by `left` and `right`: `min(height[left], height[right])`.
    b.  Calculate the `current_width` of the container: `right - left`.
    c.  Calculate the `current_area`: `current_height * current_width`.
    d.  Update `max_water` if the `current_area` is greater than the current `max_water`: `max_water = max(max_water, current_area)`.
    e.  Now, decide which pointer to move:
        i.  If `height[left]` is less than `height[right]`, it means the left line is the bottleneck for the current container's height. To potentially find a taller container, we must try to find a taller line than `height[left]`. So, increment the `left` pointer (`left++`).
        ii. Otherwise (if `height[right]` is less than or equal to `height[left]`), the right line is the bottleneck (or both are equal). We decrement the `right` pointer (`right--`) to try and find a taller line from the right side.
4.  Once the loop finishes (when `left` meets or crosses `right`), return the `max_water`.

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
        // This ensures we always have a valid width (right - left > 0).
        while (left < right) {
            // Calculate the height of the current container.
            // Water level is limited by the shorter of the two lines.
            int mheight = std::min(height[left], height[right]);

            // Calculate the width of the current container.
            // This is simply the distance between the two pointers.
            int width = right - left;

            // Calculate the area of the current container and update maxwater
            // if this area is greater than the previously recorded maximum.
            maxwater = std::max(maxwater, mheight * width);

            // Decision to move pointers:
            // To potentially find a larger area, we must try to increase the height.
            // Moving the shorter line inwards might find a taller line,
            // which could increase the container's height.
            // Moving the taller line inwards would only guarantee a reduced width
            // and either the same or reduced height (if the other line was shorter),
            // making it less likely to find a larger area.
            if (height[left] < height[right]) {
                // If the left line is shorter, move the left pointer to the right.
                left++;
            } else {
                // If the right line is shorter or equal, move the right pointer to the left.
                right--;
            }
        }
        // After the loop, maxwater holds the maximum area found.
        return maxwater;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The `left` and `right` pointers traverse the array from opposite ends, making at most `N` steps in total. Each step involves constant time operations. |
| **Space** | O(1) | Only a few constant extra variables (`left`, `right`, `maxwater`, `mheight`, `width`) are used, regardless of the input array size. |

## 🔗 Related Problems
*   167. Two Sum II - Input Array Is Sorted
*   42. Trapping Rain Water
*   283. Move Zeroes