#ifndef GRADIENT_METHOD_H
#define GRADIENT_METHOD_H

#include "utils.h"

// Function to perform gradient descent optimization
std::vector<double> gradient_descent(const Function& objective_function, const Gradient& gradient_function, const Data& optimization_data, const AlphaStrategy& alpha_strategy) {
    bool converged = false; // Variable to track convergence
    std::vector<double> current_point = optimization_data.initial_guess; // Initialize current point with the initial guess
    for (int iteration = 0; iteration < optimization_data.max_iterations && !converged; ++iteration) { // Iterate until convergence or maximum iterations reached
        std::vector<double> gradient = gradient_function(current_point); // Compute gradient at the current point
        double step_size = alpha_strategy(objective_function, current_point, gradient, optimization_data, iteration); // Compute step size
        std::vector<double> new_point = current_point - gradient * step_size; // Update current point using gradient and step size
        // Check convergence criteria
        converged = std::abs(objective_function(new_point) - objective_function(current_point)) < optimization_data.epsilon_residual
                    || vector_norm(new_point - current_point) < optimization_data.epsilon_step;
        current_point = new_point; // Update current point for the next iteration
        if (converged)
            std::cout << "Converged in " << iteration << " iterations" << std::endl; // Print convergence message
    }
    return current_point; // Return the optimal point
}

// Enumeration for different alpha selection methods
enum AlphaMethod {
    ARMIJO_RULE = 0,
    EXPONENTIAL_DECAY = 1,
    INVERSE_DECAY = 2
};

// Armijo rule for selecting step size
double armijo_rule(const Function & objective_function, const std::vector<double>& current_point, const std::vector<double>& gradient, const Data& optimization_data, int iteration) {
    double sigma = optimization_data.sigma;
    double alpha = optimization_data.alpha_0;

    while (objective_function(current_point) - objective_function(current_point - gradient * alpha) < sigma * alpha * vector_norm(gradient) * vector_norm(gradient)) {
        alpha /= 2; // Reduce step size
    }
    return alpha; // Return selected step size
}

// Exponential decay for selecting step size
double exponential_decay(const Function & objective_function, const std::vector<double>& current_point, const std::vector<double>& gradient, const Data& optimization_data, int iteration) {
    return optimization_data.alpha_0 * exp(-optimization_data.mu * iteration); // Compute step size using exponential decay
}

// Inverse decay for selecting step size
double inverse_decay(const Function & objective_function, const std::vector<double>& current_point, const std::vector<double>& gradient, const Data& optimization_data, int iteration) {
    return optimization_data.alpha_0 / (1 + optimization_data.mu * iteration); // Compute step size using inverse decay
}

#endif // GRADIENT_METHOD_H
