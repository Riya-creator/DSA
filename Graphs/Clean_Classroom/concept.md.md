# LeetCode 3568 — Minimum Moves to Clean the Classroom

## Problem Pattern

This problem is a classic example of:

> **Grid + shortest path + limited resource + collect-all-items state**

The important part is not the grid itself. The difficulty comes from the fact that reaching the same cell can represent completely different situations depending on:

- how much energy remains
- which litter has already been collected

This is a **state-space shortest-path problem**.

---

## 1. First Identify the Graph

Every non-obstacle classroom cell can be treated as a node in a graph.

From each cell, movement is possible in up to four directions:

- Up
- Down
- Left
- Right

Every movement costs exactly **1 move**.

Therefore, all graph edges have equal weight.

### Immediate pattern

If:

- you need the minimum number of moves
- every move has cost 1

then think:

> **BFS**

Dijkstra also works for equal edge weights, but BFS is simpler and more natural.

---

# 2. Why Ordinary Grid BFS Is NOT Enough

A normal grid shortest-path problem might only need:

> `(row, column)`

But this problem has additional information that affects what you can do next.

Imagine reaching the same cell twice:

### State A

- position = `(r, c)`
- energy = 8
- litter collected = `{A, B}`

### State B

- position = `(r, c)`
- energy = 2
- litter collected = `{A}`

These are clearly NOT equivalent.

From State A, you have many more possible moves and a different remaining objective.

Therefore:

> **Position alone cannot describe the state.**

---

# 3. The Critical State-Design Insight

Ask this whenever solving a complex BFS problem:

> **What information determines my future possibilities?**

For this problem, three things matter:

### 1. Position

Where am I?

- row
- column

### 2. Remaining Energy

How many more moves can I make before I need a recharge?

### 3. Collected Litter

Which litter cells have already been cleaned?

Therefore the conceptual BFS state is:

> **(row, column, energy, litter-state)**

This is the biggest insight in the problem.

---

# 4. Why `visited[row][column]` Is Wrong

In ordinary grid BFS, we often do:

> "I've visited this cell, so never visit it again."

That logic fails here.

Suppose we reach cell `(3,4)` with:

- energy = 1
- litter state = `0011`

Later we reach `(3,4)` with:

- energy = 7
- litter state = `0111`

The second state can have completely different future possibilities.

Therefore:

> **A cell is not simply visited or unvisited.**

Instead, a state is visited only when the complete combination has been seen.

Conceptually:

> `visited[position][energy][litter-state]`

The exact implementation can vary, but the idea is what matters.

---

# 5. Bitmask — The Key Trick

The number of litter cells is small.

That is the signal to consider a **bitmask**.

Suppose there are 4 litter cells:

- L0
- L1
- L2
- L3

Assign one bit to each:

- L0 → bit 0
- L1 → bit 1
- L2 → bit 2
- L3 → bit 3

Then one integer can represent the entire litter state.

For example:

| Mask | Meaning |
|---|---|
| `0000` | no litter remaining / all collected |
| `0001` | one particular litter remains |
| `0011` | two particular litters remain |
| `1010` | two particular litters remain |
| `1111` | all litters remain |

There are only:

> **2^K possible masks**

where K = number of litter cells.

With at most 10 litter cells:

> 2^10 = 1024

That is very manageable.

---

# 6. Why Bitmasking Is So Useful

Without a bitmask, you might try storing a collection such as:

- set of collected litter coordinates
- vector of collected litter IDs
- string representing collected objects

These approaches can work, but they make state comparison and visited-state management more complicated.

A bitmask turns the entire collection state into one integer.

This gives:

- fast updates
- fast comparisons
- compact state representation
- easy visited-state indexing

### General Bitmask Pattern

If item `k` corresponds to bit `k`:

> Turn bit ON → item is represented as collected

or:

> Turn bit OFF → item is represented as remaining

Both conventions are valid.

The important thing is to choose one convention and use it consistently.

---

# 7. Two Valid Mask Conventions

There are two common ways to design the mask.

## Convention A — Collected Items

A bit of `1` means:

> This litter has been collected.

Example:

`0101`

means litter 0 and litter 2 have been collected.

Completion condition:

> All required bits are 1.

---

## Convention B — Remaining Items

A bit of `1` means:

> This litter still needs to be collected.

Example:

`0101`

means litter 0 and litter 2 remain.

Completion condition:

> Mask becomes `0000`.

This convention is particularly clean for this problem because:

> **mask == 0 → everything is clean**

### Important Tip

Neither convention is inherently "more correct."

What matters is consistency.

---

# 8. Assigning IDs to Litter

Before BFS, scan the classroom.

Whenever an `L` is found:

> assign it a unique integer ID.

For example:

- first L → ID 0
- second L → ID 1
- third L → ID 2
- ...

You can maintain a mapping from:

> `(row, column) → litter ID`

