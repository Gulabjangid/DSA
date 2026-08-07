# 0204-count-primes

## 📋 Problem Description
Given a non-negative integer `n`, the task is to determine and return the total count of prime numbers that are strictly less than `n`. A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself.

## 🔍 Examples
```
Input: n = 10
Output: 4
Explanation: The prime numbers strictly less than 10 are 2, 3, 5, and 7.

Input: n = 0
Output: 0

Input: n = 1
Output: 0
```

## 📌 Constraints
*   `0 <= n <= 5 * 10^6`

## 🤔 Understanding the Problem
The problem asks us to count all prime numbers within the range `[0, n-1]`. It's important to remember that 0 and 1 are not considered prime numbers. The number 2 is the first and only even prime number. Given the constraint `n` can be up to `5 * 10^6`, a naive approach of checking each number for primality individually (e.g., by trial division up to its square root) would be too slow, as it would involve `O(N * sqrt(N))` operations. We need a more efficient method to find all primes up to a given limit.

## 💡 Core Idea
The most efficient algorithm for finding all prime numbers up to a specified limit `n` is the **Sieve of Eratosthenes**. This algorithm works by iteratively marking the multiples of each prime number as composite (not prime), thereby leaving only the prime numbers unmarked.

## 🧠 Approach — Sieve of Eratosthenes
This problem is a classic application of the **Sieve of Eratosthenes** algorithm. This pattern is perfectly suited for scenarios where you need to find all prime numbers up to a certain limit `n`, rather than just checking the primality of a single number. The Sieve avoids redundant calculations by efficiently identifying and marking all composite numbers. It starts with the smallest prime (2), marks all its multiples as non-prime, then moves to the next unmarked number (which must be prime), and repeats the process. This systematic elimination ensures that by the end, only prime numbers remain marked as true.

## 📝 Step-by-Step Algorithm
1.  **Initialization**: Create a boolean array, let's call it `isPrime`, of size `n`. Initialize all elements from index 0 to `n-1` to `true`. This array will store whether each number is considered prime (`true`) or not (`false`).
2.  **Handle Edge Cases**: If `n` is 0, 1, or 2, there are no prime numbers strictly less than `n`. In these cases, return 0 immediately.
3.  **Prime Count**: Initialize an integer variable `count` to 0. This variable will keep track of the total number of primes found.
4.  **Iterate and Sieve**: Loop through numbers `i` starting from 2 up to `n-1`.
    a.  **Check Primality**: Inside the loop, if `isPrime[i]` is `true`, it means `i` has not been marked as a multiple of any smaller prime. Therefore, `i` itself must be a prime number.
    b.  **Increment Count**: If `i` is prime, increment `count`.
    c.  **Mark Multiples**: Now that `i` is confirmed as a prime, mark all its multiples (starting from `2*i`) as not prime. Iterate with `j` starting from `2*i` and incrementing by `i` (i.e., `2*i, 3*i, 4*i, ...`) as long as `j` is less than `n`. For each such `j`, set `isPrime[j] = false`.
        *   *Note*: We start marking from `2*i` because `1*i` (which is `i` itself) is prime. An optimization often used is to start marking from `i*i`, because any multiple `k*i` where `k < i` would have already been marked by a smaller prime factor `k`. However, starting from `2*i` is also correct and simpler to implement if `i*i` might overflow or if the performance difference is negligible for the given constraints.
5.  **Return Result**: After the loop completes, `count` will hold the total number of prime numbers strictly less than `n`. Return `count`.

## 💻 Solution
```cpp
class Solution {
public:
    int countPrimes(int n) {
        // Create a boolean array `isPrime` of size `n`.
        // Initialize all elements to `true`, assuming all numbers are prime initially.
        // `isPrime[i]` will be `true` if `i` is prime, `false` otherwise.
        // Indices 0 and 1 will remain true but are not considered in the counting loop.
        vector<bool> isPrime(n, true);

        // Base cases: Numbers less than or equal to 2 have no primes strictly less than them.
        // (0 and 1 are not prime. 2 is prime, but we're looking for primes *less than* n).
        if (n <= 2) {
            return 0;
        }

        // Initialize a counter for prime numbers.
        int count = 0;

        // Iterate from 2 up to n-1. We start from 2 because it's the first prime number.
        // 0 and 1 are not prime and are implicitly handled by starting the loop at 2.
        for (int i = 2; i < n; i++) {
            // If `isPrime[i]` is true, it means `i` has not been marked as a multiple
            // of any smaller prime. Therefore, `i` itself must be a prime number.
            if (isPrime[i]) {
                // Increment the prime count.
                count++;

                // Mark all multiples of `i` as not prime.
                // We start marking from `i * 2` because `i * 1` (which is `i` itself) is prime.
                // The loop condition `j < n` ensures we only mark numbers within our array bounds.
                // `j += i` moves to the next multiple of `i`.
                // For example, if i=2, it marks 4, 6, 8...
                // If i=3, it marks 6, 9, 12... (6 might already be marked by 2, which is harmless).
                // Note: `i * 2` will not overflow an `int` for `n` up to `5 * 10^6`
                // as `2 * 5 * 10^6 = 10^7`, which fits within a 32-bit signed integer.
                for (int j = i * 2; j < n; j += i) {
                    isPrime[j] = false;
                }
            }
        }
        // Return the total count of prime numbers found.
        return count;
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N log log N) | The Sieve of Eratosthenes has a time complexity dominated by the marking process. Each number `i` causes its multiples `i, 2i, 3i, ...` to be visited. The sum of `N/p` for all primes `p < N` is approximately `N log log N`. |
| **Space** | O(N) | We use a boolean vector `isPrime` of size `N` to store the primality status for each number from 0 to `N-1`. |

## 🔗 Related Problems
- 1175. Prime Arrangements
- 263. Ugly Number
- 762. Prime Number of Set Bits