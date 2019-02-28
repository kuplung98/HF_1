#include <iostream>
#include<math.h>

double sq(double x)
{
    return x*x;
}

//Find thesquarerootof'num'bystarting the iteration from 'x0'
double sqrt_newton(double num, double x0)
{
  int i = 0;
  double x1 = 0.0;

  while(i <= 100){
    x1 = x0-(sq(x0)-num)/(2.0*x0);
    if (abs(x1-x0) <= 1e-12)
    {    
        return x1;
    }
    else
    {
        x0 = x1;
        //std::cout << "There is the solution: " << x1 << "\n";
        i++;
    }
  }

}

int main(int, char**) {
   std::cout.precision(16);
   double g = sqrt_newton(612, 10);
   std::cout<<"The solution is: "<< g <<"\n";
}
