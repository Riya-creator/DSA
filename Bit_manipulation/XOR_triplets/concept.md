# LeetCode 3513 & 3514 — Number of Unique XOR Triplets (Learning Notes)

> **Topic:** Bit Manipulation • XOR • Mathematical Observation • Hashing • Constraint Analysis

These two problems are an excellent example of a lesson that appears repeatedly in competitive programming and interviews:

> **A tiny change in the constraints can completely change the optimal solution.**

Although both problems ask for the **number of distinct XOR values obtainable from triplets**, the nature of the input transforms the problem from a **mathematical observation** into an **algorithmic optimization**.

---

# Why These Problems Are Worth Studying

Many LeetCode problems test your coding ability.

These two mainly test your ability to **observe the constraints before writing any code.**

The first instinct for both problems is usually

```
Generate every possible triplet
```

which immediately leads to

```
O(n³)
```

The goal isn't to optimize the brute force directly.

The goal is to first ask:

> **"Does the input itself contain any hidden structure?"**

That single question separates Problem **3513** from **3514**.

---

# Comparison

| Feature | LeetCode 3513 | LeetCode 3514 |
|----------|---------------|---------------|
| Input | Permutation of `1...n` | Arbitrary integer array |
| Numbers are unique | ✅ Yes | ❌ Not guaranteed |
| Every value from `1` to `n` exists | ✅ Yes | ❌ No |
| Hidden mathematical pattern | ✅ Yes | ❌ No |
| Formula based solution | ✅ Yes | ❌ No |
| Pair preprocessing required | ❌ No | ✅ Yes |
| Main idea | Pattern Recognition | XOR Optimization |

---

# The Biggest Difference

## Problem 3513

The array is **not random**.

It is guaranteed to be a permutation.

That means:

- every number exists exactly once
- no duplicates
- no missing values
- complete numerical coverage

This special structure creates a hidden mathematical pattern that eliminates the need to compute triplets.

The important lesson here is:

> **Sometimes the constraints solve the problem for you.**

---

## Problem 3514

Now the array becomes completely unrestricted.

Numbers may

- repeat
- be missing
- appear in any order
- have no mathematical relationship

The shortcut used in 3513 immediately disappears.

Instead of discovering a formula, we must optimize the computation itself.

This teaches another important lesson:

> **When structure disappears, preprocessing usually becomes the next best option.**

---

# The Role of XOR

Neither problem can be solved efficiently without understanding XOR.

The most important properties are

```
a ^ a = 0

a ^ 0 = a
```

and most importantly

```
(a ^ b) ^ c

=

a ^ (b ^ c)
```

This associative property allows computations to be reused instead of recalculated.

Whenever XOR appears in a problem, always ask yourself:

- Can intermediate XOR values be reused?
- Can expressions be regrouped?
- Can duplicate work be eliminated?

---

# What Changes Between Both Problems?

The question stays almost identical.

Only the **input guarantees** change.

This changes the entire thought process.

### In 3513

Think

```
Can I derive a mathematical formula?
```

### In 3514

Think

```
How can I avoid repeating the same XOR computations?
```

This shift in thinking is much more important than the implementation itself.

---

# Important Observations Beginners Often Miss

## 1. Read Constraints Before Coding

Most people immediately start thinking about three nested loops.

Instead,

always inspect

- input type
- constraints
- guarantees

before designing an algorithm.

The constraint often hints at the intended solution.

---

## 2. "Permutation" Is Not Just a Fancy Word

Whenever a problem says

```
Permutation
```

it usually means

- uniqueness
- complete coverage
- no repetitions

These properties often create mathematical shortcuts.

Never ignore this word.

---

## 3. Random Arrays Destroy Patterns

A mathematical trick that works on

```
1...n
```

almost never works once the numbers become arbitrary.

Whenever a problem changes from

```
Structured Input
```

to

```
General Input
```

expect your previous shortcut to disappear.

---

## 4. XOR Is Different From Addition

Many beginners unconsciously treat XOR like addition.

It isn't.

For example,

```
5 ^ 5

=

0
```

not

```
10
```

Always think in terms of **bits**, not arithmetic.

---

## 5. Reusing Computation Is a Common Pattern

3514 is not only a Bit Manipulation problem.

It is also an example of

> **Precompute once, reuse many times.**

This optimization appears in many topics:

- Prefix Sum
- Prefix XOR
- Dynamic Programming
- Sparse Tables
- Hashing
- Sieve Algorithms

Learning this mindset is more valuable than memorizing the solution.

---

# Edge Cases Worth Remembering

## Very Small Arrays

Small values of `n` often behave differently.

Many mathematical observations only become valid after a certain size.

Always verify

```
n = 1

n = 2
```

before applying a general rule.

---

## Duplicate Values

Only relevant in **3514**.

Duplicates can create identical XOR values.

This is why uniqueness must be handled carefully.

---

## Large Number of Repeated Results

Different triplets may produce the same XOR.

The problem asks for

> **Distinct XOR values**

not

> Number of triplets.

This difference is easy to overlook.

---

## Assuming Order Matters

XOR is commutative.

```
a ^ b

=

b ^ a
```

Reordering values does not change the result.

---

# Common Mistakes

❌ Applying the permutation trick to a random array.

---

❌ Ignoring the word **permutation** in the problem statement.

---

❌ Optimizing brute force before understanding the constraints.

---

❌ Counting triplets instead of counting distinct XOR values.

---

❌ Forgetting that repeated computations can often be preprocessed.

---

# Mental Checklist Before Solving Similar Problems

Whenever you encounter a new XOR problem, ask yourself:

### Step 1

Is the input

- structured?
- random?
- sorted?
- unique?
- a permutation?

---

### Step 2

Can a mathematical observation replace computation?

---

### Step 3

If not,

can intermediate XOR values be reused?

---

### Step 4

Would hashing help eliminate duplicate work?

---

### Step 5

Does the problem ask for

- total count
- distinct values
- maximum
- minimum

These often require completely different approaches.

---

# Key Learning Outcomes

After solving these two problems, you should be comfortable identifying:

- when constraints enable mathematical shortcuts
- when preprocessing is preferable to brute force
- how XOR associativity enables optimization
- why input guarantees matter as much as the algorithm
- how two nearly identical problems can require entirely different thinking

---

# Similar Problems to Practice Next

### XOR

- 136 — Single Number
- 137 — Single Number II
- 260 — Single Number III
- 421 — Maximum XOR of Two Numbers in an Array
- 1310 — XOR Queries of a Subarray
- 1442 — Count Triplets That Can Form Two Arrays of Equal XOR
- 1734 — Decode XORed Permutation
- 1829 — Maximum XOR for Each Query

### Pattern Recognition

- 319 — Bulb Switcher
- 292 — Nim Game
- 390 — Elimination Game

These problems continue building the same intuition used in 3513 and 3514.

---

# Final Takeaway

These two problems are less about XOR and more about **thinking differently based on constraints.**

Remember this simple comparison:

```
Structured Input
        │
        ▼
Look for Mathematical Patterns


Random Input
        │
        ▼
Look for Algorithmic Optimizations
```

This mindset extends far beyond these two questions and is one of the most valuable habits to develop for coding interviews and competitive programming.
