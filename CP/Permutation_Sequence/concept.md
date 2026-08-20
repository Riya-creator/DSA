

# LeetCode 60 — Permutation Sequence

## Problem

Given two integers `n` and `k`, return the `k`-th permutation of the numbers `1` to `n` in **lexicographical order**.

The important constraint is:

```text
1 <= n <= 9
1 <= k <= n!
```

---

## Core Idea

The key observation is that we **do not need to generate all permutations**.

For `n` numbers, there are:

```text
n!
```

total permutations.

If we fix the first number, the remaining `n - 1` numbers can be arranged in:

```text
(n - 1)!
```

ways.

Therefore, permutations are naturally divided into blocks.

### Example

For `n = 4`:

```text
Total permutations = 4! = 24
```

Fixing the first element gives blocks of:

```text
3! = 6
```

permutations.

So:

```text
First element     Number of permutations

1                 6
2                 6
3                 6
4                 6
```

Therefore:

```text
1 → permutations 1 to 6
2 → permutations 7 to 12
3 → permutations 13 to 18
4 → permutations 19 to 24
```

Instead of generating permutations, we determine **which block contains `k`**.

---

# Step-by-Step Approach

## 1. Store Available Numbers

Initially:

```text
1 2 3 4
```

All numbers are available.

Whenever we select a number, it is removed from the available list.

For example:

```text
1 2 3 4
```

Select `3`:

```text
1 2 4
```

The next position is determined using the same factorial-block idea.

---

## 2. Convert `k` to Zero-Based Indexing

The mathematical calculations are easier with zero-based indexing.

Therefore:

```text
k = k - 1
```

This allows us to directly use:

```text
index = k / block_size
```

---

## 3. Calculate the Block Size

If there are `n` numbers remaining, fixing the next number leaves:

```text
n - 1
```

numbers.

Therefore each block contains:

```text
(n - 1)!
```

permutations.

---

## 4. Find the Correct Number

The index of the number to select is:

```text
index = k / (n - 1)!
```

Suppose:

```text
n = 4
k = 17
```

After converting to zero-based:

```text
k = 16
```

The block size is:

```text
3! = 6
```

Therefore:

```text
index = 16 / 6
      = 2
```

The available numbers are:

```text
1 2 3 4
```

Index `2` corresponds to:

```text
3
```

So `3` is the first element.

---

## 5. Move Inside the Selected Block

After selecting the element, we only care about the position of `k` **inside that block**.

This is done using:

```text
k = k % block_size
```

For the previous example:

```text
k = 16 % 6
  = 4
```

Now the problem is reduced to finding the `4`-th position within the permutations beginning with `3`.

---

## 6. Repeat

After selecting one number:

```text
n → n - 1
```

and the available numbers become smaller.

The same process is repeated:

```text
Calculate block size
        ↓
Find index
        ↓
Select number
        ↓
Remove number
        ↓
Update k
        ↓
Repeat
```

Eventually all positions are determined.

---

# Why This Works

The entire permutation space can be viewed as a tree.

For:

```text
1 2 3 4
```

the first level looks like:

```text
                 All permutations
                        |
          +------+------+------+
          |      |      |      |
          1      2      3      4
          |      |      |      |
         3!     3!     3!     3!
```

Each branch contains exactly `(n-1)!` permutations.

After choosing a branch, the same structure appears again with one fewer number.

This allows us to jump directly to the required permutation instead of traversing every permutation.

---

# Why `k - 1` Is Important

Without converting `k` to zero-based indexing, the division can point to the wrong block.

Using:

```text
k--
```

means:

```text
k = 1 → index 0
k = 2 → index 1
...
```

This matches the zero-based indexing used by vectors/arrays.

---

# Example Walkthrough

Consider:

```text
n = 4
k = 17
```

Initially:

```text
Available = [1, 2, 3, 4]
k = 16
```

### First position

```text
Block size = 3! = 6

index = 16 / 6
      = 2
```

Select:

```text
3
```

Remaining:

```text
[1, 2, 4]
```

Update:

```text
k = 16 % 6
  = 4
```

---

### Second position

```text
Block size = 2! = 2

index = 4 / 2
      = 2
```

Select:

```text
4
```

Remaining:

```text
[1, 2]
```

Update:

```text
k = 4 % 2
  = 0
```

---

### Third position

```text
Block size = 1! = 1

index = 0 / 1
      = 0
```

Select:

```text
1
```

Remaining:

```text
[2]
```

Finally select:

```text
2
```

Answer:

```text
3412
```

---

# Why We Don't Generate All Permutations

A brute-force approach would be:

```text
Generate all permutations
        ↓
Sort them
        ↓
Return the k-th one
```

But the number of permutations is `n!`.

