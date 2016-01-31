#pragma once

namespace MathUtils
{
	template<typename T> struct Matrix44Tpl
	{
		
		inline Matrix44Tpl(){}

		inline Matrix44Tpl<T>& operator = (const Matrix44Tpl<T> &m) { ASSERT(m.IsValid()); m00=m.m00;	m01=m.m01;	m02=m.m02; m03=m.m03; m10=m.m10;	m11=m.m11;	m12=m.m12; m13=m.m13; m20=m.m20;	m21=m.m21;	m22=m.m22; m23=m.m23; m30=m.m30;	m31=m.m31;	m32=m.m32; m33=m.m33; return *this; }

		inline Matrix44Tpl<T>( const T v00, const T v01, const T v02, const T v03,	const T v10, const T v11, const T v12, const T v13, const T v20, const T v21, const T v22, const T v23,	const T v30, const T v31, const T v32, const T v33)
		{ 	
			m00=v00; m01=v01; m02=v02; m03=v03; m10=v10; m11=v11; m12=v12; m13=v13; m20=v20; m21=v21; m22=v22; m23=v23; m30=v30; m31=v31; m32=v32; m33=v33; 
		}

		inline Matrix44Tpl<T>(const Matrix33Tpl<T>& m ) { ASSERT(m.IsValid()); m00=m.m00; m01=m.m01; m02=m.m02; m03=0; m10=m.m10; m11=m.m11; m12=m.m12; m13=0; m20=m.m20; m21=m.m21; m22=m.m22; m23=0; m30=0; m31=0; m32=0; m33=1; }
		template<class T1> inline Matrix44Tpl<T>(const Matrix33Tpl<T1>& m ) { ASSERT(m.IsValid()); m00=T(m.m00); m01=T(m.m01); m02=T(m.m02); m03=0; m10=T(m.m10); m11=T(m.m11);	m12=T(m.m12); m13=0; m20=T(m.m20); m21=T(m.m21); m22=T(m.m22); m23=0; m30=0; m31=0; m32=0; m33=1;}
		inline Matrix44Tpl<T>(const Matrix34Tpl<T>& m ) { ASSERT(m.IsValid()); m00=m.m00; m01=m.m01; m02=m.m02; m03=m.m03; m10=m.m10; m11=m.m11; m12=m.m12; m13=m.m13; m20=m.m20; m21=m.m21; m22=m.m22; m23=m.m23; m30=0; m31=0; m32=0; m33=1; }
		template<class T1> inline Matrix44Tpl<T>(const Matrix34Tpl<T1>& m ) { ASSERT(m.IsValid()); m00=T(m.m00); m01=T(m.m01); m02=T(m.m02); m03=T(m.m03); m10=T(m.m10); m11=T(m.m11); m12=T(m.m12); m13=T(m.m13); m20=T(m.m20); m21=T(m.m21); m22=T(m.m22); m23=T(m.m23); m30=0; m31=0; m32=0; m33=1;}
		inline Matrix44Tpl<T>(const Matrix44Tpl<T>& m ) { ASSERT(m.IsValid()); m00=m.m00; m01=m.m01; m02=m.m02; m03=m.m03; m10=m.m10; m11=m.m11; m12=m.m12; m13=m.m13; m20=m.m20; m21=m.m21; m22=m.m22; m23=m.m23; m30=m.m30; m31=m.m31; m32=m.m32;	m33=m.m33; }
		template<class T1> inline Matrix44Tpl<T>(const Matrix44Tpl<T1>& m ) { ASSERT(m.IsValid()); m00=T(m.m00); m01=T(m.m01); m02=T(m.m02); m03=T(m.m03); m10=T(m.m10); m11=T(m.m11); m12=T(m.m12); m13=T(m.m13); m20=T(m.m20); m21=T(m.m21); m22=T(m.m22); m23=T(m.m23); m30=T(m.m30); m31=T(m.m31); m32=T(m.m32); m33=T(m.m33); }

		friend inline const Matrix44Tpl<T> operator * (const Matrix44Tpl<T>& m, const T f)
		{ 
			ASSERT(m.IsValid());
			Matrix44Tpl<T> r;
			r.m00=m.m00*f; r.m01=m.m01*f; r.m02=m.m02*f; r.m03=m.m03*f; 
			r.m10=m.m10*f; r.m11=m.m11*f; r.m12=m.m12*f; r.m13=m.m13*f; 
			r.m20=m.m20*f; r.m21=m.m21*f; r.m22=m.m22*f; r.m23=m.m23*f; 
			r.m30=m.m30*f; r.m31=m.m31*f; r.m32=m.m32*f; r.m33=m.m33*f;
			return r;
		}	

		friend inline const Matrix44Tpl<T> operator + (const Matrix44Tpl<T>& mm0, const Matrix44Tpl<T>& mm1)
		{ 
			ASSERT(mm0.IsValid()); ASSERT(mm1.IsValid());
			Matrix44Tpl<T> r;
			r.m00=mm0.m00 + mm1.m00; r.m01=mm0.m01 + mm1.m01; r.m02=mm0.m02 + mm1.m02; r.m03=mm0.m03 + mm1.m03; 
			r.m10=mm0.m10 + mm1.m10; r.m11=mm0.m11 + mm1.m11; r.m12=mm0.m12 + mm1.m12; r.m13=mm0.m13 + mm1.m13;
			r.m20=mm0.m20 + mm1.m20; r.m21=mm0.m21 + mm1.m21; r.m22=mm0.m22 + mm1.m22; r.m23=mm0.m23 + mm1.m23;
			r.m30=mm0.m30 + mm1.m30; r.m31=mm0.m31 + mm1.m31; r.m32=mm0.m32 + mm1.m32; r.m33=mm0.m33 + mm1.m33;
			return r;
		}	

		inline void SetIdentity()	
		{
			m00=1; m01=0; m02=0; m03=0;
			m10=0; m11=1; m12=0; m13=0;
			m20=0; m21=0; m22=1; m23=0;
			m30=0; m31=0; m32=0; m33=1;
		}

		inline Matrix44Tpl(ETypeIdentity) { SetIdentity(); }

		inline void Transpose()
		{
			Matrix44Tpl<T> tmp=*this;
			m00=tmp.m00; m01=tmp.m10; m02=tmp.m20; m03=tmp.m30;
			m10=tmp.m01; m11=tmp.m11; m12=tmp.m21; m13=tmp.m31;
			m20=tmp.m02; m21=tmp.m12; m22=tmp.m22; m23=tmp.m32;
			m30=tmp.m03; m31=tmp.m13; m32=tmp.m23; m33=tmp.m33;
		}

		inline const Matrix44Tpl<T> GetTransposed() const {	Matrix44Tpl<T> tmp;	tmp.Transpose(); return tmp; }
		
		void Invert( void ) 
		{
			Matrix44Tpl<T>	m=*this;
			// Calculate pairs for first 8 elements (cofactors)
			T	tmp[12] = {m.m22 * m.m33, m.m32 * m.m23, m.m12 * m.m33, m.m32 * m.m13, m.m12 * m.m23, m.m22 * m.m13, m.m02 * m.m33, m.m32 * m.m03, m.m02 * m.m23, m.m22 * m.m03, m.m02 * m.m13, m.m12 * m.m03 };

			// Calculate first 8 elements (cofactors)
			m00 = tmp[0]*m.m11 + tmp[3]*m.m21 + tmp[ 4]*m.m31;
			m00-= tmp[1]*m.m11 + tmp[2]*m.m21 + tmp[ 5]*m.m31;
			m01 = tmp[1]*m.m01 + tmp[6]*m.m21 + tmp[ 9]*m.m31;
			m01-= tmp[0]*m.m01 + tmp[7]*m.m21 + tmp[ 8]*m.m31;
			m02 = tmp[2]*m.m01 + tmp[7]*m.m11 + tmp[10]*m.m31;
			m02-= tmp[3]*m.m01 + tmp[6]*m.m11 + tmp[11]*m.m31;
			m03 = tmp[5]*m.m01 + tmp[8]*m.m11 + tmp[11]*m.m21;
			m03-= tmp[4]*m.m01 + tmp[9]*m.m11 + tmp[10]*m.m21;
			m10 = tmp[1]*m.m10 + tmp[2]*m.m20 + tmp[ 5]*m.m30;
			m10-= tmp[0]*m.m10 + tmp[3]*m.m20 + tmp[ 4]*m.m30;
			m11 = tmp[0]*m.m00 + tmp[7]*m.m20 + tmp[ 8]*m.m30;
			m11-= tmp[1]*m.m00 + tmp[6]*m.m20 + tmp[ 9]*m.m30;
			m12 = tmp[3]*m.m00 + tmp[6]*m.m10 + tmp[11]*m.m30;
			m12-= tmp[2]*m.m00 + tmp[7]*m.m10 + tmp[10]*m.m30;
			m13 = tmp[4]*m.m00 + tmp[9]*m.m10 + tmp[10]*m.m20;
			m13-= tmp[5]*m.m00 + tmp[8]*m.m10 + tmp[11]*m.m20;

			// Calculate pairs for second 8 elements (cofactors)
			tmp[ 0] = m.m20*m.m31;
			tmp[ 1] = m.m30*m.m21;
			tmp[ 2] = m.m10*m.m31;
			tmp[ 3] = m.m30*m.m11;
			tmp[ 4] = m.m10*m.m21;
			tmp[ 5] = m.m20*m.m11;
			tmp[ 6] = m.m00*m.m31;
			tmp[ 7] = m.m30*m.m01;
			tmp[ 8] = m.m00*m.m21;
			tmp[ 9] = m.m20*m.m01;
			tmp[10] = m.m00*m.m11;
			tmp[11] = m.m10*m.m01;

			// Calculate second 8 elements (cofactors)
			m20 = tmp[ 0]*m.m13 + tmp[ 3]*m.m23 + tmp[ 4]*m.m33;
			m20-= tmp[ 1]*m.m13 + tmp[ 2]*m.m23 + tmp[ 5]*m.m33;
			m21 = tmp[ 1]*m.m03 + tmp[ 6]*m.m23 + tmp[ 9]*m.m33;
			m21-= tmp[ 0]*m.m03 + tmp[ 7]*m.m23 + tmp[ 8]*m.m33;
			m22 = tmp[ 2]*m.m03 + tmp[ 7]*m.m13 + tmp[10]*m.m33;
			m22-= tmp[ 3]*m.m03 + tmp[ 6]*m.m13 + tmp[11]*m.m33;
			m23 = tmp[ 5]*m.m03 + tmp[ 8]*m.m13 + tmp[11]*m.m23;
			m23-= tmp[ 4]*m.m03 + tmp[ 9]*m.m13 + tmp[10]*m.m23;
			m30 = tmp[ 2]*m.m22 + tmp[ 5]*m.m32 + tmp[ 1]*m.m12;
			m30-= tmp[ 4]*m.m32 + tmp[ 0]*m.m12 + tmp[ 3]*m.m22;
			m31 = tmp[ 8]*m.m32 + tmp[ 0]*m.m02 + tmp[ 7]*m.m22;
			m31-= tmp[ 6]*m.m22 + tmp[ 9]*m.m32 + tmp[ 1]*m.m02;
			m32 = tmp[ 6]*m.m12 + tmp[11]*m.m32 + tmp[ 3]*m.m02;
			m32-= tmp[10]*m.m32 + tmp[ 2]*m.m02 + tmp[ 7]*m.m12;
			m33 = tmp[10]*m.m22 + tmp[ 4]*m.m02 + tmp[ 9]*m.m12;
			m33-= tmp[ 8]*m.m12 + tmp[11]*m.m22 + tmp[ 5]*m.m02;

			const T det=(m.m00*m00+m.m10*m01+m.m20*m02+m.m30*m03);
			ASSERT( !CmpTpl(AbsTpl(det),static_cast<T>(0)));

			const T idet=static_cast<T>(1.0/det);
			m00*=idet; m01*=idet; m02*=idet; m03*=idet;
			m10*=idet; m11*=idet; m12*=idet; m13*=idet;
			m20*=idet; m21*=idet; m22*=idet; m23*=idet;
			m30*=idet; m31*=idet; m32*=idet; m33*=idet;
		}
		
		inline Matrix44Tpl<T> GetInverted() const { Matrix44Tpl<T> dst=*this; dst.Invert(); return dst; }

		inline const T Determinant() const { return (m00*m11*m22) + (m01*m12*m20) + (m02*m10*m21) - (m02*m11*m20) - (m00*m12*m21) - (m01*m10*m22); }

		inline Vector3Tpl<T> TransformVector(const Vector3Tpl<T>& b) const { ASSERT(b.IsValid()); return Vector3Tpl<T>(m00*b.x + m01*b.y + m02*b.z,m10*b.x + m11*b.y + m12*b.z,m20*b.x + m21*b.y + m22*b.z); }
		inline Vector3Tpl<T> TransformPoint(const Vector3Tpl<T>& b) const { ASSERT(b.IsValid()); return Vector3Tpl<T>(m00*b.x + m01*b.y + m02* b.z + m03,m10*b.x + m11*b.y + m12* b.z + m13,m20*b.x + m21*b.y + m22* b.z + m23); }
		
		inline T *GetData() { return &m00; }
		inline const T *GetData() const { return &m00; }

		inline const T operator ()  (const uint32 i, const uint32 j) const { ASSERT ((i<4u) && (j<4u)); T* p_data=reinterpret_cast<T*>(&m00); return p_data[i*4+j]; }
		inline T& operator () (const uint32 i, const uint32 j) { ASSERT ((i<4u) && (j<4u)); T* p_data=reinterpret_cast<T*>(&m00); return p_data[i*4+j]; }

		inline void SetRow(const uint32 i, const Vector3Tpl<T> &v)  { ASSERT(i<4u); T* p=reinterpret_cast<T*>(&m00); p[0+4*i]=v.x; p[1+4*i]=v.y; p[2+4*i]=v.z; }
		inline void SetRow4(const uint32 i, const Vector4Tpl<T> &v) { ASSERT(i<4u); T* p=reinterpret_cast<T*>(&m00); p[0+4*i]=v.x; p[1+4*i]=v.y; p[2+4*i]=v.z; p[3+4*i]=v.w; }
		inline const Vector3Tpl<T>& GetRow(const uint32 i) const    { ASSERT(i<4u); return *reinterpret_cast<const Vector3Tpl<T>*>(&m00 + 4*i); }

		inline void SetColumn(const uint32 i, const Vector3Tpl<T> &v) { ASSERT(i<4u); T* p=reinterpret_cast<T*>(&m00); p[i+4*0]=v.x; p[i+4*1]=v.y; p[i+4*2]=v.z;         }
		inline const Vector3Tpl<T> GetColumn(const uint32 i) const    { ASSERT(i<4u); const T* p=reinterpret_cast<const T*>(&m00); return Vector3Tpl<T>(p[i+4*0],p[i+4*1],p[i+4*2]); }
		inline const Vector4Tpl<T> GetColumn4(const uint32 i) const   { ASSERT(i<4u); const T* p=reinterpret_cast<const T*>(&m00); return Vec4(p[i+4*0],p[i+4*1],p[i+4*2],p[i+4*3]); }

		inline const Vector3Tpl<T> GetTranslation() const { return Vector3Tpl<T>( m03, m13, m23 ); }
		inline void SetTranslation( const Vector3Tpl<T>& t ) { m03=t.x; m13=t.y; m23=t.z; }

    inline const Vector3Tpl<T>& GetFront() const { return *reinterpret_cast<const Vector3Tpl<T>*>(&m00 + 4 * 2); }
    inline const Vector3Tpl<T>& GetLeft() const { return *reinterpret_cast<const Vector3Tpl<T>*>(&m00 + 4 * 0); }
    inline const Vector3Tpl<T>& GetUp() const { return *reinterpret_cast<const Vector3Tpl<T>*>(&m00 + 4 * 1); }

    inline void SetScale(const T s) {
      m00 = s;  m01 = 0;  m02 = 0;  m03 = 0;
      m10 = 0;  m11 = s;  m12 = 0;  m13 = 0;
      m20 = 0;  m21 = 0;  m22 = s;  m23 = 0;
      m30 = 0;  m31 = 0;  m32 = 0;  m33 = 1;
    }

    inline void SetScale(const Vector3Tpl<T>& s) { 
      m00 = s.x;  m01 = 0;    m02 = 0;    m03 = 0;
      m10 = 0;    m11 = s.y;  m12 = 0;    m13 = 0;
      m20 = 0;    m21 = 0;    m22 = s.x;  m23 = 0;
      m30 = 0;    m31 = 0;    m32 = 0;    m33 = 1;
    }
    
		bool IsValid() const { return NumberValid(m00) && NumberValid(m01) && NumberValid(m02) && NumberValid(m03) && NumberValid(m10) && NumberValid(m11) && NumberValid(m12) && NumberValid(m13) && NumberValid(m20) && NumberValid(m21) && NumberValid(m22) && NumberValid(m23) && NumberValid(m30) && NumberValid(m31) && NumberValid(m32) && NumberValid(m33); }
		static bool IsEquivalent( const Matrix44Tpl<T>& m0, const Matrix44Tpl<T>& m1, const T e=VEC_EPSILON) 
		{
			return  ( 
				(AbsTpl(m0.m00-m1.m00)<=e) && (AbsTpl(m0.m01-m1.m01)<=e) && (AbsTpl(m0.m02-m1.m02)<=e) && (AbsTpl(m0.m03-m1.m03)<=e) && 
				(AbsTpl(m0.m10-m1.m10)<=e) && (AbsTpl(m0.m11-m1.m11)<=e) && (AbsTpl(m0.m12-m1.m12)<=e) && (AbsTpl(m0.m13-m1.m13)<=e) && 
				(AbsTpl(m0.m20-m1.m20)<=e) && (AbsTpl(m0.m21-m1.m21)<=e) && (AbsTpl(m0.m22-m1.m22)<=e) && (AbsTpl(m0.m23-m1.m23)<=e) &&
				(AbsTpl(m0.m30-m1.m30)<=e) && (AbsTpl(m0.m31-m1.m31)<=e) && (AbsTpl(m0.m32-m1.m32)<=e) && (AbsTpl(m0.m33-m1.m33)<=e) 
				);
		}
		
	public:
		T m00,m01,m02,m03;
		T m10,m11,m12,m13;
		T m20,m21,m22,m23;
		T m30,m31,m32,m33;
	};
	
