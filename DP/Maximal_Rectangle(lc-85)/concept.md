# 🧱 Maximal Rectangle (LeetCode 85) — Deep Dive README

## 🚀 Core Idea

The problem reduces a 2D binary matrix into a series of 1D histogram problems.

At every row, we treat that row as the **base (ground level)** and build a histogram using all rows above it.

👉 Then, for each such histogram, we compute the **largest rectangle area**.

---

## 🧠 What Are We Storing (DP Meaning)

We maintain a 1D array:

- `dp[j]` = **number of consecutive '1's vertically ending at current row for column j**

### Interpretation:
- It represents the **height of a bar** in a histogram.
- Each column becomes a bar whose height depends on how many continuous `1`s are stacked above.

---

## 🔄 Transition / Update Logic

For every cell:

- If current cell is `'1'`:
  → extend previous height (increase stack height)

- If current cell is `'0'`:
  → break continuity (reset height to 0)

👉 This ensures:
- Only valid vertical rectangles are considered
- Broken regions are discarded immediately

---

## 📊 How Rectangle Is Actually Formed

At each row:
- The `dp` array behaves like a **histogram**
- We compute the largest rectangle in that histogram

### Key Mechanics:
- Height is already known (from dp)
- Width is determined dynamically using a **monotonic stack**
- For each bar:
  - Find nearest smaller bar on left
  - Find nearest smaller bar on right
  - Width = distance between them

---

## ⚙️ Why This Works

- Vertical continuity is preserved through dp
- Horizontal expansion is safely computed using stack
- Ensures every rectangle considered is valid in the matrix

---

## ⚠️ Important Observations

- Rectangles must be **fully filled with 1s**
- Any zero immediately breaks vertical stacking
- Width cannot be precomputed safely — must be derived dynamically
- Each row independently contributes possible rectangles

---

## 🧩 Edge Cases

- Matrix full of `0`s → answer = 0
- Matrix full of `1`s → answer = rows × cols
- Single row → reduces to histogram problem
- Single column → vertical stacking only
- Sparse matrix → frequent resets in dp

---

## ⏱️ Complexity

- **Time Complexity:** O(rows × cols)  
  (Each element is processed once, stack operations are amortized)

- **Space Complexity:** O(cols)  
  (dp array + stack)

---

## 🧠 Pattern Recognition (Important for Interviews)

This problem teaches a powerful pattern:

> Convert a 2D problem into multiple 1D problems and reuse known solutions

---

## 🎮 Intuition Analogy

Imagine building towers of blocks column-wise:

- Each row adds more blocks on top if possible
- If a block is missing (0), the tower collapses at that point
- Now at every stage, you try to place the largest rectangle over these towers

---

## 🔥 Final Takeaway

- Store **heights (vertical continuity)**, not widths
- Use histogram logic to compute areas
- Combine DP + Stack for optimal performance

👉 This is a classic example of:
**"Accumulate one dimension, compute the other dynamically"**
