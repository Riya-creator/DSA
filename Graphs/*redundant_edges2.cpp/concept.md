# Leetcode 685 — Redundant Connection II

---

# 🔥 Core Problem Understanding

We are given a directed graph which was originally a rooted tree.

Then ONE extra edge was added.

We need to remove ONE edge such that the graph becomes a valid rooted tree again.

---

# 🌳 What is a Valid Rooted Tree?

A rooted tree must satisfy:

1. Exactly one root
2. Every node except root has exactly ONE parent
3. No cycles
4. All nodes connected

---

# ⚠️ The 2 Possible Violations

Only TWO things can go wrong after adding an extra edge:

| Violation | Meaning |
|---|---|
| Cycle | Loop exists |
| Multiple Parents | A node has indegree > 1 |

---

# 🧠 Biggest Insight

This is NOT just a DSU problem.

This is:

```text
Directed Graph Validation
+
Parent Constraint
+
Cycle Detection
```

Most people fail because they only think about cycle detection.

---

# 🚨 Why Normal DSU Alone Fails

DSU works beautifully for:

- Undirected cycle detection

But this problem is DIRECTED.

Example:

```text
1 → 3
2 → 3
```

No cycle exists.

But graph is still invalid because node `3` has two parents.

DSU alone cannot detect this.

---

# 🔥 Two Different "Parents"

This question has TWO different parent concepts.

---

## 1. Graph Parent

Represents actual incoming edge.

Example:

```text
1 → 3
```

means:

```cpp
graphParent[3] = 1;
```

Used for:
- detecting multiple parents

---

## 2. DSU Parent

Represents component representative/root.

Used for:
- cycle detection

---

# ⚠️ Common Pitfall

People confuse:

```cpp
parent[]
```

for both purposes.

DO NOT.

Use separate arrays.

---

# 📌 General Detection of Multiple Parents

For every edge:

```text
u → v
```

check:

```cpp
if(graphParent[v] already exists)
```

then:

```text
v has two parents
```

---

# 🔥 Why We Store TWO Candidate Edges

Suppose:

```text
1 → 3
2 → 3
```

Then suspicious edges are:

| Candidate | Edge |
|---|---|
| cand1 | 1→3 |
| cand2 | 2→3 |

One of them must be removed.

---

# 🧠 Master Strategy

---

## STEP 1 — Detect Two Parents

While iterating edges:

- if node already has parent
- store BOTH conflicting edges

---

## STEP 2 — Temporarily Ignore Later Edge

Ignore:

```text
cand2
```

Then run DSU.

---

# ⚡ Two Outcomes

---

## Case A — No Cycle Exists

Then:

```text
cand2
```

was the bad edge.

Because removing it fixed graph.

---

## Case B — Cycle Still Exists

Then:

```text
cand1
```

is bad.

Because cycle existed independently.

---

# 🔥 Why This Works

If removing later edge still leaves cycle:

```text
cycle must involve earlier edge
```

---

# 📌 Important Observation

Once a node gets TWO parents:

ONLY those two incoming edges are suspicious.

You do NOT need to test every edge.

This reduces brute force completely.

---

# 🌪️ The Three Main Cases

---

## Case 1 — Only Cycle Exists

Example:

```text
1 → 2
2 → 3
3 → 1
```

Use DSU normally.

The edge causing:

```cpp
find(u) == find(v)
```

is answer.

---

## Case 2 — Only Multiple Parents Exist

Example:

```text
1 → 3
2 → 3
```

No cycle.

Remove later edge.

---

## Case 3 — Both Exist Together (Most Important)

Example:

```text
1 → 2
2 → 3
3 → 1
4 → 1
```

Node `1` has two parents:
- 3
- 4

AND cycle exists.

Removing `4→1` won't fix cycle.

Correct answer becomes:

```text
3 → 1
```

---

# 🔥 Edge Invalidating Trick

Instead of deleting edge physically:

mark it invalid temporarily.

Example trick:

```cpp
e[1] = 0;
```

Then skip during DSU.

---

# ⚠️ Why This Trick is Useful

Avoids:
- vector erase complexity
- index shifting
- copying arrays
- messy code

Very common interview trick.

---

# 📌 DSU Cycle Detection Rule

For edge:

```text
u → v
```

if:

```cpp
find(u) == find(v)
```

then:

```text
cycle exists
```

---

# ⚠️ Important Nuance

This DSU trick is valid here because:

the graph is ALMOST a tree.

Normally DSU is not sufficient for arbitrary directed graph cycle detection.

---

# 🧠 Rooted Tree Properties Worth Memorizing

For `n` nodes:

| Property | Valid Tree |
|---|---|
| edges | n-1 |
| cycles | none |
| parents/node | at most 1 |
| connected | yes |

---

# 🚨 Common Mistakes

---

## ❌ Mistake 1

Using only DSU.

Fails on:
- two parent issue

---

## ❌ Mistake 2

Trying all edge removals brute force.

Works but inefficient.

---

## ❌ Mistake 3

Confusing graph parent with DSU parent.

VERY common.

---

## ❌ Mistake 4

Returning later edge blindly.

Sometimes earlier edge is actual cycle creator.

---

# ⚡ Key Interview Insight

The question is fundamentally asking:

```text
Which edge violates rooted-tree properties?
```

NOT:

```text
How do I remove a random cycle edge?
```

---

# 🔥 Mental Model

Think of company hierarchy.

Every employee should have:
- exactly one manager

If someone suddenly gets:
- two managers
OR
- management loop

organization becomes invalid.

This problem is basically HR corruption detection using DSU 💀

---

# ⏱️ Complexity

| Operation | Complexity |
|---|---|
| Parent detection | O(n) |
| DSU operations | O(n α(n)) |
| Total | Nearly O(n) |

---

# 🧠 Ultimate Takeaway

This problem teaches:

- DSU limitations
- directed vs undirected graph difference
- parent constraint handling
- rooted tree validation
- conflict resolution logic

This is one of the BEST graph problems for learning how to combine:
- graph properties
- DSU
- structural constraints
together.
