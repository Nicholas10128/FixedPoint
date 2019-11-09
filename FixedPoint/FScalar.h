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
	FScalar(float floatValue);

	inline operator int();
	inline operator float();
	inline FScalar & operator =(const FScalar & fs);
	inline friend DllExport FScalar & operator +(const FScalar & fs1, const FScalar & fs2);
	inline friend DllExport FScalar & operator -(const FScalar & fs1, const FScalar & fs2);
	inline friend DllExport FScalar & operator *(const FScalar & fs1, const FScalar & fs2);
	inline friend DllExport FScalar & operator /(const FScalar & fs1, const FScalar & fs2);
	inline friend DllExport std::ostream & operator<<(std::ostream & os, const FScalar & fs);

	inline friend DllExport FScalar & sqrt(const FScalar & fs);
	inline friend DllExport FScalar & pow(const FScalar & base, const FScalar & exponential);
	inline friend DllExport FScalar & log2(const FScalar & fs);
	inline friend DllExport FScalar & log(const FScalar & base, const FScalar & fs);
	inline friend DllExport FScalar & exp(const FScalar & fs);
	inline friend DllExport FScalar & sin(const FScalar & fs);
	inline friend DllExport FScalar & asin(const FScalar & fs);

private:
	int32_t rawValue;

	static const int32_t fractionBits = 10;
	static const int32_t wholeBits = 22;
	static const int32_t fractionRate = 1 << fractionBits;
	const float_t fractionRateReciprocal = 1.0f / fractionRate;
	
	static FScalar retBuffer;
};
