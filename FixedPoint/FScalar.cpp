#include "stdafx.h"
#include <math.h>
#include "FScalar.h"

FScalar FScalar::retBuffer(0);

//const float e = 2.718281828459045f;
const int32_t e = 2783;

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

void calculateParameters(int32_t rawValue, bool nMustBeEven, int32_t& n, int32_t& fenzi, int32_t& fenmu, int64_t& fenzi2, int64_t& fenzi4, int64_t& fenmu2, int64_t& fenmu4)
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
	fenzi = rawValue;
	fenmu = 1 << n;
	while (fenzi > 4096)
	{
		fenzi >>= 1;
		fenmu >>= 1;
	}
	fenzi2 = (int64_t)fenzi * fenzi;
	fenzi4 = fenzi2 * fenzi2;
	fenmu2 = (int64_t)fenmu * fenmu;
	fenmu4 = fenmu2 * fenmu2;
}

// 参数的值域为[0, 1048575.9]：
// 参数太大了基于int64的计算过程会发生溢出，无法得到正确结果。
FScalar & sqrt(const FScalar & fs)
{
	int32_t n, fenzi, fenmu;
	int64_t fenzi2, fenzi4, fenmu2, fenmu4;
	calculateParameters(fs.rawValue, true, n, fenzi, fenmu, fenzi2, fenzi4, fenmu2, fenmu4);
	FScalar::retBuffer.rawValue = (int32_t)((1i64 << ((n - FScalar::fractionBits) >> 1)) * (234 + (1331 * fenzi * fenmu2 * fenmu - 932 * fenzi2 * fenmu2 + 513 * fenzi2 * fenzi * fenmu - 125 * fenzi4) / fenmu4));
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

// 参数的值域为(0, 1048575]：
// 0的计算结果是负无穷，没有意义
// 参数太大了基于int64的计算过程会发生溢出，无法得到正确结果，并且也已经非常接近22bit整数位的32bit定点数能够表达的最大值了。
FScalar & log2(const FScalar & fs)
{
	int32_t n, fenzi, fenmu;
	int64_t fenzi2, fenzi4, fenmu2, fenmu4;
	calculateParameters(fs.rawValue, false, n, fenzi, fenmu, fenzi2, fenzi4, fenmu2, fenmu4);
	FScalar::retBuffer.rawValue = (int32_t)(((n - FScalar::fractionBits) << FScalar::fractionBits) + (-6163 * fenmu4 + 28610 * fenzi * fenmu2 * fenmu - 60718 * fenzi2 * fenmu2 + 59463 * fenzi2 * fenzi * fenmu - 21202 * fenzi4) / fenmu4);
	return FScalar::retBuffer;
}

// 参数的值域为(0, 1048575]：
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
	int64_t wholeResult = 1;
	for (int i = 0; i < wholePart && i < 3; i++)
	{
		wholeResult *= e;
	}
	for (int i = 3; i < wholePart; i++)
	{
		wholeResult *= e;
		wholeResult >>= FScalar::fractionBits;
	}
	int32_t fenzi = fs.rawValue - (wholePart << FScalar::fractionBits);
	int32_t fenmu = 1 << FScalar::fractionBits;
	int64_t fenzi2 = fenzi * fenzi;
	int64_t fenzi4 = fenzi2 * fenzi2;
	int64_t fenmu2 = fenmu * fenmu;
	int64_t fenmu4 = fenmu2 * fenmu2;
	int64_t value64 = wholeResult * (1024 + (1023 * fenzi * fenmu2 * fenmu + 520 * fenzi2 * fenmu2 + 146 * fenzi2 * fenzi * fenmu + 69 * fenzi4) / fenmu4);
	for (int i = 0; i < wholePart && i < 3; i++)
	{
		value64 >>= FScalar::fractionBits;
	}
	FScalar::retBuffer.rawValue = (int32_t)value64;
	if (isNegative)
	{
		FScalar::retBuffer = FScalar(1) / FScalar::retBuffer;
	}
	return FScalar::retBuffer;
}

FScalar & _sin(const FScalar & fs)
{
	int32_t fenzi = fs.rawValue;
	int32_t fenmu = 1 << FScalar::fractionBits;
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
	int32_t fenmu = 1 << FScalar::fractionBits;
	int64_t fenzi2 = fenzi * fenzi;
	int64_t fenzi4 = fenzi2 * fenzi2;
	int64_t fenmu2 = fenmu * fenmu;
	int64_t fenmu4 = fenmu2 * fenmu2;
	FScalar::retBuffer.rawValue = (int32_t)(1023 + (- 514 * fenzi2 * fenmu2 + 3 * fenzi2 * fenzi * fenmu + 38 * fenzi4) / fenmu4);
	return FScalar::retBuffer;
}

FScalar & sin(const FScalar & fs)
{
	if (fs.rawValue >= 804)
	{
		FScalar theta_2(fs.rawValue >> 1);
		int32_t sinTheta_2_rawValue = sin(theta_2).rawValue;
		int32_t cosTheta_2_rawValue = cos(theta_2).rawValue;
		FScalar::retBuffer.rawValue = ((int64_t)sinTheta_2_rawValue * cosTheta_2_rawValue) >> FScalar::fractionBits;
		FScalar::retBuffer.rawValue <<= 1;
		return FScalar::retBuffer;
	}
	return _sin(fs);
}

FScalar & cos(const FScalar & fs)
{
	if (fs.rawValue >= 804)
	{
		FScalar theta_2(fs.rawValue >> 1);
		int64_t cosTheta_2_rawValue = cos(theta_2).rawValue;
		int64_t sinTheta_2_rawValue = sin(theta_2).rawValue;
		cosTheta_2_rawValue *= cosTheta_2_rawValue;
		cosTheta_2_rawValue >>= FScalar::fractionBits;
		sinTheta_2_rawValue *= sinTheta_2_rawValue;
		sinTheta_2_rawValue >>= FScalar::fractionBits;
		FScalar::retBuffer.rawValue = cosTheta_2_rawValue - sinTheta_2_rawValue;
		return FScalar::retBuffer;
	}
	return _cos(fs);
}

FScalar & asin(const FScalar & fs)
{
	return FScalar::retBuffer;
}
