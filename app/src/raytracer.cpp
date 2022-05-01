#include "raytracer.h"
#include "random/randomnumbergenerator.h"
#include "system/ctimeelapsed.h"

#include <QImage>

RayTracer::RayTracer()
{
}

void RayTracer::setProgressChangedCallback(std::function<void(int)> callback) noexcept
{
	_progressCallback = std::move(callback);
}

std::pair<QImage, uint64_t> RayTracer::render(int w, int h) noexcept
{
	CTimeElapsed timer{true};

	using RandRGB = RNG<uint32_t>;

	QImage buf(w, h, QImage::Format_RGB32);
	const auto eigthLine = h / 8;
	for (int y = 0; y < h; ++y)
	{
		auto* scanLine = buf.scanLine(y);
		for (int x = 0; x < w; ++x)
		{
			const auto value = RandRGB::next() | 0xFF000000U;
			memcpy(scanLine + x * 4, &value, sizeof(value));
		}

		if (y % eigthLine == 0)
			_progressCallback(y * 100 / h);
	}

	_progressCallback(100);
	return {buf, timer.elapsed<std::chrono::microseconds>()};
}
