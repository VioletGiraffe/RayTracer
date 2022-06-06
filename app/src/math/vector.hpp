#pragma once

#include <cmath>
#include <stdint.h>
#include <type_traits>

template <typename T, int /* tag */ = 0>
struct Vec3
{
	constexpr Vec3() noexcept = default;

	constexpr Vec3(T x_, T y_, T z_) noexcept :
		x{x_}, y{y_}, z{z_}
	{}

	constexpr Vec3(T val) noexcept :
		Vec3(val, val, val)
	{}

	[[nodiscard]] constexpr T length_squared() const noexcept
	{
		return x * x + y * y + z * z;
	}

	[[nodiscard]] constexpr T length() const noexcept
	{
		return static_cast<T>(std::sqrt(length_squared()));
	}

	[[nodiscard]] constexpr T abs() const noexcept {return length();}

	[[nodiscard]] constexpr Vec3 operator*(T k) const noexcept
	{
		return Vec3(x * k, y * k, z * k);
	}

	[[nodiscard]] constexpr Vec3 operator/(T k) const noexcept
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			const auto r = T(1) / k;
			return Vec3(x * r, y * r, z * r);
		}
		else
			return Vec3(x / k, y / k, z / k);
	}

	[[nodiscard]] constexpr Vec3 operator+(const Vec3& v) const noexcept
	{
		return Vec3(x + v.x, y + v.y, z + v.z);
	}

	[[nodiscard]] constexpr Vec3 operator-(const Vec3& v) const noexcept
	{
		return Vec3(x - v.x, y - v.y, z - v.z);
	}

	constexpr Vec3& operator*=(T k) noexcept
	{
		return *this = (*this) * k;
	}

	constexpr Vec3& operator/=(T k) noexcept
	{
		return *this = (*this) / k;
	}

	constexpr Vec3& normalize() noexcept
	{
		const auto l = abs(); // Cannot be negative by definition
		if (l > T(1e-15)) [[unlikely]]
		{
			*this /= l;
		}

		return *this;
	}

	[[nodiscard]] constexpr T dot(const Vec3& v) const noexcept
	{
		return x * v.x + y * v.y + z * v.z;
	}

	[[nodiscard]] constexpr Vec3 cross(const Vec3& v) const noexcept
	{
		return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	T x, y, z;
};

template <typename T>
struct Vec4
{
	constexpr Vec4() noexcept = default;
	constexpr Vec4(T x_, T y_, T z_, T w_) noexcept :
		x{x_}, y{y_}, z{z_}, w{w_}
	{}
	constexpr Vec4(T val) noexcept :
		Vec4(val, val, val, val)
	{}

	constexpr Vec4(const Vec3<T>& v, T w) noexcept :
		Vec4(v.x, v.y, v.z, w)
	{}

	[[nodiscard]] constexpr Vec3<T> xyz() const noexcept
	{
		return Vec3<T>(x, y, z);
	}

	T x, y, z, w;
};

//using Vec3i = Vec3<int64_t>;
//using Vec3f = Vec3<float>;
//using Vec3d = Vec3<double>;

//using Point3i = Vec3<int64_t, 1>;
//using Point3f = Vec3<float, 1>;
//using Point3d = Vec3<double, 1>;

//using Vec4i = Vec4<int64_t>;
//using Vec4f = Vec4<float>;
//using Vec4d = Vec4<double>;
