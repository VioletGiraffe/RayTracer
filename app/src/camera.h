#pragma once
#include "types.hpp"

class Camera
{
public:
	inline constexpr Camera(Point pos) noexcept :
		_pos{std::move(pos)}
	{}

	void setResolution(size_t x, size_t y) noexcept;

	[[nodiscard]] Ray rayForPixel(size_t x, size_t y) const noexcept;

private:
	Point _pos;
	FloatType _screenZ = 5.0_f;
	Size _screenSize {10.0_f, 10.0_f};
	Size2D<size_t> _resolution {0, 0};
};
