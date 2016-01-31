#pragma once

namespace MathUtils
{
	// Static values declaration

	template<typename T> struct QuatTpl;
	template<typename T> struct QuatTTpl;

	template<typename T> struct QuatConstants
	{
		static QuatTpl<T> zero;
		static QuatTpl<T> identity;
	};

	template<typename T> struct QuatTConstants
	{
		static QuatTTpl<T> zero;
		static QuatTTpl<T> identity;
	};

	template <typename T> struct QuatTpl
	{
		inline QuatTpl() {}

		//The assignment operator has precedence over assignment constructor 
		inline QuatTpl<T>& operator = (const QuatTpl<T> &src){ v.x=src.v.x; v.y=src.v.y; v.z=src.v.z; w=src.w; return *this; }
		inline QuatTpl<T>( const T qw, const T qx, const T qy, const T qz):v(qx,qy,qz),w(qw){ ASSERT(IsValid()); }
		inline QuatTpl<T>( const T scalar, const Vector3Tpl<T>& vector):v(vector),w(scalar){ ASSERT(IsValid()); };
		inline QuatTpl<T>( const QuatTpl<T>& q ) { ASSERT(q.IsValid()); w=q.w; v.x=q.v.x; v.y=q.v.y; v.z=q.v.z; ASSERT(IsValid()); }
		template <class T1> inline  QuatTpl<T>( const QuatTpl<T1>& q ) { ASSERT(q.IsValid()); w=T(q.w); v.x=T(q.v.x); v.y=T(q.v.y); v.z=T(q.v.z); ASSERT(IsValid()); }
	
		//Needs to be 'explicit' because we loose fp-precision in the conversion process 
		explicit inline QuatTpl<T>( const Angle3Tpl<T>& ang ){ ASSERT(ang.IsValid());	SetRotationXYZ(ang); }
		template<class T1> explicit inline QuatTpl<T>( const Angle3Tpl<T1>& ang ){ ASSERT(ang.IsValid());	SetRotationXYZ( Angle3Tpl<T>(T(ang.x),T(ang.y),T(ang.z)));	}
	
		explicit inline QuatTpl<T>(const Matrix33Tpl<T>& m)
		{ 
			ASSERT( m.IsOrthonormalRH(0.1f) );
			T s,p,tr = m.m00 + m.m11 + m.m22;
			w=1,v.x=0,v.y=0,v.z=0;
			if(tr>0) s=SqrtTpl(tr+1.0f),p=0.5f/s,w=s*0.5f,v.x=(m.m21-m.m12)*p,v.y=(m.m02-m.m20)*p,v.z=(m.m10-m.m01)*p;
			else if ((m.m00>=m.m11) && (m.m00>=m.m22)) s=SqrtTpl(m.m00-m.m11-m.m22+1.0f),p=0.5f/s,w=(m.m21-m.m12)*p,v.x=s*0.5f,v.y=(m.m10+m.m01)*p,v.z=(m.m20+m.m02)*p;
			else if ((m.m11>=m.m00) && (m.m11>=m.m22)) s=SqrtTpl(m.m11-m.m22-m.m00+1.0f),p=0.5f/s,w=(m.m02-m.m20)*p,v.x=(m.m01+m.m10)*p,v.y=s*0.5f,v.z=(m.m21+m.m12)*p;
			else if ((m.m22>=m.m00) && (m.m22>=m.m11)) s=SqrtTpl(m.m22-m.m00-m.m11+1.0f),p=0.5f/s,w=(m.m10-m.m01)*p,v.x=(m.m02+m.m20)*p,v.y=(m.m12+m.m21)*p,v.z=s*0.5f;
		}
		template<class T1> explicit inline QuatTpl<T>(const Matrix33Tpl<T1>& m)	
		{ 
			ASSERT( m.IsOrthonormalRH(0.1f) );
			T1 s,p,tr = m.m00 + m.m11 + m.m22;
			w=1,v.x=0,v.y=0,v.z=0;
			if(tr>0) s=SqrtTpl(tr+1.0f),p=0.5f/s,w=T(s*0.5),v.x=T((m.m21-m.m12)*p),v.y=T((m.m02-m.m20)*p),v.z=T((m.m10-m.m01)*p);
			else if ((m.m00>=m.m11) && (m.m00>=m.m22)) s=SqrtTpl(m.m00-m.m11-m.m22+1.0f),p=0.5f/s,w=T((m.m21-m.m12)*p),v.x=T(s*0.5),v.y=T((m.m10+m.m01)*p),v.z=T((m.m20+m.m02)*p);
			else if ((m.m11>=m.m00) && (m.m11>=m.m22)) s=SqrtTpl(m.m11-m.m22-m.m00+1.0f),p=0.5f/s,w=T((m.m02-m.m20)*p),v.x=T((m.m01+m.m10)*p),v.y=T(s*0.5),v.z=T((m.m21+m.m12)*p);
			else if ((m.m22>=m.m00) && (m.m22>=m.m11)) s=SqrtTpl(m.m22-m.m00-m.m11+1.0f),p=0.5f/s,w=T((m.m10-m.m01)*p),v.x=T((m.m02+m.m20)*p),v.y=T((m.m12+m.m21)*p),v.z=T(s*0.5);
		}

		explicit inline QuatTpl<T>(const Matrix34Tpl<T>& m){ *this=QuatTpl<T>(Matrix33Tpl<T>(m)); }
		template<class T1> explicit inline QuatTpl<T>(const Matrix34Tpl<T1>& m){	*this=QuatTpl<T>(Matrix33Tpl<T1>(m)); }

		//special constructors
		inline QuatTpl<T>(ETypeIdentity): w(1),v(0,0,0) {}
		inline QuatTpl<T>(ETypeZero): w(0),v(0,0,0) {}

		inline void SetIdentity(){ w=1; v.x=0; v.y=0; v.z=0; }
		inline void SetZero(){ w=0; v.x=0; v.y=0; v.z=0; }
		inline static const QuatTpl<T> CreateIdentity(void) { return QuatTpl<T>(1,0,0,0); }

		//invert 
		inline const QuatTpl<T> operator ! () const { return QuatTpl(w,-v); }
		inline void Invert() { *this=!*this; }
		inline const QuatTpl<T> GetInverted() const { return !(*this); } 

		//flip quaternion. don't confuse this with quaternion-inversion.
		inline const QuatTpl<T>	operator - () const { return QuatTpl<T>( -w,-v ); };

		//multiplication by a scalar
		void operator *= (const T op) { w*=op; v*=op; }

		// Exact compare of 2 quats.
		inline const bool operator==(const QuatTpl<T>& q) const { return (v == q.v) && (w == q.w); }
		inline const bool operator!=(const QuatTpl<T>& q) const { return !(*this == q); }
		
		//A quaternion is a compressed matrix. Thus there is no problem extracting the rows & columns. 
		inline const Vector3Tpl<T> GetColumn(const uint32 input) const { if (input==0)	return GetColumn0(); if (input==1) return GetColumn1(); if (input==2) return GetColumn2(); ASSERT(0); return Vector3Tpl<T>(ZERO); }
		inline const Vector3Tpl<T> GetColumn0() const {return Vector3Tpl<T>(2*(v.x*v.x+w*w)-1,2*(v.y*v.x+v.z*w),2*(v.z*v.x-v.y*w));}
		inline const Vector3Tpl<T> GetColumn1() const {return Vector3Tpl<T>(2*(v.x*v.y-v.z*w),2*(v.y*v.y+w*w)-1,2*(v.z*v.y+v.x*w));}
		inline const Vector3Tpl<T> GetColumn2() const {return Vector3Tpl<T>(2*(v.x*v.z+v.y*w),2*(v.y*v.z-v.x*w),2*(v.z*v.z+w*w)-1);}
		inline const Vector3Tpl<T> GetRow0() const {return Vector3Tpl<T>(2*(v.x*v.x+w*w)-1,2*(v.x*v.y-v.z*w),2*(v.x*v.z+v.y*w));}
		inline const Vector3Tpl<T> GetRow1() const {return Vector3Tpl<T>(2*(v.y*v.x+v.z*w),2*(v.y*v.y+w*w)-1,2*(v.y*v.z-v.x*w));}
		inline const Vector3Tpl<T> GetRow2() const	{return Vector3Tpl<T>(2*(v.z*v.x-v.y*w),2*(v.z*v.y+v.x*w),2*(v.z*v.z+w*w)-1);}

		// These are just copy & pasted components of the GetColumn1() above.
		inline const T GetFwdX() const { return (2*(v.x*v.y-v.z*w)); }
		inline const T GetFwdY() const { return (2*(v.y*v.y+w*w)-1); }
		inline const T GetFwdZ() const { return (2*(v.z*v.y+v.x*w)); }
		inline const T GetRotZ() const { return Atan2Tpl(-GetFwdX(), GetFwdY()); }
	
		//checkers
		inline const bool IsIdentity() const { return CmpTpl(w,1) && CmpTpl(v.x,0) && CmpTpl(v.y,0) && CmpTpl(v.z,0); }
		inline const bool IsUnit(const T e = VEC_EPSILON) const { return AbsTpl(1-(w*w + v.x*v.x + v.y*v.y + v.z*v.z)) < e; }
		inline const bool IsValid(const T e = VEC_EPSILON) const { if (!v.IsValid()) return false; if (!NumberValid(w)) return false; return true; }
	
		inline void SetRotationAA(const T rad, const Vector3Tpl<T>& axis) { T s,c; SinCosTpl( rad*static_cast<T>(0.5), &s,&c); SetRotationAA(c,s,axis); }
		inline static const QuatTpl<T> CreateRotationAA(T rad, const Vector3Tpl<T> &axis){ QuatTpl<T> q; q.SetRotationAA(rad,axis); return q; }
		inline void SetRotationAA(const T cosha, const T sinha, const Vector3Tpl<T> &axis){ ASSERT(axis.IsUnit(GetEpsilon<T>())); w=cosha; v=axis*sinha; }
		inline static QuatTpl<T> CreateRotationAA(const T cosha, const T sinha, const Vector3Tpl<T> &axis){ QuatTpl<T> q; q.SetRotationAA(cosha,sinha,axis); 	return q; }
	
		//Create rotation-quaternion that around the fixed coordinate axes.
		inline void SetRotationXYZ(const Angle3Tpl<T> &a)
		{ 
			ASSERT(a.IsValid());
			T sx,cx;  SinCosTpl(T(a.x*T(0.5)),&sx,&cx);
			T sy,cy;  SinCosTpl(T(a.y*T(0.5)),&sy,&cy);
			T sz,cz;  SinCosTpl(T(a.z*T(0.5)),&sz,&cz);
			w		= cx*cy*cz + sx*sy*sz;
			v.x = cz*cy*sx - sz*sy*cx;
			v.y = cz*sy*cx + sz*cy*sx;
			v.z = sz*cy*cx - cz*sy*sx;
		}

		inline static QuatTpl<T> CreateRotationXYZ(const Angle3Tpl<T>& a){ ASSERT(a.IsValid()); QuatTpl<T> q; q.SetRotationXYZ(a); return q; }

		//Create rotation-quaternion that about the x-axis.
		inline void SetRotationX( const f32 r ){ T s,c;	SinCosTpl(T(r*T(0.5)),&s,&c); w=c; v.x=s; v.y=0; v.z=0; }
		inline static const QuatTpl<T> CreateRotationX( const f32 r ){QuatTpl<T> q;	q.SetRotationX(r); return q; }

		// Create rotation-quaternion that about the y-axis.
		inline void SetRotationY( const f32 r ){ T s,c; SinCosTpl(T(r*T(0.5)),&s,&c); w=c; v.x=0; v.y=s; v.z=0; }
		inline static const QuatTpl<T> CreateRotationY( const f32 r ){ QuatTpl<T> q; q.SetRotationY(r); return q; }
	
		//Create rotation-quaternion that about the z-axis.
		inline void SetRotationZ( const f32 r ) { T s,c; SinCosTpl(T(r*T(0.5)),&s,&c); w=c; v.x=0; v.y=0; v.z=s; }
		inline static const QuatTpl<T> CreateRotationZ( const f32 r ) {	QuatTpl<T> q; q.SetRotationZ(r); return q; }

		// Create rotation-quaternion that rotates from one vector to another.
		inline void SetRotationV0V1(const Vector3Tpl<T>& v0, const Vector3Tpl<T>& v1)
		{ 
			ASSERT(v0.IsUnit(0.01f));
			ASSERT(v1.IsUnit(0.01f));
			const T dot = v0.x*v1.x+v0.y*v1.y+v0.z*v1.z+T(1.0);
			if (dot > T(0.0001) ) 
			{
				const T vx=v0.y*v1.z-v0.z*v1.y; 
				const T vy=v0.z*v1.x-v0.x*v1.z; 
				const T vz=v0.x*v1.y-v0.y*v1.x; 
				const T d = InvSqrtTpl(dot*dot + vx*vx+vy*vy+vz*vz);
				w=T(dot*d);	v.x=T(vx*d); v.y=T(vy*d); v.z=T(vz*d);
				return;
			}
			w=0; v=v0.GetOrthogonal().GetNormalized();
		}

		inline static QuatTpl<T> CreateRotationV0V1(const Vector3Tpl<T> &v0, const Vector3Tpl<T> &v1) {	QuatTpl<T> q; q.SetRotationV0V1(v0,v1); return q; }

		/*!
		*
		* \param vdir  normalized view direction.
		* \param roll  radiant to rotate about Y-axis.
		*
		*  Given a view-direction and a radiant to rotate about Y-axis, this function builds a 3x3 look-at quaternion 
		*  using only simple vector arithmetic. This function is always using the implicit up-vector Vec3(0,0,1). 
		*  The view-direction is always stored in column(1).
		*  IMPORTANT: The view-vector is assumed to be normalized, because all trig-values for the orientation are being 
		*  extracted  directly out of the vector. This function must NOT be called with a view-direction 
		*  that is close to Vec3(0,0,1) or Vec3(0,0,-1). If one of these rules is broken, the function returns a quaternion 
		*  with an undefined rotation about the Z-axis.
		*
		*  Rotation order for the look-at-quaternion is Z-X-Y. (Zaxis=YAW / Xaxis=PITCH / Yaxis=ROLL)
		*
		*  COORDINATE-SYSTEM       
		*                                   
		*  z-axis                                 
		*    ^                               
		*    |                               
		*    |  y-axis                   
		*    |  /                         
		*    | /                           
		*    |/                             
		*    +--------------->   x-axis     
		*                                  
		*  Example:
		*     Quat LookAtQuat=Quat::CreateRotationVDir( Vec3(0,1,0) );
		*   or
		*     Quat LookAtQuat=Quat::CreateRotationVDir( Vec3(0,1,0), 0.333f );
		*/
		inline void SetRotationVDir( const Vector3Tpl<T>& vdir )
		{
			ASSERT(vdir.IsUnit(0.01f));
			//set default initialization for up-vector
			w=T(0.70710676908493042);	v.x=T(vdir.z*0.70710676908493042); v.y=T(0.0); v.z=T(0.0); 
			const T l = SqrtTpl(vdir.x*vdir.x+vdir.y*vdir.y);
			if (l>T(0.00001))	
			{
				//calculate LookAt quaternion
				Vector3Tpl<T> hv = Vector3Tpl<T> (vdir.x/l,vdir.y/l+1.0f,l+1.0f);
				T r = SqrtTpl(hv.x*hv.x + hv.y*hv.y);
				T s	= SqrtTpl(hv.z*hv.z + vdir.z*vdir.z);
				//generate the half-angle sine&cosine
				T hacos0=0.0; T hasin0=-1.0;
				if (r>T(0.00001)) { hacos0=hv.y/r; hasin0=-hv.x/r; }   //yaw
				T hacos1=hv.z/s; T hasin1=vdir.z/s;                    //pitch
				w=T(hacos0*hacos1); v.x=T(hacos0*hasin1); v.y=T(hasin0*hasin1); v.z=T(hasin0*hacos1);  
			}
		}
		inline static QuatTpl<T> CreateRotationVDir( const Vector3Tpl<T>& vdir ) { QuatTpl<T> q; q.SetRotationVDir(vdir); return q; }
	
		inline void SetRotationVDir( const Vector3Tpl<T>& vdir, const T r )
		{
			SetRotationVDir(vdir);
			T sy,cy; SinCosTpl(r*static_cast<T>(0.5),&sy,&cy);
			T vx=v.x,vy=v.y;
			v.x=T(vx*cy-v.z*sy); v.y=T(w*sy+vy*cy); v.z=T(v.z*cy+vx*sy); w=T(w*cy-vy*sy);
		}
		inline static QuatTpl<T> CreateRotationVDir( const Vector3Tpl<T>& vdir, T roll ) { QuatTpl<T> q; q.SetRotationVDir(vdir,roll); return q; }

		inline void Normalize(void) { const T d = InvSqrtTpl(w*w + v.x*v.x+v.y*v.y+v.z*v.z); w*=d; v.x*=d; v.y*=d; v.z*=d; }
		inline QuatTpl<T> GetNormalized() const { QuatTpl<T> t=*this;  t.Normalize(); return t; }

		inline void NormalizeSafe(void)
		{
			const T d = GetLengthSquared();
			if (d > GetEpsilon<T>())
			{
				d = InvSqrtTpl(d);
				w*=d; v.x*=d; v.y*=d; v.z*=d;
			}
			else
			{
				SetIdentity();
			}
		}

		inline QuatTpl<T> GetNormalizedSafe() const{ QuatTpl<T> t=*this; t.NormalizeSafe(); return t; }
		inline void	NormalizeFast(void) { ASSERT(IsValid()); const T invLen = InvSqrtFastTpl( GetLengthSquared() ); v.x*=invLen; v.y*=invLen; v.z*=invLen; w*=invLen; }
		inline QuatTpl<T> GetNormalizedFast() const { QuatTpl<T> t=*this; t.NormalizeFast(); return t;	}

		inline const T GetLength() const { return SqrtTpl(GetLengthSquared()); }
		inline const T GetLengthSquared() const { return w*w + v.x*v.x+v.y*v.y+v.z*v.z; }
		inline static const bool IsEquivalent(const QuatTpl<T>& q1, const QuatTpl<T>& q2, const T epsilon =RAD_EPSILON) { return acos(min(1.0,AbsTpl( q1.v.x*q2.v.x + q1.v.y*q2.v.y + q1.v.z*q2.v.z + q1.w*q2.w ))) <= epsilon; }

		// Exponent of Quaternion.
		inline static QuatTpl<T> Exp(const Vector3Tpl<T>& v) 
		{
			const T lensqr = v.len2();
			if (lensqr > T(0))
			{
				const T len = SqrtTpl(lensqr);
				T s,c; SinCosTpl(len,&s,&c); 
				s /= len;
				return QuatTpl<T>( c, v.x*s, v.y*s, v.z*s );
			}
			return QuatTpl<T> (IDENTITY);
		}

		// logarithm of a quaternion, imaginary part (the real part of the logarithm is always 0)
		inline static Vector3Tpl<T> Log (const QuatTpl<T>& q) 
		{
			ASSERT(q.IsValid());
			T lensqr = q.v.len2();
			if (lensqr > 0.0f)
			{
				const T len = SqrtTpl(lensqr);
				const T angle = Atan2Tpl(len, q.w) / len;
				return q.v * angle;
			}
			// logarithm of a quaternion, imaginary part (the real part of the logarithm is always 0)
			return Vector3Tpl<T>(0,0,0);
		}

		// Logarithm of Quaternion difference.
		inline static QuatTpl<T> LnDif( const QuatTpl<T>& q1,const QuatTpl<T>& q2 ) { return QuatTpl<T>(0,log(q2/q1)); }

		// linear-interpolation between quaternions (lerp)
		inline void SetNlerp( const QuatTpl<T> &p, const QuatTpl<T> &tq, const T t ) 
		{	
			QuatTpl<T> q=tq;
			ASSERT(p.IsValid());
			ASSERT(q.IsValid());
			if( (p|q) < 0 ) { q=-q; }
			v.x = p.v.x*(1.0f-t) + q.v.x*t;
			v.y = p.v.y*(1.0f-t) + q.v.y*t;
			v.z = p.v.z*(1.0f-t) + q.v.z*t;
			w   = p.w  *(1.0f-t) + q.w  *t;
			Normalize();
		}
		inline static QuatTpl<T> CreateNlerp( const QuatTpl<T> &p, const QuatTpl<T> &tq, const T t ) { QuatTpl<T> d; d.SetNlerp(p,tq,t); return d; }

		//linear-interpolation between quaternions (nlerp) in this case we convert the t-value into a 1d cubic spline to get closer to Slerp
		inline void SetNlerpCubic( const QuatTpl<T> &p, const QuatTpl<T> &tq, const T t ) 
		{
			QuatTpl<T> q=tq;
			ASSERT((AbsTpl(1-(p|p)))<0.001); //check if unit-quaternion
			ASSERT((AbsTpl(1-(q|q)))<0.001); //check if unit-quaternion
			T cosine=(p|q);
			if(cosine<0) q=-q; 
			T k=(1-AbsTpl(cosine))*T(0.4669269);
			T s = 2*k*t*t*t - 3*k*t*t + (1+k)*t;
			v.x = p.v.x*(1.0f-s) + q.v.x*s;
			v.y = p.v.y*(1.0f-s) + q.v.y*s;
			v.z = p.v.z*(1.0f-s) + q.v.z*s;
			w   = p.w  *(1.0f-s) + q.w*s;
			Normalize();
		}
		inline static QuatTpl<T> CreateNlerpCubic( const QuatTpl<T> &p, const QuatTpl<T> &tq, const T t ){ QuatTpl<T> d;  d.SetNlerpCubic(p,tq,t); return d; }

		//spherical-interpolation between quaternions (geometrical slerp)
		inline void SetSlerp( const QuatTpl<T> &tp, const QuatTpl<T> &tq, T t ) 
		{
			ASSERT(tp.IsValid());
			ASSERT(tq.IsUnit());
			QuatTpl<T> p=tp,q=tq;
			QuatTpl<T> q2;

			T cosine = (p|q);
			if (cosine < 0.0f ) { cosine=-cosine; q=-q;	} //take shortest arc
			if (cosine > 0.9999f)
			{
				SetNlerp(p,q,t);
				return;
			}
			// from now on, a division by 0 is not possible any more
			q2.w   = q.w-p.w*cosine;
			q2.v.x = q.v.x-p.v.x*cosine;
			q2.v.y = q.v.y-p.v.y*cosine;
			q2.v.z = q.v.z-p.v.z*cosine;
			T sine = sqrt(q2|q2);
			T s,c; SinCosTpl(Atan2Tpl(sine,cosine)*t,&s,&c);
			w   = T(p.w  *c + q2.w  *s/sine);
			v.x = T(p.v.x*c + q2.v.x*s/sine);
			v.y = T(p.v.y*c + q2.v.y*s/sine);
			v.z = T(p.v.z*c + q2.v.z*s/sine);
		}

		inline static QuatTpl<T> CreateSlerp( const QuatTpl<T> &p, const QuatTpl<T> &tq, const T t ) { QuatTpl<T> d; d.SetSlerp(p,tq,t); return d; }
	
		//Spherical-interpolation between quaternions (algebraic slerp_a) Both slerp-functions are returning the same result.
		inline void SetExpSlerp( const QuatTpl<T> &p, const QuatTpl<T> &tq, const T t ) 
		{
			ASSERT((AbsTpl(1-(p|p)))<0.001); //check if unit-quaternion
			ASSERT((AbsTpl(1-(tq|tq)))<0.001); //check if unit-quaternion
			QuatTpl<T> q=tq;
			if((p|q)<0) { q=-q;	} 
			*this = p * exp( log(!p*q)*t );            //algebraic slerp (1)
			//...and some more exp-slerp-functions producing all the same result
			//*this = exp( log (p* !q) * (1-t)) * q;   //algebraic slerp (2)
			//*this = exp( log (q* !p) * t) * p;       //algebraic slerp (3)
			//*this = q * exp( log (!q*p) * (1-t));    //algebraic slerp (4)
		}
		inline static QuatTpl<T> CreateExpSlerp( const QuatTpl<T> &p, const QuatTpl<T> &q, const T t ) { QuatTpl<T> d;  d.SetExpSlerp(p,q,t); 	return d;}

		//! squad(p,a,b,q,t) = slerp( slerp(p,q,t),slerp(a,b,t), 2(1-t)t).
		inline void SetSquad( const QuatTpl<T>& p,const QuatTpl<T>& a,const QuatTpl<T>& b,const QuatTpl<T>& q, const T t ){ SetSlerp( CreateSlerp(p,q,t), CreateSlerp(a,b,t), 2.0f*(1.0f-t)*t ); }
		inline static const QuatTpl<T> CreateSquad( const QuatTpl<T>& p,const QuatTpl<T>& a,const QuatTpl<T>& b,const QuatTpl<T>& q, const T t ){	QuatTpl<T> d; d.SetSquad(p,a,b,q, t); return d;	}
		
	public:
		Vector3Tpl<T> v;
		T             w;
	};

