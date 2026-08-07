# 2761-prime-pairs-with-target-sum

## 📋 Problem Description
You are given an integer `n`. The goal is to find all unique pairs of prime numbers `[x, y]` that satisfy three conditions:
1.  `1 <= x <= y <= n` (both `x` and `y` must be within the range `[1, n]`, and `x` must be less than or equal to `y`).
2.  `x + y == n` (their sum must equal the given `n`).
3.  `x` and `y` are prime numbers.

A prime number is defined as a natural number greater than `1` that has only two distinct positive divisors: `1` and itself.

The function should return a 2D list (or vector) of these prime number pairs. The list must be sorted in increasing order based on the value of `x_i`. If no such prime number pairs exist, an empty list should be returned.

## 🔍 Examples
```
Input: n = 10
Output: [[3,7],[5,5]]
Explanation: For n=10, the prime pairs are [3,7] (3+7=10) and [5,5] (5+5=10). Both 3, 5, and 7 are prime. The pairs are sorted by their first element.

Input: n = 2
Output: []
Explanation: There are no prime numbers x, y such that x+y=2 and x,y >= 2. The smallest prime is 2, so 2+2=4 is the smallest possible sum of two primes.

Input: n = 4
Output: [[2,2]]
Explanation: For n=4, the only prime pair is [2,2] (2+2=4). 2 is a prime number.
```

## 📌 Constraints
*   `1 <= n <= 10^6`

## 🤔 Understanding the Problem
The problem asks us to decompose a given integer `n` into a sum of two prime numbers, `x` and `y`, with the additional constraint that `x` must be less than or equal to `y`. The primary challenge lies in efficiently identifying prime numbers up to `n` and then quickly checking if `n-x` is also prime for various `x`. A naive approach of checking primality for each number would be too slow given `n` up to `10^6`. We also need to handle edge cases like `n` being very small (e.g., `n=2`, `n=3`) where no such pairs might exist.

## 💡 Core Idea
The core idea is to first pre-compute all prime numbers up to `n` using an efficient algorithm like the Sieve of Eratosthenes. Once we have a quick way to check if any number up to `n` is prime, we can iterate through possible values for `x` (which must be prime) and check if `n-x` is also prime.

## 🧠 Approach — Sieve of Eratosthenes + Hash Map for Efficient Lookup
This problem is best solved by combining two common algorithmic patterns:
1.  **Sieve of Eratosthenes**: This algorithm is highly efficient for finding all prime numbers up to a specified limit `N`. Instead of individually testing each number for primality (which takes `O(sqrt(N))` time per test), the Sieve can identify all primes up to `N` in `O(N log log N)` time. This is crucial because `n` can be as large as `10^6`.
2.  **Hash Map (or Hash Set)**: After generating all primes using the Sieve, storing them in a hash map (or hash set) allows for `O(1)` average-time lookup. This is essential for the second phase of the algorithm, where we iterate through potential `x` values and need to quickly verify if `n-x` is also a prime number.

By pre-calculating primes, we avoid redundant primality tests, making the overall solution efficient enough for the given constraints.

## 📝 Step-by-Step Algorithm

1.  **Handle Edge Cases**: If `n` is less than or equal to `2`, it's impossible to form a sum of two primes (smallest prime is 2, so smallest sum is 2+2=4). In this case, return an empty list immediately.

2.  **Initialize Sieve**:
    *   Create a boolean vector `isPrime` of size `n`, initialized to `true`. `isPrime[i]` will be `true` if `i` is prime, and `false` otherwise.
    *   Mark `isPrime[0]` and `isPrime[1]` as `false` since 0 and 1 are not prime numbers.

3.  **Run Sieve of Eratosthenes**:
    *   Iterate `i` from `2` up to `sqrt(n-1)` (or `n-1` if `n` is small, but `sqrt(n)` is more optimized).
    *   If `isPrime[i]` is `true` (meaning `i` is a prime number):
        *   Mark all multiples of `i` (starting from `i * 2` or `i * i` for optimization) up to `n-1` as `false` in the `isPrime` array. For example, `j = i*2, i*3, i*4, ...` up to `n-1`.

4.  **Store Primes for Quick Lookup**:
    *   Create an `unordered_map<int, int>` (or `unordered_set<int>`) called `mp`.
    *   Iterate `i` from `2` up to `n-1`.
    *   If `isPrime[i]` is `true`, insert `i` into `mp`. The value associated with the key in the map doesn't strictly matter for primality checking; `mp.count(key)` is what we'll use.