		///////////////////////////////////////////////////////////////////////////////
		// Global Operators                                                          // 
		///////////////////////////////////////////////////////////////////////////////

		template<typename T1,  typename T2> inline const Matrix44Tpl<T1> operator * (const Matrix44Tpl<T1>& l, const Matrix33Tpl<T2>& r) 
		{
			ASSERT(l.IsValid()); ASSERT(r.IsValid());
			Matrix44Tpl<T1> m;
			m.m00 =l.m00*r.m00 + l.m01*r.m10 + l.m02*r.m20;
			m.m10 =l.m10*r.m00 + l.m11*r.m10 + l.m12*r.m20;
			m.m20 =l.m20*r.m00 + l.m21*r.m10 + l.m22*r.m20;
			m.m30 =l.m30*r.m00 + l.m31*r.m10 + l.m32*r.m20;
			m.m01 =l.m00*r.m01 + l.m01*r.m11 + l.m02*r.m21;
			m.m11 =l.m10*r.m01 + l.m11*r.m11 + l.m12*r.m21;
			m.m21 =l.m20*r.m01 + l.m21*r.m11 + l.m22*r.m21;
			m.m31 =l.m30*r.m01 + l.m31*r.m11 + l.m32*r.m21;
			m.m02 =l.m00*r.m02 + l.m01*r.m12 + l.m02*r.m22;
			m.m12 =l.m10*r.m02 + l.m11*r.m12 + l.m12*r.m22;
			m.m22 =l.m20*r.m02 + l.m21*r.m12 + l.m22*r.m22;
			m.m32 =l.m30*r.m02 + l.m31*r.m12 + l.m32*r.m22;
			m.m03 =l.m03;
			m.m13 =l.m13;
			m.m23 =l.m23;
			m.m33 =l.m33;
			return m;
		}

