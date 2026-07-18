# 0134-gas-station

## 📋 Problem Description
You are given `n` gas stations arranged along a circular route. For each station `i`, `gas[i]` represents the amount of gas you can fill up, and `cost[i]` is the amount of gas required to travel from station `i` to the next station `(i + 1)`. You start with an empty gas tank at one of the gas stations.

The goal is to find a starting gas station index from which you can complete a full circular trip in the clockwise direction. If such a starting station exists, it is guaranteed to be unique. If no such station allows you to complete the circuit, return `-1`.

**Input:**
- `gas`: An integer array where `gas[i]` is the amount of gas at station `i`.
- `cost`: An integer array where `cost[i]` is the gas needed to travel from station `i` to station `i+1`.

**Output:**
- An integer representing the unique starting station index if a circuit can be completed, otherwise `-1`.

## 🔍 Examples
```
Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
Output: 3
Explanation:
If you start at station 3:
Tank = 0 (initial)
1. At station 3: Fill 4 gas. Tank = 0 + 4 = 4.
2. Travel to station 4: Cost 1. Tank = 4 - 1 = 3. At station 4: Fill 5 gas. Tank = 3 + 5 = 8.
3. Travel to station 0: Cost 2. Tank = 8 - 2 = 6. At station 0: Fill 1 gas. Tank = 6 + 1 = 7.
4. Travel to station 1: Cost 3. Tank = 7 - 3 = 4. At station 1: Fill 2 gas. Tank = 4 + 2 = 6.
5. Travel to station 2: Cost 4. Tank = 6 - 4 = 2. At station 2: Fill 3 gas. Tank = 2 + 3 = 5.
6. Travel to station 3: Cost 5. Tank = 5 - 5 = 0.
You successfully completed the circuit, returning to station 3 with 0 gas.
```

```
Input: gas = [2,3,4], cost = [3,4,3]
Output: -1
Explanation:
Total gas available = 2 + 3 + 4 = 9.
Total gas required = 3 + 4 + 3 = 10.
Since total gas available (9) is less than total gas required (10), it's impossible to complete the circuit from any starting station.
```

## 📌 Constraints
*   `n == gas.length == cost.length`
*   `1 <= n <= 10^5`
*   `0 <= gas[i], cost[i] <= 10^4`
*   The input is generated such that the answer is unique if it exists.

## 🤔 Understanding the Problem
The problem asks us to find a valid starting point on a circular route such that we can travel all the way around and return to the starting point. We need to keep track of the gas in our tank, ensuring it never drops below zero during travel. The key challenge is that a brute-force approach (trying every possible starting station and simulating the entire trip) would be too slow for large `n`. We need a more efficient way to determine the starting point.

## 💡 Core Idea
If the total amount of gas available across all stations is less than the total cost to travel between all stations, it's impossible to complete the circuit. Otherwise, a unique solution *must* exist. We can find this solution by iterating once, tracking the current tank level and resetting the potential starting point whenever the tank runs out of gas.

## 🧠 Approach — Greedy
This problem can be solved using a **Greedy** approach. The greedy strategy works because of two crucial properties:
1.  If the total gas available (`sum(gas)`) is less than the total cost required (`sum(cost)`), it's impossible to complete the circuit.
2.  If `sum(gas) >= sum(cost)`, a solution *must* exist, and it is guaranteed to be unique.
The greedy choice is to keep track of the current gas in the tank. If at any point the tank becomes negative (meaning we can't reach the next station), then our current chosen starting point is invalid. Furthermore, any station *between* our initial starting point and the station where we ran out of gas is also invalid. This allows us to "reset" our potential starting point to the station *after* the one where we failed, effectively making a locally optimal choice that leads to the global solution.

## 📝 Step-by-Step Algorithm
1.  Initialize three variables:
    *   `total_gas_balance`: To keep track of the net gas difference over the entire circuit. Initialize to `0`.
    *   `current_tank_gas`: To simulate the gas in the tank for a potential journey starting from `start_station`. Initialize to `0`.
    *   `start_station`: To store the index of the potential starting station. Initialize to `0`.
2.  Iterate through the gas stations from index `0` to `n-1`:
    a.  For each station `i`, calculate the `net_diff` by subtracting the `cost[i]` to travel to the next station from the `gas[i]` available at the current station: `net_diff = gas[i] - cost[i]`.
    b.  Add this `net_diff` to `total_gas_balance`. This accumulates the overall gas situation for the entire circuit.
    c.  Add this `net_diff` to `current_tank_gas`. This simulates the journey starting from the current `start_station`.
    d.  Check if `current_tank_gas` has become negative. If `current_tank_gas < 0`:
        *   This means we ran out of gas before reaching station `i+1` if we started at `start_station`. Therefore, `start_station` (and any station between `start_station` and `i`) cannot be a valid starting point.
        *   Reset `start_station` to `i + 1`. This is our new potential starting point.
        *   Reset `current_tank_gas` to `0`, as if we are starting fresh from `i + 1` with an empty tank.
3.  After iterating through all stations, check the `total_gas_balance`:
    a.  If `total_gas_balance >= 0`, it means there is enough total gas to complete the circuit. In this case, the `start_station` we found is the unique valid starting point. Return `start_station`.
    b.  If `total_gas_balance < 0`, it means there isn't enough gas in total to complete the circuit, regardless of the starting point. Return `-1`.

## 💻 Solution
```cpp
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        // current_tank_gas tracks the gas in the tank if we start at 'start_station'.
        // If it ever drops below zero, it means 'start_station' is not valid.
        int current_tank_gas = 0;

        // start_station stores the index of the potential starting station.
        // We initialize it to 0, assuming we might start there.
        int start_station = 0;

        // total_gas_balance tracks the net gas difference over the entire circuit.
        // If this sum is negative at the end, it's impossible to complete the circuit.
        int total_gas_balance = 0;

        // Iterate through each gas station.
        for (int i = 0; i < gas.size(); i++) {
            // Calculate the net gas difference at the current station:
            // gas[i] is what we gain, cost[i] is what we spend to leave.
            int diff = gas[i] - cost[i];

            // Add this difference to the total balance for the entire circuit.
            total_gas_balance += diff;

            // Add this difference to our current tank simulation.
            // This simulates traveling from 'start_station' up to 'i' and then to 'i+1'.
            current_tank_gas += diff;

            // If current_tank_gas becomes negative, it means we couldn't reach station 'i+1'
            // from our current 'start_station'.
            if (current_tank_gas < 0) {
                // Since we failed to reach station 'i+1', 'start_station' (and any station
                // between 'start_station' and 'i') cannot be a valid starting point.
                // The next possible valid starting point must be 'i + 1'.
                start_station = i + 1;
                // Reset current_tank_gas to 0, as if we are starting fresh from 'i + 1'
                // with an empty tank.
                current_tank_gas = 0;
            }
        }

        // After checking all stations:
        // If total_gas_balance is non-negative, it means there's enough gas overall
        // to complete the circuit. Due to the problem's properties (unique solution
        // if one exists), the 'start_station' we found is the correct one.
        // If total_gas_balance is negative, it's impossible to complete the circuit.
        return total_gas_balance >= 0 ? start_station : -1;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The algorithm iterates through the `gas` and `cost` arrays exactly once, performing constant time operations in each step. `N` is the number of gas stations. |
| **Space** | O(1) | The algorithm uses a fixed number of variables (`current_tank_gas`, `start_station`, `total_gas_balance`) regardless of the input size. |

## 🔗 Related Problems
-   53. Maximum Subarray
-   121. Best Time to Buy and Sell Stock
-   1186. Maximum Subarray Sum with One Deletion