#include "pch.h"
#include <iostream>
#include <windows.h>
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
}

int main()
{
	//PerformanceCheck();
	cout << sqrt(FScalar(1.0f)) << endl;
	int a;
	cin >> a;
}
