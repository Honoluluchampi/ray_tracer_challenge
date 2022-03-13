#pragma once
#include <math.h>

constexpr double EPSILON = 0.00001;

template <typename T>
inline bool nearlyEqual(const T& x, const T& y)
{ return std::abs(x-y) < EPSILON ? true :false; }

inline size_t pos2idx(const size_t x, const size_t y, const size_t width)
{ return x + y * width; }
