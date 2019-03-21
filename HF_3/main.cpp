#include <iostream>
#include<cmath>
#include<numeric>
#include<array>
#include<vector>

template<typename T>
T sq(T x)
{
    return x*x;
}

double average(std::vector<double> const& V) 
{
    double sum = std::accumulate(V.begin(), V.end(), 0.0);
    return sum/static_cast<double>(V.size());
}


std::array<double, 2> linear(std::vector<double> const& V,std::vector<double> const& W)
{   
    double n = average(V);
    double n1 = average(W);

    auto f = [](double a, double b){ return a + b ;};
    auto g = [n,n1](double a, double b){ return (a-n)* (b-n1);};
    double r = std::inner_product(V.begin(), V.end(), W.begin(), 0.0, f, g);
   
    auto f2 = [n](double a, double b){return a + sq((b-n));};
    double c = std::accumulate(V.begin(), V.end(), 0.0, f2);
    double m = r/c;
    double b = n1-m*n;
    
    return std::array<double, 2>{m, b};
}

int main(int, char**) {
    std::vector<double> X={0.0, 1.0, 2.0, 3.0, 4.0};
    std::vector<double> Y={0.0, 1.0, 2.0, 3.0, 4.0};

    //Test vectors:
    std::vector<double> Xt={0.0, 1.0, 2.0, 3.0, 4.0};
    std::vector<double> Yt={0.0, 1.0, 2.0, 3.0, 4.0};

    std::array<double, 2> S0 = {1.0, 0.0};
    std::array<double, 2> s = linear(X,Y);
   

    std::cout<<"Test vectors: \n";
    std::cout<<"X = {";
    for (auto e : Xt)
    {
        std::cout<< e <<" ";
    }
    std::cout<<"}";
    std::cout<<"\n";
    std::cout<<"Y = {";
    for (auto e : Yt)
    {
        std::cout<< e <<" ";
    }
    std::cout<<"}";
    std::cout<<"\n";
    std::cout<<"Test values: "<<"\n";
    std::cout<<"Steepness: " << S0[0] <<"\n";
    std::cout<<"Intersection of the axis: "<< S0[1] <<"\n\n";
    std::cout<<"The solution is: \n";
    std::cout<<"Steepness: " << s[0] <<"\n";
    if(std::abs(S0[0]-s[0])> 1e-10)
    {
        std::cout << "Incorrect result! \n";
    };
    std::cout<<"Intersection of the axis: "<< s[1] <<"\n";
    if(std::abs(S0[1]-s[1])> 1e-10)
    {
        std::cout << "Incorrect result! \n";
    };
}
