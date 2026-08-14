# LeetCode 1547 — Minimum Cost to Cut a Stick

## 1. Core Concept

This problem asks us to make all given cuts on a stick while minimizing the total cost.

The important observation is:

> **The cost of a cut depends on the length of the current stick segment on which that cut is performed.**

Therefore, the order in which we perform the cuts matters.

A cut that is cheap if performed late may be expensive if performed early because the segment is still large.

---

## 2. Why a Simple Greedy Approach Is Not Enough

A natural first thought is:

> Make the middle cut first so that the stick is divided into approximately equal parts.

This is a reasonable heuristic because balanced segments may reduce future costs.

However, it is **not guaranteed to be optimal**.

The issue is that minimizing the size of the resulting pieces does not necessarily minimize the total cost across **all future cuts**.

### General lesson

When a choice looks locally good:

> **Ask whether you can prove that the choice is always part of an optimal solution.**

If you cannot prove that, consider whether the problem requires exploring multiple choices.

---

# 3. Recognizing Interval DP

After making a cut inside a stick segment:

```text
left boundary ---- cut ---- right boundary
```

the original problem splits into two independent subproblems:

```text
[left boundary, cut]
[cut, right boundary]
```

This is the key signal for **Interval DP**.

### Interval DP pattern

When a problem repeatedly asks:

> What is the optimal answer for a range `[l, r]`?

and choosing some position `k` divides that range into:

```text
[l, k]
[k, r]
```

you should strongly consider **Interval DP**.

---

# 4. State Definition

First, sort the cut positions and add the two stick boundaries:

```text
0, sorted cuts, n
```

Let this array be `a`.

Define:

> `dp[l][r]` = minimum cost required to perform all cuts whose positions lie strictly between `a[l]` and `a[r]`.

### Important distinction

`l` and `r` are **indices in the augmented cuts array**, not physical positions.

The physical boundaries are:

```text
a[l] and a[r]
```

This distinction prevents a very common implementation mistake.

---

# 5. Why We Add the Boundaries

Adding:

```text
0
```

and:

```text
n
```

makes every subproblem represent a complete stick segment.

Instead of thinking about arbitrary physical segments, we can always describe a segment using two indices:

```text
a[l] ---------------- a[r]
```

Every possible cut inside it is represented by some index `k` satisfying:

```text
l < k < r
```

This removes the need to repeatedly search for which cuts belong to a segment.

---

# 6. Recurrence Idea

Suppose we are solving interval `[l, r]`.

Choose some cut `k` inside it to be the **first cut performed**.

That first cut costs the length of the current stick:

```text
a[r] - a[l]
```

After performing it, two independent problems remain:

```text
dp[l][k]
dp[k][r]
```

Therefore:

> **Current interval cost = cost of first cut + optimal left subproblem + optimal right subproblem.**

The recurrence is:

[
dp[l][r]
========

\min_{l<k<r}
\left(
dp[l][k]
+
dp[k][r]
+
a[r]-a[l]
\right)
]

The `min` exists because **every possible first cut must be considered**.

---

# 7. Why Does Choosing `k` as the First Cut Work?

This is the most important reasoning point.

For any interval `[l,r]`, some cut must eventually be performed first.

Suppose that first cut is `k`.

Once `k` is performed:

```text
[l, r]
```

becomes:

```text
[l, k]     [k, r]
```

The future decisions on the left do not affect the right, and vice versa.

Therefore, we can independently use the optimal solutions for both subintervals.

This is the **optimal substructure** that makes DP possible.

---

# 8. Base Case

If two boundaries are adjacent in the augmented array:

```text
a[l] and a[l+1]
```

there is no cut between them.

Therefore:

[
dp[l][l+1] = 0
]

This is an important base case.

### Why it matters with `INF`

For minimization DP, unknown states are commonly initialized with a large value such as:

```text
INF
```

But genuine zero-cost states must still be explicitly initialized.

Otherwise the smallest intervals would incorrectly remain `INF`.

---

# 9. Bottom-Up Order

The subproblems:

```text
dp[l][k]
dp[k][r]
```

are always smaller than:

```text
dp[l][r]
```

because:

```text
l < k < r
```

Therefore, we can calculate intervals in increasing order of interval size.

Conceptually:

```text
small intervals
      ↓
larger intervals
      ↓
even larger intervals
      ↓
entire stick
```

This guarantees that when calculating an interval, all of its required smaller intervals have already been solved.

---

# 10. The Three-Level Iteration

The bottom-up approach naturally has three dimensions of iteration:

### 1. Interval length

Determines how large the current subproblem is.

### 2. Left boundary

Determines which interval of that size we are processing.

### 3. First cut

Try every possible cut inside the current interval.

Conceptually:

```text
interval size
    ↓
all intervals of that size
    ↓
all possible first cuts
```

This is the standard structure of many interval-DP problems.

---

# 11. Complexity

Let:

[
m = \text{number of cuts}
]

There are:

* `O(m²)` possible intervals.
* Up to `O(m)` possible first cuts for each interval.

Therefore:

[
\boxed{O(m^3)}
]

time complexity.

The DP table contains:

[
O(m^2)
]

states.

Therefore:

[
\boxed{O(m^2)}
]

space complexity.

### Important

The complexity depends on the **number of cuts**, not the physical stick length `n`.

That distinction is useful whenever the coordinate range can be very large but the number of important positions is small.

---

# 12. Important Implementation Insight — Index vs Position

This problem has two different notions of location.

### DP index

```text
l, k, r
```

These refer to indices in the augmented array.

### Physical position

```text
a[l], a[k], a[r]
```

These refer to actual locations on the stick.

The DP state uses:

```text
dp[l][r]
```

while the cutting cost uses:

```text
a[r] - a[l]
```

### Mental rule

> **Use indices for identifying subproblems; use positions for calculating physical costs.**

This is one of the biggest traps in this problem.

---

# 13. Why We Don't Store the Cutting Order

An initial approach might try something like:

> `dp[cut][order]`

or track which cuts have already been performed.

That leads toward representing different permutations of cutting orders.

But the complete history is unnecessary.

Once we know:

```text
current interval = [l,r]
```

the future problem is completely determined.

We don't care how we arrived there.

This is a fundamental DP principle:

> **Do not store history if the current state already contains all information required to determine the future.**

---

# 14. Common Mistakes

### Mistake 1 — Assuming the middle cut is always optimal

Balanced segments are a useful intuition, but they do not establish a greedy proof.

**Lesson:** A plausible local choice isn't necessarily globally optimal.

---

### Mistake 2 — Using physical positions as DP indices

Incorrect conceptual mixing:

```text
dp[a[l]][a[r]]
```

when the state was defined using indices.

Instead:

```text
dp[l][r]
```

and use:

```text
a[r] - a[l]
```

for the physical length.

---

### Mistake 3 — Initializing every state to `0`

For minimization:

```text
min(0, positive answer)
```

will always remain `0`.

So unknown states should be initialized to a sufficiently large value.

---

### Mistake 4 — Forgetting the adjacent-interval base case

After using `INF`, remember:

```text
dp[l][l+1] = 0
```

because there are no cuts inside such an interval.

---

### Mistake 5 — Using `INT_MAX` carelessly

If an `INF` state can participate in arithmetic such as:

```text
INF + INF
```

it can overflow.

A practical competitive-programming technique is to use a sufficiently large finite value such as:

```text
1e9
```

when the true answer is guaranteed to be much smaller.

---

### Mistake 6 — Using `n` for interval-DP length

The physical stick length `n` is not the same as the number of indices in the augmented cuts array.

The interval iteration should be based on:

```text
number of cuts + 2
```

not the physical coordinate range.

---

# 15. How to Detect This Pattern in Future Problems

When reading a new problem, ask:

### Question 1

> Is the answer about a continuous range `[l,r]`?

If yes, interval DP may be relevant.

### Question 2

> Does choosing some position `k` split the problem into `[l,k]` and `[k,r]`?

Strong interval-DP signal.

### Question 3

> Does the cost of choosing `k` depend on the current interval?

If yes, this often appears in cutting, merging, matrix-chain, partitioning, and similar problems.

### Question 4

> Can I solve the left and right intervals independently after choosing `k`?

If yes, optimal substructure is likely present.

### Question 5

> Can I describe the entire future using only `[l,r]`?

If yes, you've probably found the correct state.

---

# 16. The Bigger Interval-DP Template

A very useful mental template is:

[
dp[l][r]
========

\text{best answer for interval }[l,r]
]

Then:

[
dp[l][r]
========

\operatorname{opt}_{k}
\left(
dp[l][k]
+
dp[k][r]
+
\text{cost of choosing }k
\right)
]

The exact meaning of `cost` and whether you use `min` or `max` changes from problem to problem.

But the structure is extremely reusable.

---

# 17. Key Takeaways

* **Sorting** gives an ordered set of relevant positions.
* Adding `0` and `n` makes the boundaries explicit.
* The problem has **optimal substructure** after choosing the first cut.
* `dp[l][r]` represents the optimal solution for one interval.
* Try every possible `k` as the first cut.
* The first cut costs the **current interval length**.
* Subproblems are smaller intervals.
* Therefore, bottom-up computation by interval length works.
* Adjacent boundaries have cost `0`.
* Use **DP indices** for states and **physical positions** for costs.
* Complexity is **O(m³) time and O(m²) space**, where `m = cuts.size()`.
* The deeper pattern is: **choose a partition point → solve the two resulting intervals optimally**.

### The most important mental model

> **Don't think about the sequence of cuts. Think about the current interval and ask which cut should be performed first inside that interval.**

That shift is basically the entire trick behind this problem.
