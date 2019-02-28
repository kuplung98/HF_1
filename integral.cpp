#include <iostream>
#include <math.h>

double f(double x)
{
    return std::cos(x)*std::exp(-x*x);
}

double integrate(int n, double x0, double x1)
{
    if(x0 > x1)
    {
        double a = x0;
        double b = x1;
        x1 = a;
        x0 = b;
    }

    if(n <= 0)
    {
        std::cout<<"No solution. n must be a positive integer.\n";
    }
    else
    {
     double h = (x1-x0)/(n);
     double sum = 0.0;
     for (int j = 1; j <= n-1; j++)
        {
        double xj = x0 + j*h;
         sum += f(xj);
        }

     double I = h/2*(f(x0)+2*sum+f(x1));
     //std::cout<<"The integral is: "<< I <<"\n";

     return I;
    }
}

int main(int, char**) {
   std::cout.precision(16);
   std::cout<<"The value of the definite integral between -1 and 3 is: 1.34638795680345037 \n\n";
   double I0 = 1.34638795680345037;
   std::cout<<"The integral and it's difference from the test value.:\n";
    
   for(int n = 100; n <= 2000; n = n+100)
   {
    double I = integrate(n,-1,3);
    std::cout<<"'n' = "<< n << " , The integral is: "<< I <<";  difference: "<< I0-I <<"\n";
   }

}


    