		template<typename T> inline Matrix44Tpl<T> operator * (const Matrix44Tpl<T>& l, const Matrix34Tpl<T>& r) 
		{
			ASSERT(l.IsValid()); ASSERT(r.IsValid());
			Matrix44Tpl<T> m;
			m.m00 = l.m00*r.m00 + l.m01*r.m10 + l.m02*r.m20;
			m.m10 = l.m10*r.m00 + l.m11*r.m10 + l.m12*r.m20;
			m.m20 = l.m20*r.m00 + l.m21*r.m10 + l.m22*r.m20;
			m.m30 = l.m30*r.m00 + l.m31*r.m10 + l.m32*r.m20;
			m.m01 = l.m00*r.m01 + l.m01*r.m11 + l.m02*r.m21;
			m.m11 = l.m10*r.m01 + l.m11*r.m11 + l.m12*r.m21;
			m.m21 = l.m20*r.m01 + l.m21*r.m11 + l.m22*r.m21;
			m.m31 = l.m30*r.m01 + l.m31*r.m11 + l.m32*r.m21;
			m.m02 = l.m00*r.m02 + l.m01*r.m12 + l.m02*r.m22;
			m.m12 = l.m10*r.m02 + l.m11*r.m12 + l.m12*r.m22;
			m.m22 = l.m20*r.m02 + l.m21*r.m12 + l.m22*r.m22;
			m.m32 = l.m30*r.m02 + l.m31*r.m12 + l.m32*r.m22;
			m.m03 = l.m00*r.m03 + l.m01*r.m13 + l.m02*r.m23 + l.m03;
			m.m13 = l.m10*r.m03 + l.m11*r.m13 + l.m12*r.m23 + l.m13;
			m.m23 = l.m20*r.m03 + l.m21*r.m13 + l.m22*r.m23 + l.m23;
			m.m33 = l.m30*r.m03 + l.m31*r.m13 + l.m32*r.m23 + l.m33;
			return m;
		}	

