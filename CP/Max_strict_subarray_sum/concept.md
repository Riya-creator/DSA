# Codeforces 1285B: Just Eat It! — Intuition & Solution Guide

---

## 1. Problem Understanding

There are $n$ cupcakes arranged in a row with tastiness values $a_1, a_2, \dots, a_n$ (values can be positive, zero, or negative).

- **Yasser's Choice:** Forced to take **all $n$ cupcakes** (entire array from index $1$ to $n$).
  $$\text{Yasser's Score} = \sum_{i=1}^n a_i$$
- **Adel's Choice:** Can choose **any non-empty contiguous segment** $[l, r]$ ($1 \le l \le r \le n$), with one restriction: **Adel cannot take the entire array** (i.e., $[1, n]$ is forbidden).
- **Goal:** Determine if Yasser's tastiness is **strictly greater** than Adel's maximum possible tastiness.
  - If $\text{Yasser's Score} > \text{Adel's Max Score} \implies$ Output **`YES`**
  - If $\text{Adel's Max Score} \ge \text{Yasser's Score} \implies$ Output **`NO`**

---

## 2. Core Intuition: How to Think About the Problem

### The Trap of "Negative Numbers Mean NO"
A common initial thought is that any negative number allows Adel to skip it and beat Yasser. However, skipping a negative number only helps Adel if the remaining segment's sum is large enough to exceed or match the full array sum. 

### What Does Adel Actually Gain by Skipping Elements?
Since Adel cannot choose the whole array, Adel must leave out at least one cupcake from the row. This means Adel must choose to skip:
1. A **non-empty prefix** of cupcakes, leaving a suffix $[l, n]$ where $l > 1$.
2. A **non-empty suffix** of cupcakes, leaving a prefix $[1, r]$ where $r < n$.
3. Both a prefix and a suffix, leaving an internal segment $[l, r]$.

Consider what happens when Adel skips a prefix $a_1, a_2, \dots, a_{k}$:
$$\text{Remaining Suffix Sum} = \text{Total Sum} - \sum_{i=1}^k a_i$$

- If the skipped prefix sum $\sum_{i=1}^k a_i \le 0$, then:
  $$\text{Remaining Suffix Sum} \ge \text{Total Sum}$$
  Adel immediately ties or beats Yasser!

- Similarly, if any suffix sum drops $\le 0$, skipping that suffix leaves a prefix whose sum is $\ge \text{Total Sum}$.

---

## 3. Two Equivalent Algorithmic Approaches

### Approach 1: Prefix & Suffix Validation (Simplest & Most Direct)

**Logic:**
Yasser wins if and only if **no prefix sum and no suffix sum (excluding the entire array) is $\le 0$**.

**Step-by-Step Thought Process:**
1. Maintain a running sum from left to right for indices $1$ to $n-1$. If at any point the running sum drops $\le 0$, Adel can simply omit this prefix to get a remaining score $\ge \text{Total Sum}$. Hence, return `NO`.
2. Maintain a running sum from right to left for indices $n$ down to $2$. If at any point the running sum drops $\le 0$, Adel can omit this suffix to get a remaining score $\ge \text{Total Sum}$. Hence, return `NO`.
3. If all proper prefix sums and proper suffix sums remain strictly positive ($> 0$), then every proper subarray has a sum strictly smaller than the total sum. Hence, return `YES`.

---

### Approach 2: Kadane's Algorithm on Proper Subarrays

**Logic:**
Adel wants to find the maximum contiguous subarray sum, but with the constraint of length $< n$.

**Handling the Length $< n$ Constraint:**
A standard Kadane's algorithm considers the full range $[1, n]$, which might pick the entire array when all numbers are positive. To prevent Kadane from selecting the entire array:
- Run Kadane on the range excluding the last element: indices $[1, n-1]$.
- Run Kadane on the range excluding the first element: indices $[2, n]$.

Every valid proper subsegment that Adel can legally choose is entirely contained within at least one of these two ranges.

**Decision:**
- Calculate $\text{Adel's Best} = \max(\text{Kadane}([1, n-1]), \text{Kadane}([2, n]))$.
- If $\text{Total Sum} > \text{Adel's Best} \implies$ **`YES`**
- If $\text{Adel's Best} \ge \text{Total Sum} \implies$ **`NO`**

---

## 4. Implementation Steps

1. Read $n$ and store the array of size $n$ using 64-bit integers (`long long` in C++) to prevent integer overflow.
2. Compute the total sum of the array.
3. Apply either:
   - **Running Sum Check:** Two single loops (one forward from $1$ to $n-1$, one backward from $n$ down to $2$) checking for any value $\le 0$.
   - **Kadane's Runs:** Run maximum subarray sum on $[0, n-2]$ and $[1, n-1]$, then compare the max with total sum.
4. Print `YES` or `NO` accordingly.

---

## 5. Complexity Breakdown

- **Time Complexity:** $\mathcal{O}(N)$ per testcase — requiring only 1 to 2 linear passes over the array.
- **Space Complexity:** $\mathcal{O}(N)$ or $\mathcal{O}(1)$ auxiliary memory.
