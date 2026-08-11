# LeetCode 1510 — Stone Game IV

## Alternative Approach: Static Precomputation + Bitset + Reverse DP

---

## 🧠 The Main Idea

The normal way to solve this problem is to start from a particular `n` and recursively ask:

> **"Can the current player force a win from this state?"**

The alternative approach does something different:

> **Precompute the answer for every possible state from `0` to `MAX` before any query is made.**

Then, when `winnerSquareGame(n)` is called, the answer is already stored.

So instead of:

```text
query n
   ↓
solve n
   ↓
solve smaller states
   ↓
return answer
```

we do:

```text
program starts
      ↓
precompute 0 ... MAX
      ↓
store every answer
      ↓
query n
      ↓
directly return answer
```

---

# 1. Game DP Concept

The fundamental game logic is exactly the same as the normal DP solution.

For a state `n`:

> `dp[n]` tells whether the player whose turn it currently is can force a win.

A state is:

### WINNING

If there is **at least one move** that sends the opponent to a losing state.

```text
WIN
 ↓
make a move
 ↓
opponent gets LOSE
```

### LOSING

If **every possible move** sends the opponent to a winning state.

```text
LOSE
 ↓
every move
 ↓
opponent gets WIN
```

This is the classic **minimax / game-DP pattern**.

---

# 2. Base State

The state:

```text
n = 0
```

is losing.

Why?

There are no stones left, so the player whose turn it is has no legal move.

Therefore:

```text
dp[0] = LOSE
```

This state becomes the starting point for propagating the rest of the answers.

---

# 3. Normal DP vs This Approach

## Normal Top-Down DP

The approach you originally developed is:

```text
solve(n)
   ↓
try every square <= n
   ↓
solve(n - square)
   ↓
if any resulting state is LOSE
   ↓
current state is WIN
```

This is **top-down DP / memoization**.

Only states that are actually needed are calculated.

---

## This Alternative Approach

This approach reverses the direction.

Instead of asking:

> "Can I move from `n` to a losing state?"

it asks:

> "If `i` is a losing state, which states can move to `i`?"

Suppose:

```text
i = LOSE
```

and a player can remove `j²`.

Then:

```text
i + j²
```

can move to `i`.

Therefore:

```text
i + j² = WIN
```

because that player has a move that leaves the opponent at a losing state.

So the propagation becomes:

```text
LOSE state
    ↓
add a perfect square
    ↓
reachable state
    ↓
WIN
```

---

# 4. Why `dp.set(i + j²)` Works

Suppose:

```text
dp[i] = LOSE
```

Consider:

```text
x = i + j²
```

From `x`, the current player can remove `j²`:

```text
x - j²
= i + j² - j²
= i
```

Since `i` is losing, the player at `x` has found a winning move.

Therefore:

```text
dp[x] = WIN
```

This is exactly what the update:

```text
dp.set(i + j²)
```

represents.

---

# 5. Why We Only Process Unset States

Initially, every bit is:

```text
0
```

An unset bit represents a state that has not been marked as winning.

The algorithm processes such states as potential losing states.

If a state is already marked:

```text
dp[i] = 1
```

then it is already known to be winning.

There is no reason to use it as a losing-state source.

Therefore:

```text
if dp[i] is already WIN
    skip it
```

This is why the approach can use the absence of a bit as the losing information.

---

# 6. Important Subtlety: `0` Means LOSE

The bitset does not explicitly store:

```text
WIN
LOSE
```

Instead:

```text
bit = 1 → WIN
bit = 0 → LOSE
```

This works because of the way the states are propagated.

Starting from:

```text
dp[0] = 0
```

the algorithm marks every state that can reach a losing state as `1`.

Any state that remains unmarked is therefore losing.

This is a neat example of using the **default state of a data structure as meaningful information**.

---

# 7. Why Precompute Everything?

The problem has a fixed maximum value of `n`.

If:

```text
MAX = 100000
```

then the program can calculate:

```text
0, 1, 2, 3, ..., 100000
```

once.

After that:

```text
winnerSquareGame(n)
```

does not perform the game DP again.

It simply looks up the already calculated answer.

This is called:

> **Static / global precomputation**

---

# 8. Why Is the Actual Function So Small?

After preprocessing:

```text
winnerSquareGame(n)
```

only needs to ask:

```text
Is bit n set?
```

Therefore the query itself is:

> **O(1)**

The expensive work has already been performed before the query.

---

# 9. `bitset` Concept

A normal DP could use:

```text
vector<bool>
vector<int>
bool array
```

But the state only has two possibilities:

```text
WIN
LOSE
```

Therefore only **one bit** is required.

A `bitset` stores exactly that.

For example:

```text
index:  0 1 2 3 4 5 6
value:  0 1 0 1 1 0 1
```

Each position represents one game state.

---

# 10. `bitset::set()` and `bitset::test()`

Two important operations are used.

### `set(i)`

Marks state `i` as:

```text
WIN
```

Conceptually:

```text
dp[i] = true
```

### `test(i)`

Checks whether the bit at position `i` is set.

Conceptually:

```text
if dp[i] == true
```

So:

```text
dp.test(i)
```

means:

> "Is state `i` already known to be winning?"

---

# 11. Why Use `MAX + 1`?

The valid states are:

```text
0 ... MAX
```

There are therefore:

```text
MAX + 1
```

states.

For:

```text
MAX = 100000
```

we need:

```text
100001 bits
```

---

# 12. Why `static`?

The DP table is shared by the class.

Instead of every `Solution` object having its own copy:

```text
Solution object 1 → dp
Solution object 2 → dp
Solution object 3 → dp
```

there is one shared table:

```text
             dp
              ↑
       ┌──────┴──────┐
       │             │
   Solution      Solution
```

For competitive programming, this allows the precomputed table to be reused.

---

# 13. Why `constexpr`?

The maximum value:

```text
MAX = 100000
```

is known at compile time.

`constexpr` tells C++ that this is a compile-time constant.

This is useful because `bitset` requires its size as a compile-time constant.

---

# 14. Why `inline static`?

Modern C++ allows a static data member to be defined directly inside the class using:

```text
inline static
```

Without getting too deep into linkage rules:

> `inline static` allows this single shared variable to be defined inside the class safely.

This is mainly a **C++ language feature**, not part of the game algorithm.

---

# 15. The Weird Lambda

The code contains something like:

```text
inline static bool init = []() {
    // preprocessing
    return false;
}();
```

This combines:

### Lambda

```text
[]() {
    ...
}
```

An unnamed function.

### Immediately Invoked Lambda

The final:

```text
()
```

calls the lambda immediately.

So:

```text
[]() {
    preprocessing
    return false;
}()
```

means:

```text
create lambda
     ↓
execute lambda immediately
     ↓
perform preprocessing
     ↓
store returned value in init
```

---

# 16. Why Use a Lambda Here?

The purpose is not the `bool init`.

The purpose is to make the preprocessing happen automatically during static initialization.

Conceptually:

```text
class starts
    ↓
static variables initialized
    ↓
lambda executes
    ↓
DP table gets filled
    ↓
winnerSquareGame() can now use it
```

The value returned by the lambda is irrelevant to the actual game.

The `bool init` is basically a vehicle used to trigger the computation.

---

# 17. Generating Perfect Squares

The inner loop generates:

```text
1²
2²
3²
4²
...
```

Instead of storing all squares separately, the root `j` is enough to generate them.

The condition:

```text
j² <= MAX - i
```

ensures:

```text
i + j² <= MAX
```

So the generated state never goes outside the precomputed range.

---

# 18. Why This Does Not Recalculate Squares From Scratch

The squares themselves are generated mathematically:

```text
1², 2², 3², ...
```

for every losing state.

The important repeated work isn't checking whether something is a square.

The actual DP transition is:

```text
for every losing state
    try every valid square
```

There can be approximately:

```text
√MAX
```

possible square moves for a state.

---

# 19. Complexity

Let:

```text
N = MAX
```

There are `N` possible states.

For each state, up to approximately `√N` squares can be considered.

Therefore preprocessing takes approximately:

> **O(N√N)**

The bitset uses:

> **O(N) bits**

which is much more compact than storing an `int` for every state.

The individual query:

```text
winnerSquareGame(n)
```

takes:

> **O(1)**

---

# 20. Comparison With Your Original Solution

| Feature           | Your Recursive DP             | This Approach                       |
| ----------------- | ----------------------------- | ----------------------------------- |
| Direction         | Top-down                      | Bottom-up / forward propagation     |
| Starting point    | Requested `n`                 | `0 ... MAX`                         |
| DP                | Memoization                   | Full precomputation                 |
| State calculation | On demand                     | All states                          |
| Transition        | `n → n - square`              | `lose → lose + square`              |
| Query time        | Depends on computed states    | **O(1)**                            |
| Preprocessing     | Only when needed              | Entire range                        |
| Typical storage   | `vector<int>`                 | `bitset`                            |
| Main idea         | "Can I reach a losing state?" | "What can reach this losing state?" |

---

# 21. Top-Down vs Reverse Propagation

### Your approach

```text
n
│
├── n - 1
├── n - 4
├── n - 9
└── ...
```

You recursively explore smaller states.

The question is:

> **Can I move to a state where the opponent loses?**

---

### This approach

```text
        LOSE
          │
     ┌────┼────┐
     ↓    ↓    ↓
   +1²  +2²  +3²
     ↓    ↓    ↓
    WIN  WIN  WIN
```

The question becomes:

> **If this state is losing, which states can move into it?**

Same game theory.

Different DP direction.

---

# 22. Why This Is a Cool Technique

This solution combines several independent ideas:

```text
Game Theory
     +
Dynamic Programming
     +
Reverse State Propagation
     +
Static Precomputation
     +
Bitset Compression
     +
Immediately Invoked Lambda
```

None of these ideas individually solves the problem.

The interesting part is how they are combined.

---

# 23. When Should You Think of This Approach?

This style is particularly useful when:

* The maximum input value is known.
* The state space is relatively small.
* There may be many queries.
* The same DP can be reused.
* Each state has only a small number of boolean outcomes.
* Precomputation is acceptable.

For example:

```text
MAX = 100000
```

is manageable.

But if:

```text
MAX = 10^9
```

then precomputing every state would obviously be impossible.

---

# 24. General Pattern to Remember

When you see a two-player game, first find:

```text
What is a losing state?
```

Then ask:

> If I know a state is losing, which states can move into it?

Those states are automatically winning.

This gives the reusable pattern:

```text
Known LOSE
    ↓
generate reverse moves
    ↓
mark WIN
    ↓
repeat
```

This pattern is useful beyond Stone Game IV.

---

# ⭐ Final Takeaway

Your original solution and this solution are **not two completely different algorithms**.

They are two views of the **same game-DP recurrence**.

Your solution says:

> **"For `n`, search for a move that makes the opponent lose."**

This solution says:

> **"Whenever I know a state is losing, mark every state that can move to it as winning."**

The first is more natural for learning and implementing the problem from scratch.

The second is a more aggressive optimization when the entire state range is small enough to precompute.

The biggest lesson is:

> **Don't memorize the bitset/lambda trick. Memorize the game-DP relationship.**

Once you understand that `WIN ⇔ exists a move to LOSE`, both implementations become just different ways of traversing the same state graph.
