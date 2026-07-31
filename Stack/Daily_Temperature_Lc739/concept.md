# 📚 Monotonic Stack - Next Greater Element Pattern (README)

# 🎯 Goal

Monotonic Stack is **not a separate data structure**. It is simply a stack maintained in a specific order so that it helps answer "nearest" or "next/previous" element questions in **O(n)** instead of **O(n²)**.

The biggest mistake beginners make is trying to memorize problems.

Instead, memorize **the pattern**.

---

# 🧠 Step 1 : Identify the Pattern

Whenever a question contains words like

- Next Greater
- Next Smaller
- Previous Greater
- Previous Smaller
- First larger element
- First smaller element
- Nearest greater
- Nearest smaller
- Waiting for something better
- Distance to next greater
- Index of next greater
- Days until...
- Warmer day
- Taller building
- Discount after...
- Span
- Visibility

your first thought should be

> "Can a Monotonic Stack solve this?"

---

# 🧠 Step 2 : Ask Yourself Three Questions

Before writing anything, answer these.

### Question 1

Who is waiting?

Current element?

Previous elements?

Future elements?

The one who is waiting usually goes inside the stack.

---

### Question 2

What am I waiting for?

Greater element?

Smaller element?

Equal element?

First greater?

Strictly greater?

Greater or equal?

One symbol (`>` vs `>=`) changes the entire solution.

Never ignore this.

---

### Question 3

Which direction makes more sense?

Can future elements answer previous ones?

→ Traverse Left to Right

Can previous elements answer current one?

→ Traverse Right to Left

Both directions are valid for many problems.

Choose whichever makes the logic simpler.

---

# 🧠 The Biggest Idea

A stack stores **elements whose answer is still unknown.**

As soon as the required element appears,

their waiting ends,

their answer is fixed,

and they leave the stack forever.

Think of it like a queue of students waiting for interview results.

The moment a student's result comes,

they leave the queue permanently.

---

# 📌 Why is Time Complexity O(n)?

People often think

"There is a while loop inside a for loop."

So shouldn't it be O(n²)?

No.

Every element

- enters the stack once
- leaves the stack once

It can never come back.

So every element is processed at most twice.

Hence

O(n)

This is called **Amortized Analysis**.

---

# 🎯 When Do We Pop?

Always ask

"Can the current element finally answer the element at the top?"

If Yes

Pop.

Keep popping until

- stack becomes empty

OR

- top can no longer be answered.

Never pop only once unless the question specifically requires it.

---

# 🎯 What Does the Stack Represent?

The stack is NOT storing random elements.

It always represents

> "People still waiting for an answer."

If an element already has its answer,

it has no reason to remain.

---

# 📌 Should I Store Values or Indices?

This is probably the most common mistake.

Store **indices** whenever the question asks for

- distance
- position
- number of days
- index
- answer in original order

Store **values** only when the value itself is sufficient.

Whenever confused,

store indices.

From an index you can always get

- value
- position
- distance

The reverse is impossible.

---

# 📌 Strict vs Non-Strict Comparison

This is one of the easiest places to make mistakes.

Carefully read the question.

Does it say

Greater

or

Greater than or Equal?

Smaller

or

Smaller than or Equal?

One extra '=' completely changes which elements stay in the stack.

Never assume.

Read twice.

---

# 📌 Direction Selection

## Traverse Left → Right

Useful when

Current element is solving older elements.

Think

"I finally found what previous elements were waiting for."

---

## Traverse Right → Left

Useful when

Future elements already exist.

Current element wants to know something about the future.

Think

"I already know everything on my right."

---

# 🎯 How to Build the Intuition

Imagine every element asks

> "Who is my first bigger neighbour?"

or

> "Who is my first smaller neighbour?"

Instead of checking everyone one by one,

maintain only the useful candidates.

Anyone who can never become someone's answer is removed immediately.

---

# 🚨 Common Mistakes

## Mistake 1

Choosing the wrong comparison operator.

Read carefully.

Greater?

Greater or Equal?

Smaller?

Smaller or Equal?

---

## Mistake 2

Storing values when indices are required.

If distance or index is needed,

store indices.

---

## Mistake 3

Forgetting that multiple pops may happen.

One current element can answer many previous elements.

Always use a while loop.

---

## Mistake 4

Not understanding what the stack represents.

Every element inside the stack is still waiting.

No exceptions.

---

## Mistake 5

Trying to memorize code.

Instead memorize

- Who is waiting?
- What are they waiting for?
- When should they leave?

The code will come naturally.

---

## Mistake 6

Forgetting duplicates.

Questions involving equal values are usually where wrong answers happen.

Always check whether '=' belongs in the comparison.

---

## Mistake 7

Thinking the top of the stack is always the answer.

It is only the answer after removing every invalid candidate.

---

# 🎯 Generic Thinking Process

Whenever you see a problem,

follow this checklist.

✅ Is it asking for nearest/next/previous?

↓

✅ Greater or Smaller?

↓

✅ Left side or Right side?

↓

✅ Who is waiting?

↓

✅ What should the stack store?

↓

✅ When should elements be removed?

↓

✅ Do I need indices or values?

↓

✅ Are duplicates important?

↓

Start coding only after answering these.

---

# 🔥 Mental Model

Imagine every element standing in a line.

Each one is searching for someone.

Some are searching for a taller person.

Some for a shorter person.

Some for the first warmer day.

Some for a cheaper price.

The stack simply keeps those people who haven't found their match yet.

Whenever a new element arrives,

it either

- becomes someone's answer,

or

- starts waiting itself.

Nothing more.

---

# 📝 Final Thumb Rules

✔ Think "waiting elements."

✔ Stack contains unresolved elements.

✔ One element enters once.

✔ One element leaves once.

✔ Always question the comparison operator.

✔ Prefer storing indices.

✔ Pop until the stack becomes valid.

✔ Don't memorize code.

✔ Memorize the thought process.

✔ If the question contains "next", "previous", "nearest", or "first", check whether a Monotonic Stack fits before considering other approaches.

---

# 💡 Golden Line

> **A Monotonic Stack is nothing more than a collection of unresolved elements maintained in an order such that the current element can resolve as many of them as possible in one pass.**