This lets you quickly determine which bit should change when BFS enters a litter cell.

---

# 9. What Happens During a Move?

Every transition starts with:

> Move to a neighboring cell.

That costs:

> **1 move**

Then inspect the destination cell.

---

## Normal Cell

Nothing special happens.

Energy decreases by one.

Litter state stays unchanged.

---

## Litter Cell

Energy decreases by one.

The corresponding litter bit is updated.

This means:

> "We have now collected this litter."

---

## Recharge Cell

When entering the recharge cell, energy is restored to the maximum.

The litter state does not change.

---

# 10. Energy Is Part of the State

This is one of the most important ideas.

Consider:

- `(r,c,energy=1)`
- `(r,c,energy=8)`

They cannot be merged into one state.

The second state can travel much farther before needing a recharge.

Therefore:

> **Energy must be included in the BFS state and visited-state definition.**

---

# 11. Why Recharge Cells Make Normal DFS/Visited Logic Dangerous

A common first attempt is:

> "Mark a cell visited and never come back."

That can be wrong.

You may need to return to a previously visited location after:

- collecting different litter
- having different remaining energy
- reaching a recharge point

Therefore, do NOT think:

> "Have I visited this coordinate?"

Think:

> "Have I visited this exact state?"

This distinction appears in many advanced graph problems.

---

# 12. Why the Original Global Litter Counter Fails

A global counter such as:

> `l++`

looks convenient but is incorrect for branching search.

Imagine two branches:

```text
        S
       /      L1   L2
```

One DFS branch collects L1.

Another branch collects L2.

A global counter remembers both and effectively mixes the histories.

But those branches represent separate possible paths.

### General lesson

> **Never use a global mutable variable to represent branch-specific search state unless you carefully backtrack it.**

Better:

> Make branch-dependent information part of the state.

The bitmask solves exactly this problem.

---

# 13. Why Scanning the Entire Grid Repeatedly Is Unnecessary

A function that repeatedly scans the whole classroom to ask:

> "Are there any L cells remaining?"

is inefficient and unnecessary.

The litter state is already encoded in the mask.

So completion can be checked directly using the mask.

### General optimization lesson

If some property can be represented compactly in your state, don't repeatedly recompute it from the entire input.

This is a classic **state compression** technique.

---

# 14. Why BFS Gives the Minimum

BFS explores states level by level.

Think of:

- Level 0 → 0 moves
- Level 1 → 1 move
- Level 2 → 2 moves
- Level 3 → 3 moves
- ...

Therefore, the first time BFS reaches a state where:

> all litter has been collected

that distance is automatically the minimum number of moves.

No separate shortest-distance calculation between litter cells is necessary.

---

# 15. Why "Distance Between Litter Cells" Is Not Enough

A tempting approach is:

1. Find distance from S to every L.
2. Find distance between every pair of L cells.
3. Solve an ordering problem over the litter cells.

This can be useful in some problems, but energy makes this problem more complicated.

The feasibility of moving from one place to another depends on:

- current energy
- recharge locations
- current position
- already collected litter

Therefore, simply knowing:

> `distance(L1, L2)`

does not fully describe the transition.

### General lesson

Before compressing a grid into special nodes, ask:

> **Does the shortest distance between those nodes preserve all the information needed by the original problem?**

If not, keep the full state-space search.

---

# 16. Why Dijkstra Is Not Necessary

Dijkstra is designed for graphs with non-negative edge weights.

Here every move costs exactly:

> 1

So the graph is unweighted.

Therefore:

> **BFS is enough.**

### Recognition trick

Whenever you see:

> "minimum number of moves / steps / operations"

and every operation costs the same:

> Think BFS before Dijkstra.

Use Dijkstra when edge costs differ.

---

# 17. State Explosion — The Constraint Check

A very important competitive-programming habit:

> **Never design a state without checking how many states exist.**

Suppose:

- grid = M × N
- maximum energy = E
- litter count = K

Then the number of possible states is roughly:

> **M × N × E × 2^K**

Each state has at most four transitions.

So the complexity is approximately:

> **O(M × N × E × 2^K)**

and the memory requirement is of the same order in the worst case.

---

# 18. Why the Bitmask Is Feasible Here

The key is that K is small.

For K = 10:

> 2^10 = 1024

So the litter dimension is manageable.

This is one of the biggest signals that the problem expects a bitmask.

### Pattern to memorize

If a problem says:

> "There are at most 10/12/15 special objects"

immediately ask:

> **Can I represent subsets of these objects using a bitmask?**

---

# 19. The Complete Mental Algorithm

Before coding, mentally simulate:

### Step 1

Scan the grid.

Find:

- starting position
- number of litter cells
- ID of every litter cell

### Step 2

Create the initial litter mask.

### Step 3

Create a BFS queue containing the starting state:

> position + energy + mask

### Step 4

For every state:

Look at four neighboring cells.

