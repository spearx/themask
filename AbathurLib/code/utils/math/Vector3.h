#pragma once

namespace MathUtils
{
	template<typename T> struct Vector3Tpl;
	template<typename T> struct Vector3Constants
	{
		static const Vector3Tpl<T> zero;
		static const Vector3Tpl<T> oneX;
		static const Vector3Tpl<T> oneY;
		static const Vector3Tpl<T> oneZ;
		static const Vector3Tpl<T> one;
	};

	template <typename T> struct Vector3Tpl
	{
	public:
		inline Vector3Tpl(){}

		inline Vector3Tpl(ETypeZero):x(0),y(0),z(0){}
		inline Vector3Tpl(ETypeMin){x=y=z=-GetMax<T>();}
		inline Vector3Tpl(ETypeMax){x=y=z=GetMax<T>();}

		inline Vector3Tpl( const T vx, const T vy, const T vz ) : x(vx),y(vy),z(vz){ ASSERT(IsValid()); }
		inline Vector3Tpl( const Vector2Tpl<T>& v, const T vz ) : x(v.x),y(v.y),z(vz) { ASSERT(IsValid()); }
		inline void operator() (const T vx, const T vy, const T vz ) { x=vx; y=vy; z=vz; ASSERT(IsValid()); }
		inline const Vector3Tpl<T>& Set(const T xval,const T yval, const T zval) { x=xval; y=yval; z=zval; ASSERT(IsValid()); return *this; }
		explicit inline Vector3Tpl( T input ) : x(input),y(input),z(input) { ASSERT(IsValid()); }

		template <typename T2> inline Vector3Tpl( const Vector3Tpl<T2>& input ) : x(static_cast<T>(input.x)), y(static_cast<T>(input.y)), z(static_cast<T>(input.z)) { ASSERT(IsValid()); }
		explicit inline Vector3Tpl(const Angle3Tpl<T>& input) : x(static_cast<T>(input.x)), y(static_cast<T>(input.y)), z(static_cast<T>(input.z)) { ASSERT(IsValid()); }
		inline Vector3Tpl(const Vector2Tpl<T>& input) : x(static_cast<T>(input.x)), y(static_cast<T>(input.y)), z(0) { ASSERT(IsValid()); }

		//operators
		inline Vector3Tpl<T> operator * (const T k) const { const Vector3Tpl<T> v = *this; return Vector3Tpl<T>(v.x*k,v.y*k,v.z*k);	}
		inline Vector3Tpl<T> operator / (T k) const { k=static_cast<T>(1.0/k); return Vector3Tpl<T>(x*k,y*k,z*k); }
		inline friend Vector3Tpl<T> operator * (const T scalar, const Vector3Tpl &vec) { return Vector3Tpl(static_cast<T>(scalar*vec.x), static_cast<T>(scalar*vec.y), static_cast<T>(scalar*vec.z)); }

		inline const Vector3Tpl<T>& operator *= (const T k) { x*=k;y*=k;z*=k; return *this; }
		inline const Vector3Tpl<T>& operator /= (const T k) { k=static_cast<T>(1.0/k); x*=k;y*=k;z*=k; return *this; }

		inline Vector3Tpl<T> operator - ( void ) const { return Vector3Tpl<T>(-x,-y,-z);	}
		inline const Vector3Tpl<T>& Flip() { x=-x; y=-y; z=-z; return *this; }
	
		inline       T& operator [] (const uint32 index)      { ASSERT(index<=2u); return (reinterpret_cast<T*>(this))[index]; }
		inline const T operator [] (const uint32 index) const { ASSERT(index<=2u); return (reinterpret_cast<T*>(this))[index]; }

		inline const bool operator==(const Vector3Tpl<T>& vec) { return x == vec.x && y == vec.y && z == vec.z; }
		inline const bool operator!=(const Vector3Tpl<T>& vec) { return !(*this == vec); }

		inline friend const bool operator ==(const Vector3Tpl<T>& v0, const Vector3Tpl<T>& v1){	return ((v0.x==v1.x) && (v0.y==v1.y) && (v0.z==v1.z));	}
		inline friend const bool operator !=(const Vector3Tpl<T>& v0, const Vector3Tpl<T>& v1){	return !(v0==v1);	}

		inline const bool IsZero(const T e = static_cast<T>(0.0)) const { return  (AbsTpl(x) <= e) && (AbsTpl(y) <= e) && (AbsTpl(z) <= e); }
		inline const bool IsEquivalent(const Vector3Tpl<T>& input, const T epsilon=VEC_EPSILON) const { return IsEquivalent(*this,input); }

		inline static const bool IsEquivalent(const Vector3Tpl<T>& v0, const Vector3Tpl<T>& v1, const T epsilon=VEC_EPSILON) 
		{ 
			ASSERT(v0.IsValid()); ASSERT(v1.IsValid()); 
			return ((AbsTpl(v0.x-v1.x) <= epsilon) &&	(AbsTpl(v0.y-v1.y) <= epsilon)&& (AbsTpl(v0.z-v1.z) <= epsilon));
		}
	
		inline const bool IsUnit(const T epsilon=VEC_EPSILON) const {	return (AbsTpl(1 - GetLengthSquared()) <= epsilon); }
		inline const bool IsValid() const {	return NumberValid(x) && NumberValid(y) && NumberValid(z); }

		inline const T GetLength() const { return SqrtTpl(GetLengthSquared()); }
		inline const T GetLengthFast() const { return SqrtFastTpl(GetLengthSquared()); }
		inline const T GetLengthSquared() const	{ return x*x+y*y+z*z; }
		inline const T GetLength2D() const { return SqrtTpl(GetLengthSquared2D()); }
		inline const T GetLengthFast2D() const { return SqrtFastTpl(GetLengthSquared2D()); }
		inline const T GetLengthSquared2D() const {	return x*x+y*y; }

		inline const T GetDistance(const Vector3Tpl<T>& input) const { return (input - *this).GetLength(); }
		inline const T GetDistanceSquared ( const Vector3Tpl<T>& input) const { return (input - *this).GetLengthSquared(); }
		inline const T GetDistance2D ( const Vector3Tpl<T>& input) const { return (input - *this).GetLength2D(); }
		inline const T GetDistanceSquared2D ( const Vector3Tpl<T>& input) const { return  (input - *this).GetLengthSquared2D(); }

		inline void	Normalize()
		{ 
			ASSERT(IsValid()); 
			const T invLen = InvSqrtSafeTpl( GetLengthSquared() );
			x*=invLen; y*=invLen; z*=invLen; 
		}

		inline void NormalizeFast() 
		{
			ASSERT(IsValid()); 
			const T invLen = InvSqrtFastTpl( GetLengthSquared() );
			x*=invLen; y*=invLen; z*=invLen; 
		}

		inline const Vector3Tpl& NormalizeSafe(const struct Vector3Tpl<T>& safeValue = Vector3Constants<T>::zero) { ASSERT(IsValid()); *this = GetNormalizedSafe(safeValue);	return *this; }

		inline Vector3Tpl GetNormalized() const { return *this * InvSqrtSafeTpl( GetLengthSquared() ); }
		inline Vector3Tpl GetNormalizedFast() const { return *this * InvSqrtFastTpl( GetLengthSquared() ); }
		inline Vector3Tpl GetNormalizedSafe(const struct Vector3Tpl<T>& safe = Vector3Constants<T>::oneX) const { ASSERT(IsValid()); return (GetLengthSquared() > 0.0f)? GetNormalized() : safe; }

		inline const T GetVolume() const { return x*y*z; }

		inline Vector3Tpl Abs() const { return Vector3Tpl(AbsTpl(x),AbsTpl(y),AbsTpl(z)); }
		inline void MinBound(const Vector3Tpl<T>& other){ x = GET_MIN(other.x,x); y = GET_MIN(other.y,y); z = GET_MIN(other.z,z); }
		inline void MaxBound(const Vector3Tpl<T>& other){ x = GET_MAX(other.x,x); y = GET_MAX(other.y,y); z = GET_MAX(other.z,z); }

		/*
		inline void SetOrthogonal( const Vector3Tpl<T>& v )
		{
			const int32 i = isneg(square((T)0.9)*v.GetLengthSquared()-v.x*v.x);
			(*this)[i]=0; (*this)[incm3(i)]= v[decm3(i)];	(*this)[decm3(i)]=-v[incm3(i)];
		}
		// returns a vector orthogonal to this one
		inline Vector3Tpl GetOrthogonal() const
		{
			int i = isneg(square((T)0.9)*GetLengthSquared()-x*x);
			Vector3Tpl<T> res;
			res[i]=0; res[incm3(i)]=(*this)[decm3(i)]; res[decm3(i)]=-(*this)[incm3(i)];
			return res;
		}
		*/

		inline void SetProjection( const Vector3Tpl& i, const Vector3Tpl& n ) { *this = i-n*(n|i); }
		inline static Vector3Tpl<T> CreateProjection( const Vector3Tpl& i, const Vector3Tpl& n ) { return i-n*(n|i); }

		inline void SetReflection( const Vector3Tpl<T>& incident , const Vector3Tpl<T>& normal){ *this=(normal*(incident |normal)*2)-incident ; }
		inline static Vector3Tpl<T> CreateReflection( const Vector3Tpl<T>& incident, const Vector3Tpl<T>& normal ){	return (normal*(incident|normal)*2)-incident; }
	
		inline Vector3Tpl<T> GetRotated(const Vector3Tpl<T>& axis, const T cosa, const T sina) const 
		{
			Vector3Tpl<T> zax = axis*(*this|axis); 
			Vector3Tpl<T> xax = *this-zax; 
			Vector3Tpl<T> yax = axis%xax;
			return xax*cosa + yax*sina + zax;
		}

		inline Vector3Tpl<T> GetRotated(const Vector3Tpl<T>& axis, const T angle) const { return GetRotated(axis,CosTpl(angle),SinTpl(angle)); }
		inline Vector3Tpl<T> GetRotated(const Vector3Tpl<T>& center,const Vector3Tpl<T>& axis, const T angle) const { return center+(*this-center).GetRotated(axis,angle);}
		inline Vector3Tpl<T> GetRotated(const Vector3Tpl<T>& center,const Vector3Tpl<T>& axis, const T cosa, const T sina) const { return center+(*this-center).GetRotated(axis,cosa,sina); }

		inline Vector3Tpl<T> GetRotatedZ(const T angle) const {	const Vector2Tpl<T>& rotated = Vector2Tpl<T>(x,y).GetRotated(angle); return Vector3Tpl<T>(rotated.x, rotated.y, z); }

		inline Vector3Tpl CompMul( const Vector3Tpl<T>& rhs ) const { return( Vector3Tpl( x * rhs.x, y * rhs.y, z * rhs.z ) ); }

		inline const T Dot (const Vector3Tpl<T>& input)	const { return x*input.x + y*input.y + z*input.z;	}
		inline Vector3Tpl<T> Cross (const Vector3Tpl<T> input) const { return Vector3Tpl<T>( y*input.z - z*input.y, z*input.x - x*input.z, x*input.y - y*input.x); }
		inline Vector3Tpl& Zero() { x=y=z=0; return *this; }

	public:
		T x;
		T y;
		T z;
	};

