# ♛ N-Queen Genetic Algorithm in Python

This project solves the classical N-Queen Problem using a Genetic Algorithm (GA) implemented in Python.

The N-Queen problem requires placing N queens on an N×N chessboard so that no two queens attack each other — meaning no two queens share the same row, column, or diagonal.

---

## 🧠 Algorithm Overview

- Language: Python 3  
- Method: Genetic Algorithm  
- Key Features:
  - Permutation-based representation
  - Fitness = number of diagonal conflicts
  - Elitism & selection
  - PMX (Partially Mapped Crossover) & Single-Point crossover supported
  - Random swap mutation

---

## 🧬 Genetic Operators

### ✅ Crossover

- Single-Point Crossover: Basic crossover that preserves partial order.
- PMX (Partially Mapped Crossover): Maintains valid permutations, ideal for N-Queen.

### ✅ Mutation

Randomly selects two genes (columns) and swaps them to introduce diversity.

---

## 📂 Files

- n_queen_ga.py → Python source code with Genetic Algorithm
- README.md → This documentation file

---

## ▶️ How to Run

1. Install Python (version ≥ 3.6)
2. Run the file:

`bash
python n_queen_ga.py

