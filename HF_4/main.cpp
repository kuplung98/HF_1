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

    //The sum of the two vectors :
    Vector2<double> w = V1 + V2 ;
    if(std::abs(w.x-tsum.x) > 1e-10 || std::abs(w.y-tsum.y) > 1e-10)
    {
        std::cout << "Incorrect result of sum! \n\n";
    };

    //The sum of the two vectors, by += operator:
    Vector2<double> w0 = V2;
    w0 += V1;
    if(std::abs(w0.x-tsum.x) > 1e-10 || std::abs(w0.y-tsum.y) > 1e-10)
    {
        std::cout << "Incorrect result of sum by += operator! \n\n";
    };

    //The difference of the two vectors:
    Vector2<double> w1 = V1 - V2 ;
    if(std::abs(w1.x-tdiff.x) > 1e-10 || std::abs(w1.y-tdiff.y) > 1e-10)
    {
        std::cout << "Incorrect result of difference! \n\n";
    };

    //The difference of the two vectors, by -= operator:
    Vector2<double> w2 = V1;
    w2 -= V2;
    if(std::abs(w2.x-tdiff.x) > 1e-10 || std::abs(w2.y-tdiff.y) > 1e-10)
    {
        std::cout << "Incorrect result of difference by -= operator! \n\n";
    };

    //The two vectors multiplied by number from left:
    Vector2<double> w3 = b0 * V1 ;
    Vector2<double> w4 = b0 * V2  ;
    if(std::abs(w3.x-tmul1.x) > 1e-10 || std::abs(w3.y-tmul1.y) > 1e-10 || std::abs(w4.x-tmul2.x) > 1e-10 || std::abs(w4.y-tmul2.y) > 1e-10)
    {
        std::cout << "Incorrect result of multiplied by number from left! \n\n";
    };

    //The two vectors multiplied by number from left, by *= operator:
    Vector2<double> w5 = V1 ;
    w5 *= b0;
    Vector2<double> w6 = V2 ;
    w6 *= b0;
    if(std::abs(w5.x-tmul1.x) > 1e-10 || std::abs(w5.y-tmul1.y) > 1e-10 || std::abs(w6.x-tmul2.x) > 1e-10 || std::abs(w6.y-tmul2.y) > 1e-10)
    {
        std::cout << "Incorrect result of multiplied by number,  by *= operator! \n\n";
    };

    //The two vectors multiplied by number from right:
    Vector2<double> w7 = V1 * b0;
    Vector2<double> w8 = V2 * b0;
    if(std::abs(w7.x-tmur1.x) > 1e-10 || std::abs(w7.y-tmur1.y) > 1e-10 || std::abs(w8.x-tmur2.x) > 1e-10 || std::abs(w8.y-tmur2.y) > 1e-10)
    {
        std::cout << "Incorrect result of multiplied by number from right! \n\n";
    };

    //The two vectors divided by number:
    Vector2<double> w9 = V1 / b0;
    Vector2<double> w10 = V2 / b0;
    if(std::abs(w9.x-tdiv1.x) > 1e-10 || std::abs(w9.y-tdiv1.y) > 1e-10 || std::abs(w10.x-tdiv2.x) > 1e-10 || std::abs(w10.y-tdiv2.y) > 1e-10)
    {
        std::cout << "Incorrect result of divided by number! \n\n";
    };

    //The two vectors divided by number, by /= operator:
    Vector2<double> w11 = V1 ;
    Vector2<double> w12 = V2 ;
    w11 /= b0;
    w12 /= b0;
    if(std::abs(w11.x-tdiv1.x) > 1e-10 || std::abs(w11.y-tdiv1.y) > 1e-10 || std::abs(w12.x-tdiv2.x) > 1e-10 || std::abs(w12.y-tdiv2.y) > 1e-10)
    {
        std::cout << "Incorrect result of divided by number, by /= operator! \n\n";
    };

    // The two vectors dot product:
    double r = dot(V1, V2) ;
    if(std::abs(r-tdot) > 1e-10 )
    {
        std::cout << "Incorrect result of dot! \n\n";
    };

    // The length of vectors:
    double r1 = length(V1) ;
    double r2 = length(V2) ;
    if(std::abs(r1-tl1) > 1e-10 || std::abs(r2-tl2) > 1e-10 )
    {
        std::cout << "Incorrect result of length! \n\n";
    };

    // The sqlength of vectors:
    double r3 = sqlength(V1) ;
    double r4 = sqlength(V2) ;
    if(std::abs(r3-tsql1) > 1e-10 || std::abs(r4-tsql2) > 1e-10 )
    {
        std::cout << "Incorrect result of square length! \n\n";
    };

    // The normalized value of vectors:
    Vector2<double> w13 = normalize(V1);
    Vector2<double> w14 = normalize(V2);
    if(std::abs(w13.x-tn1.x) > 1e-10 || std::abs(w13.y-tn1.y) > 1e-10 || std::abs(w14.x-tn2.x) > 1e-10 || std::abs(w14.y-tn2.y) > 1e-10)
    {
        std::cout << "Incorrect result of normalized! \n\n";
    };

    // The iostream test: 
    Vector2<double> V3={2.3, 5.1 };
    Vector2<double> V4={7.5, 13.7 };
    {
		std::string str("2.3,5.1");
		std::stringstream oo1;
		oo1 << V3;
		std::string o1 = oo1.str();
		bool b = o1 == str;
		if(b != true){std::cout << "Incorrect ostream! \n\n"; };
	}

	{
		std::string str("7.5,13.7");
		std::stringstream oo1(str);
		Vector2<double> p;
		oo1 >> p;
		if(std::abs(V4.x-p.x) > 1e-10 || std::abs(V4.y-p.y) > 1e-10 ){ std::cout << "Incorrect istream! \n\n";    }
	}


    return 0;

}  
