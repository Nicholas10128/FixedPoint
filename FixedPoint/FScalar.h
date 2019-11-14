#pragma once

#include <iostream>
#include <stdint.h>
#include "FixedPoint.h"

/*****************************
[-2097152.0~2097151.990234375]
*****************************/
class DllExport FScalar
{
public:
	FScalar() noexcept;
	FScalar(float floatValue) noexcept;
	FScalar(int32_t scalarValue) noexcept;

	inline operator int() noexcept;
	inline operator float() noexcept;
	inline FScalar & operator =(const FScalar & fs) noexcept;
	inline FScalar & operator =(const float & floatValue) noexcept;
	inline FScalar & operator =(const int32_t & scalarValue) noexcept;
	inline friend DllExport FScalar & operator +(const FScalar & fs1, const FScalar & fs2) noexcept;
	inline friend DllExport FScalar & operator -(const FScalar & fs1, const FScalar & fs2) noexcept;
	inline friend DllExport FScalar & operator *(const FScalar & fs1, const FScalar & fs2) noexcept;
	inline friend DllExport FScalar & operator /(const FScalar & fs1, const FScalar & fs2) noexcept;
	inline friend DllExport std::ostream & operator<<(std::ostream & os, const FScalar & fs) noexcept;

	inline friend DllExport FScalar & sqrt(const FScalar & fs) noexcept;
	inline friend DllExport FScalar & pow(const FScalar & base, const FScalar & exponential) noexcept;
	inline friend DllExport FScalar & log2(const FScalar & fs) noexcept;
	inline friend DllExport FScalar & log(const FScalar & fs) noexcept;
	inline friend DllExport FScalar & log10(const FScalar & fs) noexcept;
	inline friend DllExport FScalar & exp(const FScalar & fs) noexcept;
	inline friend DllExport FScalar & sin(const FScalar & fs) noexcept;
	inline friend DllExport FScalar & cos(const FScalar & fs) noexcept;
	inline friend DllExport FScalar & asin(const FScalar & fs) noexcept;
	inline friend DllExport FScalar & acos(const FScalar & fs) noexcept;
	inline friend DllExport FScalar & atan(const FScalar & fs) noexcept;
	inline friend DllExport FScalar & acot(const FScalar & fs) noexcept;

private:
	int32_t rawValue;

	static const int32_t fractionBits = 10;
	static const int32_t wholeBits = 22;
	static const int32_t fractionRate = 1 << fractionBits;
	const float_t fractionRateReciprocal = 1.0f / fractionRate;
	
	static FScalar retBuffer;

	inline friend int32_t _sin(const int32_t & rawValue) noexcept;
	inline friend int32_t _cos(const int32_t & rawValue) noexcept;
};
