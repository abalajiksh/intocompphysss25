#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

double trapezoidalRule(double a, double b, int n) {
    double h = (b - a) / n; 
    double sum = 0.5 * (func(a) + func(b)); 

    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        sum += func(x);
    }

    return sum * h;
}

double simpsonsRule(double a, double b, int n) {
    if (n % 2 != 0) {
        n++;
    }

    double h = (b - a) / n;
    double sum = func(a) + func(b);

    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        sum += (i % 2 == 0) ? 2 * func(x) : 4 * func(x);
    }

    return (sum * h) / 3;
}

int main() {

}