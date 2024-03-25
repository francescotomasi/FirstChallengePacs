### PACS Challenge 1: Gradient Method for Multivariate Function Minimization

This repository serves as the first assignment for the APSC course of 2023-2024. The C++ program provided implements gradient descent optimization techniques to identify the minimum of a specified function. It reads input parameters from a JSON file, conducts optimization, and presents the final result. Additionally, it offers options for adjusting step sizes through techniques like exponential decay, inverse decay, and Armijo rule.

#### Overview

The program is composed of the following components:

- **main.cpp:** Defines the objective function and its gradient, reads input parameters from a JSON file, and executes the optimization function.
- **utils.h:** Header file containing utility functions and data structures.
- **gradient_method.h:** Header file containing implementations of gradient descent methods and alpha methods.

#### Objective Function

The objective function and its gradient, subject to optimization, are defined within main.cpp. By default, the objective function is set to:

```
f(x) = x[0] * x[1] + 4 * pow(x[0], 4) + pow(x[1], 2) + 3 * x[0]
```

Users can adapt these functions in main.cpp according to their specific optimization problems.

#### Requirements

- C++ compiler supporting C++11.
- JSON for Modern C++ library for parsing JSON files.

#### Usage

1. Clone the repository.
2. Modify the `LIB_ROOT` variable in the Makefile.
3. Adjust the data.json file with desired parameters.
4. Compile and execute the program:

```bash
make
./main
```

if it doesn't run, try to put in the terminal LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/ .. /pacs-examples/Examples/lib

#### Input Parameters

Optimization parameters are provided through a JSON file (data.json). Supported parameters include:

- `epsilon_residual`: Tolerance for residual (default: 1e-6).
- `epsilon_step`: Tolerance for step (default: 1e-6).
- `alpha_0`: Initial step size (default: 0.1).
- `mu`: Decay parameter (default: 0.2).
- `max_iterations`: Maximum number of iterations (default: 10000).
- `sigma`: Parameter for Armijo rule (default: 0.2).
- `x0`: Initial guess for optimization (default: [0.0, 0.0]).
- `alpha_method`: Alpha selection method (0 for Armijo rule, 1 for exponential decay, 2 for inverse decay) (default: 0).

#### Output

The program outputs:

- The selected optimization method.
- The optimal values of x where the minimum is found.
- The minimum value of the objective function f(x) at the optimal point.

#### Example data.json

```json
{
  "epsilon_residual" : 1e-6,
  "epsilon_step" : 1e-6,
  "alpha_0" : 0.1,
  "mu" : 0.2,
  "max_iterations" : 10000,
  "sigma" : 0.2,
  "x0" : [0.0, 0.0],
  "alpha_method" : 0
}
```