	///////////////////////////////////////////////////////////////////////////////
	// Global Operators                                                          // 
	///////////////////////////////////////////////////////////////////////////////

	//The "inner product" or "dot product" operation.
	template<typename T1,typename T2> inline T1 operator | (const QuatTpl<T1>& q, const QuatTpl<T2>& p){ ASSERT(q.v.IsValid());	ASSERT(p.v.IsValid()); return (q.v.x*p.v.x + q.v.y*p.v.y + q.v.z*p.v.z + q.w*p.w); } 

	template<typename T1,typename T2> const QuatTpl<T1> inline operator * (const QuatTpl<T1>& q, const QuatTpl<T2>& p) 
	{ 
		ASSERT(q.IsValid());
		ASSERT(p.IsValid());
		return QuatTpl<T1>( q.w*p.w  - (q.v.x*p.v.x + q.v.y*p.v.y + q.v.z*p.v.z),	q.v.y*p.v.z-q.v.z*p.v.y + q.w*p.v.x + q.v.x*p.w, q.v.z*p.v.x-q.v.x*p.v.z + q.w*p.v.y + q.v.y*p.w,	q.v.x*p.v.y-q.v.y*p.v.x + q.w*p.v.z + q.v.z*p.w );
	}

	template<typename T1,typename T2> inline void operator *= (QuatTpl<T1>& q, const QuatTpl<T2>& p) { ASSERT(q.IsValid()); ASSERT(p.IsValid()); T1 s0=q.w; q.w=q.w*p.w-(q.v|p.v); q.v=p.v*s0+q.v*p.w+(q.v%p.v); }
	template<typename T1,typename T2> inline const QuatTTpl<T1> operator * (const QuatTpl<T1>& q, const QuatTTpl<T2>& p) { return QuatTTpl<T1>(q*p.q, q*p.t); }

