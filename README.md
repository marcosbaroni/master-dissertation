# My Master Dissertation Implementation

Author: Marcos Daniel Baroni

Date: 2012-01-27

This work treats the application of the eigenvector centrality in solving the Graph
Isomorphism Problem. This property, taken from spectral graph theory, was used
by Philippe Santos in [S ANTOS 2010] to propose a spectral algorithm for solving this
problem. An adaptation of the power method is proposed to compute the eigenvec-
tor centrality, producing a competitive version to the spectral algorithm of [S ANTOS
2010]. Based on this adaptation, the efficiency of the eigenvector centrality in solving
the problem is studied. In addition, it is proposed an iterative labeling algorithm, cal-
led Centrality Based Iterative Algorithm, which can be applied to any type of graph,
including regular ones. Several tests are performed to compare the two proposed
algorithms with some others well-known algorithms from literature, such as Nauty.

KEYWORDS: Graph theory, Isomorphims, Algorithms, Eigenvectors.

### Execution
Compile and execute program:
```
make
./isom g1.txt g2.txt
```
where g1.txt and g2.txt are plain text adjacency matrix. (Please check example)

### The dissertation (pt-br): [dissertation-mbaroni-2012.pdf](dissertation-mbaroni-2012.pdf?raw=true)

### Paper about the approach (en): [paper.pdf](paper.pdf?raw=true)

### Results summary
(todo)
