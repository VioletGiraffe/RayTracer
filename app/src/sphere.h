#pragma once
#include "types.hpp"

#include <optional>

class Sphere
{
public:
	constexpr Sphere(Point origin, FloatType radius) noexcept :
		_center{std::move(origin)},
		_r{radius}
	{}

	std::optional<Vec> intersection(const Ray& ray) const noexcept;

private:
	const Point _center;
	const FloatType _r;
};
