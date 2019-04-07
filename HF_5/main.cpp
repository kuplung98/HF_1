#include "matrix.h"
#include <iostream>


int main()
{
	auto err = [](auto str){ std::cout << "Matrix.h error in: " << str << "\n"; std::exit(-1); };

	//Test default constructor:
	{
		Matrix<double> u;
		if(u.size() != 0)         { err("default contructor test [size]");           }
		if(u.begin() != u.end())  { err("default contructor test [begin == end]");   }
		if(u.cbegin() != u.cend()){ err("default contructor test [cbegin == cend]"); }
	}

	//Test list initialization and indexing:
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		if(a.size() != 4)                            { err("initializer list constructor test [size]");               }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 7.5){ err("initializer list constructor test [indexing with ()]");   }
		if( ++ ++ ++ ++(a.begin()) != a.end() )         { err("initializer list constructor test [begin + 3 == end]");   }
		if( ++ ++ ++ ++(a.cbegin()) != a.cend() )       { err("initializer list constructor test [cbegin + 3 == cend]"); }
	}

	//Test copy constructor:
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> b{a};
		if(b.size() != 4)                            { err("copy constructor test [size]");               }
		if(b[0] != 3.1 || b[1] != 5.2 || b[2] != 9.3, b[3] != 7.5){ err("copy constructor test [elements]");           }
		if( ++ ++ ++ ++(b.begin()) != b.end() )         { err("copy constructor test [begin + 3 == end]");   }
		if( ++ ++ ++ ++(b.cbegin()) != b.cend() )       { err("copy constructor test [cbegin + 3 == cend]"); }
		if(a.size() != 4)                            { err("copy constructor test [src size]");           }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 7.5){ err("copy constructor test [src elements]");       }
	}

	//Test move constructor:
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> b{ std::move(a) };
		if(a.size() != 0)                            { err("move constructor test [src size]");             }
		if(a.begin() != a.end())                     { err("move constructor test [src begin == src end]"); }
		if(b.size() != 4)                            { err("move constructor test [size]");                 }
		if(b[0] != 3.1 || b[1] != 5.2 || b[2] != 9.3, b[3] != 7.5){ err("move constructor test [elements]");             }
		if( ++ ++ ++ ++(b.begin()) != b.end() )         { err("move constructor test [begin + 3 == end]");     }
		if( ++ ++ ++ ++(b.cbegin()) != b.cend() )       { err("move constructor test [cbegin + 3 == cend]");   }
	}
	
	//Test 2D indexible function constructor:
	{
		Matrix<int> a{Idx2{}, [](int i, int j){ return 100*i+10*j+5; }, 2};
		if(a.size() != 4)                                         { err("2D constructor from indexible test [size]");     }
		if(a(0,0) != 5 || a(0,1) != 15 || a(1,0) != 105 || a(1,1) != 115){ err("2D constructor from indexible test [elements]"); }
	}

	//Test 1D indexible function constructor:
	{
		Matrix<int> a{Idx1{}, [](int i){ return 100*i+5; }, 2};
		if(a.size() != 4)                                         { err("1D constructor from indexible test [size]");     }
		if(a[0] != 5 || a[1] != 105 || a[2] != 205 || a[3] != 305){ err("1D constructor from indexible test [elements]"); }
	}

	//Test assignment:
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> b;
		b = a;
		if(b.size() != 4)                            { err("assignment test [size]");         }
		if(b[0] != 3.1 || b[1] != 5.2 || b[2] != 9.3, b[3] != 7.5){ err("assignment test [elements]");     }
		if(a.size() != 4)                            { err("assignment test [src size]");     }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 7.5){ err("assignment test [src elements]"); }
	}

	//Test self assignment:
	{
		Matrix<double> c = {2,{3.1, 5.2, 9.3, 7.5}};
		c = c;
		if(c.size() != 4)                            { err("self assignment test [size]");     }
		if(c[0] != 3.1 || c[1] != 5.2 || c[2] != 9.3 || c[3] != 7.5){ err("self assignment test [elements]"); }
	}

	//Test move assignment:
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> b;
		b = std::move(a);
		if(a.begin() != a.end())                     { err("assignment test [src begin == src end]"); }
		if(a.size() != 0)                            { err("assignment test [src size]");             }
		if(b.size() != 4)                            { err("assignment test [size]");                 }
		if(b(0,0) != 3.1 || b(0,1) != 5.2 || b(1,0) != 9.3, b(1,1) != 7.5){ err("assignment test [elements]");             }
	}

	//Test operator- (l-value, l-value)
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> b = {2,{2.1, 3.2, 7.3, 1.5}};
		Matrix<double> ref = {2,{1.0, 2.0, 2.0, 6.0}};
		Matrix<double> res = a - b;
		if(a.size() != 4)                              { err("operator- test (l-value, l-value) [src size]");     }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 7.5) { err("operator- test (l-value, l-value) [src elements]"); }
		if(b.size() != 4)                              { err("operator- test (l-value, l-value) [src size]");     }
		if(b[0] != 2.1 || b[1] != 3.2 || b[2] != 7.3 || b[3] != 1.5){ err("operator- test (l-value, l-value) [src elements]"); }
		if(res.size() != 4)                            { err("operator- test (l-value, l-value) [size]");         }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
           std::abs(ref[3]-res[3]) > 1e-15   ){ err("operator- test (l-value, l-value) [elements]"); }
	}

	//Test operator- (r-value, l-value)
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> b = {2,{2.1, 3.2, 7.3, 1.5}};
		Matrix<double> ref = {2,{1.0, 2.0, 2.0, 6.0}};
		Matrix<double> res = std::move(a) - b;
		if(a.size() != 0)                              { err("operator- test (r-value, l-value) [src size]");     }
		if(b.size() != 4)                              { err("operator- test (r-value, l-value) [src size]");     }
		if(res.size() != 4)                            { err("operator- test (r-value, l-value) [size]");         }
		if(b[0] != 2.1 || b[1] != 3.2 || b[2] != 7.3 || b[3] != 1.5){ err("operator- test (r-value, l-value) [src elements]"); }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
           std::abs(ref[3]-res[3]) > 1e-15   ){ err("operator- test (r-value, l-value) [value]");        }
	}

	//Test operator- (l-value, r-value)
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> b = {2,{2.1, 3.2, 7.3, 1.5}};
		Matrix<double> ref = {2,{1.0, 2.0, 2.0, 6.0}};
		Matrix<double> res = a - std::move(b);
		if(a.size() != 4)                              { err("operator- test (l-value, r-value) [src size]");     }
		if(b.size() != 0)                              { err("operator- test (l-value, r-value) [src size]");     }
		if(res.size() != 4)                            { err("operator- test (l-value, r-value) [size]");         }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 7.5){ err("operator- test (l-value, r-value) [src elements]"); }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
           std::abs(ref[3]-res[3]) > 1e-15   ){ err("operator- test (r-value, l-value) [value]");        }
	}

	//Test operator- (r-value, r-value)
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> b = {2,{2.1, 3.2, 7.3, 1.5}};
		Matrix<double> ref = {2,{1.0, 2.0, 2.0, 6.0}};
		Matrix<double> res = std::move(a) - std::move(b);
		if(a.size() != 0)            { err("operator- test (r-value, r-value) [src size]"); }
		if(b.size() != 4)            { err("operator- test (r-value, r-value) [src size]"); }
		if(res.size() != 4)          { err("operator- test (r-value, r-value) [size]");     }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
           std::abs(ref[3]-res[3]) > 1e-15   ){ err("operator- test (r-value, l-value) [value]");        }
	}

	//Test operator+ (l-value, l-value)
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> b = {2,{2.1, 3.2, 7.3, 1.5}};
		Matrix<double> ref = {2,{5.2, 8.4, 16.6, 9.0}};
		Matrix<double> res = a + b;
		if(a.size() != 4)                              { err("operator+ test (l-value, l-value) [src size]");     }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 7.5) { err("operator- test (l-value, l-value) [src elements]"); }
		if(b.size() != 4)                              { err("operator+ test (l-value, l-value) [src size]");     }
		if(b[0] != 2.1 || b[1] != 3.2 || b[2] != 7.3 || b[3] != 1.5){ err("operator- test (l-value, l-value) [src elements]"); }
		if(res.size() != 4)                            { err("operator+ test (l-value, l-value) [size]");         }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
           std::abs(ref[3]-res[3]) > 1e-15   ){ err("operator+ test (l-value, l-value) [elements]"); }
	}

	//Test operator+ (r-value, l-value)
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> b = {2,{2.1, 3.2, 7.3, 1.5}};
		Matrix<double> ref = {2,{5.2, 8.4, 16.6, 9.0}};
		Matrix<double> res = std::move(a) + b;
		if(a.size() != 0)                              { err("operator+ test (r-value, l-value) [src size]");     }
		if(b.size() != 4)                              { err("operator+ test (r-value, l-value) [src size]");     }
		if(b[0] != 2.1 || b[1] != 3.2 || b[2] != 7.3 || b[3] != 1.5){ err("operator+ test (r-value, l-value) [src elements]"); }
		if(res.size() != 4)                            { err("operator+ test (r-value, r-value) [size]");         }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
           std::abs(ref[3]-res[3]) > 1e-15   ){ err("operator+ test (l-value, l-value) [elements]"); }
	}

	//Test operator+ (l-value, r-value)
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> b = {2,{2.1, 3.2, 7.3, 1.5}};
		Matrix<double> ref = {2,{5.2, 8.4, 16.6, 9.0}};
		Matrix<double> res = a + std::move(b);
		if(a.size() != 4)                              { err("operator+ test (l-value, r-value) [src size]");     }
        if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 7.5){ err("operator+ test (l-value, r-value) [src elements]"); }
		if(b.size() != 0)                              { err("operator+ test (l-value, r-value) [src size]");     }
		if(res.size() != 4)                            { err("operator+ test (l-value, r-value) [size]");         }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
           std::abs(ref[3]-res[3]) > 1e-15   ){ err("operator+ test (l-value, l-value) [elements]"); }
	}

	//Test operator+ (r-value, r-value)
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> b = {2,{2.1, 3.2, 7.3, 1.5}};
		Matrix<double> ref = {2,{5.2, 8.4, 16.6, 9.0}};
		Matrix<double> res = std::move(a) + std::move(b);
		if(a.size() != 0)                              { err("operator+ test (r-value, r-value) [src size]");     }
		if(b.size() != 4)                              { err("operator+ test (r-value, r-value) [src size]");     }
		if(res.size() != 4)                            { err("operator+ test (r-value, r-value) [size]");         }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
           std::abs(ref[3]-res[3]) > 1e-15   ){ err("operator+ test (l-value, l-value) [elements]"); }
	}

	//Test +=:
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> b = {2,{2.1, 3.2, 7.3, 1.5}};
		Matrix<double> ref = {2,{5.2, 8.4, 16.6, 9.0}};
	    a += b;
		if(a.size() != 4)                              { err("+= test [size]");         }
		if(b.size() != 4)                              { err("+= test [src size]");     }
		if(b[0] != 2.1 || b[1] != 3.2 || b[2] != 7.3 || b[3] != 1.5){ err("+= test [src elements]"); }
		if(std::abs(ref[0]-a[0]) > 1e-15 ||
		   std::abs(ref[1]-a[1]) > 1e-15 || 
		   std::abs(ref[2]-a[2]) > 1e-15 ||
           std::abs(ref[3]-a[3]) > 1e-15   )                 { err("+= test [value]");        }
		
	}

	//Test -=:
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> b = {2,{2.1, 3.2, 7.3, 1.5}};
		Matrix<double> ref = {2,{1.0, 2.0, 2.0, 6.0}};
		a -= b;
		if(a.size() != 4)                            { err("-= test [size]");         }
		if(b.size() != 4)                            { err("-= test [src size]");     }
		if(b[0] != 2.1 || b[1] != 3.2 || b[2] != 7.3 || b[3] != 1.5){ err("-= test [src elements]"); }
		if(std::abs(ref[0]-a[0]) > 1e-15 ||
		   std::abs(ref[1]-a[1]) > 1e-15 || 
		   std::abs(ref[2]-a[2]) > 1e-15 ||
           std::abs(ref[3]-a[3]) > 1e-15   )                    { err("-= test [value]");        }
	}

	//Test *=:
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> ref = {2,{6.2, 10.4, 18.6, 15.0}};
		a *= 2.0;
		if(a.size() != 4)          { err("*= test [size]");  }
		if(std::abs(ref[0]-a[0]) > 1e-15 ||
		   std::abs(ref[1]-a[1]) > 1e-15 || 
		   std::abs(ref[2]-a[2]) > 1e-15 ||
           std::abs(ref[3]-a[3]) > 1e-15   ) { err("*= test [value]"); }
	}

	//Test operator* (l-value, scalar)
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> ref = {2,{6.2, 10.4, 18.6, 15.0}};
		Matrix<double> res = a * 2.0;
		if(a.size()   != 4)                           { err("operator* test (l-value, scalar) [src size]");     }
		if(res.size() != 4)                           { err("operator* test (l-value, scalar) [size]");         }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 7.5){ err("operator* test (l-value, scalar) [src elements]"); }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
           std::abs(ref[3]-res[3]) > 1e-15   )            { err("operator* test (l-value, scalar) [value]");        }
	}

	//Test operator* (r-value, scalar)
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> ref = {2,{6.2, 10.4, 18.6, 15.0}};
		Matrix<double> res = std::move(a) * 2.0;
		if(a.size()   != 0)          { err("operator* test (r-value, scalar) [src size]");     }
		if(res.size() != 4)          { err("operator* test (r-value, scalar) [size]");         }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
           std::abs(ref[3]-res[3]) > 1e-15   ) { err("operator* test (r-value, scalar) [value]");        }
	}

	//Test operator* (scalar, l-value)
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> ref = {2,{6.2, 10.4, 18.6, 15.0}};
		Matrix<double> res = 2.0 * a ;
		if(a.size()   != 4)                           { err("operator* test (scalar, l-value) [src size]");     }
		if(res.size() != 4)                           { err("operator* test (scalar, l-value) [size]");         }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 7.5){ err("operator* test (scalar, l-value) [src elements]"); }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
           std::abs(ref[3]-res[3]) > 1e-15   ) { err("operator* test (scalar, l-value) [value]");        }
	}

	//Test operator* (scalar, r-value)
	{
        Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> ref = {2,{6.2, 10.4, 18.6, 15.0}};
		Matrix<double> res = 2.0 * std::move(a); 
		if(a.size()   != 0)          { err("operator* test (scalar, r-value) [src size]");     }
		if(res.size() != 4)          { err("operator* test (scalar, r-value) [size]");         }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
           std::abs(ref[3]-res[3]) > 1e-15   ){ err("operator* test (scalar, r-value) [value]");        }
	}

	//Test /=:
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> ref = {2,{1.55, 2.6, 4.65, 3.75}};
		a /= 2.0;
		if(a.size() != 4)          { err("/= test [size]");  }
		if(std::abs(ref[0]-a[0]) > 1e-15 ||
		   std::abs(ref[1]-a[1]) > 1e-15 || 
		   std::abs(ref[2]-a[2]) > 1e-15 ||
           std::abs(ref[3]-a[3]) > 1e-15   ){ err("/= test [value]"); }
	}

	//Test operator/ (l-value, scalar)
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> ref = {2,{1.55, 2.6, 4.65, 3.75}};
		Matrix<double> res = a / 2.0;
		if(a.size()   != 4)                             { err("operator/ test (l-value, scalar) [src size]");     }
		if(res.size() != 4)                             { err("operator/ test (l-value, scalar) [size]");         }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 7.5){ err("operator/ test (l-value, scalar) [src elements]"); }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
           std::abs(ref[3]-res[3]) > 1e-15   )  { err("operator/ test (l-value, scalar) [value]");        }
	}

	//Test operator/ (r-value, scalar)
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> ref = {2,{1.55, 2.6, 4.65, 3.75}};
		Matrix<double> res = std::move(a) / 2.0;
		if(a.size()   != 0)          { err("operator/ test (r-value, scalar) [src size]"); }
		if(res.size() != 4)          { err("operator/ test (r-value, scalar) [size]");     }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15 ||
           std::abs(ref[3]-res[3]) > 1e-15   ){ err("operator/ test (r-value, scalar) [value]");    }
	}

	//Matrix multiplication:
	//(l-value, l-value)
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> b = {2,{2.1, 3.2, 7.3, 1.5}};
		Matrix<double> ref = {2,{44.47, 17.72, 74.28, 41.01}};
		Matrix<double> res = a*b;
		if(a.size() != 4)                             { err("mu test (l-value, l-value) [src size]");     }
		if(b.size() != 4)                             { err("mu test (l-value, l-value) [src size]");     }
		if(res.size() != 4)          				  { err("mu test (l-value, l-value) [size]");     }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 7.5){ err("mu* test (l-value, l-value) [src elements]"); }
		if(b[0] != 3.1 || b[1] != 5.2 || b[2] != 9.3, b[3] != 1.5){ err("mu test (l-value, l-value) [src elements]"); }
		if(std::abs(ref[0]-res[0]) > 1e-14 ||
		   std::abs(ref[1]-res[1]) > 1e-14 || 
		   std::abs(ref[2]-res[2]) > 1e-14 ||
           std::abs(ref[3]-res[3]) > 1e-14   ){ err("mu test (l-value, l-value) [value]");    }
	}

	//(r-value, l-value)
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> b = {2,{2.1, 3.2, 7.3, 1.5}};
		Matrix<double> ref = {2,{44.47, 17.72, 74.28, 41.01}};
		Matrix<double> res = std::move(a) * b;
		if(a.size() != 0)                             { err("mu test (r-value, l-value) [src size]");     }
		if(b.size() != 4)                             { err("mu test (r-value, l-value) [src size]");     }
		if(res.size() != 4)          				  { err("mu test (l-value, r-value) [size]");     }
		if(b[0] != 2.1 || b[1] != 3.2 || b[2] != 7.3 || b[3] != 1.5){ err("mu test (r-value, l-value) [src elements]"); }
		if(std::abs(ref[0]-res[0]) > 1e-14 ||
		   std::abs(ref[1]-res[1]) > 1e-14 || 
		   std::abs(ref[2]-res[2]) > 1e-14 ||
           std::abs(ref[3]-res[3]) > 1e-14   ){ err("mu test (r-value, l-value) [value]");    }
	}

	//(l-value, r-value)
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> b = {2,{2.1, 3.2, 7.3, 1.5}};
		Matrix<double> ref = {2,{44.47, 17.72, 74.28, 41.01}};
		Matrix<double> res = a*std::move(b);
		if(a.size() != 4)                             { err("mu test (l-value, r-value) [src size]");     }
		if(b.size() != 0)                             { err("mu test (l-value, r-value) [src size]");     }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 7.5){ err("mu test (l-value, r-value) [src elements]"); }
		if(std::abs(ref[0]-res[0]) > 1e-14 ||
		   std::abs(ref[1]-res[1]) > 1e-14 || 
		   std::abs(ref[2]-res[2]) > 1e-14 ||
           std::abs(ref[3]-res[3]) > 1e-14   ){ err("mu test (l-value, r-value) [value]");    }
	}

	//(r-value, r-value)
	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		Matrix<double> b = {2,{2.1, 3.2, 7.3, 1.5}};
		Matrix<double> ref = {2,{44.47, 17.72, 74.28, 41.01}};
		Matrix<double> res = std::move(a) * std::move(b);
		if(a.size() != 0)                             { err("mu test (r-value, r-value) [src size]");     }
		if(b.size() != 4)                             { err("mu test (r-value, r-value) [src size]");     }
		if(std::abs(ref[0]-res[0]) > 1e-14 ||
		   std::abs(ref[1]-res[1]) > 1e-14 || 
		   std::abs(ref[2]-res[2]) > 1e-14 ||
           std::abs(ref[3]-res[3]) > 1e-14   ){ err("mu test (r-value, r-value) [value]");    }
	}

	// Test iostream:

	{
		Matrix<double> a = {2,{3.1, 5.2, 9.3, 7.5}};
		std::string str("2;3.1,5.2,9.3,7.5");
		std::stringstream oo1;
		oo1 << a;
		if(a.size() != 4)                             { err("istream test [src size]");     }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3 || a[3] != 7.5){ err("istream test [src elements]");    }
		std::string o1 = oo1.str();
		bool b = o1 == str;
		if(b != true){err("istream test [value]"); }
	}

	{
		Matrix<double> b = {2,{2.1, 3.2, 7.3, 1.5}};
		std::string str("2;2.1,3.2,7.3,1.5");
		std::stringstream oo1(str);
		Matrix<double> p;
		oo1 >> p;
		if(b.size() != 4)							  { err("ostream test [src size]");     }
		if(b[0] != 2.1 || b[1] != 3.2 || b[2] != 7.3 || b[3] != 1.5){ err("ostream test [src elements]");    }
		if(p.size() != 4)							  { err("ostream test [size]");     }
		if(std::abs(b[0]-p[0]) > 1e-15 ||
		   std::abs(b[1]-p[1]) > 1e-15 || 
		   std::abs(b[2]-p[2]) > 1e-15 ||
           std::abs(b[3]-p[3]) > 1e-15   ){ err("istream test [value]");    }
	}



    std::cout << "All tests are successful!\n";
	return 0;
}
