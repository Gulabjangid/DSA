# 0045-jump-game-ii

## 📋 Problem Description
You are given a 0-indexed array of non-negative integers `nums` of length `n`. You start at index 0.

Each element `nums[i]` represents the maximum length of a forward jump you can make from index `i`. This means if you are at index `i`, you can jump to any index `(i + j)` such that `0 <= j <= nums[i]` and `i + j < n`.

Your task is to return the minimum number of jumps required to reach the last index of the array, `n - 1`. The test cases are designed such that it's always guaranteed that you can reach the last index.

## 🔍 Examples
```
Input: nums = [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2.
             1. Jump 1 step from index 0 to 1 (since nums[0] = 2, we can jump 1 or 2 steps).
             2. Then jump 3 steps from index 1 to the last index (since nums[1] = 3, we can jump 1, 2, or 3 steps).
```

```
Input: nums = [2,3,0,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2.
             1. Jump 1 step from index 0 to 1.
             2. Then jump 3 steps from index 1 to the last index.
```

## 📌 Constraints
*   `1 <= nums.length <= 10^4`
*   `0 <= nums[i] <= 1000`
*   It's guaranteed that you can reach `nums[n - 1]`.

## 🤔 Understanding the Problem
The problem asks for the shortest path in terms of jumps from the start of an array to its end. From any position, we have a range of possible next positions. Since we want the *minimum* number of jumps, this often hints at either a Breadth-First Search (BFS) approach or a Greedy strategy. The non-trivial aspect is deciding which jump to make at each step to ensure the overall minimum. We don't want to just jump to the absolute farthest point every time, as that might not be optimal for subsequent jumps.

## 💡 Core Idea
The core idea is a greedy approach: at each step, we want to make a jump that maximizes our reach for the *next* jump. We don't necessarily jump to the absolute farthest point possible with the *current* jump, but rather ensure that from all positions reachable within the current jump's range, we identify the one that allows us to reach the furthest overall.

## 🧠 Approach — Greedy
This problem can be efficiently solved using a **Greedy** approach.

The greedy strategy works here because we are always trying to extend our reach as much as possible with each jump. We maintain a `current_end` which is the maximum index we can reach with the current number of jumps. As we iterate through the array, we also keep track of `farthest`, which is the maximum index we *could* reach if we were to make one more jump from any point within our current `current_end` range. When our current position `i` reaches `current_end`, it means we've exhausted all options for the current jump, so we must make a new jump. At this point, we increment our jump count and update `current_end` to `farthest`, effectively making the jump that covers the most ground for the next step. This ensures we always take the minimum number of jumps to cover the required distance.

## 📝 Step-by-Step Algorithm
1.  Initialize three variables:
    *   `jumps = 0`: This will count the total minimum jumps taken.
    *   `current_end = 0`: This marks the boundary of the current jump. All indices from the start up to `current_end` are reachable with `jumps` number of jumps. When our iteration index `i` reaches `current_end`, it means we need to make another jump.
    *   `farthest = 0`: This keeps track of the maximum index we can reach from any position `i` that we have visited so far within the current jump's range.

2.  Iterate through the `nums` array using an index `i` from `0` up to `n - 2` (where `n` is `nums.size()`). We iterate up to `n - 2` because if we are at `n - 1`, we have already reached the destination and don't need to make another jump.

3.  Inside the loop, for each `i`:
    *   Update `farthest`: Calculate the maximum index reachable from the current position `i` (which is `i + nums[i]`). Update `farthest` to be the maximum of its current value and this new calculated reach: `farthest = max(farthest, i + nums[i])`. This ensures `farthest` always holds the maximum possible reach from any point within the current jump's range.

    *   Check if `i` has reached `current_end`: If `i == current_end`, it means we have explored all positions reachable with the previous jump and must now commit to a new jump.
        *   Increment `jumps` by 1.
        *   Update `current_end` to `farthest`. This new `current_end` becomes the maximum reach achieved by the newly made jump.
        *   **Optimization**: If the new `current_end` is already greater than or equal to `n - 1`, it means we have reached or surpassed the last index. We can stop early and `break` out of the loop, as we've found the minimum jumps.

4.  After the loop finishes, return the total `jumps`.

## 💻 Solution
```cpp
class Solution {
public:
    int jump(vector<int>& nums) {
        // 'farthest' tracks the maximum index we can reach from any position
        // within the current jump's range.
        int farthest = 0;
        
        // 'jumps' counts the total number of jumps made.
        int jumps = 0;
        
        // 'current_end' marks the boundary of the current jump.
        // All positions from the start up to 'current_end' are reachable
        // with 'jumps' number of jumps. When 'i' reaches 'current_end',
        // it means we must make another jump.
        int current_end = 0;

        // We iterate through the array. We only need to iterate up to nums.size() - 2
        // because if we are at nums.size() - 1, we have already reached the end,
        // and we don't need to make another jump from there.
        // The loop condition 'i < nums.size() - 1' ensures we don't process the last element
        // as a starting point for a jump.
        for (int i = 0; i < nums.size() - 1; i++) {
            // Update 'farthest': from the current position 'i', we can jump
            // up to 'i + nums[i]'. We take the maximum of this and the
            // previously recorded 'farthest' reach. This 'farthest' represents
            // the maximum reach possible if we were to make our *next* jump
            // from any point between the previous 'current_end' and the current 'i'.
            farthest = max(farthest, i + nums[i]);
            
            // If 'i' has reached 'current_end', it means we have explored all
            // positions reachable with the previous jump. We must now make
            // a new jump to extend our reach.
            if (i == current_end) {
                // Increment the jump count.
                jumps++;
                
                // The new 'current_end' becomes the 'farthest' point we could
                // reach from any position within the range of the *previous* jump.
                // This effectively "makes" the jump to the point that allows maximum
                // future reach.
                current_end = farthest;

                // Optimization: If the new 'current_end' already reaches or
                // surpasses the last index (nums.size() - 1), we have found
                // the minimum jumps. We can stop early.
                if (current_end >= nums.size() - 1) {
                    break;
                }
            }
        }
        // Return the total number of jumps.
        return jumps;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The algorithm iterates through the `nums` array once. Each operation inside the loop (max, comparison, assignment) takes constant time. |
| **Space** | O(1) | The algorithm uses a fixed number of extra variables (`farthest`, `jumps`, `current_end`) regardless of the input array size. |

## 🔗 Related Problems
*   55. Jump Game
*   134. Gas Station
*   1306. Jump Game III