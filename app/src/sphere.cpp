#include "sphere.h"

std::optional<Vec> Sphere::intersection(const Ray &ray) const noexcept
{
	const auto r = ray.vec3();
	const auto ro = ray.origin();

	const auto L = ro - _center;
	const auto a = r.length_squared();
	const auto b = 2_f * r.dot(L);
	const auto c = L.length_squared() - _r * _r;

	const auto D = b * b - 4_f * a * c;
	if (D < 0_f) [[likely]]
		return {};

	const auto d = std::sqrt(D);
	const auto t1 = (-b + d) / (2_f * a);
	const auto t2 = (-b - d) / (2_f * a);

	if (t1 < 0_f && t2 < 0_f)
		return {};
	else if (t1 < 0_f || t2 < 0_f)
		return ro + r * std::max(t1, t2);
	else [[likely]]
		return ro + r * std::min(t1, t2);
}
