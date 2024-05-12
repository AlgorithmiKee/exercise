# Path In Matrix

## Problem Formulation

Consider a binary matrix $M\in \{0, 1\}^{n\times m}$ as a map. Each cell $M[i,j]$ is reachable if $M[i,j]=1$, non-reachable otherwise. A "robot" starts from $M[0,0]$ and tries to reach $M[n-1,m-1]$. At each step, the robot can move either right or down if the subsequential cell is reachable. 

**Probem:** What is the number of all possible paths from $M[0,0]$ to $M[n-1,m-1]$?

For simplicity, you may assume that $M[0,0] = M[n-1,m-1] =1$ always holds

**Example:** given a 3 by 4 map
$$
 \begin{bmatrix}
    1 & 0 & 1 & 1 \\
    1 & 1 & 1 & 1 \\
    1 & 0 & 1 & 1 \\
 \end{bmatrix}
$$

There are two paths from $M[0,0]$ to $M[2,3]$ :

* `M[0,0] -> M[1,0] -> M[1,1] -> M[1,2] -> M[1,3] -> M[2,3]`
* `M[0,0] -> M[1,0] -> M[1,1] -> M[1,2] -> M[2,2] -> M[2,3]`

## The Algorithms

### Naive Recursion

### Memoized Recursion
