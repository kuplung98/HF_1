#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>

template<typename T>
struct Vector2
{
    T x, y;

    Vector2<T>& operator+=( Vector2<T> const& v)
    {
    x += v.x;  y += v.y;
    return *this;
    }    

    Vector2<T>& operator-=( Vector2<T> const& v)
    {
    x -= v.x;  y -= v.y;
    return *this;
    }    

    Vector2<T>& operator*=( T const& b)
    {
    x *= b;  y *= b;
    return *this;
    }    

     Vector2<T>& operator/=( T const& b)
    {
    x /= b;  y /= b;
    return *this;
    }    
};

template<typename T>
Vector2<T>  operator+( Vector2<T>  const& a, Vector2<T>  const& b)
{
    return Vector2<T> { a.x + b.x, a.y + b.y};
}

template<typename T>
Vector2<T>  operator-( Vector2<T>  const& a, Vector2<T>  const& b)
{
    return Vector2<T> { a.x - b.x, a.y - b.y};
}

template<typename T>
Vector2<T>  operator*( Vector2<T>  const& a, T b)
{
    return Vector2<T> { a.x * b, a.y * b};
}

template<typename T>
Vector2<T>  operator*( T b, Vector2<T>  const& a)
{
    return Vector2<T> { b * a.x , b * a.y};
}

template<typename T>
Vector2<T>  operator/( Vector2<T>  const& a, T b)
{
    return Vector2<T> { a.x / b, a.y / b};
}

template<typename T>
T dot(Vector2<T> const& a, Vector2<T> const& b)
{
    return a.x * b.x + a.y * b.y;
}

template<typename T>
T sq(T a)
{
    return a * a;
}

template<typename T>
T sqlength(Vector2<T> const& a)
{
    return sq(a.x) + sq(a.y) ;
}


template<typename T>
T length(Vector2<T> const& a)
{
    return  std::sqrt(sqlength(a));
}

template<typename T>
Vector2<T> normalize(Vector2<T> const& a)
{
    return a / length(a);
}

template<typename T>
std::ostream& operator<< (std::ostream& o, Vector2<T> const& v)
{
    o << v.x << ","<< v.y;
	return o;
}

template<typename T>
std::istream& operator>> (std::istream& s, Vector2<T> & v)
	{
		const auto state= s.rdstate();
		const auto pos= s.tellg();

		std::string tmp;
		std::getline(s, tmp);
		std::stringstream ss(tmp);
		
			std::getline(ss, tmp, ','); 
			if(tmp.size() == 0){ s.seekg(pos); s.setstate(state); return s; }
			v.x = std::stod(tmp);
            std::getline(ss, tmp); 
            if(tmp.size() == 0){ s.seekg(pos); s.setstate(state); return s; }
            v.y = std::stod(tmp);
		
		return s;
	
	}



