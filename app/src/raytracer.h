#pragma once

#include <functional>
#include <stdint.h>
#include <utility>

class QImage;

class RayTracer
{
public:
	RayTracer();

	void setProgressChangedCallback(std::function<void(int)> callback) noexcept;

	std::pair<QImage, uint64_t> render(int w, int h) noexcept;

private:
	std::function<void(int)> _progressCallback = nullptr;
};
