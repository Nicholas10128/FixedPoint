#include "pch.h"
#include <iostream>
#include <windows.h>
#include <math.h>
#include "../FixedPoint/FScalar.h"

using namespace std;

float Add(const float f1, const float f2)
{
	return f1 + f2;
}

float Minus(const float f1, const float f2)
{
	return f1 - f2;
}

float Multiply(const float f1, const float f2)
{
	return f1 * f2;
}

float Divide(const float f1, const float f2)
{
	return f1 / f2;
}

// Since the Release version does a lot of optimizations on the test code itself and
// can't get fair test data, you can only use Debug to run the following test code.
void PerformanceCheck()
{
	const int calculateTimes = 10000000;
	float f1 = 12.5f, f2 = 0.25f;
	FScalar fs1(f1), fs2(f2);
	cout << "Start compare for + operator by calculate " << calculateTimes << " times." << endl;
	DWORD now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		fs1 + fs2;
	}
	DWORD elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		Add(f1, f2);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for - operator by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		fs1 - fs2;
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		Minus(f1, f2);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for * operator by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		fs1 * fs2;
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		Multiply(f1, f2);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for / operator by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		fs1 / fs2;
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		Divide(f1, f2);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	//
	cout << "Start compare for sqrt function by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		sqrt(fs1);
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		sqrt(f1);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for pow function by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		pow(fs1, fs2);
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		pow(f1, f2);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for log2 function by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		log2(fs1);
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		log2(f1);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for log function by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		log(fs1, fs2);
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		log(f2) / log(f1);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for exp function by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		exp(fs1);
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		exp(f1);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for sin function by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		sin(fs1);
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		sin(f1);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for cos function by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		cos(fs1);
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		cos(f1);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
}

int main()
{
	//PerformanceCheck();
	cout << atan(FScalar(0.5f)) << endl;
	cout << atan(FScalar(1.0f)) << endl;
	cout << atan(FScalar(2.0f)) << endl;
	cout << atan(FScalar(4.0f)) << endl;
	int a;
	cin >> a;
}
