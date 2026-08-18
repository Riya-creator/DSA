# LeetCode 1563 — Stone Game V
## DP State Design, Prefix Sums, Minimax Thinking & Common Pitfalls

---

## 1. The Most Important Part: Choosing the DP State

For this problem, the hardest part is **not writing the recurrence**. It is deciding what information completely describes a subproblem.

A good DP state must answer:

> “If I pause the game at this point, what information do I need so that I can calculate the answer from here without knowing how I reached here?”

This leads to a very important DP principle:

### A DP state must uniquely identify the remaining problem.

If two different situations can produce the same DP key, but have different possible future decisions, then the state is incomplete.

### The key questions to ask when designing a state

1. **What portion of the array is still active?**
2. **What information affects the sum of the left and right portions?**
3. **Does the way I reached this state affect future decisions?**
4. **Can two different intervals accidentally map to the same DP entry?**
5. **Can one parameter be derived from another instead of being stored explicitly?**

For Stone Game V, the remaining interval is fundamental.

A state must distinguish different combinations of:

- left boundary
- right boundary
- the effective previous boundary when needed for calculating the left sum

A particularly useful observation is that the “previous boundary” is tied to the current interval's left boundary. Therefore, it does not necessarily need to become a separate DP dimension.

This is a classic example of **state compression through an invariant**.

---

# 2. Why the State Must Represent the Whole Interval

Suppose you try to identify a state using only:

- the current starting position
- the previous partition position

That can look reasonable initially.

But imagine two situations:

- same starting position
- same previous partition
- different ending positions

These are **not the same subproblem**.

Why?

Because the available elements to the right are different, which means:

- different possible partition points
- different right-side sums
- different future states
- potentially different optimal scores

Therefore, two different intervals must never share the same DP value.

### DP collision principle

If:

> `State A != State B`

but both map to:

> `dp[same key]`

then the DP is invalid.

This is one of the most important debugging techniques for multidimensional DP.

Whenever you design a state, actively try to construct:

> “Can two different recursive calls have the same DP indices?”

If yes, your state probably needs more information.

---

# 3. History vs State

A common misconception in recursive DP is:

> “I need to remember how I reached this state.”

Usually, you don't.

DP does **not** care about the complete history.

It only cares about the information that can affect future decisions.

For this problem:

### Unnecessary information

The exact sequence of partitions Alice previously selected.

### Necessary information

The current remaining interval and the information required to calculate its valid sums.

This is the core idea behind **overlapping subproblems**:

Different histories can eventually lead to the same mathematical state.

Once that happens, their future answer is identical, so the result can be reused.

---

# 4. Prefix Sum Is Essential Here

Every possible partition requires calculating:

- sum of the left part
- sum of the right part

Doing this directly for every partition would repeatedly scan portions of the array.

Prefix sums turn these calculations into constant-time operations.

### General idea

A prefix sum stores:

> sum of elements from the beginning up to a particular index.

Then the sum of any contiguous range can be obtained using a subtraction of prefix values.

For this problem, that means every candidate partition can quickly determine:

- left sum
- right sum

without repeatedly traversing the array.

### Prefix sum tip

Whenever a problem repeatedly asks:

> “What is the sum of this subarray?”

think:

> **Prefix Sum**

especially when the array values do not change.

---

# 5. Understand the Game Before Writing the Recurrence

At every partition, the array is divided into:

- left portion
- right portion

The rules depend entirely on comparing their sums.

### Case 1 — Left sum < Right sum

Alice is forced to keep the left portion.

Therefore:

- Alice gains the left sum immediately.
- The next recursive problem is the left portion.

### Case 2 — Left sum > Right sum

Alice is forced to keep the right portion.

Therefore:

- Alice gains the right sum immediately.
- The next recursive problem is the right portion.

### Case 3 — Left sum == Right sum

Alice can choose either side.

Therefore:

- evaluate both possibilities
- take the better future result for Alice

This is where the problem becomes a **maximization DP**.

---

# 6. The Critical Recurrence Insight

A very easy mistake is to calculate only the result of the recursive call.

But Alice receives stones **at the current partition** before the game continues.

Therefore, conceptually every transition looks like:

> **current stones obtained + best answer from the remaining subproblem**

Not simply:

> best answer from the remaining subproblem

This distinction is extremely important in game DP.

### Mental checklist

For every transition, ask:

1. What does Alice gain immediately?
2. What state remains afterward?
3. What is the best result from that remaining state?
4. What is the total of the immediate gain plus the future result?

---

# 7. Why Every Possible Partition Must Be Considered

An early approach might try to find one “best-looking” partition, such as the partition where the smaller side is largest.

That is a **greedy assumption**.

But the game is not asking:

> “Which partition gives the largest immediate amount?”

The partition also determines the **future subproblem**.

A partition with a smaller immediate gain can potentially lead to a much better future score.

Therefore:

> Every valid partition must be considered.

For each partition:

1. calculate both sums
2. determine which side Alice is allowed to keep
3. calculate the resulting future state
4. add the current gain
5. compare this result against the other partition choices

This is the central reason the solution is DP rather than a simple greedy algorithm.

---

# 8. Minimax / Game-DP Perspective

Although the problem involves two players, the recurrence can be viewed primarily from Alice's perspective.

At each state:

- Alice chooses a partition.
- The rules determine which side survives.
- If the sums are equal, Alice chooses whichever surviving side gives her the better result.

Therefore, the DP state stores:

> **The maximum number of stones Alice can obtain from this state onward.**

This is a useful pattern in game problems:

### Ask:

> “What is the value of this state assuming the current player plays optimally?”

Once that definition is clear, the recurrence becomes much easier to derive.

---

# 9. Why the Ending Boundary Matters

One of the biggest lessons from this problem is that the **range itself is part of the state**.

Consider two recursive calls that start at the same position but end at different positions.

Even if their starting information is identical, they can have:

- different total sums
- different partition choices
- different forced directions
- different future possibilities

So:

> Same starting point ≠ same DP state.

A complete interval is generally identified by:

> **start + end**

This is a common pattern in interval DP.

---

# 10. Recognizing Interval DP

Stone Game V has a strong interval-DP structure.

Whenever a problem repeatedly asks you to:

- choose a split inside a range
- divide the range into two parts
- recurse on one of the resulting ranges
- find the best result

you should immediately consider:

> **Interval DP**

Typical state form:

> answer for interval `[l, r]`

The current partition then acts as the transition.

### Interval DP checklist

If you see:

- subarray
- split
- left/right segment
- recursive range
- best answer

think:

> `DP[l][r]`

before trying more complicated state designs.

---

# 11. State Compression Through Invariants

An important advanced technique appears in this problem.

Initially, you may think:

> “I need start, end, and previous partition as three dimensions.”

But inspect the relationship between them.

If the previous partition is always immediately before the current active interval, then:

> previous boundary = start boundary - 1

That means the previous boundary is **not independent information**.

Whenever one parameter can always be derived from another, storing both is unnecessary.

### General DP optimization rule

If:

> `A = f(B)`

for every valid state, then storing both `A` and `B` may be redundant.

This can reduce:

> 3D DP → 2D DP

and can dramatically improve memory usage.

This technique is called exploiting an **invariant** or **state dependency**.

---

# 12. Common Mistakes to Watch For

## Mistake 1: Greedily choosing the “best” partition

Choosing the split with the largest immediate smaller side is not sufficient.

The future recursive result matters.

---

## Mistake 2: Forgetting the immediate score

The answer from a transition is not just the recursive answer.

It includes the stones Alice obtains at the current split.

---

## Mistake 3: Treating equality like one of the inequality cases

Equal sums give Alice a choice.

Both branches need to be evaluated.

---

## Mistake 4: Incomplete DP state

If two different intervals can map to the same DP entry, the state is invalid.

Always test your state against this question:

> “Can different recursive calls collide here?”

---

## Mistake 5: Adding unnecessary dimensions

The opposite mistake also happens.

Do not store every variable just because it appears in the recursive function.

Check whether one variable can be derived from another.

---

## Mistake 6: Mixing recursion parameters with DP identity

A recursive function may receive helper parameters that are useful for computation.

That does **not** automatically mean every parameter belongs in the DP key.

The DP key should contain only information that uniquely determines the future problem.

---

