# C++ Static, Inline, Const & Compile-Time Constants

## 1. Why These Keywords Matter

When writing C++, especially for competitive programming, you will often see:

- `static`
- `const`
- `inline`
- `constexpr`
- compile-time constant
- run-time object

They solve **different problems**. The most important thing is not to treat them as interchangeable keywords.

A useful mental model is:

> **`static` → who owns it / how long it exists**  
> **`const` → can it be modified?**  
> **`constexpr` → can its value be evaluated at compile time?**  
> **`inline` (for variables) → where can the definition live?**

---

# 2. `static` Class Members

A normal data member belongs to each object.

Conceptually:

    Object A → its own x
    Object B → its own x
    Object C → its own x

A `static` class member belongs to the **class**, so there is only one shared member.

    Class
      │
      └── static x
           ↑
       shared by
       all objects

Example idea:

    class A {
        static int x;
    };

`x` is associated with `A`, not with each individual object.

It can conceptually be accessed as:

    A::x

### Important

`static` does **not** mean:

- constant
- compile-time
- faster
- immutable

It only describes the storage/ownership behavior of the member.

---

# 3. Static Member Definition

Historically, a static class member was usually:

1. Declared inside the class.
2. Defined outside the class.

Conceptually:

    class A {
        static int x;      // declaration
    };

    int A::x = 10;         // definition

### Declaration vs Definition

Think of:

> **Declaration:** "This thing exists."

> **Definition:** "Here is the actual thing/storage."

For many static data members, the class declaration alone was not enough.

---

# 4. Why `static const vector` Can Need an Outside Definition

A simple integral constant has historically had special treatment:

    static const int x = 10;

But an object such as:

    static const vector<string> mp = {...};

is different.

A `vector<string>` is an actual object and is not just a simple integral compile-time constant.

The traditional form is therefore:

    class A {
        static const vector<string> mp;
    };

    const vector<string> A::mp = {...};

The first line declares the member.

The second line defines it.

---

# 5. `const`

`const` means the object cannot be modified through that const object/reference after initialization.

Mental model:

    const → "don't change this"

For example, a const mapping is useful when your program only needs to read the mapping.

`const` does NOT automatically mean:

- static
- compile-time
- globally shared
- faster

These are separate concepts.

You can have:

    const int

without `static`.

You can have:

    static int

without `const`.

You can also combine them:

    static const int

Each keyword contributes its own meaning.

---

# 6. `inline static`

C++17 introduced **inline variables**.

This allows a static data member to be defined directly inside the class without requiring a separate out-of-class definition.

Conceptually:

    class A {
        inline static const vector<string> mp = {...};
    };

This is both:

- `static` → one shared class member
- `inline` → the definition can safely appear in the class definition

So the important distinction is:

    static
        → shared class member

    inline static
        → shared class member + definition can stay in class

### Important

Here, `inline` does NOT mean:

> "The compiler will definitely make it faster."

For variables, `inline` mainly solves the **One Definition Rule / multiple-definition** issue and allows the definition to be placed in the class definition.

---

# 7. Why Does `inline` Remove the Outside Definition?

Without `inline`:

    class A {
        static const vector<string> x;
    };

    const vector<string> A::x = {...};

With `inline static`:

    class A {
        inline static const vector<string> x = {...};
    };

The second version contains the definition directly inside the class.

So:

    static
       ↓
    declaration in class
       ↓
    traditional definition outside

while:

    inline static
       ↓
    definition can remain inside

This is one of the main reasons you may see `inline static` in modern C++.

---

# 8. `constexpr`

`constexpr` means a variable/function can participate in **constant-expression evaluation**.

The important idea is:

> The value is intended to be known/evaluable at compile time when the rules allow it.

For example:

    constexpr int x = 10;

The compiler knows the value of `x` at compile time.

`constexpr` is therefore much more closely related to **compile-time evaluation** than `static` or `const`.

---

# 9. Compile-Time Constant vs Run-Time Value

### Compile-time

The compiler can determine the value while compiling.

Conceptually:

    constexpr int x = 10;

The value is known before the program starts running.

### Run-time

The value is determined while the program is executing.

Conceptually:

    int x = getValue();

The compiler cannot generally replace this with a known constant because the value depends on run-time execution.

---

# 10. `const` vs `constexpr`

This distinction is VERY important.

### `const`

Means:

> This object cannot be modified after initialization.