	template<typename T1,typename T2> inline const QuatTpl<T1> operator / (const QuatTpl<T1>& q, const QuatTpl<T2>& p) { return (!p*q); }
	template<typename T1,typename T2> inline void operator /= (QuatTpl<T1>& q, const QuatTpl<T2>& p) { q=(!p*q); }
	template<typename T1,typename T2> inline const QuatTpl<T1> operator + (const QuatTpl<T1>& q, const QuatTpl<T2> &p) { return QuatTpl<T1>( q.w+p.w, q.v+p.v ); }
	template<typename T1,typename T2> inline void operator += (QuatTpl<T1>& q, const QuatTpl<T2>& p) { q.w+=p.w; q.v+=p.v; }

	template<class T1,class T2> inline QuatTpl<T1> operator - (const QuatTpl<T1> &q, const QuatTpl<T2>& p) { return QuatTpl<T1>( q.w-p.w, q.v-p.v); }
	template<class T1,class T2> inline void operator -= (QuatTpl<T1> &q, const QuatTpl<T2> &p) { q.w-=p.w; q.v-=p.v; }

	//! Scale quaternion free function.
	template <typename T> inline QuatTpl<T>	operator * ( const T t, const QuatTpl<T> &q ) {	return QuatTpl<T>( t*q.w, t*q.v ); }
	template <typename T1,typename T2> inline QuatTpl<T1> operator * ( const QuatTpl<T1>& q, const T2 t ) {	return QuatTpl<T1>( q.w*t, q.v*t ); }
	template <typename T1,typename T2> inline QuatTpl<T1> operator / ( const QuatTpl<T1>& q, const T2 t ) {	return QuatTpl<T1>( q.w/t, q.v/t ); }

