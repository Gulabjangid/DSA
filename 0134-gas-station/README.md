# 0134-gas-station

## 📋 Problem Description
You are given `n` gas stations arranged along a circular route. For each station `i`, `gas[i]` represents the amount of gas available at that station, and `cost[i]` represents the gas required to travel from station `i` to the next station `(i + 1)`. You start with an empty gas tank at one of the stations. Your car has an unlimited gas tank.

The goal is to find a starting gas station index from which you can travel around the entire circular route once in the clockwise direction. If such a starting station exists, return its 0-indexed position. If no such station allows you to complete the circuit, return `-1`. It is guaranteed that if a solution exists, it is unique.

**Input:**
Two integer arrays, `gas` and `cost`, both of length `n`.

**Output:**
An integer representing the 0-indexed starting station, or `-1` if no solution exists.

## 🔍 Examples
```
Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
Output: 3
Explanation:
Start at station 3 (index 3) and fill up with 4 units of gas. Your tank = 0 + 4 = 4
Travel to station 4. Your tank = 4 - 1 + 5 = 8
Travel to station 0. Your tank = 8 - 2 + 1 = 7
Travel to station 1. Your tank = 7 - 3 + 2 = 6
Travel to station 2. Your tank = 6 - 4 + 3 = 5
Travel to station 3. The cost is 5. Your gas is just enough to travel back to station 3.
Therefore, return 3 as the starting index.
```

```
Input: gas = [2,3,4], cost = [3,4,3]
Output: -1
Explanation:
You can't start at station 0 or 1, as there is not enough gas to travel to the next station.
Let's start at station 2 and fill up with 4 units of gas. Your tank = 0 + 4 = 4
Travel to station 0. Your tank = 4 - 3 + 2 = 3
Travel to station 1. Your tank = 3 - 3 + 3 = 3
You cannot travel back to station 2, as it requires 4 units of gas but you only have 3.
Therefore, you can't travel around the circuit once no matter where you start.
```

## 📌 Constraints
*   `n == gas.length == cost.length`
*   `1 <= n <= 10^5`
*   `0 <= gas[i], cost[i] <= 10^4`
*   The input is generated such that the answer is unique.

## 🤔 Understanding the Problem
The problem asks us to find a valid starting point on a circular route where we can complete a full loop, given gas available at each station and cost to travel to the next. The key challenge is that the route is circular, and we need to manage our gas tank balance. The "unlimited gas tank" simply means we don't have to worry about overflow, only underflow (running out of gas). The guarantee of a unique solution simplifies things, as we don't need to find all possible starting points.

## 💡 Core Idea
The core idea is that if the total amount of gas available across all stations is less than the total cost to travel between all stations, it's impossible to complete the circuit. Otherwise, a solution must exist. We can find this unique starting point by tracking the current gas in the tank and resetting our potential starting point whenever the tank runs dry.

## 🧠 Approach — Greedy
This problem can be solved using a **Greedy** approach. The greedy strategy works here because if we cannot reach station `i+1` starting from station `j`, then any station between `j` and `i` (inclusive) also cannot be a valid starting point to reach `i+1`. This allows us to "discard" a range of potential starting points and move our candidate starting point forward.

The logic is that we iterate through the stations, keeping track of the current gas in the tank. If at any point our tank balance drops below zero, it means our current chosen starting point was invalid. We then reset our tank to zero and consider the *next* station as a new potential starting point. By doing this, we ensure that the final `start` index we are left with, assuming a solution exists, will be the correct one.

## 📝 Step-by-Step Algorithm
1.  Initialize three variables:
    *   `total_gas_balance`: To keep track of the net gas difference (`gas[i] - cost[i]`) across the entire circuit. Initialize to 0.
    *   `current_tank_balance`: To keep track of the gas in the tank if we started at the current `start_station_candidate`. Initialize to 0.
    *   `start_station_candidate`: To store the index of the potential starting station. Initialize to 0.

