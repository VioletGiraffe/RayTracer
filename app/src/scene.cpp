#include "scene.h"
#include "color.hpp"

Scene::Scene()
{
	_objects.emplace_back(Object{Sphere(Point(-6.0f, 6.0f, 10.0f), 2.0f), {255, 255, 0}});
}

Color Scene::intersect(const Ray &r) const noexcept
{
	for (auto&& sceneItem: _objects)
	{
		auto intersection = std::visit([&r](auto&& item) {
			return item.intersection(r);
		}, sceneItem.object);

		if (!intersection)
			continue;

		return sceneItem.color;
	}

	return Color{30, 180, 250};
}
