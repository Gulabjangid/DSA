# 0204-count-primes

## 📋 Problem Description
Given an integer `n`, the task is to determine and return the count of all prime numbers that are strictly less than `n`.

A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself.

## 🔍 Examples
```
Input: n = 10
Output: 4
Explanation: The prime numbers strictly less than 10 are 2, 3, 5, and 7. There are 4 such numbers.

Input: n = 0
Output: 0
Explanation: There are no prime numbers less than 0.

Input: n = 1
Output: 0
Explanation: There are no prime numbers less than 1.
```

## 📌 Constraints
*   `0 <= n <= 5 * 10^6`

## 🤔 Understanding the Problem
The problem asks us to count all prime numbers up to a given limit `n` (exclusive). A prime number is a positive integer greater than 1 that has no positive integer divisors other than 1 and itself. Numbers like 0, 1, and negative integers are not prime. The challenge lies in efficiently checking primality for a potentially large range of numbers, up to `5 * 10^6`. A naive approach of checking each number for primality using trial division would be too slow. We need a more optimized method to find all primes within the given range.

## 💡 Core Idea
Instead of individually testing each number for primality, we can use an efficient method to *eliminate* composite numbers. The key insight is that every composite number has a prime factor less than or equal to its square root. By iteratively marking multiples of prime numbers as composite, we can quickly identify all primes up to `n`.

## 🧠 Approach — Sieve of Eratosthenes
This problem is a classic application of the **Sieve of Eratosthenes** algorithm. This pattern is specifically designed for finding all prime numbers up to a given limit `n`. It works by maintaining a boolean array (or similar data structure) where each index `i` corresponds to the number `i`. Initially, all numbers are assumed to be prime. The algorithm then iteratively finds the next unmarked number (which must be prime) and marks all its multiples as composite (not prime). This process avoids redundant checks and is significantly faster than checking each number for primality individually, making it highly efficient for finding all primes within a range.

## 📝 Step-by-Step Algorithm
1.  **Initialize Primality Array:** Create a boolean array, let's call it `isprime`, of size `n+1`. Initialize all entries from index 0 to `n` as `true`, assuming all numbers are initially prime.
2.  **Handle Base Cases:** Numbers 0 and 1 are not prime. While the algorithm's main loop starts from 2, it's good to remember these aren't counted. For `n <= 2`, the count of primes will be 0.
3.  **Initialize Count:** Set a counter variable, `count`, to 0. This will store the total number of primes found.
4.  **Iterate Through Numbers:** Start a loop from `i = 2` up to `n-1` (since we need primes *strictly less than* `n`).
5.  **Check for Primality:** Inside the loop, if `isprime[i]` is `true`, it means `i` has not been marked as composite by any smaller prime. Therefore, `i` is a prime number.
    *   Increment `count`.
    *   **Mark Multiples:** Since `i` is prime, all its multiples (i.e., `2*i`, `3*i`, `4*i`, and so on) cannot be prime. Start another inner loop from `j = i*2` and increment `j` by `i` in each step (i.e., `j = j + i`). For each such `j` that is less than `n`, set `isprime[j]` to `false`. This efficiently marks all multiples of `i` as composite.
6.  **Return Count:** After the outer loop finishes, `count` will hold the total number of prime numbers strictly less than `n`. Return `count`.

## 💻 Solution
```cpp
class Solution {
public:
    int countPrimes(int n) {
        // Handle edge cases where n is 0, 1, or 2.
        // No primes are strictly less than or equal to 2.
        if (n <= 2) {
            return 0;
        }

        // Create a boolean vector 'isprime' of size 'n'.
        // Initialize all entries to 'true', assuming all numbers are prime initially.
        // We only care about numbers up to n-1, so size n is sufficient.
        // isprime[i] will be true if i is prime, false otherwise.
        // Note: The problem asks for primes strictly less than n, so we check up to n-1.
        // The vector size n means indices 0 to n-1 are valid.
        std::vector<bool> isprime(n, true);

        // Initialize a counter for prime numbers.
        int count = 0;

        // The Sieve of Eratosthenes algorithm starts checking from 2.
        // Numbers 0 and 1 are not prime, so we don't need to process them.
        for (int i = 2; i < n; ++i) {
            // If isprime[i] is true, it means 'i' has not been marked as composite yet.
            // Therefore, 'i' is a prime number.
            if (isprime[i]) {
                // Increment the prime count.
                count++;

                // Mark all multiples of 'i' as not prime.
                // We start marking from i*2 because i*1 is 'i' itself (which is prime).
                // Any multiple k*i where k < i would have already been marked by a smaller prime factor.
                // For example, for i=2, we mark 4, 6, 8...
                // For i=3, we mark 6, 9, 12... (6 is already marked by 2, which is fine)
                // The loop continues as long as j is less than n.
                for (long long j = (long long)i * i; j < n; j += i) {
                    // Optimization: We can start marking multiples from i*i.
                    // Any multiple k*i where k < i would have already been marked
                    // by a prime factor smaller than i (or by k itself if k is prime).
                    // For example, for i=5, we start marking from 25.
                    // Multiples like 10, 15, 20 would have already been marked by 2 or 3.
                    isprime[j] = false;
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
| **Time** | O(N log log N) | The Sieve of Eratosthenes algorithm has a time complexity of approximately N multiplied by the natural logarithm of the natural logarithm of N. This is highly efficient for finding all primes up to N. |
| **Space** | O(N) | We use a boolean vector of size `N` to store the primality status for each number up to `N-1`. |

## 🔗 Related Problems
- 263. Ugly Number
- 264. Ugly Number II
- 172. Factorial Trailing Zeroes