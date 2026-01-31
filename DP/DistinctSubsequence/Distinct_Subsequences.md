# 📌 Distinct Subsequences — DP Strategy & Optimization Guide

This repository contains three carefully designed Dynamic Programming solutions for the **Distinct Subsequences** problem:

- 🧠 **Memoization using 2D DP**
- 📊 **Tabulation using 2D DP**
- 🚀 **Space-Optimized DP using 1D array**

Each version uses the **same DP state definition**, but differs in how memory and computation are handled.

> 💡 The progression shows how to move from intuitive recursion-based DP → iterative DP → memory-efficient production-level solution.

---

## 🧩 Problem Overview

Given two strings:

- `s` → source  
- `t` → target  

Count how many **distinct subsequences** of `s` equal `t`.

A subsequence preserves order but may skip characters.

---

## 🎯 DP State Philosophy

All approaches rely on the same idea:

## dp[i][j] = number of ways to form t[j...] from s[i...]


This 2-D state is:

- Stored directly in memoization  
- Filled iteratively in tabulation  
- Compressed into 1-D for space optimization  

Only the **implementation style** changes — not the logic.

---

# 🛠️ Implemented Approaches

---

## 🟡 1. Memoization (Top-Down DP with 2D Vector)

📄 Code 👉 [Memoization.cpp](Memoization.cpp)

📍 **What it is:**  
Recursive solution with a `dp[n][m]` table to cache overlapping subproblems.

### ✅ Why Use?

- Easy to derive from recursion  
- Mirrors mathematical recurrence  
- Interview-friendly explanation  
- Prevents recomputation  

### ⚠️ Limitations

- Uses recursion stack  
- Higher memory than 1-D version  

### ⏱️ Complexity

- **Time:** `O(n × m)`
- **Space:** `O(n × m)` + recursion stack

---

## 🟢 2. Tabulation (Bottom-Up with 2D Vector)

📄 Code 👉 [Tabulation](Tabulation.cpp)

📍 **What it is:**  
Iterative DP filling a full 2-D matrix from base cases upward.

### ✅ Why Use?

- No recursion stack  
- Deterministic iteration order  
- Clear base-case handling  
- Faster than memoization in practice  

### ⚠️ Limitations

- Consumes `O(n × m)` memory  
- Still heavy for very large strings  

### ⏱️ Complexity

- **Time:** `O(n × m)`
- **Space:** `O(n × m)`

---

## 🔵 3. Space-Optimized DP (1D Vector)

📄 Code 👉 [Space-Optimized](spaceOptimized.cpp)

📍 **What it is:**  
A memory-reduced version of tabulation that compresses the 2-D DP table into a single array.

### ✅ Why Use?

- Only `O(m)` memory  
- No recursion  
- Fastest & scalable  
- Competitive-programming ready  

### ⚠️ Limitations

- Trickier iteration order  
- Requires careful overwrite control  

### ⏱️ Complexity

- **Time:** `O(n × m)`
- **Space:** `O(m)`

---

# 📊 Comparison Summary

| Approach | DP Storage | Time | Space | Recursion | Best Use Case |
|--------|-----------|------|------|-----------|-------------|
| Memoization | 2D | O(n×m) | O(n×m) | ✅ | Deriving optimized logic |
| Tabulation | 2D | O(n×m) | O(n×m) | ❌ | Clean iterative DP |
| Space-Optimized | 1D | O(n×m) | O(m) | ❌ | Large constraints / CP |

---

# 🔹 Reverse Iteration in 1-D DP

While updating the 1-D array, always move **right → left** to avoid overwriting needed values.

---

### 🔹 Overflow Awareness

Use `unsigned long long` — the count of subsequences can grow fast 📈.

---

### 🔹 Pattern Recognition Trick

Whenever a problem says:

> “Number of ways…”

Translate in your brain:

 **Counting DP on strings**.

---
