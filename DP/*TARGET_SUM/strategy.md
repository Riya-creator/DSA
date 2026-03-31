# 🎯 LeetCode 494 - Target Sum

---

## 🧠 Problem Explanation

You are given an array of integers and a target value.

You need to assign either a **‘+’ or ‘-’ sign** to each number such that the final expression evaluates to the target.

👉 Goal: **Count the number of ways** to achieve this target.

---

## 🧩 Core Observation

Each number has 2 choices:

- Add it → contributes positively
- Subtract it → contributes negatively

This creates a **binary decision tree → 2^n combinations**

---

# 🧠 APPROACH 1: Try All Combinations (Recursion + DP)

---

## 💡 Thinking

At every index:

- You either take `+nums[i]`
- Or take `-nums[i]`

---

## 🔁 DP Definition
dp[i][currSum] = number of ways to reach currSum using first i elements


---

## ⚠️ Problem with this approach

- `currSum` can range from **-totalSum → +totalSum**
- So DP table becomes:
Size ≈ O(n × 2 * totalSum)


👉 Requires **offset handling** (to deal with negative indices)  
👉 Memory heavy  
👉 Conceptually messy  

---

## ❌ Limitations

- Large DP table
- Negative indexing complications
- Harder to implement cleanly

---

# 🚀 APPROACH 2: Mathematical Transformation (Optimized)

---

## 🧠 Key Insight

Instead of thinking about `+` and `-`, think in terms of **partitioning the array**

---

## 🧩 Partition Idea

Split array into:

- S1 → elements with '+'
- S2 → elements with '-'

---

## 📌 Equation Formation
S1 - S2 = target ...(1)
S1 + S2 = totalSum ...(2)


---

## 🔄 Solving Equations

Adding (1) and (2):
2S1 = target + totalSum
S1 = (target + totalSum) / 2

OR

S2 = (totalSum - target) / 2


---

## 🎯 Final Conversion

👉 Problem becomes:
Count subsets with sum = (totalSum - target) / 2

---

## 🧠 Why this works

- Instead of assigning signs → we choose a subset
- One subset defines the other automatically
- Reduces complexity drastically

---

## ⚠️ Validity Conditions

- `(totalSum - target)` must be **even**
- `totalSum >= target`

---

# ❓ Why NOT use S1?

We can use:
S1 = (totalSum + target) / 2


BUT:

👉 S1 is usually **larger**

Since DP depends on sum:


Time = O(n × sum)

👉 Using S2 gives **smaller DP → faster & efficient**

---

# 🔥 WHY TRANSFORMATION IS POWERFUL

| Approach | Complexity | Cleanliness |
|--------|-----------|------------|
| Try all +/- | O(n × 2*sum) | ❌ messy |
| Subset sum | O(n × sum) | ✅ clean |

---

# 🧠 APPROACH 2 IMPLEMENTATIONS

---

## 🔁 1. Recursion + Memoization

### DP Definition
dp[i][target] = number of ways to form target using elements from index 0 to i

---

### Key Idea

At each index:

- Take element → reduce target
- Not take → keep target same

---

## 📊 2. Tabulation (Bottom-Up)

### DP Definition
dp[i][j] = number of ways to get sum j using first i elements


---

### Benefits

- No recursion stack
- Iterative
- Easier to debug

---

## ⚡ 3. Space Optimization

### DP Definition
dp[j] = number of ways to form sum j

---

### Optimization Idea

- Only previous row is needed
- Use 1D array
- Traverse backwards

---

# ⚠️ IMPORTANT EDGE CASE (ZERO)

If array contains `0`:

- `+0` and `-0` both valid
- Each zero **doubles number of ways**

---

# 🧠 COMPARISON

| Feature | Try All +/- | Subset Sum |
|--------|------------|-----------|
| Complexity | High | Optimized |
| DP Size | Large (neg + pos) | Smaller |
| Implementation | Complex | Standard |
| Interview Friendly | ❌ | ✅ |

---

# 💡 ADVANCED THINKING PATTERN

Whenever you see:

- + / - choices  
- target difference  
- partition  
- count ways  

👉 Think:
Difference → Partition → Subset Sum

---

# 🧠 HOW TO THINK LIKE A PRO

---

## 🔥 Step-by-step mental model

1. Identify decision choices (+ / -)
2. Convert into partition (S1, S2)
3. Form equations
4. Reduce to subset sum
5. Apply DP

---

## ⚡ Golden Rule
If choices are binary → think subset
If difference involved → think partition

---

# 💀 COMMON MISTAKES

- Using `%2` instead of `/2`
- Forgetting edge condition
- Mixing forward/backward recursion
- Wrong DP definition
- Ignoring zero case

---

# 🚀 PRO TIPS (LEVEL UP)

- Always ask: *Can this be reduced to subset sum?*
- Practice pattern recognition, not memorization
- Stick to one recursion direction consistently
- Build intuition for DP state definition
- Prefer transformation when DP becomes messy

---

# 🧠 FINAL TAKEAWAY

This problem is NOT about signs.

👉 It is about:
Smart problem transformation + subset sum DP


Master this → unlock multiple DP problems 🚀

---
