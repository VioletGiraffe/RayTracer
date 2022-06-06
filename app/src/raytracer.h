#pragma once
#include "scene.h"
#include "camera.h"

#include <atomic>
#include <functional>
#include <stdint.h>
#include <utility>

class QImage;

class RayTracer
{
public:
	RayTracer();

	void setProgressChangedCallback(std::function<void(size_t)> callback) noexcept;

	std::pair<QImage, uint64_t> render(size_t w, size_t h) noexcept;

	[[nodiscard]] bool inProgress() const noexcept;

private:
	Scene _scene;
	Camera _camera;
	std::function<void(size_t)> _progressCallback = nullptr;
	std::atomic_bool _inProgress {false};
};
