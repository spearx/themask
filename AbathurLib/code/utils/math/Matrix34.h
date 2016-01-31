#pragma once

namespace MathUtils
{
	template <typename T> struct Matrix34Tpl
	{
		inline Matrix34Tpl(){};
		inline Matrix34Tpl<T>& operator = (const Matrix34Tpl<T>& m) { ASSERT(m.IsValid()); m00=m.m00; m01=m.m01; m02=m.m02; m03=m.m03; m10=m.m10; m11=m.m11; m12=m.m12; m13=m.m13;	m20=m.m20; m21=m.m21; m22=m.m22; m23=m.m23; return *this;	}
		inline Matrix34Tpl<T>( const f32 v00, const f32 v01, const f32 v02, const f32 v03, const f32 v10, const f32 v11, const f32 v12, const f32 v13, const f32 v20, const f32 v21, const f32 v22, const f32 v23)
		{
			m00=v00; m01=v01; m02=v02; m03=v03; m10=v10; m11=v11; m12=v12; m13=v13; m20=v20; m21=v21; m22=v22; m23=v23; 
		}

		Matrix34Tpl( const Vector3Tpl<T>& s, const QuatTpl<T>& q, const Vector3Tpl<T>& t = Vector3Tpl<T>(ZERO) ) {	Set(s, q, t); }
		inline Matrix34Tpl<T>(const Matrix33Tpl<T>& m) { ASSERT(m.IsValid()); m00=m.m00; m01=m.m01; m02=m.m02; m03=0; m10=m.m10; m11=m.m11; m12=m.m12; m13=0; m20=m.m20; m21=m.m21; m22=m.m22; m23=0; }
		template<class T1> inline Matrix34Tpl<T>(const Matrix33Tpl<T1>& m) { ASSERT(m.IsValid()); m00=T(m.m00); m01=T(m.m01); m02=T(m.m02); m03=0; m10=T(m.m10); m11=T(m.m11); m12=T(m.m12); m13=0; m20=T(m.m20); m21=T(m.m21); m22=T(m.m22); m23=0; }
		inline Matrix34Tpl<T>(const Matrix33Tpl<T>& m, const Vector3Tpl<T>& t){	ASSERT(m.IsValid()); ASSERT(t.IsValid()); m00=m.m00; m01=m.m01; m02=m.m02; m03=t.x;	m10=m.m10; m11=m.m11; m12=m.m12; m13=t.y; m20=m.m20; m21=m.m21; m22=m.m22; m23=t.z; }
		template<class T1> inline Matrix34Tpl<T>(const Matrix33Tpl<T1>& m, const Vector3Tpl<T1>& t){ASSERT(m.IsValid()); ASSERT(t.IsValid()); m00=T(m.m00); m01=T(m.m01); m02=T(m.m02);	m03=T(t.x); m10=T(m.m10); m11=T(m.m11); m12=T(m.m12); m13=T(t.y); m20=T(m.m20);	m21=T(m.m21); m22=T(m.m22); m23=T(t.z); }

		inline Matrix34Tpl<T>( const Matrix34Tpl<T>& m ) { ASSERT(m.IsValid());	m00=m.m00; m01=m.m01; m02=m.m02; m03=m.m03; m10=m.m10; m11=m.m11; m12=m.m12; m13=m.m13;	m20=m.m20; m21=m.m21; m22=m.m22; m23=m.m23; }
		template<class T1> inline Matrix34Tpl<T>( const Matrix34Tpl<T1>& m ) { ASSERT(m.IsValid());	m00=T(m.m00); m01=T(m.m01); m02=T(m.m02); m03=T(m.m03);	m10=T(m.m10); m11=T(m.m11); m12=T(m.m12); m13=T(m.m13); m20=T(m.m20); m21=T(m.m21); m22=T(m.m22); m23=T(m.m23);	}
		inline explicit Matrix34Tpl<T>(const Matrix44Tpl<T>& m ){ ASSERT(m.IsValid()); m00=m.m00; m01=m.m01; m02=m.m02; m03=m.m03; m10=m.m10; m11=m.m11; m12=m.m12;	m13=m.m13; m20=m.m20; m21=m.m21; m22=m.m22;	m23=m.m23; }
		template<class T1> inline explicit Matrix34Tpl<T>(const Matrix44Tpl<T1>& m ){ ASSERT(m.IsValid()); m00=T(m.m00); m01=T(m.m01); m02=T(m.m02); m03=T(m.m03); m10=T(m.m10); m11=T(m.m11); m12=T(m.m12); m13=T(m.m13); m20=T(m.m20); m21=T(m.m21); m22=T(m.m22); m23=T(m.m23); }

		explicit inline Matrix34Tpl<T>( const QuatTpl<T>& q ) { *this=Matrix33Tpl<T>(q); }
		template<class T1> explicit inline Matrix34Tpl<T>( const QuatTpl<T1>& q ) { *this=Matrix33Tpl<T>(q); }
		explicit inline Matrix34Tpl<T>( const QuatTTpl<T> &q ) { *this=Matrix34Tpl<T>(Matrix33Tpl<T>(q.q),q.t); }
		template<class T1> inline explicit Matrix34Tpl( const QuatTTpl<T1> q ) { *this=Matrix34Tpl<T>(Matrix33Tpl<T1>(q.q),q.t); }

		inline explicit Matrix34Tpl<T>( const DualQuatTpl<T> &q ) 
		{
			ASSERT((AbsTpl(1-(q.nq|q.nq)))<0.01); //check if unit-quaternion
			Vector3Tpl<T>  t=(q.nq.w*q.dq.v - q.dq.w*q.nq.v + q.nq.v%q.dq.v); //perfect for HLSL
			Vector3Tpl<T> v2=q.nq.v+q.nq.v;
			T xx=1-v2.x*q.nq.v.x;  T yy=v2.y*q.nq.v.y;  T xw=v2.x*q.nq.w;
			T xy=v2.y*q.nq.v.x;    T yz=v2.z*q.nq.v.y;  T yw=v2.y*q.nq.w;
			T xz=v2.z*q.nq.v.x;    T zz=v2.z*q.nq.v.z;  T zw=v2.z*q.nq.w;
			m00=1-yy-zz;  m01=xy-zw;  m02=xz+yw;  m03=t.x+t.x;
			m10=xy+zw;    m11=xx-zz;  m12=yz-xw;  m13=t.y+t.y;
			m20=xz-yw;    m21=yz+xw;  m22=xx-yy;  m23=t.z+t.z;
		}

		template<class T1> inline explicit Matrix34Tpl<T>( const DualQuatTpl<T1> &q ) 
		{
			ASSERT((AbsTpl(1-(q.nq|q.nq)))<0.01); //check if unit-quaternion
			Vector3Tpl<T1>  t=(q.nq.w*q.dq.v - q.dq.w*q.nq.v + q.nq.v%q.dq.v); //perfect for HLSL
			Vector3Tpl<T1> v2=q.nq.v+q.nq.v;
			T1 xx=1-v2.x*q.nq.v.x;  T1 yy=v2.y*q.nq.v.y;  T1 xw=v2.x*q.nq.w;
			T1 xy=v2.y*q.nq.v.x;    T1 yz=v2.z*q.nq.v.y;  T1 yw=v2.y*q.nq.w;
			T1 xz=v2.z*q.nq.v.x;    T1 zz=v2.z*q.nq.v.z;  T1 zw=v2.z*q.nq.w;
			m00=T(1-yy-zz);  m01=T(xy-zw);  m02=T(xz+yw);  m03=T(t.x+t.x);
			m10=T(xy+zw);    m11=T(xx-zz);  m12=T(yz-xw);  m13=T(t.y+t.y);
			m20=T(xz-yw);    m21=T(yz+xw);  m22=T(xx-yy);  m23=T(t.z+t.z);
		}

		inline void ScaleColumn( const Vector3Tpl<T>& s) { m00*=s.x; m01*=s.y; m02*=s.z; m10*=s.x; m11*=s.y; m12*=s.z; m20*=s.x; m21*=s.y; m22*=s.z; }
		void SetIdentity( void ) { m00=1.0f; m01=0.0f; m02=0.0f; m03=0.0f; m10=0.0f; m11=1.0f; m12=0.0f; m13=0.0f; m20=0.0f; m21=0.0f; m22=1.0f; m23=0.0f; }
		inline static const Matrix34Tpl<T> CreateIdentity( void ) { Matrix34Tpl<T> m; m.SetIdentity(); return m; }

		inline Matrix34Tpl(ETypeIdentity){ SetIdentity(); }
		inline const bool IsIdentity() const { return CmpTpl(0,(AbsTpl(static_cast<T>(1)-m00) + AbsTpl(m01) + AbsTpl(m02) + AbsTpl(m03) + AbsTpl(m10) + AbsTpl(static_cast<T>(1)-m11) + AbsTpl(m12) + AbsTpl(m13) + AbsTpl(m20) + AbsTpl(m21) + AbsTpl(static_cast<T>(1)-m22)) + AbsTpl(m23)); }
		inline int IsZero() const {	return CmpTpl(0,(AbsTpl(m00) + AbsTpl(m01) + AbsTpl(m02) + AbsTpl(m03) + AbsTpl(m10) + AbsTpl(m11) + AbsTpl(m12) + AbsTpl(m13) + AbsTpl(m20) + AbsTpl(m21) + AbsTpl(m22)) + AbsTpl(m23)); }

		inline void SetRotationAA(const T rad, const Vector3Tpl<T>& axis, const Vector3Tpl<T>& t=Vector3Tpl<T>(ZERO) ) { *this=Matrix33Tpl<T>::CreateRotationAA(rad,axis); this->SetTranslation(t); }
		inline static const Matrix34Tpl<T> CreateRotationAA( const T rad, const Vector3Tpl<T>& axis, const Vector3Tpl<T>& t=Vector3Tpl<T>(ZERO) ){	Matrix34Tpl<T> m34;  m34.SetRotationAA(rad,axis,t); return m34; }

		inline void SetRotationAA(const Vector3Tpl<T>& rot, const Vector3Tpl<T>& t=Vector3Tpl<T>(ZERO) ) { *this=Matrix33Tpl<T>::CreateRotationAA(rot); this->SetTranslation(t); }
		inline static Matrix34Tpl<T> CreateRotationAA( const Vector3Tpl<T>& rot, const Vector3Tpl<T>& t=Vector3Tpl<T>(ZERO) ) {	Matrix34Tpl<T> m34; m34.SetRotationAA(rot,t); return m34; }

		inline void SetRotationX(const f32 rad, const Vector3Tpl<T>& t=Vector3Tpl<T>(ZERO) ) { *this=Matrix33Tpl<T>::CreateRotationX(rad); this->SetTranslation(t); }
		inline static const Matrix34Tpl<T> CreateRotationX( const f32 rad, const Vector3Tpl<T>& t=Vector3Tpl<T>(ZERO) ){ Matrix34Tpl<T> m34; m34.SetRotationX(rad,t); return m34; }
		inline void SetRotationY(const f32 rad, const Vector3Tpl<T>& t=Vector3Tpl<T>(ZERO) ) { *this=Matrix33Tpl<T>::CreateRotationY(rad);	this->SetTranslation(t); }
		inline static const Matrix34Tpl<T> CreateRotationY( const f32 rad, const Vector3Tpl<T>& t=Vector3Tpl<T>(ZERO) ){ Matrix34Tpl<T> m34; m34.SetRotationY(rad,t); return m34; }

		inline void SetRotationZ(const f32 rad, const Vector3Tpl<T>& t=Vector3Tpl<T>(ZERO) ) { *this=Matrix33Tpl<T>::CreateRotationZ(rad);  this->SetTranslation(t); }
		inline static const Matrix34Tpl<T> CreateRotationZ( const f32 rad, const Vector3Tpl<T>& t=Vector3Tpl<T>(ZERO) ){ Matrix34Tpl<T> m34;  m34.SetRotationZ(rad,t); return m34; }

		inline void SetRotationXYZ( const Angle3Tpl<T>& rad, const Vector3Tpl<T>& t=Vector3Tpl<T>(ZERO) ) { ASSERT(rad.IsValid()); ASSERT(t.IsValid()); *this=Matrix33Tpl<T>::CreateRotationXYZ(rad); this->SetTranslation(t); }
		inline static Matrix34Tpl<T> CreateRotationXYZ( const Angle3Tpl<T>& rad, const Vector3Tpl<T>& t=Vector3Tpl<T>(ZERO) ){ ASSERT(rad.IsValid()); ASSERT(t.IsValid()); Matrix34Tpl<T> m34; m34.SetRotationXYZ(rad,t);	return m34; }

		inline void SetRotationAA(const T c, const T s, Vector3Tpl<T> axis, const Vector3Tpl<T>& t=Vector3Tpl<T>(ZERO) ) { ASSERT(axis.IsValid()); ASSERT(t.IsValid()); *this=Matrix33Tpl<T>::CreateRotationAA(c, s, axis); m03=t.x; m13=t.y; m23=t.z; }
		inline static Matrix34Tpl<T> CreateRotationAA(T c, T s, Vector3Tpl<T> axis, const Vector3Tpl<T>& t=Vector3Tpl<T>(ZERO) ) {	Matrix34Tpl<T> m34;	m34.SetRotationAA(c,s,axis,t); return m34; }

		inline void SetTranslationMat( const Vector3Tpl<T>& v ) { m00=1.0f;	m01=0.0f;m02=0.0f; m03=v.x; m10=0.0f; m11=1.0f; m12=0.0f; m13=v.y; m20=0.0f; m21=0.0f; m22=1.0f; m23=v.z; }
		inline static Matrix34Tpl<T> CreateTranslationMat( const Vector3Tpl<T>& v ) { Matrix34Tpl<T> m34; m34.SetTranslationMat(v); return m34; }

		inline void SetFromVectors(const Vector3Tpl<T>& vx, const Vector3Tpl<T>& vy, const Vector3Tpl<T>& vz, const Vector3Tpl<T>& pos)	{m00=vx.x; m01=vy.x; m02=vz.x; m03 = pos.x;	m10=vx.y; m11=vy.y; m12=vz.y; m13 = pos.y; m20=vx.z; m21=vy.z; m22=vz.z; m23 = pos.z; }
		inline static Matrix34Tpl<T> CreateFromVectors(const Vector3Tpl<T>& vx, const Vector3Tpl<T>& vy, const Vector3Tpl<T>& vz, const Vector3Tpl<T>& pos) {	Matrix34Tpl<T> m; m.SetFromVectors(vx,vy,vz,pos); return m;	}

		inline void InvertFast() 
		{ 
			ASSERT(IsOrthonormal());
			T t; const Vector3Tpl<T> v(m03,m13,m23);
			t=m01; m01=m10; m10=t; m03=-v.x*m00-v.y*m01-v.z*m20;
			t=m02; m02=m20; m20=t; m13=-v.x*m10-v.y*m11-v.z*m21;
			t=m12; m12=m21; m21=t; m23=-v.x*m20-v.y*m21-v.z*m22;
		}

		const Matrix34Tpl<T> GetInvertedFast() const 
		{
			ASSERT(IsOrthonormal());
			Matrix34Tpl<T> dst;
			dst.m00=m00;  dst.m01=m10;  dst.m02=m20;  dst.m03=-m03*m00-m13*m10-m23*m20;
			dst.m10=m01;  dst.m11=m11;  dst.m12=m21;  dst.m13=-m03*m01-m13*m11-m23*m21;
			dst.m20=m02;  dst.m21=m12;  dst.m22=m22;  dst.m23=-m03*m02-m13*m12-m23*m22;
			return dst;
		}

		inline const Vector3Tpl<T> TransformVector(const Vector3Tpl<T> &v) const { ASSERT(v.IsValid());	return Vector3Tpl<T>(m00*v.x+m01*v.y+m02*v.z, m10*v.x+m11*v.y+m12*v.z, m20*v.x+m21*v.y+m22*v.z); }
		inline const Vector3Tpl<T> TransformPoint(const Vector3Tpl<T> &p) const {	ASSERT(p.IsValid()); return Vector3Tpl<T>( m00*p.x+m01*p.y+m02*p.z+m03, m10*p.x+m11*p.y+m12*p.z+m13, m20*p.x+m21*p.y+m22*p.z+m23); }

		//! Remove scale from matrix.
		void OrthonormalizeFast()
		{
			Vector3Tpl<T> x( m00,m10,m20 );
			Vector3Tpl<T> y( m01,m11,m21 );
			Vector3Tpl<T> z;
			x = x.GetNormalized();
			z = (x % y).GetNormalized();
			y = (z % x).GetNormalized();
			m00=x.x;  m10=x.y;  m20=x.z;
			m01=y.x;  m11=y.y;  m21=y.z;
			m02=z.x;  m12=z.y;  m22=z.z;
		}

		inline const f32 Determinant() const { return (m00*m11*m22) + (m01*m12*m20) + (m02*m10*m21) - (m02*m11*m20) - (m00*m12*m21) - (m01*m10*m22); }

		T *GetData() { return &m00; }
		const T *GetData() const { return &m00; }

		inline const T operator () (const uint32 i, const uint32 j) const {	ASSERT ((i<3) && (j<4)); T* p_data=reinterpret_cast<T*>(&m00); return p_data[i*4+j]; }
		inline T& operator () (const uint32 i, const uint32 j) { ASSERT ((i<3) && (j<4)); T* p_data=reinterpret_cast<T*>(&m00); return p_data[i*4+j]; }

		inline void SetRow(const uint32 i, const Vector3Tpl<T> &v) { ASSERT(i<3); T* p=reinterpret_cast<T*>(&m00); p[0+4*i]=v.x; p[1+4*i]=v.y; p[2+4*i]=v.z; }

		inline const Vector3Tpl<T>& GetRow(const uint32 i) const { ASSERT(i<3); return *reinterpret_cast<const Vector3Tpl<T>*>(&m00 + 4*i); }
		inline const Vector4Tpl<T>& GetRow4(const int32 i) const { ASSERT(i<3); return *reinterpret_cast<const Vector4Tpl<T>*>(&m00 + 4*i); }

		inline void SetColumn(const uint32 i, const Vector3Tpl<T> &v) { ASSERT(i<4); T* p=reinterpret_cast<T*>(&m00); p[i+4*0]=v.x; p[i+4*1]=v.y; p[i+4*2]=v.z; }
		inline const Vector3Tpl<T> GetColumn(const uint32 i) const { ASSERT(i<4); T* p=reinterpret_cast<T*>(&m00); return Vector3Tpl<T>(p[i+4*0],p[i+4*1],p[i+4*2]); }
		inline const Vector3Tpl<T> GetColumn0() const { return Vector3Tpl<T>(m00,m10,m20); }
		inline const Vector3Tpl<T> GetColumn1() const { return Vector3Tpl<T>(m01,m11,m21); }
		inline const Vector3Tpl<T> GetColumn2() const { return Vector3Tpl<T>(m02,m12,m22); }
		inline const Vector3Tpl<T> GetColumn3() const { return Vector3Tpl<T>(m03,m13,m23); }

		inline void SetTranslation( const Vector3Tpl<T>& t ) { m03=t.x;	m13=t.y; m23=t.z; }
		inline const Vector3Tpl<T> GetTranslation() const { return Vector3Tpl<T>(m03,m13,m23); }
		inline void ScaleTranslation (const T s){ m03*=s; m13*=s; m23*=s; }
		inline const Matrix34Tpl<T> AddTranslation( const Vector3Tpl<T>& t ){ m03+=t.x; m13+=t.y; m23+=t.z; return *this; }
		inline void SetRotation33( const Matrix33Tpl<T>& m33 ){ m00=m33.m00; m01=m33.m01; m02=m33.m02; m10=m33.m10; m11=m33.m11; m12=m33.m12; m20=m33.m20; m21=m33.m21; m22=m33.m22; }

		//check if we have an orthonormal-base (general case, works even with reflection matrices)
		int IsOrthonormal(const T threshold=0.001) const 
		{ 
			f32 d0=AbsTpl(GetColumn0()|GetColumn1()); if (d0>threshold) return 0;
			f32 d1=AbsTpl(GetColumn0()|GetColumn2()); if (d1>threshold) return 0;
			f32 d2=AbsTpl(GetColumn1()|GetColumn2()); if (d2>threshold) return 0;
			int a=(AbsTpl(1-(GetColumn0()|GetColumn0())))<threshold;
			int b=(AbsTpl(1-(GetColumn1()|GetColumn1())))<threshold;
			int c=(AbsTpl(1-(GetColumn2()|GetColumn2())))<threshold;
			return a&b&c;
		}

		//check if we have an orthonormal-base (assuming we are using a right-handed coordinate system)
		const bool IsOrthonormalRH(T threshold=0.001) const { Vector3Tpl<T>::IsEquivalent(GetColumn0(),GetColumn1()%GetColumn2(),threshold) && Vector3Tpl<T>::IsEquivalent(GetColumn1(),GetColumn2()%GetColumn0(),threshold) && Vector3Tpl<T>::IsEquivalent(GetColumn2(),GetColumn0()%GetColumn1(),threshold); }

		static const bool IsEquivalent( const Matrix34Tpl<T>& m0, const Matrix34Tpl<T>& m1, const T e=VEC_EPSILON) 
		{
			return  ( 
				(AbsTpl(m0.m00-m1.m00)<=e) && (AbsTpl(m0.m01-m1.m01)<=e) && (AbsTpl(m0.m02-m1.m02)<=e) && (AbsTpl(m0.m03-m1.m03)<=e) && 
				(AbsTpl(m0.m10-m1.m10)<=e) && (AbsTpl(m0.m11-m1.m11)<=e) && (AbsTpl(m0.m12-m1.m12)<=e) && (AbsTpl(m0.m13-m1.m13)<=e) && 
				(AbsTpl(m0.m20-m1.m20)<=e) && (AbsTpl(m0.m21-m1.m21)<=e) && (AbsTpl(m0.m22-m1.m22)<=e) && (AbsTpl(m0.m23-m1.m23)<=e) 
				);
		}

		inline const bool IsValid() const{ return NumberValid(m00) && NumberValid(m01) && NumberValid(m02) && NumberValid(m03) &&  NumberValid(m10) && NumberValid(m11) && NumberValid(m12) && NumberValid(m13) &&	NumberValid(m20) && NumberValid(m21) && NumberValid(m22) && NumberValid(m23); }

		inline void Set( const Vector3Tpl<T>& s, const QuatTpl<T>& q, const Vector3Tpl<T>& t=Vector3Tpl<T>(ZERO)  ) 
		{
			ASSERT(s.IsValid()); ASSERT(q.IsUnit(0.1f)); ASSERT(t.IsValid());
			const T vxvx=q.v.x*q.v.x;   const T vzvz=q.v.z*q.v.z;   const T vyvy=q.v.y*q.v.y; 
			const T vxvy=q.v.x*q.v.y;   const T vxvz=q.v.x*q.v.z;   const T vyvz=q.v.y*q.v.z; 
			const T svx=q.w*q.v.x;      const T svy=q.w*q.v.y;      const T svz=q.w*q.v.z;
			m00=(1-(vyvy+vzvz)*2)*s.x;  m01=(vxvy-svz)*2*s.y;       m02=(vxvz+svy)*2*s.z;       m03=t.x;
			m10=(vxvy+svz)*2*s.x;       m11=(1-(vxvx+vzvz)*2)*s.y;  m12=(vyvz-svx)*2*s.z;       m13=t.y;
			m20=(vxvz-svy)*2*s.x;       m21=(vyvz+svx)*2*s.y;       m22=(1-(vxvx+vyvy)*2)*s.z;  m23=t.z;
		}
		inline static Matrix34Tpl<T> Create(  const Vector3Tpl<T>& s, const QuatTpl<T>& q, const Vector3Tpl<T>& t=Vector3Tpl<T>(ZERO) ){	Matrix34Tpl<T> m34;	m34.Set(s,q,t); return m34;	}

		inline void SetScale( const Vector3Tpl<T> &s, const Vector3Tpl<T>& t=Vector3Tpl<T>(ZERO) ) {	*this=Matrix33Tpl<T>::CreateScale(s); this->SetTranslation(t); }
		inline static Matrix34Tpl<T> CreateScale(  const Vector3Tpl<T> &s, const Vector3Tpl<T>& t=Vector3Tpl<T>(ZERO) ) { Matrix34Tpl<T> m34; m34.SetScale(s,t); return m34;	}

		inline Matrix44Tpl<T> GetTransposed() const
		{
			Matrix44Tpl<T> tmp;
			tmp.m00=m00; tmp.m01=m10; tmp.m02=m20; tmp.m03=0;
			tmp.m10=m01; tmp.m11=m11; tmp.m12=m21; tmp.m13=0;
			tmp.m20=m02; tmp.m21=m12; tmp.m22=m22; tmp.m23=0;
			tmp.m30=m03; tmp.m31=m13; tmp.m32=m23; tmp.m33=1;
			return tmp;
		}

		inline void Invert( void ) 
		{
			Matrix34Tpl<T>	m=*this;
			m00= m.m22*m.m11-m.m12*m.m21;
			m10= m.m12*m.m20-m.m22*m.m10;
			m20= m.m10*m.m21-m.m20*m.m11;
			m01= m.m02*m.m21-m.m22*m.m01;
			m11= m.m22*m.m00-m.m02*m.m20;
			m21= m.m20*m.m01-m.m00*m.m21;
			m02= m.m12*m.m01-m.m02*m.m11;
			m12= m.m02*m.m10-m.m12*m.m00;
			m22= m.m00*m.m11-m.m10*m.m01;
			m03= (m.m22*m.m13*m.m01 + m.m02*m.m23*m.m11 + m.m12*m.m03*m.m21) - (m.m12*m.m23*m.m01 + m.m22*m.m03*m.m11 + m.m02*m.m13*m.m21);
			m13= (m.m12*m.m23*m.m00 + m.m22*m.m03*m.m10 + m.m02*m.m13*m.m20) - (m.m22*m.m13*m.m00 + m.m02*m.m23*m.m10 + m.m12*m.m03*m.m20);
			m23= (m.m20*m.m11*m.m03 + m.m00*m.m21*m.m13 + m.m10*m.m01*m.m23) - (m.m10*m.m21*m.m03 + m.m20*m.m01*m.m13 + m.m00*m.m11*m.m23);
			const T det=1.0f/(m.m00*m00+m.m10*m01+m.m20*m02);
			ASSERT( AbsTpl(det)>static_cast<T>(0.00000001) );
			m00*=det; m01*=det; m02*=det; m03*=det;
			m10*=det; m11*=det; m12*=det; m13*=det;
			m20*=det; m21*=det; m22*=det; m23*=det;
		}
		inline Matrix34Tpl<T> GetInverted() const {	Matrix34Tpl<T> dst=*this; dst.Invert(); return dst; }

		inline static Matrix34Tpl<T> CreateReflectionMat ( const Vector3Tpl<T>& p, const Vector3Tpl<T>& n )
		{
			Matrix34Tpl<T> m;
			const T vxy = -2.0f * n.x * n.y; const T vxz = -2.0f * n.x * n.z; const T vyz = -2.0f * n.y * n.z; const T pdotn = 2.0f * (p|n);
			m.m00=1.0f-2.0f*n.x*n.x;  m.m01=vxy;                m.m02=vxz;                m.m03=pdotn*n.x;
			m.m10=vxy;                m.m11=1.0f-2.0f*n.y*n.y;  m.m12=vyz;                m.m13=pdotn*n.y;
			m.m20=vxz;                m.m21=vyz;                m.m22=1.0f-2.0f*n.z*n.z;  m.m23=pdotn*n.z;
			return m;
		}

	public:
		T m00,m01,m02,m03;
		T m10,m11,m12,m13;
		T m20,m21,m22,m23;
	};

