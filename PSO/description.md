# PSO: Particle Swarm Optimization

Basically, in this problem, we implement PSO to optimize 4 functions:
1. f1: Rastrigin (d = 2 variations and 10 variations).
2. f2: Rosenbrock (d = 2 variations and 10 variations)
3. f3: Eggholder (d = 2 variations)
4. f4: Ackley (d = 2 variations)
\
using two neighbourhood topology: T = star and T = ring.\
Further information about these functions can be found on this [link](https://en.wikipedia.org/wiki/Test_functions_for_optimization).

Core conceopt of PSO is to maintains a swarm (i.e., a population) of particles that move through the search space. Each particle determines its movement based on:
* Its current position.
* Its best previous position.
* Its neighbors’ best previous position.
\
A more detailed algorithm can also be found [here](https://en.wikipedia.org/wiki/Particle_swarm_optimization#Algorithm).

In this problem, we set constant values to *w* and *c_1 = c_2* as 0.7298 and 1.49618 respectively.

The 'log' folder contains log files of each combination of f and T. A log file has information of random seed, best solution and objective value of PSO.\
The 'contour' folder contains contour motion picture of each combination of f and T through 50 generations.
