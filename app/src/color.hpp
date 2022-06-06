#pragma once

#include <stdint.h>

struct Color {
	uint8_t r;
	uint8_t g;
	uint8_t b;

	[[nodiscard]] inline constexpr uint32_t to32bit() const noexcept {
		return static_cast<uint32_t>(r << 16)
			 | static_cast<uint32_t>(g << 8)
			 | static_cast<uint32_t>(b);
	}
};