	///////////////////////////////////////////////////////////////////////////////
	// Global Operators                                                          // 
	///////////////////////////////////////////////////////////////////////////////

	// dot product (2 versions)
	template<typename T1,typename T2> inline const T1 operator * (const Vector3Tpl<T1>& v0, const Vector3Tpl<T2>& v1) {	return v0.Dot(v1); } 
	template<typename T1,typename T2> inline const T1 operator | (const Vector3Tpl<T1>& v0, const Vector3Tpl<T2>& v1) { return v0.Dot(v1); } 

	// cross product (2 versions)
	template<typename T1,typename T2> inline const Vector3Tpl<T1> operator ^ (const Vector3Tpl<T1>& v0, const Vector3Tpl<T2>& v1) {	return v0.Cross(v1); }
	template<typename T1,typename T2> inline const Vector3Tpl<T1> operator % (const Vector3Tpl<T1>& v0, const Vector3Tpl<T2>& v1) {	return v0.Cross(v1); } 

	//vector addition																																							  												  
	template<typename T1,typename T2> inline const Vector3Tpl<T1> operator + (const Vector3Tpl<T1>& v0, const Vector3Tpl<T2>& v1)	{ return Vector3Tpl<T1>(v0.x+v1.x, v0.y+v1.y, v0.z+v1.z); }
	template<typename T1,typename T2> inline const Vector3Tpl<T1> operator + (const Vector2Tpl<T1>& v0, const Vector3Tpl<T2>& v1) {	return Vector3Tpl<T1>(v0.x+v1.x, v0.y+v1.y, v1.z); }
	template<typename T1,typename T2> inline const Vector3Tpl<T1> operator + (const Vector3Tpl<T1>& v0, const Vector2Tpl<T2>& v1) {	return Vector3Tpl<T1>(v0.x+v1.x, v0.y+v1.y, v0.z); }