# 13. A Powerful Way to Design DP States

Before writing any code, write this sentence:

> **“DP[state] means ______.”**

For this problem, your sentence should describe:

- exactly which interval is active
- what the stored value represents
- whose score is being maximized

If you cannot write this sentence clearly, the state is probably not ready.

Then ask:

### State validation test

For every pair of recursive calls:

> If their DP keys are equal, must their answers always be equal?

If the answer is **no**, the DP state is missing information.

If the answer is **yes**, the state is likely valid.

This is one of the best practical techniques for debugging DP design.

---

# 14. Recursive Solution → Memoization → DP

A clean way to develop this solution is:

### Step 1: Build the brute-force recursion

Try every possible partition.

Do not optimize yet.

---

### Step 2: Define the state clearly

Identify the exact interval represented by a recursive call.

---

### Step 3: Find overlapping subproblems

Check whether different partition choices can lead to the same interval.

They can.

That is where DP becomes useful.

---

### Step 4: Memoize

Store the answer for each unique interval.

---

### Step 5: Analyze complexity

If there are approximately `O(n²)` interval states and each state tries `O(n)` partitions, the resulting DP has roughly:

- **Time:** `O(n³)`
- **Space:** `O(n²)`

Prefix sums make each partition's sum calculation `O(1)`, which is crucial for keeping the transition efficient.

---

# 15. A Mental Model for Debugging Your DP

When your solution gives a wrong answer, don't immediately change random lines.

Instead, inspect these layers in order:

### Layer 1 — State

Does the DP state uniquely identify the subproblem?

### Layer 2 — Transition

Are all possible partitions considered?

### Layer 3 — Rules

Are `<`, `>`, and `==` handled correctly?

### Layer 4 — Immediate score

Did you add the stones obtained at the current partition?

### Layer 5 — Future state

Does the recursive/DP transition represent exactly the remaining interval?

### Layer 6 — Memoization

Are you storing the result under the correct state?

This debugging order is much faster than blindly modifying the recurrence.

---

# 16. General DP Lessons From This Problem

### Lesson 1

**State design comes before optimization.**

A fast DP with a wrong state is still wrong.

### Lesson 2

**The state should describe the future, not the past.**

You don't need the entire history.

### Lesson 3

**Every DP key must uniquely identify the answer.**

No two genuinely different subproblems should share one DP entry.

### Lesson 4

**Look for invariants.**

A parameter that can be derived from another parameter does not necessarily deserve another DP dimension.

### Lesson 5

**Greedy immediate gain is dangerous when the decision changes the future state.**

Always inspect the recursive consequence of a choice.

### Lesson 6

**Prefix sums are often the missing optimization in interval problems.**

They turn repeated range-sum calculations into constant-time operations.

---

# 17. Quick Revision Cheat Sheet

| Concept | Key Idea |
|---|---|
| Prefix Sum | Fast range-sum calculation |
| DP State | Must uniquely identify the remaining problem |
| History | Usually unnecessary if the current state contains all future-relevant information |
| Interval DP | Natural when repeatedly splitting `[l, r]` |
| Partition | Every possible split must be considered |
| `<` | Keep left side |
| `>` | Keep right side |
| `==` | Evaluate both sides |
| Transition | Immediate gain + future optimal result |
| Greedy | Not reliable because the split affects future states |
| State Compression | Remove parameters that are derivable from others |
| Memoization | Cache answers for repeated interval states |
| Expected DP Complexity | `O(n²)` states × `O(n)` transitions = `O(n³)` |

---

# 18. Final Takeaway

The biggest lesson from Stone Game V is **not the recurrence itself**.

It is learning how to ask:

> **“What exactly defines one unique subproblem?”**

Once that is correct:

1. Prefix sums give fast partition sums.
2. Every partition can be evaluated.
3. The game rules determine the surviving side.
4. The current gain is added to the future result.
5. Equal sums create two possible transitions.
6. Repeated intervals are memoized.
7. Redundant state variables can be removed using invariants.

That thought process is reusable far beyond this one LeetCode problem.

When a DP problem feels confusing, pause and define the state in plain English first. If you can explain exactly what `DP[l][r]` means without mentioning how you arrived there, you're usually on the right track.
