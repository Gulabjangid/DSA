# 0045-jump-game-ii

## 📋 Problem Description
You are given a 0-indexed array of non-negative integers, `nums`, of length `n`. You start at index 0. Each element `nums[i]` represents the maximum possible length of a forward jump you can make from index `i`. This means if you are at index `i`, you can jump to any index `(i + j)` where `0 <= j <= nums[i]` and `i + j < n`.

The goal is to find the minimum number of jumps required to reach the last index of the array, `n - 1`. It is guaranteed that you can always reach the last index.

The function should accept a `std::vector<int> nums` as input and return an `int` representing the minimum number of jumps.

## 🔍 Examples
```
Input: nums = [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2.
             1. Jump 1 step from index 0 to 1 (since nums[0] = 2, we can jump up to 2 steps).
             2. Then jump 3 steps from index 1 to the last index (since nums[1] = 3, we can jump up to 3 steps).
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
The problem asks us to find the shortest path in terms of jumps from the start of an array to its end. Each array element tells us how far we *can* jump, not how far we *must* jump. This means we have choices at each step. The challenge is to make optimal choices to minimize the total number of jumps, which makes it a classic optimization problem. The guarantee that the end is always reachable simplifies things by removing the need to handle unreachable cases.

## 💡 Core Idea
The core idea is a greedy approach: at each step, when we are forced to make a jump, we should always choose the jump that allows us to reach the farthest possible index. This maximizes our progress with each jump, thus minimizing the total number of jumps.

## 🧠 Approach — Greedy
This problem can be efficiently solved using a **Greedy** approach. The greedy strategy works here because to minimize the total number of jumps, at any point where we *must* make a jump, we should always aim to make the jump that extends our reach as far as possible. This ensures we cover the maximum ground with each jump, reducing the total count. We don't need to consider all possible jump combinations; simply picking the "best" immediate jump (the one that reaches farthest) will lead to the global optimum.

## 📝 Step-by-Step Algorithm
1.  Initialize three variables:
    *   `jumps`: To count the total number of jumps taken, starting at 0.
    *   `current_end`: This marks the maximum index reachable with the *current* number of jumps. Initially, we are at index 0, so the first "jump" hasn't happened yet, and its effective range is 0.
    *   `farthest`: This tracks the maximum index we can reach from *any* position within the current jump's range. Initialize to 0.

2.  Iterate through the `nums` array from index `i = 0` up to `nums.size() - 2`. We stop at `nums.size() - 2` because if `i` reaches `nums.size() - 1`, it means we are already at the last index, and no more jumps are needed from that position.

3.  Inside the loop, for each index `i`:
    *   Update `farthest`: Calculate the maximum index reachable from the current position `i` (`i + nums[i]`). Update `farthest` to be the maximum of its current value and this new potential reach. This `farthest` represents the best possible reach if we were to make a jump from *any* point within our current jump's range.

    *   Check if `i` has reached `current_end`: If `i` is equal to `current_end`, it means we have explored all positions reachable with the *previous* jump. We are now at the boundary, and we *must* take another jump to proceed.
        *   Increment `jumps` by 1.
        *   Update `current_end`: The new `current_end` for the next jump will be the `farthest` position we could have reached from any point within the previous jump's range.
        *   **Early Exit Condition**: After updating `current_end`, check if `current_end` has already reached or surpassed the last index (`nums.size() - 1`). If it has, it means we have successfully reached the target with the current number of jumps, so we can `break` out of the loop and return `jumps`.

4.  After the loop finishes, return the total `jumps` count.

## 💻 Solution
```cpp
class Solution {
public:
    int jump(vector<int>& nums) {
        // 'farthest' tracks the maximum index we can reach from any point
        // within the current jump's range.
        int farthest = 0;
        
        // 'jumps' counts the total number of jumps taken.
        int jumps = 0;
        
        // 'current_end' marks the boundary of the current jump's reach.
        // When 'i' reaches 'current_end', it means we've explored all positions
        // reachable with the previous jump, and now we must take a new jump.
        int current_end = 0;

        // We iterate through the array. The loop goes up to nums.size() - 2
        // because if 'i' is nums.size() - 1, we are already at the last index,
        // and no more jumps are needed from that position.
        for (int i = 0; i < nums.size() - 1; i++) {
            // Update 'farthest': Calculate the maximum index reachable from the
            // current position 'i' (i + nums[i]).
            // 'farthest' will always store the maximum reach possible from any
            // point we've visited so far within the current jump's scope.
            farthest = max(farthest, i + nums[i]);
            
            // If 'i' has reached 'current_end', it means we have explored all
            // positions reachable with the *previous* jump. We are at the boundary
            // and must take a new jump to proceed further.
            if (i == current_end) {
                // Increment the jump count.
                jumps++;
                
                // The new 'current_end' for the next jump will be the 'farthest'
                // position we could have reached from any point within the previous jump's range.
                current_end = farthest;

                // Optimization: If our new 'current_end' already reaches or surpasses
                // the last index, we've successfully reached the target.
                // We can break early as no more jumps are needed.
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
| **Time** | O(N) | The algorithm iterates through the `nums` array exactly once, performing constant time operations in each step. |
| **Space** | O(1) | The algorithm uses a fixed number of variables (`farthest`, `jumps`, `current_end`) regardless of the input array size. |

## 🔗 Related Problems
-   55. Jump Game
-   134. Gas Station
-   739. Daily Temperatures (uses a monotonic stack, but similar idea of finding "next greater/farthest" element)