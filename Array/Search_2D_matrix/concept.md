# Search in a Sorted Matrix — Concept Notes

## Problem Pattern

This problem belongs to the category of **searching in a 2D sorted structure**. The key challenge is not simply searching every cell, but **using the ordering of the matrix to eliminate impossible regions**.

Whenever a matrix is sorted, the first question should never be *"How do I traverse it?"* but rather:

> **"How can I use the sorted property to avoid traversing most of it?"**

---

# Initial Recursive Idea

A natural first approach is to start from the smallest element and recursively move:

* Right
* Down
* Diagonal

The intuition is that every move leads to larger values, so eventually the target should be found if it exists.

While this approach is logically correct, it is computationally expensive.

---

# Why the Recursive Solution Causes TLE

## 1. Multiple Paths Reach the Same Cell

A cell can often be reached through several different paths.

For example, one position may be reached by:

* moving down then right,
* moving right then down,
* or through other combinations.

Without remembering previously visited cells, the same region is explored repeatedly.

This creates an exponential number of recursive calls.

---

## 2. Branching Factor Becomes Too Large

At each cell, the recursion branches into multiple directions.

Although each branch seems reasonable individually, the total number of recursive calls grows extremely fast.

Even relatively small matrices can generate an enormous recursion tree.

This is the primary reason for the Time Limit Exceeded (TLE).

---

# Why Using a Visited Array Helps

A visited array ensures that every cell is explored only once.

Once the algorithm has already explored everything reachable from a particular cell, revisiting that same cell provides no new information.

This removes repeated work and reduces the complexity from exponential to linear in terms of the number of cells.

**Important:**
This is **not Dynamic Programming**.

A DP table stores computed answers.

A visited array only prevents revisiting already explored states.

---

# Why This Still Isn't the Optimal Solution

Although the visited approach avoids repeated work, it still examines many cells that are unnecessary.

The matrix provides much stronger information than simply "sorted."

Both:

* every row is sorted, and
* every column is sorted.

A better solution exploits both properties simultaneously instead of treating the matrix like a graph.

---

# Why Only Two Corners Are Ideal Starting Points

A matrix has four corners.

However, only two of them allow us to eliminate either an entire row or an entire column after every comparison.

These are:

* Top-right
* Bottom-left

---

## Top-Right Corner

At this position:

* Everything to the left is smaller.
* Everything below is larger.

Therefore:

* If the current value is larger than the target, eliminate the entire column.
* If the current value is smaller than the target, eliminate the entire row.

Every comparison immediately discards a complete section of the matrix.

---

## Bottom-Left Corner

This corner provides the exact opposite ordering.

* Everything above is smaller.
* Everything to the right is larger.

Again, every comparison removes an entire row or an entire column.

---

# Why the Other Two Corners Are Poor Choices

## Top-Left

The current element is the smallest among all reachable elements.

If it is smaller than the target, there are two possible directions:

* Right
* Down

Both remain valid.

The comparison cannot determine which direction is correct.

The search therefore splits into multiple possibilities.

---

## Bottom-Right

The current element is the largest.

If it is larger than the target, both:

* Left
* Up

remain possible.

Again, the comparison cannot uniquely determine the next move.

The search branches instead of narrowing.

---

# General Rule

Choose a starting position where:

* one direction always contains larger values, and
* the other direction always contains smaller values.

This guarantees that every comparison eliminates a complete row or a complete column.

If a comparison cannot eliminate a large portion of the search space, it is probably not the ideal starting position.

---

# How to Recognize This Pattern During an Interview

Whenever you notice:

* every row is sorted, **and**
* every column is sorted,

immediately ask:

> "Can one comparison eliminate an entire row or column?"

If the answer is yes, avoid DFS, BFS, or exhaustive recursion.

Instead, search from one of the two useful corners.

---

# General Problem-Solving Guidelines

## Pattern 1 — Sorted Array

Think Binary Search.

Goal:

* Remove half of the search space after every comparison.

---

## Pattern 2 — Sorted Matrix (rows only)

Treat the matrix as a flattened sorted array or locate the candidate row first, then perform binary search.

---

## Pattern 3 — Rows and Columns Both Sorted

Think about eliminating an entire row or an entire column after every comparison.

This is usually more efficient than exploring multiple paths.

---

## Pattern 4 — Recursive Search

Always ask:

* Can different paths reach the same state?

If yes:

* Expect repeated computation.
* Consider memoization or a visited structure.

---

## Pattern 5 — Graph-Like Exploration

Whenever movement is possible in multiple directions, ask:

* Will different paths revisit the same position?

If yes, avoid plain recursion.

---

# Common Mistakes

* Treating a sorted matrix like an ordinary grid.
* Ignoring the sorting property.
* Exploring multiple directions when one comparison can already eliminate an entire region.
* Calling a visited array "DP."
* Using recursion without checking whether states repeat.

---

# Key Takeaways

* A correct solution is not always an efficient solution.
* The strongest property of the input should drive the algorithm.
* Eliminating search space is almost always better than exploring it.
* Before writing recursion, identify whether states overlap.
* Before choosing a starting point, ask what information each comparison provides.
* The best algorithms are often those that **avoid work**, not those that **perform it faster**.
