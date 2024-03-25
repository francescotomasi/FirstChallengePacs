#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#include "json.hpp" // JSON library
#include "utils.h" // Utility functions and data structures
#include "gradient_method.h" // Gradient descent optimization functions

using json = nlohmann::json;

int main() {
    // Define the objective function
    Function f = [](const std::vector<double>& x) {
        return x[0] * x[1] + 4 * pow(x[0], 4) + pow(x[1], 2) + 3 * x[0];
    };

    // Define the gradient of the objective function
    Gradient grad_f = [](const std::vector<double>& x) {
        return std::vector<double>{x[1] + 16*pow(x[0], 3) + 3, x[0] + 2*x[1]};
    };

    // Read parameters from a JSON file
    std::ifstream file("data.json");
    json j = json::parse(file);

    // Extract values from JSON and store them in a structure
    Data data;
    data.epsilon_residual = j.value("epsilon_residual", 1e-8); // Tolerance for how close the residual can be to zero
    data.epsilon_step = j.value("epsilon_step", 1e-8); // Tolerance for how small the step size can be
    data.alpha_0 = j.value("alpha_0", 0.1); // Initial step size for gradient descent
    data.mu = j.value("mu", 0.3); // Rate at which step size decreases
    data.max_iterations = j.value("max_iterations", 100); // Maximum number of iterations for optimization
    data.sigma = j.value("sigma", 0.2); // Parameter for Armijo rule to determine step size
    std::vector<double> initial_guess = j["x0"]; // Initial guess for the optimization algorithm
    data.x0 = initial_guess;
    data.alpha_method = j.value("alpha_method", 0); // Method for selecting step size

    std::vector<double> x_min(2); // Variable to store the minimum point found by optimization

    // Select optimization method based on the chosen step size selection method
    if (data.alpha_method == ARMIJO_RULE) {
        std::cout << "Using Armijo Rule for optimization" << std::endl;
        x_min = gradient_method(f, grad_f, data, armijo_rule);
    } else if (data.alpha_method == EXPONENTIAL_DECAY) {
        std::cout << "Using Exponential Decay for optimization" << std::endl;
        x_min = gradient_method(f, grad_f, data, exponential_decay);
    } else if (data.alpha_method == INVERSE_DECAY) {
        std::cout << "Using Inverse Decay for optimization" << std::endl;
        x_min = gradient_method(f, grad_f, data, inverse_decay);
    } else {
        std::cerr << "Error: Invalid method for selecting step size" << std::endl;
        return 1; // Return error code
    }

    // Output the optimal point and the value of the objective function at that point
    std::cout << "Optimal point (x_min): (" << x_min[0] << ", " << x_min[1] << ")" << std::endl;
    std::cout << "Objective function value at x_min (f(x_min)): " << f(x_min) << std::endl;

    return 0; // Return success
} 