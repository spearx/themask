#pragma once

namespace MathUtils
{
	template<typename T> struct Vector4Tpl;
	template<typename T> struct Vector4Constants
	{
		static const Vector4Tpl<T> zero;
		static const Vector4Tpl<T> oneX;
		static const Vector4Tpl<T> oneY;
		static const Vector4Tpl<T> oneZ;
		static const Vector4Tpl<T> oneW;
		static const Vector4Tpl<T> one;
	};
	
	template <typename T> struct Vector4Tpl
	{
	public:

		inline Vector4Tpl(){}
		inline Vector4Tpl(ETypeZero):x(0),y(0),z(0),w(0){}
		inline Vector4Tpl(ETypeMin){x=y=z=w=-GetMax<T>();}
		inline Vector4Tpl(ETypeMax){x=y=z=w=GetMax<T>();}
		template<typename T2>	inline Vector4Tpl<T>& operator = (const Vector4Tpl<T2> &v1) { x=T(v1.x); y=T(v1.y); z=T(v1.z); w=T(v1.w);	return (*this);	}
		inline Vector4Tpl( const T input):x(input),y(input),z(input),w(input){}
		inline Vector4Tpl( const T vx, const T vy, const T vz, const T vw ):x(vx),y(vy),z(vz),w(vw){}
		inline Vector4Tpl( const Vector2Tpl<T>& v, const T vz, const T vw):x(v.x),y(v.y),z(vz),w(vw){}
		inline Vector4Tpl( const Vector2Tpl<T>& v1, const Vector2Tpl<T>& v2):x(v1.x),y(v1.y),z(v2.x),w(v2.y){}
		inline Vector4Tpl( const Vector3Tpl<T>& v, const T vw ):x(v.x),y(v.y),z(v.z),w(vw) {}
    inline const Vector4Tpl<T>& Set(const T xval, const T yval, const T zval, const T wval) { x = xval; y = yval; z = zval; w = wval; ASSERT(IsValid()); return *this; }

		inline void operator () ( const T vx, const T vy, const T vz, const T vw ) { x=vx; y=vy; z=vz; w=vw; };
		inline void operator () ( const Vector3Tpl<T>& v, T vw ) {  x=v.x; y=v.y; z=v.z; vw=vw; };

		inline T &operator [] (const uint32 index) { ASSERT(index<=3); return (reinterpret_cast<T*>(this))[index]; }
		inline const T operator [] (const uint32 index) const { ASSERT(index<=3); return (reinterpret_cast<T*>(this))[index]; }
		template <typename T2> inline  Vector4Tpl( const Vector4Tpl<T2>& v ) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)), w(static_cast<T>(v.w)) { ASSERT(IsValid()); }

		inline bool IsEquivalent(const Vector4Tpl<T>& v1, const T epsilon=VEC_EPSILON) const { ASSERT(v1.IsValid()); ASSERT(IsValid()); return  ((AbsTpl(x-v1.x) <= epsilon) &&	(AbsTpl(y-v1.y) <= epsilon)&&	(AbsTpl(z-v1.z) <= epsilon) && (AbsTpl(w-v1.w) <= epsilon)); }

		inline Vector4Tpl& operator=( const Vector4Tpl& src ) {	x=src.x; y=src.y; z=src.z; w=src.w; return *this; }

		inline const Vector4Tpl<T> operator * (const T k) const { return Vector4Tpl<T>(x*k,y*k,z*k,w*k); }
		inline const Vector4Tpl<T> operator / (const T k) const { k=static_cast<T>(1.0/k); return Vector4Tpl<T>(x*k,y*k,z*k,w*k); }

		inline const Vector4Tpl<T>& operator *= (const T k) { x*=k; y*=k; z*=k; w*=k; return *this; }
		inline const Vector4Tpl<T>& operator /= (const T k) { k=static_cast<T>(1.0/k); x*=k; y*=k; z*=k; w*=k; return *this; }

		inline const T Dot (const Vector4Tpl<T> &input) const { return x*input.x + y*input.y + z*input.z + w*input.w; }
		inline const T GetLength() const { return SqrtTpl(GetLengthSquared()); }
		inline const T GetLengthSquared() const { return Dot(*this); }
		inline const bool IsValid() const { return NumberValid(x) && NumberValid(y) && NumberValid(z) && NumberValid(w); }

		inline bool operator==(const Vector4Tpl<T> &vec){	return CmpTpl(x,vec.x) && CmpTpl(y,vec.y) && CmpTpl(z,vec.z) && CmpTpl(w,vec.w); }
		inline bool operator!=(const Vector4Tpl<T> &vec){ return !(*this == vec); }

		inline friend bool operator ==(const Vector4Tpl<T> &v0, const Vector4Tpl<T> &v1){ return (CmpTpl(v0.x,v1.x) && CmpTpl(v0.y,v1.y) && CmpTpl(v0.z,v1.z) && CmpTpl(v0.w,v1.w)); }
		inline friend bool operator !=(const Vector4Tpl<T> &v0, const Vector4Tpl<T> &v1){ return !(v0==v1); }

		inline void	Normalize(){ ASSERT( IsValid()); const T invLen = InvSqrtSafeTpl( GetLengthSquared() ); x*=invLen; y*=invLen; z*=invLen; w*=invLen; }
		inline void NormalizeFast() { ASSERT(this->IsValid()); const T invLen = InvSqrtFastTpl( GetLengthSquared() ); x*=invLen; y*=invLen; z*=invLen; w*=invLen; }

	public:
		T x;
		T y;
		T z;
		T w;
	}; 

	///////////////////////////////////////////////////////////////////////////////
	// Global Operators                                                          // 
	///////////////////////////////////////////////////////////////////////////////

	template<typename T1,typename T2> inline Vector4Tpl<T1>& operator += (Vector4Tpl<T1>& v0, const Vector4Tpl<T2>& v1) { v0=v0+v1; return v0; }
	template<typename T1,typename T2> inline Vector4Tpl<T1>& operator -= (Vector4Tpl<T1>& v0, const Vector4Tpl<T2>& v1) { v0=v0-v1; return v0; }
	template<typename T1,typename T2> inline Vector4Tpl<T1>& operator *= (Vector4Tpl<T1>& v0, const Vector4Tpl<T2>& v1) { v0=v0*v1; return v0; }
	template<typename T1,typename T2> inline Vector4Tpl<T1>& operator /= (Vector4Tpl<T1>& v0, const Vector4Tpl<T2>& v1) { v0=v0/v1; return v0; }
	template<typename T1,typename T2> inline const Vector4Tpl<T1> operator + (const Vector4Tpl<T1>& v0, const Vector4Tpl<T2>& v1){ return Vector4Tpl<T1>(v0.x+v1.x, v0.y+v1.y, v0.z+v1.z, v0.w+v1.w); }
	template<typename T1,typename T2> inline const Vector4Tpl<T1> operator - (const Vector4Tpl<T1>& v0, const Vector4Tpl<T2>& v1){ return Vector4Tpl<T1>(v0.x-v1.x, v0.y-v1.y, v0.z-v1.z, v0.w-v1.w); }
	template<typename T1,typename T2> inline const Vector4Tpl<T1> operator * (const Vector4Tpl<T1>& v0, const Vector4Tpl<T2>& v1){ return Vector4Tpl<T1>(v0.x*v1.x, v0.y*v1.y, v0.z*v1.z, v0.w*v1.w); }
	template<typename T1,typename T2> inline const Vector4Tpl<T1> operator / (const Vector4Tpl<T1>& v0, const Vector4Tpl<T2>& v1){ return Vector4Tpl<T1>(v0.x/v1.x, v0.y/v1.y, v0.z/v1.z, v0.w/v1.w); }

	///////////////////////////////////////////////////////////////////////////////
	// Typedefs                                                                  // 
	///////////////////////////////////////////////////////////////////////////////

	typedef Vector4Tpl<f32>     Vector4f;
	typedef Vector4Tpl<f64>     Vector4d;
	typedef Vector4Tpl<int32>   Vector4i;
	typedef Vector4Tpl<uint32>  Vector4u;

	template<> inline Vector4u::Vector4Tpl(ETypeMin){x=y=z=w=0u;}
	template<> inline Vector4i::Vector4Tpl(ETypeMin){x=y=z=w=GetMin<int32>();}

	template <typename T> const Vector4Tpl<T> Vector4Constants<T>::zero(0, 0, 0, 0);
	template <typename T> const Vector4Tpl<T> Vector4Constants<T>::oneX(1, 0, 0, 0);
	template <typename T> const Vector4Tpl<T> Vector4Constants<T>::oneY(0, 1, 0, 0);
	template <typename T> const Vector4Tpl<T> Vector4Constants<T>::oneZ(0, 0, 1, 0);
	template <typename T> const Vector4Tpl<T> Vector4Constants<T>::oneW(0, 0, 0, 1);
	template <typename T> const Vector4Tpl<T> Vector4Constants<T>::one(1, 1, 1, 1);


	///////////////////////////////////////////////////////////////////////////////
	// Global Methods                                                            // 
	///////////////////////////////////////////////////////////////////////////////
	
	template<> inline const Vector4f ClampTpl<Vector4f>(const Vector4f input, const Vector4f Min, const Vector4f Max){ return Vector4f( ClampTpl(input.x, Min.x, Max.x), ClampTpl(input.y, Min.y, Max.y), ClampTpl(input.z, Min.z, Max.z), ClampTpl(input.w, Min.w, Max.w) ); }
}