	///////////////////////////////////////////////////////////////////////////////
	// Global Operators                                                          // 
	///////////////////////////////////////////////////////////////////////////////

	template<typename T> inline const Matrix34Tpl<T> operator * (const Matrix34Tpl<T>& m, const f32 f)	
	{ 
		ASSERT(m.IsValid());
		Matrix34Tpl<T> r;
		r.m00=m.m00*f; r.m01=m.m01*f; r.m02=m.m02*f; r.m03=m.m03*f; 
		r.m10=m.m10*f; r.m11=m.m11*f; r.m12=m.m12*f; r.m13=m.m13*f;
		r.m20=m.m20*f; r.m21=m.m21*f; r.m22=m.m22*f; r.m23=m.m23*f;
		return r;
	}	

	template<typename T> inline const Vector3Tpl<T> operator * (const Matrix34Tpl<T>& m, const Vector3Tpl<T> &p) 
	{
		ASSERT(m.IsValid()); ASSERT(p.IsValid());
		Vector3Tpl<T> tp;
		tp.x = m.m00*p.x + m.m01*p.y + m.m02*p.z + m.m03;
		tp.y = m.m10*p.x + m.m11*p.y + m.m12*p.z + m.m13;
		tp.z = m.m20*p.x + m.m21*p.y + m.m22*p.z + m.m23;
		return tp;
	}