		template<typename T1, typename T2> inline Matrix44Tpl<T1> operator * (const Matrix44Tpl<T1>& l, const Matrix44Tpl<T2>& r)
		{
			ASSERT(l.IsValid()); ASSERT(r.IsValid());
			Matrix44Tpl<T1> res;
			res.m00 = l.m00*r.m00 + l.m01*r.m10 + l.m02*r.m20 + l.m03*r.m30;
			res.m10 = l.m10*r.m00 + l.m11*r.m10 + l.m12*r.m20 + l.m13*r.m30;
			res.m20 = l.m20*r.m00 + l.m21*r.m10 + l.m22*r.m20 + l.m23*r.m30;
			res.m30 = l.m30*r.m00 + l.m31*r.m10 + l.m32*r.m20 + l.m33*r.m30;
			res.m01 = l.m00*r.m01 + l.m01*r.m11 + l.m02*r.m21 + l.m03*r.m31;
			res.m11 = l.m10*r.m01 + l.m11*r.m11 + l.m12*r.m21 + l.m13*r.m31;
			res.m21 = l.m20*r.m01 + l.m21*r.m11 + l.m22*r.m21 + l.m23*r.m31;
			res.m31 = l.m30*r.m01 + l.m31*r.m11 + l.m32*r.m21 + l.m33*r.m31;
			res.m02 = l.m00*r.m02 + l.m01*r.m12 + l.m02*r.m22 + l.m03*r.m32;
			res.m12 = l.m10*r.m02 + l.m11*r.m12 + l.m12*r.m22 + l.m13*r.m32;
			res.m22 = l.m20*r.m02 + l.m21*r.m12 + l.m22*r.m22 + l.m23*r.m32;
			res.m32 = l.m30*r.m02 + l.m31*r.m12 + l.m32*r.m22 + l.m33*r.m32;
			res.m03 = l.m00*r.m03 + l.m01*r.m13 + l.m02*r.m23 + l.m03*r.m33;
			res.m13 = l.m10*r.m03 + l.m11*r.m13 + l.m12*r.m23 + l.m13*r.m33;
			res.m23 = l.m20*r.m03 + l.m21*r.m13 + l.m22*r.m23 + l.m23*r.m33;
			res.m33 = l.m30*r.m03 + l.m31*r.m13 + l.m32*r.m23 + l.m33*r.m33;
			return res;
		}

