# 🧱 Largest Rectangle in Histogram (LeetCode 84)

## 📌 Problem Overview
Given an array of integers representing the heights of bars in a histogram, the task is to find the area of the largest rectangle that can be formed.

---

## 🧠 Core Idea

For every bar `i`, we assume:
> This bar is the **minimum height** of a rectangle.

Then we try to find:
- How far it can extend **left**
- How far it can extend **right**

👉 Condition:
All bars in that range must have height ≥ height[i]


---

## ⚡ Key Insight

Instead of checking every possible rectangle (which leads to O(n²)), we:

👉 Find boundaries efficiently using a **monotonic stack**

For each index `i`:
- `left[i]` = nearest smaller element on the left
- `right[i]` = nearest smaller element on the right

---

## 📐 Area Formula
width = right[i] - left[i] - 1
area = height[i] * width


---

## 🔥 Why This Works

- The rectangle height is determined by the **minimum bar**
- If we know the nearest smaller elements:
  - we know the maximum valid width
- No need to scan repeatedly

---

## 🧠 Stack Strategy

We maintain a stack such that:
heights are in increasing order


### Behavior:
- If current height is **greater** → push index
- If current height is **smaller** → pop until valid

---

## 💥 When Do We Calculate Area?

When we encounter a smaller height:
- It becomes the **right boundary**
- We pop taller bars and compute their area

---

## 📍 Boundary Definitions

### Right Boundary
- Current index `i` when popping
- OR `n` (if no smaller element exists)

### Left Boundary
- New stack top after popping
- OR `-1` (if no smaller element exists)

---

## ⚠️ Special Case: `left = -1`

This means:
> No smaller element on the left

So:
width = right - (-1) - 1 = right


👉 Rectangle extends till index `0`

---

## 🚨 Important Rules

- ❌ Do NOT modify heights
- ❌ Do NOT merge bars
- ❌ Do NOT use DP here
- ❌ Do NOT scan left/right repeatedly

- ✅ Each bar is processed **once**
- ✅ Each bar is pushed and popped **at most once**

---

## ⏱️ Complexity

| Operation | Time |
|----------|------|
| Traversal | O(n) |
| Stack ops | O(n) |
| **Total** | **O(n)** |

---

## 🧠 Mental Model

Think of each bar as:
> "Waiting to find its right boundary"

- When a smaller bar appears → it gets finalized
- Area is computed instantly

---

## 🧩 Problem Transformation

This problem is equivalent to:

> For each element, find the largest subarray where it is the minimum

---

## 🔄 Edge Cases

- Increasing heights → stack not empty at end
- Decreasing heights → continuous popping
- All equal heights → full width rectangle
- Single element → area = height

---

## 🚀 Advanced Variations

- Maximal Rectangle in Binary Matrix (LC 85)
- Using Segment Tree (Divide & Conquer)
- Cartesian Tree approach

---

## 🧠 Final Takeaway

👉 Don’t try to explore all rectangles  
👉 Let each bar compute its max rectangle **once**

This is a **boundary detection problem**, not a brute force or DP problem.

---

## 🧪 Practice Tip

Try dry runs on:
[2, 4, 5, 6, 3]
[1, 3, 5, 7, 6, 4, 2]


Focus on:
- Stack state
- When pops happen
- How width is calculated

---

## 💡 Interview One-Liner

> Use a monotonic increasing stack to find nearest smaller elements on both sides and compute the maximum area for each bar.

---