For example:

| `n` | `n!` |
|---:|---:|
| 5 | 120 |
| 7 | 5,040 |
| 9 | 362,880 |
| 10 | 3,628,800 |
| 12 | 479,001,600 |

The factorial growth becomes extremely large.

The factorial-block approach directly calculates the required permutation.

---

# Complexity

## Time Complexity

The solution maintains the available numbers in a vector.

Selecting an element is fast, but removing an element from the middle of a vector requires shifting elements.

Across all iterations, this gives:

```text
O(n²)
```

## Space Complexity

We maintain:

- Available numbers
- Factorial values
- Answer

Therefore:

```text
O(n)
```

### Final Complexity

```text
Time  : O(n²)
Space : O(n)
```

---

# Why `O(n²)` Is Completely Fine Here

The constraint is:

```text
n <= 9
```

Therefore:

```text
n² <= 81
```

So there is no practical need to introduce a complicated data structure.

This is an important competitive-programming lesson:

> **Do not optimize blindly. Optimize according to the constraints.**

An `O(n²)` solution with `n <= 9` is effectively constant-time in practice.

---

# Optimization Analysis

When looking for optimization opportunities, don't immediately focus only on Big-O.

First identify **what operation is causing the repeated work**.

In this problem, the main repeated operations are:

1. Finding the required available number.
2. Removing that number from the available collection.

The factorial calculation itself is not the main bottleneck.

---

## What Should We Check Before Optimizing?

### 1. Input Constraints

Always check:

```text
How large can n be?
```

For this problem:

```text
n <= 9
```

So `O(n²)` is completely acceptable.

If the constraint were:

```text
n <= 10⁵
```

then the same approach would need serious reconsideration.

---

### 2. Identify the Repeated Operation

Ask:

> What am I doing again and again?

Here:

```text
Find available element
        ↓
Remove element
        ↓
Repeat
```

Repeated scanning/removal is what determines the complexity.

---

### 3. Look at the Data Structure

The vector is convenient because:

- Numbers remain ordered.
- We can directly access an index.
- The implementation is simple.

But deleting from the middle costs `O(n)`.

If the constraints were much larger, we could consider data structures designed for:

```text
Find k-th available element
Remove element
```

Examples:

- Fenwick Tree / Binary Indexed Tree
- Segment Tree
- Order-statistics tree

For this problem, however, those would be unnecessary.

---

# Data Structure Selection Lesson

The right data structure depends on the operations you need.

| Requirement | Possible Choice |
|---|---|
| Check whether number is used | `used[]` |
| Maintain remaining numbers | `vector` |
| Frequent middle deletion | More advanced structure |
| Find k-th available element efficiently | Fenwick Tree / Segment Tree |
| Very small `n` | Simple vector/array |

The important lesson is:

> **Choose a data structure based on the operations and constraints, not because it has a better theoretical reputation.**

---

# Mathematical Concept Behind the Solution

This problem is closely related to the:

- **Factorial Number System**
- **Lehmer Code**
- **Factorial-based ranking of permutations**

Each position determines how many unused elements come before the selected element.

The values:

```text
(n-1)!
(n-2)!
(n-3)!
...
1!
0!
```

act as the weights used to determine the permutation.

This is why the solution can construct the answer directly from `k`.

---

# General Pattern to Recognize

Whenever you encounter a problem asking for:

- `k`-th permutation
- `k`-th lexicographical arrangement
- `k`-th ordering
- Directly find an arrangement without generating all arrangements

Think:

```text
Can I divide the search space into equal-sized blocks?
```

Then ask:

```text
How many possibilities does each choice produce?
```

If that number can be calculated mathematically, you may be able to **jump directly to the required branch**.

---

# Mental Template

```text
k-th arrangement problem
        ↓
Calculate number of possibilities per choice
        ↓
Divide k by block size
        ↓
Select the corresponding element
        ↓
Remove selected element
        ↓
Update k using remainder
        ↓
Repeat
```

---

# Key Takeaways

### Algorithmic

- Don't generate all permutations when the required permutation can be constructed directly.
- Use factorials to calculate permutation block sizes.
- Convert `k` to zero-based indexing.
- Select the appropriate block using division.
- Use the remainder to continue inside that block.

### Data Structures

- A simple vector is sufficient because `n <= 9`.
- More advanced structures are only useful if the constraints demand them.

### Optimization

- Always inspect constraints before optimizing.
- Find the actual bottleneck.
- Identify repeated scans/removals.
- Choose data structures according to required operations.
- Don't trade simplicity for theoretical optimization when the input is tiny.

### Core Insight

> **The biggest optimization in this problem happens at the algorithmic level: instead of searching through permutations, use factorial mathematics to jump directly to the required permutation.**