	template<typename T1,typename T2> inline Vector3Tpl<T1> operator * (const QuatTpl<T1>& q, const Vector3Tpl<T2>& v) 
	{ 
		//Ramon ~ TODO FIXME
		//ASSERT(v.IsValid()); ASSERT(q.IsValid());
		//Vector3Tpl<T1> r2((q.v.y*v.z-q.v.z*v.y)+q.w*v.x,(q.v.z*v.x-q.v.x*v.z)+q.w*v.y,(q.v.x*v.y-q.v.y*v.x)+q.w*v.z);
		//return Vector3Tpl<T1>((r2.z*q.v.y-r2.y*q.v.z); out.x+=out.x+v.x,(r2.x*q.v.z-r2.z*q.v.x); out.y+=out.y+v.y,(r2.y*q.v.x-r2.x*q.v.y); out.z+=out.z+v.z);
		//return Vector3Tpl<T1>(ZERO);

    //Ruben
    Vector3Tpl<T1> out;
    QuatTpl<T1> q2(q.w, -q.v.x, -q.v.y, -q.v.z); //wxyz!!
    QuatTpl<T1> temp(
      -(q2.v.x*v.x + q2.v.y*v.y + q2.v.z*v.z),
      q2.w*v.x + q2.v.y*v.z - q2.v.z*v.y,
      q2.w*v.y + q2.v.z*v.x - q2.v.x*v.z,
      q2.w*v.z + q2.v.x*v.y - q2.v.y*v.x
      );
    temp *= q;

    out.x = temp.v.x;
    out.y = temp.v.y;
    out.z = temp.v.z;
    return out;
	}

