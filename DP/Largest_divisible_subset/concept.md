# LeetCode 368 — Largest Divisible Subset

## 1. Problem Idea

Given an array of distinct positive integers, find the largest subset such that for every pair of elements:

* `a % b == 0`, or
* `b % a == 0`

The order of the elements in the original array does not matter.

---

## 2. Key Observation

The important trick is to **sort the array** first.

For example:

`[1, 2, 4, 8]`

After sorting, if:

`nums[i] % nums[j] == 0`

for `j < i`, then `nums[j] <= nums[i]`, so `nums[j]` can be placed before `nums[i]`.

Therefore, instead of checking every pair inside every possible subset, we can build the answer incrementally.

---

## 3. DP State

Define:

`dp[i] = length of the largest divisible subset ending at nums[i]`

Initially:

`dp[i] = 1`

because every individual element forms a valid subset.

For every previous element `j < i`:

```text
if nums[i] % nums[j] == 0
```

then `nums[i]` can extend the subset ending at `nums[j]`.

So:

```text
dp[i] = max(dp[i], dp[j] + 1)
```

---

## 4. Why Sorting Is Important

Suppose:

`nums = [1, 2, 4, 8]`

After sorting:

```text
1 → 2 → 4 → 8
```

Now we only need to check whether the larger number is divisible by the smaller number.

Without sorting, we would have to worry about both directions:

```text
a % b == 0
b % a == 0
```

Sorting reduces this to:

```text
larger % smaller == 0
```

This is the main observation that makes the DP clean.

---

## 5. Reconstructing the Answer

Knowing only the maximum length isn't enough.

We also need to know:

> Which previous element produced the best DP state?

For this, maintain:

`parent[i] = previous index used to construct the best subset ending at i`

Whenever we update:

```text
dp[i] = dp[j] + 1
```

we also store:

```text
parent[i] = j
```

Then keep track of the index having the largest `dp`.

Starting from that index, repeatedly follow `parent`:

```text
last → parent[last] → parent[parent[last]] → ...
```

This reconstructs the subset backwards.

Finally, reverse it.

---

## 6. Example

Consider:

```text
[1, 2, 3, 4, 8]
```

After sorting:

```text
1  2  3  4  8
```

DP can become:

```text
nums:    1  2  3  4  8
dp:      1  2  1  3  4
parent: -1  0 -1  1  3
```

For `8`:

```text
8 % 4 == 0
```

so it can extend the subset ending at `4`.

And:

```text
4 % 2 == 0
2 % 1 == 0
```

Therefore:

```text
1 → 2 → 4 → 8
```

is the largest divisible subset.

---

## 7. Complexity

### Time

Sorting:

```text
O(n log n)
```

DP:

```text
O(n²)
```

Reconstruction:

```text
O(n)
```

Overall:

```text
O(n²)
```

because `O(n²)` dominates `O(n log n)`.

### Space

```text
dp      → O(n)
parent  → O(n)
answer  → O(n)
```

Overall:

```text
O(n)
```

---

## 8. Is There a More Optimized Solution?

For the standard/general version of this problem, **O(n²) is the expected optimal practical solution**.

There are alternative approaches based on:

* Enumerating divisors
* Prime factorization
* Hash maps
* Number-theoretic properties

But they depend heavily on the **value range of the numbers**, not just `n`.

They also don't provide a generally better worst-case complexity for arbitrary input.

So for an interview/OA:

> **Sorted + DP + Parent Reconstruction = the solution to go with.**

Don't over-engineer this one.

---

## 9. Important Pattern to Remember

This problem is basically:

```text
Sort
  ↓
Define DP ending at each element
  ↓
Check previous compatible elements
  ↓
Store parent for reconstruction
  ↓
Find maximum DP
  ↓
Backtrack using parent
```

This is closely related to **Longest Increasing Subsequence (LIS)**.

The difference is the compatibility condition:

### LIS

```text
nums[j] < nums[i]
```

### Largest Divisible Subset

```text
nums[i] % nums[j] == 0
```

The DP structure is almost the same.

---

## 10. Interview Insight

When you see:

* "largest subset"
* "longest sequence"
* "ending at an element"
* Some relation between two elements
* Need to reconstruct the actual sequence

Think:

```text
Sort → DP[i] = best ending at i → parent[i]
```

The **parent array** is especially important whenever the question asks for the actual subset/sequence rather than only its length.

---

## 11. Optimization Check

Your code:

```text
Sorting              O(n log n)
Nested DP loop       O(n²)
Parent reconstruction O(n)
```

Therefore:

```text
Time  = O(n²)
Space = O(n)
```

So yes — **your current solution is already the one you should submit.**

The bigger optimization here isn't finding a magical `O(n log n)` solution. It's recognizing the **LIS-style DP pattern quickly** and not wasting time trying to force a more complicated approach.
