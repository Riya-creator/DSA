# 📈 Stock Buy & Sell (Unlimited Transactions) — Deep Understanding Guide

> This README is NOT about just solving one problem.  
> It’s about building a **mental model** that works for an entire class of problems.

---

# 🧠 1. Problem Mindset

You are given:
- Prices of a stock over days
- You can:
  - Buy
  - Sell
  - Hold
- Constraint:
  - Only **one stock at a time**
  - **Unlimited transactions allowed**

You are allowed to:
- Enter (buy) and exit (sell) the market multiple times
- But you cannot overlap transactions

---

# 🔥 2. What “Unlimited Transactions” REALLY Means

❌ It does NOT mean:
- Infinite profit
- Multiple stocks at once

✅ It means:
- You can perform **multiple buy → sell pairs**
- But must sell before buying again

---

## 💡 Key Insight

> We are NOT counting transactions —  
> We are allowing **state transitions freely**

---

# ⚡ 3. Two Ways to Think About It

---

## 🟢 A. Greedy Thinking

> “Take every profitable opportunity”

- If price increases → take profit
- Ignore global structure

### Mental Model:
- Every upward slope = profit
- Treat each increase independently

---

### ✅ Why it works
- No dependency between transactions
- Profit segments are independent

---

### ❌ Limitations
Breaks when:
- Cooldown is introduced
- Transaction fee exists
- Limited number of transactions

---

---

## 🔵 B. DP Thinking

> “Track all possible states and transitions”

---

### 🧩 Core Idea

At any day, you are in one of two states:

- HOLDING stock  
- NOT HOLDING stock  

---

### 💡 State Representation

- `Holding` → you own a stock  
- `Not Holding` → you don’t  

---

### 🔁 Transitions

From each state, you can:
- Stay in same state
- Switch state (buy/sell)

---

### 🧠 Deep Insight

> DP is not tracking transactions —  
> it is tracking **state transitions over time**

---

# ⚖️ 4. Greedy vs DP

| Feature | Greedy | DP |
|--------|-------|----|
| Complexity | Simple | Slightly complex |
| Speed | Fast | Same O(n) |
| Flexibility | Low | High |
| Handles constraints | ❌ | ✅ |
| Thinking depth | Local | Global |

---
# ⚖️ Greedy vs DP — Decision Table (When to Use What)

> Use this as a **quick diagnostic checklist** before coding.

---

## 🧠 Core Question

> “Can I make a locally optimal choice safely, or do I need to consider future consequences?”

---

## 🔥 Decision Table

| Criteria | Greedy ✅ | DP 🔵 |
|----------|----------|------|
| **Local optimal = Global optimal** | ✔️ Yes | ❌ Not guaranteed |
| **Future decisions depend on current choice** | ❌ No | ✔️ Yes |
| **Multiple ways to reach same state** | ❌ Ignore | ✔️ Track all |
| **Overlapping subproblems** | ❌ Not handled | ✔️ Core idea |
| **Need to explore all possibilities** | ❌ No | ✔️ Yes |
| **Constraints (cooldown, fee, limits)** | ❌ Breaks | ✔️ Handles |
| **State tracking required (e.g., hold/not hold)** | ❌ No | ✔️ Yes |
| **Problem asks for max/min over choices** | Sometimes | ✔️ Usually |
| **Transitions between states matter** | ❌ No | ✔️ Yes |
| **Greedy proof exists** | ✔️ Required | ❌ Not needed |

---

## ⚡ Quick Smell Test

| Question | If YES → Use |
|---------|-------------|
| Can I safely take the best option now without regret later? | Greedy |
| Does current decision affect future choices? | DP |
| Do I need to remember past states? | DP |
| Are there multiple valid paths to solution? | DP |

---

## 💡 Pattern Recognition

| Problem Pattern | Approach |
|---------------|--------|
| Increasing/decreasing sequences | Greedy |
| Interval scheduling | Greedy |
| Stock (no constraints) | Greedy |
| Stock (with constraints) | DP |
| Knapsack | DP |
| Coin Change | DP |
| Subsequence / substring | DP |
| Graph shortest path (weighted) | DP / Dijkstra |

---

## 🚨 Red Flags (Greedy will FAIL)

