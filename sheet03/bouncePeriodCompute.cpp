#include <iostream>
#include <fstream>
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
    return sqrt(2 * (E - mu * B(z)) / m);
}

double integrand(double z) {
    double v_par = v_parallel(z);
    return 1 / (v_par + 1e-12);
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

double simpsonsRule(double a, double b, int n) {
    if (n % 2 != 0) {
        n++;
    }

    double h = (b - a) / n;
    double sum = integrand(a) + integrand(b);

    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        sum += (i % 2 == 0) ? 2 * integrand(x) : 4 * integrand(x);
    }

    return (sum * h) / 3;
}

int main() {
    double a = -0.1875;
    double b = 0.1875;
    double EPS = 1e-3;
    double v1_trap, v2_trap, v1_simp, v2_simp;
    int n = 10;

    std::ofstream outFile("bouncePeriodCompute.txt");

    v1_trap = trapezoidalRule(a, b, n);
    v1_simp = simpsonsRule(a, b, n);

    std::cout << "Iteration " << 0 << ", Trap: " << std::setprecision(10) << v1_trap << ", Simpson: " << v1_simp << std::endl;
    outFile << "Iteration " << 0 << ", Trap: " << std::setprecision(10) << v1_trap << ", Simpson: " << v1_simp << std::endl;

    int i = 1;
    do {
        n *= 2;
        v2_trap = trapezoidalRule(a, b, n);
        v2_simp = simpsonsRule(a, b, n);

        std::cout << "Iteration " << i << ", Trap: " << std::setprecision(10) << v2_trap << ", Simpson: " << v2_simp << std::endl;
        outFile << "Iteration " << i << ", Trap: " << std::setprecision(10) << v2_trap << ", Simpson: " << v2_simp << std::endl;

        i++;
    } while (fabs(v2_trap - v1_trap) >= EPS || fabs(v2_simp - v1_simp) >= EPS);

    outFile.close();

    return 0;
}
