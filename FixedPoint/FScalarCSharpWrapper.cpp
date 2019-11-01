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

	DllExport FScalar* Internal_Pow(FScalar* fs)
	{
		return &pow(*fs);
	}

	DllExport FScalar* Internal_Log(FScalar* fs)
	{
		return &log(*fs);
	}

	DllExport FScalar* Internal_Exp(FScalar* fs)
	{
		return &exp(*fs);
	}

	DllExport FScalar* Internal_Sin(FScalar* fs)
	{
		return &sin(*fs);
	}

	DllExport FScalar* Internal_ASin(FScalar* fs)
	{
		return &asin(*fs);
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