	//vector subtraction																																					  												  
	template<typename T1,typename T2> inline const Vector3Tpl<T1> operator - (const Vector3Tpl<T1>& v0, const Vector3Tpl<T2>& v1) {	return Vector3Tpl<T1>(static_cast<T1>(v0.x-v1.x), static_cast<T1>(v0.y-v1.y), static_cast<T1>(v0.z-v1.z)); }
	template<typename T1,typename T2> inline const Vector3Tpl<T1> operator - (const Vector2Tpl<T1>& v0, const Vector3Tpl<T2>& v1) {	return Vector3Tpl<T1>(v0.x-v1.x, v0.y-v1.y, 0.0f-v1.z); }
	template<typename T1,typename T2> inline const Vector3Tpl<T1> operator - (const Vector3Tpl<T1>& v0, const Vector2Tpl<T2>& v1) {	return Vector3Tpl<T1>(v0.x-v1.x, v0.y-v1.y, v0.z); }

	//vector self-addition and subtraction
	template<typename T1,typename T2> inline const Vector3Tpl<T1>& operator += (Vector3Tpl<T1>& v0, const Vector3Tpl<T2>& v1) { v0=v0+v1; return v0; }
	template<typename T1,typename T2> inline const Vector3Tpl<T1>& operator -= (Vector3Tpl<T1>& v0, const Vector3Tpl<T2>& v1) { v0=v0-v1; return v0; }

