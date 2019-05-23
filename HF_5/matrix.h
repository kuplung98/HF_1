#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <initializer_list>
#include <cmath>
#include <string>
#include <sstream>

//Helper functions:
namespace detail
{
	template<typename M1, typename M2, typename F>
	void transform_matrix1(M1 const& m1, M2& m2, F f)
	{
		std::transform(m1.cbegin(), m1.cend(), m2.begin(), f);
	}

	template<typename M1, typename M2, typename M3, typename F>
	void transform_matrix2(M1 const& m1, M2 const& m2, M3& m3, F f)
	{
		std::transform(m1.cbegin(), m1.cend(), m2.cbegin(), m3.begin(), f);
	}
}

//Common lambdas:
inline auto add = [](auto const& x, auto const& y){ return x + y; };
inline auto sub = [](auto const& x, auto const& y){ return x - y; };

// Helper structs:
struct Idx1{}; 
struct Idx2{};

template<typename T> 
T sq(T a)
{
    return a * a;
}

template<typename T>
class Matrix
{
	
	int N;
   	std::vector<T> data;
	
public:

	//2D operator for reading and writing:
	T&       operator()( int i, int j )      
		{ return data[N*i+j]; }
	T const& operator()( int i, int j ) const 
		{ return data[N*i+j]; }

	//1D operator for reading and writing:
	T&       operator[]( int i )      
		{ return data[i]; }
	T const& operator[]( int i) const 
		{ return data[i]; }


	//Default, Copy and Move constructors implemented by the compiler:
	Matrix( Matrix const& ) = default;
	Matrix( Matrix && m)
	{
		N=m.n();
		//data.resize(sq(N));
		data = std::move(m.data);
		m.N=0;
		m.data.resize(0);
	}
	Matrix():N{0}
    {
        data.resize(sq(N));
	}

	//Copy and Move assignment operators implemented by the compiler:
	Matrix<T>& operator=(Matrix const&) = default;
	Matrix<T>& operator=(Matrix && m)
	{
		N=m.n();
		//data.resize(sq(N));
		data = std::move(m.data);
		m.N=0;
		m.data.resize(0);
		return *this;
	}

	//Constructs from function :
	template<typename F>
	Matrix(Idx1, F f, int n)
	{
		N = n;
		data.resize(sq(n));

    	for(int j=0;j < size();j++)
    	{
        	data[j]=f(j);
    	}
		
	}

	template<typename F>
	Matrix (Idx2, F f, int n)
	{
		N = n;
		data.resize(sq(n));

    	for(int i=0;i<=n-1;i++)
    	{
        	for(int j=0;j<=n-1;j++)
        	{
            	data[n*i+j]=f(i,j);
        	}
		}
	}

	//Construct from initializer list:
	Matrix(int n, std::initializer_list<T> const& il ) :N{n}, data{il}
	{
		 if(il.size()!=static_cast<size_t>(sq(n)))
        {
            std::cout<<"The dimension of the matrix does not match number of the elements!"<<std::endl;
            std::exit(-1);
		
		}
	}

	//Number of elements of the Matrix:
	int size()const
	{
		return static_cast<int>(data.size());
	}

	int n()const
	{
		return N;
	}	

	//begin and end for compatibility with STL:
	auto begin()
	{
		return data.begin();
	}

	auto cbegin() const
	{
		return data.cbegin();
	}

	auto end()
	{
		return data.end();
	}

	auto cend() const
	{
		return data.cend();
	}
	
	//Add assignment operators:
	Matrix<T>& operator+= (Matrix<T> const& cpy)
	{
		detail::transform_matrix2(*this, cpy, *this, add);
		return *this;
	}

	//Subtract assignment operators:
	Matrix<T>& operator-= (Matrix<T> const& cpy)
	{
		detail::transform_matrix2(*this, cpy, *this, sub);
		return *this;
	}

	//Multiplication by scalar:
	Matrix<T>& operator*= (T const& scl)
	{
		detail::transform_matrix1(*this, *this, [=](T const& x){ return x * scl;} );
		return *this;
	}

	//Division by scalar:
	Matrix<T>& operator/= (T const& scl)
	{
		detail::transform_matrix1(*this, *this, [=](T const& x){ return x / scl;} );
		return *this;
	}

	// + operator:

	friend
	Matrix<T> operator+( Matrix<T>  const& m1, Matrix<T>  const& m2)
	{
		return Matrix<T>(Idx1{}, [&](auto i){ return m1[i] + m2[i]; }, m1.n());	
	}

	friend
	Matrix<T>&& operator+( Matrix<T>&& m1, Matrix<T> const& m2 )
	{
		detail::transform_matrix2(m1, m2, m1, add);
		return  std::move(m1);	
	}

	friend
	Matrix<T>&& operator+( Matrix<T> const& m1, Matrix<T>&& m2 )
	{
		detail::transform_matrix2(m1, m2, m2, add);
		return  std::move(m2);	
	}

	friend
	Matrix<T>&& operator+( Matrix<T>&& m1, Matrix<T>&& m2 )
	{
		detail::transform_matrix2(m1, m2, m1, add);
		return  std::move(m1);	
	}

	// - operator:

	friend
	Matrix<T> operator-( Matrix<T> const& m1, Matrix<T> const& m2 )
	{
		return Matrix<T>(Idx1{}, [&](auto i){ return m1[i] - m2[i]; },m1.n());
	}

	friend
	Matrix<T>&& operator-( Matrix<T>&& m1, Matrix<T> const& m2 )
	{
		detail::transform_matrix2(m1, m2, m1, sub);
		return  std::move(m1);	
	}

	friend
	Matrix<T>&& operator-( Matrix<T> const& m1, Matrix<T>&& m2 )
	{
		detail::transform_matrix2(m1, m2, m2, sub);
		return  std::move(m2);	
	}

	friend
	Matrix<T>&& operator-( Matrix<T>&& m1, Matrix<T>&& m2 )
	{
		detail::transform_matrix2(m1, m2, m1, sub);
		return  std::move(m1);	
	}

	// * operator (by scalar):

	friend
	Matrix<T> operator*(Matrix<T> const& m, T const& scl)
	{
		return Matrix<T>(Idx1{}, [&](auto i){ return m[i] * scl; }, m.n());
	}

	friend
	Matrix<T>&& operator*(Matrix<T>&& m, T const& scl)
	{
		detail::transform_matrix1(m, m, [=](T const& x){ return x * scl;} );
		return std::move(m);
	}

	friend
	Matrix<T> operator*(T const& scl, Matrix<T> const& m)
	{
		return Matrix<T>(Idx1{}, [&](auto i){ return scl * m[i] ; }, m.n());
	}

	friend
	Matrix<T>&& operator*(T const& scl, Matrix<T>&& m)
	{
		detail::transform_matrix1(m, m, [=](T const& x){ return x * scl;} );
		return std::move(m);
	}

	// / operator:

	friend
	Matrix<T> operator/(Matrix<T> const& m, T const& scl)
	{
		return Matrix<T>(Idx1{}, [&](auto i){ return m[i] / scl; }, m.n());
	}

	friend
	Matrix<T>&& operator/(Matrix<T>&& m, T const& scl)
	{
		detail::transform_matrix1(m, m, [=](T const& x){ return x / scl;} );
		return std::move(m);
	}

	//Matrix multiplication:

	friend
	Matrix<T> operator*(Matrix<T> const& m1, Matrix<T> const& m2)
	{
		int N = m1.n();
		return Matrix<T> (Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for(int k = 0; k<N; ++k)
			{
				sum += m1(i, k) * m2(k, j);
			}
			return sum;
		},  N);
	}

	friend
	Matrix<T>&& operator*(Matrix<T> && m1, Matrix<T> const& m2)
	{
		int N = m1.n();
		std::vector<T> v(N);
		for(int i=0;i<N;i++)
    	{
        	for(int j=0;j<N;j++)
        	{
				T sum = 0.0;
				for(int k = 0; k<N; ++k)
				{
					sum += m1(i, k) * m2(k, j);
				}
				v[j]=sum;
			}
			for(int j=0;j<N;j++)
			{
				m1(i, j)=v[j];
			}
		}
		return std::move(m1);	
	}

	friend
	Matrix<T>&& operator*(Matrix<T> const& m1, Matrix<T> && m2)
	{
		int N = m2.n();
		std::vector<T> v(N);
		for(int i=0;i<N;i++)
    	{
        	for(int j=0;j<N;j++)
        	{
				T sum = 0.0;
				for(int k = 0; k<N; ++k)
				{
					sum += m1(j, k) * m2(k, i);
				}
				v[j]=sum;
			}
		
			for(int j=0;j<N;j++)
			{
				m2(j, i)=v[j];
			}

		}
		return std::move(m2);
	}

	friend
	Matrix<T>&& operator*(Matrix<T> && m1, Matrix<T> && m2)
	{
		int N = m1.n();
		std::vector<T> v(N);
		for(int i=0;i<N;i++)
    	{
        	for(int j=0;j<N;j++)
        	{
				T sum = 0.0;
				for(int k = 0; k<N; ++k)
				{
					sum += m1(i, k) * m2(k, j);
				}
				v[j]=sum;
			}
			for(int j=0;j<N;j++)
			{
				m1(i, j)=v[j];
			}
		}
		return std::move(m1);
	}

	// ostream

	friend
	std::ostream& operator<< (std::ostream& o, Matrix<T> const& m)
	{
		int n = m.size();
		o<< m.n() <<";";
		if( n > 0 )
		{
			for(int i=0; i<=n-2; ++i)
			{
				o << m[i] << ",";
			}
			o << m[n-1];
		}
		return o;
	}

	// istream

	friend
	std::istream& operator>> (std::istream& s, Matrix<T> & m)
	{
		const auto state= s.rdstate();
		const auto pos= s.tellg();

		std::string tmp;
		std::getline(s, tmp);
		std::stringstream ss(tmp);

		std::getline(ss,tmp,';');
		if(tmp.size() == 0){ s.seekg(pos); s.setstate(state); return s; }
		m.N = std::stoi(tmp);
		int n = m.N*m.N;
		m.data.resize(n);
		for(int i=0; i<=n-2; ++i)
		{
			std::getline(ss, tmp, ','); 
			if(tmp.size() == 0){ s.seekg(pos); s.setstate(state); return s; }
			std::stringstream dat(tmp);
			dat>>m.data[i];
		}
		std::getline(ss, tmp);
		if(tmp.size() == 0){ s.seekg(pos); s.setstate(state); return s; }
		std::stringstream dat1(tmp);
		dat1>>m.data[n-1];
		
		return s;
	
	}
};
