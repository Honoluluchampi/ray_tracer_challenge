#pragma once
#include <utils.hpp>
#include <math.h>
#include <iostream>

namespace renderer {

template <typename T>
struct tuple
{
    T x, y, z;
    // 1 indicates point, 0 indicates vector
    unsigned flag;
    tuple(T x_, T y_, T z_, unsigned f_) : x(x_), y(y_), z(z_), flag(f_) {}
    // the length of the vector
    T magnitude() const 
    {
        if(flag == 1) throw std::runtime_error("point doesnt have length.");
        else return std::sqrt(x*x + y*y + z*z);
    }
    tuple<T> normalize()
    {
        // exception for point normalization is thrown in magnitude();
        T mag = this->magnitude();
        x /= mag; y /= mag; z /= mag;
        return *this;
    }
};

// should be inline?
template <typename T> tuple<T> operator+ (const tuple<T>& lhs, const tuple<T>& rhs)
{ return tuple<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.flag + rhs.flag); }
template <typename T> tuple<T> operator- (const tuple<T>& lhs, const tuple<T>& rhs)
{ return tuple<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.flag - rhs.flag); }
template <typename T> tuple<T> operator* (const tuple<T>& lhs, const T& rhs)
{ return tuple<T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.flag); }
template <typename T> tuple<T> operator/ (const tuple<T>& lhs, const T& rhs)
{ return tuple<T>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.flag); }
template <typename T> tuple<T>& operator+= (tuple<T>& lhs, const tuple<T>& rhs)
{ lhs.x += rhs.x; lhs.y += rhs.y; lhs.z += rhs.z; lhs.flag += rhs.flag; return lhs; }
template <typename T> tuple<T>& operator-= (tuple<T>& lhs, const tuple<T>& rhs)
{ lhs.x -= rhs.x; lhs.y -= rhs.y; lhs.z -= rhs.z; lhs.flag -= rhs.flag; return lhs; }
template <typename T> tuple<T>& operator*= (tuple<T>& lhs, const T& rhs)
{ lhs.x *= rhs; lhs.y *= rhs; lhs.z *= rhs; return lhs; }
template <typename T> tuple<T>& operator/= (tuple<T>& lhs, const T& rhs)
{ lhs.x /= rhs; lhs.y /= rhs; lhs.z /= rhs; return lhs; }

// for comparision
template <typename T> bool operator== (const tuple<T>& lhs, const tuple<T>& rhs)
{ return (nearlyEqual<T>(lhs.x, rhs.x) && nearlyEqual<T>(lhs.y, rhs.y) && nearlyEqual<T>(lhs.z, rhs.z) && lhs.flag == rhs.flag); }
template <typename T> bool operator!= (const tuple<T>& lhs, const tuple<T>& rhs)
{ return !(lhs == rhs); }

template <typename T>
void pointOrVector(const tuple<T>& t)
{
    if(t.flag == 0) 
        std::cout << "this tuple is a point." << std::endl;
    else if(t.flag == 1)
        std::cout << "this tuple is a vector." << std::endl;
    else
        std::cout << "this is neither a point nor a vector." << std::endl;
}

template <typename T>
inline tuple<T> pointFactory(T x, T y, T z) { return tuple<T>(x, y, z, 1); }

template <typename T>
inline tuple<T> vectorFactory(T x, T y, T z) { return tuple<T>(x, y, z, 0); }

// dot, cross product
template <typename T>
inline T dot(const tuple<T>& a, const tuple<T>& b)
{
    // if I accidentally use dot() for points, I would be able to detect the bug thanks to flag*flag (=1);
    return a.x*b.x + a.y*b.y + a.z*b.z + a.flag*b.flag;
}
template <typename T>
inline tuple<T> cross(const tuple<T>& a, const tuple<T>& b)
{
    return vectorFactory(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}
} // the end of the namespace