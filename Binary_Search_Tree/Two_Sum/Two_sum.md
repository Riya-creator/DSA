#   📌 LeetCode 653 — Two Sum IV (BST)

## 🧠 Problem Summary

You are given the root of a **Binary Search Tree (BST)** and an integer `k`.

Return `true` if there exist **two different nodes** in the tree whose values add up to `k`, otherwise return `false`.

---

## 🌲 Key BST Property

In a BST:

- Left subtree values < root
- Right subtree values > root
- **Inorder traversal produces a sorted sequence**

This sorted nature is the backbone of the optimal solutions.

---

## 🎯 What This Problem Is Testing

- Tree traversal (DFS / inorder)
- Two-sum logic
- Stack-based iterators
- Space vs Time trade-offs
- Leveraging BST ordering

---

# ⚠️ Things To Keep In Mind

- You **cannot reuse the same node twice**
- Skewed BST → height becomes `O(n)`
- Try to avoid storing all nodes if asked for optimized space
- BST ≠ Binary Tree (ordering matters!)
- When using two pointers, ensure `left < right`

---

# 🧪 Three Ways To Solve

---

## ✅ 1) DFS + HashMap

📄 Code
👉[DFS + HashMap](Dfs__HashMap.cpp)

### 💡 Idea:
Traverse the tree using DFS.

For every node:
- check if `(k - node->val)` exists in a hash set
- if yes → return true
- else insert node->val

---

### ⏱ Complexity

| Metric | Value |
|------|------|
| Time | O(n) |
| Space | O(n) |

---

### 👍 Pros / 👎 Cons

✔ Easy to code  
✔ Works for any binary tree  
✖ Uses extra memory

---

---

## ✅ 2) Stack-Based Two Pointer on BST (Optimal)

📄 Code
👉[Stack](Stack.cpp)

### 💡 Idea:

Simulate two iterators:

- one from **smallest** (inorder)
- one from **largest** (reverse inorder)

Use two stacks to avoid storing all values.

---

### 🧾 Core Steps

1. Push all left nodes → stack1
2. Push all right nodes → stack2
3. Compare top values
4. Move left iterator if sum < k
5. Move right iterator if sum > k

---

### ⏱ Complexity

| Metric | Value |
|------|------|
| Time | O(n) |
| Space | O(h) (tree height) |

---

### ⭐ Why This Is Best

- Uses BST ordering directly
- Memory efficient
- Interview gold

---

---

## ✅ 3) Inorder Traversal + Two Pointers

📄 Code
👉[Inorder_Traversal](Inorder_2_pointer.cpp)

### 💡 Idea:

1. Perform inorder traversal → store values in vector
2. Use classic two-pointer on sorted array

---

### ⏱ Complexity

| Metric | Value |
|------|------|
| Time | O(n) |
| Space | O(n) |

---

### 👍 Pros / 👎 Cons

✔ Simple logic  
✔ Easy debugging  
✖ Extra memory

---

# 🧠 Mental Model

Think of the BST like a **sorted list hidden inside a tree**.

You either:

- scan while remembering numbers (hash set)
- pull smallest + largest lazily (stacks)
- or flatten then two-pointer

---

# 💬 Interview Tips

- Start with HashSet → baseline
- Mention inorder → sorted
- Upgrade to stack iterators for optimal space
- Discuss worst-case skewed tree
- Say: “This is similar to two-sum on sorted structure.”

---

# 🚀 Pattern Tag

- Binary Search Tree
- Two Pointers
- Tree Traversal
- Stack
- Hashing

---

# 📝 TL;DR

| Approach | Time | Space |
|--------|------|------|
| DFS + HashSet | O(n) | O(n) |
| Two Stack Iterators | O(n) | O(h) |
| Inorder + Two Pointers | O(n) | O(n) |

---
