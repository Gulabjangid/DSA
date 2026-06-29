## 💡 Core Idea
The core idea leverages the sorted nature of the input array. By using two pointers, one at the beginning and one at the end, we can efficiently check the sum of the elements they point to. Based on whether this sum is greater than, less than, or equal to the target, we can strategically move one of the pointers to narrow down the search space.

## 🧠 Solution Pattern
This solution employs the **Two Pointers** algorithmic pattern. This pattern is ideal for problems involving sorted arrays where you need to find a pair of elements that satisfy a certain condition (like summing to a target). By moving pointers from opposite ends, we can efficiently explore potential pairs while maintaining the sorted property to guide our search.

## 📝 Step-by-Step Explanation
1.  **Initialization**:
    *   Initialize a `left` pointer to the beginning of the array (index `0`).
    *   Initialize a `right` pointer to the end of the array (index `nums.size() - 1`).

2.  **Iteration**:
    *   Enter a `while` loop that continues as long as `left` is less than `right`. This ensures we are always considering two distinct elements and that the pointers haven't crossed.

3.  **Calculate Current Sum**:
    *   Inside the loop, calculate the `current_sum` by adding the elements at the `left` and `right` pointers: `nums[left] + nums[right]`.

4.  **Compare with Target**:
    *   **Case 1: `current_sum == target`**: If the `current_sum` equals the `target`, we have found the desired pair. The problem asks for 1-indexed results, so we return `{left + 1, right + 1}`.
    *   **Case 2: `current