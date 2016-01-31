#pragma once

namespace MathUtils
{

	template<typename T> struct Matrix33Tpl
	{
		inline Matrix33Tpl(){};
		inline Matrix33Tpl<T>& operator = (const Matrix33Tpl<T>& m) { ASSERT(m.IsValid()); m00=m.m00;	m01=m.m01; m02=m.m02; m10=m.m10;	m11=m.m11;	m12=m.m12; m20=m.m20;	m21=m.m21;	m22=m.m22; return *this; }
		explicit inline Matrix33Tpl<T>(const T x00, const T x01, const T x02, const T x10, const T x11, const T x12, const T x20, const T x21, const T x22) {	m00 = x00; m01 = x01; m02 = x02; m10 = x10; m11 = x11; m12 = x12; m20 = x20; m21 = x21; m22 = x22; }
		explicit inline Matrix33Tpl<T>(const Vector3Tpl<T>& vx, const Vector3Tpl<T>& vy, const Vector3Tpl<T>& vz){ m00=vx.x;	m01=vy.x;	m02=vz.x; m10=vx.y;	m11=vy.y;	m12=vz.y;	m20=vx.z;	m21=vy.z;	m22=vz.z; }
		template<class T1> explicit inline Matrix33Tpl<T>(const Vector3Tpl<T1>& vx, const Vector3Tpl<T1>& vy, const Vector3Tpl<T1>& vz)	{	m00=T(vx.x); m01=T(vy.x);	m02=T(vz.x); m10=T(vx.y);	m11=T(vy.y); m12=T(vz.y);	m20=T(vx.z); m21=T(vy.z);	m22=T(vz.z); }
		inline Matrix33Tpl<T>(const Matrix33Tpl<T>& m) { ASSERT(m.IsValid()); m00=m.m00;	m01=m.m01;	m02=m.m02; m10=m.m10;	m11=m.m11;	m12=m.m12; m20=m.m20;	m21=m.m21;	m22=m.m22; }
		template<class T1> inline Matrix33Tpl<T>(const Matrix33Tpl<T1>& m) { ASSERT(m.IsValid());	m00=T(m.m00);	m01=T(m.m01);	m02=T(m.m02); m10=T(m.m10);	m11=T(m.m11);	m12=T(m.m12);	m20=T(m.m20);	m21=T(m.m21);	m22=T(m.m22); }
		explicit inline Matrix33Tpl<T>(const Matrix34Tpl<T>& m ) {	ASSERT(m.IsValid()); m00=m.m00;	m01=m.m01; m02=m.m02;	m10=m.m10; m11=m.m11;	m12=m.m12; m20=m.m20;	m21=m.m21; m22=m.m22;	}
		template<class T1> explicit inline Matrix33Tpl<T>(const Matrix34Tpl<T1>& m )	{	ASSERT(m.IsValid()); m00=T(m.m00); m01=T(m.m01); m02=T(m.m02); m10=T(m.m10); m11=T(m.m11); m12=T(m.m12); m20=T(m.m20); m21=T(m.m21); m22=T(m.m22); }

		explicit inline Matrix33Tpl<T>(const Matrix44Tpl<T>& m ){	ASSERT(m.IsValid()); m00=m.m00; m01=m.m01; m02=m.m02; m10=m.m10;	m11=m.m11; m12=m.m12; m20=m.m20;	m21=m.m21; m22=m.m22; }
		template<class T1> explicit inline Matrix33Tpl<T>(const Matrix44Tpl<T1>& m ) { ASSERT(m.IsValid());	m00=T(m.m00);	m01=T(m.m01);	m02=T(m.m02); m10=T(m.m10);	m11=T(m.m11);	m12=T(m.m12);	m20=T(m.m20);	m21=T(m.m21);	m22=T(m.m22); }

		explicit inline Matrix33Tpl<T>(const QuatTpl<T>& q) 
		{
			ASSERT(q.IsValid(0.05f));
			const Vector3Tpl<T> v2=q.v+q.v;
			const T xx=1-v2.x*q.v.x;    const T yy=v2.y*q.v.y;   const T xw=v2.x*q.w;
			const T xy=v2.y*q.v.x;      const T yz=v2.z*q.v.y;   const T yw=v2.y*q.w;
			const T xz=v2.z*q.v.x;      const T zz=v2.z*q.v.z;   const T zw=v2.z*q.w;
			m00=1-yy-zz;                m01=xy-zw;               m02=xz+yw;
			m10=xy+zw;                  m11=xx-zz;               m12=yz-xw;
			m20=xz-yw;                  m21=yz+xw;               m22=xx-yy;
		}

		template<class T1> explicit inline Matrix33Tpl<T>( const QuatTpl<T1>& q) 
		{
			ASSERT(q.IsValid(0.05f));
			Vector3Tpl<T1> v2=q.v+q.v;
			const T1 xx=1-v2.x*q.v.x;   const T1 yy=v2.y*q.v.y;     const T1 xw=v2.x*q.w;
			const T1 xy=v2.y*q.v.x;     const T1 yz=v2.z*q.v.y;     const T1 yw=v2.y*q.w;
			const T1 xz=v2.z*q.v.x;     const T1 zz=v2.z*q.v.z;     const T1 zw=v2.z*q.w;
			m00=T(1-yy-zz);             m01=T(xy-zw);               m02=T(xz+yw);
			m10=T(xy+zw);               m11=T(xx-zz);               m12=T(yz-xw);
			m20=T(xz-yw);               m21=T(yz+xw);               m22=T(xx-yy);
		}

		explicit inline Matrix33Tpl<T>( const Angle3Tpl<T>& ang ) { ASSERT(ang.IsValid()); SetRotationXYZ(ang); }
		template<class T1> explicit inline Matrix33Tpl<T>( const Angle3Tpl<T1>& ang ) { ASSERT(ang.IsValid()); SetRotationXYZ( Angle3Tpl<T>(T(ang.x),T(ang.y),T(ang.z)) ); }

		inline void SetIdentity(void) { m00=1; m01=0; m02=0; m10=0;	m11=1; m12=0;	m20=0; m21=0; m22=1; }
		inline static Matrix33Tpl<T> CreateIdentity() {	Matrix33Tpl<T> m33;	m33.SetIdentity(); return m33; }
		inline Matrix33Tpl(ETypeIdentity) { SetIdentity(); }
		inline void SetZero() { m00=0; m01=0; m02=0; m10=0;	m11=0; m12=0; m20=0;	m21=0; m22=0; }

		inline void SetRotationAA(const T angle, const Vector3Tpl<T> axis) { T s,c; SinCosTpl(angle,&s,&c);	SetRotationAA(c,s,axis); }
		inline static Matrix33Tpl<T> CreateRotationAA( const T rad, const Vector3Tpl<T>& axis ){ Matrix33Tpl<T> m33;	m33.SetRotationAA(rad,axis); return m33; }

		inline void SetRotationAA(const T c, const T s, const Vector3Tpl<T>& axis) 
		{ 
			ASSERT(axis.IsUnit(0.001f));
			const T	mc	=	1-c;
			m00=mc*axis.x*axis.x + c;           m01=mc*axis.x*axis.y - axis.z*s;  m02=mc*axis.x*axis.z + axis.y*s;
			m10 = mc*axis.y*axis.x + axis.z*s;  m11 = mc*axis.y*axis.y + c;       m12 = mc*axis.y*axis.z - axis.x*s;
			m20=mc*axis.z*axis.x - axis.y*s;    m21=mc*axis.z*axis.y + axis.x*s;  22=mc*axis.z*axis.z + c;
		}

		inline static const Matrix33Tpl<T> CreateRotationAA(const T c, const T s, const Vector3Tpl<T>& axis) { Matrix33Tpl<T> m33;	m33.SetRotationAA(c,s,axis); return m33; }
		inline void SetRotationAA(const Vector3Tpl<T> axis) { const T angle = axis.GetLength();	if (CmpTpl(angle,T(0)))	SetIdentity(); else SetRotationAA(angle, axis / angle); }
		inline static const Matrix33Tpl<T> CreateRotationAA(const Vector3Tpl<T>& axis) { Matrix33Tpl<T> m33;	m33.SetRotationAA(axis); return m33; }

		inline void SetRotationX(const T rad ) { T s,c; SinCosTpl(rad,&s,&c);	m00=1.0f;	m01=0.0f;	m02=0.0f;	m10=0.0f;	m11=c; m12=-s; m20=0.0f; m21=s;	m22= c; }
		inline static const Matrix33Tpl<T> CreateRotationX(const T rad ) {	Matrix33Tpl<T> m33; m33.SetRotationX(rad); return m33;	}

		inline void SetRotationY(const T rad ) { T s,c; SinCosTpl(rad,&s,&c); m00	=	c; m01 = 0;	m02	=	s; m10 = 0; m11	=	1; m12 =	0; m20=-s; m21 = 0;	m22	= c; }
		inline static const Matrix33Tpl<T> CreateRotationY(const T rad ) { Matrix33Tpl<T> m33; m33.SetRotationY(rad);	return m33;	}

		inline void SetRotationZ( const f32 rad ) {	T s,c; SinCosTpl(rad,&s,&c); m00 = c;	m01	=-s; m02 = 0.0f; m10 = s; m11 = c; m12 = 0.0f; m20 = 0.0f; m21 = 0.0f; m22 = 1.0f; }
		inline static const Matrix33Tpl<T> CreateRotationZ(const f32 rad) {	Matrix33Tpl<T> m33;	m33.SetRotationZ(rad);	return m33;	}

		inline void SetRotationXYZ( const Angle3Tpl<T>& rad ) 
		{
			ASSERT(rad.IsValid());
			T sx,cx;  SinCosTpl(rad.x,&sx,&cx);
			T sy,cy;  SinCosTpl(rad.y,&sy,&cy);
			T sz,cz;  SinCosTpl(rad.z,&sz,&cz);
			T sycz  =(sy*cz), sysz  =(sy*sz);
			m00=cy*cz;  m01=sycz*sx-cx*sz;  m02=sycz*cx+sx*sz;
			m10=cy*sz;  m11=sysz*sx+cx*cz;  m12=sysz*cx-sx*cz;
			m20=-sy;    m21=cy*sx;          m22=cy*cx;
		}

		inline static const Matrix33Tpl<T> CreateRotationXYZ( const Angle3Tpl<T>& rad ) {	ASSERT(rad.IsValid()); Matrix33Tpl<T> m33;	m33.SetRotationXYZ(rad); return m33; }

		inline void SetRotationV0V1( const Vector3Tpl<T>& v0, const Vector3Tpl<T>& v1 ) 
		{
			ASSERT((AbsTpl(1-(v0|v0)))<0.01); //check if unit-vector
			ASSERT((AbsTpl(1-(v1|v1)))<0.01); //check if unit-vector
			const T dot = v0|v1;
			if ( dot < T(-0.9999f) )	
			{
				const Vector3Tpl<T> axis = v0.GetOrthogonal().GetNormalized(); 
				m00=T(2*axis.x*axis.x-1);  m01=T(2*axis.x*axis.y);    m02=T(2*axis.x*axis.z);
				m10=T(2*axis.y*axis.x);    m11=T(2*axis.y*axis.y-1);  m12=T(2*axis.y*axis.z);
				m20=T(2*axis.z*axis.x);    m21=T(2*axis.z*axis.y);    m22=T(2*axis.z*axis.z-1);
			}	
			else	
			{
				const Vector3Tpl<T> v = v0%v1;
				const T h = 1/(1 + dot);
				m00=T(dot+h*v.x*v.x);    m01=T(h*v.x*v.y-v.z);    m02=T(h*v.x*v.z+v.y);
				m10=T(h*v.x*v.y+v.z);    m11=T(dot+h*v.y*v.y);    m12=T(h*v.y*v.z-v.x);
				m20=T(h*v.x*v.z-v.y);    m21=T(h*v.y*v.z+v.x);    m22=T(dot+h*v.z*v.z);
			}
		}

		inline static const Matrix33Tpl<T> CreateRotationV0V1( const Vector3Tpl<T>& v0, const Vector3Tpl<T>& v1 ) {	Matrix33Tpl<T> m33;	m33.SetRotationV0V1(v0,v1); return m33;	}

		inline void SetRotationVDir( const Vector3Tpl<T>& vdir ) 
		{
			ASSERT((AbsTpl(1-(vdir|vdir)))<0.01); //check if unit-vector
			m00=1;  m01=0;       m02=0;
			m10=0;  m11=0;       m12=-vdir.z;
			m20=0;  m21=vdir.z;  m22=0;
			const T len = SqrtTpl(vdir.x*vdir.x+vdir.y*vdir.y);
			if (len > T(0.00001) )
			{
				const T xl=-vdir.x/len; 
				const T yl=vdir.y/len;
				m00=T(yl);  m01=T(vdir.x);  m02=T(xl*vdir.z);
				m10=T(xl);  m11=T(vdir.y);  m12=T(-vdir.z*yl);
				m20=0;      m21=T(vdir.z);  m22=T(len);
			}
		}

		inline static Matrix33Tpl<T> CreateRotationVDir( const Vector3Tpl<T> vdir ) {	Matrix33Tpl<T> m33;	m33.SetRotationVDir(vdir); return m33; }

		inline void SetRotationVDir( const Vector3Tpl<T>& vdir, const T roll ) 
		{
			SetRotationVDir( vdir );
			T s,c; SinCosTpl(roll,&s,&c);
			const T x00=m00,x10=m10;
			m00=m00*c-m02*s;  m02=x00*s+m02*c;
			m10=m10*c-m12*s;  m12=x10*s+m12*c;
			m20=-m22*s;       m22=m22*c;
		}

		inline static const Matrix33Tpl<T> CreateRotationVDir( const Vector3Tpl<T>& vdir, const T roll  ) {	Matrix33Tpl<T> m33;	m33.SetRotationVDir(vdir,roll ); return m33; }

		inline static const Matrix33Tpl<T> CreateOrthogonalBase( const Vector3Tpl<T>& invDirection )
		{
			Vector3Tpl<T> outvA = (invDirection.z<-0.5f || invDirection.z>0.5f)? outvA=Vec3(invDirection.z,invDirection.y,-invDirection.x) : outvA=Vec3(invDirection.y,-invDirection.x,invDirection.z);
			const Vector3Tpl<T> outvB = (invDirection % outvA).GetNormalized();
			outvA = (invDirection % outvB).GetNormalized();
			return CreateFromVectors(invDirection,outvA,outvB);
		}

		inline static const Matrix33Tpl<T> CreateOrientation( const Vector3Tpl<T>& dir,const Vector3Tpl<T>& up,const float rollAngle )
		{
			// LookAt transform.
			Vector3Tpl<T> xAxis,yAxis,zAxis;
			const Vector3Tpl<T> upVector = up;
			if (dir.IsZeroFast()) {	Matrix33Tpl<T> tm; tm.SetIdentity(); return tm;	}
			yAxis = dir.GetNormalized();
			if (yAxis.x == 0 && yAxis.y == 0 && up.IsEquivalent(Vector3Tpl<T>(0,0,1.0f))) upVector.Set( -yAxis.z,0,0 );

			xAxis = (upVector % yAxis).GetNormalized();
			zAxis = (xAxis % yAxis).GetNormalized();

			Matrix33Tpl<T> tm;
			tm.SetFromVectors( xAxis,yAxis,zAxis );

			if (rollAngle != 0)
			{
				Matrix33Tpl<T> RollMtx;
				RollMtx.SetRotationY(rollAngle);
				tm = tm * RollMtx;
			}
			return tm;
		}

		inline void SetSlerp( const Matrix33Tpl<T>& m, const Matrix33Tpl<T>& n, const T t)
		{
			ASSERT(m.IsValid());
			ASSERT(n.IsValid());
			//calculate delta-rotation between m and n (=39 flops)
			Matrix33Tpl<T> d,i;
			d.m00=m.m00*n.m00+m.m10*n.m10+m.m20*n.m20;  d.m01=m.m00*n.m01+m.m10*n.m11+m.m20*n.m21;  d.m02=m.m00*n.m02+m.m10*n.m12+m.m20*n.m22;
			d.m10=m.m01*n.m00+m.m11*n.m10+m.m21*n.m20;  d.m11=m.m01*n.m01+m.m11*n.m11+m.m21*n.m21;  d.m12=m.m01*n.m02+m.m11*n.m12+m.m21*n.m22;
			d.m20=d.m01*d.m12-d.m02*d.m11;              d.m21=d.m02*d.m10-d.m00*d.m12;              d.m22=d.m00*d.m11-d.m01*d.m10;
			ASSERT( d.IsOrthonormalRH(0.0001f) );

			Vector3Tpl<T> axis(d.m21-d.m12,d.m02-d.m20,d.m10-d.m01);
			T l = sqrt(axis|axis);	if (l>T(0.00001) ) axis/=l;	else axis(1,0,0); 
			i.SetRotationAA(acos(clamp((d.m00+d.m11+d.m22-1)*0.5f,-1,+1))*t,axis); //angle interpolation and calculation of new delta-matrix (=26 flops) 

			//final concatenation (=39 flops)
			m00=T(m.m00*i.m00+m.m01*i.m10+m.m02*i.m20);  m01=T(m.m00*i.m01+m.m01*i.m11+m.m02*i.m21);  m02=T(m.m00*i.m02+m.m01*i.m12+m.m02*i.m22);
			m10=T(m.m10*i.m00+m.m11*i.m10+m.m12*i.m20);  m11=T(m.m10*i.m01+m.m11*i.m11+m.m12*i.m21);  m12=T(m.m10*i.m02+m.m11*i.m12+m.m12*i.m22);
			m20=m01*m12-m02*m11;                         m21=m02*m10-m00*m12;                         m22=m00*m11-m01*m10;
			ASSERT( this->IsOrthonormalRH(0.0001f) );
		}

		inline static const Matrix33Tpl<T> CreateSlerp( const Matrix33Tpl<T> m, const Matrix33Tpl<T> n, const T t) {	Matrix33Tpl<T> m33;	m33.SetSlerp(m,n,t); return m33; }
		inline void SetScale( const Vector3Tpl<T>& s ) { m00=s.x; m01=0; m02=0;	m10=0; m11=s.y; m12=0; m20=0;	m21=0; m22=s.z; }
		inline static const Matrix33Tpl<T> CreateScale( const Vector3Tpl<T> &s  ) { Matrix33Tpl<T> m; m.SetScale(s);	return m;	}

		inline void SetFromVectors(const Vector3Tpl<T>& vx, const Vector3Tpl<T>& vy, const Vector3Tpl<T>& vz)	{	m00=vx.x;	m01=vy.x;	m02=vz.x; m10=vx.y;	m11=vy.y;	m12=vz.y;	m20=vx.z;	m21=vy.z;	m22=vz.z; }
		inline static const Matrix33Tpl<T> CreateFromVectors( const Vector3Tpl<T>& vx, const Vector3Tpl<T>& vy, const Vector3Tpl<T>& vz ) {	Matrix33Tpl<T> dst; dst.SetFromVectors(vx,vy,vz); return dst;	}

		inline void Transpose() { T t; t=m01; m01=m10; m10=t;	t=m02; m02=m20; m20=t; t=m12; m12=m21; m21=t;	}
		inline const Matrix33Tpl<T> GetTransposed() const {	Matrix33Tpl<T> dst;	dst.m00=m00; dst.m01=m10;	dst.m02=m20; dst.m10=m01; dst.m11=m11; dst.m12=m21;	dst.m20=m02; dst.m21=m12;	dst.m22=m22; return dst; }

		inline Matrix33Tpl& Fabs() { m00=AbsTpl(m00); m01=AbsTpl(m01);	m02=AbsTpl(m02); m10=AbsTpl(m10); m11=AbsTpl(m11); m12=AbsTpl(m12); m20=AbsTpl(m20); m21=AbsTpl(m21);	m22=AbsTpl(m22); return *this; }
		inline Matrix33Tpl<T> GetFabs() const {	Matrix33Tpl<T> m=*this; m.Fabs();	return m;	}

		inline void Adjoint( void ) 
		{  
			Matrix33Tpl<T> m=*this;
			m00=m.m11*m.m22-m.m12*m.m21;  m01=m.m12*m.m20-m.m10*m.m22;  m02=m.m10*m.m21-m.m11*m.m20;
			m10=m.m21*m.m02-m.m22*m.m01;  m11=m.m22*m.m00-m.m20*m.m02;  m12=m.m20*m.m01-m.m21*m.m00;
			m20=m.m01*m.m12-m.m02*m.m11;  m21=m.m02*m.m10-m.m00*m.m12;  m22=m.m00*m.m11-m.m01*m.m10;
		}
		inline Matrix33Tpl<T> GetAdjoint() const {	Matrix33Tpl<T> dst=*this; dst.Adjoint(); return dst;	}

		inline const bool Invert( void ) 
		{  
			Matrix33Tpl<T>	m=*this;
			m00=m.m22*m.m11-m.m12*m.m21;  m01=m.m02*m.m21-m.m22*m.m01;  m02=m.m12*m.m01-m.m02*m.m11;
			m10=m.m12*m.m20-m.m22*m.m10;  m11=m.m22*m.m00-m.m02*m.m20;  m12=m.m02*m.m10-m.m12*m.m00;
			m20=m.m10*m.m21-m.m20*m.m11;  m21=m.m20*m.m01-m.m00*m.m21;  m22=m.m00*m.m11-m.m10*m.m01;
			const T det=(m.m00*m00 + m.m10*m01 + m.m20*m02);
			if (AbsTpl(det)<1E-20f) return 0;	
			const T idet=(T)1.0/det;
			m00*=idet;  m01*=idet;  m02*=idet;
			m10*=idet;  m11*=idet;  m12*=idet;
			m20*=idet;  m21*=idet;  m22*=idet;
			return 1;
		}

		inline const Matrix33Tpl<T> GetInverted() const {	Matrix33Tpl<T> dst=*this; dst.Invert(); return dst;	}
		inline const Vector3Tpl<T> TransformVector(const Vector3Tpl<T> &v) const { return Vector3Tpl<T>(m00*v.x+m01*v.y+m02*v.z, m10*v.x+m11*v.y+m12*v.z, m20*v.x+m21*v.y+m22*v.z); }

		inline void OrthonormalizeFast()
		{
			const Vector3Tpl<T> x = Vec3(m00,m10,m20).GetNormalized();
			const Vector3Tpl<T> y = (Vec3(m02,m12,m22)%x).GetNormalized();
			const Vector3Tpl<T> z = (x%y);
			m00=x.x;  m01=y.x;  m02=z.x;
			m10=x.y;  m11=y.y;  m12=z.y;
			m20=x.z;  m21=y.z;  m22=z.z;
		}

		inline const f32 Determinant() const { return (m00*m11*m22) + (m01*m12*m20) + (m02*m10*m21) - (m02*m11*m20) - (m00*m12*m21) - (m01*m10*m22); }

		T* GetData() { return &m00; }
		const T* GetData() const { return &m00; }

		inline T operator () (const uint32 i, const uint32 j) const {	ASSERT ((i<3) && (j<3));	const T* const p_data=reinterpret_cast<const T*>(&m00); 	return p_data[i*3+j];	}
		inline T& operator () (const uint32 i, const uint32 j)	{	ASSERT ((i<3) && (j<3));	T* p_data=reinterpret_cast<T*>(&m00);		return p_data[i*3+j];	}
		inline void SetRow(const uint32 i, const Vector3Tpl<T> &v)	{	ASSERT(i<3);	T* p=reinterpret_cast<T*>(&m00);	p[0+3*i]=v.x;	p[1+3*i]=v.y;	p[2+3*i]=v.z;		}
		inline const Vector3Tpl<T> GetRow(const uint32 i) const	{	ASSERT(i<3);	const T* const p=reinterpret_cast<const T*>(&m00);	return Vector3Tpl<T>(p[0+3*i],p[1+3*i],p[2+3*i]);	}
		inline void SetColumn(const uint32 i, const Vector3Tpl<T> &v)	{	ASSERT(i<3);	T* p=reinterpret_cast<T*>(&m00);	p[i+3*0]=v.x;	p[i+3*1]=v.y;	p[i+3*2]=v.z;		}
		inline const Vector3Tpl<T> GetColumn(const uint32 i) const	{	ASSERT(i<3u);	const T* const p=reinterpret_cast<const T*>(&m00);	return Vector3Tpl<T>(p[i+3*0],p[i+3*1],p[i+3*2]);	}

		inline const Vector3Tpl<T> GetColumn0() const { return Vector3Tpl<T> (m00,m10,m20);	}
		inline const Vector3Tpl<T> GetColumn1() const { return Vector3Tpl<T> (m01,m11,m21);	}
		inline const Vector3Tpl<T> GetColumn2() const { return Vector3Tpl<T> (m02,m12,m22);	}
		inline void SetColumn0(const Vector3Tpl<T>& v) { m00=v.x; m10=v.y; m20=v.z;	}
		inline void SetColumn1(const Vector3Tpl<T>& v) { m01=v.x; m11=v.y; m21=v.z;	}
		inline void SetColumn2(const Vector3Tpl<T>& v) { m02=v.x; m12=v.y; m22=v.z;	}

		inline Matrix33Tpl<T>& operator *= (const T op) { m00*=op; m01*=op;	m02*=op; m10*=op; m11*=op;	m12*=op; m20*=op; m21*=op;	m22*=op; return *this; }

		inline Matrix33Tpl<T>& operator /= (const T op) {	const T iop=static_cast<T>(1.0/op);	m00*=iop; m01*=iop;	m02*=iop;	m10*=iop; m11*=iop;	m12*=iop;	m20*=iop; m21*=iop;	m22*=iop;	return *this;	}

		inline static const bool IsEquivalent( const Matrix33Tpl<T>& m0, const Matrix33Tpl<T>& m1, const T e=VEC_EPSILON) 
		{
			return  ( 
				(AbsTpl(m0.m00-m1.m00)<=e) && (AbsTpl(m0.m01-m1.m01)<=e) && (AbsTpl(m0.m02-m1.m02)<=e) && 
				(AbsTpl(m0.m10-m1.m10)<=e) && (AbsTpl(m0.m11-m1.m11)<=e) && (AbsTpl(m0.m12-m1.m12)<=e) && 
				(AbsTpl(m0.m20-m1.m20)<=e) && (AbsTpl(m0.m21-m1.m21)<=e) && (AbsTpl(m0.m22-m1.m22)<=e) 
				);
		}

		inline bool IsIdentity() const	{ return 0 == (AbsTpl(static_cast<T>(1)-m00)+AbsTpl(m01)+AbsTpl(m02)+AbsTpl(m10)+AbsTpl(static_cast<T>(1)-m11)+AbsTpl(m12)+AbsTpl(m20)+AbsTpl(m21)+AbsTpl(static_cast<T>(1)-m22)); }
		inline int IsZero() const { return 0 == (AbsTpl(m00)+AbsTpl(m01)+AbsTpl(m02)+AbsTpl(m10)+AbsTpl(m11)+AbsTpl(m12)+AbsTpl(m20)+AbsTpl(m21)+AbsTpl(m22)); }

		inline const bool IsOrthonormal(const T threshold=0.001) const 
		{ 
			const f32 d0=AbsTpl(GetColumn0()|GetColumn1()); if (d0>threshold) return 0;
			const f32 d1=AbsTpl(GetColumn0()|GetColumn2()); if (d1>threshold) return 0;
			const f32 d2=AbsTpl(GetColumn1()|GetColumn2()); if (d2>threshold) return 0;
			const bool a=(AbsTpl(1-(GetColumn0()|GetColumn0())))<threshold;
			const bool b=(AbsTpl(1-(GetColumn1()|GetColumn1())))<threshold;
			const bool c=(AbsTpl(1-(GetColumn2()|GetColumn2())))<threshold;
			return a&&b&&c;
		}

		inline int IsOrthonormalRH(const T threshold=0.002) const 
		{ 
			const Vector3Tpl<T> x=GetColumn0();
			const Vector3Tpl<T> y=GetColumn1();
			const Vector3Tpl<T> z=GetColumn2();
			return x.IsEquivalent(y%z,threshold) && y.IsEquivalent(z%x,threshold) && z.IsEquivalent(x%y,threshold) && x.IsUnit(threshold) && y.IsUnit(threshold) && z.IsUnit(threshold);
		}

		inline void NoScale()	{ *this /= GetColumn(0).GetLength(); }
		inline bool IsValid() const { return NumberValid(m00) && NumberValid(m01) && NumberValid(m02) && NumberValid(m10) && NumberValid(m11) && NumberValid(m12) && NumberValid(m20) && NumberValid(m21) && NumberValid(m22); }

	public:

		T m00,m01,m02;
		T m10,m11,m12;
		T m20,m21,m22;
	};

	///////////////////////////////////////////////////////////////////////////////
	// Global Operators                                                          // 
	///////////////////////////////////////////////////////////////////////////////

	template<typename T1, typename T2> inline const Matrix33Tpl<T1> operator * (const Matrix33Tpl<T1>& l, const Matrix33Tpl<T2>& r) 
	{
		ASSERT(l.IsValid());	ASSERT(r.IsValid());
		Matrix33Tpl<T1> m;
		m.m00 = l.m00*r.m00 + l.m01*r.m10 + l.m02*r.m20;  m.m01 = l.m00*r.m01 + l.m01*r.m11 + l.m02*r.m21;  m.m02 = l.m00*r.m02 + l.m01*r.m12 + l.m02*r.m22;
		m.m10 = l.m10*r.m00 + l.m11*r.m10 + l.m12*r.m20;  m.m11 = l.m10*r.m01 + l.m11*r.m11 + l.m12*r.m21;  m.m12 = l.m10*r.m02 + l.m11*r.m12 + l.m12*r.m22;
		m.m20 = l.m20*r.m00 + l.m21*r.m10 + l.m22*r.m20;  m.m21 = l.m20*r.m01 + l.m21*r.m11 + l.m22*r.m21;  m.m22 = l.m20*r.m02 + l.m21*r.m12 + l.m22*r.m22;
		return m;
	}

	template<typename T1, typename T2> inline const Matrix34Tpl<T2> operator * (const Matrix33Tpl<T1>& l, const Matrix34Tpl<T2>& r) 
	{
		ASSERT(l.IsValid());	ASSERT(r.IsValid());
		Matrix34Tpl<T2> m;
		m.m00 = l.m00*r.m00 + l.m01*r.m10 + l.m02*r.m20;  m.m10 = l.m10*r.m00 + l.m11*r.m10 + l.m12*r.m20;  m.m20 = l.m20*r.m00 + l.m21*r.m10 + l.m22*r.m20;
		m.m01 = l.m00*r.m01 + l.m01*r.m11 + l.m02*r.m21;  m.m11 = l.m10*r.m01 + l.m11*r.m11 + l.m12*r.m21;  m.m21 = l.m20*r.m01 + l.m21*r.m11 + l.m22*r.m21;
		m.m02 = l.m00*r.m02 + l.m01*r.m12 + l.m02*r.m22;  m.m12 = l.m10*r.m02 + l.m11*r.m12 + l.m12*r.m22;  m.m22 = l.m20*r.m02 + l.m21*r.m12 + l.m22*r.m22;
		m.m03 = l.m00*r.m03 + l.m01*r.m13 + l.m02*r.m23;  m.m13 = l.m10*r.m03 + l.m11*r.m13 + l.m12*r.m23;  m.m23 = l.m20*r.m03 + l.m21*r.m13 + l.m22*r.m23;
		return m;
	}