	template<typename T1, typename T2> inline Matrix34Tpl<T1>& operator += (Matrix34Tpl<T1>& l, const Matrix34Tpl<T2>& r) 
	{
		ASSERT(l.IsValid()); ASSERT(r.IsValid());
		l.m00+=r.m00; l.m01+=r.m01; l.m02+=r.m02; l.m03+=r.m03; 
		l.m10+=r.m10; l.m11+=r.m11; l.m12+=r.m12; l.m13+=r.m13;
		l.m20+=r.m20; l.m21+=r.m21; l.m22+=r.m22; l.m23+=r.m23;
		return l;
	}

	template<typename T> inline const Matrix34Tpl<T> operator * (const Matrix34Tpl<T>& l, const Matrix33Tpl<T>& r) 
	{
		ASSERT(l.IsValid()); ASSERT(r.IsValid());
		Matrix34Tpl<T> m;
		m.m00 = l.m00*r.m00 + l.m01*r.m10 + l.m02*r.m20;
		m.m10 = l.m10*r.m00 + l.m11*r.m10 + l.m12*r.m20;
		m.m20 = l.m20*r.m00 + l.m21*r.m10 + l.m22*r.m20;
		m.m01 = l.m00*r.m01 + l.m01*r.m11 + l.m02*r.m21;
		m.m11 = l.m10*r.m01 + l.m11*r.m11 + l.m12*r.m21;
		m.m21 = l.m20*r.m01 + l.m21*r.m11 + l.m22*r.m21;
		m.m02 = l.m00*r.m02 + l.m01*r.m12 + l.m02*r.m22;
		m.m12 = l.m10*r.m02 + l.m11*r.m12 + l.m12*r.m22;
		m.m22 = l.m20*r.m02 + l.m21*r.m12 + l.m22*r.m22;
		m.m03 = l.m03;
		m.m13 = l.m13;
		m.m23 = l.m23;
		return m;
	}

