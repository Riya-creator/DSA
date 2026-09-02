# Jumping Through Segments (Codeforces 1907D)

A guide on solving interval-reachability problems using the **Binary Search on the Answer + Interval Propagation** technique.

---

## Problem Overview

* **Problem:** [Codeforces 1907D - Jumping Through Segments](https://codeforces.com/problemset/problem/1907/D)
* **Goal:** Find the minimum non-negative integer jump capacity $k$ such that starting from position $0$, you can land within segment $[l_i, r_i]$ on step $i$ for all $1 \le i \le n$.
* **Move Rule:** From position $x$, you can move to any coordinate $y$ satisfying $\vert{}x - y\vert{} \le k$ (i.e., $x - k \le y \le x + k$).

---

## Why Greedy Fails

A tempting strategy is to greedily pick the closest point in the next segment at each step.

This fails because **a single point cannot capture all future options**. Landing at the closest border point might save distance on the current jump, but it can leave you stranded if subsequent segments require you to be further to the right or left. Instead of tracking an individual point, you must maintain the **entire continuous range of reachable positions**.

---

## Key Observation: Monotonicity

The problem exhibits monotonic behavior with respect to jump size $k$:

* If a jump size $k$ is sufficient to clear all $n$ segments, then any larger jump size $k' > k$ is also sufficient.
* If a jump size $k$ cannot reach a segment, no smaller jump size can either.

This monotonic property enables **Binary Search on the Answer** over the search space $k \in [0, 10^9]$.

---

## Interval Propagation Strategy

For a fixed jump capacity $k$, we determine feasibility by propagating a reachability interval $[L, R]$ across all segments.

### 1. Initialization

Before step 1, you are stationed at the origin:


$$[L, R] = [0, 0]$$

### 2. Step-by-Step Transition

At step $i$, target segment $[l_i, r_i]$ must be reached:

1. **Range Expansion (Jump Step):**
Every reachable point in $[L, R]$ can jump by at most $k$ in either direction. The new potential span expands to:

$$[L_{\text{new}}, R_{\text{new}}] = [\max(0, L - k), R + k]$$



*(Since all segment boundaries are non-negative, coordinates below 0 do not help).*
2. **Range Restriction (Intersection Step):**
The rules require you to land inside $[l_i, r_i]$ at this turn. The valid set of positions is the overlap between the expanded range and the target segment:

$$L = \max(L_{\text{new}}, l_i)$$


$$R = \min(R_{\text{new}}, r_i)$$


3. **Validity Check:**
* If $L \le R$, the overlap is non-empty. Update the interval to $[L, R]$ and proceed to the next step.
* If $L > R$, the overlap is empty. It is impossible to reach segment $i$ using jump capacity $k$. The check fails immediately.



### 3. Conclusion

If all $n$ segments are processed without the interval collapsing ($L > R$), then jump capacity $k$ is valid.

---

## Concrete Example

Consider $k = 5$ on the following sequence:

* Start: $0$
* Segment 1: $[2, 8]$
* Segment 2: $[6, 8]$

| Step | Prior $[L, R]$ | Expanded $[L - k, R + k]$ | Segment $[l_i, r_i]$ | Overlap $[L, R]$ | Status |
| --- | --- | --- | --- | --- | --- |
| **0** | — | — | — | $[0, 0]$ | Initial state |
| **1** | $[0, 0]$ | $[0, 5]$ | $[2, 8]$ | $[\max(0, 2), \min(5, 8)] = [2, 5]$ | Reachable |
| **2** | $[2, 5]$ | $[0, 10]$ | $[6, 8]$ | $[\max(0, 6), \min(10, 8)] = [6, 8]$ | Reachable |

Since the interval remains non-empty across all steps, $k = 5$ is feasible.

---

## Complexity

* **Feasibility Check:** $O(n)$ single-pass interval updates per test.
* **Binary Search Range:** $\log_2(10^9) \approx 30$ iterations.
* **Total Time Complexity:** $O(n \log(\max R))$ per test case, easily fitting well under the typical 2.0-second limit for $n \le 2 \cdot 10^5$.
* **Space Complexity:** $O(n)$ or $O(1)$ auxiliary space if segments are checked as read.