	template<typename T1, typename T2> inline const Matrix44Tpl<T2> operator * (const Matrix33Tpl<T1>& l, const Matrix44Tpl<T2>& r) 
	{
		ASSERT(l.IsValid());	ASSERT(r.IsValid());
		Matrix44Tpl<T2> m;
		m.m00 = l.m00*r.m00 + l.m01*r.m10 + l.m02*r.m20;  m.m10 = l.m10*r.m00 + l.m11*r.m10 + l.m12*r.m20;  m.m20 = l.m20*r.m00 + l.m21*r.m10 + l.m22*r.m20;  m.m30 = r.m30;
		m.m01 = l.m00*r.m01 + l.m01*r.m11 + l.m02*r.m21;  m.m11 = l.m10*r.m01 + l.m11*r.m11 + l.m12*r.m21;  m.m21 = l.m20*r.m01 + l.m21*r.m11 + l.m22*r.m21;  m.m31 = r.m31;
		m.m02 = l.m00*r.m02 + l.m01*r.m12 + l.m02*r.m22;  m.m12 = l.m10*r.m02 + l.m11*r.m12 + l.m12*r.m22;  m.m22 = l.m20*r.m02 + l.m21*r.m12 + l.m22*r.m22;  m.m32 = r.m32;
		m.m03 = l.m00*r.m03 + l.m01*r.m13 + l.m02*r.m23;  m.m13 = l.m10*r.m03 + l.m11*r.m13 + l.m12*r.m23;  m.m23 = l.m20*r.m03 + l.m21*r.m13 + l.m22*r.m23;  m.m33 = r.m33;
		return m;
	}

