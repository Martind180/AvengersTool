#pragma once
#ifndef MMATH_H
#define MMATH_H

#include <cmath>
#include "vectors.h"

constexpr float PI = 3.14159265358979323846f;


float dotProduct(const vec2<float>& v1, const vec2<float>& v2);
float dotProduct(const vec3<float>& v1, const vec3<float>& v2);

float determinant(const vec2<float>& v1, const vec2<float>& v2);

float angleBetween(const vec2<float>& v1, const vec2<float>& v2);

float magnitude(const vec2<float>& v);
float magnitude(const vec3<float>& v);

float toRadians(float degrees);
float toDegrees(float radians);

float tiltAngle(const vec2<float>& v);

vec2<float> truncateVector(const vec3<float>& v);

vec3<float> subtractVector(const vec3<float>& v1, const vec3<float>& v2);  //v1 - v2
vec3<float> addVector(const vec3<float>& v1, const vec3<float>& v2);
vec2<float> addVector(const vec2<float>& v1, const vec2<float>& v2);
vec3<float> vectorNormalize(vec3<float> v);
vec2<float> vectorNormalize(vec2<float> v);
vec2<float> rotateVector(const vec2<float>& v, float angle);

float normalise(float value, float start, float end);
float distance(const vec2<float>& p1, const vec2<float>& p2);
float distance(const vec3<float>& p1, const vec3<float>& p2);

#endif
