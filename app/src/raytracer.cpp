#include "raytracer.h"
#include "system/ctimeelapsed.h"
#include "utility/on_scope_exit.hpp"

#include <QImage>

RayTracer::RayTracer() :
	_camera(Point(0.0f, 3.0f, 0.0f))
{
}

void RayTracer::setProgressChangedCallback(std::function<void (size_t)> callback) noexcept
{
	_progressCallback = std::move(callback);
}

std::pair<QImage, uint64_t> RayTracer::render(size_t w, size_t h) noexcept
{
	_inProgress = true;
	EXEC_ON_SCOPE_EXIT([this] {	_inProgress = false; });

	CTimeElapsed timer{true};

	_camera.setResolution(w, h);

	QImage buf((int)w, (int)h, QImage::Format_RGB32);
	const auto eighthLine = h / 8;
	for (size_t y = 0; y < h; ++y)
	{
		auto* scanLine = buf.scanLine((int)y);
		for (size_t x = 0; x < w; ++x)
		{
			const auto colorValue = _scene.intersect(_camera.rayForPixel(x, y)).to32bit();
			::memcpy(scanLine + x * sizeof(uint32_t), &colorValue, sizeof(uint32_t));
		}

		if (y % eighthLine == 0)
			_progressCallback(y * 100 / h);
	}

	_progressCallback(100);
	return {buf, timer.elapsed<std::chrono::microseconds>()};
}

bool RayTracer::inProgress() const noexcept
{
	return _inProgress;
}