	template<typename T1,typename T2> inline Vector3Tpl<T2> operator * (const Vector3Tpl<T1> &v, const QuatTpl<T2> &q) 
	{
		//Ramon ~ TODO FIXME
		//ASSERT(v.IsValid());	ASSERT(q.IsValid());
		//Vector3Tpl<T1> r2((q.v.z*v.y-q.v.y*v.z)+q.w*v.x,(q.v.x*v.z-q.v.z*v.x)+q.w*v.y,(q.v.y*v.x-q.v.x*v.y)+q.w*v.z);
		//return Vector3Tpl<T1>((r2.y*q.v.z-r2.z*q.v.y); out.x+=out.x+v.x,(r2.z*q.v.x-r2.x*q.v.z); out.y+=out.y+v.y,(r2.x*q.v.y-r2.y*q.v.x); out.z+=out.z+v.z);
    return Vector3Tpl<T1>(ZERO);
	}

	template<typename T1,typename T2> inline QuatTpl<T1> operator % (const QuatTpl<T1>& q, const QuatTpl<T2>& tp) 
	{ 
		QuatTpl<T1> p=tp;
		if( (p|q) < 0 ) { p=-p; } 
		return QuatTpl<T1>( q.w+p.w, q.v+p.v ); 
	}

	template<typename T1,typename T2> inline void operator %= (QuatTpl<T1>& q, const QuatTpl<T2>& tp) 
	{ 
		QuatTpl<T1> p=tp;
		if( (p|q) < 0 ) { p=-p; } 
		q = QuatTpl<T1>( q.w+p.w, q.v+p.v ); 
	}

	///////////////////////////////////////////////////////////////////////////////
	// Typedefs                                                                  // 
	///////////////////////////////////////////////////////////////////////////////

	typedef QuatTpl<f32> Quatf;
	typedef QuatTpl<f64> Quatd;

