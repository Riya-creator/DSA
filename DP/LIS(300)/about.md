# 🧠 Longest Increasing Subsequence (LIS) — Thinking Cheatsheet

## 🚀 Core Mindset Shift
Stop thinking:
> “Which subsequence should I build?”

Start thinking:
> “What is the best subsequence that **ends at this index**?”

This single shift kills confusion.

---

## 🔍 Problem Identification (VERY IMPORTANT)

You are likely dealing with LIS-type DP when you see:

- Keywords:
  - "subsequence" (NOT subarray)
  - "increasing / decreasing"
  - "strictly greater / smaller"
- Constraints:
  - Order matters, but elements are NOT necessarily contiguous
- Hidden Pattern:
  - Current decision depends on **previous elements**

💡 If you see:
> “Choose elements such that condition with previous holds”

👉 Trigger LIS thinking immediately.

---

## 🧠 Mental Model

Each element is like a person trying to join a group:
- They can only join a group smaller than them
- They want to join the **best (longest) group possible**

---

## ⚙️ State Thinking (The Clean Way)

Instead of tracking:
- all subsequences ❌
- take / not take ❌
- previous values explicitly ❌

👉 Think:
> “Best answer ending at index i”

---

## 🧩 Transition Intuition

At index `i`, ask:
- Who before me can I connect to?

Then:
- Extend the **best valid one**

---

## ⚠️ Common Mistakes (Avoid These Like Bugs)

### ❌ 1. Thinking in Subarrays
LIS is NOT contiguous → don't use sliding window mindset.

---

### ❌ 2. Using 2D DP (Overengineering)
If you're doing:
- `dp[i][prev]`
- or tracking values directly

👉 You're making life harder.

---

### ❌ 3. Assuming Answer Ends at Last Index
Big trap.

👉 LIS can end anywhere → always track global max.

---

### ❌ 4. Greedy Without Thinking
Just picking next bigger element = WRONG.

👉 Future choices matter.

---

## 🔥 Recognition Pattern (Golden Rule)

If problem says:
- “pick elements”
- “maintain order”
- “some relation with previous”

👉 Instantly test:
> “Can I define answer ending at index i?”

---

## 🧠 Edge Case Awareness

- No valid previous element?
  → Start new subsequence (length = 1)

- Multiple valid previous?
  → Choose the BEST one (max)

---

## ⚡ Optimization Insight (Advanced Hint)

Once you master DP:

Ask:
> “Do I really need to check ALL previous elements?”

👉 Leads to:
- Binary Search
- Patience Sorting
- O(n log n) solution

---

## 🧪 Self-Test Checklist

Before solving, ask yourself:

- [ ] Is this subsequence (not subarray)?
- [ ] Does current depend on previous?
- [ ] Can I define answer ending at index i?
- [ ] Do I need global max instead of last index?
- [ ] Am I overcomplicating with 2D DP?

---

## 💡 Analogy (Lock it in)

Think of building a gaming streak 🎮:

Each level:
- You can only move forward if your score increases
- You choose the **best previous streak** to continue

---

## 🧠 Final Takeaway

> LIS is NOT about generating subsequences  
> It’s about **extending the best valid history**

---

## 😏 Pro Tip

If your brain says:
> “Let’s try recursion + take/not take”

Pause.

Ask:
> “Can I compress this into ‘ending at index i’?”

👉 That’s your upgrade from beginner → problem solver.
