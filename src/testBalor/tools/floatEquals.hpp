#pragma once

#include <algorithm>
#include <cmath>
#include <limits>


namespace tools {



/// ���������_���̌덷���l���������l����
inline bool floatEquals(float lhs, float rhs) {
	float d = std::max(std::abs(lhs), std::abs(rhs));
	return (d == 0.0f ? 0.0f : std::abs(lhs - rhs) / d) <= std::numeric_limits<float>::epsilon();
}


/// ���������_���̌덷���l���������l����
inline bool floatEquals(double lhs, double rhs) {
	double d = std::max(std::abs(lhs), std::abs(rhs));
	return (d == 0.0 ? 0.0 : std::abs(lhs - rhs) / d) <= std::numeric_limits<double>::epsilon();
}



}