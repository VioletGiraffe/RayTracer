#pragma once
#include "types.hpp"
#include "sphere.h"
#include "color.hpp"

#include <variant>
#include <vector>


class Scene
{
public:
	Scene();

	Color intersect(const Ray& r) const noexcept;

private:
	struct Object {
		std::variant<Sphere> object;
		Color color;
	};

	std::vector<Object> _objects;
};
