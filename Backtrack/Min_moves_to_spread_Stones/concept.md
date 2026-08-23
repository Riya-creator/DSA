# Minimum Moves to Spread Stones Over Grid — Conceptual README

## 1. Problem Overview

You are given a `3 × 3` grid containing exactly `9` stones in total.

Each cell should eventually contain **exactly one stone**.

A move consists of:

* Taking one stone from a cell containing more than one stone.
* Moving it to an adjacent cell.
* The cost of that move is `1`.

The goal is to find the **minimum number of moves** required to make every cell contain exactly one stone.

---

# 2. First Important Observation

Don't think about the individual moves immediately.

Instead, look at the grid in terms of:

### Surplus cells

A cell containing more than one stone has **extra stones**.

For a cell containing `x` stones:

> Extra stones = `x - 1`

Example:

```text
4 stones → 3 extra stones
2 stones → 1 extra stone
1 stone  → 0 extra stones
```

### Empty cells

A cell containing `0` stones needs exactly **one stone**.

Therefore the problem can be transformed into:

> Move every extra stone to an empty cell while minimizing the total Manhattan distance.

This is the key conceptual transformation.

---

# 3. Solution 1 — Recursive Backtracking

## Core idea

Your solution directly simulates the process.

The thinking is:

1. Find an empty cell.
2. This cell must eventually receive a stone.
3. Find every cell having more than one stone.
4. Take one extra stone from each possible source.
5. Move that stone directly to the chosen empty cell.
6. Recursively solve the remaining grid.
7. Undo the move.
8. Take the minimum among all possibilities.

---

## Why can we directly use Manhattan distance?

Suppose an extra stone is at:

```text
(r1, c1)
```

and the empty cell is:

```text
(r2, c2)
```

The minimum number of adjacent moves needed is:

[
|r1-r2| + |c1-c2|
]

This is the **Manhattan distance**.

So instead of simulating:

```text
up → right → right → down
```

we can directly calculate its cost.

---

# 4. Why Fixing One Empty Cell Works

Your important insight is:

> Every move should ultimately fill an empty cell.

Once we choose a zero cell, we can ask:

> Which surplus stone should be used to fill this zero?

Try every possible source.

This guarantees that every possible decision is explored.

After filling that zero, there are fewer empty cells remaining, so recursion continues.

---

# 5. Why Backtracking Is Correct

For every empty cell, there may be multiple possible surplus sources.

You explore all of them:

```text
              Empty cell
             /     |      \
          Source A Source B Source C
             |       |        |
          recurse  recurse  recurse
```

Then:

[
answer = \min(all\ possible\ choices)
]

Because every valid way of distributing the stones is considered, the minimum found is the optimal answer.

---

# 6. Time Complexity of Backtracking

The major issue is that the recursion explores many possible states.

At every state you scan the entire `3 × 3` grid to:

* Find an empty cell.
* Find possible surplus sources.

The number of possible states grows exponentially with the number of stones that need to be redistributed.

So conceptually:

> **Time: Exponential in the number of extra stones / reachable states.**

For this particular problem, the grid is fixed at only `3 × 3`, so the search space is small enough to pass comfortably.

This is an important distinction:

### General problem

Backtracking → potentially expensive.

### This specific LeetCode problem

Backtracking → perfectly practical because the state space is tiny.

---

# 7. Space Complexity of Backtracking

The recursion depth is bounded by the number of empty cells.

A `3 × 3` grid can have at most `8` empty cells because there are exactly `9` stones.

Therefore:

> **Space: O(number of empty cells)**

For this problem, that is effectively **O(1)** because the grid size is fixed.

The grid itself is modified in-place, so you don't create another grid for every recursive call.

---

# 8. Solution 2 — Minimum-Cost Matching

Now comes the bigger conceptual optimization.

Instead of thinking:

> "Which move should I make next?"

Think:

> "Which extra stone should ultimately go to which empty cell?"

This completely changes the problem.

---

## Step 1 — Extract extra stones

For every cell:

```text
stones > 1
```

extract:

[
stones - 1
]

extra stones.

For example:

```text
Cell A has 3 stones
```

means:

```text
A → extra stone
A → extra stone
```

because one stone stays there.

---

## Step 2 — Extract empty cells

Every zero cell becomes a destination.

Example:

```text
0 0
```

means:

```text
Destination 1
Destination 2
```

Since the total number of stones is exactly `9`, the number of extra stones must equal the number of empty cells.

---

# 9. Convert the Problem into Matching

Suppose we have:

```text
Extra stones:
A B C

Empty cells:
X Y Z
```

We need to decide:

```text
A → ?
B → ?
C → ?
```

Each assignment has a cost:

[
distance(extra\ stone,\ empty\ cell)
]

So we want:

[
minimum\ total\ distance
]

This is a classic:

> **Minimum-Cost Assignment / Matching Problem**

---

# 10. Why Manhattan Distance Is Still the Cost

For every possible pair:

```text
extra stone → empty cell
```

calculate:

[
|r_1-r_2| + |c_1-c_2|
]

This gives the minimum movement cost for that particular pairing.

Then the problem becomes:

> Find the pairing whose total Manhattan distance is minimum.

---

# 11. Solution 2A — Bitmask DP

Because there are at most **8 empty cells**, the number of destinations is tiny.

That makes bitmask DP a perfect fit.

---

## What does the mask represent?

