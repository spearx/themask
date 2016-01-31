#pragma once

namespace MathUtils
{
	template<typename T> struct Vector2Tpl;
	template<typename T> struct Vector2Constants
	{
		static Vector2Tpl<T> zero;
		static Vector2Tpl<T> oneX;
		static Vector2Tpl<T> oneY;
		static Vector2Tpl<T> oneZ;
		static Vector2Tpl<T> one;
	};

	template<typename T> struct Vector2Tpl 
	{
	public:
		typedef T value_type;
	
		inline Vector2Tpl()	{}
		inline Vector2Tpl(ETypeZero) : x(0),y(0) {}
		inline Vector2Tpl(ETypeMin){x=y=-GetMax<T>();}
		inline Vector2Tpl(ETypeMax){x=y=GetMax<T>();}
		inline Vector2Tpl(const T input):x(input),y(input){}
		inline Vector2Tpl(const T vx,const T vy):x(vx),y(vy){}
		inline Vector2Tpl& Set(const T nx,const T ny) { x=T(nx); y=T(ny); return *this; }

		template<typename T1> inline Vector2Tpl(const Vector2Tpl<T1>& input) { x=T(input.x); y=T(input.y); }
		template<typename T1> inline explicit Vector2Tpl(const Vector3Tpl<T1>& input) { x=T(input.x); y=T(input.y); }
		template<typename T1> inline explicit Vector2Tpl(const T1* pinput) { x=T(pinput[0]); y=T(pinput[1]); }

		explicit inline Vector2Tpl(const Vector3Tpl<T>& input) : x(static_cast<T>(input.x)), y(static_cast<T>(input.y)) { ASSERT(IsValid()); }

		inline const Vector2Tpl& operator= (const Vector2Tpl& input) { x=input.x; y=input.y; return *this; }
		inline bool operator!() const { return x==0 && y==0; }

		// The default Normalize function is in fact "safe". 0 vectors remain unchanged.
		const Vector2Tpl& Normalize() 
		{
			const T fInvLen = InvSqrtSafeTpl(x*x+y*y);
			x *= fInvLen; y *= fInvLen; 
			return *this; 
		}

		inline Vector2Tpl GetNormalized() const { return *this * InvSqrtSafeTpl(x*x+y*y); }
	
		Vector2Tpl GetNormalizedSafe( const struct Vector2Tpl<T>& safeValue = Vector2Constants<T>::oneX ) const 
		{ 
			const T len2 = x*x+y*y;	
			if (len2 > 0.0f)
			{
				const T fInvLen = InvSqrtTpl(len2);
				return *this * fInvLen;
			}
			else
			{
				return safeValue;
			}
		}

		// Normalize if non-0, otherwise set to specified "safe" value.
		inline const Vector2Tpl& NormalizeSafe( const struct Vector2Tpl<T>& safeValue = Vector2Constants<T>::zero ) { *this = GetNormalizedSafe(safeValue); return *this; }

		inline const T GetLengthSquared() const { return x*x+y*y; }
		inline const T GetLength() const { return SqrtTpl(GetLengthSquared()); }
		inline const T Area() const { return x*y; }

		inline const T& operator[](const uint32 idx) { return *(reinterpret_cast<T*>(&x+idx)); }
		inline const T operator[](const uint32 idx) const { return *(reinterpret_cast<T*>(&x+idx)); }
		inline operator T*() { return &x; }

		inline const Vector2Tpl& Flip() { x=-x;y=-y; return *this; }
		inline const Vector2Tpl& Zero() { x=y=0; return *this; }
		inline Vector2Tpl rot90ccw() const { return Vector2Tpl(-y,x); }
		inline Vector2Tpl rot90cw() const { return Vector2Tpl(y,-x); }

		inline Vector2Tpl operator-() const { return Vector2Tpl(-x,-y); }
		inline Vector2Tpl operator*(const T input) const { return Vector2Tpl(x*input,y*input); }
		inline Vector2Tpl& operator*=(const T input) { x*=input; y*=input; return *this; }
		inline Vector2Tpl operator/(const T input) const { return *this * (static_cast<T>(1.0f/input)); }
		inline Vector2Tpl& operator/=(const T input) { return *this *= (static_cast<T>(1.0/input)); }

		inline const bool operator!=(const Vector2Tpl<T>& input) { return !(*this == input); }

		inline friend const bool operator==(const Vector2Tpl<T>& left, const Vector2Tpl<T>& right){ return left.x == right.x && left.y == right.y; }
		inline friend const bool operator!=(const Vector2Tpl<T>& left, const Vector2Tpl<T>& right){	return !(left==right); }

		inline const bool IsZero(T e = static_cast<T>(0.0)) const {	return  (AbsTpl(x) <= e) && (AbsTpl(y) <= e);	}
		inline const T Dot(const Vector2Tpl& rhs) const {return x*rhs.x + y*rhs.y;}
		inline const Vector2Tpl Perp() const {return Vector2Tpl(-y, x);}
		inline const T Cross (const Vector2Tpl<T> &input) const	{	return float (x*input.y - y*input.x);	}	

		inline Vector2Tpl<T> GetRotated(const T angle) const{ return *this * CosTpl(angle) + rot90ccw() * SinTpl(angle); }
		inline bool IsValid() const { return NumberValid(x) && NumberValid(y); }

	public:
		T x;
		T y;
	};

