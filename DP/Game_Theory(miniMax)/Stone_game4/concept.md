# LeetCode 1510 — Stone Game IV

## 🧠 Core Concept

This is a **two-player game DP / Minimax** problem.

At any state `n`, the player whose turn it is can remove any **perfect square** `x²` such that:

* `x² <= n`
* The game then moves to state `n - x²`.

The important question is not:

> "Which move gives me the biggest immediate advantage?"

Instead, ask:

> **"Can I make at least one move that leaves my opponent in a losing state?"**

This gives the fundamental game-DP idea:

* If **any** reachable state is losing → current state is **winning**.
* If **all** reachable states are winning → current state is **losing**.

---

## 📌 DP State Meaning

A useful 1D state is:

> `dp[n]` = whether the player whose turn it is with `n` stones remaining can force a win.

This interpretation is important because you **do not need separate states for Player 1 and Player 2**.

The same `dp[n]` meaning works regardless of whose actual turn it is.

---

## 🎯 Base Case

When:

> `n = 0`

there are no moves available.

Therefore, the player whose turn it is **loses**.

So the zero state is naturally a **losing state**.

This base case is what allows the winning states to propagate.

---

## 🔄 Minimax Pattern

The recurrence follows a very common game-DP pattern:

```text
Current state is WIN
        if
there exists a move
        ↓
Opponent reaches a LOSE state
```

In logical terms:

```text
WIN = exists(LOOSE reachable state)
LOSE = all(WIN reachable states)
```

This `exists opponent-loses` pattern appears in many impartial games.

### ⭐ Reusable Trick

Whenever you see:

> "Two players alternate turns and both play optimally"

immediately consider:

**Minimax + DP / memoization.**

You often don't need to explicitly model both players.

---

## 🧮 Possible Moves

The only legal moves are:

```text
1², 2², 3², 4², ...
```

up to the current value.

For a state `n`, the number of possible square moves is approximately:

> `√n`

This is important for complexity analysis.

---

## ⚡ Precomputing Perfect Squares

Instead of repeatedly determining whether a number is a perfect square, the possible square moves can be prepared beforehand.

Useful approaches include:

* A sorted vector of squares
* A set of squares
* Directly generating squares using their root

### Which structure is preferable?

For this problem, a **vector is generally more natural** because:

* Perfect squares are generated in sorted order.
* No insertion/deletion is required later.
* Memory is contiguous.
* Binary search can still be used.
* There is no need for tree-based ordering.

A `set` works, but its automatic ordering is unnecessary here.

---

## 🔍 `lower_bound` vs `upper_bound`

When you need:

> **largest perfect square ≤ `n`**

a useful STL trick is:

> `upper_bound(n)` → first value strictly greater than `n`

Then move one position backward.

This directly gives the largest valid square.

This avoids accidentally considering a square larger than the current state.

### General STL Tip

For:

> largest value `<= x`

think:

**`upper_bound(x)` → step back once**

For:

> first value `>= x`

think:

**`lower_bound(x)`**

This distinction is extremely useful in binary-search-based problems.

---

## 💾 Memoization / DP Optimization

Without DP, the same state can be reached through many different sequences of square removals.

For example, different previous moves may eventually lead to the same remaining value.

Instead of solving that state again:

> Store its result once and reuse it.

This converts an exponential-looking recursive game tree into a manageable DP solution.

### Key Recognition Pattern

If recursive calls look like:

```text
solve(n - something)
```

and many different paths can produce the same `n`:

> **Think memoization.**

---

## 📊 Complexity

There are at most `n` different states:

```text
0 ... n
```

For each state, there can be up to approximately `√n` possible square moves.

Therefore:

### Time

> **O(n√n)**

### Space

> **O(n)**

for the DP states, with only `O(√n)` additional space if the square values are stored separately.

---

# 🚀 Alternative Optimization: Full Precomputation

There is another interesting approach where all answers up to a fixed maximum `N` are computed **once**.

Then each individual query becomes:

> **O(1)**

This is useful when:

* Many test cases use the same maximum range.
* The maximum `n` is known beforehand.
* You can afford preprocessing.

The idea is essentially:

```text
Precompute answers for:
0, 1, 2, 3, ... N

Then:

query(n)
   ↓
directly return precomputed result
```

This is sometimes called:

> **Global / static precomputation**

---

# 🧠 Bitset Optimization

Since every DP state only needs two possible values:

```text
WIN
LOSE
```

you technically need only **one bit per state**.

A `bitset` can therefore represent the entire DP table very compactly.

This can reduce memory substantially compared with storing an integer for every state.

### General Optimization Insight

Whenever a DP state contains only:

```text
true / false
```

consider whether a:

* `bitset`
* boolean array
* packed representation

could be used instead of an integer array.

---

# 🔥 Important Game-DP Insight

The most important takeaway from this problem is not the square numbers.

It's this pattern:

```text
             Current State
                   │
             Try every move
                   │
        ┌──────────┴──────────┐
        │                     │
 Opponent loses          Opponent wins
        │                     │
        ↓                     ↓
 Current = WIN          Keep searching
                              │
                    No losing state found
                              ↓
                       Current = LOSE
```

This is one of the most reusable patterns for **turn-based optimal games**.

---

# 📝 Things to Remember

* Two-player optimal game → think **Minimax / Game DP**.
* `dp[n]` can represent the outcome for **the player whose turn it is**.
* A state is **WIN if at least one move reaches a LOSE state**.
* A state is **LOSE if every possible move reaches a WIN state**.
* `0` is naturally a losing state because no move is possible.
* Perfect squares can be precomputed.
* For sorted square values, a `vector` is usually enough.
* `upper_bound(x)` + one step backward gives the largest value `<= x`.
* Memoization prevents recomputation of the same state.
* Number of square moves for a state `n` is `O(√n)`.
* Standard DP solution: **O(n√n) time, O(n) space**.
* If many queries share a bounded maximum `N`, **precompute everything once**.
* Boolean DP states can potentially be compressed using a **bitset**.

---

## 💡 Reusable Mental Template

For future game problems, ask:

1. **What is my state?**
2. **What moves are legal from this state?**
3. **When is the state immediately losing?**
4. **Can I make one move that makes the opponent lose?**
5. **Can the same state be reached through different paths?**
6. **If yes → memoization / DP.**
7. **How many states exist?**
8. **How many transitions does each state have?**

That checklist will take you surprisingly far in game-DP problems.
