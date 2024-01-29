#include "mmath.h"

#include "vectors.h"


float dotProduct(const vec2<float>& v1, const vec2<float>& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float dotProduct(const vec3<float>& v1, const vec3<float>& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float determinant(const vec2<float>& v1, const vec2<float>& v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

float angleBetween(const vec2<float>& v1, const vec2<float>& v2)
{
	return atan2f(determinant(v1, v2), dotProduct(v1, v2));
}

float magnitude(const vec2<float>& v)
{
	using namespace std;
	return sqrtf(pow(v.x, 2) + pow(v.y, 2));
}

float magnitude(const vec3<float>& v)
{
	using namespace std;
	return sqrtf(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

float toRadians(float degrees)
{
	return degrees * PI / 180.f;
}

float toDegrees(float radians)
{
	return radians * 180.f / PI;
}

float tiltAngle(const vec2<float>& v)
{
	return normalise(std::atan2f(v.y, v.x) * 180.f / PI, 0.f, 360.f);
}

vec2<float> truncateVector(const vec3<float>& v)
{
	return vec2<float>(v.x, v.y);
}

vec3<float> subtractVector(const vec3<float>& v1, const vec3<float>& v2)
{
	return vec3<float>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

vec3<float> addVector(const vec3<float>& v1, const vec3<float>& v2)
{
	return vec3<float>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

vec2<float> addVector(const vec2<float>& v1, const vec2<float>& v2)
{
	return vec2<float>(v1.x + v2.x, v1.y + v2.y);
}

vec3<float> vectorNormalize(vec3<float> v)
{
	float m = magnitude(v);
	return vec3<float>(v.x / m, v.y / m, v.z / m);
}

vec2<float> vectorNormalize(vec2<float> v)
{
	float m = magnitude(v);
	return vec2<float>(v.x / m, v.y / m);
}

vec2<float> rotateVector(const vec2<float>& v, float angle)
{
	vec2<float> rv;

	rv.x = v.x * cosf(toRadians(angle)) + v.y * sinf(toRadians(angle));
	rv.y = -v.x * sinf(toRadians(angle)) + v.y * cosf(toRadians(angle));

	return rv;
}

float normalise(float value, float start, float end)  //TODO: start < 0
{
	if (end == 90.f) {
		if (value < 90.f) {
			value = normalise(value, 0, 360);  //LOL
		}
		value -= static_cast<int>(value / 90.f) * 90.f;
	}
	else if (end == 180.f) {
		value -= 360.f * std::floor((value + 180.f) * (1.f / 360.f));
	}
	else if (end == 360.f) {
		value -= 360.f * std::floor(value * (1.f / 360.f));
	}
	
	return value;
}

float distance(const vec2<float>& p1, const vec2<float>& p2)
{
	return sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2));
}

float distance(const vec3<float>& p1, const vec3<float>& p2)
{
	float dx = p1.x - p2.x;
	float dy = p1.y - p2.y;
	float dz = p1.z - p2.z;

	return (float)sqrt((dx * dx) + (dy * dy) + (dz * dz));
}
