#include "game_math.h"
#include "pch.h"

namespace mm
{
	float to_radians(float degrees)
	{
		return degrees * PI / 180.f;
	}

	vec2<float> truncate_vector(const vec3<float>& v)
	{
		return vec2<float>(v.x, v.y);
	}

	vec2<float> rotate_point(const vec2<float>& p1, const vec2<float>& p2, float angle)
	{
		vec2<float> p;
		angle = to_radians(angle);
		p.x = cosf(angle) * (p1.x - p2.x) - sinf(angle) * (p1.y - p2.y) + p2.x;
		p.y = sinf(angle) * (p1.x - p2.x) + cosf(angle) * (p1.y - p2.y) + p2.y;
		return p;
	}

	float normalise(float value, float start, float end)
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

	double short_to_angle(int angle)
	{
		return ((angle) * (360.0 / 65536));
	}

	float tilt_angle(const vec2<float>& v)
	{
		return normalise(std::atan2f(v.y, v.x) * 180.f / PI, 0.f, 360.f);
	}
	float to_degrees(float radians)
	{
		return radians * 180.f / PI;
	}
}
