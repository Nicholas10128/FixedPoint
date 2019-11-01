#include "stdafx.h"
#include <math.h>
#include <assert.h>
#include "FScalar.h"

FScalar FScalar::retBuffer(0);

FScalar::FScalar(float floatValue)
{
	rawValue = (int)(floatValue * fractionRate);
}

inline FScalar & FScalar::operator =(const FScalar & fs)
{
	rawValue = fs.rawValue;
	return *this;
}

inline FScalar & operator +(const FScalar & fs1, const FScalar & fs2)
{
	FScalar::retBuffer.rawValue = fs1.rawValue + fs2.rawValue;
	return FScalar::retBuffer;
}

inline FScalar & operator -(const FScalar & fs1, const FScalar & fs2)
{
	FScalar::retBuffer.rawValue = fs1.rawValue - fs2.rawValue;
	return FScalar::retBuffer;
}

inline FScalar & operator *(const FScalar & fs1, const FScalar & fs2)
{
	FScalar::retBuffer.rawValue = ((int64_t)fs1.rawValue * fs2.rawValue) >> FScalar::fractionBits;
	return FScalar::retBuffer;
}

inline FScalar & operator /(const FScalar & fs1, const FScalar & fs2)
{
	FScalar::retBuffer.rawValue = ((int64_t)fs1.rawValue << FScalar::fractionBits) / fs2.rawValue;
	return FScalar::retBuffer;
}

inline std::ostream & operator<<(std::ostream & os, const FScalar & fs)
{
	os << fs.rawValue * fs.fractionRateReciprocal;
	return os;
}
