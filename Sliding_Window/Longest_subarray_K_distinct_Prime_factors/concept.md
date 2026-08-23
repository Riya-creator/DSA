# Sliding Window + Prime Factorization — Concepts & Cheat Sheet

## 1. Core Idea

Sliding Window is useful when we are working with a **contiguous subarray/substring** and need to maintain some property of the current range.

We keep two pointers:

* `left` → start of the window
* `right` → end of the window

The window is:

**`[left ... right]`**

Instead of checking every possible subarray, we move the pointers intelligently.

---

# 2. The Most Important Sliding Window Rule

Do **NOT** memorize:

> "When valid, shrink."

That is only true for certain problems.

Instead, first ask:

> **What am I trying to optimize?**

### Longest / Maximum valid window

Pattern:

**Expand → become invalid → shrink → become valid → expand**

Mental model:

```text
VALID → keep expanding
INVALID → shrink until VALID
```

Typical goal:

* Longest substring
* Longest subarray
* Maximum length satisfying a condition

---

### Shortest / Minimum valid window

Pattern:

**Expand → become valid → shrink while valid**

Mental model:

```text
INVALID → keep expanding
VALID → record answer + shrink
```

Typical goal:

* Minimum window substring
* Smallest subarray satisfying a condition
* Minimum length satisfying a requirement

---

# 3. Sliding Window Cheat Sheet

## Type 1 — Longest Valid Window

Use when the question asks:

* longest
* maximum length
* maximum size
* largest valid subarray/substring

### Template in words

1. Expand `right`
2. Add the new element to the window state
3. Check whether the window became invalid
4. If invalid, move `left`
5. Keep shrinking until valid again
6. Update the answer

### Golden pattern

```text
EXPAND
   ↓
INVALID?
   ↓ yes
SHRINK
   ↓
VALID
   ↓
UPDATE ANSWER
   ↓
EXPAND
```

### Key principle

> **For longest-window problems, maintain validity before updating the answer.**

---

# 4. Type 2 — Shortest Valid Window

Use when the question asks:

* shortest
* minimum length
* smallest window
* minimum substring/subarray satisfying something

### Template in words

1. Expand `right`
2. Add the new element
3. Check whether the window became valid
4. If valid, record the answer
5. Try shrinking from `left`
6. Continue shrinking while it remains valid
7. Once invalid, go back to expanding

### Golden pattern

```text
EXPAND
   ↓
VALID?
   ↓ yes
UPDATE ANSWER
   ↓
SHRINK
   ↓
INVALID
   ↓
EXPAND AGAIN
```

### Key principle

> **For shortest-window problems, exploit validity by shrinking as much as possible.**

---

# 5. The Question You Should Ask Before Coding

Whenever you see a sliding-window problem, ask these questions:

### Q1. What does my window represent?

Example:

> The current contiguous subarray from `left` to `right`.

### Q2. What makes the window valid?

Examples:

* At most `k` distinct values
* Sum ≤ `k`
* Number of zeros ≤ `k`
* Contains all required characters
* At most `k` prime factors

### Q3. What makes it invalid?

This is extremely important.

If the condition is:

> At most `k` distinct elements

Then:

```text
valid   → distinct <= k
invalid → distinct > k
```

### Q4. What happens when it becomes invalid?

Usually:

> Move `left` until the window becomes valid again.

### Q5. When do I update the answer?

For **longest**:

> After restoring validity.

For **shortest**:

> While the window is valid.

---

# 6. The Universal Longest-Window Pattern

For most longest-window problems, think:

```text
right moves → window grows

if window becomes invalid:
    left moves → window shrinks

when valid:
    calculate/update answer
```

The important invariant is:

> **After the shrinking phase finishes, the window must be valid.**

This is why the `while` loop is usually used for shrinking.

---

# 7. Why `while`, Not `if`?

Suppose your window is invalid.

Moving `left` once might not be enough.

Example:

```text
distinct = 5
k = 2
```

You need to remove enough elements to reach:

```text
distinct <= 2
```

Therefore:

```text
while invalid:
    shrink
```

not:

```text
if invalid:
    shrink once
```

### Rule

> **Shrink repeatedly until the invariant is restored.**

---

# 8. Window State / Frequency Map

A sliding window often needs some data structure to describe what's currently inside the window.

Common choices:

| Requirement               | Useful structure         |
| ------------------------- | ------------------------ |
| Frequency of values       | `map` / `unordered_map`  |
| Presence only             | `set` / `unordered_set`  |
| Character frequencies     | Array of size 26/128/256 |
| Sum                       | Simple variable          |
| Number of distinct values | Map + counter            |
| Maximum/minimum in window | Deque                    |
| Complex range property    | Depends on condition     |

The important concept:

> **The data structure represents the current window, not the entire array.**

---

# 9. Adding and Removing Elements

Every sliding-window implementation has two fundamental operations:

### Add right element

When `right` moves:

> Add the new element to the window state.

### Remove left element

When `left` moves:

> Remove that element from the window state.

This means your window state must support:

```text
ADD(x)
REMOVE(x)
```

If you cannot correctly remove an element, your sliding-window implementation will usually break.

---

# 10. Important Pointer Rule

Never randomly move pointers.

For a normal sliding window:

```text
right → moves forward to expand
left  → moves forward to shrink
```

Both pointers generally move:

**left →→→**

**right →→→**

They should almost never move backward.

This gives the major efficiency benefit:

> Each element enters the window once and leaves the window once.

---

# 11. Why Sliding Window Is Efficient

Consider an array of size `n`.

A brute-force approach might examine:

```text
O(n²)
```

subarrays.

With sliding window:

* `right` moves at most `n` times
* `left` moves at most `n` times

Therefore the pointer movement is:

**O(n)**

If each add/remove operation is O(1) average using a hash map, the overall window processing can also be approximately:

**O(n)**

---

# 12. Prime Factorization — Concept Used in This Problem

Sometimes the sliding-window condition isn't directly about the array values.

Instead, we transform each number into some property.

For example:

```text
12 → 2 × 2 × 3
18 → 2 × 3 × 3
```

The **distinct prime factors** are:

```text
12 → {2, 3}
18 → {2, 3}
```

Notice:

> Repeated powers of the same prime do not create additional distinct factors.

Therefore:

```text
12 = 2² × 3
```

has:

```text
2 distinct prime factors
```

not 3.

---

# 13. Prime Factorization Pitfall

When factorizing a number, once you discover a prime factor:

> Count that prime once, then remove all of its copies.

For example:

```text
72 = 2³ × 3²
```

Distinct prime factors:

```text
{2, 3}
```

not:

```text
{2, 2, 2, 3, 3}
```

This distinction matters when the sliding-window condition is based on **distinct prime factors**.

---

# 14. Combining Prime Factors With Sliding Window

The clever part of this problem is that the window isn't directly tracking numbers.

It tracks:

> **Which prime factors are currently represented by the elements inside the window.**

For example:

```text
nums = [6, 10, 15]
```

Prime factors:

```text
6  → {2,3}
10 → {2,5}
15 → {3,5}
```

The window state contains:

```text
{2,3,5}
```

So the sliding-window condition can be based on:

```text
number of distinct primes
```

This is an example of:

> **Transforming the input into a property that the window can maintain.**

This technique is useful far beyond prime factors.

---

# 15. Why Frequency Is Necessary

Suppose the current window contains:

```text
[6, 10]
```

Prime factors:

```text
6  → 2,3
10 → 2,5
```

The window contains:

```text
2,3,5
```

Now remove `6`.

Prime `2` is still present because `10` contains `2`.

Therefore you cannot simply say:

> "6 contains 2, so remove 2."

You need to know:

```text
prime 2 → appears in how many window elements?
```

Hence the frequency map.

### Core idea

```text
prime → number of current window elements containing that prime
```

If its frequency becomes zero:

> That prime no longer exists in the window.

Then it can be removed from the map.

---

# 16. A Very Important Distinction

There are two different frequencies you might accidentally track.

### Frequency of occurrences

For:

```text
12 = 2² × 3
```

Prime `2` occurs twice mathematically.

### Frequency of elements containing the prime

For sliding window purposes, you may instead want:

```text
12 contains 2 → contributes once
```

If the condition is based on **distinct prime factors**, you care about the second interpretation.

Always determine:

> **What exactly am I counting?**

---

# 17. Sliding Window Invariant

This is probably the most important concept to add to your DSA vocabulary.

An **invariant** is something that should remain true at a particular stage of the algorithm.

For a longest valid sliding window:

> **After shrinking, the current window must be valid.**

So:

```text
Before shrinking:
    window may be invalid

After shrinking:
    window MUST be valid
```

Then you can safely calculate:

```text
current window length
```

This way of thinking is much more powerful than memorizing templates.

---

# 18. How to Recognize Sliding Window Problems

Look for these clues:

### Strong signals

* subarray
* substring
* contiguous
* longest
* shortest
* maximum/minimum length
* at most `k`
* exactly `k`
* contains
* satisfies a condition

Especially when the question asks for an **optimal contiguous range**.

---

# 19. When Sliding Window Usually Does NOT Work

Be careful when:

* The elements don't need to be contiguous
* You need arbitrary subsequences
* Removing the left element doesn't allow you to maintain the condition
* The condition behaves unpredictably when expanding/shrinking
* Negative numbers make a sum-based condition non-monotonic

For example, the classic:

> longest subarray with sum ≤ k

works nicely with positive numbers.

With negative numbers, the usual sliding-window logic can break because adding an element doesn't necessarily make the sum larger.

---

# 20. Your Personal Sliding Window Cheat Sheet

## 🟢 Longest

```text
EXPAND
↓
INVALID?
↓ yes
SHRINK until VALID
↓
UPDATE ANSWER
```

**Memory phrase:**

> **Longest = Expand freely, shrink only when broken.**

---

## 🔵 Shortest

```text
EXPAND
↓
VALID?
↓ yes
UPDATE ANSWER
↓
SHRINK while VALID
↓
INVALID
↓
EXPAND
```

**Memory phrase:**

> **Shortest = Become valid, then squeeze.**

---

## 🟡 Always Ask

```text
1. What is my window?
2. What makes it valid?
3. What makes it invalid?
4. How do I restore validity?
5. When do I update the answer?
6. What state do I need to maintain?
7. Can I add/remove elements efficiently?
```

---

# 21. The One-Line Mental Model

If you remember only ONE thing:

> **Longest → maintain validity.**
>
> **Shortest → exploit validity.**

Or even simpler:

```text
LONGEST:
    invalid → shrink

SHORTEST:
    valid → shrink
```

That tiny distinction solves a surprisingly huge chunk of sliding-window problems.

---

# 22. Final Pattern to Internalize

Don't look at sliding window as:

> "Move left, move right, use a map..."

Instead think:

```text
             ┌──────────────┐
             │   EXPAND     │
             │  right →     │
             └──────┬───────┘
                    ↓
              Check condition
                    ↓
             ┌──────┴───────┐
             │              │
          VALID           INVALID
             │              │
             ↓              ↓
       depends on       SHRINK left
       the objective        ↓
             │          until valid
             │              │
             └──────┬───────┘
                    ↓
              Update answer
```

The **objective determines when you shrink**.

That's the part you should train your brain to recognize rather than memorizing individual LeetCode solutions.
