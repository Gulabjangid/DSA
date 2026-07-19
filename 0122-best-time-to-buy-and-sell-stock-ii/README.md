# 0122-best-time-to-buy-and-sell-stock-ii

## 📋 Problem Description
You are given an array of integers called `prices`, where `prices[i]` represents the price of a given stock on the `i`-th day.

Your goal is to find and return the maximum total profit you can achieve.

You are allowed to perform multiple transactions. On any given day, you can decide to buy, sell, or do nothing. However, there are two important rules:
1. You can only hold at most one share of the stock at any time. This means you must sell any stock you currently hold before you can buy another one.
2. You can sell and buy the stock multiple times on the same day. This implies that if you sell a stock, you are immediately free to buy another one on the very same day if it's profitable.

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
Total profit is 4.
(Alternatively, you could buy on day 1, sell on day 2 (profit 1); buy on day 2, sell on day 3 (profit 1); etc. The sum of these individual profits would also be 4.)
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
This problem asks us to maximize profit by buying and selling a stock, with the key difference from "Best Time to Buy and Sell Stock I" being that we can perform *multiple* transactions. The constraint of holding "at most one share" means we must sell before we can buy again. The ability to sell and buy on the same day simplifies things, essentially meaning a transaction pair (buy then sell) can be completed instantly, freeing us up for another. The core challenge is to figure out how to leverage these multiple transactions to get the highest possible total profit.

## 💡 Core Idea
Since we can make as many transactions as we want, we can capture every single price increase. If the stock price goes up from one day to the next, we can "buy" on the lower-priced day and "sell" on the higher-priced day to make a profit.

## 🧠 Approach — Greedy
The algorithm used here is a **Greedy** approach.
This pattern fits because the ability to make unlimited transactions means that any positive profit, no matter how small or short-lived, can be added to our total profit without negatively impacting future opportunities. If the price increases from day `i-1` to day `i`, we can always make `prices[i] - prices[i-1]` profit. This local optimal choice (taking every immediate profit) contributes directly to the global optimal solution because a larger upward trend (e.g., `A < B < C`) can be broken down into smaller, consecutive upward trends (`(B-A) + (C-B)`), yielding the same total profit as a single transaction (`C-A`).

## 📝 Step-by-Step Algorithm
1.  Initialize a variable `totalProfit` to `0`. This variable will store the accumulated maximum profit.
2.  Iterate through the `prices` array starting from the second day (index `1`) up to the last day. We need to compare each day's price with the previous day's price.
3.  For each day `i` (from `1` to `prices.size() - 1`):
    a.  Compare the current day's price (`prices[i]`) with the previous day's price (`prices[i-1]`).
    b.  If `prices[i]` is strictly greater than `prices[i-1]`, it means there was an increase in price. We can imagine buying on day `i-1` and selling on day `i` to capture this profit.
    c.  Add this positive difference (`prices[i] - prices[i-1]`) to `totalProfit`.
4.  After the loop finishes, `totalProfit` will contain the maximum profit achievable by summing up all positive price differences.
5.  Return `totalProfit`.

## 💻 Solution
```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // Initialize total profit to 0. This variable will accumulate all positive profits
        // obtained from individual buy-sell transactions.
        int profit = 0;

        // Iterate through the prices array starting from the second day (index 1).
        // We compare each day's price with the previous day's price to identify upward trends.
        for (int i = 1; i < prices.size(); i++) {
            // If the current day's price (prices[i]) is higher than the previous day's price (prices[i-1]),
            // it means there's an opportunity to make a profit.
            // We can conceptually "buy" on day i-1 and "sell" on day i.
            if (prices[i] > prices[i-1]) {
                // Add this positive difference (profit) to our total profit.
                // This greedy strategy works because we can perform unlimited transactions;
                // any upward movement contributes to the maximum total profit.
                profit += prices[i] - prices[i-1];
            }
        }
        // After iterating through all consecutive days, 'profit' will hold the maximum total profit
        // achievable by summing all positive price differences.
        return profit;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N) | We iterate through the `prices` array exactly once, where N is the number of days. |
| **Space** | O(1) | We only use a single integer variable (`profit`) to store the accumulated profit, regardless of the input size. |

## 🔗 Related Problems
- 121. Best Time to Buy and Sell Stock
- 123. Best Time to Buy and Sell Stock III
- 188. Best Time to Buy and Sell Stock IV
- 309. Best Time to Buy and Sell Stock with Cooldown
- 714. Best Time to Buy and Sell Stock with Transaction Fee