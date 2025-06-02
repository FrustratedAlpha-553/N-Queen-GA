
# ♛ N-Queen Genetic Algorithm in Python & C

This project solves the classical **N-Queen Problem** using a **Genetic Algorithm (GA)** implemented in both **Python** and **C**.

The N-Queen problem requires placing N queens on an N×N chessboard so that no two queens attack each other — meaning no two queens share the same row, column, or diagonal.

---

## 🧠 Algorithm Overview

- **Languages**: Python 3, C (ANSI C standard)
- **Method**: Genetic Algorithm
- **Key Features**:
  - Permutation-based representation
  - Fitness = number of diagonal conflicts
  - Elitism & selection
  - Crossover:
    - PMX (Partially Mapped Crossover)
    - Single-Point Crossover
  - Mutation:
    - Random swap mutation for diversity

---

## 🧬 Genetic Operators

### ✅ Crossover

- **Single-Point Crossover**: Preserves partial order and structure.
- **PMX (Partially Mapped Crossover)**: Ensures valid permutations, ideal for N-Queen solutions.

### ✅ Mutation

- Swaps two randomly selected genes (columns) to introduce variation.

---

## 📂 Project Structure

- `n_queen_ga.py` → Python implementation of Genetic Algorithm
- `n_queen_ga.c` → C implementation of Genetic Algorithm
- `README.md` → Project documentation

---