5.  **Find Prime Pairs**:
    *   Initialize an empty 2D vector `ans` to store the resulting prime pairs.
    *   Iterate through the `mp` (which contains all primes found). For each prime `x` (the key in `mp`):
        *   Calculate the potential second number `y = n - x`.
        *   Check two conditions:
            *   `y` must be greater than or equal to `x` (`y >= x`). This ensures that we only add each pair once (e.g., `[3,7]` but not `[7,3]`) and that `x` is the smaller element as required.
            *   `y` must also be a prime number. Check this efficiently using the hash map: `mp.count(y)`.
        *   If both conditions are met, add the pair `[x, y]` to the `ans` vector.

6.  **Sort Results**: After checking all possible `x` values, sort the `ans` vector. The problem requires the list to be sorted in increasing order of `x_i`. Since we iterated through primes `x` in increasing order and added pairs, the `ans` vector will likely be mostly sorted, but a final `sort` call ensures strict adherence to the requirement.

7.  **Return `ans`**: Return the `ans` vector containing all valid prime pairs.

## 💻 Solution

```cpp
class Solution {
public:
    vector<vector<int>> findPrimePairs(int n) {
        // Handle edge cases where n is too small to form a sum of two primes.
        // The smallest prime is 2, so the smallest sum of two primes is 2+2=4.
        if (n <= 3) { // n=1, 2, 3 cannot form prime pairs
            return {};
        }

        // Step 1 & 2: Initialize and run Sieve of Eratosthenes
        // Create a boolean array to mark primality up to n.
        // isPrime[i] will be true if i is prime, false otherwise.
        // We need to check numbers up to n-1, so size n is sufficient for indices 0 to n-1.
        vector<bool> isPrime(n, true); 
        isPrime[0] = false; // 0 is not prime
        isPrime[1] = false; // 1 is not prime

        // Sieve of Eratosthenes: Mark non-prime numbers.
        // We only need to iterate up to sqrt(n) for the outer loop.
        // However, iterating up to n-1 is also correct, just slightly less optimized
        // for the outer loop condition (but inner loop optimization is more critical).
        for (int i = 2; i < n; i++) {
            if (isPrime[i]) {
                // If i is prime, mark all its multiples as non-prime.
                // Start marking from i*2 (or i*i for further optimization,
                // but i*2 is simpler and sufficient for this problem's constraints).
                for (long long j = (long long)i * 2; j < n; j += i) {
                    isPrime[j] = false;
                }
            }
        }

        // Step 3: Store Primes for Quick Lookup
        // Using an unordered_map (or unordered_set) for O(1) average-time lookup.
        // The value 'count' is not strictly necessary for the logic, just the key.
        unordered_map<int, int> mp;
        int count = 0; // This variable is not used in the final logic for finding pairs
        for (int i = 2; i < n; i++) {
            if (isPrime[i]) {
                mp.insert({i, count}); // Store prime numbers in the map
                count++; // Increment count (not used later)
            }
        }

        // Step 4: Extracting the pairs
        vector<vector<int>> ans;
        // Iterate through the primes found (keys in the map).
        // 'it.first' represents 'x'.
        for (auto it : mp) {
            int first = it.first;
            int second = n - first; // Calculate 'y' such that first + second = n

            // Check conditions:
            // 1. second >= first: Ensures x <= y and avoids duplicate pairs like [7,3] if [3,7] is already added.
            // 2. mp.count(second): Checks if 'second' is also a prime number using the hash map.
            if (second >= first && mp.count(second)) {
                ans.push_back({first, second});
            }
        }

        // Step 5: Sort the resulting pairs.
        // The problem requires the list to be sorted in increasing order of x_i.
        // Although iterating through mp might give somewhat sorted x,
        // an explicit sort ensures the final output is strictly ordered.
        sort(ans.begin(), ans.end());
        
        return ans;
    }
};

```

## ⏱️ Complexity Analysis

| | Complexity | Reason |
|---|---|---|
| **Time** | O(N log log N) | The Sieve of Eratosthenes dominates the time complexity, taking `O(N log log N)` to find all primes up to `N`. Populating the hash map and iterating through primes to find pairs takes `O(N)` on average. Sorting the final `k` pairs takes `O(k log k)`, where `k` is the number of prime pairs (at most `N/2`). `O(N log log N)` is the highest order term. |
| **Space** | O(N) | We use a boolean vector `isPrime` of size `N` and an `unordered_map` to store primes, which can store up to `N` elements in the worst case (though practically `π(N)` primes, where `π(N) ≈ N/ln N`). The `ans` vector can also store up to `N/2` pairs. All these contribute `O(N)` space. |

## 🔗 Related Problems
*   204. Count Primes
*   1175. Prime Arrangements
*   1. Two Sum (Conceptual similarity in finding pairs that sum to a target, but with primality constraint)