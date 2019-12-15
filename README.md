# Algorithms, 2019 Fall (EE 4003 02)
Algorithms course programming homeworks

## PA0

## PA1
Implement Insersion Sort, Merge Sort, Quick Sort and Heap Sort.

### Test program
Program for testing test cases

#### Usage
```bash
$ python3 test.py <options>

Options:
-IS → Insersion Sort
-MS → Merge Sort
-QS → Quick Sort
-HS → Heap Sort
```

## PA2 Max Planar Subset

Run test
```bash
$ ./run
```

## PA3 Cycle Breaking
Given a graph `G= (V, E)` which may containcycles, we want to remove some edges to make the graph acyclic with minimum total cost.  

### Undirected graph
Can be treated as Reversing Delete MST problem.

### Directed graph
Is a NP-hard problem.