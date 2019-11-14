#include "stdafx.h"
#include <math.h>
#include "FScalar.h"

//extern "C" int64_t _Div128_64(int64_t a_low, int64_t a_high, int64_t b, int64_t* ret);
extern "C" int32_t _bsf_32(int32_t number);
extern "C" int32_t _bsr_32(int32_t number);

FScalar FScalar::retBuffer(0);

const int32_t e = 2783;
const int32_t log_e = 1477;
const int32_t log_10 = 3401;
const int32_t pi = 3217;
const int32_t pi_2 = pi >> 1;
const int32_t pi2 = pi << 1;
const int32_t sqrt_2 = 1448;

FScalar::FScalar() noexcept
{
	rawValue = 0;
}

FScalar::FScalar(float floatValue) noexcept
{
	rawValue = (int32_t)(floatValue * fractionRate);
}

FScalar::FScalar(int32_t scalarValue) noexcept
{
	rawValue = scalarValue;
}

inline FScalar::operator int() noexcept
{
	return rawValue;
}

inline FScalar::operator float() noexcept
{
	return rawValue * fractionRateReciprocal;
}

inline FScalar & FScalar::operator =(const FScalar & fs) noexcept
{
	rawValue = fs.rawValue;
	return *this;
}

inline FScalar & FScalar::operator =(const float & floatValue) noexcept
{
	rawValue = (int32_t)(floatValue * fractionRate);
	return *this;
}

inline FScalar & FScalar::operator =(const int32_t & scalarValue) noexcept
{
	rawValue = scalarValue;
	return *this;
}

inline FScalar & operator +(const FScalar & fs1, const FScalar & fs2) noexcept
{
	FScalar::retBuffer.rawValue = fs1.rawValue + fs2.rawValue;
	return FScalar::retBuffer;
}

inline FScalar & operator -(const FScalar & fs1, const FScalar & fs2) noexcept
{
	FScalar::retBuffer.rawValue = fs1.rawValue - fs2.rawValue;
	return FScalar::retBuffer;
}

inline FScalar & operator *(const FScalar & fs1, const FScalar & fs2) noexcept
{
	FScalar::retBuffer.rawValue = ((int64_t)fs1.rawValue * fs2.rawValue) >> FScalar::fractionBits;
	return FScalar::retBuffer;
}

inline FScalar & operator /(const FScalar & fs1, const FScalar & fs2) noexcept
{
	FScalar::retBuffer.rawValue = ((int64_t)fs1.rawValue << FScalar::fractionBits) / fs2.rawValue;
	return FScalar::retBuffer;
}

inline std::ostream & operator<<(std::ostream & os, const FScalar & fs) noexcept
{
	os << fs.rawValue * fs.fractionRateReciprocal;
	return os;
}

// The value range of the parameter is[0, 2097151.937]:
// Too large parameter will cause the int64 - based calculation process overflow and the correct result will not be obtained.
inline FScalar & sqrt(const FScalar & fs) noexcept
{
	if (fs.rawValue == 0)
	{
		FScalar::retBuffer.rawValue = 0;
		return FScalar::retBuffer;
	}
	int32_t n = _bsr_32(fs.rawValue) + 1;
	int64_t x, x2, x4;
	x = (((int64_t)fs.rawValue << FScalar::fractionBits) / (1i64 << n));
	x2 = (int64_t)x * x >> FScalar::fractionBits;
	x4 = x2 * x2 >> FScalar::fractionBits;
	int32_t extra = n - FScalar::fractionBits;
	int32_t sqrt2 = FScalar::fractionRate;
	int64_t result = 234 + ((1331 * x - 932 * x2 + ((513 * x2) >> FScalar::fractionBits) * x - 125 * x4) >> FScalar::fractionBits);
	if (n % 2 != 0)
	{
		sqrt2 = sqrt_2;
	}
	if (extra >= 0)
	{
		extra = (1i64 << (extra >> 1)) * sqrt2;
		FScalar::retBuffer.rawValue = (int32_t)(extra * result >> FScalar::fractionBits);
	}
	else
	{
		extra = (1i64 << (-extra >> 1)) * sqrt2;
		FScalar::retBuffer.rawValue = (int32_t)((result << FScalar::fractionBits) / extra);
	}
	return FScalar::retBuffer;
}