2.  Iterate through the stations from index `0` to `n-1`:
    *   For each station `i`, calculate the `diff = gas[i] - cost[i]`. This represents the net change in gas when arriving at station `i` and then traveling to `i+1`.
    *   Add `diff` to `total_gas_balance`. This accumulates the overall gas balance for the entire circuit.
    *   Add `diff` to `current_tank_balance`. This simulates filling up at station `i` and then spending gas to travel to `i+1`, assuming `start_station_candidate` was our actual starting point.
    *   Check if `current_tank_balance` becomes negative:
        *   If `current_tank_balance < 0`, it means we ran out of gas before reaching station `i+1` if we started at `start_station_candidate`. Therefore, `start_station_candidate` (and any station between it and `i`) cannot be a valid starting point.
        *   In this case, update `start_station_candidate` to `i + 1` (the next station after the one where we failed).
        *   Reset `current_tank_balance` to `0`, as we are effectively "restarting" our journey from `i + 1` with an empty tank.

3.  After iterating through all stations:
    *   Check `total_gas_balance`:
        *   If `total_gas_balance >= 0`, it means there is enough gas overall to complete the circuit. Because of the problem guarantee that a unique solution exists if one is possible, the final `start_station_candidate` will be the correct answer. Return `start_station_candidate`.
        *   If `total_gas_balance < 0`, it means there isn't enough gas in total to complete the circuit, regardless of the starting point. Return `-1`.

## 💻 Solution

```cpp
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        // current_tank_balance tracks the gas in the tank if we start at 'start_station_candidate'
        // and travel up to the current station 'i'.
        int current_tank_balance = 0; 
        
        // start_station_candidate stores the potential starting station index.
        // It gets updated whenever 'current_tank_balance' drops below zero.
        int start_station_candidate = 0; 
        
        // total_gas_balance tracks the net gas difference (gas[i] - cost[i])
        // accumulated over all stations. If this sum is negative at the end,
        // it's impossible to complete the circuit.
        int total_gas_balance = 0; 

        // Iterate through each station to simulate the journey.
        for (int i = 0; i < gas.size(); i++) {
            // Calculate the net gas difference at the current station:
            // gas[i] is filled, cost[i] is spent to travel to the next station.
            int diff = gas[i] - cost[i];
            
            // Add this difference to the total balance for the entire circuit.
            total_gas_balance += diff;
            
            // Add this difference to the current tank balance.
            // This simulates the gas in the tank if we started from 'start_station_candidate'.
            current_tank_balance += diff;
            
            // If current_tank_balance drops below zero, it means we ran out of gas
            // before reaching station i+1, assuming we started from 'start_station_candidate'.
            // Therefore, 'start_station_candidate' (and any station between it and 'i')
            // cannot be a valid starting point.
            if (current_tank_balance < 0) {
                // We must try starting from the next station, i+1.
                start_station_candidate = i + 1;
                // Reset the current tank balance to 0, as we are effectively
                // "restarting" our journey from the new 'start_station_candidate' with an empty tank.
                current_tank_balance = 0;
            }
        }
        
        // After iterating through all stations:
        // If total_gas_balance is non-negative, it means there's enough gas overall
        // to complete the circuit. The 'start_station_candidate' found by the greedy approach
        // will be the unique valid starting point.
        // If total_gas_balance is negative, it's impossible to complete the circuit.
        return total_gas_balance >= 0 ? start_station_candidate : -1;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | The algorithm iterates through the `gas` and `cost` arrays exactly once, performing constant time operations in each step. |
| **Space** | O(1) | The algorithm uses a fixed number of variables (`current_tank_balance`, `start_station_candidate`, `total_gas_balance`) regardless of the input size `N`. |

## 🔗 Related Problems
- 53. Maximum Subarray (Kadane's Algorithm - similar idea of tracking a running sum and resetting)
- 121. Best Time to Buy and Sell Stock (Greedy approach, tracking minimums/maximums)
- 135. Candy (Greedy approach, two-pass array traversal)