		template<typename T1, typename T2> inline const Vector4Tpl<T1> operator*(const Matrix44Tpl<T2> &m, const Vector4Tpl<T1> &v) { ASSERT(m.IsValid()); ASSERT(v.IsValid()); return Vector4Tpl<T1>(v.x*m.m00 + v.y*m.m01 + v.z*m.m02 + v.w*m.m03, v.x*m.m10 + v.y*m.m11 + v.z*m.m12 + v.w*m.m13, v.x*m.m20 + v.y*m.m21 + v.z*m.m22 + v.w*m.m23, v.x*m.m30 + v.y*m.m31 + v.z*m.m32 + v.w*m.m33); }
		template<typename T1, typename T2> inline const Vector4Tpl<T1> operator*(const Vector4Tpl<T1> &v, const Matrix44Tpl<T2> &m) { ASSERT(m.IsValid()); ASSERT(v.IsValid()); return Vector4Tpl<T1>(v.x*m.m00 + v.y*m.m10 + v.z*m.m20 + v.w*m.m30, v.x*m.m01 + v.y*m.m11 + v.z*m.m21 + v.w*m.m31, v.x*m.m02 + v.y*m.m12 + v.z*m.m22 + v.w*m.m32, v.x*m.m03 + v.y*m.m13 + v.z*m.m23 + v.w*m.m33); }

		///////////////////////////////////////////////////////////////////////////////
		// Typedefs                                                                  //
		///////////////////////////////////////////////////////////////////////////////

		typedef Matrix44Tpl<f32> Matrix44f;
		typedef Matrix44Tpl<f64> Matrix44d;
}