	template<typename T1,typename T2> inline const Vector3Tpl<T1> operator / (const Vector3Tpl<T1>& v0, const Vector3Tpl<T2>& v1){ return Vector3Tpl<T1>(v0.x/v1.x, v0.y/v1.y, v0.z/v1.z); } 

	///////////////////////////////////////////////////////////////////////////////
	// Typedefs                                                                  // 
	///////////////////////////////////////////////////////////////////////////////

	typedef Vector3Tpl<f32>     Vector3f;
	typedef Vector3Tpl<f64>     Vector3d;
	typedef Vector3Tpl<int32>   Vector3i;
	typedef Vector3Tpl<uint32>  Vector3u;

	template<> inline Vector3u::Vector3Tpl(ETypeMin){x=y=z=0u;}
	template<> inline Vector3i::Vector3Tpl(ETypeMin){x=y=z=GetMin<int32>();}

	template <typename T> const Vector3Tpl<T> Vector3Constants<T>::zero(0, 0, 0);
	template <typename T> const Vector3Tpl<T> Vector3Constants<T>::oneX(1, 0, 0);
	template <typename T> const Vector3Tpl<T> Vector3Constants<T>::oneY(0, 1, 0);
	template <typename T> const Vector3Tpl<T> Vector3Constants<T>::oneZ(0, 0, 1);
	template <typename T> const Vector3Tpl<T> Vector3Constants<T>::one(1, 1, 1);
	
	///////////////////////////////////////////////////////////////////////////////
	// Global Methods                                                            // 
	///////////////////////////////////////////////////////////////////////////////

