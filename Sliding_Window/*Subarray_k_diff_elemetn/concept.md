# LeetCode 992 – Subarrays with K Different Integers

## Core Learning Objective

This problem is **not** about implementing a sliding window.

It is about recognizing **when the original problem is difficult to count directly** and transforming it into a version that has a **monotonic property**.

---

# Initial Intuition

The first natural thought is:

* Expand the window.
* Maintain exactly `K` distinct elements.
* Count valid windows.

Unfortunately, this approach quickly becomes difficult because a **single valid window can represent multiple valid subarrays**.

Example:

```
[1, 1, 2]
```

When the window becomes valid,

```
[1,1,2]
```

both of these are valid:

```
[1,1,2]
[1,2]
```

So,

```
One valid window ≠ One valid answer
```

This is the first major realization.

---

# Why Direct Counting Becomes Difficult

Once a window is valid, the question becomes

> **How many different starting positions are still valid for this fixed ending position?**

Trying to answer this directly often leads to ideas like:

* storing indices
* storing first occurrence
* storing last occurrence
* using queues/deques
* tracking removable elements

Most of these ideas work conceptually but become unnecessarily complicated because the information constantly changes as the window slides.

---

# The Important Observation

Instead of asking

```
Exactly K Distinct
```

ask

```
At Most K Distinct
```

Why?

Because **At Most K** has a monotonic property.

Removing elements from the left can **never increase** the number of distinct elements.

That single property makes counting extremely easy.

---

# The Transformation Trick

```
Exactly(K)
=
AtMost(K)
-
AtMost(K-1)
```

This removes every window having

```
0
1
2
...
K-1
```

distinct elements and leaves only windows having exactly `K` distinct elements.

This is the biggest insight of the problem.

---

# Why "At Most K" Is Easy

Maintain a window such that

```
Distinct <= K
```

Whenever the window becomes valid,

every subarray ending at the current right pointer is also valid.

Suppose

```
i          j
↓          ↓
1 2 1 2
```

Possible starting positions are

```
i
i+1
i+2
...
j
```

Hence,

```
Number of valid subarrays
=
(j - i + 1)
```

No additional counting is required.

---

# Why This Doesn't Work for "Exactly K"

Suppose

```
1 2 3
```

Exactly 3 distinct.

Length is 3.

But

```
2 3
```

has only 2 distinct.

So not every smaller window remains valid.

Therefore,

```
j - i + 1
```

cannot be used directly for "Exactly K".

This is why the subtraction trick is needed.

---

# Sliding Window Invariant

Always ask yourself:

> **What property am I maintaining throughout the algorithm?**

Here the invariant is

```
Current window always has At Most K distinct elements.
```

Every movement of the pointers should preserve this property.

---

# Common Mistakes

### Mistake 1

Thinking

```
One valid window
=
One answer
```

False.

---

### Mistake 2

Trying to directly count "Exactly K."

If direct counting becomes messy,

ask yourself

> Can I transform the problem?

---

### Mistake 3

Overengineering the data structure.

Typical thoughts include

* deque
* first index
* last index
* occurrence lists

Before introducing a new structure, ask

> Does a simple frequency map already contain enough information?

Many sliding window problems only require the **current state**, not the complete history.

---

### Mistake 4

Confusing "window validity" with "number of answers."

A valid window is only a state.

The real question is

> **How many subarrays does this state contribute?**

---

# Analysis Framework for Future Problems

Whenever you encounter a counting problem, follow this checklist.

### Step 1

Can I use a sliding window?

Usually applicable when

* contiguous subarray
* substring
* interval

---

### Step 2

What property should the window always satisfy?

Examples

* sum <= K
* distinct <= K
* zeros <= K
* odd numbers <= K

This becomes the window invariant.

---

### Step 3

Can I count directly?

If not,

look for a transformation.

Typical transformations include

```
Exactly
=
AtMost
-
AtMost(previous)
```

or

```
Exactly
=
AtLeast
-
AtLeast(next)
```

---

### Step 4

After obtaining one valid window, ask

> **How many answers does this single window generate?**

Sometimes

```
+1
```

is enough.

Sometimes

```
window length
```

is enough.

Sometimes

a completely different counting strategy is required.

Never assume.

---

# Pattern Recognition

Whenever a problem contains words like

* Exactly K
* Exactly X
* Exactly N

immediately ask yourself

> Can I convert this into At Most or At Least?

This trick appears in many problems.

Examples include

* LC 992 – Subarrays with K Different Integers
* LC 1248 – Count Number of Nice Subarrays
* LC 930 – Binary Subarrays With Sum
* Many sliding window counting problems

---

# Big Lessons Learned

* A hard problem can become easy after changing its formulation.
* The best algorithm is not always the one with the cleverest data structure.
* Before inventing extra structures, question whether the current window state already contains enough information.
* Maintain a clear invariant before writing code.
* Count contributions, not just valid states.
* Monotonic properties are the biggest advantage of sliding window algorithms.

---

# Final Takeaway

> **When direct counting feels complicated, don't immediately search for a more complex data structure. First ask whether you're solving the right version of the problem. Transforming the problem into a monotonic version is often the real algorithmic insight.**
