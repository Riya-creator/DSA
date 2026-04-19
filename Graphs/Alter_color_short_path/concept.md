
# 🚦 Shortest Path with Alternating Colors (LeetCode 1129) — Deep Concept Guide

---

## 🧠 Core Idea

This problem is NOT a normal BFS.

👉 It is a **State-Based BFS**, where each state is:
```

(node, last_edge_color_used)

```

Because:
- Reaching the same node using different colors = **different situations**
- Future moves depend on the last color used

---

## 🔴 Key Concept Shift

### ❌ Wrong Thinking:
> "Shortest path to a node"

### ✅ Correct Thinking:
> "Shortest path to a node WITH a specific last color"

---

## 🧩 Graph Representation

- Each edge has a color:
  - Red → `0`
  - Blue → `1`

- Graph should store:
```

adj[node] = list of (neighbor, color)

```

- Same nodes can have:
  - Red edge
  - Blue edge
  - Both

---

## 🚀 BFS Strategy

### Start State:
- Push BOTH:
```

(0, red)
(0, blue)

```

👉 Because first move can be either

---

### Transition Rule:
Only move if:
```

next_edge_color != last_edge_color

```

---

### Distance Tracking:
```

dist[node][color]

```

Meaning:
- `dist[i][0]` → shortest path to `i` ending with RED
- `dist[i][1]` → shortest path to `i` ending with BLUE

---

## ⚠️ VERY IMPORTANT RULE

👉 `(node, red)` ≠ `(node, blue)`

You must treat them as **completely separate states**

---

## 🔥 Types of BFS (Important Distinction)

### 1️⃣ Level-Based BFS
Used in:
- Simple shortest path (unweighted graph)

Concept:
- Each level = same distance

Limitation:
- Fails when extra constraints exist (like color alternation)

---

### 2️⃣ State-Based BFS ✅ (Used Here)

Used when:
- Path depends on previous move
- Constraints like:
  - alternating colors
  - parity (even/odd)
  - direction
  - keys/locks

Concept:
```

State = node + extra condition

```

Distance:
```

dist[next] = dist[current] + 1

```

---

### 3️⃣ Multi-Dimensional BFS (Extension)

Used in:
- Grid problems
- Bitmask BFS
- Shortest path with keys

State example:
```

(node, mask)
(node, direction)
(node, color)

```

---

## ⚠️ Common Mistakes (HIGH RISK)

### ❌ Using `visited[node]`
👉 WRONG — loses color info

### ✅ Correct:
```

visited[node][color]

```

---

### ❌ Checking visited at POP time
- Leads to duplicate states in queue

### ✅ Correct:
Check at PUSH time

---

### ❌ Using level (`step`) for distance
- Breaks in multi-state BFS

### ✅ Correct:
```

dist[next] = dist[current] + 1

```

---

### ❌ Using `min(dist[i][0], dist[i][1])` blindly

If one is `-1`, result becomes wrong

### ✅ Correct handling:
- If one is `-1`, take the other
- Else take min

---

### ❌ Not pushing both starting states
- Misses valid paths

---

## 🧠 Mental Model (Remember This Forever)

Think like:
- Red edge = bike 🚴
- Blue edge = car 🚗

Rule:
> You must switch vehicle every move

So:
- Reaching a node by bike ≠ reaching by car

---

## ⚡ Edge Cases You Must Handle

- Node unreachable → answer = `-1`
- Only one color path exists
- Self-loops
- Multiple edges between same nodes
- Cycles with alternating colors

---

## ⏱️ Complexity Analysis

### Time Complexity:
```

O(N + E)

```

But technically:
```

O(2 * (N + E)) → still O(N + E)

```

Because:
- Each node has 2 states (red/blue)

---

### Space Complexity:
```

O(N + E)

```

Breakdown:
- Graph → O(E)
- Distance array → O(2N)
- Queue → O(2N)

---

## 🔥 Pattern Recognition (Interview Gold)

If you see:
- "alternating"
- "no two same moves"
- "previous matters"
- "color/direction constraint"

👉 Instantly think:
```

STATE BFS

```

---

## 🧠 Final Summary

- Use BFS with state `(node, color)`
- Track distance in 2D array
- Alternate colors strictly
- Avoid revisiting same state
- Compute answer carefully

---

## 🚀 Pro Insight

This is a **template problem**

Same pattern appears in:
- shortest path with keys 🔑
- grid with constraints
- bitmask BFS
- direction-based graphs

👉 Master this once → unlock MANY hard problems

---
```