	///////////////////////////////////////////////////////////////////////////////
	// Global Operators                                                          // 
	///////////////////////////////////////////////////////////////////////////////

	template<class T> Vector2Tpl<T> operator*(const T op1, const Vector2Tpl<T> &op2) { return Vector2Tpl<T>(op1*op2.x, op1*op2.y); }

	template<typename T1,typename T2> T1 operator*(const Vector2Tpl<T1> &op1, const Vector2Tpl<T2>& op2) { return op1.x*op2.x+op1.y*op2.y; } // dot product
	template<typename T1,typename T2> T1 operator|(const Vector2Tpl<T1> &op1, const Vector2Tpl<T2>& op2) { return op1.x*op2.x+op1.y*op2.y; } // dot product
	template<typename T1,typename T2> T1 operator^(const Vector2Tpl<T1> &op1, const Vector2Tpl<T2>& op2) { return op1.x*op2.y-op1.y*op2.x; } // cross product

	template<typename T1,typename T2> const Vector2Tpl<T1> operator+(const Vector2Tpl<T1> &op1, const Vector2Tpl<T2> &op2) { return Vector2Tpl<T1>(op1.x+op2.x,op1.y+op2.y); }
	template<typename T1,typename T2> const Vector2Tpl<T1> operator-(const Vector2Tpl<T1> &op1, const Vector2Tpl<T2> &op2) { return Vector2Tpl<T1>(op1.x-op2.x,op1.y-op2.y); }

	template<typename T1,typename T2> const Vector2Tpl<T1> operator+=(Vector2Tpl<T1> &op1, const Vector2Tpl<T2> &op2) { op1.x+=op2.x;op1.y+=op2.y; return op1; }
	template<typename T1,typename T2> const Vector2Tpl<T1> operator-=(Vector2Tpl<T1> &op1, const Vector2Tpl<T2> &op2) { op1.x-=op2.x;op1.y-=op2.y; return op1; }

	template<class T> const bool operator==(const Vector2Tpl<T>& left, const Vector2Tpl<T>& right) { return left.x == right.x && left.y == right.y; }

	///////////////////////////////////////////////////////////////////////////////
	// Typedefs                                                                  // 
	///////////////////////////////////////////////////////////////////////////////

	typedef Vector2Tpl<f32>     Vector2f;
	typedef Vector2Tpl<f64>     Vector2d;
	typedef Vector2Tpl<int32>   Vector2i;
	typedef Vector2Tpl<uint32>  Vector2u;

	template<> inline Vector2u::Vector2Tpl(ETypeMin){x=y=0u;}
	template<> inline Vector2i::Vector2Tpl(ETypeMin){x=y=GetMin<int32>();}

	template <typename T> Vector2Tpl<T> Vector2Constants<T>::zero(0, 0);
	template <typename T> Vector2Tpl<T> Vector2Constants<T>::oneX(1, 0);
	template <typename T> Vector2Tpl<T> Vector2Constants<T>::oneY(0, 1);
	template <typename T> Vector2Tpl<T> Vector2Constants<T>::oneZ(0, 0);
	template <typename T> Vector2Tpl<T> Vector2Constants<T>::one(1, 1);
	
	///////////////////////////////////////////////////////////////////////////////
	// Global Methods                                                            // 
	///////////////////////////////////////////////////////////////////////////////

	template<> inline const Vector2f ClampTpl<Vector2f>(const Vector2f input, const Vector2f Min, const Vector2f Max){ return Vector2f( ClampTpl(input.x, Min.x, Max.x), ClampTpl(input.y, Min.y, Max.y) ); }

}