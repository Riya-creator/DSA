# 🧠 Number of Longest Increasing Subsequences (LC 673) — Thinking Cheatsheet

---

## 🚀 Core Idea (Don’t Miss This)

This is NOT just LIS.

This is:
> **Find the length of LIS AND count how many such LIS exist**

---

## 🧠 Mindset Shift

In LC 300:
> “What is the longest length?”

In LC 673:
> “How many ways can I achieve the longest length?”

---

## 🔥 Key Observation

At every index `i`, you need to know:

- 📏 `length[i]` → longest increasing subsequence ending at `i`
- 🔢 `count[i]` → number of ways to get that length at `i`

---

## ⚙️ Transition Thinking

For each index `i`, check all `j < i`:
length[j] + 1 > length[i]


👉 Then:
- Update `length[i]`
- **Copy count from j**

💡 Why?
Because you found a strictly better subsequence

---

### ✅ Case 2: Same Length Found

If:
length[j] + 1 == length[i]

👉 Then:
- **Add count from j**

💡 Why?
Because you found another way to reach same best length

---

## ⚠️ Golden Rule

> Counts are accumulated ONLY when lengths match

---

## 🧩 Final Answer Logic

1. Find **maximum length** among all `length[i]`
2. Sum all `count[i]` where:
3. length[i] == maxLength


---

## 💣 Common Mistakes (VERY IMPORTANT)

### ❌ Mistake 1: Using Binary Search / Tails
- Works for LC 300 ❌
- Fails for LC 673 ❌

👉 Because it loses multiple paths

---

### ❌ Mistake 2: Using 2D DP
- Overcomplicates problem
- Not needed

👉 Problem is solvable in 1D DP

---

### ❌ Mistake 3: Handling Equal Elements
- LIS is **strictly increasing**
- `nums[j] == nums[i]` should NOT be used

---

### ❌ Mistake 4: Returning Last Index
- LIS may end anywhere

👉 Always take global maximum

---

### ❌ Mistake 5: Forgetting to Reset Count
When you find a better length:
- You must **replace count**
- NOT add

---

## 🧠 Deep Intuition

Each index is like a checkpoint 🏁:

- `length[i]` → best score to reach here
- `count[i]` → number of ways to achieve that score

---

## 🔥 Why This Works

You are not storing full subsequences.

You are storing:
> “Summary of best possible sequences ending here”

---

## 🧪 Example Insight

For:[1, 3, 5, 4, 7]


Two LIS:
- 1 → 3 → 5 → 7  
- 1 → 3 → 4 → 7  

👉 Multiple paths → must track counts

---

## ⚡ Pattern Recognition

Use this approach when:
- Problem asks for **number of subsequences**
- Constraint involves **ordering + comparison**
- Multiple valid paths exist

---

## 🧠 Edge Cases

### 🔹 All elements same

[2, 2, 2, 2]

👉 Each element is LIS of length 1  
👉 Answer = n

---

### 🔹 Strictly increasing array
[1, 2, 3, 4]

👉 Only one LIS  
👉 Answer = 1

---

### 🔹 Strictly decreasing array
[5, 4, 3, 2]

👉 Each element forms LIS  
👉 Answer = n

---

## ⚡ Time Complexity

- O(n²) → must check all previous `j`
- Cannot optimize with binary search (loses paths)

---

## 🧠 Final Takeaway

> LC 300 = optimize length  
> LC 673 = preserve all optimal paths

---

## 😏 Pro Insight

If your brain says:
> “Let’s compress states like tails”

🚫 STOP

Because:
> Compression kills path information

---

## 💬 Self-Test Checklist

- [ ] Do I track both length and count?
- [ ] Do I copy count when better length is found?
- [ ] Do I add count when equal length is found?
- [ ] Do I ignore equal elements?
- [ ] Do I take global max at end?

---

## 🧠 One-Line Summary

> Don’t just find the best path — count how many best paths exist.
### Condition:
