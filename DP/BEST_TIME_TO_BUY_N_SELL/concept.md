# 📈 Best Time to Buy and Sell Stock III — FULL MASTERY GUIDE

> From brute force ➝ DP ➝ optimized state machine  
> Goal: Not just solve… but *understand like a beast* 🧠🔥

---

# 🧠 Problem Essence

- You can make **at most 2 transactions**
- Each transaction = **buy → sell**
- You cannot hold multiple stocks at once
- Objective: **maximize total profit**

---

# 🚨 Core Challenge

Unlike simpler stock problems:
- You **cannot greedily take all profits**
- You must **strategically split transactions**

---

# 🧪 Naive Thinking (Your Initial Idea)

> “Let me try all subarrays and combine profits”

### ❌ Issues:
- Time complexity → **O(n³)**
- Hard to manage **global optimal split**
- Overthinking with `dp[i][j]`

👉 Good intuition, wrong abstraction.

---

# 🧠 Real Insight

This problem is NOT about:
- subarrays ❌
- intervals ❌

It IS about:
> **decisions evolving over time (STATE TRANSITIONS)** ✅

---

# 🧱 Step 1: DP Formulation (Full Table)
dp[i][k][0] → max profit on day i, k transactions left, NOT holding
dp[i][k][1] → max profit on day i, k transactions left, HOLDING

---

## 🔄 Transitions

### 🔵 Not Holding (sell state)
dp[i][k][0] = max(
dp[i-1][k][0], // do nothing
dp[i-1][k][1] + price // sell today
)

---

### 🟢 Holding (buy state)
dp[i][k][1] = max(
dp[i-1][k][1], // do nothing
dp[i-1][k-1][0] - price // buy today
)

---

## ⚠️ Important Concept

👉 **Transaction count decreases on BUY, not SELL**

Why?
- Buying = starting a transaction
- Selling = completing it

---

# 📊 Step 2: Observing Redundancy

Notice:
- `dp[i]` depends only on `dp[i-1]`
- We don’t need full table ❌

👉 We can compress space

---

# 🔥 Step 3: Mapping DP → Variables

For **k = 2**, states become:

| DP State | Variable |
|--------|---------|
| dp[i][1][1] | buy1 |
| dp[i][1][0] | sell1 |
| dp[i][2][1] | buy2 |
| dp[i][2][0] | sell2 |

---

# ⚙️ Final Optimized Code (O(n), O(1))

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int buy1 = INT_MAX, buy2 = INT_MAX;
        int sell1 = 0, sell2 = 0;

        for (int p : prices) {
            buy1 = min(buy1, p);               // lowest price to buy first stock
            sell1 = max(sell1, p - buy1);      // best profit after first sell

            buy2 = min(buy2, p - sell1);       // effective cost after first profit
            sell2 = max(sell2, p - buy2);      // best profit after second sell
        }

        return sell2;
    }
};

We define:
