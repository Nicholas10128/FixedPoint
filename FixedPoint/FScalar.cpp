#include "stdafx.h"
#include <math.h>
#include "FScalar.h"

FScalar FScalar::retBuffer(0);

//const float e = 2.718281828459045f;
const int32_t e = 2783;
const int32_t pi = 3217;
const int32_t pi_2 = pi >> 1;
const int32_t pi2 = pi << 1;

FScalar::FScalar(float floatValue)
{
	rawValue = (int32_t)(floatValue * fractionRate);
}

FScalar::FScalar(int32_t scalarValue)
{
	rawValue = scalarValue;
}

inline FScalar::operator int()
{
	return rawValue;
}

inline FScalar::operator float()
{
	return rawValue * fractionRateReciprocal;
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

void calculateParameters(int32_t rawValue, bool nMustBeEven, int32_t& n, int64_t& x, int64_t& x2, int64_t& x4)
{
	n = 31;
	int32_t mask = 0x40000000;
	for (; n > 0 && (rawValue & mask) == 0; n--, mask >>= 1)
	{
	}
	if (nMustBeEven && n % 2 != 0)
	{
		n++;
	}
	x = (((int64_t)rawValue << FScalar::fractionBits) / (1i64 << n));
	x2 = (int64_t)x * x >> FScalar::fractionBits;
	x4 = x2 * x2 >> FScalar::fractionBits;
}

// 参数的值域为[0, 2097151.937]：
// 参数太大了基于int64的计算过程会发生溢出，无法得到正确结果。
FScalar & sqrt(const FScalar & fs)
{
	int32_t n;
	int64_t x, x2, x4;
	calculateParameters(fs.rawValue, true, n, x, x2, x4);
	FScalar::retBuffer.rawValue = (int32_t)((1i64 << ((n - FScalar::fractionBits) >> 1)) * (234 + ((1331 * x - 932 * x2 + ((513 * x2) >> FScalar::fractionBits) * x - 125 * x4) >> FScalar::fractionBits)));
	return FScalar::retBuffer;
}

// 对于22bit整数位的32bit定点数，pow的计算过程中精度丢失严重，几乎不可用
FScalar & pow(const FScalar & base, const FScalar & exponential)
{
	FScalar logBase(log2(base).rawValue), logE(1.4427f);
	FScalar::retBuffer = exp(exponential * logBase / logE);
	return FScalar::retBuffer;
}

//extern "C" int64_t _Div128_64(int64_t a_low, int64_t a_high, int64_t b, int64_t* ret);

// 参数的值域为(0, 2097151.937f]：
// 0的计算结果是负无穷，没有意义
// 参数太大了基于int64的计算过程会发生溢出，无法得到正确结果，并且也已经非常接近22bit整数位的32bit定点数能够表达的最大值了。
FScalar & log2(const FScalar & fs)
{
	int32_t n;
	int64_t x, x2, x4;
	calculateParameters(fs.rawValue, false, n, x, x2, x4);
	FScalar::retBuffer.rawValue = (int32_t)(((n - FScalar::fractionBits) << FScalar::fractionBits) - 6163 + ((28610 * x - 60718 * x2 + ((59463 * x2) >> FScalar::fractionBits) * x - 21202 * x4) >> FScalar::fractionBits));
	return FScalar::retBuffer;
}

// 参数的值域为(0, 2097151.937f]：
// 0的计算结果是负无穷，没有意义
// 参数太大了基于int64的计算过程会发生溢出，无法得到正确结果，并且也已经非常接近22bit整数位的32bit定点数能够表达的最大值了。
FScalar & log(const FScalar & base, const FScalar & fs)
{
	int32_t fsValue = log2(fs).rawValue;
	int32_t baseValue = log2(base).rawValue;
	FScalar::retBuffer.rawValue = ((int64_t)fsValue << FScalar::fractionBits) / baseValue;
	return FScalar::retBuffer;
}

// 参数的值域为(-2.0, 14.5]：
// 参数小于0的时候误差比较大，因为22bit整数位的32bit定位数无法表达那么高的小数精度。
// 参数太大了基于int64的计算过程会发生溢出，无法得到正确结果，并且也已经非常接近22bit整数位的32bit定点数能够表达的最大值了。
FScalar & exp(const FScalar & fs)
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

FScalar & _sin(const FScalar & fs)
{
	int32_t fenzi = fs.rawValue;
	int32_t fenmu = FScalar::fractionRate;
	int64_t fenzi2 = fenzi * fenzi;
	int64_t fenzi4 = fenzi2 * fenzi2;
	int64_t fenmu2 = fenmu * fenmu;
	int64_t fenmu4 = fenmu2 * fenmu2;
	FScalar::retBuffer.rawValue = (int32_t)((1023 * fenzi * fenmu2 * fenmu + fenzi2 * fenmu2 - 179 * fenzi2 * fenzi * fenmu + 14 * fenzi4) / fenmu4);
	return FScalar::retBuffer;
}

FScalar & _cos(const FScalar & fs)
{
	int32_t fenzi = fs.rawValue;
	int32_t fenmu = FScalar::fractionRate;
	int64_t fenzi2 = fenzi * fenzi;
	int64_t fenzi4 = fenzi2 * fenzi2;
	int64_t fenmu2 = fenmu * fenmu;
	int64_t fenmu4 = fenmu2 * fenmu2;
	FScalar::retBuffer.rawValue = (int32_t)(1023 + (- 514 * fenzi2 * fenmu2 + 3 * fenzi2 * fenzi * fenmu + 38 * fenzi4) / fenmu4);
	return FScalar::retBuffer;
}

FScalar & sin(const FScalar & fs)
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
		else if (rawValue >= pi_2)
		{
			rawValue = pi - rawValue;
		}
		FScalar theta_2(rawValue >> 1);
		int32_t sinTheta_2_rawValue = sin(theta_2).rawValue;
		int32_t cosTheta_2_rawValue = cos(theta_2).rawValue;
		FScalar::retBuffer.rawValue = ((int64_t)sinTheta_2_rawValue * cosTheta_2_rawValue) >> FScalar::fractionBits;
		FScalar::retBuffer.rawValue <<= 1;
		if (isNegative)
		{
			FScalar::retBuffer.rawValue = -FScalar::retBuffer.rawValue;
		}
		return FScalar::retBuffer;
	}
	return _sin(fs);
}

