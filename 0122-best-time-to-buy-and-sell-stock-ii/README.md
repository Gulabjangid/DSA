# 0122-best-time-to-buy-and-sell-stock-ii

## 📋 Problem Description
You are given an array of integers `prices`, where `prices[i]` represents the price of a given stock on the `i`-th day.

Your goal is to find and return the maximum profit you can achieve. You are allowed to perform multiple transactions. On any given day, you may decide to buy and/or sell the stock. However, you can only hold at most one share of the stock at any time. This means you must sell any stock you hold before buying another. You can even sell and buy on the same day if it's profitable, as long as you never hold more than one share simultaneously.

## 🔍 Examples
```
Input: prices = [7,1,5,3,6,4]
Output: 7
Explanation: 
Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5 - 1 = 4.
Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6 - 3 = 3.
Total profit is 4 + 3 = 7.
```

```
Input: prices = [1,2,3,4,5]
Output: 4
Explanation: 
Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5 - 1 = 4.
Total profit is 4. (Note: This is equivalent to summing up (2-1) + (3-2) + (4-3) + (5-4) = 1+1+1+1 = 4)
```

```
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: There is no way to make a positive profit, so we never buy the stock to achieve the maximum profit of 0.
```

## 📌 Constraints
*   `1 <= prices.length <= 3 * 10^4`
*   `0 <= prices[i] <= 10^4`

## 🤔 Understanding the Problem
The problem asks us to find the maximum profit by buying and selling a stock multiple times. The key rule is that we can only hold one share at a time, meaning we must sell before buying again. Crucially, there are no limits on the number of transactions, and no transaction fees. This implies that we can complete a transaction (buy and sell) and immediately start another one on the very next day, or even on the same day if the price allows. The goal is to maximize the *total* accumulated profit from all transactions.

## 💡 Core Idea
The core insight is that since we can perform as many transactions as we want without fees, we should capture every single positive price increase. If the price goes up from one day to the next, we can make a profit by buying on the lower-priced day and selling on the higher-priced day.

## 🧠 Approach — Greedy Algorithm
This problem can be efficiently solved using a **Greedy Algorithm**.
The greedy approach works here because each local optimal decision (taking an immediate profit from a price increase) contributes directly to the global optimal solution. Since there are no transaction limits or fees, we don't need to "save" a stock for a potentially larger future profit if there's a dip in between. We can simply sell, take the profit, and then buy again later if the price rises. Summing up all positive differences between consecutive days' prices will yield the maximum total profit.

## 📝 Step-by-Step Algorithm
1.  Initialize a variable `totalProfit` to `0`. This variable will store the maximum profit accumulated from all transactions.
2.  Iterate through the `prices` array starting from the second day (index `1`) up to the last day. We need to compare each day's price with the previous day's price.
3.  For each day `i` (where `i` ranges from `1` to `prices.size() - 1`):
    a.  Compare `prices[i]` (current day's price) with `prices[i-1]` (previous day's price).
    b.  If `prices[i]` is strictly greater than `prices[i-1]`, it means there's an opportunity to make a profit by buying on day `i-1` and selling on day `i`.
    c.  In this case, add the difference `prices[i] - prices[i-1]` to `totalProfit`.
4.  After the loop finishes, `totalProfit` will contain the maximum profit achievable by summing up all positive price increments.
5.  Return `totalProfit`.

## 💻 Solution
```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // Initialize total profit to 0. This variable will accumulate all positive profits.
        int profit = 0;

        // Iterate through the prices array starting from the second day (index 1).
        // We compare each day's price with the previous day's price.
        // The loop runs from i = 1 up to prices.size() - 1.
        for (int i = 1; i < prices.size(); ++i) {
            // If the current day's price (prices[i]) is higher than the previous day's price (prices[i-1]),
            // it means there's an opportunity to make a profit.
            // Since we can perform multiple transactions and there are no transaction fees,
            // we can capture every such positive price difference.
            if (prices[i] > prices[i-1]) {
                // Add this immediate profit (prices[i] - prices[i-1]) to our total profit.
                // This greedy approach works because any upward trend can be broken down
                // into a sum of consecutive daily increases. For example, if prices go from 1 to 5,
                // then 3, then 6:
                // [1, 5, 3, 6]
                // Day 1 (price 1) -> Day 2 (price 5): profit += (5 - 1) = 4.
                // Day 2 (price 5) -> Day 3 (price 3): prices[i] is not > prices[i-1], so no profit added.
                // Day 3 (price 3) -> Day 4 (price 6): profit += (6 - 3) = 3.
                // Total profit = 4 + 3 = 7.
                // This is equivalent to buying at 1 and selling at 5, then buying at 3 and selling at 6.
                profit += prices[i] - prices[i-1];
            }
        }
        // Return the accumulated maximum profit.
        return profit;
    }
};

```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the `prices` array once, performing a constant number of operations for each element. `N` is the number of days (length of the `prices` array). |
| **Space** | O(1) | We only use a single integer variable (`profit`) to store the accumulated profit, regardless of the input array size. No additional data structures are allocated. |

## 🔗 Related Problems
- 121. Best Time to Buy and Sell Stock
- 123. Best Time to Buy and Sell Stock III
- 188. Best Time to Buy and Sell Stock IV
- 309. Best Time to Buy and Sell Stock with Cooldown
- 714. Best Time to Buy and Sell Stock with Transaction Fee