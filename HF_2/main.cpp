#include <iostream>
#include<cmath>

//template<typename F, typename T>

template<typename F,typename G, typename T>
//Find thesquarerootof'num'bystarting the iteration from 'x0'
T newton_iteration(F f,G g, T x0)
{
  if(x0 = 0.0)
  {
      std::cout<<"No solution. x0 must be positive.\n";
      return 0.0;
  }  
  else{
  int i = 0;
  double x1 = 0.0;


  while(i <= 10){
    x1 = x0-f(x0)/g(x0) ;
    if (std::abs(x1-x0) <= 1e-12)
    {    
        return x1;
    }
    else
    {
        x0 = x1;
        i++;
    }
  }
  return x1;
  }
}


int main(int, char**) {
   std::cout.precision(16);
   double s0 = 24.738633753705963298;
   std::cout<<"The squareroot of 612 is: "<<s0<< "\n\n";
   double g = newton_iteration([](double x){ return x*x-612.0; },[](double x){ return 2.0*x; }, 10.0);
   std::cout<<"The solution is: "<< g <<"\n";
   std::cout<<"Difference from the test value.:"<< s0-g << "\n";
}
