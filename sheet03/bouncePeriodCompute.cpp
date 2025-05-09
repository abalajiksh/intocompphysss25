#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

double func(int f, double x) {
    double v;

    if (f == 1) {
        v = //func1;
    } else {
        v = //func2;
    }

    return v; 
}

double trapezoidalRule(double a, double b, int n, int f) {
    double h = (b - a) / n; 
    double sum = 0.5 * (func(f, a) + func(f, b)); 

    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        sum += func(f, x);
    }

    return sum * h;
}

double simpsonsRule(double a, double b, int n, int f) {
    if (n % 2 != 0) {
        n++;
    }

    double h = (b - a) / n;
    double sum = func(f, a) + func(f, b);

    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        sum += (i % 2 == 0) ? 2 * func(f, x) : 4 * func(f, x);
    }

    return (sum * h) / 3;
}

int main() {

}