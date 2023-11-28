# Benchmarking using the Julia set

The purpose is the assess the performance of some programming languages for computational programming.
The programms are run on my Dell XPS 13 laptop running Ubuntu 22.xx, with the powersaving-mode set to *performance*.

## Results

The time in the table below is the time to determine convergence of a single elements, in nanoseconds, and the number in the elements column refers to the total number of elements that was calculated, when measuring the performance.

|Language|Time (ns)| Elements (millions)|
|:--|:--|---|
|Python|1303|16|
|Julia|35|64|
|C++|82|77.44|
|Matlab|||

## Background

For the general definition of the Julia set, please consult external sources. For the purposes of this experiment, a more strict definition has been used: it contains all compex numbers $z$ such that the recursive formula
$$z_{n+1}=z_n^2+c, $$
where $c$ is some complex number, converges. Because no explicit formula can be given for $z_n$, we are left to approximate convergence. This is done in the following steps:

1. Assume that $z_n$ diverges if its norm is greater than 1.5;  $|z_n|>1.5$.
1. Assume that $z_n$ convergers (using the above definition for divergence) if $z_{n}<1.5 \quad\forall\quad n\in[0, 200]$.

The above approximations leave us with a simple algorithm for testing convergence, which can then be implemented in different programming languages.

## Implementation

The algorithm above can be implemented in a number of ways. The easiest is to simply use some representation of complex numbers, and implement the algorithm above. For the purposes of this experiment, I let $c=-0.4+0.6i$, and set the iteration limit to 200. The algorithm looked like this:

```
function converge (complex z)
    int k from 0 to limit
        z = z * z + c
        if norm(z) > 1.5
            return k
        end
    return limit
end
```

This works fine, but using complex numbers leaves us with alot of computational overhead. Since only addition and multiplication need to be done, this can easily be midigated. Let $z=a+bi$ be a complex number and consider that $z^2=a^2-b^2+2abi$, which leave us with an implementation of the above algorithm, taking the real and imaginary parts of the complex number $z$, respectivelly:

```
function converge(float a, float b)
    int k from 0 to limit
        a, b = (a * a - b * b, 2 * a * b)
        a, b += (real(c), imag(c))
        if a * a + b * b > 2.25
            return k 
        end
    return limit
end
```

which proved to be significantly faster, regardless of language. Not only is it faster, but it also makes for a more reasonable comparison, as the structures for complex numbers may differ as language varies. Removing the need for language-dependent complex number-structure, makes for a more fair comparison. The language that benefitted the most from this was C++. It should further be noted that the time compared was the average computation time for a large matrix.

### Note regarding python code

In the Python implementation, the numpy function `np.vectorize()` was used. There was slight concern that this would unfairly benefit the Python performance, however, reading the numpy documentation, one can gather that: 
>The vectorize function is provided primarily for convenience, not for performance. The implementation is essentially a for loop.
(from )