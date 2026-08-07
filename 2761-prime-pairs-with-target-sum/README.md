# 2761-prime-pairs-with-target-sum

## 📋 Problem Description
You are given an integer `n`. The goal is to find all unique pairs of integers `(x, y)` that satisfy the following conditions:
1.  `1 <= x <= y <= n`
2.  `x + y == n`
3.  Both `x` and `y` are prime numbers.

The function should return a 2D list of these prime number pairs `[x_i, y_i]`. The list must be sorted in increasing order of `x_i`. If no such prime number pairs exist, an empty array should be returned. A prime number is defined as a natural number greater than 1 that has only two factors: 1 and itself.

## 🔍 Examples
```
Input: n = 10
Output: [[3,7],[5,5]]
Explanation: For n=10, the prime pairs that sum to 10 are [3,7] and [5,5]. Both 3, 7, and 5 are prime numbers. The pairs are returned sorted by their first element.

Input: n = 2
Output: []
Explanation: For n=2, there are no prime number pairs (x,y) such that x+y=2 and x,y are prime, because the smallest prime is 2, and x<=y implies x+y >= 4.

Input: n = 4
Output: [[2,2]]
Explanation: For n=4, the only prime pair that sums to 4 is [2,2]. Both 2 and 2 are prime numbers.
```

## 📌 Constraints
*   `1 <= n <= 10^6`

## 🤔 Understanding the Problem
The problem asks us to decompose a given integer `n` into a sum of two prime numbers, `x` and `y`. We need to find all such unique pairs, ensuring that `x` is less than or equal to `y`, and then present them in a sorted list based on `x`. The core challenge lies in efficiently identifying prime numbers up to `n` and then quickly checking if a complement `(n - x)` is also prime. Edge cases like `n` being very small (e.g., 2 or 3) where no pairs can exist also need to be handled.

## 💡 Core Idea
The most efficient way to find all prime numbers up to a given limit `n` is to use the Sieve of Eratosthenes. Once we have pre-computed all primes, we can iterate through them and for each prime `x`, quickly check if `n - x` is also a prime number using a hash map for O(1) average time lookups.

## 🧠 Approach — Sieve of Eratosthenes + Hash Map Lookup
This problem is best solved by combining the **Sieve of Eratosthenes** for prime generation with a **Hash Map** for efficient lookups.
The Sieve of Eratosthenes is an optimal algorithm for finding all prime numbers up to a specified integer `n`. Since we need to check primality for both `x` and `n-x`, pre-calculating all primes up to `n` is crucial to avoid redundant computations. A hash map (like `unordered_map` in C++) allows us to store these primes and perform O(1) average time lookups to quickly determine if `n-x` is also prime. This two-step approach is significantly faster than checking primality for each number individually, which would be too slow for `n` up to `10^6`.

## 📝 Step-by-Step Algorithm
1.  **Handle Edge Cases**: If the input `n` is less than or equal to 2, it's impossible to form a prime pair (since the smallest prime is 2, and `x <= y` implies `x+y >= 4`). In this case, return an empty list immediately.
2.  **Initialize Sieve**: Create a boolean array, `isPrime`, of size `n`. Initialize all entries to `true`. This array will be used to mark numbers as prime or not prime. `isPrime[i]` will be `true` if `i` is prime, and `false` otherwise.
3.  **Populate Primes using Sieve**:
    *   Iterate with a variable `i` from `2` up to `n-1`.
    *   If `isPrime[i]` is `true` (meaning `i` is currently considered prime):
        *   Add `i` to a hash map (e.g., `unordered_map<int, int> mp`). The key will be the prime number `i`. The value can be anything, as we only care about the existence of the key.
        *   Mark all multiples of `i` as not prime: Iterate with `j` starting from `i * 2` up to `n-1`, incrementing `j` by `i` in each step. For each `j`, set `isPrime[j] = false`. This eliminates all non-prime multiples.
