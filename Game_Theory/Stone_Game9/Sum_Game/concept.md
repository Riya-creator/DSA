# LeetCode 1927 — Sum Game

## 🧠 Core Idea

This is a **game theory + invariant** problem.

The first instinct may be to think about every possible digit that can be placed in `?`, but that leads to an enormous number of possibilities.

The key is to stop thinking about the exact digits and instead track:

1. The **current sum difference** between the two halves.
2. The **number of `?` on each side**.
3. Whether the second player can **perfectly counterbalance** the first player's moves.

The goal is to determine whether Alice can **force** the two half-sums to become different.

---

## 1. Start With the Final Condition

The game ends with:

> **Alice wins if the two half-sums are different.**

Bob wins only if he can guarantee:

> **Left sum = Right sum**

So instead of asking:

> "What digit should Alice/Bob put?"

ask:

> **"Can Bob always maintain the possibility of equal sums?"**

This shift in perspective is the biggest part of solving the problem.

---

## 2. Track Only the Important Information

For each half, keep conceptually:

* Current sum of known digits
* Number of unknown `?`

Let:

* `L` = current left sum
* `R` = current right sum
* `qL` = number of `?` on the left
* `qR` = number of `?` on the right

The exact positions of the `?` don't matter.

What matters is **how many unknown moves each player has available on each side**.

---

# 3. Why the Number of `?` Matters

Suppose both sides have the same number of unknowns.

```text
qL = qR
```

The moves can essentially be paired.

Alice changes one side.

Bob can respond on the other side and try to cancel the effect.

Therefore, if the current sums are already equal, Bob has a natural way to preserve equality.

So:

> **Equal number of `?` → existing sum difference must be zero for Bob to win.**

---

# 4. What If One Side Has More `?`?

This is where the interesting part happens.

Suppose:

```text
qL > qR
```

The left side has additional unknown positions.

Those extra positions create an unavoidable potential imbalance.

Digits range from:

```text
0 → 9
```

So the maximum difference a single unmatched contribution can create is related to **9**.

Because moves are alternating and Bob is trying to counter Alice's choices, the effective compensation appears as:

```text
9 / 2
```

per difference in the number of unknown positions.

Therefore, Bob can win only when the **existing sum difference exactly compensates for the imbalance in the number of `?`**.

---

# 5. Bob's Winning Condition

Using:

```text
L - R
```

as the current sum difference:

Bob wins only when:

```text
L - R = 9 × (qR - qL) / 2
```

Conceptually, don't memorize this equation first.

Remember:

> **Existing sum imbalance must exactly cancel the imbalance created by the unequal number of unknown positions.**

The equation is simply the mathematical form of that idea.

---

# 6. Why Exact Equality Matters

This is a **forcing game**.

If Bob's required balance is even slightly off:

```text
current imbalance ≠ required compensation
```

Alice can exploit the remaining `?` and force the final sums to differ.

So Bob doesn't win merely because the values are "close".

He needs the **exact balance** that allows him to respond to Alice throughout the game.

---

# 7. Odd Number of `?`

This is an important shortcut.

If the total number of `?` is odd:

```text
qL + qR = odd
```

Alice gets the extra move.

That means Bob cannot pair every Alice move with a response.

Alice can use the final unmatched move to force the sums apart.

Therefore:

> **Odd total number of `?` → Alice wins.**

No complicated balancing is required.

---

# 8. The Mental Model

Think of the game as a **balance scale**:

```text
             LEFT              RIGHT
              │                  │
              ▼                  ▼
        known sum + ?      known sum + ?
              │                  │
              └───────┬──────────┘
                      ▼
                Can Bob cancel
                every effect?
                   /      \
                 YES      NO
                  │        │
              Bob wins   Alice wins
```

The two things Bob must account for are:

```text
Existing imbalance
        +
Imbalance in number of ?
```

If they cancel **exactly**, Bob can survive.

Otherwise Alice can force a difference.

---

# 9. How to Think About It in a Contest

When you see a problem like this, don't immediately simulate the game.

Use this sequence:

### Step 1 — Identify the final winning condition

Here:

```text
Left sum != Right sum
```

means Alice wins.

---

### Step 2 — Ask what information actually affects the final state

The exact arrangement of digits isn't important.

Only:

```text
current sums
+
number of unknown positions
```

matter.

---

### Step 3 — Look for pairing

Because players alternate:

> Can Bob pair his move with Alice's move?

If yes, equality can potentially be maintained.

If not, the unmatched move becomes important.

---

### Step 4 — Find the maximum effect of a move

A digit can range from:

```text
0 to 9
```

so the important extreme difference is:

```text
9
```

This is where the `9/2` relationship comes from.

---

### Step 5 — Derive the invariant

Instead of exploring moves, ask:

> **What must already be true for Bob's counter-strategy to work?**

That produces the exact balance condition.

---

# 10. The Biggest Lesson From This Problem

Your original thought was actually close:

> **"Track the sum and make the difference deviate or match."**

The upgrade is:

> ❌ Don't track only the sum difference.
> ✅ Track **sum difference + distribution of `?` between the two halves**.

That's the missing invariant.

Your original idea of using **small/large digits (`0` and `9`)** was also pointing in the right direction.

---

# 11. What NOT to Do

### ❌ Don't brute force the choices

Each `?` has 10 possibilities.

The number of possible games explodes extremely quickly.

---

### ❌ Don't greedily decide based only on the current difference

For example:

> "Left is currently smaller, so I'll put 9 on left."

That isn't enough.

The **remaining number and distribution of `?`** determine whether the opponent can counter your move.

---

### ❌ Don't think only about total `?`

```text
qL + qR
```

is not sufficient.

You need:

```text
qL
qR
```

separately.

Two strings can have the same total number of `?` but completely different game outcomes because the `?` are distributed differently.

---

# 12. Final Cheat-Sheet 🧠

```text
Goal:
    Determine whether Alice can force unequal sums.

Track:
    L = known left sum
    R = known right sum
    qL = unknowns on left
    qR = unknowns on right

First:
    If total ? is odd
        → Alice wins

Otherwise:
    Bob wins only if the current sum difference
    exactly compensates for the imbalance
    in the number of ?.

Bob condition:

    L - R = 9 × (qR - qL) / 2

Otherwise:
    Alice wins.
```

### One-line intuition

> **Bob wins only when the existing sum imbalance is exactly the amount needed to neutralize the unequal number of future moves.**

That's the real concept behind LC 1927 — **not digit simulation, but finding the invariant that makes Bob's counter-strategy possible.**
