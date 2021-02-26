#pragma once

#include <cstdint>
#include <cstddef>
#include "common/include/glm.h"

template <typename T> uint32_t thash(const T& p)
{
	uint32_t h = 5381;
	const uint8_t *c = (const uint8_t *)&p;
	for (size_t i = 0; i < sizeof(T); ++i) {
		h = ((h << 5) + h) + c[i];
	}
	return h;
}

template <> uint32_t inline thash<glm::vec3> (const glm::vec3& p) {
	return thash(p.x) ^ thash(p.y) ^ thash(p.z);
}