// For 32-bit fixed-point numbers of 22-bit integer bits, the accuracy of the calculation of pow is seriously lost and almost impossible.
inline FScalar & pow(const FScalar & base, const FScalar & exponential) noexcept
{
	int32_t n = _bsr_32(base.rawValue) + 1;
	int64_t x, x2, x4;
	x = (((int64_t)base.rawValue << FScalar::fractionBits) / (1i64 << n));
	x2 = (int64_t)x * x >> FScalar::fractionBits;
	x4 = x2 * x2 >> FScalar::fractionBits;
	int32_t logBase = (int32_t)(((n - FScalar::fractionBits) << FScalar::fractionBits) - 6163 + ((28610 * x - 60718 * x2 + ((59463 * x2) >> FScalar::fractionBits) * x - 21202 * x4) >> FScalar::fractionBits));
	int32_t rawValue = (int32_t)((int64_t)exponential.rawValue * logBase / log_e);
	bool isNegative = rawValue < 0;
	int32_t wholePart = (isNegative ? -rawValue : rawValue) >> FScalar::fractionBits;
	int64_t wholeResult = FScalar::fractionRate;
	for (int i = 0; i < wholePart; i++)
	{
		wholeResult = (wholeResult * e) >> FScalar::fractionBits;
	}
	x = (int64_t(rawValue - (wholePart << FScalar::fractionBits)) << FScalar::fractionBits) / FScalar::fractionRate;
	x2 = (int64_t)x * x >> FScalar::fractionBits;
	x4 = x2 * x2 >> FScalar::fractionBits;
	FScalar::retBuffer.rawValue = (int32_t)(wholeResult * (1024 + ((1023 * x + 520 * x2 + ((146 * x2) >> FScalar::fractionBits) * x + 69 * x4) >> FScalar::fractionBits)) >> FScalar::fractionBits);
	if (isNegative)
	{
		FScalar::retBuffer = (int32_t)((1i64 << FScalar::fractionBits) / FScalar::retBuffer.rawValue);
	}
	return FScalar::retBuffer;
}

// The value range of the parameter is (0, 2097151.937f]:
// The result of 0 is negative infinity, meaningless.
// Too large parameter will cause the int64-based calculation process overflow and will not get the correct result,
// and it is already very close to the maximum value that can be expressed by the 32-bit fixed-point number of 22-bit integer bits.
inline FScalar & log2(const FScalar & fs) noexcept
{
	int32_t n = _bsr_32(fs.rawValue) + 1;
	int64_t x, x2, x4;
	x = (((int64_t)fs.rawValue << FScalar::fractionBits) / (1i64 << n));
	x2 = (int64_t)x * x >> FScalar::fractionBits;
	x4 = x2 * x2 >> FScalar::fractionBits;
	FScalar::retBuffer.rawValue = (int32_t)(((n - FScalar::fractionBits) << FScalar::fractionBits) - 6163 + ((28610 * x - 60718 * x2 + ((59463 * x2) >> FScalar::fractionBits) * x - 21202 * x4) >> FScalar::fractionBits));
	return FScalar::retBuffer;
}

// The value range of the parameter is (0, 2097151.937f]:
// The result of 0 is negative infinity, meaningless.
// Too large parameter will cause the int64-based calculation process overflow and will not get the correct result,
// and it is already very close to the maximum value that can be expressed by the 32-bit fixed-point number of 22-bit integer bits.
inline FScalar & log(const FScalar & fs) noexcept
{
	int32_t n = _bsr_32(fs.rawValue) + 1;
	int64_t x, x2, x4;
	x = (((int64_t)fs.rawValue << FScalar::fractionBits) / (1i64 << n));
	x2 = (int64_t)x * x >> FScalar::fractionBits;
	x4 = x2 * x2 >> FScalar::fractionBits;
	int32_t fsValue = (int32_t)(((n - FScalar::fractionBits) << FScalar::fractionBits) - 6163 + ((28610 * x - 60718 * x2 + ((59463 * x2) >> FScalar::fractionBits) * x - 21202 * x4) >> FScalar::fractionBits));
	FScalar::retBuffer.rawValue = ((int64_t)fsValue << FScalar::fractionBits) / log_e;
	return FScalar::retBuffer;
}

inline FScalar & log10(const FScalar & fs) noexcept
{
	int32_t n = _bsr_32(fs.rawValue) + 1;
	int64_t x, x2, x4;
	x = (((int64_t)fs.rawValue << FScalar::fractionBits) / (1i64 << n));
	x2 = (int64_t)x * x >> FScalar::fractionBits;
	x4 = x2 * x2 >> FScalar::fractionBits;
	int32_t fsValue = (int32_t)(((n - FScalar::fractionBits) << FScalar::fractionBits) - 6163 + ((28610 * x - 60718 * x2 + ((59463 * x2) >> FScalar::fractionBits) * x - 21202 * x4) >> FScalar::fractionBits));
	FScalar::retBuffer.rawValue = ((int64_t)fsValue << FScalar::fractionBits) / log_10;
	return FScalar::retBuffer;
}

