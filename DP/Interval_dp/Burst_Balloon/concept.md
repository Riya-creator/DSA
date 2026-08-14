# Burst Balloons — LeetCode 312

## 1. Problem Pattern

**Pattern:** Interval DP

**Core idea:**
Instead of deciding **which balloon to burst first**, decide:

> **Which balloon is going to be burst LAST inside an interval?**

This change in perspective is the main trick of the problem.

---

## 2. Why Is This Problem Difficult?

For:

```text
[3, 1, 5, 8]
```

If we burst `5`:

```text
3 1 [5] 8
```

we get:

```text
1 × 5 × 8 = 40
```

But after bursting some other balloons first, `5` can have completely different neighbors.

So the coins earned by a balloon depend on **what has already been removed**.

### The problem with thinking forward

If we ask:

> "Which balloon should I burst first?"

the future neighbors keep changing.

This makes the state difficult to define.

### The trick

Ask:

> **"Which balloon should be burst LAST?"**

If `k` is the last balloon in an interval, then everything else inside that interval has already disappeared.

Therefore, when `k` is finally burst, its neighbors are fixed: the two boundaries of the interval.

---

# 3. Add Virtual Boundaries

Given:

```text
[3, 1, 5, 8]
```

add `1` on both sides:

```text
[1, 3, 1, 5, 8, 1]
```

The virtual `1`s are never burst.

They simply represent the outside boundaries.

---

# 4. DP State

Define:

```cpp
dp[l][r]
```

as:

> Maximum coins obtained by bursting **all balloons strictly between `l` and `r`**.

So:

```text
l                       r
↓                       ↓
1   3   1   5   8   1
    ^^^^^^^^^^^^^^^
    balloons to burst
```

Important:

```text
l and r are NOT burst.
```

Only balloons satisfying:

```text
l < k < r
```

can be chosen as the last balloon.

---

# 5. The Most Important Concept

Suppose:

```text
l       k       r
↓       ↓       ↓
1  ... 5  ...   1
```

and we decide that `k` is the **LAST** balloon to burst.

Before bursting `k`:

* Everything between `l` and `k` has disappeared.
* Everything between `k` and `r` has disappeared.
* Therefore, `k` is now directly between `l` and `r`.

So the coins obtained from `k` are:

```text
a[l] × a[k] × a[r]
```

The two sides can be solved independently:

```text
dp[l][k] + dp[k][r]
```

Therefore:

```text
dp[l][r] =
    max(
        dp[l][k]
        + dp[k][r]
        + a[l] * a[k] * a[r]
    )
```

for every:

```text
l < k < r
```

---

# 6. Why "LAST" Is the Detection Technique

Whenever you see a problem where:

* Removing an element changes its neighbors.
* The operation's cost depends on neighboring elements.
* The order of operations matters.
* You need the maximum/minimum result.
* The elements form a contiguous interval.

Think:

> **Can I decide the LAST operation instead of the FIRST operation?**

This often converts a messy sequence problem into **Interval DP**.

### Recognition pattern

```text
Changing neighbors
        ↓
Order matters
        ↓
Try LAST operation
        ↓
Interval splits into LEFT + RIGHT
        ↓
Interval DP
```

This is the key pattern to remember.

---

---

# 8. Understanding the Three DP Components

This line:

```cpp
dp[l][k] + dp[k][r] + a[l] * a[k] * a[r]
```

should become automatic.

### Part 1

```cpp
dp[l][k]
```

Solve everything on the **left** of `k`.

### Part 2

```cpp
dp[k][r]
```

Solve everything on the **right** of `k`.

### Part 3

```cpp
a[l] * a[k] * a[r]
```

Finally burst `k`.

Visual:

```text
          k = LAST
            ↓
[ LEFT ]    K    [ RIGHT ]
    ↓              ↓
 solved          solved

            ↓

       burst K
```

---

# 9. Why Do We Process Small Intervals First?

Suppose we're calculating:

```cpp
dp[l][r]
```

and choose `k`.

We need:

```cpp
dp[l][k]
dp[k][r]
```

These are smaller intervals.

Therefore, they must already be calculated.

Dependency:

```text
Small intervals
      ↓
Medium intervals
      ↓
Large intervals
      ↓
Entire array
```

That's why we use:

```cpp
for (int len = 2; len < n + 2; len++)
```

---

# 10. Why `len = 2`?

Remember:

```text
dp[l][r]
```

contains balloons **strictly between** `l` and `r`.

If:

```text
r = l + 1
```

then:

```text
l   r
↓   ↓
1   1
```

There is nothing between them.

So:

```cpp
dp[l][r] = 0;
```

No balloon exists to burst.

The first useful interval is:

```text
r = l + 2
```

