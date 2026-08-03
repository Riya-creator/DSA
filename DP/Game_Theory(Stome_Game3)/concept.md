# Comprehensive Guide: Dynamic Programming & Minimax in Stone Game III

---

# 1. Core Problem Concept & Minimax Mechanics

LeetCode **1406 (Stone Game III)** is a **zero-sum, two-player game** where both Alice and Bob play **optimally**.

Both players know the complete game state and always choose the move that maximizes their own final score.

Instead of storing:

- Alice's score
- Bob's score

we store only **one value**:

> **Current Player's Advantage over the Opponent**

This is the biggest trick behind most minimax DP problems.

---

## Relative Advantage Formulation

At any state,

```text
Advantage = Current Player Score − Opponent Score
```

Suppose we are currently standing at index `i`.

The current player may take:

- 1 stone
- 2 stones
- 3 stones

If he takes `X` stones,

```text
Immediate Gain = Sum of first X stones
```

After taking them,

the opponent starts playing from

```text
i + X
```

Since the opponent now becomes the current player,

their future advantage works **against us**.

Therefore,

```text
Our Advantage
=
Immediate Gain
− Opponent Advantage
```

Hence,

\[
dp(i)=\max_{1\le X\le3}
\left(
\sum_{k=0}^{X-1} stoneValue[i+k]
-
dp(i+X)
\right)
\]

This single recurrence completely represents the game.

---

# 2. Why Pure Recursion Gives TLE

A recursive solution explores every possible decision.

```
                     solve(0)
              /         |          \
        solve(1)    solve(2)    solve(3)
        / |  \       / |  \      / |  \
      s2 s3 s4     s3 s4 s5    s4 s5 s6
```

Every state generates at most **3 recursive calls**.

---

## Exponential Explosion

If every level creates 3 new calls,

the recursion grows like

```
3 × 3 × 3 × 3 × ...
```

which becomes

\[
O(3^N)
\]

For

```
N = 50000
```

this is practically impossible.

Hence,

**Time Limit Exceeded (TLE).**

---

## Overlapping Subproblems

Notice

```
solve(3)
```

is reached from multiple paths.

Example:

```
0 -> 1 -> 3

0 -> 2 -> 3

0 -> 3
```

So

```
solve(3)
```

gets recomputed again and again.

This repeated work is the real reason recursion becomes exponential.

---

# 3. Dynamic Programming Fix

The idea is simple.

> Solve every state **only once**.

Store the answer.

Whenever that state appears again,

simply reuse it.

This reduces complexity from

```
O(3^N)
```

to

```
O(N)
```

---

# 4. Top-Down DP (Memoization)

## Idea

Start from the original question.

```
solve(0)
```

Whenever recursion needs another state,

compute it.

If that state was already computed,

return it immediately.

---

## Workflow

```
solve(0)

↓

Needs solve(1)

↓

Needs solve(4)

↓

Store answer

↓

Reuse later whenever needed
```

Only required states are computed.

This is called

> Lazy Computation

---

## Complexity

Time

```
O(N)
```

Space

```
O(N)
```

because of

- recursion stack
- DP array

---

## Drawback

Very deep recursion.

For very large input,

the recursion stack may overflow.

Example:

```
N = 50000
```

This can cause

```
Segmentation Fault
```

even though time complexity is optimal.

---

# 5. Bottom-Up DP (Tabulation)

Instead of asking

```
"What is solve(0)?"
```

we ask

```
"What is the smallest state I already know?"
```

The smallest known state is

```
dp[N]=0
```

because no stones remain.

Now compute

```
dp[N-1]

↓

dp[N-2]

↓

...

↓

dp[0]
```

Every required future answer is already available.

No recursion is needed.

---

## Why Reverse Loop?

Observe recurrence.

```
dp[i]
```

needs

```
dp[i+1]

dp[i+2]

dp[i+3]
```

Future states.

Therefore,

future states must already exist.

Hence,

iterate

```
for(i=N-1;i>=0;i--)
```

Never

```
0 → N
```

because dependencies wouldn't be ready.

---

## Complexity

Time

```
O(N)
```

Space

```
O(N)
```

---

# 6. Converting Memoization into Tabulation

Whenever converting recursive DP into iterative DP, follow this checklist.

