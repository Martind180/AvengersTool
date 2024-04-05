#pragma once
#include "vectors.h"
#include "cod4Structs.h"

namespace mm
{
	constexpr float PI = 3.14159265358979323846f;
	vec2<float> truncate_vector(const vec3<float>& v);
	vec2<float> rotate_point(const vec2<float>& p1, const vec2<float>& p2, float angle);  //p1 around p2
	float normalise(float value, float start, float end);
	double short_to_angle(int angle);
	float tilt_angle(const vec2<float>& v);
	float to_degrees(float radians);
	void angle_vectors(vec3<float> angles, float* forward, float* right, float* up);
	void angle_vectors(vec3<float> angles, vec3<float>* forward, vec3<float>* right, vec3<float>* up);
}
