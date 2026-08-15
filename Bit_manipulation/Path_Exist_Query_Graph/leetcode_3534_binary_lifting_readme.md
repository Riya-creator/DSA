# LeetCode 3534 --- Path Existence Queries in a Graph II

## 1. Binary Lifting --- The Core Idea

Binary lifting answers questions of the form:

> If I repeatedly follow the same transition, where will I be after `k`
> steps?

Instead of moving one step at a time, preprocess destinations for powers
of two:

-   `2^0 = 1` step
-   `2^1 = 2` steps
-   `2^2 = 4` steps
-   `2^3 = 8` steps
-   ...

Any number of steps can be represented using powers of two. For example,
`13 = 8 + 4 + 1`.

The mental model is:

-   level 0 → destination after 1 transition
-   level 1 → destination after 2 transitions
-   level 2 → destination after 4 transitions
-   level 3 → destination after 8 transitions

The important point is that the level `k` is **not** the number of
transitions. It represents `2^k` transitions.

------------------------------------------------------------------------

## 2. How to Detect Binary Lifting

Think about binary lifting when a problem has:

-   repeated movement
-   a deterministic next state
-   "after k moves"
-   k-th ancestor / successor
-   many queries on the same static structure
-   a query that could require walking through many states

The strongest signal is:

> There is a predictable next state, and the same transition is applied
> repeatedly.

This occurs in trees, functional graphs, arrays, teleportation problems,
successor problems, and state machines.

Do not associate binary lifting only with trees. The deeper pattern is
**repeated application of a deterministic transition**.

------------------------------------------------------------------------

## 3. The Hidden Transformation in This Problem

At first glance, the problem looks like a general graph problem:

> Two nodes are connected if their values differ by at most `maxDiff`.

A brute-force solution might compare every pair and build all edges.
That is `O(n^2)` and is already too expensive for `n` around `10^5`.

The key question is:

> Does sorting expose structure in this graph?

Yes.

After sorting:

`a[0] <= a[1] <= ... <= a[n-1]`

if a position `i` can reach a later position `j`, then every position
between `i` and `j` can also be reached from `i`.

So instead of storing every edge, store only:

> **the farthest reachable position from each position in one move.**

This is the critical graph-compression observation.

------------------------------------------------------------------------

## 4. Why Sorting Changes the Problem

Suppose:

`a[j] - a[i] <= maxDiff`

Because the array is sorted, every `x` between `i` and `j` satisfies:

`a[x] <= a[j]`

therefore:

`a[x] - a[i] <= maxDiff`

So the reachable positions form a continuous interval.

This means the graph does not need to be represented as a potentially
dense adjacency list.

Instead, conceptually define:

> `next[i]` = farthest sorted position reachable from `i` in one valid
> move.

This single transition captures the useful rightward reach.

------------------------------------------------------------------------

## 5. Finding the Farthest Position in O(n)

For every `i`, we need the largest `j` satisfying:

`a[j] - a[i] <= maxDiff`

Doing an independent search for every `i` can be `O(n log n)`, which is
acceptable, but there is an even better observation.

Because the array is sorted:

> As `i` moves right, the farthest valid `j` never needs to move left.

Therefore a two-pointer/sliding-window technique finds all `next[i]`
values in `O(n)` after sorting.

### Two-Pointer Detection Rule

Whenever you see:

> For every `i`, find the largest `j` satisfying some condition.

ask:

> If `i` increases, can the valid `j` only move forward?

If yes, two pointers may reduce an `O(n^2)` search to `O(n)`.

------------------------------------------------------------------------

## 6. Why We Do Not Need the Entire Graph

A common mistake is:

> The problem says graph, so I should build an adjacency list.

Not necessarily.

Graphs can often be represented implicitly.

Here, storing every valid edge is wasteful because the useful
information is summarized by the farthest reachable position.

General lesson:

> **Do not materialize information that can be represented by a smaller
> structure.**

This kind of compression is often the difference between an impossible
and feasible solution.

------------------------------------------------------------------------

## 7. From One Jump to Many Jumps

After preprocessing, we have a deterministic transition:

`i -> next[i]`

A query may require repeatedly following it:

`u -> next[u] -> next[next[u]] -> ...`

Doing this one step at a time can cost `O(n)` for one query.

With `q` large queries, that can become `O(nq)`.

Now the binary lifting pattern appears naturally.

------------------------------------------------------------------------

## 8. Building the Jump Table

Conceptually:

-   level 0 = destination after 1 jump
-   level 1 = destination after 2 jumps
-   level 2 = destination after 4 jumps
-   level 3 = destination after 8 jumps
-   ...

The reason the table can be built efficiently is:

> A `2^k` jump is two consecutive `2^(k-1)` jumps.

Therefore:

`2^k = 2^(k-1) + 2^(k-1)`

This is the entire recurrence behind binary lifting.

With `n` states and `O(log n)` levels:

-   preprocessing time: `O(n log n)`
-   memory: `O(n log n)`

------------------------------------------------------------------------

## 9. How a Query Uses Binary Lifting

Suppose we need to move from sorted position `u` to target `v`.

Try the largest jump first:

`2^LOG`, then `2^(LOG-1)`, ..., down to `1`.

For every level ask:

> If I take this jump, will I remain before the target?

If yes:

-   take it
-   add `2^k` to the number of transitions

If no:

-   skip it
-   try a smaller jump

This is essentially greedy binary decomposition.

------------------------------------------------------------------------

## 10. Why We Stop Before the Target

During the query, use the invariant:

> **The current position is the furthest position reached so far while
> still remaining strictly before the target.**

This makes the final check clean.

After all large jumps have been considered, check whether one more
normal transition can reach the target.

Because `next[i]` is the **farthest** position reachable in one move,
the final condition is conceptually:

> `next[current] >= target`

not only equality.

This is a common source of bugs.

If the farthest reachable position is beyond the target, the target is
still reachable because every position inside the reachable interval is
valid.

------------------------------------------------------------------------

## 11. Farthest vs Exact Destination

This distinction is extremely important.

`next[i]` does **not** mean:

> The only position I can reach.

It means:

> **The furthest position I can reach in one move.**

So if:

`next[i] = 10`

then every valid position from `i` through `10` is reachable in one
move.

This explains why a target smaller than `next[i]` can still be reached
immediately.

------------------------------------------------------------------------

## 12. Why We Can Normalize Queries

After sorting, every original index has a sorted position.

Convert:

`original index -> sorted position`

Then, if the first sorted position is greater than the second, swap
them.

Now every query can be treated as:

> Move from left to right.

This means only one directional jump table is necessary.

### General Optimization

If a problem is symmetric in two directions, ask:

> **Can I normalize the input so every query has one canonical
> direction?**

If yes, you may avoid maintaining separate left and right structures.

Some implementations instead keep both `jumpLeft` and `jumpRight`. That
is valid, but often more machinery than necessary.

------------------------------------------------------------------------

## 13. Why Another Solution May Have `jumpLeft`

A solution may preserve the original query direction.

If the destination is to the right, use right jumps.

If the destination is to the left, use left jumps.

That requires:

-   right jump table
-   left jump table
-   two query procedures

It is valid.

The normalized approach is often simpler:

> Swap the sorted endpoints so every query moves right.

This is a useful general problem-solving trick: **transform the input to
eliminate symmetric cases.**

------------------------------------------------------------------------

## 14. Top-Down Memoization vs Bottom-Up Binary Lifting

Binary lifting can be implemented in two common ways.

### Bottom-Up

Explicitly build:

-   level 0
-   level 1
-   level 2
-   ...

This is usually easier to visualize.

### Top-Down + Memoization

Define a function representing:

> Where do I end up after `2^k` transitions?

If that state has already been calculated, reuse it.

Otherwise calculate it recursively and store it.

This is still binary lifting.

The difference is implementation style:

> **Bottom-up DP vs top-down memoized DP.**

The mathematical recurrence is the same.

------------------------------------------------------------------------

## 15. Why Ordinary Memoization Is Not Enough

An initial instinct might be:

> Run DFS once and memoize the result for future queries.

The problem is that memoizing arbitrary source-target distances can
require `O(n^2)` states.

Binary lifting stores only strategically useful jump lengths:

`1, 2, 4, 8, 16, ...`

So the state count becomes:

`O(n log n)`

### General Lesson

When memoization seems to need too many states, ask:

> **Can I store only powers/doubling levels instead of every possible
> amount?**

This is the broader **doubling technique**.

------------------------------------------------------------------------

## 16. Binary Lifting vs Binary Search

They can both have a logarithmic loop, but they solve different
problems.

### Binary Search

Asks:

> Which position satisfies a condition?

Example:

> Find the first value greater than `X`.

### Binary Lifting

Asks:

> After repeatedly applying a transition, where do I end up?

Example:

> After `k` transitions from state `u`, where am I?

In this problem both ideas can potentially appear:

1.  Binary search can find the farthest valid position.
2.  Binary lifting handles repeated transitions.

Two pointers can replace the per-position binary searches and reduce
that preprocessing stage to `O(n)` after sorting.

------------------------------------------------------------------------

## 17. Complexity

Let:

-   `n` = number of nodes
-   `q` = number of queries

Sorting:

`O(n log n)`

Farthest reachable positions using two pointers:

`O(n)`

Jump table:

`O(n log n)`

Each query:

`O(log n)`

Overall:

`O(n log n + q log n)`

Space:

`O(n log n)`

This is suitable for large `n` and `q`.

------------------------------------------------------------------------

## 18. Common Wrong Approaches

### A. Build every graph edge

Pairwise construction costs `O(n^2)`.

**Lesson:** Numeric graph conditions often become simpler after sorting.

### B. DFS/BFS for every query

Repeated searches can become too expensive.

**Lesson:** Many queries on a static structure usually suggest
preprocessing.

### C. Follow `next` one step at a time

A single query can cost `O(n)`.

**Lesson:** Repeated deterministic transitions are a strong
binary-lifting signal.

### D. Store every source-target distance

Potentially `O(n^2)` memory.

**Lesson:** Look for compressed states rather than memoizing every pair.

### E. Treat level `k` as `k` jumps

Wrong.

Level `k` represents `2^k` jumps.

**Lesson:** Always explicitly associate:

`level k -> 2^k transitions`

------------------------------------------------------------------------

## 19. Binary Lifting Checklist

When reading a new problem, ask:

-   Is there a deterministic next state?
-   Do I repeatedly follow it?
-   Are there many queries?
-   Could one query take `O(n)` by normal walking?
-   Can I precompute destinations after powers of two transitions?
-   Is the transition static?
-   Can every required number of transitions be represented using powers
    of two?
-   Do I need extra information along the jump, such as min/max/sum?

If most answers are yes, consider binary lifting.

------------------------------------------------------------------------

## 20. Binary Lifting Can Store More Than Destinations

A jump table does not have to store only the destination.

Each jump can also store information accumulated during that jump:

-   minimum value
-   maximum value
-   sum
-   maximum edge weight
-   minimum edge weight
-   number of special nodes
-   whether a condition was violated

Then when two half-jumps are combined, their stored information can also
be combined.

This turns binary lifting into a much more general **doubling DP
technique**.

------------------------------------------------------------------------

## 21. A Deeper DP Interpretation

Binary lifting can be viewed as DP over jump length.

Instead of asking:

> What is the result after one transition?

we maintain:

> What is the result after `2^k` transitions?

The transition is based on:

`2^k = 2^(k-1) + 2^(k-1)`

So binary lifting is essentially:

> **DP where the transition count grows exponentially by powers of
> two.**

This viewpoint is useful because it connects binary lifting to other
doubling techniques instead of making it feel like an isolated
algorithm.

------------------------------------------------------------------------

## 22. The Full Reasoning Chain for LeetCode 3534

The intended thought process is:

1.  The graph appears potentially dense.
2.  Pairwise edge construction is too expensive.
3.  Sort values to expose monotonic structure.
4.  Reachable nodes from a position form a continuous interval.
5.  Store only the farthest reachable position.
6.  Use two pointers to compute all such positions efficiently.
7.  The graph has now become a deterministic jump transition.
8.  Queries may require many repeated transitions.
9.  Binary lifting precomputes powers-of-two transitions.
10. Each query greedily takes the largest safe jump.
11. Finish with one final reachability check.

The important part to remember is not the code.

The important transformation is:

> **Dense graph → sorted array → interval reachability → farthest
> transition → repeated transition → binary lifting.**

------------------------------------------------------------------------

## 23. Final Mental Template

When you see:

`state -> next state`

and the problem asks you to repeatedly follow it:

1.  Can I define one useful transition?
2.  Can I repeatedly apply it?
3.  Are there many queries?
4.  Would walking normally be too slow?
5.  Can I precompute `2^k` transitions?
6.  Can I answer a query by greedily combining those powers?

If yes, binary lifting is likely appropriate.

### One Sentence to Remember

> **Binary lifting is a way of replacing many repeated one-step
> transitions with a small number of precomputed power-of-two jumps.**

And for this problem:

> **Sorting exposes the one-step transition; binary lifting makes
> repeated use of that transition fast.**
