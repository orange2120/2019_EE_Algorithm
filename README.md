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
~~Can be treated as Reversing Deleting MST problem.~~ ← The performance is not good in this implementation.
Using Kruskal's algorithm to find the removed edges not in the Maximum Spanning Tree.

### Directed graph
Known as minimum feedback arc set problem
Is a NP-hard problem.

Adjacency list
```
[V0]->V1->V3...
[V1]->
[V2]->
...
[Vn]->
```

`V_i : pair(<vertex index>,<weight>)`  

Method 1 : Directly perform DFS  
1. DFS to find cycle.
2. Backtrack all vertices in the cycle.
3. Find the minimum weight edge then set a flag.
4. Repeat until there are no cycles.
5. Output edges which is labeled to remove.

Method 2 :  Derive from MST
1. Treat the graph as undirected graph, perform Kruskal to find MST.  
2. We got the removed edge list.  
3. Add the edges from the list edge by edge back to the graph if there is no cycle.  
※ Heuristic : only add positive weight edges back to the graph to minimize the cost. (That is, adding negative weight edges to "Removed" edge list.)

### Test cases
For `public_cases/public_case_N.in`:
`1, 2, 4, 5, 6`: undirected weighted
`3, 7, 8`: directed weighted