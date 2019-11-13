#include "stdafx.h"
#include "FScalar.h"

// C# wrapper for Unity using.
extern "C"
{
	DllExport FScalar* Internal_CreateFScalar(float floatValue)
	{
		FScalar* obj = new FScalar(floatValue);
		return obj;
	}

	DllExport void Internal_DestroyFScalar(FScalar* obj)
	{
		if (obj != NULL)
		{
			delete obj;
			obj = NULL;
		}
	}

	DllExport FScalar* Internal_Add(FScalar* fs1, FScalar* fs2)
	{
		return &((*fs1) + (*fs2));
	}

	DllExport FScalar* Internal_Minus(FScalar* fs1, FScalar* fs2)
	{
		return &((*fs1) - (*fs2));
	}

	DllExport FScalar* Internal_Multiply(FScalar* fs1, FScalar* fs2)
	{
		return &((*fs1) * (*fs2));
	}

	DllExport FScalar* Internal_Divide(FScalar* fs1, FScalar* fs2)
	{
		return &((*fs1) / (*fs2));
	}

	DllExport FScalar* Internal_Sqrt(FScalar* fs)
	{
		return &sqrt(*fs);
	}

	DllExport FScalar* Internal_Pow(FScalar* base, FScalar* exponential)
	{
		return &pow(*base, *exponential);
	}

	DllExport FScalar* Internal_Log2(FScalar* fs)
	{
		return &log2(*fs);
	}

	DllExport FScalar* Internal_Log(FScalar* base, FScalar* fs)
	{
		return &log(*base, *fs);
	}

	DllExport FScalar* Internal_Exp(FScalar* fs)
	{
		return &exp(*fs);
	}

	DllExport FScalar* Internal_Sin(FScalar* fs)
	{
		return &sin(*fs);
	}

	DllExport FScalar* Internal_Cos(FScalar* fs)
	{
		return &cos(*fs);
	}

	DllExport FScalar* Internal_ASin(FScalar* fs)
	{
		return &asin(*fs);
	}

	DllExport FScalar* Internal_ACos(FScalar* fs)
	{
		return &acos(*fs);
	}

	DllExport FScalar* Internal_ATan(FScalar* fs)
	{
		return &atan(*fs);
	}

	DllExport FScalar* Internal_ACot(FScalar* fs)
	{
		return &acot(*fs);
	}

	DllExport int Internal_GetScalarValue(FScalar* fs)
	{
		return *fs;
	}

	DllExport float Internal_GetFloatValue(FScalar* fs)
	{
		return *fs;
	}
}
