#include <iostream>
#include <math.h>

double f(double x)
{
    return std::cos(x)*std::exp(-x*x);
}

double integrate(int n, double x0, double x1)
{
    double h = (x1-x0)/(n);

    double sum = 0.0;

    for (int j = 1; j <= n-1; j++)
    {
        double xj = x0 + j*h;
         sum += f(xj);
    }

    double I = h/2*(f(x0)+2*sum+f(x1));
    std::cout<<"The integral is: "<< I <<"\n";

}

int main(int, char**) {
    std::cout.precision(16);
    integrate(10000,-1,3);
    
}
