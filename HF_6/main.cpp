#include <iostream>
#include <random>
#include <vector>
#include "matrix.h"
#include <chrono>
#include <fstream>

int main(int, char**) {
   std::random_device rd{};
   std::mt19937 gen(rd());
   std::normal_distribution<double> distr(100,20);
   std::ofstream myfile;
   myfile.open("time.txt",std::fstream::app);
   for(int N=100;N<=1500;N+=100)
   {
      double min1=1e10;
      double min2=1e10;
      for(int i=0; i<10; i++)
      {
            Matrix<double> m0(Idx1{},[&](auto i){ return distr(gen); },N);
            Matrix<double> m1(Idx1{},[&](auto i){ return distr(gen); },N);
            Matrix<double> m2(Idx1{},[&](auto i){ return distr(gen); },N);
            Matrix<double> m3(Idx1{},[&](auto i){ return distr(gen); },N);

            auto t1 = std::chrono::high_resolution_clock::now();
            m0*m1;
            auto t2 = std::chrono::high_resolution_clock::now();
            std::move(m2)*std::move(m3);
            auto t3 = std::chrono::high_resolution_clock::now();

            min1=std::min(min1,(static_cast<std::chrono::duration<double,std::milli>>(t2-t1)).count());
            min2=std::min(min2,(static_cast<std::chrono::duration<double,std::milli>>(t3-t2)).count());
      }
      myfile<<N<<" "<<min1<<" "<<min2<<"\n";
      std::cout<<N<<"\n";
   }
   myfile.close();
   return 0;
}
