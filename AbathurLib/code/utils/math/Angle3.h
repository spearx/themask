#pragma once

namespace MathUtils
{
	template <typename T> struct Angle3Tpl
	{
	public:
		inline Angle3Tpl(){}
		Angle3Tpl(ETypeZero):x(0),y(0),z(0){}

		void operator () ( const T vx, const T vy, const T vz ) { x=vx; y=vy; z=vz; };
		inline Angle3Tpl<T>( const T vx, const T vy, const T vz )	{	x=vx; y=vy; z=vz;	}  

		explicit inline Angle3Tpl(const Vector3Tpl<T>& v) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)) { ASSERT(IsValid()); }

		inline const bool operator==(const Angle3Tpl<T>& vec) { return x == vec.x && y == vec.y && z == vec.z; }
		inline const bool operator!=(const Angle3Tpl<T>& vec) { return !(*this == vec); }

		inline const Angle3Tpl<T> operator * (const T k) const { return Angle3Tpl<T>(x*k,y*k,z*k); }
		inline const Angle3Tpl<T> operator / (const T k) const { k=static_cast<T>(1.0/k); return Angle3Tpl<T>(x*k,y*k,z*k); }
		inline Angle3Tpl<T>& operator *= (const T k) { x*=k;y*=k;z*=k; return *this; }
		inline const Angle3Tpl<T> operator - ( void ) const { return Angle3Tpl<T>(-x,-y,-z); }

		inline friend bool operator ==(const Angle3Tpl<T> &v0, const Angle3Tpl<T> &v1) { return ((v0.x==v1.x) && (v0.y==v1.y) && (v0.z==v1.z));	}
		inline void Set(const T xval,const T yval,const T zval) { x=xval; y=yval; z=zval; }

		inline bool IsEquivalent( const Angle3Tpl<T>& v1, const T epsilon=VEC_EPSILON) const { return  ((AbsTpl(x-v1.x) <= epsilon) &&	(AbsTpl(y-v1.y) <= epsilon)&&	(AbsTpl(z-v1.z) <= epsilon));	}
		inline bool IsInRangePI() const {	return MathUtils::IsInRangePI(x) && MathUtils::IsInRangePI(y) && MathUtils::IsInRangePI(z);}
		inline void RangePI() { x = MathUtils::RangePI(x); y = MathUtils::RangePI(y); z = MathUtils::RangePI(z); }

		//Convert unit quaternion to angle (xyz).
		template<class T1> explicit Angle3Tpl( const QuatTpl<T1>& q )
		{
			ASSERT(q.IsValid());
			y = T( AsinTpl(max((T)-1.0,min((T)1.0,-(q.v.x*q.v.z-q.w*q.v.y)*2))) );
			if (AbsTpl(AbsTpl(y)-static_cast<T>(static_cast<T>(gfPI)*static_cast<T>(0.5)))<static_cast<T>(0.01))	
			{
				x = T(0);
				z = T(Atan2Tpl(-2*(q.v.x*q.v.y-q.w*q.v.z),1-(q.v.x*q.v.x+q.v.z*q.v.z)*2));
			} 
			else 
			{
				x = T(Atan2Tpl((q.v.y*q.v.z+q.w*q.v.x)*2, 1-(q.v.x*q.v.x+q.v.y*q.v.y)*2));
				z = T(Atan2Tpl((q.v.x*q.v.y+q.w*q.v.z)*2, 1-(q.v.z*q.v.z+q.v.y*q.v.y)*2));
			}
		}

		//Convert matrix33 to angle (xyz).
		template<class T1> explicit Angle3Tpl( const Matrix33Tpl<T1>& m )
		{
			ASSERT( m.IsOrthonormalRH(0.001f) );
			y = static_cast<T>(AsinTpl(max(static_cast<T>(-1.0),min((T)1.0,-m.m20))));
			if (AbsTpl(AbsTpl(y)-static_cast<T>(static_cast<T>(gfPI)*static_cast<T>(0.5)))<static_cast<T>(0.01))	
			{
				x = T(0);
				z = T(Atan2Tpl(-m.m01,m.m11));
			} 
			else 
			{
				x = T(Atan2Tpl(m.m21, m.m22));
				z = T(Atan2Tpl(m.m10, m.m00));
			}
		}

		//Convert matrix34 to angle (xyz).
		template<class T1> explicit Angle3Tpl( const Matrix34Tpl<T1>& m )
		{
			ASSERT( m.IsOrthonormalRH(0.001f) );
			y = static_cast<T>(AsinTpl(max(static_cast<T>(-1.0),min(static_cast<T>(1.0),-m.m20))) );
			if (AbsTpl(AbsTpl(y)-static_cast<T>(static_cast<T>(gfPI)*static_cast<T>(0.5)))<static_cast<T>(0.01))	
			{
				x = T(0);
				z = T(Atan2Tpl(-m.m01,m.m11));
			} 
			else 
			{
				x = T(Atan2Tpl(m.m21, m.m22));
				z = T(Atan2Tpl(m.m10, m.m00));
			}
		}

		//Convert matrix34 to angle (xyz).
		template<class T1> explicit Angle3Tpl( const Matrix44Tpl<T1>& m )
		{
			ASSERT( Matrix33(m).IsOrthonormalRH(0.001f) );
			y = static_cast<T>( AsinTpl(max(static_cast<T>(-1.0),min(static_cast<T>(1.0),-m.m20))) );
			if (AbsTpl(AbsTpl(y)-static_cast<T>(static_cast<T>(gfPI)*static_cast<T>(0.5)))<static_cast<T>(0.01))	
			{
				x = T(0);
				z = T(Atan2Tpl(-m.m01,m.m11));
			} 
			else 
			{
				x = T(Atan2Tpl(m.m21, m.m22));
				z = T(Atan2Tpl(m.m10, m.m00));
			}
		}

		template<typename T1>	static inline const T CreateRadZ( const Vector2Tpl<T1>& v0, const Vector2Tpl<T1>& v1 ){	return T( Atan2Tpl(v0.x*v1.y-v0.y*v1.x,v0.x*v1.x+v0.y*v1.y) ); }
		template<typename T1>	static inline const T CreateRadZ( const Vector3Tpl<T1>& v0, const Vector3Tpl<T1>& v1 ){	return T( Atan2Tpl(v0.x*v1.y-v0.y*v1.x,v0.x*v1.x+v0.y*v1.y) ); }

		template<typename T1>	inline static const Angle3Tpl<T> GetAnglesXYZ( const QuatTpl<T1>& q ) { return Angle3Tpl<T>(q); }
		template<typename T1>	inline void SetAnglesXYZ( const QuatTpl<T1>& q ) { *this=Angle3Tpl<T>(q); }

		template<typename T1>	inline static const Angle3Tpl<T> GetAnglesXYZ( const Matrix33Tpl<T1>& m ) {	return Angle3Tpl<T>(m); }
		template<typename T1>	inline void SetAnglesXYZ( const Matrix33Tpl<T1>& m ) { *this=Angle3Tpl<T>(m); }

		template<typename T1>	inline static const Angle3Tpl<T> GetAnglesXYZ( const Matrix34Tpl<T1>& m ) {	return Angle3Tpl<T>(m); }
		template<typename T1>	inline void SetAnglesXYZ( const Matrix34Tpl<T1>& m ) { *this=Angle3Tpl<T>(m); }

		inline T &operator [] (const uint32 index) { ASSERT(index<=2); return (reinterpret_cast<T*>(this))[index]; }
		inline const T operator [] (const uint32 index) const { ASSERT(index<=2); return (reinterpret_cast<T*>(this))[index]; }

		inline const bool IsValid() const { return NumberValid(x) && NumberValid(y) && NumberValid(z); }

	public:
		T x;
		T y;
		T z;
	};

	///////////////////////////////////////////////////////////////////////////////
	// Global Operators                                                          // 
	///////////////////////////////////////////////////////////////////////////////

	//angles addition & subtraction
	template<typename T1,typename T2> inline const Angle3Tpl<T1> operator + (const Angle3Tpl<T1>& v0, const Angle3Tpl<T2>& v1) { return Angle3Tpl<T1>(v0.x+v1.x, v0.y+v1.y, v0.z+v1.z); }
	template<typename T1,typename T2> inline const Angle3Tpl<T1> operator - (const Angle3Tpl<T1>& v0, const Angle3Tpl<T2>& v1) { return Angle3Tpl<T1>(v0.x-v1.x, v0.y-v1.y, v0.z-v1.z); }

	//angles self-operations
	template<typename T1,typename T2> inline Angle3Tpl<T1>& operator += (Angle3Tpl<T1>& v0, const Angle3Tpl<T2>& v1) { v0=v0+v1; return v0; }
	template<typename T1,typename T2> inline Angle3Tpl<T1>& operator -= (Angle3Tpl<T1>& v0, const Angle3Tpl<T2>& v1) { v0=v0-v1; return v0; }

	///////////////////////////////////////////////////////////////////////////////
	// Typedefs                                                                  // 
	///////////////////////////////////////////////////////////////////////////////

	typedef Angle3Tpl<f32>	Angle3f;
	typedef Angle3Tpl<f64>	Angle3d;

	///////////////////////////////////////////////////////////////////////////////
	// Global Methods                                                            // 
	///////////////////////////////////////////////////////////////////////////////

	template<> inline const Angle3f ClampTpl<Angle3f>(const Angle3f input, const Angle3f Min, const Angle3f Max){ return Angle3f( ClampTpl(input.x, Min.x, Max.x), ClampTpl(input.y, Min.y, Max.y), ClampTpl(input.z, Min.z, Max.z) ); }
}
