#include "sphere.h"

std::optional<Vec> Sphere::intersection(const Ray &ray) const noexcept
{
	const auto r = ray.vec3();
	const auto ro = ray.origin();
	const auto a = r.length_squared();
	const auto b =
		2_f * r.x * (ro.x - _center.x) +
		2_f * r.y * (ro.y - _center.y) +
		2_f * r.z * (ro.z - _center.z);

	const auto c =
		_center.length_squared()
		+ ro.length_squared()
		+ -2_f * (_center.x * ro.x + _center.y * ro.y + _center.z * ro.z)
		- _r * _r;

	const auto D = b * b - 4_f * a * c;
	if (D < 0_f) [[likely]]
		return {};

	const auto t = (-b - std::sqrt(D)) / (2_f * a);
	return ro + r * t;
}