	template <typename T> inline const bool IsEquivalent(const Vector3Tpl<T> &v0, const Vector3Tpl<T> &v1, f32 epsilon=VEC_EPSILON ) { return  ((AbsTpl(v0.x-v1.x) <= epsilon) &&	(AbsTpl(v0.y-v1.y) <= epsilon)&&	(AbsTpl(v0.z-v1.z) <= epsilon)); }
	template<> inline const Vector3f ClampTpl<Vector3f>(const Vector3f input, const Vector3f Min, const Vector3f Max){ return Vector3f( ClampTpl(input.x, Min.x, Max.x), ClampTpl(input.y, Min.y, Max.y), ClampTpl(input.z, Min.z, Max.z) ); }
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T> struct PlaneTpl
	{
		inline PlaneTpl(){};
		inline PlaneTpl( const PlaneTpl<T>& p ) {	normal=p.normal; distance=p.distance; }
		inline PlaneTpl( const Vector3Tpl<T>& inputNormal, const T inputDistance ) {  normal=inputNormal; distance=inputDistance; }

		inline void Set(const Vector3Tpl<T>& vNormal,const T fDist)	{	normal = vNormal; distance = fDist;	}
		inline void SetPlane( const Vector3Tpl<T>& inputNormal, const Vector3Tpl<T> &inputPoint ) { normal=inputNormal; distance=-(inputPoint | normal); }
		inline static const PlaneTpl<T> CreatePlane( const Vector3Tpl<T>& inputNormal, const Vector3Tpl<T>& inputPoint ) { return PlaneTpl<T>( inputNormal,-(inputPoint|inputNormal) ); }

		inline const PlaneTpl<T> operator - ( void ) const { return PlaneTpl<T>(-normal,-distance); }

		//Constructs the plane by tree given Vec3s (=triangle) with a right-hand (anti-clockwise) winding
		inline void SetPlane( const Vector3Tpl<T> &v0, const Vector3Tpl<T>& v1, const Vector3Tpl<T>& v2 ) { normal = ((v1-v0)%(v2-v0)).GetNormalized();	distance = -(normal | v0);	}
		inline static const PlaneTpl<T> CreatePlane( const Vector3Tpl<T>& v0, const Vector3Tpl<T>& v1, const Vector3Tpl<T>& v2 ) { PlaneTpl<T> p;	p.SetPlane(v0,v1,v2);	return p; }

		inline const T operator | (const Vector3Tpl<T>& point ) const { return (normal | point) + distance; }
		inline const T DistFromPlane (const Vector3Tpl<T>& point) const	{	return (normal * point + distance); }

		inline const PlaneTpl<T> operator - ( const PlaneTpl<T>& p) const { return PlaneTpl<T>( normal-p.normal, distance-p.distance); }
		inline const PlaneTpl<T> operator + ( const PlaneTpl<T>& p) const { return PlaneTpl<T>(normal+p.normal,distance+p.distance); }
		inline void operator -= (const PlaneTpl<T>& p) { distance-=p.distance; normal-=p.normal; }
		inline const PlaneTpl<T> operator * ( const T s ) const {	return PlaneTpl<T>(normal*s,distance*s);	}
		inline const PlaneTpl<T> operator / ( const T s ) const {	return PlaneTpl<T>(normal/s,distance/s); }

		friend	bool operator ==(const PlaneTpl<T> &p1, const PlaneTpl<T> &p2) { return CmpTpl(p1.normal.x,p2.normal.x) && CmpTpl(p1.normal.y,p2.normal.y) && CmpTpl(p1.normal.z,p2.normal.z) && CmpTpl(p1.distance,p2.distance); }

		const Vector3Tpl<T> MirrorVector(const Vector3Tpl<T>& i)   {	return normal*(2*(normal|i))-i;	}
		const Vector3Tpl<T> MirrorPosition(const Vector3Tpl<T>& i) {  return i - normal*(2*((normal|i)+distance)); }

	public:
		Vector3Tpl<T>  normal;
		T              distance;
	};

	///////////////////////////////////////////////////////////////////////////////
	// Typedefs                                                                  // 
	///////////////////////////////////////////////////////////////////////////////

	typedef PlaneTpl<f32> Planef;
	typedef PlaneTpl<f64> Planed;

}

