#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

const double m = 9.11e-31;
const double B0 = 0.1;
const double L = 0.5;
const double v_perp = 2e5;
const double v_parallel_0 = 1.5e5;

const double mu = 0.5 * m * v_perp * v_perp / B0;

const double E = 0.5 * m * v_perp * v_perp + 0.5 * m * v_parallel_0 * v_parallel_0;

double B(double z, double epsilon) {
    return B0 * (1 + epsilon * (z * z) / (L * L));
}

double v_parallel(double z, double epsilon) {
    double term = 2 * (E - mu * B(z, epsilon)) / m;
    return term > 0 ? sqrt(term) : 0;
}

double integrand(double z, double epsilon) {
    double v_par = v_parallel(z, epsilon);
    return v_par > 0 ? 1 / v_par : 0;
}

double trapezoidalRule(double a, double b, int n, double epsilon) {
    double h = (b - a) / n;
    double sum = 0.5 * (integrand(a, epsilon) + integrand(b, epsilon));

    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        sum += integrand(x, epsilon);
    }

    return sum * h;
}

int main() {
    double a = -0.1875;
    double b = 0.1875;
    int N = 100000;

    std::ofstream outFile("mirrorRatioConvergence.txt");

    for (double epsilon = 1.0; epsilon <= 10.0; epsilon += 1.0) {
        double result_N = trapezoidalRule(a, b, N, epsilon);

        std::cout << "Epsilon = " << std::setprecision(2) << epsilon << ", Tb = " << std::setprecision(10) << result_N << std::endl;
        outFile << "Epsilon = " << std::setprecision(2) << epsilon << ", Tb = " << std::setprecision(10) << result_N << std::endl;
    }

    outFile.close();

    return 0;
}
