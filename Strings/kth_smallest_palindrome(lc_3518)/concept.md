# README – K-th Smallest Palindrome (Greedy + Combinatorics)

## Problem Overview

The objective is to find the **k-th lexicographically smallest palindrome** that can be formed from the given string.

A brute-force approach would generate every distinct palindrome, sort them, and return the k-th one. However, the number of distinct palindromes grows factorially, making generation infeasible.

The key is to **count** how many valid palindromes belong to each lexicographic group instead of generating them.

---

# Core Observation 1 – A Palindrome is Determined by its Left Half

Every palindrome is completely determined by:

* The left half.
* The middle character (only if the length is odd).

The right half is simply the reverse of the left half.

Example:

```
Left : abc
Mid  : d

Palindrome

abcdcba
```

Therefore, instead of constructing the entire palindrome, we only need to construct the left half.

---

# Core Observation 2 – Think in Groups Instead of Individual Strings

Suppose the first position of the left half can contain:

```
a
b
c
```

Rather than generating every palindrome,

think of them as groups.

```
Starts with 'a'
----------------
120 palindromes

Starts with 'b'
----------------
65 palindromes

Starts with 'c'
----------------
18 palindromes
```

If

```
k = 140
```

then

* Skip every palindrome beginning with 'a'
* Remaining k becomes

```
140 - 120 = 20
```

Now the answer must begin with 'b'.

This idea is called **group skipping**.

---

# Greedy Construction

Instead of deciding the whole palindrome at once,

repeat the following process for every position of the left half:

1. Try every available character in lexicographic order.
2. Temporarily fix that character.
3. Count how many palindromes can still be formed.
4. If that count is smaller than k:

   * Skip the entire group.
   * Reduce k.
5. Otherwise:

   * Permanently fix that character.
   * Move to the next position.

Repeat until the left half is complete.

Finally mirror it.

---

# Why Counting is Better than Generation

Generating every permutation has factorial complexity.

Instead,

only compute

> "How many solutions exist if I make this choice?"

This changes the problem from

```
Generate
↓

Sort
↓

Take kth
```

into

```
Count
↓

Skip

↓

Fix

↓

Repeat
```

This is a common strategy in:

* K-th permutation
* K-th lexicographical string
* Ranking / Unranking
* Digit DP
* Catalan object ranking
* Trie ranking problems

---

# Counting the Number of Remaining Palindromes

This is the heart of the solution.

Initially, it is tempting to use the multinomial formula

```
n!
------------------
f1! f2! f3! ...
```

where

* n = total remaining characters
* fi = frequency of each character

This correctly counts the number of distinct arrangements.

However, directly computing factorials quickly overflows.

---

# First Attempt (My Approach)

The initial approach was:

* Compute factorials.
* Divide by every frequency factorial.
* Prevent overflow using GCD cancellation.
* Later optimize by updating the count after fixing one character.

Advantages:

* Mathematically correct.
* Good understanding of multinomial counting.
* Introduced GCD cancellation to reduce overflow.

Problems:

* Initial counting remained expensive.
* Repeated GCD operations became a bottleneck.
* Maintaining exact counts while avoiding overflow became difficult.
* Updating parent counts using integer arithmetic could lose precision.
* Overall complexity was still too high.

---

# Editorial's Counting Method

Instead of thinking

```
Arrange characters
```

the editorial thinks

```
Choose positions
```

These are mathematically equivalent.

Instead of

```
n!
-------------
f1! f2! ...
```

it computes

```
Choose positions for character 1

×

Choose positions for character 2

×

Choose positions for character 3
```

Which becomes

```
C(n, f1)

×

C(n-f1, f2)

×

C(n-f1-f2, f3)
```

This completely avoids factorial computation.

---

# Why Choosing Positions Works

Suppose frequencies are

```
a : 2
b : 1
c : 1
```

Instead of asking

> "How many arrangements exist?"

think

> "Where should the two 'a' characters go?"

There are

```
4C2
```

ways.

Now only

```
2
```

positions remain.

Choose where 'b' goes

```
2C1
```

The last position automatically belongs to 'c'.

Multiply every choice together.

This produces exactly the same answer as the multinomial formula.

---

# Early Stopping (One of the Best Optimizations)

The algorithm only needs to know whether

```
ways >= k
```

It never needs the exact value once it exceeds k.

Therefore,

while computing combinations,

the count is capped once it becomes larger than k.

This avoids:

* Overflow
* Unnecessary multiplication
* Large intermediate values

This optimization significantly improves performance.

---

# Parent → Child Relationship

During the attempt to optimize counting,

another useful identity appeared.

If the current state has

```
Ways(parent)
```

then after fixing one occurrence of a character,

the child count can be derived from the parent count instead of recomputing everything.

This avoids repeatedly evaluating the entire multinomial expression.

Although the editorial ultimately uses a different counting method,

this identity is still an important combinatorial insight.

---

# Complexity

Editorial approach:

* Frequency counting: O(26)
* Greedy construction: O(26 × leftHalfLength)
* Counting uses combinations instead of factorials.

Overall efficient enough for the constraints.

---

# Comparison – My Final Attempt vs Editorial

## Similarities

* Uses only the left half.
* Greedy construction.
* Lexicographical traversal.
* Skip complete groups.
* Mirror the left half at the end.
* Never generates all palindromes.

These are the core algorithmic ideas, and they match the editorial.

---

## Differences

### My Approach

Counted arrangements using

```
Multinomial

n!
--------------
f1!f2!...
```

Attempted to:

* Avoid overflow.
* Cancel factors using GCD.
* Update child counts incrementally.

This worked conceptually but remained computationally expensive.

---

### Editorial

Reformulated the counting problem as

```
Choose positions
```

using combinations.

Benefits:

* No factorial tables.
* No GCD cancellation.
* Simpler arithmetic.
* Easy early stopping.
* Better performance.

---

# General Pattern for Future Problems

Whenever a problem asks for

* K-th permutation
* K-th lexicographical arrangement
* K-th palindrome
* K-th valid sequence

ask yourself:

1. Can I divide all answers into lexicographic groups?
2. Can I count the size of each group?
3. Can I skip entire groups instead of generating them?
4. Can I greedily fix one decision at a time?
5. Can I update counts instead of recomputing them?

If the answer is yes, generation is usually unnecessary.

---

# Biggest Takeaway

The hardest part of this problem was **not** the implementation.

It was recognizing that:

* counting is better than generating,
* answers can be grouped lexicographically,
* entire groups can be skipped,
* the palindrome is determined solely by its left half,
* and combinatorial counting can replace brute force.

Those ideas extend far beyond this single problem and are useful across many advanced combinatorial and greedy algorithms.