	template<typename T> inline const Matrix34Tpl<T> operator * (const Matrix34Tpl<T>& l, const Matrix34Tpl<T>& r) 
	{
		ASSERT(l.IsValid()); ASSERT(r.IsValid());
		Matrix34Tpl<T> m;
		m.m00 = l.m00*r.m00 + l.m01*r.m10 + l.m02*r.m20;
		m.m10 = l.m10*r.m00 + l.m11*r.m10 + l.m12*r.m20;
		m.m20 = l.m20*r.m00 + l.m21*r.m10 + l.m22*r.m20;
		m.m01 = l.m00*r.m01 + l.m01*r.m11 + l.m02*r.m21;
		m.m11 = l.m10*r.m01 + l.m11*r.m11 + l.m12*r.m21;
		m.m21 = l.m20*r.m01 + l.m21*r.m11 + l.m22*r.m21;
		m.m02 = l.m00*r.m02 + l.m01*r.m12 + l.m02*r.m22;
		m.m12 = l.m10*r.m02 + l.m11*r.m12 + l.m12*r.m22;
		m.m22 = l.m20*r.m02 + l.m21*r.m12 + l.m22*r.m22;
		m.m03 = l.m00*r.m03 + l.m01*r.m13 + l.m02*r.m23 + l.m03;
		m.m13 = l.m10*r.m03 + l.m11*r.m13 + l.m12*r.m23 + l.m13;
		m.m23 = l.m20*r.m03 + l.m21*r.m13 + l.m22*r.m23 + l.m23;
		return m;
	}

