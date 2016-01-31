#pragma once 

namespace MathUtils
{
	//type specifics
	template<typename T> inline const T GetMin();
	template<typename T> inline const T GetMax();
	template<typename T> inline const T GetEpsilon();
	
	//instances
	template<> inline const f32     GetMin<f32>()  { return FLT_MIN; }
	template<> inline const f64     GetMin<f64>()  { return DBL_MIN; }
	template<> inline const int32   GetMin<int32>(){ return INT_MIN; }
	template<> inline const uint32 GetMin<uint32>(){ return 0u; }

	template<> inline const f32     GetMax<f32>()   { return FLT_MAX; }
	template<> inline const f64     GetMax<f64>()   { return DBL_MAX; }
	template<> inline const int32   GetMax<int32>() { return INT_MAX; }
	template<> inline const uint32  GetMax<uint32>(){ return UINT_MAX; }

	template<> inline const f32     GetEpsilon<f32>()   { return FLT_EPSILON; }
	template<> inline const f64     GetEpsilon<f64>()   { return DBL_EPSILON; }
	template<> inline const int32   GetEpsilon<int32>() { return 1; }
	template<> inline const uint32  GetEpsilon<uint32>(){ return 1u; }

	//Specific functions
	namespace 
	{
		inline const f32 SqrtFast( const f32 number ){	long i;	float x, y;	const float f=1.5f; x=number*0.5f; y=number; i=*(long*)&y; i=0x5f3759df-(i>>1); y=*(float*)&i; y=y*(f-(x*y*y)); return number*y; }
	}

	//Basic
	template<typename T> inline const T CosTpl(const T input){ return static_cast<T>(cosf(static_cast<f32>(input)));}
	template<typename T> inline const T SinTpl(const T input){ return static_cast<T>(sinf(static_cast<f32>(input)));}
	template<typename T> inline void SinCosTpl(const T input, T* const pSin, T* const pCos){ *pSin = SinTpl<T>(input);	*pCos = CosTpl<T>(input); }
	template<typename T> inline const T AcosTpl(const T input){ return static_cast<T>(acosf(static_cast<f32>(input)));}
	template<typename T> inline const T AsinTpl(const T input){ return static_cast<T>(asinf(static_cast<f32>(input)));}
	template<typename T> inline const T AtanTpl(const T input){ return static_cast<T>(atanf(static_cast<f32>(input)));}
	template<typename T> inline const T Atan2Tpl(const T first, const T second){ return static_cast<T>(atan2f(static_cast<f32>(first), static_cast<f32>(second)));}
	template<typename T> inline const T TanTpl(const T input){ return static_cast<T>(tanf(static_cast<f32>(input)));}
	template<typename T> inline const T ExpTpl(const T input){ return static_cast<T>(expf(static_cast<f32>(input)));}
	template<typename T> inline const T LogTpl(const T input){ return static_cast<T>(logf(static_cast<f32>(input)));}
	template<typename T> inline const T AbsTpl(const T input){ return static_cast<T>(fabsf(static_cast<f32>(input)));}
	template<typename T> inline const T FloorTpl(const T input){ return static_cast<T>(floorf(static_cast<f32>(input)));}
	template<typename T> inline const T CeilTpl(const T input){ return static_cast<T>(ceilf(static_cast<f32>(input)));}

	template<typename T> inline const T SqrtTpl(const T input){ return static_cast<T>(sqrtf(static_cast<f32>(input)));}
	template<typename T> inline const T SqrtFastTpl(const T input){ return static_cast<T>(SqrtFast(static_cast<f32>(input)));}
	template<typename T> inline const T InvSqrtTpl(const T input){ return static_cast<T>(1.0)/SqrtTpl<T>(input);}
	template<typename T> inline const T InvSqrtFastTpl(const T input){ return static_cast<T>(1.0)/SqrtFastTpl<T>(input);}
	template<typename T> inline const T InvSqrtSafeTpl(const T input){ return static_cast<T>(1.0)/SqrtTpl<T>(input+GetMin<T>());}
	
	//Specializations for f64
	template<> inline const f64 ExpTpl<f64>(const f64 input){ return exp(input); }
	template<> inline const f64 LogTpl<f64>(const f64 input){ return log(input); }
	template<> inline const f64 AbsTpl<f64>(const f64 input){ return fabs(input); }
	template<> inline const f64 FloorTpl<f64>(const f64 input){ return fabs(input); }
	template<> inline const f64 CeilTpl<f64>(const f64 input){ return fabs(input); }
	template<> inline const f64 SqrtTpl<f64>(const f64 input){ return sqrt(input); }

	//Specializations for int32
	template<> inline const int32 AbsTpl<int32>(const int32 input){ const int32 mask=input>>31; return input+mask^mask;  }
	template<> inline const int32 FloorTpl<int32>(const int32 input){ return input; }
	template<> inline const int32 CeilTpl<int32>(const int32 input){ return input; }

	//Specializations for uint32 
	template<> inline const uint32 AbsTpl<uint32>(const uint32 input){ return input; }
	template<> inline const uint32 FloorTpl<uint32>(const uint32 input){ return input; }
	template<> inline const uint32 CeilTpl<uint32>(const uint32 input){ return input; }

	//General 
	template<typename T> const bool CmpTpl(const T a, const T b ) { return AbsTpl<T>(a-b) <= GetEpsilon<T>(); }
	template<typename T> inline const T ClampTpl(const T input, const T a, const T b){ return (input<a)? a : ((input>b)? b : input ); }
	template<typename T> inline const T MaxTpl(const T a, const T b){ return (a>b)? a : b; }
	template<typename T> inline const T MinTpl(const T a, const T b){ return (a>b)? b : a; }
	template<typename T> inline const T SqrTpl(const T input) { return input*input; }
	//Angular 
	template<typename T> inline const T RangePI(const T input){ return (input < static_cast<T>(-gfPI))? input+static_cast<T>(gfPI2) : ((input>static_cast<T>(gfPI))? input-static_cast<T>(gfPI2) : input ); }
	template<typename T> inline const bool IsInRangePI(const T input) { return (input > -gfPI) && ( input < gfPI); }
}