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

const int calculateTimes = 1000000;
float randFloat[calculateTimes];
FScalar randScalar[calculateTimes];

// Since the Release version does a lot of optimizations on the test code itself and
// can't get fair test data, you can only use Debug to run the following test code.
void Benchmark()
{
	for (int i = 0; i < calculateTimes; i++)
	{
		randFloat[i] = ((rand() % 1000) + 1) * 0.001f;
		randScalar[i] = randFloat[i];
	}
	cout << "Start compare for + operator by calculate " << calculateTimes << " times." << endl;
	DWORD now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		randScalar[i] + randScalar[i];
	}
	DWORD elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		Add(randFloat[i], randFloat[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for - operator by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		randScalar[i] - randScalar[i];
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		Minus(randFloat[i], randFloat[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for * operator by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		randScalar[i] * randScalar[i];
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		Multiply(randFloat[i], randFloat[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for / operator by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		randScalar[i] / randScalar[i];
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		Divide(randFloat[i], randFloat[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for sqrt function by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		sqrt(randScalar[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		sqrt(randFloat[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for pow function by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		pow(randScalar[i], randScalar[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		pow(randFloat[i], randFloat[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for log2 function by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		log2(randScalar[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		log2(randFloat[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for log function by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		log(randScalar[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		log(randFloat[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for log10 function by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		log10(randScalar[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		log10(randFloat[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for exp function by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		exp(randScalar[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		exp(randFloat[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for sin function by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		sin(randScalar[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		sin(randFloat[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for cos function by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		cos(randScalar[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		cos(randFloat[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for asin function by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		asin(randScalar[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		asin(randFloat[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for acos function by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		acos(randScalar[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		acos(randFloat[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for atan function by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		atan(randScalar[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		atan(randFloat[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
	cout << "Start compare for acot function by calculate " << calculateTimes << " times." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		acot(randScalar[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "Fixed point use " << elapsed << "ms." << endl;
	now = GetTickCount();
	for (int i = 0; i < calculateTimes; i++)
	{
		atan(1.0 / randFloat[i]);
	}
	elapsed = GetTickCount() - now;
	cout << "General float use " << elapsed << "ms." << endl;
}

int main()
{
	Benchmark();
	int a;
	cin >> a;
}
