LeetCode 204 — Count Primes

Method Used

Sieve of Eratosthenes

---

Problem Pattern

This problem belongs to the Prime Number Precomputation category.

Whenever the question asks to:

- Count all prime numbers less than "n"
- Find every prime within a range
- Answer multiple prime-related queries efficiently
- Work with large values of "n"

the first algorithm that should come to mind is the Sieve of Eratosthenes.

The goal is not to check whether one number is prime, but to efficiently identify all prime numbers up to a limit.

---

Core Concept

Instead of testing every number individually for primality, the Sieve of Eratosthenes works by eliminating numbers that are guaranteed to be composite.

Initially, every number is considered a possible prime.

The algorithm repeatedly selects the next confirmed prime number and marks all of its multiples as composite because a multiple of a prime number can never be prime (except the prime itself).

By the end, the only numbers that remain unmarked are prime numbers.

Think of it as a filtering process rather than a searching process.

---

Why This Algorithm Is Efficient

A common beginner's approach is to check every number separately using trial division.

Although correct, it repeats similar work thousands of times.

The Sieve removes this repetition.

Every composite number is eliminated through one of its smallest prime factors, preventing unnecessary checks later.

This makes it one of the fastest algorithms for generating primes within a range.

---

The Most Important Observation

The algorithm begins marking multiples from the square of the current prime.

Reason:

Every smaller multiple has already been marked while processing a smaller prime factor.

For example, before reaching 7, all multiples such as 14, 21, 28, 35 and 42 have already been removed because they are multiples of 2, 3 or 5.

Therefore, the first multiple that has not been processed yet is 7² = 49.

This observation removes a huge amount of redundant work.

---

Why We Only Process Until √n

Every composite number has at least one factor less than or equal to its square root.

If a composite number had no factor smaller than or equal to √n, both factors would have to be greater than √n, making their product larger than the number itself, which is impossible.

Because of this mathematical property, once every number up to √n has been processed, every composite number has already been eliminated.

---

Thinking Process

When solving problems involving prime numbers, ask yourself these questions:

1. Am I checking a single number or many numbers?
2. Can I eliminate impossible candidates instead of verifying every candidate?
3. Can I preprocess once and answer quickly afterward?

If the answer is "many numbers," Sieve of Eratosthenes is usually the correct direction.

---

Time Complexity

- Time: O(n log log n)
- Space: O(n)

This is significantly faster than checking every number individually.

---

Common Mistakes

- Forgetting that the problem asks for primes less than "n", not less than or equal to "n".
- Treating 0 and 1 as prime numbers.
- Starting to mark multiples too early instead of from the square of the current prime.
- Continuing the outer process beyond √n, which only performs unnecessary work.
- Confusing this algorithm with trial division. They solve the same problem but use completely different approaches.

---

Interview & OA Recognition

If you notice words such as:

- Count primes
- Generate primes
- Prime numbers up to N
- Multiple prime queries
- Range of primes
- Large constraints involving millions of numbers

there is a very high chance that the intended solution is based on the Sieve of Eratosthenes.

---

Real-World Connection

The idea behind the Sieve is preprocessing.

Spend some time once to build useful information, then reuse it repeatedly.

This same philosophy appears in many important algorithms such as prefix sums, dynamic programming tables, hash-based caching, lookup tables, and graph preprocessing.

Understanding the Sieve helps build the habit of recognizing when preprocessing is more efficient than solving the same subproblem repeatedly.

---

Related Concepts to Learn Next

- Segmented Sieve
- Smallest Prime Factor (SPF) Sieve
- Prime Factorization using SPF
- Euler's Linear Sieve
- Modular Arithmetic
- Greatest Common Divisor (GCD) and Least Common Multiple (LCM)

These topics are natural extensions of the Sieve of Eratosthenes and frequently appear in coding interviews and online assessments.

---

Revision Snapshot

- Pattern: Prime number preprocessing
- Method: Sieve of Eratosthenes
- Key Idea: Eliminate multiples instead of checking every number individually.
- Optimization: Begin marking from the square of the current prime.
- Outer Limit: Process only up to √n.
- Best Use Case: Finding or counting many prime numbers efficiently.
- Mindset: Precompute once, answer many times.
