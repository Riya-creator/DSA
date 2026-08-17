# Bermuda Rectangle (Union of Rectangles & Prefix Range Queries)

**Problem Link:** [[Insert Problem Link Here](https://codeforces.com/contest/2257/problem/D#)]()

---

## 📌 Problem Statement

The Beaver is exploring the mysterious "Bermuda Rectangle".
* You are given an integer area $S$.
* A Bermuda Rectangle is defined as any rectangle with:
  1. Its bottom-left corner placed at the origin $(0, 0)$.
  2. Integer side lengths $w$ (width) and $h$ (height).
  3. Total area $w \times h = S$.
* A cell $(a, b)$ is considered to be within the Bermuda Rectangle if there exists **at least one** valid Bermuda Rectangle that covers it (i.e., $a \in [0, w]$ and $b \in [0, h]$).
* You are given $q$ independent queries. Each query consists of two integers $(x, y)$, defining a query bounding box $[0, x] \times [0, y]$ anchored at $(0, 0)$.

**Goal:** For each query $(x, y)$, find the total number of $1 \times 1$ cells located in the intersection between the query rectangle $[0, x] \times [0, y]$ and the union of all possible Bermuda Rectangles of area $S$.

---

## 🔍 Conceptual Breakdown & Geometric Intuition

### 1. The Union of Rectangles (The "Blue Staircase")
Because $w \times h = S$ with integer side lengths, the width $w$ must be a **positive divisor** of $S$, and the corresponding height is $h = \frac{S}{w}$.

If we sort all $k$ divisors of $S$ in ascending order:
$$d_1 < d_2 < \dots < d_k \quad (\text{where } d_1 = 1 \text{ and } d_k = S)$$

Each divisor $d_i$ defines a rectangle of dimension $d_i \times \frac{S}{d_i}$. 
* As the width $d_i$ increases, the height $h_i = \frac{S}{d_i}$ strictly decreases.
* Superimposing all these rectangles from the origin forms a **monotonically decreasing staircase profile**.

### 2. Discretizing into Step Blocks
The staircase can be divided into $k$ non-overlapping vertical rectangular slices (steps):
* **Step $i$ X-range:** From $x = d_{i-1}$ to $x = d_i$ (width $= d_i - d_{i-1}$, with $d_0 = 0$).
* **Step $i$ Height:** $h_i = \frac{S}{d_i}$.
* **Step $i$ Area:** $\text{Area}_i = (d_i - d_{i-1}) \times h_i$.

---

## ⚙️ Query Resolution Logic: $O(\log k)$ per Query

For any query $(x, y)$, the effective overlap height at any column along the X-axis is:
$$\text{Overlap Height}(x') = \min(\text{Staircase Height}(x'), y)$$

This partitions the problem into two distinct horizontal zones:

### Zone A: Capped Region ($h_i \ge y$)
* The staircase is taller than or equal to the query height $y$.
* This condition is equivalent to $\frac{S}{d_i} \ge y \iff d_i \le \lfloor \frac{S}{y} \rfloor$.
* Let $j$ be the largest index such that $d_j \le \lfloor \frac{S}{y} \rfloor$ (located via binary search / `std::upper_bound`).
* Across the interval $x' \in [0, \min(x, d_j)]$, every column is capped at height $y$.
* **Area of Zone A:**
  $$\text{Area}_A = \min(x, d_j) \times y$$
*(If $x \le d_j$, the entire query box is contained within this capped region, giving an immediate answer of $x \times y$.)*

### Zone B: Uncapped Region ($h_i < y$)
* For $x' > d_j$, the staircase height is already strictly less than $y$, so the query ceiling $y$ has no clamping effect. The overlap is simply the true staircase area.
* Locate the step $m$ where the query right boundary $x$ lands ($d_{m-1} < x \le d_m$) using binary search (`std::lower_bound`).
* **1. Full Intermediate Steps:** All complete steps from index $j+1$ to $m-1$ are computed in $O(1)$ using a **Prefix Sum Array** of the step areas:
  $$\text{Full Steps Area} = \text{pref}[m-1] - \text{pref}[j]$$
* **2. Final Partial Step:** The remaining slice of the $m$-th step up to width $x$:
  $$\text{Partial Step Area} = (x - d_{m-1}) \times h_m$$

---

## 🧮 Final Combined Formula

$$\text{Total Intersecting Area} = (d_j \times y) + (\text{pref}[m-1] - \text{pref}[j]) + ((x - d_{m-1}) \times h_m)$$

---

## ⏱️ Complexity Analysis

* **Divisor Factorization & Precomputation:** $O(\sqrt{S} + k \log k)$, where $k = d(S)$ is the number of divisors of $S$ (for $S \le 10^{14}$, $k \le 6720$).
* **Per Query Time:** $O(\log k)$ using binary search to find indices $j$ and $m$.
* **Overall Time Complexity:** $O(\sqrt{S} + q \log k)$, which runs well under the standard time limit for $q \le 3 \cdot 10^5$.
* **Space Complexity:** $O(k)$ to store the divisor array and prefix sum array.

---

## 💡 Key Takeaways & Pro-Tips

1. **Union of Hyperbolic Rectangles:** Any problem asking for the union of rectangles with constant product $w \cdot h = S$ reduces to the divisors of $S$ forming a monotonically decreasing step-function.
2. **Clamping via Binary Search:** Whenever a query imposes a ceiling $\min(h(x), y)$, determine the threshold point where $h(x) = y$ using binary search rather than processing column by column.
3. **Prefix Sums for Geometric Steps:** Summing rectilinear areas across discrete interval steps with prefix sums turns an $O(k)$ summation into an instantaneous $O(1)$ range lookup.