	template<typename T1, typename T2> inline Matrix33Tpl<T1>& operator *= (Matrix33Tpl<T1>& l,	const Matrix33Tpl<T2>& r) 
	{
		ASSERT(l.IsValid());	ASSERT(r.IsValid());
		Matrix33Tpl<T1> tmp;
		tmp.m00 = l.m00*r.m00 + l.m01*r.m10 + l.m02*r.m20;  tmp.m01 = l.m00*r.m01 + l.m01*r.m11 + l.m02*r.m21; tmp.m02 = l.m00*r.m02 + l.m01*r.m12 + l.m02*r.m22;
		tmp.m10 = l.m10*r.m00 + l.m11*r.m10 + l.m12*r.m20;  tmp.m11 = l.m10*r.m01 + l.m11*r.m11 + l.m12*r.m21; tmp.m12 = l.m10*r.m02 + l.m11*r.m12 + l.m12*r.m22;
		tmp.m20 = l.m20*r.m00 + l.m21*r.m10 + l.m22*r.m20;  tmp.m21 = l.m20*r.m01 + l.m21*r.m11 + l.m22*r.m21; tmp.m22 = l.m20*r.m02 + l.m21*r.m12 + l.m22*r.m22;
		l=tmp;
		return l;
	}

	template<typename T1, typename T2> inline const Matrix33Tpl<T1> operator+(const Matrix33Tpl<T1>& l, const Matrix33Tpl<T2>& r) 
	{
		ASSERT(l.IsValid()); ASSERT(r.IsValid());
		Matrix33Tpl<T1> res;
		res.m00=l.m00+r.m00; res.m01=l.m01+r.m01; res.m02=l.m02+r.m02; res.m10=l.m10+r.m10; res.m11=l.m11+r.m11; res.m12=l.m12+r.m12; res.m20=l.m20+r.m20; res.m21=l.m21+r.m21; res.m22=l.m22+r.m22; 
		return res;
	}

