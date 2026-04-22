# 🚀 LeetCode 1514 — Path with Maximum Probability

---

## 🧠 Core Idea

This problem is a variation of graph traversal where:

- Instead of minimizing distance → we **maximize probability**
- Each edge has a probability (`0 → 1`)
- Goal: find path from `start` to `end` with **maximum product of probabilities**

---

## ⚡ Key Transformation

Traditional shortest path:
- Works on **addition**

This problem:
- Works on **multiplication**

### 🔁 Concept Shift:
| Normal Dijkstra | This Problem |
|----------------|-------------|
| minimize sum   | maximize product |
| distance       | probability |
| min heap       | **max heap** |

---

## 🧠 Intuition

Think of it like:

> 🎰 Choosing a sequence of bets — you want the path where the **overall success chance is highest**, not the shortest route.

---

## 🧩 Approach Summary

- Use **Dijkstra-like greedy algorithm**
- Maintain a **max heap (priority queue)**
- Track best probability for each node
- Update only if a better probability is found

---

## 🧠 Why Greedy Works Here?

- Probabilities ∈ [0,1]
- Multiplying probabilities never increases unexpectedly
- Best-so-far approach remains valid

---

## 🔍 Important Observations

- Revisiting nodes is allowed if a better probability is found
- Priority queue ensures we always expand the most promising path first
- Similar structure to shortest path, just replacing operations

---

## ⚠️ Edge Cases (VERY IMPORTANT)

### 1. 🚫 No Path Exists
- Return `0.0`

---

### 2. 🎯 Start == End
- Return `1.0`
- (Probability of staying at same node)

---

### 3. 🧊 Zero Probability Edges
- These edges are effectively useless
- They will never improve any path

---

### 4. 🔁 Cycles in Graph
- Safe because:
  - We only update when probability improves
  - Prevents infinite loops

---

### 5. 📉 Multiple Paths to Same Node
- Only keep the **best probability**
- Ignore worse paths

---

### 6. 📦 Disconnected Graph
- Some nodes may never be reached
- Their probability remains `0`

---

### 7. 🔢 Floating Point Precision
- Small precision errors may occur
- Usually acceptable within constraints

---

## 🧠 Common Mistakes (VERY HIGH VALUE)

### ❌ Forgetting Initialization
- Start node probability must be `1.0`

---

### ❌ Using Min Heap Instead of Max Heap
- Will give incorrect result

---

### ❌ Using Integer Instead of Double
- Probabilities get truncated → WRONG ANSWER

---

### ❌ Wrong Relaxation Logic
- Correct:
```

newProb = currentProb * edgeProb

```
- Not:
```

prob[node] * currentProb

```

---

### ❌ Skipping Pruning
- Must ignore outdated states
- Otherwise TLE risk

---

## ⚡ Optimization Insight

- Early exit when destination is reached
- Helps reduce unnecessary computation

---

## 🧠 Alternative Approach (Advanced)

### Log Transformation

Convert:
```

maximize (p1 * p2 * p3)

```

To:
```

maximize (log p1 + log p2 + log p3)

```

→ Then solve using standard shortest path

---

## 📊 Complexity

| Type | Complexity |
|------|----------|
| Time | O(E log V) |
| Space | O(V + E) |

---

## 🧠 Mental Model

```

You are expanding paths in order of "most reliable so far"

```

Not shortest, not fastest — **most trustworthy path**

---

## ⚡ Debugging Tips

- If all outputs are `0` → initialization issue
- If incorrect answers → check multiplication logic
- If TLE → missing pruning condition

---

## 🧠 Real-World Connections

- Network reliability analysis 🌐
- Probability chains in AI/ML 🤖
- Risk analysis in finance 💸

---

## 🧠 Final Takeaway

> This is NOT a new algorithm — it's just **Dijkstra wearing a different outfit** 😄

Master this pattern and you unlock:
- Maximum probability problems
- Maximum product paths
- Variations of weighted graph traversal

---

## 🚀 What To Remember

- Replace `+` with `*`
- Use **max heap**
- Initialize start = `1.0`
- Relax only if better probability found
- Always prune outdated states

---

Stay sharp. This pattern shows up more often than you think. 🔥
```
