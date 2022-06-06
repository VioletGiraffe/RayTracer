#include "camera.h"

void Camera::setResolution(size_t x, size_t y) noexcept
{
	_resolution = {x, y};
	const float aspect = x / (float)y;
	_screenSize.h = _screenSize.w / aspect;
}

Ray Camera::rayForPixel(size_t x, size_t y) const noexcept
{
	const float dx = _screenSize.w / _resolution.w;

	const float viewportTopLeftX = _screenSize.h * -0.5f;
	const float viewportTopLeftY = _screenSize.w;
	return Ray{Vec{viewportTopLeftX + dx * x, viewportTopLeftY - dx * y, _screenZ} - _pos, _pos};
}
