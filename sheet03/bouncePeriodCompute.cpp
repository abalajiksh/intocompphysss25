#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

double func(double x) {
    return x*x - x*x*x; 
}

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
    double v1 = 100.00, v2 = 10.00, a = 0.5, b = 3.0;
    for(int i = 0; (v2-v1) >= 0.0001; ++i){ //check the crap you fucked up here
        v1 = v2;
        v2 = trapezoidalRule(a,b, 10+i);
        std::cout << "Iteration " << i << ", Trap: " << std::setprecision(10) << v2 << ", und Simpson: " << simpsonsRule(a,b,10+i) << std::endl;
    }
     

    return 0;
}