# ⚡ Longest Increasing Subsequence (LIS) — Binary Search / Greedy Cheatsheet

## 🚀 Core Idea (Read This Twice)
We are **NOT building the actual subsequence**.

We are maintaining:
> The **best possible endings** of increasing subsequences of different lengths

---

## 🧠 Mental Model

Think of `tails` like this:

> `tails[k]` = smallest possible ending value of an increasing subsequence of length `k+1`

---

## 🔥 Key Insight

For every number:
- Either **extend** the longest subsequence
- Or **replace** an existing ending to make it *better (smaller)*

---

## ⚙️ What Actually Happens

For each element:
1. Find where it fits in `tails` (using binary search)
2. Two possibilities:

### ✅ Case 1: Bigger than all → EXTEND
- New longer subsequence found

### ✅ Case 2: Fits somewhere → REPLACE
- Improve an existing subsequence ending

---

## 💣 WHY THIS WORKS (Deep Intuition)

### 🔑 Invariant:
> At any time, for every length `L`,  
> there exists an increasing subsequence of length `L`  
> ending with value `tails[L-1]`

---

### 🔥 Replacement Logic

When replacing:
> You are NOT destroying a subsequence  
> You are making it **more extendable**

---
[2, 5] vs [2, 3]

👉 `[2, 3]` is better because:
- Smaller ending → easier to extend later

---

## ⚠️ BIG TRUTH (INTERVIEW TRAP)

> `tails` is NOT the actual LIS ❌

It is just a **helper structure** to compute the length.

---

## 🧠 Why Length is Always Correct

We increase size ONLY when:
> Current element is greater than all endings

👉 This guarantees:
- A longer subsequence truly exists

---

## 🧩 Analogy (Lock It In)

Think of ladders 🪜:

- Each ladder = subsequence of length `k`
- `tails[k]` = lowest possible top of that ladder

👉 Lower top = easier to climb higher

---

## ⚠️ Common Mistakes (Avoid These)

### ❌ Mistake 1: Thinking this gives actual sequence
Nope. It only gives length.
e.g: there we have chosed in tails like 1, 2, 3, 5, 6,7 then comes 4 we replace 5 to 4  
-becomes: 1, 2, 3,4 ,6, 7 then comes  8 will be added to the end which is correct in length acc to one with 5 but wrong in value with 4
---

### ❌ Mistake 2: Mixing with DP logic
- No `dp[i]`
- No checking all previous elements

👉 Completely different paradigm

---

### ❌ Mistake 3: Thinking replacement is risky
Reality:
- Replacement only improves future possibilities

---

### ❌ Mistake 4: Using upper_bound blindly
- For **strictly increasing**, use `lower_bound`
- Using wrong one breaks logic

---

## 🔍 Pattern Recognition

Use this approach when:
- Problem asks for **length of LIS**
- Constraints are large (O(n²) too slow)
- Sequence must be **strictly increasing**

---

## ⚡ When NOT to Use This

Avoid when:
- You need to **print the actual LIS**
- You need **count of LIS**
- You need **all subsequences**

👉 Use DP in those cases

---

## 🧠 Advanced Insight

This is a mix of:
- **Greedy** → always keep best endings
- **Binary Search** → efficient placement

---

## 🧪 Self-Check Questions

- [ ] Why do we replace instead of ignore?
- [ ] Why does smaller ending help?
- [ ] Why is `tails` not the actual LIS?
- [ ] When do we increase length?

If you can answer all → you're interview ready.

---

## 😏 Final Takeaway

> We are not building the sequence  
> We are optimizing the **future potential of sequences**

That’s why this works in O(n log n).
### 📊 Example Thinking

Between:
