#include <iostream>
#include <cmath>
#include <vector>
#include "vector2.h"

int main(int, char**) {

    //Test data:
    Vector2<double> V1={2.0, 5.0 };
    Vector2<double> V2={7.0, 13.0};
    double b0 = 3.0;
    Vector2<double> tsum={9.0, 18.0};
    Vector2<double> tdiff={-5.0, -8.0};
    Vector2<double> tmul1={6.0, 15.0};
    Vector2<double> tmul2={21.0, 39.0};
    Vector2<double> tmur1={6.0, 15.0};
    Vector2<double> tmur2={21.0, 39.0};
    Vector2<double> tdiv1={0.666666666666, 1.666666666666};
    Vector2<double> tdiv2={2.333333333333, 4.333333333333};
    double tdot = 79.0 ;
    double tl1 = 5.385164807134 ;
    double tl2 = 14.764823060233 ;
    double tsql1 = 29.0 ;
    double tsql2 = 218.0 ;
    Vector2<double> tn1={0.371390676354, 0.928476690885};
    Vector2<double> tn2={0.474099823035, 0.880471099922};


    std::cout << "Test data: \n";
    std::cout << "Test vector 1:\n" << V1 <<"\n";
    std::cout << "Test vector 2:\n" << V2 <<"\n";
    std::cout << "Test number: \n";
    std::cout << b0;
    std::cout << "\n\n";
    Vector2<double> v1, v2;
    std::cout << "Enter vector 1:\n";
    std::cin >> v1;
    std::cout << "Enter vector 2:\n";
    std::cin >> v2;
    std::cout << "Enter number:\n";
    double b;
    std::cin >> b;
    Vector2<double> w = v1 + v2 ;
    std::cout << "The sum of the two vectors is:\n" << w <<"\n\n";
    if(std::abs(w.x-tsum.x) > 1e-10 || std::abs(w.y-tsum.y) > 1e-10)
    {
        std::cout << "Incorrect result! \n\n";
    };
    Vector2<double> w0 = v2;
    w0 += v1;
    std::cout << "The sum of the two vectors, by += operator is:\n" << w0 <<"\n\n";
    if(std::abs(w0.x-tsum.x) > 1e-10 || std::abs(w0.y-tsum.y) > 1e-10)
    {
        std::cout << "Incorrect result! \n\n";
    };

    Vector2<double> w1 = v1 - v2 ;
    std::cout << "The difference of the two vectors is:\n" << w1 <<"\n\n";
    if(std::abs(w1.x-tdiff.x) > 1e-10 || std::abs(w1.y-tdiff.y) > 1e-10)
    {
        std::cout << "Incorrect result! \n\n";
    };
    Vector2<double> w2 = v1;
    w2 -= v2;
    std::cout << "The difference of the two vectors, by -= operator is:\n" << w2 <<"\n\n";
    if(std::abs(w2.x-tdiff.x) > 1e-10 || std::abs(w2.y-tdiff.y) > 1e-10)
    {
        std::cout << "Incorrect result! \n\n";
    };
    Vector2<double> w3 = b * v1 ;
    Vector2<double> w4 = b * v2  ;
    std::cout << "The two vectors multiplied by number from left:\n" <<"num*v1: "<< w2 <<", num*v2: "<< w3 << "\n\n";
    if(std::abs(w3.x-tmul1.x) > 1e-10 || std::abs(w3.y-tmul1.y) > 1e-10 || std::abs(w4.x-tmul2.x) > 1e-10 || std::abs(w4.y-tmul2.y) > 1e-10)
    {
        std::cout << "Incorrect result! \n\n";
    };
    Vector2<double> w5 = v1 ;
    w5 *= b;
    Vector2<double> w6 = v2 ;
    w6 *= b;
    std::cout << "The two vectors multiplied by number from left, by *= operator:\n" <<"num*v1: "<< w2 <<", num*v2: "<< w3 << "\n\n";
    if(std::abs(w5.x-tmul1.x) > 1e-10 || std::abs(w5.y-tmul1.y) > 1e-10 || std::abs(w6.x-tmul2.x) > 1e-10 || std::abs(w6.y-tmul2.y) > 1e-10)
    {
        std::cout << "Incorrect result! \n\n";
    };
    Vector2<double> w7 = v1 * b;
    Vector2<double> w8 = v2 * b  ;
    std::cout << "The two vectors multiplied by number from right:\n" <<"v1*num: "<< w4 <<", v2*num: "<< w5 << "\n\n";
    if(std::abs(w7.x-tmur1.x) > 1e-10 || std::abs(w7.y-tmur1.y) > 1e-10 || std::abs(w8.x-tmur2.x) > 1e-10 || std::abs(w8.y-tmur2.y) > 1e-10)
    {
        std::cout << "Incorrect result! \n\n";
    };

    Vector2<double> w9 = v1 / b;
    Vector2<double> w10 = v2 / b;
    std::cout << "The two vectors divided by number:\n" <<"v1/num: "<< w6 <<", v2/num: "<< w7 << "\n\n";
    if(std::abs(w9.x-tdiv1.x) > 1e-10 || std::abs(w9.y-tdiv1.y) > 1e-10 || std::abs(w10.x-tdiv2.x) > 1e-10 || std::abs(w10.y-tdiv2.y) > 1e-10)
    {
        std::cout << "Incorrect result! \n\n";
    };

    Vector2<double> w11 = v1 ;
    Vector2<double> w12 = v2 ;
    w11 /= b;
    w12 /= b;
    std::cout << "The two vectors divided by number, by /= operator:\n" <<"v1/num: "<< w6 <<", v2/num: "<< w7 << "\n\n";
    if(std::abs(w11.x-tdiv1.x) > 1e-10 || std::abs(w11.y-tdiv1.y) > 1e-10 || std::abs(w12.x-tdiv2.x) > 1e-10 || std::abs(w12.y-tdiv2.y) > 1e-10)
    {
        std::cout << "Incorrect result! \n\n";
    };
    double r = dot(v1, v2) ;
    std::cout << "The dot product of the two vectors is:\n" << r << "\n\n";
    if(std::abs(r-tdot) > 1e-10 )
    {
        std::cout << "Incorrect result! \n\n";
    };
    double r1 = length(v1) ;
    double r2 = length(v2) ;
    std::cout << "The length of vectors :\n" <<"length v1: "<< r1 <<", length v2: "<< r2 << "\n\n";
    if(std::abs(r1-tl1) > 1e-10 || std::abs(r2-tl2) > 1e-10 )
    {
        std::cout << "Incorrect result! \n\n";
    };
    double r3 = sqlength(v1) ;
    double r4 = sqlength(v2) ;
    std::cout << "The square length of vectors :\n" <<"length v1: "<< r3 <<", length v2: "<< r4 << "\n\n";
    if(std::abs(r3-tsql1) > 1e-10 || std::abs(r4-tsql2) > 1e-10 )
    {
        std::cout << "Incorrect result! \n\n";
    };
    Vector2<double> w13 = normalize(v1);
    Vector2<double> w14 = normalize(v2);
    std::cout << "The normalized of vectors :\n" <<"norrmalized v1: "<< w8 <<", normalized v2: "<< w9 << "\n\n";
    if(std::abs(w13.x-tn1.x) > 1e-10 || std::abs(w13.y-tn1.y) > 1e-10 || std::abs(w14.x-tn2.x) > 1e-10 || std::abs(w14.y-tn2.y) > 1e-10)
    {
        std::cout << "Incorrect result! \n\n";
    };

    return 0;

}  