---

## Step 1 — Identify State

Look at changing recursion parameters.

Example

```
solve(index)
```

Only

```
index
```

changes.

Hence,

```
State = index
```

---

## Step 2 — Create DP Table

```
vector<int> dp(n+4);
```

Meaning

```
dp[i]

=

maximum advantage starting from index i
```

---

## Step 3 — Convert Base Case

Recursive

```
if(index>=n)
    return 0;
```

becomes

```
dp[n]=0

dp[n+1]=0

dp[n+2]=0

dp[n+3]=0
```

Extra padding removes boundary checks.

---

## Step 4 — Decide Loop Direction

Observe dependencies.

```
dp[i]

depends on

dp[i+1]

dp[i+2]

dp[i+3]
```

Future values.

Hence,

loop backwards.

```
for(i=n-1;i>=0;i--)
```

---

## Step 5 — Replace Recursive Calls

Replace

```
solve(i+1)
```

with

```
dp[i+1]
```

Similarly,

```
solve(i+2)

↓

dp[i+2]

solve(i+3)

↓

dp[i+3]
```

Nothing else changes.

---

# 7. Space Optimization

Look carefully at the recurrence.

```
dp[i]
```

only needs

```
dp[i+1]

dp[i+2]

dp[i+3]
```

It never needs

```
dp[i+4]

dp[i+5]

...

dp[N]
```

again.

So why keep the whole array?

---

## Sliding Window Observation

Current computation only depends on

```
next 3 states
```

Therefore,

instead of

```
dp[0...N]
```

store only

```
next1 = dp[i+1]

next2 = dp[i+2]

next3 = dp[i+3]
```

After computing current state,

shift them.

```
next3 = next2

next2 = next1

next1 = current
```

Exactly like a sliding window.

---

## Space Complexity

Before

```
O(N)
```

After

```
O(1)
```

Time remains

```
O(N)
```

---

# 8. Mental Model

Think of the game like this.

```
Current Player

↓

Take 1/2/3 stones

↓

Earn Immediate Score

↓

Opponent starts playing

↓

Opponent will also play perfectly

↓

Subtract opponent's best advantage

↓

Choose the move giving maximum advantage
```

Everything revolves around

```
Current Gain
−
Opponent's Best Future Gain
```

That is exactly what Minimax represents.

---

# 9. Common Mistakes

### Mistake 1

Trying to store Alice's score and Bob's score separately.

Instead,

store only

```
Current Player Advantage
```

---

### Mistake 2

Adding future DP instead of subtracting.

Wrong

```
take + dp[next]
```

Correct

```
take - dp[next]
```

because

```
dp[next]
```

belongs to the opponent.

---

### Mistake 3

Iterating DP from left to right.

Current state depends on future states.

Always iterate

```
N-1

↓

0
```

---

### Mistake 4

Forgetting padding.

Without padding,

```
dp[i+3]
```

may go out of bounds.

Using

```
dp(n+4)
```

avoids unnecessary boundary checks.

---

### Mistake 5

Thinking recursion and memoization are different algorithms.

Memoization is simply

```
Recursion
+
Caching
```

---

# 10. Complexity Summary

| Approach | Time | Auxiliary Space | Main Issue |
|-----------|------|-----------------|------------|
| Pure Recursion | **O(3^N)** | **O(N)** (Call Stack) | Massive repeated computations → TLE |
| Top-Down Memoization | **O(N)** | **O(N)** DP + **O(N)** Stack | Possible Stack Overflow |
| Bottom-Up DP | **O(N)** | **O(N)** | Reliable iterative solution |
| Space Optimized DP | **O(N)** | **O(1)** | Optimal solution |

---

# Key Takeaways

- Convert a two-player game into a **score difference** problem.
- Store **Current Player Advantage**, not both players' scores.
- Minimax recurrence is:

\[
dp(i)=
\max
(
\text{Current Gain}
-
dp(next)
)
\]

- Pure recursion is exponential because of overlapping subproblems.
- Memoization ensures each state is solved exactly once.
- Bottom-up computes states in reverse dependency order.
- If only a few future states are needed, use **rolling variables** for **O(1)** space.
- Always think in terms of **"What is the maximum advantage I can guarantee from this state?"**
