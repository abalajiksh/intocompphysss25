#include <iostream>
#include <cmath>
#include <iomanip>

const double m = 9.11e-31;
const double B0 = 0.1;
const double epsilon = 4;
const double L = 0.5;
const double v_perp = 2e5;
const double v_parallel_0 = 1.5e5;

const double mu = 0.5 * m * v_perp * v_perp / B0;

const double E = 0.5 * m * v_perp * v_perp + 0.5 * m * v_parallel_0 * v_parallel_0;

double B(double z) {
    return B0 * (1 + epsilon * (z * z) / (L * L));
}

double v_parallel(double z) {
    double term = 2 * (E - mu * B(z)) / m;
    return term > 0 ? sqrt(term) : 0;
}

double integrand(double z) {
    double v_par = v_parallel(z);
    return v_par > 0 ? 1 / v_par : 0;
}

double trapezoidalRule(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (integrand(a) + integrand(b));

    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        sum += integrand(x);
    }

    return sum * h;
}

int main() {
    double a = -0.1875;
    double b = 0.1875;
    int N = 100000;

    double result_N = trapezoidalRule(a, b, N);
    double result_2N = trapezoidalRule(a, b, 2 * N);

    double relative_error = fabs((result_2N - result_N) / result_2N);

    std::cout << "Result with N = " << N << ": " << std::setprecision(10) << result_N << std::endl;
    std::cout << "Result with 2N = " << 2 * N << ": " << std::setprecision(10) << result_2N << std::endl;
    std::cout << "Relative Error: " << std::setprecision(10) << relative_error << std::endl;

    if (relative_error < 1e-6) {
        std::cout << "Convergence achieved." << std::endl;
    } else {
        std::cout << "Convergence not achieved. Increase N further." << std::endl;
    }

    return 0;
}
