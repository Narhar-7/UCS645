

## Introduction

This project computes the Pearson correlation between rows of a matrix.  
The goal is to understand how parallel programming improves performance when handling large computations.

The program compares performance using different numbers of threads.

---

## Problem Statement

Given a matrix of size **ny × nx**, each row represents a vector.

We compute the correlation between every pair of rows (i, j) such that:

0 ≤ j ≤ i < ny

The result is stored using:

result[i + j * ny]

Only the lower triangular matrix is stored because the correlation matrix is symmetric.


---

## Implementation 

### 1. Sequential Version
- Single-threaded
- Direct computation
- Used as baseline for comparison

---

### 2. OpenMP Parallel Version
- Uses multiple CPU cores
- Parallelizes outer loops
- Improves execution time significantly

---

### 3. Optimized Version
This version improves performance further by:

- Normalizing rows (mean = 0, variance = 1)
- Reducing correlation to dot products
- Improving memory access patterns
- Using OpenMP + SIMD vectorization

---

## System Used

OS: Ubuntu (WSL2)  
Compiler: g++ with OpenMP support  
CPU: 4 cores  

---

## Sample Performance Results (400 × 400 Matrix)

Threads    Sequential    OpenMP    Optimized
--------------------------------------------
1          0.051 s       0.052 s   0.051 s
2          0.050 s       0.026 s   0.026 s
4          0.050 s       0.014 s   0.015 s
8          0.062 s       0.025 s   0.020 s

---

## Observations

• Performance improves significantly when using multiple threads  
• Near-linear speedup observed up to 4 threads  
• Performance drops at 8 threads due to system being 4 cores
• Optimized version performs better for larger workloads  

---

## Optimization Techniques Used

• Computed only half the matrix (symmetry)  
• Row normalization to simplify calculations  
• OpenMP multithreading  
• SIMD/vectorization hints  
• Cache-friendly memory access  
• Compiler optimization (-O3)

---

## Complexity

Time Complexity: O(ny² × nx)  
Memory Usage: O(ny × nx)  

---

## Key Learnings

• Parallel programming greatly reduces computation time  
• Thread scaling is limited by hardware resources  
• Memory access patterns affect performance  
• Optimization techniques can significantly improve speed  