// The value range of the parameter is (-2.0, 14.5):
// The error is larger when the parameter is less than 0, because the 32-bit positioning number of the 22-bit integer bit cannot express such a high decimal precision.
// Too large parameter will cause the int64-based calculation process overflow and will not get the correct result,
// and it is already very close to the maximum value that can be expressed by the 32-bit fixed-point number of 22-bit integer bits.
inline FScalar & exp(const FScalar & fs) noexcept
{
	bool isNegative = fs.rawValue < 0;
	int32_t wholePart = (isNegative ? -fs.rawValue : fs.rawValue) >> FScalar::fractionBits;
	int64_t wholeResult = FScalar::fractionRate;
	for (int i = 0; i < wholePart; i++)
	{
		wholeResult = (wholeResult * e) >> FScalar::fractionBits;
	}
	int32_t x = (int64_t(fs.rawValue - (wholePart << FScalar::fractionBits)) << FScalar::fractionBits) / FScalar::fractionRate;
	int64_t x2 = (int64_t)x * x >> FScalar::fractionBits;
	int64_t x4 = x2 * x2 >> FScalar::fractionBits;
	FScalar::retBuffer.rawValue = (int32_t)(wholeResult * (1024 + ((1023 * x + 520 * x2 + ((146 * x2) >> FScalar::fractionBits) * x + 69 * x4) >> FScalar::fractionBits)) >> FScalar::fractionBits);
	if (isNegative)
	{
		FScalar::retBuffer = (int32_t)((1i64 << FScalar::fractionBits) / FScalar::retBuffer.rawValue);
	}
	return FScalar::retBuffer;
}

inline int32_t _sin(const int32_t & rawValue) noexcept
{
	int32_t fenzi = rawValue;
	int32_t fenmu = FScalar::fractionRate;
	int64_t fenzi2 = fenzi * fenzi;
	int64_t fenzi4 = fenzi2 * fenzi2;
	int64_t fenmu2 = fenmu * fenmu;
	int64_t fenmu4 = fenmu2 * fenmu2;
	return (int32_t)((1023 * fenzi * fenmu2 * fenmu + fenzi2 * fenmu2 - 179 * fenzi2 * fenzi * fenmu + 14 * fenzi4) / fenmu4);
}

inline int32_t _cos(const int32_t & rawValue) noexcept
{
	int32_t fenzi = rawValue;
	int32_t fenmu = FScalar::fractionRate;
	int64_t fenzi2 = fenzi * fenzi;
	int64_t fenzi4 = fenzi2 * fenzi2;
	int64_t fenmu2 = fenmu * fenmu;
	int64_t fenmu4 = fenmu2 * fenmu2;
	return (int32_t)(1023 + (- 514 * fenzi2 * fenmu2 + 3 * fenzi2 * fenzi * fenmu + 38 * fenzi4) / fenmu4);
}

inline FScalar & sin(const FScalar & fs) noexcept
{
	int32_t rawValue = fs.rawValue;
	if (rawValue >= 804)
	{
		while (rawValue >= pi2)
		{
			rawValue -= pi2;
		}
		bool isNegative = false;
		if (rawValue >= pi)
		{
			rawValue -= pi;
			isNegative = true;
		}
		if (rawValue >= pi_2)
		{
			rawValue = pi - rawValue;
		}
		int32_t theta_2 = rawValue >> 1;
		int32_t sinTheta_2_rawValue = _sin(theta_2);
		int32_t cosTheta_2_rawValue = _cos(theta_2);
		FScalar::retBuffer.rawValue = (int32_t)(((int64_t)sinTheta_2_rawValue * cosTheta_2_rawValue) >> FScalar::fractionBits);
		FScalar::retBuffer.rawValue <<= 1;
		if (isNegative)
		{
			FScalar::retBuffer.rawValue = -FScalar::retBuffer.rawValue;
		}
		return FScalar::retBuffer;
	}
	FScalar::retBuffer.rawValue = _sin(fs.rawValue);
	return FScalar::retBuffer;
}

