# LeetCode 421 --- Maximum XOR of Two Numbers in an Array

## 1. Core Problem

The goal is to find the maximum value of:

**nums\[i\] XOR nums\[j\]**

The important property of XOR is that each bit is decided independently.

For XOR to be large, the highest possible bits matter more than the
lower bits.

Therefore, the answer should be constructed from the **most significant
bit (MSB) to the least significant bit (LSB)**.

------------------------------------------------------------------------

## 2. Why Greedy Bit-by-Bit Construction Works

A higher bit contributes more to the final number than all lower bits
combined.

So while constructing the answer:

-   First try to make the highest bit `1`.
-   If that is possible, keep it.
-   Then try to make the next bit `1`.
-   Continue until the lowest bit.

A decision made for a higher bit should never be sacrificed just to
improve lower bits.

This gives a greedy strategy.

------------------------------------------------------------------------

## 3. The Main Question at Every Bit

For every bit, ask:

> **Can some pair of numbers produce `1` at this bit while keeping all
> previously selected higher bits of the XOR valid?**

To answer this efficiently, we work with **prefixes** of the numbers.

------------------------------------------------------------------------

## 4. Prefixes

At a particular bit, only the bits from the current bit up to the most
significant bit matter.

A **prefix** is the portion of a number containing only those currently
relevant bits.

As we move from MSB to LSB, the prefix becomes longer.

The purpose of storing prefixes is to determine whether two numbers can
produce the XOR pattern we are currently trying to build.

------------------------------------------------------------------------

## 6. Candidate Answer

At every bit, we temporarily assume:

> **What if the current bit of the answer can be `1`?**

The existing answer represents the bits that have already been
successfully established.

The **candidate** is:

> **The current known answer with the current bit optimistically set to
> `1`.**

We then test whether this candidate is actually achievable by some pair
of numbers.

------------------------------------------------------------------------

## 7. The XOR Complementary-Prefix Idea

Suppose we want:

**prefix₁ XOR prefix₂ = candidate**

From the XOR property:

**prefix₂ = prefix₁ XOR candidate**

Therefore, if we choose one prefix, we can calculate exactly what the
other prefix would need to be.

This required prefix is the **needed prefix**.

------------------------------------------------------------------------

## 9. Why a Set Is Used

We only need to answer:

> **Does this prefix exist?**

We don't need to know which number produced it.

A set provides fast existence checking.

This allows us to test complementary prefixes efficiently instead of
checking every pair of numbers.

------------------------------------------------------------------------

## 10. The Complete Mental Flow

**Start with answer = 0**

↓

**Process bits from MSB → LSB**

↓

**Expand the prefix mask**

↓

**Create prefixes of all numbers**

↓

**Assume the current answer bit can be `1`**

↓

**Create the candidate answer**

↓

**For each prefix, calculate its required complementary prefix**

↓

**Check whether that prefix exists**

↓

**If yes → keep the current bit**

↓

**If no → leave the current bit as `0`**

↓

**Move to the next lower bit**

↓

**Final answer = maximum possible XOR**

------------------------------------------------------------------------

## 11. Three Important Variables to Remember

### `mask`

Think:

> **"Which bits are currently part of the prefix?"**

It grows one bit at a time as we move downward.

### `candidate`

Think:

> **"What would my answer be if I successfully make the current bit
> `1`?"**

It is an optimistic version of the answer.

### `needed`

Think:

> **"If I use this prefix, what other prefix do I need to produce the
> candidate XOR?"**

It comes directly from the XOR relationship.

------------------------------------------------------------------------

## 13. Connection With Binary Trie

The Prefix Set method and Binary Trie method are based on the same
fundamental idea:

> **For maximum XOR, try to make the highest possible bit `1`.**

### Binary Trie

At each bit:

-   Look for the opposite bit.
-   Prefer the opposite bit because it makes XOR `1`.

### Prefix Set

At each bit:

-   Assume the current XOR bit can be `1`.
-   Look for complementary prefixes that make that candidate possible.

So both approaches are different implementations of the same greedy
bitwise principle.

------------------------------------------------------------------------

## 15. Pattern to Recognize in Future Problems

When you see:

-   XOR
-   Maximum or minimum XOR
-   Large number of possible pairs
-   Need to optimize a bitwise value

Think:

**Bitwise greedy → MSB to LSB → complementary bits/prefixes → Binary
Trie or Prefix Set**

This pattern is useful beyond LeetCode 421 and is a valuable
bit-manipulation technique for interviews and competitive programming.
