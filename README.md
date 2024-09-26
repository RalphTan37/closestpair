# Finding the Closest Pair of Given Points in the Plane

The program contains a main driver that parses commandline arguments with the following form: </br>
```driver A N [S]``` </br>
where **A** is an integer with value 0,1, or 2 that designates the algorithm to be used, **N** is the number of the points in the data set, and **S** is an (optional) integer seed to the random-number generator, thereby allowing you to repeat trials on the same data set. </br>

Algorithm "0" is the quadratic-time brute force implementation. </br>
Algorithm "1" is the divide-and-conquer algorithm. </br>
Algorithm "2" is an optimized algorithm. </br>

The driver takes care of pseudorandomly generating N points with nonnegative integer coordinates, sending the points as a parameter to the indicated algorithm, and reporting the running time of the algorithm. The codebase already includes an implementation of a basic Point struct with fields x and y, together with useful utility functions: </br>

**distSquared(a, b)**, which returns the square of the distance between points a and b. Note that we rely on using the square of the distance rather than the actual distacne because this allows us to use exact comparision of integer values, rather than the floating-points that would result from a square-root computation if computing the actual distance. </br>

**compareByX(a, b)**, a boolean function that can be used with the standard sorting tools to sort a collection of points according to x-coordinate (and using the y-coordinate as a tie-breaker). </br>

**compareByY(a, b)**, a boolean function that can be used with the standard sorting tools to sort a collection of points according to y-coordinate (and using the x-coordinate as a tie-breaker). </br>

The codebase also includes the definition for a simple Outcome struct, which allows an algorithm to return the pair of closests points and the square of the distance between them. </br>

