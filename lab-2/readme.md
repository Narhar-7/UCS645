# UCS645 - Parallel & Distributed Computing  
## Lab 2: Performance Evaluation of OpenMP Programs

### Question 1: Molecular Dynamics – Lennard-Jones Force Calculation

Compute pairwise Lennard-Jones forces and total potential energy for N particles in 3D.

Parallelization strategy:

- Outer loop parallelized using OpenMP
- Atomic operations used for force accumulation
- Reduction used for total energy
- Dynamic scheduling used for better load balancing

## Performance Results

Dynamic scheduling used for better load balancing
| Threads | Time (s) | Speedup | Efficiency |
|---------|----------|---------|------------|
| 1       | 0.103977 | 1.00184 | 1.00184    |
| 2       | 0.0539918| 1.92933 | 0.964667   |
| 4       | 0.0271062| 3.84297 | 0.960742   |
| 8       | 0.0276139| 3.77231 | 0.471538   |

## Analysis

- Near-linear scaling up to 4 threads.
- Efficiency at 4 threads ≈ 91%.
- At 8 threads, performance plateaus due to hardware limitation (4 physical cores).


# Question 2: Smith-Waterman DNA Sequence Alignment

## Problem Description

Implementation of local sequence alignment using dynamic programming:

H(i,j) = max(0, diagonal + match/mismatch, up + gap, left + gap)

Parallelization strategy:

- Wavefront (anti-diagonal) parallelization
- Reduction for maximum alignment score
- Synchronization occurs at every diagonal

Matrix size: 10000 × 10000

**Performance Results:**

| Threads | Time (s) | Speedup | Efficiency |
|---------|----------|---------|------------|
| 1       | 6.924757 | 1.000000 | 1.000000 |
| 2       | 4.037569 | 1.715081 | 0.857540 |
| 4       | 2.748181 | 2.519761 | 0.629940 |
| 8       | 7.644054 | 0.905901 | 0.113238 |

## Analysis:
- Moderate scaling up to 4 threads.
- Efficiency drops to 63% at 4 threads.
- Performance degrades at 8 threads due to oversubscription.


## Analysis

- Moderate scaling up to 4 threads.
- Efficiency drops to 63% at 4 threads.
- Performance degrades at 8 threads due to oversubscription.
- Wavefront structure limits parallelism.
- Synchronization barrier at every diagonal reduces scalability.
- Reduction overhead contributes to performance loss.

Compared to Molecular Dynamics, Smith-Waterman shows reduced scalability due to structured data dependencies and synchronization costs.

---

# Question 3: 2D Heat Diffusion Simulation

## Problem Description

Simulate heat diffusion using finite difference method:

T_new(i,j) = 0.25 × [T(i+1,j) + T(i-1,j) + T(i,j+1) + T(i,j-1)]

Parallelization strategy:

- Parallel spatial loop
- No race conditions (each thread writes to unique cell)
- One barrier per time step
- Reduction used for total heat computation

Grid size: 2000 × 2000  
Time steps: 500  

## Performance Results

| Threads | Time (s) | Speedup | Efficiency |
|---------|----------|---------|------------|
| 1       | 38.351733| 1.000000| 1.000000   |
| 2       | 16.969854| 2.259992| 1.129996   |
| 4       | 9.276156 | 4.134442| 1.033611   |
| 8       | 9.438288 | 4.063420| 0.507928   |

Final Total Heat: 1000.000000

## Analysis

- Near-ideal scaling up to 4 threads.
- Superlinear speedup observed at 2 and 4 threads.
- Efficiency > 1 due to improved cache utilization.
- At 8 threads, performance saturates due to hardware limits.


