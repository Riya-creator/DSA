# LeetCode 76 — Minimum Window Substring

## Problem

Given two strings `s` and `t`, find the **smallest substring of `s`** that contains every character of `t` with the required frequency.

If no such substring exists, return `""`.

### Example

```text
s = "ADOBECODEBANC"
t = "ABC"

Answer = "BANC"
```

---

# 1. Initial Thought Process

A natural brute-force idea is:

```text
t
↓
store required characters
↓
find all indices of those characters in s
↓
select combinations of indices
↓
find the smallest valid range
```

This can work logically, but it becomes expensive because a character can occur many times.

For example:

```text
s = "AAAAAAAAAAAAAAAAAB"
t = "AAAB"
```

There are many possible occurrences of `A` that could participate in the answer.

So instead of generating many possible windows, we should **maintain one window and optimize it continuously**.

---

# 2. Key Observation

The answer is a **substring**, so it is a contiguous range:

```text
[i ... j]
```

This immediately suggests:

> **Sliding Window / Two Pointers**

We maintain:

```text
i = left boundary
j = right boundary
```

The window is:

```text
s[i ... j]
```

---

# 3. Core Idea

Maintain two frequency maps:

```text
need[c] → frequency required from t
use[c]  → frequency currently inside the window
```

Example:

```text
t = "AABC"
```

Then:

```text
need:
A → 2
B → 1
C → 1
```

---

# 4. The `total` Invariant

Instead of checking every character in the window repeatedly, maintain:

```text
total = number of required character occurrences
        that are still missing
```

Initially:

```text
total = t.size()
```

For:

```text
t = "AABC"
```

we have:

```text
total = 4
```

As characters enter the window:

```text
A → total = 3
A → total = 2
B → total = 1
C → total = 0
```

When:

```text
total == 0
```

the current window is **valid**.

---

# 5. Handling Duplicate Characters

This is one of the most important parts.

Suppose:

```text
t = "AABC"
```

We need:

```text
A = 2
B = 1
C = 1
```

If the window contains:

```text
AAA
```

the third `A` doesn't help satisfy any new requirement.

Therefore:

```text
if(use[c] <= need[c])
    total--;
```

Only the occurrences that satisfy an actual requirement reduce `total`.

---

# 6. When Should We Shrink?

This was the key point in the original approach.

Don't think:

```text
"Do I have 2 or more characters?"
```

Instead ask:

> **Is the current window valid?**

The condition is:

```text
total == 0
```

Therefore:

```text
while(total == 0)
```

we should try shrinking from the left.

---

# 7. Why Shrinking Works

Suppose:

```text
s = "ADOBECODEBANC"
t = "ABC"
```

Eventually we get:

```text
ADOBEC
^    ^
i    j
```

The window contains:

```text
A ✓
B ✓
C ✓
```

So:

```text
total == 0
```

Now try removing characters from the left:

```text
ADOBEC
 ^
```

Remove unnecessary characters:

```text
DOBEC
 ^
```

Continue until removing the next character would make the window invalid.

This guarantees that for every valid right boundary, we find the **smallest valid window ending there**.

---

# 8. Shrinking Logic

When removing `s[i]`:

```text
use[s[i]]--
```

If that removal causes us to lose a required occurrence:

```text
use[s[i]] < need[s[i]]
```

then the window is no longer valid.

So:

```text
total++
```

This gives the symmetric logic:

### Adding a character

```text
use[c]++

if(use[c] <= need[c])
    total--
```

### Removing a character

```text
use[c]--

if(use[c] < need[c])
    total++
```

This pair is the heart of the solution.

---

# 9. Complete Flow

```text
Start
  ↓
Create need frequencies
  ↓
Set total = t.size()
  ↓
Move right pointer
  ↓
Add s[j] to window
  ↓
Does this satisfy a missing requirement?
  ↓
Decrease total
  ↓
Is total == 0?
  ↓
YES
  ↓
Current window is valid
  ↓
Update minimum answer
  ↓
Remove s[i]
  ↓
Did removal break a requirement?
  ↓
YES → total++
  ↓
Move left pointer
  ↓
Window invalid
  ↓
Move right again
```

---

# 10. Important Invariant

At every point:

```text
total
=
number of required character occurrences
still missing from the current window
```

Therefore:

```text
total > 0
→ window is invalid

total == 0
→ window is valid
```

This invariant makes the entire algorithm easy to reason about.

---

# 11. Why We Don't Need `start`

An earlier approach introduced something like:

```text
start
```

to track the first relevant character.

This isn't necessary.

The left pointer already tells us where the window starts:

```text
[i ... j]
 ^
 left
```

So the only state we need is:

```text
i → left boundary
j → right boundary
need → required frequencies
use → current frequencies
total → missing requirements
```

Avoiding unnecessary state makes the sliding-window invariant much cleaner.

---

# 12. Why No Special Cleanup Is Required

Another mistake to avoid is doing extra processing **after the main loop**.

The window should be optimized whenever:

```text
total == 0
```

inside the main traversal.

Therefore:

```text
for every j:
    add s[j]

    while window is valid:
        update answer
        remove s[i]
```

This naturally handles the final valid window too.

No separate cleanup phase is necessary.

---

# 13. Complexity

Let:

```text
n = s.size()
m = t.size()
```

### Time

```text
O(n + m)
```

Why isn't the nested `while` O(n²)?

Because both pointers only move forward.

```text
j → at most n movements
i → at most n movements
```

Therefore the total number of pointer movements is at most:

```text
2n
```

So the algorithm is linear.

### Space

```text
O(k)
```

where `k` is the number of distinct characters being tracked.

For a fixed character set such as ASCII, this is effectively:

```text
O(1)
```

---

# 14. Brute Force vs Optimized Thinking

| Approach               | Main Idea                            | Complexity               |
| ---------------------- | ------------------------------------ | ------------------------ |
| Brute force substrings | Check every substring                | O(n²) or worse           |
| Index combinations     | Store positions and combine them     | Can become combinatorial |
| Sliding Window         | Maintain and shrink one valid window | **O(n + m)**             |

The important optimization isn't merely using `unordered_map`.

The real optimization is:

> **Don't generate all candidate windows. Maintain the current window incrementally.**

---

# 15. General Pattern to Recognize

When you encounter:

```text
substring / subarray
+
minimum / maximum
+
some condition
```

ask:

```text
1. Can I represent the answer as [left, right]?
2. What makes the window valid?
3. Can I maintain that condition incrementally?
4. If valid, should I shrink?
5. If invalid, should I expand?
```

For Minimum Window Substring:

```text
substring
    ↓
sliding window
    ↓
frequency requirement
    ↓
maintain counts
    ↓
valid when total == 0
    ↓
shrink while valid
```

---

# 16. Key Takeaway

The biggest lesson from this problem is not the code.

It's the transition in thinking:

```text
"How can I generate possible answers?"
                ↓
"How can I maintain one candidate?"
                ↓
"How can I eliminate unnecessary parts?"
```

For LC 76:

```text
Expand → Become valid → Shrink → Become invalid → Expand
```

Once this pattern becomes intuitive, a **lot of substring/subarray problems stop looking like brute-force search problems and start looking like state-maintenance problems.**