It does **not** necessarily mean the value is known at compile time.

Conceptually:

    int n = getValue();
    const int x = n;

`x` cannot be changed after initialization, but its value was obtained at run time.

### `constexpr`

Means:

> This must satisfy the rules for a constant expression.

Conceptually:

    constexpr int x = 10;

So:

    const
      → immutable after initialization

    constexpr
      → compile-time constant-expression capable

A useful shortcut:

> **Every `constexpr` variable is const-like, but not every `const` variable is a compile-time constant.**

---

# 11. `static const` vs `static constexpr`

These are easy to confuse.

### `static const`

Means:

- one shared class member
- cannot be modified

But `const` alone does not communicate compile-time evaluation.

### `static constexpr`

Means:

- one shared class member
- compile-time constant-expression semantics

For example:

    static constexpr int x = 10;

This is a natural choice for fixed numeric constants.

---

# 12. Why `constexpr` Works Differently for Simple Types

Consider:

    static constexpr int x = 10;

This is a simple compile-time value.

The compiler can directly treat `10` as a constant expression.

But a structure like:

    vector<string>

is a much more complicated run-time object.

So don't assume:

> "If something is fixed, I can always make it constexpr."

Whether something can be `constexpr` depends on the type and the C++ standard/library support.

For your phone-number mapping, `inline static const vector<string>` is a simple modern choice.

---

# 13. Quick Comparison

| Keyword | Main idea |
|---|---|
| `static` | One shared class member |
| `const` | Cannot be modified after initialization |
| `constexpr` | Constant-expression / compile-time evaluation |
| `inline` variable | Definition can appear in the class/header safely |
| `static const` | Shared + immutable |
| `static constexpr` | Shared + compile-time constant |
| `inline static const` | Shared + immutable + definition can stay inside class |

---

# 14. The Mental Model to Remember

Instead of memorizing random syntax, ask four questions:

### Question 1 — Who owns it?

If one copy should be shared by the class:

    static

### Question 2 — Can it change?

If it should not change:

    const

### Question 3 — Must it be known at compile time?

If yes and the type supports it:

    constexpr

### Question 4 — Do I want the static definition directly inside the class?

If yes:

    inline static

This makes the keywords much easier to reason about.

---

# 15. Applying the Concepts to the Phone Mapping

The phone keypad mapping is:

- shared
- never modified
- fixed for the program
- used by multiple recursive calls

So the useful conceptual properties are:

    shared      → static
    immutable   → const
    in-class definition → inline

That is why a modern C++ declaration can naturally use:

    inline static const ...

There is no need to memorize this as a magic LeetCode trick.

It follows directly from what the data represents.

---

# 16. One More Important Distinction: Lifetime vs Compile Time

Do not mix these two ideas.

### Lifetime / storage

`static` is strongly associated with:

- shared class members
- static storage duration
- keeping an object alive for the appropriate static lifetime

### Compile-time evaluation

`constexpr` is associated with:

- constant expressions
- compile-time evaluation

They answer different questions.

A variable can be:

    static

without being:

    constexpr

And something can be:

    constexpr

without being a class static member.

---

# 17. Common Mistakes

### Mistake 1

Thinking:

    static = constant

Wrong.

`static` does not mean immutable.

---

### Mistake 2

Thinking:

    const = compile time

Not necessarily.

A const object can be initialized using a run-time value.

---

### Mistake 3

Thinking:

    inline = faster

Not for inline variables.

Here it primarily affects how the definition can be provided.

---

### Mistake 4

Thinking every fixed object should be `constexpr`

Not necessarily.

The type and language/library rules matter.

---

### Mistake 5

Thinking `inline static` means two copies

It does not.

It is still a **single static class member**.

`inline` changes the definition rules, not the ownership model.

---

# 18. Final Cheat Sheet

    static
    → shared class member / static storage semantics

    const
    → cannot modify after initialization

    constexpr
    → constant-expression / compile-time evaluation

    inline variable
    → definition can be placed in the class/header

    static const
    → shared + immutable

    static constexpr
    → shared + compile-time constant

    inline static const
    → shared + immutable + in-class definition

## Key Takeaway

Don't memorize:

> "vector needs inline static."

Instead reason:

> "I have one fixed mapping shared by the class, I don't want it modified, and I want to define it directly inside the class."

That naturally leads to:

**static + const + inline**

And that is the real C++ concept worth remembering.
"""
