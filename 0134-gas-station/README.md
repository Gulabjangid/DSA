# 0134-gas-station

## 📋 Problem Description
You are given `n` gas stations arranged along a circular route. For each station `i`, `gas[i]` represents the amount of gas available at that station, and `cost[i]` represents the amount of gas required to travel from station `i` to the next station `(i + 1)`. You start your journey with an empty gas tank at one of the gas stations. Your car has an unlimited gas tank capacity.

The goal is to find a starting gas station index from which you can complete a full circle (travel around the route once in the clockwise direction). If such a starting station exists, return its 0-indexed position. If no such station exists, return `-1`. It is guaranteed that if a solution exists, it will be unique.

**Input:**
Two integer arrays, `gas` and `cost`, both of length `n`.

**Output:**
An integer representing the 0-indexed starting station, or `-1` if no solution exists.

## 🔍 Examples
```
Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
Output: 3
Explanation:
Start at station 3 (index 3) with 0 gas.
1. At station 3: tank = 0 + gas[3] = 0 + 4 = 4
2. Travel to station 4: tank = 4 - cost[3] + gas[4] = 4 - 1 + 5 = 8
3. Travel to station 0: tank = 8 - cost[4] + gas[0] = 8 - 2 + 1 = 7
4. Travel to station 1: tank = 7 - cost[0] + gas[1] = 7 - 3 + 2 = 6
5. Travel to station 2: tank = 6 - cost[1] + gas[2] = 6 - 4 + 3 = 5
6. Travel to station 3: tank = 5 - cost[2] = 5 - 5 = 0. You successfully return to station 3.
Therefore, station 3 is the starting index.
```

```
Input: gas = [2,3,4], cost = [3,4,3]
Output: -1
Explanation:
Let's try starting at station 0:
1. At station 0: tank = 0 + gas[0] = 2
2. Travel to station 1: tank = 2 - cost[0] = 2 - 3 = -1. Not enough gas.

Let's try starting at station 1:
1. At station 1: tank = 0 + gas[1] = 3
2. Travel to station 2: tank = 3 - cost[1] = 3 - 4 = -1. Not enough gas.

Let's try starting at station 2:
1. At station 2: tank = 0 + gas[2] = 4
2. Travel to station 0: tank = 4 - cost[2] + gas[0] = 4 - 3 + 2 = 3
3. Travel to station 1: tank = 3 - cost[0] + gas[1] = 3 - 3 + 3 = 3
4. Travel to station 2: tank = 3 - cost[1] = 3 - 4 = -1. Not enough gas.

No matter where you start, you cannot complete the circuit. Therefore, return -1.
```

## 📌 Constraints
*   `n == gas.length == cost.length`
*   `1 <= n <= 10^5`
*   `0 <= gas[i], cost[i] <= 10^4`
*   The input is generated such that the answer is unique.

## 🤔 Understanding the Problem
The problem asks us to find a valid starting point on a circular route from which we can complete a full loop. The key challenge is that we need to maintain a non-negative gas tank throughout the journey. Since the route is circular and we can start anywhere, a naive approach of trying every possible starting station and simulating the journey would be too slow for large `n`. We need an efficient way to determine if a solution exists and, if so, find the unique starting point.

## 💡 Core Idea
The fundamental insight is that if the total amount of gas available across all stations is less than the total cost to travel the entire circuit, then it's impossible to complete the circuit. Otherwise, a solution *must* exist. Furthermore, if we ever run out of gas while attempting a journey starting from a particular station, that station (and any station between it and the point where we ran out of gas) cannot be the correct starting point.

## 🧠 Approach — Greedy Approach
This problem can be solved using a **Greedy Approach**. The greedy strategy here is to iterate through the stations, keeping track of the current gas in the tank and a potential starting point. If at any point our tank balance drops below zero, it means our current `start` station was not valid. We then "reset" our potential starting point to the next station and reset our tank to zero, effectively discarding the previous segment as a potential starting path. This works because if we couldn't make it from `start` to `i`, we certainly couldn't make it from any station `j` between `start` and `i` to `i` either, as starting at `j` would mean we'd have even less gas accumulated by `i`.

## 📝 Step-by-Step Algorithm
1.  Initialize three variables:
    *   `total_gas_balance`: To keep track of the net gas (gas gained - gas spent) for the entire circuit. Initialize to 0.
    *   `current_tank_balance`: To keep track of the gas in the tank for the *current* potential journey. Initialize to 0.
    *   `start_station_index`: To store the potential starting station. Initialize to 0.

2.  Iterate through the stations from `i = 0` to `n - 1`:
    *   Calculate the `diff` for the current station: `diff = gas[i] - cost[i]`. This represents the net change in gas when you fill up at station `i` and travel to station `i+1`.
    *   Add `diff` to `total_gas_balance`. This accumulates the total net gas for the entire circuit.
    *   Add `diff` to `current_tank_balance`. This simulates the journey starting from `start_station_index`.
    *   Check if `current_tank_balance` has dropped below 0:
        *   If `current_tank_balance < 0`, it means that starting from `start_station_index`, we ran out of gas before reaching station `i+1`. Therefore, `start_station_index` (and any station between it and `i`) cannot be the correct starting point.
        *   In this case, update `start_station_index` to `i + 1` (the next station after the one where we failed).
        *   Reset `current_tank_balance` to 0, as we are effectively starting a new potential journey from `i + 1` with an empty tank.

3.  After the loop finishes, check the `total_gas_balance`:
    *   If `total_gas_balance >= 0`: This means there is enough total gas to complete the circuit. The `start_station_index` found by our greedy approach is the unique valid starting point. Return `start_station_index`.
    *   If `total_gas_balance < 0`: This means there isn't enough gas in total to complete the circuit, regardless of the starting point. Return `-1`.

## 💻 Solution
```cpp
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        // current_tank_balance tracks the gas in the tank if we start from 'start_station_index'.
        // If it ever drops below zero, it means 'start_station_index' is not a valid starting point.
        int current_tank_balance = 0;

        // start_station_index stores the potential starting station.
        // We initialize it to 0 and update it if our current journey fails.
        int start_station_index = 0;

        // total_gas_balance tracks the net gas for the entire circuit.
        // If this sum is negative, it's impossible to complete the circuit at all.
        int total_gas_balance = 0;

        // Iterate through each station to simulate the journey and find the potential start.
        for (int i = 0; i < gas.size(); i++) {
            // Calculate the net gas difference at the current station:
            // gas[i] is what we get, cost[i] is what we spend to leave.
            int diff = gas[i] - cost[i];

            // Add this difference to the total balance for the entire circuit.
            total_gas_balance += diff;

            // Add this difference to the current tank balance for the ongoing journey.
            current_tank_balance += diff;

            // If the current tank balance drops below zero, it means we ran out of gas
            // before reaching station i+1, starting from 'start_station_index'.
            if (current_tank_balance < 0) {
                // Therefore, 'start_station_index' is not valid.
                // The next potential starting station must be 'i + 1'.
                start_station_index = i + 1;
                // Reset the current tank balance to 0, as we are effectively
                // "restarting" our journey from the new 'start_station_index' with an empty tank.
                current_tank_balance = 0;
            }
        }

        // After checking all stations:
        // If total_gas_balance is non-negative, it means there's enough gas overall.
        // Due to the problem's guarantee of a unique solution if one exists,
        // the 'start_station_index' found by our greedy approach is the correct one.
        // If total_gas_balance is negative, it's impossible to complete the circuit.
        return total_gas_balance >= 0 ? start_station_index : -1;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the `gas` and `cost` arrays exactly once. Each operation inside the loop is constant time. |
| **Space** | O(1) | We only use a few constant-space variables (`current_tank_balance`, `start_station_index`, `total_gas_balance`) regardless of the input size `n`. |

## 🔗 Related Problems
- 53. Maximum Subarray
- 121. Best Time to Buy and Sell Stock