which contains exactly one balloon.

---

# 11. Tiny Example

Consider:

```text
[3]
```

After adding boundaries:

```text
[1, 3, 1]
```

We calculate:

```text
dp[0][2]
```

Only possible `k`:

```text
k = 1
```

So:

```text
dp[0][2]
=
dp[0][1]
+
dp[1][2]
+
1 × 3 × 1
```

Both smaller intervals contain nothing:

```text
0 + 0 + 3
```

Answer:

```text
3
```

---

# 12. Why `l`, `k`, `r` Are Different

Always maintain:

```text
l < k < r
```

Think of:

```text
l       k       r
↓       ↓       ↓
|  ...  |  ...  |
boundary last  boundary
```

Therefore:

```cpp
for (int k = l + 1; k < r; k++)
```

### `l`

Left boundary.

### `r`

Right boundary.

### `k`

Balloon chosen as the **last balloon**.

They are not interchangeable.

---

# 13. Common Mistake

### ❌ Wrong thinking

```text
dp[i][j] = maximum coins from bursting balloons i...j
```

This makes the recurrence confusing because the boundaries change.

### ✅ Better definition

```text
dp[l][r] =
maximum coins from bursting balloons
STRICTLY between l and r
```

This gives us fixed boundaries.

---

# 14. Common Wrong Approach: Greedy

You might try:

> Burst the balloon with the largest value first.

Wrong.

Or:

> Burst the balloon giving the maximum coins right now.

Also wrong.

For example:

```text
3 1 5 8
```

Bursting the locally best balloon can destroy a future opportunity to get a larger multiplication.

The optimal answer depends on the **entire order**, not the current best move.

Therefore this is not a greedy problem.

---

# 15. Common Mistake: Thinking About FIRST

If you try:

```text
Which balloon do I burst first?
```

then after bursting it:

```text
neighbors change
        ↓
next choice changes
        ↓
state becomes messy
```

Instead:

```text
Which balloon do I burst LAST?
        ↓
its neighbors are fixed
        ↓
left and right become independent
        ↓
easy recurrence
```

---

# 16. Complexity

There are approximately:

```text
O(n²)
```

intervals.

For each interval, we try:

```text
O(n)
```

possible last balloons.

Therefore:

```text
Time = O(n³)
```

The DP table contains:

```text
O(n²)
```

states.

Therefore:

```text
Space = O(n²)
```

### Final

```text
Time  : O(n³)
Space : O(n²)
```

---

# 17. Interview Explanation

A clean explanation:

> "Since bursting a balloon changes its neighbors, choosing the first balloon makes the state difficult to define. I instead consider the balloon that is burst last in each interval. Once that balloon is chosen, everything to its left and right has already been removed, so its neighbors are fixed as the interval boundaries. This splits the problem into two independent subproblems, giving an interval DP."

That's a very solid interview explanation.

---

# 18. How to Detect Interval DP in Future Problems

Look for these clues:

### Clue 1 — Contiguous range

Something like:

```text
[l ... r]
```

### Clue 2 — Operations happen inside the range

Examples:

* Burst
* Remove
* Merge
* Split
* Cut
* Combine
* Parenthesize

### Clue 3 — Order matters

Doing operation A before B gives a different result than B before A.

### Clue 4 — Choosing the LAST operation makes boundaries fixed

This is the strongest clue.

### Clue 5 — Choosing `k` splits the interval

If:

```text
[l ........ r]
```

becomes:

```text
[l ... k] + [k ... r]
```

you should immediately think:

> **Interval DP.**

---

# 19. Similar Problems / Pattern Family

Once Burst Balloons clicks, look at these concepts:

```text
Matrix Chain Multiplication
       ↓
Interval DP

Burst Balloons
       ↓
Interval DP

Minimum Cost to Cut a Stick
       ↓
Interval DP

Palindrome Partitioning
       ↓
Interval / Partition DP

Boolean Parenthesization
       ↓
Interval DP
```

The exact recurrence changes, but the **"choose a partition point / last operation"** mindset is reusable.

---

# 20. Quick Cheat Sheet

```text
Problem:
Burst Balloons

Pattern:
Interval DP

Main trick:
Choose LAST balloon

State:
dp[l][r]

Meaning:
Maximum coins by bursting everything
strictly between l and r

Transition:
for every k where l < k < r:

dp[l][r] =
max(
    dp[l][k]
    + dp[k][r]
    + a[l] * a[k] * a[r]
)

Boundary:
Add 1 at both ends

Loop:
Small intervals → large intervals

Time:
O(n³)

Space:
O(n²)
```

## 🔥 One-line memory trick

> **"Neighbors are dynamic when I think FIRST, but fixed when I think LAST."**

That's the core insight behind LC 312.
