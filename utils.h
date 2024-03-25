#include <iostream> // Standard input/output stream
#include <vector> // Vector containers
#include <cmath> // Math functions
#include <fstream> // File stream

#include "json.hpp" // JSON library

#include "utils.h" // Utility functions and data structures
#include "gradient_method.h" // Gradient descent optimization functions

using json = nlohmann::json; // Namespace alias for JSON library

int main() {
    // Define the objective function
    Function f = [](const std::vector<double>& x) {
        return x[0] * x[1] + 4 * pow(x[0], 4) + pow(x[1], 2) + 3 * x[0];
    };

    // Define the gradient of the objective function
    Gradient grad_f = [](const std::vector<double>& x) {
        return std::vector<double>{x[1] + 16*pow(x[0], 3) + 3, x[0] + 2*x[1]};
    };

    // Read parameters from JSON file
    std::ifstream file("data.json"); // Open JSON file
    json j = json::parse(file); // Parse JSON content

    // Extract values from JSON and assign them to the Data struct
    Data data; // Data structure to store parameters
    data.epsilon_residual = j.value("epsilon_residual", 1e-8); // Tolerance for residual
    data.epsilon_step = j.value("epsilon_step", 1e-8); // Tolerance for step
    data.alpha_0 = j.value("alpha_0", 0.1); // Initial step size
    data.mu = j.value("mu", 0.3); // Decay parameter
    data.max_iterations = j.value("max_iterations", 100); // Maximum number of iterations
    data.sigma = j.value("sigma", 0.2); // Parameter for Armijo rule
    std::vector<double> initial_guess = j["x0"]; // Initial guess
    data.x0 = initial_guess;
    data.alpha_method = j.value("alpha_method", 0); // Alpha selection method

    std::vector<double> x_min(2); // Variable to store the minimum point

    // Select optimization method based on alpha selection method
    if (data.alpha_method == ARMIJO_RULE) {
        std::cout << "Selected method: Armijo Rule" << std::endl;
        x_min = gradient_method(f, grad_f, data, armijo_rule);
    } else if (data.alpha_method == EXPONENTIAL_DECAY) {
        std::cout << "Selected method: Exponential Decay" << std::endl;
        x_min = gradient_method(f, grad_f, data, exponential_decay);
    } else if (data.alpha_method == INVERSE_DECAY) {
        std::cout << "Selected method: Inverse Decay" << std::endl;
        x_min = gradient_method(f, grad_f, data, inverse_decay);
    } else {
        std::cerr << "Error: alpha method not valid" << std::endl;
        return 1; // Return error code
    }

    // Output the optimal point and the value of the objective function at that point
    std::cout << "x_min: (" << x_min[0] << ", " << x_min[1] << ")" << std::endl;
    std::cout << "f(x_min): " << f(x_min) << std::endl;

    return 0; // Return success
}
