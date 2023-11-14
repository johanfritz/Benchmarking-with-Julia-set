## Benchmarking using the Julia set
The purpose is the assess the performance of some programming languages for computational programming.
The programms are run on my Dell XPS 13 laptop running Ubuntu 22.xx, with the powersaving-mode set to *performance*.
# Background: 
For the general definition of the Julia set, please consult external sources. For the purposes of this experiment, a more strict definition has been used: it contains all compex numbers $z$ such that the recursive formula 
$$z_{n+1}=z_n^2+c, $$ 
where $c$ is some complex number, converges. Because no general formula can be given for $z_n$, we are left to approximate convegence. This is done in the following steps:

1. Assume that $z_n$ diverges if its norm is greater than 1.5;  $|z_n|>1.5$.
1. Assume that $z_n$ convergers (using the above definition for divergence) if $z_{100}<1.5$.

The above approximations leave us with a simple algorithm for testing convergence, which can then be implemented in different programming languages. 


# Python

# Julia

# C++