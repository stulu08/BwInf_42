#pragma once
#include "Core.h"

template<typename T>
struct vector4_t {
	using type_vec = vector4_t<T>;

	vector4_t() = default;
	vector4_t(const type_vec&) = default;
	vector4_t(type_vec&&) = default;

	T x, y, z, w;
};

template<typename T>
struct vector3_t {
	using type_vec = vector3_t<T>;

	vector3_t() = default;
	vector3_t(const type_vec&) = default;
	vector3_t(type_vec&&) = default;

	T x, y, z;
};

template<typename T>
struct vector2_t {
	using type_vec = vector2_t<T>;

	vector2_t() = default;
	vector2_t(const type_vec&) = default;
	vector2_t(type_vec&&) = default;

	T x, y;
};

using ivec2 = vector2_t<int32_t>;
using ivec3 = vector3_t<int32_t>;
using ivec4 = vector4_t<int32_t>;

using uvec2 = vector2_t<uint32_t>;
using uvec3 = vector3_t<uint32_t>;
using uvec4 = vector4_t<uint32_t>;