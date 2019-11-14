using System;
using System.Runtime.InteropServices;
using UnityEngine;

public class FixedPointTest : MonoBehaviour
{
    [DllImport("FixedPoint")]
    static extern IntPtr Internal_CreateFScalar(float floatValue);
    [DllImport("FixedPoint")]
    static extern void Internal_DestroyFScalar(IntPtr fs);
    [DllImport("FixedPoint")]
    static extern IntPtr Internal_Add(IntPtr fs1, IntPtr fs2);
    [DllImport("FixedPoint")]
    static extern IntPtr Internal_Minus(IntPtr fs1, IntPtr fs2);
    [DllImport("FixedPoint")]
    static extern IntPtr Internal_Multiply(IntPtr fs1, IntPtr fs2);
    [DllImport("FixedPoint")]
    static extern IntPtr Internal_Divide(IntPtr fs1, IntPtr fs2);
    [DllImport("FixedPoint")]
    static extern IntPtr Internal_Sqrt(IntPtr fs);
    [DllImport("FixedPoint")]
    static extern IntPtr Internal_Pow(IntPtr fs1, IntPtr fs2);
    [DllImport("FixedPoint")]
    static extern IntPtr Internal_Log2(IntPtr fs);
    [DllImport("FixedPoint")]
    static extern IntPtr Internal_Log(IntPtr fs);
    [DllImport("FixedPoint")]
    static extern IntPtr Internal_Log10(IntPtr fs);
    [DllImport("FixedPoint")]
    static extern IntPtr Internal_Exp(IntPtr fs);
    [DllImport("FixedPoint")]
    static extern IntPtr Internal_Sin(IntPtr fs);
    [DllImport("FixedPoint")]
    static extern IntPtr Internal_Cos(IntPtr fs);
    [DllImport("FixedPoint")]
    static extern IntPtr Internal_ASin(IntPtr fs);
    [DllImport("FixedPoint")]
    static extern IntPtr Internal_ACos(IntPtr fs);
    [DllImport("FixedPoint")]
    static extern IntPtr Internal_ATan(IntPtr fs);
    [DllImport("FixedPoint")]
    static extern IntPtr Internal_ACot(IntPtr fs);
    [DllImport("FixedPoint")]
    static extern int Internal_GetScalarValue(IntPtr fs);
    [DllImport("FixedPoint")]
    static extern float Internal_GetFloatValue(IntPtr fs);

    void Start()
    {
        IntPtr fs1 = Internal_CreateFScalar(1.5f);
        IntPtr fs2 = Internal_CreateFScalar(0.25f);
        Debug.Log(Internal_GetFloatValue(Internal_Add(fs1, fs2)));
        Debug.Log(Internal_GetFloatValue(Internal_Minus(fs1, fs2)));
        Debug.Log(Internal_GetFloatValue(Internal_Multiply(fs1, fs2)));
        Debug.Log(Internal_GetFloatValue(Internal_Divide(fs1, fs2)));
        Debug.Log(Internal_GetFloatValue(Internal_Sqrt(fs1)));
        Debug.Log(Internal_GetFloatValue(Internal_Pow(fs1, fs2)));
        Debug.Log(Internal_GetFloatValue(Internal_Log2(fs1)));
        Debug.Log(Internal_GetFloatValue(Internal_Log(fs1)));
        Debug.Log(Internal_GetFloatValue(Internal_Log10(fs1)));
        Debug.Log(Internal_GetFloatValue(Internal_Exp(fs1)));
        Debug.Log(Internal_GetFloatValue(Internal_Sin(fs1)));
        Debug.Log(Internal_GetFloatValue(Internal_Cos(fs1)));
        Debug.Log(Internal_GetFloatValue(Internal_ASin(fs1)));
        Debug.Log(Internal_GetFloatValue(Internal_ACos(fs1)));
        Debug.Log(Internal_GetFloatValue(Internal_ATan(fs1)));
        Debug.Log(Internal_GetFloatValue(Internal_ACot(fs1)));
    }
}
