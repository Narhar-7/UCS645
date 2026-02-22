# Assignment 4 – Introduction to MPI

## Objective

The aim of this assignment is to understand the basics of MPI (Message Passing Interface) and how parallel programs run using multiple processes.

---

## Exercise 1: Ring Communication

### Problem
- Process 0 starts with value **100**  
- Each process adds its rank  
- Value travels in a ring topology  
- Final value returns to Process 0  

### Output
```
Process 0 starts with value: 100
Process 1 updated value to: 101
Process 2 updated value to: 103
Process 3 updated value to: 106

Process 0 received final value: 106

(4 cores used)
```

---

## Exercise 2: Parallel Array Sum

### Problem
- Create numbers from **1 to 100**  
- Divide the array among processes  
- Each process computes its partial sum  
- Combine results using MPI_Reduce  
- Expected sum = **5050**

### Output
```
Global Sum = 5050
Average = 50.5
```

---

## Exercise 3: Global Maximum & Minimum

### Problem
- Each process generates 10 random numbers  
- Find local maximum & minimum  
- Compute global maximum & minimum  
- Identify which process found them  

### Output
```
Process 3 Local Max: 975 Local Min: 56
Process 0 Local Max: 863 Local Min: 21
Process 1 Local Max: 968 Local Min: 17
Process 2 Local Max: 944 Local Min: 89

Global Maximum: 975 (Process 3)
Global Minimum: 17 (Process 1)
```

---

## Exercise 4: Parallel Dot Product

### Problem

Compute dot product of:

```
A = [1,2,3,4,5,6,7,8]
B = [8,7,6,5,4,3,2,1]
```

Expected result:

```
120
```

### Output
```
Dot Product = 120
```

---

## Performance Metrics

### Speedup
```
S = T₁ / Tₚ
```

### Efficiency
```
E = S / p
```

---

## Notes

- Programs were executed using **4 cores**.
- Output values may vary for Exercise 3 due to random numbers.
- MPI enables efficient parallel computation using multiple processes.