- Cooldown between actions ❄️  
- Transaction fee 💸  
- Limited operations 🎯  
- Dependencies across steps 🔗  
- Need to revisit previous decisions 🔁  

👉 If you see these → **switch to DP immediately**

---

## 🧠 Mental Model

| Greedy | DP |
|-------|----|
| “Take best now” | “Evaluate all futures” |
| Fast instinct | Structured reasoning |
| Minimal memory | Stores states |
| Shortcut | Complete solution |

---

## 😏 One-Liner to Remember

> “If I can prove my choice is always safe → Greedy  
> If I’m unsure → DP saves me”

---

## 🚀 Pro Tip

> Start with DP → Understand full state space  
> Then optimize to Greedy **only if proof exists**

---

🔥 Master this table and you’ll stop guessing —  
you’ll **know exactly which approach to use**.
# 🧠 5. When to Use What?

---

## ✅ Use Greedy when:
- No constraints
- Independent profit segments
- Local optimal = global optimal

---

## ✅ Use DP when:
- Future decisions depend on current
- Constraints exist
- Multiple choices affect outcome

---
## 💡 Key Insight

> DP is NOT tracking transactions  
> It is tracking **state transitions**

---

# 🚨 6. Key DP Pattern You Learned

> “State Machine DP”

---

### Structure:

- States: Holding / Not Holding  
- Actions: Buy / Sell / Skip  
- Transition: Maximize profit  

---

## 💡 This pattern appears in:

- Stock problems
- Trading systems
- Resource allocation
- Game strategies

---

# ⚠️ 7. Overflow & Infinity Concepts (VERY IMPORTANT)

---

## 🔢 Data Type Limits

| Type | Max Value |
|------|----------|
| int | ~2 × 10⁹ |
| long long | ~9 × 10¹⁸ |

---

## 🚨 Why `INT_MAX` is dangerous

- Adding anything → overflow
- Causes incorrect results silently

---
INF = INT_MAX


---

## ✅ Good Practices

INF = INT_MAX / 2
INF = 1e9
INF = 1e18 (for long long)


---

## 💡 Golden Rule

> “Infinity in coding is fake —  
> make it large, but safe for addition”

---

# ⚡ 8. Why `1e9` is Used

- Large enough for constraints
- Safe within `int`
- Common placeholder for “infinity”

---

## ⚠️ Risks

- Multiple additions → overflow
- Confusion with actual values

---

# 🧠 9. Why Use `long long`

---

## ✅ Advantages

- Prevents overflow in intermediate steps
- Safer for DP and graphs
- Handles large sums

---

## ⚠️ Important Rule

> Even if final answer fits in `int`,  
> intermediate values might NOT

---

## ✅ Safe Conversion

- Only convert to `int` if value ≤ `INT_MAX`

---

# 🔥 10. DP Dimension Thinking

---

## 🧠 Rule:

> Number of DP dimensions = number of independent variables

---

### Examples:

| Situation | DP Type |
|----------|--------|
| Only index matters | 1D |
| Index + state (hold/not) | 2D |
| Left + right range | 2D |
| Index + transactions | 3D |

---

---

# ⚡ 11. Optimization Insight

---

## Step-by-step thinking:

1. Start with 2D DP (clear understanding)
2. Optimize to 1D (space optimization)

---

### 💡 Example here:

- 2 states → can be stored in variables
- No need for full DP table

---

# 🧠 12. Core Learning Summary

---

### 🔥 What you should remember:

- Greedy = shortcut of DP
- DP = handles all constraints
- State transitions > counting actions
- Always think in terms of **states**

---

### ⚡ Key Concepts You Mastered:

- State-based DP
- Transition logic
- Overflow handling
- Choosing correct data types
- When greedy fails

---

# 😏 13. Final Mental Model

> Greedy: “Grab profit whenever possible”  
> DP: “Track all possibilities and choose best”

---

# 🚀 14. Where This Applies Next

You can now handle:

- Stock with fee 💸  
- Stock with cooldown ❄️  
- Stock with k transactions 🎯  
- Knapsack problems 🎒  
- Coin change 💰  
- Graph shortest paths 🛣️  

---

# 💬 Final Thought

> You’re no longer just solving problems —  
> you’re learning how to **model decisions over time**

---

🔥 If you truly get this,  
you’ve unlocked one of the most powerful DP patterns in interviews.

## ❌ Bad Practice