	template<typename T1, typename T2> inline Matrix33Tpl<T1>& operator+=(Matrix33Tpl<T1>& l,	const Matrix33Tpl<T2>& r) 
	{
		ASSERT(l.IsValid()); ASSERT(r.IsValid());
		l.m00+=r.m00; l.m01+=r.m01; l.m02+=r.m02; l.m10+=r.m10; l.m11+=r.m11; l.m12+=r.m12; l.m20+=r.m20; l.m21+=r.m21; l.m22+=r.m22; 
		return l;
	}

	template<typename T1, typename T2> inline const Matrix33Tpl<T1> operator - (const Matrix33Tpl<T1>& l, const Matrix33Tpl<T2>& r) 
	{
		ASSERT(l.IsValid()); ASSERT(r.IsValid());
		Matrix33Tpl<T1> res;
		res.m00 = l.m00-r.m00; res.m01 = l.m01-r.m01; res.m02 = l.m02-r.m02; res.m10 = l.m10-r.m10; res.m11 = l.m11-r.m11; res.m12 = l.m12-r.m12; res.m20 = l.m20-r.m20; res.m21 = l.m21-r.m21; res.m22 = l.m22-r.m22; 
		return res;
	}
	template<typename T1, typename T2> 
	inline Matrix33Tpl<T1>& operator-=(Matrix33Tpl<T1>& l, const Matrix33Tpl<T2>& r) 
	{
		ASSERT(l.IsValid()); ASSERT(r.IsValid());
		l.m00-=r.m00; l.m01-=r.m01; l.m02-=r.m02; l.m10-=r.m10; l.m11-=r.m11; l.m12-=r.m12; l.m20-=r.m20; l.m21-=r.m21; l.m22-=r.m22; 
		return l;
	}

	template<typename T> inline const Matrix33Tpl<T> operator*(const Matrix33Tpl<T>& m, const T op) 
	{
		ASSERT(m.IsValid());
		Matrix33Tpl<T> res;
		res.m00=m.m00*op; res.m01=m.m01*op; res.m02=m.m02*op; res.m10=m.m10*op; res.m11=m.m11*op; res.m12=m.m12*op; res.m20=m.m20*op; res.m21=m.m21*op;	res.m22=m.m22*op;
		return res;
	}

	template<class T> inline const Matrix33Tpl<T> operator/(const Matrix33Tpl<T>& src, const T op) { return src*(static_cast<T>(1.0/op)); }

	//post-multiply
	template<typename T1, typename T2> inline Vector3Tpl<T1> operator*(const Matrix33Tpl<T2>& m, const Vector3Tpl<T1>& p) 
	{
		ASSERT(m.IsValid()); ASSERT(p.IsValid());
		Vector3Tpl<T1> tp;
		tp.x = T1(m.m00*p.x + m.m01*p.y + m.m02*p.z); tp.y = T1(m.m10*p.x + m.m11*p.y + m.m12*p.z); tp.z = T1(m.m20*p.x + m.m21*p.y + m.m22*p.z);
		return tp;
	}

	template<typename T1, typename T2> inline const Vector3Tpl<T1> operator*(const Vector3Tpl<T1>& p, const Matrix33Tpl<T2>& m) 
	{
		ASSERT(m.IsValid()); ASSERT(p.IsValid());
		Vector3Tpl<T1> tp;
		tp.x = T1(p.x*m.m00 + p.y*m.m10 + p.z*m.m20); tp.y = T1(p.x*m.m01 + p.y*m.m11 + p.z*m.m21); tp.z = T1(p.x*m.m02 + p.y*m.m12 + p.z*m.m22);
		return tp;
	}

	template<class T1, class T2> inline const Vector2Tpl<T1> operator*(const Matrix33Tpl<T2>& m, const Vector2Tpl<T1>& v) { ASSERT(m.IsValid()); ASSERT(v.IsValid()); return Vector2Tpl<T1>(v.x*m.m00+v.y*m.m01,   v.x*m.m10 + v.y*m.m11); }
	template<class T1, class T2> inline const Vector2Tpl<T1> operator*(const Vector2Tpl<T1>& v, const Matrix33Tpl<T2>& m) { ASSERT(m.IsValid()); ASSERT(v.IsValid()); return Vector2Tpl<T1>(v.x*m.m00 + v.y*m.m10, v.x*m.m01 + v.y*m.m11); }

	template<class T1> inline Matrix33Tpl<T1>& CrossProductMatrix(const Vector3Tpl<T1>& v, Matrix33Tpl<T1>& m) {	m.m00=0; m.m01=-v.z; m.m02=v.y;	m.m10=v.z; m.m11=0; m.m12=-v.x; m.m20=-v.y; m.m21=v.x; m.m22=0;	return m; }
	template<class T1> inline Matrix33Tpl<T1>& DotProductMatrix(const Vector3Tpl<T1>& v, const Vector3Tpl<T1>& op, Matrix33Tpl<T1>& m) 
	{	
		m.m00=v.x*op.x; m.m10=v.y*op.x; m.m20=v.z*op.x; m.m01=v.x*op.y; m.m11=v.y*op.y; m.m21=v.z*op.y; m.m02=v.x*op.z; m.m12=v.y*op.z; m.m22=v.z*op.z; 
		return m; 
	}

	///////////////////////////////////////////////////////////////////////////////
	// Typedefs                                                                  //
	///////////////////////////////////////////////////////////////////////////////

	typedef Matrix33Tpl<f32> Matrix33f;
	typedef Matrix33Tpl<f64> Matrix33d;
}