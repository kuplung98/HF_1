#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <initializer_list>
#include <cmath>
#include <string>
#include <sstream>

// Helper structs:
struct Idx1{}; 
struct Idx2{};

template<typename T>
class Matrix
{
	
	int N;
   	std::vector<T> data;
	
public:

   	T sq(T a)
	{
    return a * a;
	}

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
	Matrix( Matrix && ) = default;
	Matrix():N{0}
    {
        data.resize(static_cast<size_t>(sq(N)));
	}

	//Copy and Move assignment operators implemented by the compiler:
	Matrix<T>& operator=(Matrix const&) = default;
	Matrix<T>& operator=(Matrix &&) = default;

	//Constructs from function :
	template<typename F>
	Matrix(Idx1, F f, int N)
	{
		data.resize(sq(N));

    	for(int j=0;j<=sq(N)-1;j++)
    	{
        	data[j]=f(j);
    	}
		
	}

	template<typename F>
	Matrix(Idx2, F f, int N)
	{
		data.resize(sq(N));

    	for(int i=0;i<=N-1;i++)
    	{
        	for(int j=0;j<=N-1;j++)
        	{
            	data[N*i+j]=f(i,j);
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
		*this = Matrix<T>(Idx1{}, [&](auto i){ return (*this)[i] + cpy[i]; }, std::sqrt((*this).size()));
		return *this;
	}

	//Subtract assignment operators:
	Matrix<T>& operator-= (Matrix<T> const& cpy)
	{
		*this = Matrix<T>(Idx1{}, [&](auto i){ return (*this)[i] - cpy[i]; }, std::sqrt((*this).size()));
		return *this;
	}


	//Multiplication by scalar:
	Matrix<T>& operator*= (T const& scl)
	{
		*this = Matrix<T>(Idx1{}, [&](auto i){ return (*this)[i] * scl; }, std::sqrt((*this).size()));
		return *this;
	}

	//Division by scalar:
	Matrix<T>& operator/= (T const& scl)
	{
		*this = Matrix<T>(Idx1{}, [&](auto i){ return (*this)[i] / scl; }, std::sqrt((*this).size()));
		return *this;
	}

	// + operator:

	friend
	Matrix<T> operator+( Matrix<T>  const& m1, Matrix<T>  const& m2)
	{
		return Matrix<T>(Idx1{}, [&](auto i){ return m1[i] + m2[i]; }, std::sqrt(m1.size()));	
	}

	friend
	Matrix<T>&& operator+( Matrix<T>&& m1, Matrix<T> const& m2 )
	{
		m1 = Matrix<T>(Idx1{}, [&](auto i){ return m1[i] + m2[i]; }, std::sqrt(m2.size()));
		return std::move(m1);
	}

	friend
	Matrix<T>&& operator+( Matrix<T> const& m1, Matrix<T>&& m2 )
	{
		m2 = Matrix<T>(Idx1{}, [&](auto i){ return m1[i] + m2[i]; }, std::sqrt(m1.size()));
		return std::move(m2);
	}

	friend
	Matrix<T>&& operator+( Matrix<T>&& m1, Matrix<T>&& m2 )
	{
		m1 = Matrix<T>(Idx1{}, [&](auto i){ return m1[i] + m2[i]; }, std::sqrt(m1.size()));
		return std::move(m1);
	}

	// - operator:

	friend
	Matrix<T> operator-( Matrix<T> const& m1, Matrix<T> const& m2 )
	{
		return Matrix<T>(Idx1{}, [&](auto i){ return m1[i] - m2[i]; }, std::sqrt(m1.size()));
	}

	friend
	Matrix<T>&& operator-( Matrix<T>&& m1, Matrix<T> const& m2 )
	{
		m1 = Matrix<T>(Idx1{}, [&](auto i){ return m1[i] - m2[i]; }, std::sqrt(m2.size()));
		return std::move(m1);
	}

	friend
	Matrix<T>&& operator-( Matrix<T> const& m1, Matrix<T>&& m2 )
	{
		m2 = Matrix<T>(Idx1{}, [&](auto i){ return m1[i] - m2[i]; }, std::sqrt(m1.size()));
		return std::move(m2);
	}

	friend
	Matrix<T>&& operator-( Matrix<T>&& m1, Matrix<T>&& m2 )
	{
		m1 = Matrix<T>(Idx1{}, [&](auto i){ return m1[i] - m2[i]; }, std::sqrt(m1.size()));
		return std::move(m1);
	}

	// * operator (by scalar):

	friend
	Matrix<T> operator*(Matrix<T> const& m, T const& scl)
	{
		return Matrix<T>(Idx1{}, [&](auto i){ return m[i] * scl; }, std::sqrt(m.size()));
	}

	friend
	Matrix<T>&& operator*(Matrix<T>&& m, T const& scl)
	{
		m = Matrix<T>(Idx1{}, [&](auto i){ return m[i] * scl; }, std::sqrt(m.size()));
		return std::move(m);
	}

	friend
	Matrix<T> operator*(T const& scl, Matrix<T> const& m)
	{
		Matrix<T> result; result.data.resize(m.data.size());
		return Matrix<T>(Idx1{}, [&](auto i){ return scl * m[i] ; }, std::sqrt(m.size()));
	}

	friend
	Matrix<T>&& operator*(T const& scl, Matrix<T>&& m)
	{
		
		m = Matrix<T>(Idx1{}, [&](auto i){ return scl * m[i] ; }, std::sqrt(m.size()));
		return std::move(m);
	}

	// / operator:

	friend
	Matrix<T> operator/(Matrix<T> const& m, T const& scl)
	{
		Matrix<T> result; result.data.resize(m.data.size());
		return Matrix<T>(Idx1{}, [&](auto i){ return m[i] / scl; }, std::sqrt(m.size()));
	}

	friend
	Matrix<T>&& operator/(Matrix<T>&& m, T const& scl)
	{
		m = Matrix<T>(Idx1{}, [&](auto i){ return m[i] / scl; }, std::sqrt(m.size()));
		return std::move(m);
	}

	//Matrix multiplication:

	friend
	Matrix<T> operator*(Matrix<T> const& m1, Matrix<T> const& m2)
	{
		int N = std::sqrt(m1.size());
		auto m = Matrix<T> (Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for(int k = 0; k<N; ++k)
			{
				sum += m1(i, k) * m2(k, j);
			}
			return sum;
		}, N);

		return m;
	}

	friend
	Matrix<T>&& operator*(Matrix<T> && m1, Matrix<T> const& m2)
	{
		int N = std::sqrt(m2.size());
		m1 = Matrix<T> (Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for(int k = 0; k<N; ++k)
			{
				sum += m1(i, k) * m2(k, j);
			}
			return sum;
		}, N);

		return std::move(m1);
	}

	friend
	Matrix<T>&& operator*(Matrix<T> const& m1, Matrix<T> && m2)
	{
		int N = std::sqrt(m1.size());
		m2 = Matrix<T> (Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for(int k = 0; k<N; ++k)
			{
				sum += m1(i, k) * m2(k, j);
			}
			return sum;
		}, N);

		return std::move(m2);
	}

	friend
	Matrix<T>&& operator*(Matrix<T> && m1, Matrix<T> && m2)
	{
		int N = std::sqrt(m2.size());
		m1 = Matrix<T> (Idx2{}, [&](int i, int j)
		{
			T sum = 0.0;
			for(int k = 0; k<N; ++k)
			{
				sum += m1(i, k) * m2(k, j);
			}
			return sum;
		}, N);

		return std::move(m1);
	}

	// ostream

	friend
	std::ostream& operator<< (std::ostream& o, Matrix<T> const& m)
	{
		int n = m.size();
		o<<std::sqrt(n)<<";";
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
			m.data[i] = std::stod(tmp);
		}
		std::getline(ss, tmp);
		if(tmp.size() == 0){ s.seekg(pos); s.setstate(state); return s; }
		m.data[n-1] = std::stod(tmp);
		
		return s;
	
	}
};