### Step 5

Reject:

- out-of-bounds cells
- obstacles
- moves that cannot be made because energy is insufficient

### Step 6

Update the state according to the destination:

- normal cell → consume energy
- litter → update mask
- recharge → restore energy

### Step 7

If this exact state has already been visited:

> skip it.

Otherwise:

> mark it visited and push it into BFS.

### Step 8

When the litter mask represents:

> **all litter collected**

return the BFS distance.

### Step 9

If BFS finishes without reaching that state:

> return `-1`.

---

# 20. How to Detect This Pattern in Future Problems

This is probably the most valuable part to remember.

When reading a new problem, look for these clues.

## Clue 1 — Grid movement

Words like:

- move up/down/left/right
- neighboring cells
- maze
- classroom
- board
- grid

→ Think **graph/BFS/DFS**.

---

## Clue 2 — Minimum moves

Words like:

- minimum steps
- minimum moves
- shortest number of operations

→ Think **BFS** if every move costs the same.

---

## Clue 3 — Small number of special objects

Words like:

- collect all keys
- visit all targets
- clean all cells
- activate all switches
- collect treasures

and the number of objects is small.

→ Think **bitmask**.

---

## Clue 4 — A resource changes

Examples:

- energy
- fuel
- health
- remaining moves
- battery
- number of jumps

→ Resource may need to become part of the state.

---

## Clue 5 — Same position can have different possibilities

Ask:

> "If I reach the same cell twice, could the future be different?"

If YES:

> `visited[row][col]` is probably insufficient.

Look for additional state dimensions.

---

# 21. The Golden State Rule

For difficult BFS/DP problems, remember:

> **A state should contain exactly the information required to determine all possible future transitions.**

Too little information:

> Incorrect.

Too much information:

> Potentially enormous state space.

The art is finding the **minimum sufficient state**.

For this problem:

> **position + energy + litter mask**

is the important state.

---

# 22. Common Wrong Approaches

### ❌ Global litter counter

Fails because different DFS/BFS branches have different histories.

### ❌ `visited[row][col]`

Fails because energy and collected litter change the state.

### ❌ Repeatedly scanning the grid for remaining litter

Unnecessary once litter state is encoded.

### ❌ Only calculating distances between litter cells

Doesn't preserve the energy/recharge state.

### ❌ DFS for minimum path

Possible with exhaustive search, but potentially exponential and much harder to manage correctly.

### ❌ Dijkstra by default

Works conceptually for unit weights, but BFS is simpler.

### ❌ Hardcoding the number of litter cells

Never assume the input has exactly a particular number unless the constraints explicitly guarantee it.

---

# 23. Bitmask Operations Worth Memorizing

These are useful far beyond this problem.

Suppose item `k` corresponds to bit `k`.

### Add / mark an item

> `mask |= (1 << k)`

### Remove / clear an item

> `mask &= ~(1 << k)`

### Check whether an item exists

> `(mask & (1 << k)) != 0`

### Toggle an item

> `mask ^= (1 << k)`

### Number of represented items

> `popcount(mask)`

### All K bits set

> `(1 << K) - 1`

These operations are basically the bread-and-butter of subset-state problems.

---

# 24. A Useful Interview/Contest Thought Process

Instead of immediately coding, ask these questions in order:

### Q1
What is the graph?

→ Classroom cells.

### Q2
What is the cost of an edge?

→ One move.

### Q3
What algorithm gives shortest path?

→ BFS.

### Q4
Is position alone enough?

→ No.

### Q5
What else changes?

→ Energy and collected litter.

### Q6
Can the litter set be compressed?

→ Yes, because the number of litter cells is small.

### Q7
What represents the set?

→ Bitmask.

### Q8
What is the complete state?

→ Position + energy + mask.

### Q9
What does visited mean?

→ This exact state has already been processed.

### Q10
When do we stop?

→ All litter has been collected.

This sequence is a reusable problem-solving framework.

---

# 25. The Big Pattern to Add to Your DSA Brain

When you see:

> **Shortest path + grid + small number of collectible/required objects + changing resource**

immediately think:

> **State-space BFS**

with a state resembling:

> **(position, resource, bitmask)**

This pattern appears in problems involving:

- keys and doors
- collecting all treasures
- cleaning rooms
- visiting required targets
- activating switches
- masks of visited cities/items
- limited fuel/energy
- grid puzzles with changing conditions

The exact dimensions change, but the underlying idea is the same.

---

# Final Takeaway

The problem initially looks like:

> "Find a path through a grid."

But that is misleading.

The actual problem is:

> **Find the shortest path through a graph of states.**

A physical classroom cell is only part of the state.

The real state is:

> **Where am I + how much energy do I have + what litter remains?**

Once that realization happens:

**Grid → Graph → BFS → State expansion → Bitmask → Shortest answer**

That is the core lesson of LeetCode 3568.