	template<typename T> inline Matrix44Tpl<T> operator * (const Matrix34Tpl<T>& l, const Matrix44Tpl<T>& r) {
		ASSERT(l.IsValid()); ASSERT(r.IsValid());
		Matrix44Tpl<T> m;
		m.m00 = l.m00*r.m00 + l.m01*r.m10 + l.m02*r.m20 + l.m03*r.m30;
		m.m10 = l.m10*r.m00 + l.m11*r.m10 + l.m12*r.m20 + l.m13*r.m30;
		m.m20 = l.m20*r.m00 + l.m21*r.m10 + l.m22*r.m20 + l.m23*r.m30;
		m.m30 = r.m30;
		m.m01 = l.m00*r.m01 + l.m01*r.m11 + l.m02*r.m21 + l.m03*r.m31;
		m.m11 = l.m10*r.m01 + l.m11*r.m11 + l.m12*r.m21 + l.m13*r.m31;
		m.m21 = l.m20*r.m01 + l.m21*r.m11 + l.m22*r.m21 + l.m23*r.m31;
		m.m31 = r.m31;
		m.m02 = l.m00*r.m02 + l.m01*r.m12 + l.m02*r.m22 + l.m03*r.m32;
		m.m12 = l.m10*r.m02 + l.m11*r.m12 + l.m12*r.m22 + l.m13*r.m32;
		m.m22 = l.m20*r.m02 + l.m21*r.m12 + l.m22*r.m22 + l.m23*r.m32;
		m.m32 = r.m32;
		m.m03 = l.m00*r.m03 + l.m01*r.m13 + l.m02*r.m23 + l.m03*r.m33;
		m.m13 = l.m10*r.m03 + l.m11*r.m13 + l.m12*r.m23 + l.m13*r.m33;
		m.m23 = l.m20*r.m03 + l.m21*r.m13 + l.m22*r.m23 + l.m23*r.m33;
		m.m33 = r.m33;
		return m;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Typedefs                                                                  //
	///////////////////////////////////////////////////////////////////////////////

	typedef Matrix34Tpl<f32> Matrix34f;
	typedef Matrix34Tpl<f64> Matrix34d;
}