4.  **Find Prime Pairs**:
    *   Initialize an empty 2D vector, `ans`, to store the resulting prime pairs.
    *   Iterate through the prime numbers stored as keys in the hash map (`mp`). Let the current prime be `first`.
    *   Calculate the potential second number: `second = n - first`.
    *   **Check Conditions for a Valid Pair**:
        *   Verify that `second` is greater than or equal to `first` (`second >= first`). This ensures that `x <= y` as required by the problem and prevents adding duplicate pairs (e.g., if `[3,7]` is added, we don't want to add `[7,3]`).
        *   Check if `second` is also a prime number by looking it up in the hash map (`mp.count(second)`).
    *   If both conditions are met, add the pair `[first, second]` to the `ans` list.
5.  **Sort Result**: After checking all possible `first` primes, sort the `ans` list. The default `std::sort` for a vector of vectors will sort based on the first element of each inner vector, which satisfies the problem's requirement for sorting by `x_i`.
6.  **Return**: Return the `ans` list.

## 💻 Solution
```cpp
class Solution {
public:
    vector<vector<int>> findPrimePairs(int n) {
        // A boolean array to mark prime numbers using Sieve of Eratosthenes.
        // isPrime[i] will be true if i is prime, false otherwise.
        // We need to check primality up to n-1, so a size of n is sufficient.
        vector<bool> isPrime(n, true);

        // Handle edge cases where n is too small to form any prime pairs.
        // The smallest prime number is 2. For x + y = n with x, y >= 2,
        // the minimum sum is 2 + 2 = 4.
        // If n is 1 or 2, no prime pairs can be formed.
        if (n <= 2) {
            return {};
        }

        // Store prime numbers found by the Sieve in a hash map for O(1) average time lookups.
        // The value (int) associated with the key (prime number) doesn't strictly matter here;
        // we only care about the existence of the key.
        unordered_map<int, int> mp;
        int count = 0; // A simple counter, not strictly needed for the logic but present in original code.

        // Step 1: Sieve of Eratosthenes to find all primes up to n-1.
        // We start from i = 2, as 0 and 1 are not prime numbers.
        for (int i = 2; i < n; i++) {
            if (isPrime[i]) {
                // If 'i' is prime, add it to our map of primes.
                mp.insert({i, count});
                count++; // Increment count (can be removed without affecting correctness).

                // Mark all multiples of 'i' as not prime.
                // We start from i * 2 because 'i' itself is prime.
                // Multiples less than i * 2 would have already been marked by smaller primes.
                for (int j = i * 2; j < n; j = j + i) {
                    isPrime[j] = false;
                }
            }
        }

        // Step 2: Extract prime pairs.
        vector<vector<int>> ans;
        // Iterate through the prime numbers we found (stored as keys in 'mp').
        // 'entry.first' represents our 'x' candidate.
        for (auto const& entry : mp) {
            int first = entry.first; 
            int second = n - first;  // Calculate the 'y' candidate such that first + second = n.

            // Check two crucial conditions for a valid pair:
            // 1. second >= first: This ensures that x <= y as required by the problem statement.
            //    It also prevents adding duplicate pairs (e.g., if [3,7] is found, we don't
            //    want to later add [7,3] when 'first' becomes 7).
            // 2. mp.count(second): This efficiently checks if 'second' is also a prime number
            //    by looking it up in our hash map of pre-computed primes.
            if (second >= first && mp.count(second)) {
                ans.push_back({first, second});
            }
        }

        // Step 3: Sort the resulting pairs.
        // The problem requires the list to be sorted in increasing order of x_i.
        // std::sort on a vector of vectors will by default sort based on the first element
        // of each inner vector. If first elements are equal, it then compares second elements.
        // (In this problem, due to 'second >= first', first elements will not be equal for distinct pairs).
        sort(ans.begin(), ans.end());

        return ans;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N log log N + P log P) | The Sieve of Eratosthenes takes O(N log log N) time to find all primes up to `N`. Iterating through the primes (at most `N/log N` primes) and performing hash map lookups takes O(N) in the worst case (if `N` is prime, we iterate `N` times, but lookups are O(1) on average). Sorting the `P` resulting pairs takes O(P log P) time, where `P` is the number of prime pairs. Since `P` can be at most `N/2`, this is at most O(N log N). For `N = 10^6`, the Sieve dominates the overall time complexity. |
| **Space** | O(N) | The `isPrime` boolean vector requires O(N) space. The `mp` hash map stores all prime numbers up to `N`, which by the Prime Number Theorem is approximately `N / log N` primes. This also contributes O(N) space in the worst case. |

## 🔗 Related Problems
- 204. Count Primes
- 1. Two Sum
- 167. Two Sum II - Input Array Is Sorted