	template <typename T> QuatTpl<T> QuatConstants<T>::zero(0,0,0,0);
	template <typename T> QuatTpl<T> QuatConstants<T>::identity(IDENTITY);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	template <typename T> struct QuatTTpl
	{
	public:
		inline QuatTTpl(){}
		inline QuatTTpl(const Vector3Tpl<T>& _t, const QuatTpl<T>& _q):q(_q),t(_t){ ASSERT(IsValid()); }
		inline QuatTTpl(ETypeIdentity):q(0,0,0,1),t(0,0,0){ ASSERT(IsValid()); }
		inline QuatTTpl& operator = (const QuatTTpl<T> &qt){ q=qt.q; t=qt.t; return *this; }
		template <typename T1> inline QuatTTpl( const QuatTTpl<T1>& qt ):q(qt.q),t(qt.t){}
		inline QuatTTpl( const DualQuatTpl<T>& qd ) { q=qd.nq; t=(qd.nq.w*qd.dq.v - qd.dq.w*qd.nq.v + qd.nq.v%qd.dq.v)*2; ASSERT(IsValid()); }
		explicit inline QuatTTpl(	const Matrix34Tpl<T>& m) { q = QuatTpl<T>( Matrix33(m) ); t=m.GetTranslation(); ASSERT(IsValid()); }
		explicit inline QuatTTpl( const Matrix33Tpl<T>& m) { q = QuatTpl<T>(m); t=Vector3Tpl<T>(IDENTITY);}
		inline QuatTTpl(const QuatTpl<T>& quat, const Vector3Tpl<T>& trans):q(quat),t(trans) { ASSERT(IsValid()); }

		inline void SetIdentity() { q.w=1; q.v.x=0; q.v.y=0; q.v.z=0; t.x = 0; t.y = 0; t.z = 0; }
		inline const bool IsIdentity() const{ return (q.IsIdentity() && t.IsZero()); }

		inline void SetRotationXYZ( const Angle3Tpl<T>& rad, const Vector3Tpl<T>& trans=Vector3Tpl<T>(ZERO) ) { ASSERT(rad.IsValid()); ASSERT(trans.IsValid()); q.SetRotationXYZ(rad); t=trans; }
		inline static QuatTTpl<T> CreateRotationXYZ( const Angle3Tpl<T>& rad, const Vector3Tpl<T>& trans=Vector3Tpl<T>(ZERO) ) {	ASSERT(rad.IsValid()); ASSERT(trans.IsValid()); QuatTTpl<T> qp;	qp.SetRotationXYZ(rad,trans); return qp; }

		inline void SetRotationAA(const T cosha, const T sinha, const Vector3Tpl<T> axis, const Vector3Tpl<T>& trans=Vector3Tpl<T>(ZERO) )	{ q.SetRotationAA(cosha,sinha,axis); t=trans; }
		inline static QuatTTpl<T> CreateRotationAA( const T cosha, const T sinha, const Vector3Tpl<T> axis, const Vector3Tpl<T>& trans=Vector3Tpl<T>(ZERO) ) {	QuatTTpl<T> qt;  qt.SetRotationAA(cosha,sinha,axis,trans);	return qt; }
		inline void Invert() { ASSERT(q.IsValid()); t=-t*q; q=!q;}
		inline const QuatTTpl<T> GetInverted() const { ASSERT(q.IsValid()); QuatTTpl<T> qpos; qpos.q=!q; qpos.t=-t*q; return qpos; }
		inline void SetTranslation( const Vector3Tpl<T>& trans )	{	t=trans; }

		inline const Vector3Tpl<T> GetColumn0() const { return q.GetColumn0();}
		inline const Vector3Tpl<T> GetColumn1() const { return q.GetColumn1();}
		inline const Vector3Tpl<T> GetColumn2() const { return q.GetColumn2();}
		inline const Vector3Tpl<T> GetColumn3() const { return t;}
		inline const Vector3Tpl<T> GetRow0()    const { return q.GetRow0(); }
		inline const Vector3Tpl<T> GetRow1()    const { return q.GetRow1(); }
		inline const Vector3Tpl<T> GetRow2()    const { return q.GetRow2(); }

		inline static bool IsEquivalent( const QuatTTpl<T>& qt1, const QuatTTpl<T>& qt2, T qe=RAD_EPSILON,T ve=VEC_EPSILON) 
		{
			const T rad = acos(min(1.0f,AbsTpl(qt1.q|qt2.q)));
			bool qdif = rad<=qe;
			bool vdif = AbsTpl(qt1.t.x-qt2.t.x)<=ve && AbsTpl(qt1.t.y-qt2.t.y)<=ve &&	AbsTpl(qt1.t.z-qt2.t.z)<=ve;
			return (qdif &&	vdif);
		}

		inline const bool IsValid() const	{ return t.IsValid() && q.IsValid(); }

		inline void SetNLerp( const QuatTTpl<T> &p, const QuatTTpl<T> &tq, const T ti ) 
		{	
			ASSERT(p.q.IsValid());
			ASSERT(tq.q.IsValid());
			const QuatTpl<T> d=tq.q;
			if( (p.q|d) < 0 ) { d=-d; } 
			q.v = p.q.v + ((d.v - p.q.v) * ti);
			q.w	= p.q.w + ((d.w - p.q.w) * ti);
			q.Normalize();
			t = p.t + (tq.t - p.t * ti);
		}

		inline static const QuatTTpl<T> CreateNLerp( const QuatTTpl<T>& p, const QuatTTpl<T>& q,const T t ) { QuatTTpl<T> d; d.SetNLerp(p,q,t); return d; }

		template<typename T2> inline void SetFromVectors(const Vector3Tpl<T2>& vx, const Vector3Tpl<T2>& vy, const Vector3Tpl<T2>& vz, const Vector3Tpl<T2>& pos)	
		{
			//all vectors are stored in columns
			Matrix34Tpl<T> m34;
			m34.m00=static_cast<T>(vx.x); m34.m01=static_cast<T>(vy.x); m34.m02=static_cast<T>(vz.x); m34.m03=static_cast<T>(pos.x);
			m34.m10=static_cast<T>(vx.y); m34.m11=static_cast<T>(vy.y); m34.m12=static_cast<T>(vz.y); m34.m13=static_cast<T>(pos.y);
			m34.m20=static_cast<T>(vx.z); m34.m21=static_cast<T>(vy.z); m34.m22=static_cast<T>(vz.z); m34.m23=static_cast<T>(pos.z);
			*this = QuatTTpl<T>(m34);
		}

		inline static const QuatTTpl<T> CreateFromVectors(const Vector3Tpl<T>& vx, const Vector3Tpl<T>& vy, const Vector3Tpl<T>& vz, const Vector3Tpl<T>& pos){ QuatTTpl<T> qt; qt.SetFromVectors(vx,vy,vz,pos); return qt; }
		inline const QuatTTpl<T> GetScaled(const T scale){ return QuatTTpl<T>(t * scale, q.GetScaled(scale)); }

	public:
		QuatTpl<T>    q;
		Vector3Tpl<T> t;
	};