Suppose there are 4 empty cells:

```text
D0 D1 D2 D3
```

We can represent which destinations have already been used:

```text
0000
```

means:

> Nothing has been assigned.

```text
0101
```

means:

> Destination 0 and destination 2 have been assigned.

The mask is essentially a compact checklist.

---

# 12. DP State

Think of the DP as:

> "I've already assigned some number of extra stones. Which empty destinations have I used, and what is the minimum cost so far?"

For every state:

1. Determine how many destinations are already used.
2. That tells us which extra stone we are currently assigning.
3. Try every unused destination.
4. Calculate the Manhattan distance.
5. Continue.
6. Take the minimum.

---

# 13. Why Bitmask DP Is Better

Your backtracking stores the **entire grid state**.

Bitmask DP stores only:

> Which destinations have already been used.

That's much smaller.

Instead of repeatedly exploring equivalent situations, DP remembers the answer for a state and reuses it.

This is the classic difference between:

### Backtracking

```text
Try → recurse → try again → repeat
```

and:

### Memoized DP

```text
Try → solve state → remember answer
                     ↓
                reuse later
```

---

# 14. Complexity of Bitmask DP

Let:

[
k = number\ of\ empty\ cells
]

Since the grid is `3 × 3`:

[
k \leq 8
]

There are:

[
2^k
]

possible masks.

For each mask, we may try up to `k` destinations.

Therefore:

> **Time: O(k × 2^k)**

and:

> **Space: O(2^k)**

For `k ≤ 8`, this is extremely small.

---

# 15. Solution 3 — Hungarian Algorithm

There is another way to recognize the problem.

Once you've converted:

```text
extra stones → empty cells
```

you have a standard **assignment problem**.

The Hungarian Algorithm solves the general assignment problem efficiently.

Its typical complexity is:

[
O(k^3)
]

where `k` is the number of sources/destinations.

---

# 16. Why We Don't Need Hungarian Algorithm Here

Although Hungarian Algorithm is theoretically more sophisticated, it is **overkill** for this problem.

Remember:

```text
3 × 3 grid
↓
maximum 8 empty cells
↓
maximum 8 extra stones
```

So:

```text
Bitmask DP
O(k × 2^k)
```

is incredibly small.

Using Hungarian Algorithm would introduce more conceptual and implementation complexity without providing any meaningful benefit.

---

# 17. Comparing All Three Approaches

| Approach     | Main Idea                         |         Time |            Space | Verdict  |
| ------------ | --------------------------------- | -----------: | ---------------: | -------- |
| Backtracking | Simulate choices on the grid      |  Exponential | `O(k)` recursion | ✅ Good   |
| Bitmask DP   | Match extras to zeros using masks | `O(k × 2^k)` |         `O(2^k)` | ⭐ Best   |
| Hungarian    | General assignment algorithm      |      `O(k³)` |          `O(k²)` | Overkill |

---

# 18. Which One Should You Prefer?

### For solving this LeetCode problem quickly

Your **backtracking solution is completely valid**.

Because the grid is only `3 × 3`, the state space is tiny.

---

### For a cleaner algorithmic solution

Prefer:

> **Bitmask DP + Manhattan Distance**

It exposes the real structure of the problem instead of simulating the grid.

---

### For a general large assignment problem

Think:

> **Minimum-Cost Matching / Hungarian Algorithm**

But don't reach for Hungarian automatically when `k` is tiny.

---

# 19. How to Recognize This Pattern in Future Problems

This problem is a really good pattern-recognition exercise.

Whenever you see:

```text
Some locations have EXTRA items
Some locations NEED items
Move items between them
Movement has a COST
```

pause and ask:

### Step 1

What are the **surplus** locations?

### Step 2

What are the **deficit** locations?

### Step 3

Can each surplus item be treated independently?

### Step 4

What is the cost of assigning:

```text
surplus → deficit
```

### Step 5

Is this actually a:

> **Minimum-cost matching problem?**

### Step 6

How many items are there?

If the number is small:

> **Bitmask DP**

If the number is larger:

> **Assignment / Matching algorithms**

This mental transformation is much more valuable than memorizing this particular problem.

---

# 20. The Most Important Insight

The biggest upgrade from your current solution is this:

### Don't think about MOVES first.

Think about the **final ownership of stones**.

Instead of:

```text
Move stone
↓
Move stone
↓
Move stone
↓
...
```

think:

```text
Extra stones
      ↓
Which empty cell should each one serve?
      ↓
Minimize total distance
```

Then movement becomes just a **distance calculation**.

That's the abstraction that turns this from a grid simulation problem into a small assignment problem.

---

# 21. Your Current Solution — Verdict

Your approach is **correct and demonstrates good recursive thinking**.

The strongest part of your reasoning is:

> **Fix one zero and decide which surplus cell fills it.**

That's a valid way to reduce the branching.

The main weakness is that you're still carrying the **entire mutable grid as the state**.

The more optimized thought process is:

> **The actual state isn't the whole grid. The actual state is which empty destinations have already been matched.**

Once you see that, **bitmask DP naturally falls out of the problem**.

### Final takeaway

```text
Grid Problem
     ↓
Find surplus + empty cells
     ↓
Extra stones ↔ Empty cells
     ↓
Manhattan distance = assignment cost
     ↓
Small number of items
     ↓
Bitmask DP ⭐
```

That is the pattern I'd want you to remember from LC 2850.