FScalar & cos(const FScalar & fs)
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
		else if (rawValue >= pi_2)
		{
			rawValue = pi - rawValue;
			isNegative = true;
		}
		FScalar theta_2(rawValue >> 1);
		int64_t cosTheta_2_rawValue = cos(theta_2).rawValue;
		int64_t sinTheta_2_rawValue = sin(theta_2).rawValue;
		cosTheta_2_rawValue *= cosTheta_2_rawValue;
		cosTheta_2_rawValue >>= FScalar::fractionBits;
		sinTheta_2_rawValue *= sinTheta_2_rawValue;
		sinTheta_2_rawValue >>= FScalar::fractionBits;
		FScalar::retBuffer.rawValue = (int32_t)(cosTheta_2_rawValue - sinTheta_2_rawValue);
		if (isNegative)
		{
			FScalar::retBuffer.rawValue = -FScalar::retBuffer.rawValue;
		}
		return FScalar::retBuffer;
	}
	return _cos(fs);
}

const int32_t atan1 = 804;

FScalar & asin(const FScalar & fs)
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
	int32_t fenmu = sqrt(FScalar((int32_t)((1i64 << FScalar::fractionBits) - x2))).rawValue;
	FScalar::retBuffer = atan(FScalar((int32_t)((int64_t)x << FScalar::fractionBits) / fenmu));
	return FScalar::retBuffer;
}

// 算出来不对的
FScalar & acos(const FScalar & fs)
{
	int32_t x = fs.rawValue;
	if (x == 0)
	{
		FScalar::retBuffer.rawValue = pi_2;
		return FScalar::retBuffer;
	}
	int64_t x2 = (int64_t)x * x >> FScalar::fractionBits;
	int32_t fenzi = sqrt(FScalar((int32_t)((1i64 << FScalar::fractionBits) - x2))).rawValue;
	if (x < 0)
	{
		FScalar::retBuffer.rawValue = pi - atan(FScalar((int32_t)((int64_t)fenzi << FScalar::fractionBits) / (-x))).rawValue;
	}
	else
	{
		FScalar::retBuffer.rawValue = atan(FScalar((int32_t)((int64_t)fenzi << FScalar::fractionBits) / x)).rawValue;
	}
	return FScalar::retBuffer;
}

// 参数的值域为(0.001, 2097150.9f]：
// 参数太大了基于int64的计算过程会发生溢出，无法得到正确结果。
FScalar & atan(const FScalar & fs)
{
	bool xbelow1 = fs.rawValue < FScalar::fractionRate;
	int32_t x = fs.rawValue;
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
	return FScalar::retBuffer;
}

FScalar & acot(const FScalar & fs)
{
	return FScalar::retBuffer;
}
