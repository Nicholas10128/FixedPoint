#pragma once

#include <iostream>
#include <stdint.h>
#include "FixedPoint.h"

/*****************************
[-2097152.0~2097151.990234375]
*****************************/
class CLASS_DECLSPEC FScalar
{
public:
	FScalar(float floatValue);

	inline FScalar & operator =(const FScalar & fs);
	inline friend CLASS_DECLSPEC FScalar & operator +(const FScalar & fs1, const FScalar & fs2);
	inline friend CLASS_DECLSPEC FScalar & operator -(const FScalar & fs1, const FScalar & fs2);
	inline friend CLASS_DECLSPEC FScalar & operator *(const FScalar & fs1, const FScalar & fs2);
	inline friend CLASS_DECLSPEC FScalar & operator /(const FScalar & fs1, const FScalar & fs2);
	inline friend CLASS_DECLSPEC std::ostream & operator<<(std::ostream & os, const FScalar & fs);

private:
	int32_t rawValue;

	static const int32_t fractionBits = 10;
	static const int32_t wholeBits = 22;
	static const int32_t fractionRate = 1 << fractionBits;
	const float_t fractionRateReciprocal = 1.0f / fractionRate;
	
	static FScalar retBuffer;
};