	///////////////////////////////////////////////////////////////////////////////
	// Global Operators                                                          // 
	///////////////////////////////////////////////////////////////////////////////

	template<typename T1,typename T2> inline const QuatTTpl<T1> operator * ( const QuatTTpl<T1>& p, const QuatTpl<T2>& q) { ASSERT(p.IsValid()); ASSERT(q.IsValid());	return QuatTTpl<T1>(p.q*q,p.t); }
	template<typename T1,typename T2> inline const QuatTTpl<T1> operator * ( const QuatTTpl<T1>& q, const QuatTTpl<T2>& p) { ASSERT(q.IsValid()); ASSERT(p.IsValid()); return QuatTTpl<T1>( q.q*p.q, q.q*p.t+q.t ); }

	template<typename T1,typename T2> const Vector3Tpl<T1> operator * (const QuatTTpl<T1>&q, const Vector3Tpl<T2>& v) 
	{
		ASSERT(v.IsValid());
		ASSERT(q.IsValid());
		const Vector3Tpl<T1> r2((q.q.v.y*v.z-q.q.v.z*v.y)+q.q.w*v.x,(q.q.v.z*v.x-q.q.v.x*v.z)+q.q.w*v.y,(q.q.v.x*v.y-q.q.v.y*v.x)+q.q.w*v.z);
		Vector3Tpl<T1> out;
		out.x =(r2.z*q.q.v.y-r2.y*q.q.v.z); out.x+=out.x+v.x+q.t.x;
		out.y =(r2.x*q.q.v.z-r2.z*q.q.v.x); out.y+=out.y+v.y+q.t.y;
		out.z =(r2.y*q.q.v.x-r2.x*q.q.v.y); out.z+=out.z+v.z+q.t.z;
		return out;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Typedefs                                                                  // 
	///////////////////////////////////////////////////////////////////////////////

	typedef QuatTTpl<f32> QuatTf;
	typedef QuatTTpl<f64> QuatTd;

	template <typename T> QuatTTpl<T> QuatTConstants<T>::zero(QuatConstants<T>::zero,Vector3Constants<T>::zero);
	template <typename T> QuatTTpl<T> QuatTConstants<T>::identity(IDENTITY);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template <typename T> struct DualQuatTpl
	{
		inline DualQuatTpl(){}
		inline DualQuatTpl( const QuatTpl<T>& q, const Vector3Tpl<T>& t )	
		{ 
			//copy the quaternion part
			nq=q; 
			//convert the translation into a dual quaternion part
			dq.w   =-0.5f*( t.x*q.v.x + t.y*q.v.y + t.z*q.v.z);
			dq.v.x = 0.5f*( t.x*q.w   + t.y*q.v.z - t.z*q.v.y);
			dq.v.y = 0.5f*(-t.x*q.v.z + t.y*q.w   + t.z*q.v.x);
			dq.v.z = 0.5f*( t.x*q.v.y - t.y*q.v.x + t.z*q.w);
		}

		inline DualQuatTpl( const QuatTTpl<T>& qt )
		{ 
			//copy the quaternion part
			nq=qt.q; 
			//convert the translation into a dual quaternion part
			dq.w   =-0.5f*( qt.t.x*qt.q.v.x + qt.t.y*qt.q.v.y + qt.t.z*qt.q.v.z);
			dq.v.x = 0.5f*( qt.t.x*qt.q.w   - qt.t.z*qt.q.v.y + qt.t.y*qt.q.v.z	);
			dq.v.y = 0.5f*( qt.t.y*qt.q.w   - qt.t.x*qt.q.v.z + qt.t.z*qt.q.v.x);
			dq.v.z = 0.5f*( qt.t.x*qt.q.v.y - qt.t.y*qt.q.v.x + qt.t.z*qt.q.w);
		}

		inline DualQuatTpl( const Matrix34Tpl<T>& m34 )
		{ 
			// non-dual part (just copy q0):
			nq=QuatTpl<T>(m34); 
			const T tx=m34.m03;
			const T ty=m34.m13;
			const T tz=m34.m23;

			// dual part:
			dq.w   =-0.5f*( tx*nq.v.x + ty*nq.v.y + tz*nq.v.z);
			dq.v.x = 0.5f*( tx*nq.w   + ty*nq.v.z - tz*nq.v.y);
			dq.v.y = 0.5f*(-tx*nq.v.z + ty*nq.w   + tz*nq.v.x);
			dq.v.z = 0.5f*( tx*nq.v.y - ty*nq.v.x + tz*nq.w);
		}

		inline DualQuatTpl( ETypeIdentity ) { SetIdentity(); }
		inline DualQuatTpl( ETypeZero ) { SetZero(); }

		template <typename T1> inline DualQuatTpl( const DualQuatTpl<T1>& QDual ) 
		{	
			nq.w = QDual.nq.w; nq.v.x = QDual.nq.v.x; nq.v.y = QDual.nq.v.y; nq.v.z = QDual.nq.v.z; 
			dq.w = QDual.dq.w; dq.v.x = QDual.dq.v.x; dq.v.y = QDual.dq.v.y; dq.v.z = QDual.dq.v.z; 
		}

		inline DualQuatTpl& operator = (const DualQuatTpl<T>& QDual ) 
		{ 
			nq.w = QDual.nq.w; nq.v.x = Dual.nq.v.x; nq.v.y = QDual.nq.v.y; nq.v.z = QDual.nq.v.z; 
			dq.w = QDual.dq.w; dq.v.x = Dual.dq.v.x; dq.v.y = QDual.dq.v.y; dq.v.z = QDual.dq.v.z; 
			return *this;
		}

		inline void SetIdentity() { nq.SetIdentity(); dq.SetZero(); }
		inline void SetZero() { nq.SetZero(); dq.SetZero(); } 

		inline void Normalize() { const T norm = InvSqrtSafeTpl(nq.v.GetLengthSquared() + nq.w*nq.w); nq *= norm; dq *= norm; }

	public:
		QuatTpl<T> nq;
		QuatTpl<T> dq; 
	};

	///////////////////////////////////////////////////////////////////////////////
	// Global Operators                                                          // 
	///////////////////////////////////////////////////////////////////////////////

	template<typename T1, typename T2> inline DualQuatTpl<T1> operator*(const DualQuatTpl<T1>& l, const T2 r) 
	{
		DualQuatTpl<T1> dual;
		dual.nq.w  =l.nq.w  *r; dual.nq.v.x=l.nq.v.x*r; dual.nq.v.y=l.nq.v.y*r; dual.nq.v.z=l.nq.v.z*r;
		dual.dq.w  =l.dq.w  *r; dual.dq.v.x=l.dq.v.x*r; dual.dq.v.y=l.dq.v.y*r; dual.dq.v.z=l.dq.v.z*r;
		return dual;
	}

	template<typename T1, typename T2> inline DualQuatTpl<T1> operator+(const DualQuatTpl<T1>& l, const DualQuatTpl<T2>& r) 
	{
		DualQuatTpl<T1> dual;
		dual.nq.w  =l.nq.w  +r.nq.w; dual.nq.v.x=l.nq.v.x+r.nq.v.x; dual.nq.v.y=l.nq.v.y+r.nq.v.y; dual.nq.v.z=l.nq.v.z+r.nq.v.z;
		dual.dq.w  =l.dq.w  +r.dq.w; dual.dq.v.x=l.dq.v.x+r.dq.v.x; dual.dq.v.y=l.dq.v.y+r.dq.v.y; dual.dq.v.z=l.dq.v.z+r.dq.v.z;
		return dual;
	}

	template<typename T1, typename T2> inline void operator += (DualQuatTpl<T1>& l, const DualQuatTpl<T2>& r) 
	{ 
		l.nq.w  +=r.nq.w; l.nq.v.x+=r.nq.v.x; l.nq.v.y+=r.nq.v.y; l.nq.v.z+=r.nq.v.z;
		l.dq.w  +=r.dq.w; l.dq.v.x+=r.dq.v.x; l.dq.v.y+=r.dq.v.y; l.dq.v.z+=r.dq.v.z;
	}

	template<typename T1, typename T2> inline Vector3Tpl<T1> operator*(const DualQuatTpl<T1>& dq, const Vector3Tpl<T2>& v) 
	{
		T2 t;
		register const T2 ax=dq.nq.v.y*v.z-dq.nq.v.z*v.y+dq.nq.w*v.x;
		register const T2 ay=dq.nq.v.z*v.x-dq.nq.v.x*v.z+dq.nq.w*v.y;
		register const T2 az=dq.nq.v.x*v.y-dq.nq.v.y*v.x+dq.nq.w*v.z;
		register T2 x=dq.dq.v.x*dq.nq.w-dq.nq.v.x*dq.dq.w+dq.nq.v.y*dq.dq.v.z-dq.nq.v.z*dq.dq.v.y; x+=x; t=(az*dq.nq.v.y-ay*dq.nq.v.z); x+=t+t+v.x; 
		register T2 y=dq.dq.v.y*dq.nq.w-dq.nq.v.y*dq.dq.w+dq.nq.v.z*dq.dq.v.x-dq.nq.v.x*dq.dq.v.z; y+=y; t=(ax*dq.nq.v.z-az*dq.nq.v.x); y+=t+t+v.y; 
		register T2 z=dq.dq.v.z*dq.nq.w-dq.nq.v.z*dq.dq.w+dq.nq.v.x*dq.dq.v.y-dq.nq.v.y*dq.dq.v.x; z+=z; t=(ay*dq.nq.v.x-ax*dq.nq.v.y); z+=t+t+v.z; 
		return Vector3Tpl<T2>(x,y,z);
	}

	template<typename T1, typename T2> inline DualQuatTpl<T1> operator*(const DualQuatTpl<T1> &a, const DualQuatTpl<T2> &b) 
	{
		DualQuatTpl<T1> dual;

		dual.nq.v.x = a.nq.v.y*b.nq.v.z-a.nq.v.z*b.nq.v.y + a.nq.w*b.nq.v.x + a.nq.v.x*b.nq.w;
		dual.nq.v.y = a.nq.v.z*b.nq.v.x-a.nq.v.x*b.nq.v.z + a.nq.w*b.nq.v.y + a.nq.v.y*b.nq.w;
		dual.nq.v.z = a.nq.v.x*b.nq.v.y-a.nq.v.y*b.nq.v.x + a.nq.w*b.nq.v.z + a.nq.v.z*b.nq.w;  
		dual.nq.w = a.nq.w*b.nq.w  - (a.nq.v.x*b.nq.v.x + a.nq.v.y*b.nq.v.y + a.nq.v.z*b.nq.v.z);

		//dual.dq	= a.nq*b.dq + a.dq*b.nq;
		dual.dq.v.x = a.nq.v.y*b.dq.v.z-a.nq.v.z*b.dq.v.y + a.nq.w*b.dq.v.x + a.nq.v.x*b.dq.w;
		dual.dq.v.y = a.nq.v.z*b.dq.v.x-a.nq.v.x*b.dq.v.z + a.nq.w*b.dq.v.y + a.nq.v.y*b.dq.w;
		dual.dq.v.z = a.nq.v.x*b.dq.v.y-a.nq.v.y*b.dq.v.x + a.nq.w*b.dq.v.z + a.nq.v.z*b.dq.w;  
		dual.dq.w   = a.nq.w*b.dq.w -(a.nq.v.x*b.dq.v.x + a.nq.v.y*b.dq.v.y + a.nq.v.z*b.dq.v.z);

		dual.dq.v.x += a.dq.v.y*b.nq.v.z-a.dq.v.z*b.nq.v.y + a.dq.w*b.nq.v.x + a.dq.v.x*b.nq.w;
		dual.dq.v.y += a.dq.v.z*b.nq.v.x-a.dq.v.x*b.nq.v.z + a.dq.w*b.nq.v.y + a.dq.v.y*b.nq.w;
		dual.dq.v.z += a.dq.v.x*b.nq.v.y-a.dq.v.y*b.nq.v.x + a.dq.w*b.nq.v.z + a.dq.v.z*b.nq.w;  
		dual.dq.w += a.dq.w*b.nq.w - (a.dq.v.x*b.nq.v.x + a.dq.v.y*b.nq.v.y + a.dq.v.z*b.nq.v.z);

		return dual;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Typedefs                                                                  // 
	///////////////////////////////////////////////////////////////////////////////

	typedef DualQuatTpl<f32> DualQuatf;
	typedef DualQuatTpl<f64> DualQuatd;

}