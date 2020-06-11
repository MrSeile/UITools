#pragma once

#define _USE_MATH_DEFINES

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <functional>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <math.h>

#include "Vec2.h"

#ifndef PI
#define PI M_PI
#endif

typedef unsigned int uint;

namespace ui
{
	typedef Vec2<float> Vec2f;
	typedef Vec2<double> Vec2d;
	typedef Vec2<int> Vec2i;
	typedef Vec2<uint> Vec2u;

	inline float map(const float& value, const float& inputMin, const float& inputMax, const float& outputMin, const float& outputMax)
	{
		return outputMin + ((outputMax - outputMin) / (inputMax - inputMin)) * (value - inputMin);
	}

	inline float snap(const float& value, const float& step)
	{
		return roundf(value / step) * step;
	}

	template<typename T>
	inline T RadToDeg(const T& rad)
	{
		return (rad * (T)180) / (T)PI;
	}

	template<typename T>
	inline T DegToRad(const T& deg)
	{
		return (deg * (T)PI) / (T)180;
	}

	//inline bool inBetween()
}