inline FScalar & cos(const FScalar & fs) noexcept
{
	int32_t rawValue = fs.rawValue;
	if (rawValue >= 804)
	{
		while (rawValue >= pi2)
		{
			rawValue -= pi2;
		}
		bool isNegative = false;
		if (rawValue >= pi)
		{
			rawValue = pi2 - rawValue;
		}
		if (rawValue >= pi_2)
		{
			rawValue = pi - rawValue;
			isNegative = true;
		}
		int32_t theta_2 = rawValue >> 1;
		int32_t cosTheta_2_rawValue = _cos(theta_2);
		int32_t sinTheta_2_rawValue = _sin(theta_2);
		cosTheta_2_rawValue = (int32_t)(((int64_t)cosTheta_2_rawValue * cosTheta_2_rawValue) >> FScalar::fractionBits);
		sinTheta_2_rawValue = (int32_t)(((int64_t)sinTheta_2_rawValue * sinTheta_2_rawValue) >> FScalar::fractionBits);
		FScalar::retBuffer.rawValue = cosTheta_2_rawValue - sinTheta_2_rawValue;
		if (isNegative)
		{
			FScalar::retBuffer.rawValue = -FScalar::retBuffer.rawValue;
		}
		return FScalar::retBuffer;
	}
	FScalar::retBuffer.rawValue = _cos(fs.rawValue);
	return FScalar::retBuffer;
}

const int32_t atan1 = 804;

// The value range of the parameter is[-1.0f, 1.0f]:
inline FScalar & asin(const FScalar & fs) noexcept
{
	int32_t x = fs.rawValue;
	if (x == FScalar::fractionRate)
	{
		FScalar::retBuffer.rawValue = pi_2;
		return FScalar::retBuffer;
	}
	else if (x == -FScalar::fractionRate)
	{
		FScalar::retBuffer.rawValue = -pi_2;
		return FScalar::retBuffer;
	}
	int64_t x2 = (int64_t)x * x >> FScalar::fractionBits;
	int32_t rawValue = (int32_t)((1i64 << FScalar::fractionBits) - x2);
	int32_t fenmu = 0;
	if (rawValue == 0)
	{
		fenmu = 0;
	}
	else
	{
		int32_t n = _bsr_32(rawValue) + 1;
		int64_t x, x2, x4;
		x = (((int64_t)rawValue << FScalar::fractionBits) / (1i64 << n));
		x2 = (int64_t)x * x >> FScalar::fractionBits;
		x4 = x2 * x2 >> FScalar::fractionBits;
		int32_t extra = n - FScalar::fractionBits;
		int32_t sqrt2 = FScalar::fractionRate;
		int64_t result = 234 + ((1331 * x - 932 * x2 + ((513 * x2) >> FScalar::fractionBits) * x - 125 * x4) >> FScalar::fractionBits);
		if (n % 2 != 0)
		{
			sqrt2 = sqrt_2;
		}
		if (extra >= 0)
		{
			extra = (1i64 << (extra >> 1)) * sqrt2;
			fenmu = (int32_t)(extra * result >> FScalar::fractionBits);
		}
		else
		{
			extra = (1i64 << (-extra >> 1)) * sqrt2;
			fenmu = (int32_t)((result << FScalar::fractionBits) / extra);
		}
	}
	x = (int32_t)((int64_t)x << FScalar::fractionBits) / fenmu;
	bool isNegative = x < 0;
	if (isNegative)
	{
		x = -x;
	}
	bool xbelow1 = x < FScalar::fractionRate;
	if (!xbelow1)
	{
		x = ((int64_t)(x - FScalar::fractionRate) << FScalar::fractionBits) / (x + FScalar::fractionRate);
	}
	x2 = (int64_t)x * x >> FScalar::fractionBits;
	int64_t x4 = x2 * x2 >> FScalar::fractionBits;
	FScalar::retBuffer.rawValue = -1 + (int32_t)((1024 * x - x2 - (376 * x2 >> FScalar::fractionBits) * x + 155 * x4) >> FScalar::fractionBits);
	if (!xbelow1)
	{
		FScalar::retBuffer.rawValue += atan1;
	}
	if (isNegative)
	{
		FScalar::retBuffer.rawValue = -FScalar::retBuffer.rawValue;
	}
	return FScalar::retBuffer;
}

