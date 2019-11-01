#pragma once

#ifdef _EXPORTING
#define DllExport    __declspec(dllexport)
#else
#define DllExport    __declspec(dllimport)
#endif

#include "FScalar.h"
