# 0204-count-primes

## 📋 Problem Description
Given an integer `n`, the task is to determine and return the total count of prime numbers that are strictly less than `n`. A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself.

The function `countPrimes` receives one integer `n` as input and must return an integer representing the number of primes less than `n`.

## 🔍 Examples
```
Input: n = 10
Output: 4
Explanation: The prime numbers strictly less than 10 are 2, 3, 5, and 7. There are 4 such numbers.
```

```
Input: n = 0
Output: 0
Explanation: There are no prime numbers less than 0.
```

```
Input: n = 1
Output: 0
Explanation: There are no prime numbers less than 1.
```

## 📌 Constraints
*   `0 <= n <= 5 * 10^6`

## 🤔 Understanding the Problem
The problem asks us to count all prime numbers within a specific range, from 2 up to `n-1`. A key challenge is that `n` can be quite large (up to 5 million), which means a naive approach of checking each number for primality individually would be too slow. We need an efficient method to identify all primes up to a given limit. Edge cases like `n=0` or `n=1` should correctly yield 0 primes, as prime numbers are defined as being greater than 1.

## 💡 Core Idea
The most efficient algorithm for finding all prime numbers up to a specified limit is the **Sieve of Eratosthenes**. This method works by iteratively marking the multiples of each prime number as composite (not prime), thereby leaving only the prime numbers unmarked.

## 🧠 Approach — Sieve of Eratosthenes
This problem is a classic application of the **Sieve of Eratosthenes** algorithm. This pattern is ideal when you need to find *all* prime numbers up to a certain limit, rather than just checking the primality of a single number. It fits this specific problem perfectly because we need to count all primes up to `n-1`. The Sieve works by starting with an assumption that all numbers are prime, and then systematically eliminating the multiples of known prime numbers. This approach avoids redundant calculations by marking all multiples of a prime in one go, making it significantly faster than performing individual primality tests for each number.

## 📝 Step-by-Step Algorithm
1.  **Handle Edge Cases**: If `n` is 0, 1, or 2, there are no primes strictly less than `n`. In these cases, immediately return 0.
2.  **Initialization**: Create a boolean array (or vector in C++), let's call it `isprime`, of size `n`. Initialize all entries from index 0 up to `n-1` to `true`. This array will keep track of whether a number is considered prime (`true`) or composite (`false`).
3.  **Prime Count**: Initialize an integer variable `count` to 0. This variable will store the total number of prime numbers found.
4.  **Iterate Through Numbers**: Start a loop with a variable `i` from `2` up to `n-1`.
5.  **Check for Primality**: Inside the loop, check if `isprime[i]` is `true`.
    *   If `isprime[i]` is `true`, it means `i` has not been marked as a multiple of any smaller prime. Therefore, `i` itself is a prime number.
    *   Increment `count` by 1.
6.  **Mark Multiples**: Since `i` is a prime number, all of its multiples (e.g., `2*i`, `3*i`, `4*i`, etc.) cannot be prime.
    *   Start an inner loop with a variable `j` from `2*i`.
    *   Continue this inner loop as long as `j` is less than `n`.
    *   In each iteration of the inner loop, set `isprime[j]` to `false` to mark `j` as a composite number.
    *   Increment `j` by `i` in each step (i.e., `j = j + i`) to move to the next multiple.
7.  **Return Result**: After the outer loop completes, the `count` variable will hold the total number of prime numbers strictly less than `n`. Return `count`.

## 💻 Solution
```cpp
class Solution {
public:
    int countPrimes(int n) {
        // Handle edge cases where n is 0, 1, or 2.
        // Prime numbers are strictly greater than 1.
        // If n is 0, 1, or 2, there are no primes strictly less than n.
        if (n <= 2) {
            return 0;
        }

        // Create a boolean vector 'isprime' of size 'n'.
        // Initialize all entries to 'true', assuming all numbers are prime initially.
        // isprime[i] will be true if 'i' is potentially prime, false if it's composite.
        // We only care about numbers up to n-1.
        vector<bool> isprime(n, true);

        // Initialize a counter for prime numbers found.
        int count = 0;

        // Iterate from 2 up to n-1.
        // 'i' represents the current number we are checking for primality.
        for (int i = 2; i < n; i++) {
            // If isprime[i] is true, it means 'i' has not been marked as a multiple
            // of any smaller prime number. Therefore, 'i' itself is a prime number.
            if (isprime[i]) {
                count++; // Increment the prime count.

                // Now, mark all multiples of 'i' as not prime (composite).
                // We start marking from i*2 because smaller multiples (like i*1, which is 'i' itself)
                // have already been handled or are the current prime 'i'.
                // Using 'long long' for 'j' is a good practice to prevent potential overflow
                // if 'i * 2' or 'i * i' (in an optimized Sieve) were to exceed INT_MAX,
                // although for 'i * 2' with n up to 5*10^6, it fits in int.
                for (long long j = (long long)i * 2; j < n; j += i) {
                    isprime[j] = false; // Mark 'j' as not prime.
                }
            }
        }
        return count; // Return the total count of prime numbers found.
    }
};
```

## ⏱️ Complexity Analysis
| | Complexity | Reason |
|---|---|---|
| **Time** | O(N log log N) | The outer loop runs `N` times. The inner loop marks multiples for each prime `p` approximately `N/p` times. The sum of `N/p` for all primes `p < N` is known to be `N log log N`. |
| **Space** | O(N) | A boolean vector `isprime` of size `N` is used to store primality information for each number up to `N-1`. |

## 🔗 Related Problems
- 263. Ugly Number
- 172. Factorial Trailing Zeroes
- 1025. Divisor Game