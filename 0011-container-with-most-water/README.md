# 0011-container-with-most-water

## 📋 Problem Description
You are given an array of integers `height`, where `n` is the length of the array. This array represents `n` vertical lines. For each index `i`, a line is drawn from coordinate `(i, 0)` to `(i, height[i])`.

The goal is to find two of these lines that, when combined with the x-axis, form a container capable of holding the maximum amount of water. You are not allowed to slant the container.

The function should return the maximum area of water that can be stored.

## 🔍 Examples
```
Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The lines at index 1 (height 8) and index 8 (height 7) form the container. The width is 8-1=7. The height is min(8,7)=7. Area = 7 * 7 = 49. This is the maximum possible.

Input: height = [1,1]
Output: 1
Explanation: The lines at index 0 (height 1) and index 1 (height 1) form the container. The width is 1-0=1. The height is min(1,1)=1. Area = 1 * 1 = 1.
```

## 📌 Constraints
*   `n == height.length`
*   `2 <= n <= 10^5`
*   `0 <= height[i] <= 10^4`

## 🤔 Understanding the Problem
The problem asks us to find two vertical lines from a given set such that the area they enclose with the x-axis is maximized. The area of a container formed by two lines `i` and `j` (where `i < j`) is determined by the height of the shorter line multiplied by the distance between them (`min(height[i], height[j]) * (j - i)`). A naive approach of checking every possible pair of lines would be `O(N^2)`, which is too slow for `N` up to `10^5`. The challenge is to find an efficient way to explore the pairs without checking all of them.

## 💡 Core Idea
The key insight is to start with the widest possible container and then iteratively reduce the width. In each step, we move the pointer associated with the *shorter* of the two current lines inwards. This is because moving the taller line would not increase the container's height (it's still limited by the shorter line) and would only decrease the width, thus guaranteeing a smaller or equal area. Moving the shorter line, however, offers a chance to find a taller line that could potentially increase the container's height and thus its area, even with a reduced width.

## 🧠 Approach — Two Pointers
This problem can be efficiently solved using the **Two Pointers** pattern. This pattern is suitable here because we need to find an optimal pair of elements (lines) from an array, and the decision of how to move the pointers (inwards) can prune a significant portion of the search space. By starting with pointers at the extreme ends and moving them based on a specific condition (the height of the shorter line), we systematically explore potential containers. This approach guarantees that we consider all potentially maximal areas without redundant calculations, as we eliminate one of the current lines from further consideration in each step.

## 📝 Step-by-Step Algorithm
1.  Initialize two pointers: `left` at the beginning of the `height` array (index 0) and `right` at the end of the `height` array (index `n-1`).
2.  Initialize a variable `max_water` to 0, which will store the maximum area found so far.
3.  Enter a loop that continues as long as the `left` pointer is less than the `right` pointer.
    a.  Calculate the `current_height` of the container. This is limited by the shorter of the two lines, so `current_height = min(height[left], height[right])`.
    b.  Calculate the `current_width` of the container. This is simply the distance between the two pointers: `current_width = right - left`.
    c.  Calculate the `current_area` using the `current_height` and `current_width`: `current_area = current_height * current_width`.
    d.  Update `max_water` if the `current_area` is greater than the `max_water` found so far: `max_water = max(max_water, current_area)`.
    e.  Now, decide which pointer to move inwards:
        i.  If `height[left]` is less than `height[right]`, it means the `left` line is currently limiting the container's height. To potentially find a taller container, we must try to increase the height. Moving the `left` pointer inwards (`left++`) might find a taller line, while moving the `right` pointer would only decrease the width without increasing the height.
        ii. Otherwise (if `height[right]` is less than or equal to `height[left]`), the `right` line is limiting the height. We move the `right` pointer inwards (`right--`) for the same reason.
4.  Once the `left` pointer crosses or meets the `right` pointer, the loop terminates.
5.  Return the final `max_water`.

## 💻 Solution

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        // Initialize the left pointer at the beginning of the array.
        int left = 0;
        // Initialize the right pointer at the end of the array.
        int right = height.size() - 1;

        // Initialize maxwater to store the maximum area found so far.
        int maxwater = 0;

        // Continue as long as the left pointer is to the left of the right pointer.
        // This ensures we always have a valid width (right - left > 0).
        while (left < right) {
            // Calculate the height of the container.
            // The water level is limited by the shorter of the two lines.
            int mheight = min(height[left], height[right]);
            
            // Calculate the width of the container.
            // This is the distance between the two lines.
            int width = right - left;
            
            // Calculate the current area and update maxwater if it's larger.
            maxwater = max(maxwater, mheight * width);
            
            // Decision to move pointers:
            // To potentially find a larger area, we must try to increase the height,
            // as the width is always decreasing.
            // The current height is limited by the shorter line.
            // Moving the taller line inward will not increase the height (still limited by the shorter line)
            // and will only decrease the width, thus guaranteeing a smaller or equal area.
            // Therefore, we must move the pointer of the shorter line inward,
            // hoping to find a taller line that can increase the container's height.
            if (height[left] < height[right]) {
                left++; // Move the left pointer if the left line is shorter.
            } else {
                right--; // Move the right pointer if the right line is shorter or equal.
            }
        }
        // Return the maximum water area found.
        return maxwater;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The `left` and `right` pointers traverse the array from opposite ends, making at most `N` steps in total. Each step involves constant time operations. |
| **Space** | O(1) | Only a few constant extra variables (`left`, `right`, `maxwater`, `mheight`, `width`) are used, regardless of the input size. |

## 🔗 Related Problems
*   167. Two Sum II - Input Array Is Sorted
*   42. Trapping Rain Water
*   283. Move Zeroes