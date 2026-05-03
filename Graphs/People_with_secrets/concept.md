# 🧠 LeetCode 2092 — Find All People With Secret

---

## 🎯 Core Problem Essence

You are tracking how **information spreads over time** through meetings.

But here’s the twist:

> ⏱️ Meetings happening at the same time are **simultaneous**, not sequential.

So you are NOT simulating a timeline step-by-step —
you are processing **time-based batches of interactions**.

---

## 🧠 The Golden Mental Model

> “Connections exist temporarily at a given time, but only survive if the secret flows through them.”

---

## 🔥 Key Concepts You MUST Understand

### 1. ⏱️ Time-Based Grouping (Batch Processing)

* Meetings are grouped by **same timestamp**
* All interactions at that time happen **together**
* No ordering inside same time matters

👉 Treat each timestamp as a **mini world**

---

### 2. 🧱 Temporary Connectivity (Dynamic Groups)

* At a given time, people form **connected components**
* These components represent **who can influence whom instantly**

👉 Think: “Who is in the same network right now?”

---

### 3. 🧠 Secret Propagation Rule

Inside each time group:

* If **any one person knows the secret**
  → the **entire connected component learns it**

* If **no one knows**
  → no one learns anything

👉 Spread happens **instantly within a component**

---

### 4. ✂️ Reset / Pruning Concept (CRITICAL)

After processing a time group:

* If a component **did NOT receive the secret**
  → its connections must be **discarded**

👉 Why?

Because:

* Those connections were only valid at that time
* They should NOT affect future interactions

---

### 5. 🌍 Global vs Local Thinking

| Concept          | Scope                           |
| ---------------- | ------------------------------- |
| Secret knowledge | Global (persists forever)       |
| Connections      | Local (valid only at that time) |

👉 This separation is the **core trick of the problem**

---

### 6. 🔗 Connectivity Tracking (DSU Insight)

* You maintain a structure that tracks **who is connected**
* But it must support:

  * **forming connections**
  * **checking groups**
  * **removing invalid connections**

👉 This is where DSU (Union-Find) fits perfectly

---

### 7. 🧩 Component-Based Thinking

Instead of thinking person-by-person:

👉 Think in terms of **connected components**

For each component:

* Check → does it contain a secret holder?
* If yes → entire component becomes “aware”
* If no → component is irrelevant → discard

---

### 8. 🧠 State Separation (VERY IMPORTANT)

You must separate:

| Thing        | Meaning                          |
| ------------ | -------------------------------- |
| Connectivity | who is linked (temporary)        |
| Knowledge    | who knows the secret (permanent) |

👉 Mixing these leads to wrong answers

---

## ⚠️ Common Pitfalls (Interview Traps)

### ❌ Thinking order matters within same time

→ It does NOT (everything is simultaneous)

---

### ❌ Keeping connections forever

→ Leads to false spreading in future

---

### ❌ Not resetting invalid groups

→ Causes incorrect propagation

---

### ❌ Mixing DSU structure with “secret state”

→ DSU should NOT represent knowledge

---

### ❌ Using parent directly instead of root

→ Breaks component grouping

---

## 🚀 High-Level Flow (Pure Logic)

For each time:

1. Form connections among meeting participants
2. Identify connected groups
3. Check which groups contain a secret holder
4. Spread secret within those groups
5. Remove groups that didn’t receive the secret

---

## 🧠 Intuition Lock (Analogy)

Imagine:

* Each timestamp = a **temporary party 🎉**
* People form groups and interact
* If someone brings gossip:
  → whole group knows instantly

If no one has gossip:
→ party ends, nothing spreads

👉 No memory of connections unless gossip passed

---

## 🎯 Final Takeaway

> “Simulate time in batches, track temporary connections, and only preserve those where information actually flows.”

---

## ⚡ Interview Power Line

If you had to explain in one sentence:

> “We group meetings by time, form temporary connections, propagate the secret within connected components, and discard connections that don’t contribute to the spread.”

---

## 🧩 Why This Problem Is Special

This problem tests:

* Dynamic graph thinking
* Time-based state transitions
* Separation of structure vs information
* Controlled propagation logic

---

## 🏁 Mastery Check

If you understand this fully, you should be able to answer:

* Why order inside same time doesn’t matter
* Why resetting connections is required
* Why DSU alone is not enough without pruning
* How information persists but connections don’t

---

## 🚀 Final Thought

This is not just DSU.

This is:

> **“DSU + Time + Controlled Information Flow”**

---

Stay sharp. This pattern shows up in real-world systems like
network propagation, event simulation, and distributed syncing ⚡
