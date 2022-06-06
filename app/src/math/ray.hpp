#pragma once
#include "vector.hpp"

template <typename T>
struct RayX
{
	constexpr RayX(Vec3<T> ray, Vec3<T> origin) noexcept :
		_ray{std::move(ray)},
		_origin{std::move(origin)}
	{
		_ray.normalize();
	}

	[[nodiscard]] constexpr Vec3<T> vec3() const noexcept
	{
		return _ray;
	}

	[[nodiscard]] constexpr Vec3<T> origin() const noexcept
	{
		return _origin;
	}

private:
	Vec3<T> _ray;
	Vec3<T> _origin;
};
