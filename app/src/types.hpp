#pragma once
#include "math/ray.hpp"
#include "math/size2d.hpp"

using FloatType = float;

using Vec = Vec3<FloatType>;
using Point = Vec;
using Size = Size2D<FloatType>;
using Ray = RayX<FloatType>;

[[nodiscard]] consteval FloatType operator "" _f(long double v)
{
	return static_cast<FloatType>(v);
}

[[nodiscard]] consteval FloatType operator "" _f(unsigned long long v)
{
	return static_cast<FloatType>(v);
}