// The value range of the parameter is[-1.0f, 1.0f]:
inline FScalar & acos(const FScalar & fs) noexcept
{
	int32_t x = fs.rawValue;
	bool isNegative = x < 0;
	if (x == 0)
	{
		FScalar::retBuffer.rawValue = pi_2;
		return FScalar::retBuffer;
	}
	int64_t x2 = (int64_t)x * x >> FScalar::fractionBits;
	//
	int32_t rawValue = (int32_t)((1i64 << FScalar::fractionBits) - x2);
	int32_t fenzi = 0;
	if (rawValue == 0)
	{
		fenzi = 0;
	}
	else
	{
		int32_t n = _bsr_32(rawValue) + 1;
		int64_t x, x2, x4;
		x = (((int64_t)rawValue << FScalar::fractionBits) / (1i64 << n));
		x2 = (int64_t)x * x >> FScalar::fractionBits;
		x4 = x2 * x2 >> FScalar::fractionBits;
		int32_t extra = n - FScalar::fractionBits;
		int32_t sqrt2 = FScalar::fractionRate;
		int64_t result = 234 + ((1331 * x - 932 * x2 + ((513 * x2) >> FScalar::fractionBits) * x - 125 * x4) >> FScalar::fractionBits);
		if (n % 2 != 0)
		{
			sqrt2 = sqrt_2;
		}
		if (extra >= 0)
		{
			extra = (1i64 << (extra >> 1)) * sqrt2;
			fenzi = (int32_t)(extra * result >> FScalar::fractionBits);
		}
		else
		{
			extra = (1i64 << (-extra >> 1)) * sqrt2;
			fenzi = (int32_t)((result << FScalar::fractionBits) / extra);
		}
	}
	if (isNegative)
	{
		x = (int32_t)((int64_t)fenzi << FScalar::fractionBits) / (-x);
	}
	else
	{
		x = (int32_t)((int64_t)fenzi << FScalar::fractionBits) / x;
	}
	bool xbelow1 = x < FScalar::fractionRate;
	if (!xbelow1)
	{
		x = ((int64_t)(x - FScalar::fractionRate) << FScalar::fractionBits) / (x + FScalar::fractionRate);
	}
	x2 = (int64_t)x * x >> FScalar::fractionBits;
	int64_t x4 = x2 * x2 >> FScalar::fractionBits;
	FScalar::retBuffer.rawValue = -1 + (int32_t)((1024 * x - x2 - (376 * x2 >> FScalar::fractionBits) * x + 155 * x4) >> FScalar::fractionBits);
	if (!xbelow1)
	{
		FScalar::retBuffer.rawValue += atan1;
	}
	if (isNegative)
	{
		FScalar::retBuffer.rawValue = pi - FScalar::retBuffer.rawValue;
	}
	return FScalar::retBuffer;
}

// The value range of the parameter is[-2097150.9f, 2097150.9f]:
// Too large parameter will cause the int64 - based calculation process overflow and the correct result will not be obtained.
inline FScalar & atan(const FScalar & fs) noexcept
{
	int32_t x = fs.rawValue;
	bool isNegative = x < 0;
	if (isNegative)
	{
		x = -x;
	}
	bool xbelow1 = x < FScalar::fractionRate;
	if (!xbelow1)
	{
		x = ((int64_t)(x - FScalar::fractionRate) << FScalar::fractionBits) / (x + FScalar::fractionRate);
	}
	int64_t x2 = (int64_t)x * x >> FScalar::fractionBits;
	int64_t x4 = x2 * x2 >> FScalar::fractionBits;
	FScalar::retBuffer.rawValue = -1 + (int32_t)((1024 * x - x2 - (376 * x2 >> FScalar::fractionBits) * x + 155 * x4) >> FScalar::fractionBits);
	if (!xbelow1)
	{
		FScalar::retBuffer.rawValue += atan1;
	}
	if (isNegative)
	{
		FScalar::retBuffer.rawValue = -FScalar::retBuffer.rawValue;
	}
	return FScalar::retBuffer;
}

// The value range of the parameter is(-1.5708f, 1.5708f):
inline FScalar & acot(const FScalar & fs) noexcept
{
	if (fs.rawValue == 0)
	{
		FScalar::retBuffer.rawValue = pi_2;
		return FScalar::retBuffer;
	}
	int32_t rawValue = fs.rawValue;
	bool isNegative = rawValue < 0;
	if (isNegative)
	{
		rawValue = -rawValue;
	}
	int32_t x = (int32_t)(((int64_t)FScalar::fractionRate << FScalar::fractionBits) / rawValue);
	bool xbelow1 = x < FScalar::fractionRate;
	if (!xbelow1)
	{
		x = ((int64_t)(x - FScalar::fractionRate) << FScalar::fractionBits) / (x + FScalar::fractionRate);
	}
	int64_t x2 = (int64_t)x * x >> FScalar::fractionBits;
	int64_t x4 = x2 * x2 >> FScalar::fractionBits;
	FScalar::retBuffer.rawValue = -1 + (int32_t)((1024 * x - x2 - (376 * x2 >> FScalar::fractionBits) * x + 155 * x4) >> FScalar::fractionBits);
	if (!xbelow1)
	{
		FScalar::retBuffer.rawValue += atan1;
	}
	if (isNegative)
	{
		FScalar::retBuffer.rawValue = -FScalar::retBuffer.rawValue;
	}
	return FScalar::retBuffer;
}
