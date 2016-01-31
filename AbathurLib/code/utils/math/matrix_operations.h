#pragma once

#include "utils/math/math.h"

namespace MathUtils
{
	template<typename T> inline void MatrixPerspectiveFovTpl(Matrix44Tpl<T>* pMatr, const T fovY, const T Aspect, const T zn, const T zf)
	{
		const T yScale = static_cast<T>(1.0)/TanTpl(fovY/static_cast<T>(2.0));
		const T xScale = yScale / Aspect;
		const T invTmp = static_cast<T>(1.0)/(zn-zf);

		(*pMatr)(0,0) = xScale;              (*pMatr)(1,0) = static_cast<T>(0);  (*pMatr)(2,0) = static_cast<T>(0);   (*pMatr)(3,0) = static_cast<T>(0); 
		(*pMatr)(0,1) = static_cast<T>(0);   (*pMatr)(1,1) = yScale;             (*pMatr)(2,1) = static_cast<T>(0);   (*pMatr)(3,1) = static_cast<T>(0); 
		(*pMatr)(0,2) = static_cast<T>(0);   (*pMatr)(1,2) = static_cast<T>(0);  (*pMatr)(2,2) = zf*invTmp;           (*pMatr)(3,2) = static_cast<T>(-1.0); 
		(*pMatr)(0,3) = static_cast<T>(0);   (*pMatr)(1,3) = static_cast<T>(0);  (*pMatr)(2,3) = zn*zf*invTmp;        (*pMatr)(3,3) = static_cast<T>(0); 
	}

	template<typename T> inline void MatrixOrthoTpl(Matrix44Tpl<T>* pMatr, const T w, const T h, const T zn, const T zf)
	{
		const T invTmp = static_cast<T>(1.0)/(zn-zf);

		(*pMatr)(0,0) = static_cast<T>(2.0)/w;  (*pMatr)(1,0) = static_cast<T>(0);     (*pMatr)(2,0) = static_cast<T>(0);  (*pMatr)(3,0) = static_cast<T>(0);
		(*pMatr)(0,1) = static_cast<T>(0);      (*pMatr)(1,1) = static_cast<T>(2.0)/h; (*pMatr)(2,1) = static_cast<T>(0);  (*pMatr)(3,1) = static_cast<T>(0);
		(*pMatr)(0,2) =	static_cast<T>(0);      (*pMatr)(1,2) = static_cast<T>(0);     (*pMatr)(2,2) = invTmp;             (*pMatr)(3,2) = static_cast<T>(0);
		(*pMatr)(0,3) =	static_cast<T>(0);      (*pMatr)(1,3) = static_cast<T>(0);     (*pMatr)(2,3) = zn*invTmp;          (*pMatr)(3,3) = static_cast<T>(1);
	}

	template<typename T> inline void MatrixOrthoOffCenterTpl(Matrix44* pMatr, const T l, const T r, const T b, const T t, const T zn, const T zf)
	{
		const T invTmp = static_cast<T>(1.0)/(zn-zf);

		(*pMatr)(0,0) = static_cast<T>(2.0)/(r-l);  (*pMatr)(1,0) = static_cast<T>(0);           (*pMatr)(2,0) = static_cast<T>(0);     (*pMatr)(3,0) = static_cast<T>(0);
		(*pMatr)(0,1) = static_cast<T>(0);          (*pMatr)(1,1) = static_cast<T>(2.0)/(t-b);   (*pMatr)(2,1) = static_cast<T>(0);     (*pMatr)(3,1) = static_cast<T>(0);
		(*pMatr)(0,2) =	static_cast<T>(0);          (*pMatr)(1,2) =	static_cast<T>(0);           (*pMatr)(2,2) =	invTmp;               (*pMatr)(3,2) = static_cast<T>(0);
		(*pMatr)(0,3) =	(l+r)/(l-r);                (*pMatr)(1,3) =(t+b)/(b-t);                  (*pMatr)(2,3) = zn*invTmp;             (*pMatr)(3,3) = static_cast<T>(1.0);
	}

	template<typename T> inline void MatrixOrthoOffCenterLHTpl(Matrix44* pMatr, const T l, const T r, const T b, const T t, const T zn, const T zf)
	{
		const T invTmp = static_cast<T>(1.0)/(zn-zf);

		(*pMatr)(0,0) = 2.0f/(r-l);    (*pMatr)(1,0) = 0;            (*pMatr)(2,0) = 0;             (*pMatr)(3,0) = 0;
		(*pMatr)(0,1) = 0;             (*pMatr)(1,1) = 2.0f/(t-b);   (*pMatr)(2,1) = 0;             (*pMatr)(3,1) = 0;
		(*pMatr)(0,2) = 0;             (*pMatr)(1,2) =	 0;          (*pMatr)(2,2) = invTmp;        (*pMatr)(3,2) = 0;
		(*pMatr)(0,3) = (l+r)/(l-r);   (*pMatr)(1,3) =(t+b)/(b-t);   (*pMatr)(2,3) = zn*invTmp;     (*pMatr)(3,3) = 1.0f;
	}

	template<typename T> inline void MatrixPerspectiveOffCenterTpl(Matrix44* pMatr, const T l, const T r, const T b, const T t, const T zn, const T zf)
	{
		const T invTmp1 = static_cast<T>(1.0)/(r-l);
		const T invTmp2 = static_cast<T>(1.0)/(t-b);
		const T invTmp3 = static_cast<T>(1.0)/(zn-zf);
	
		(*pMatr)(0,0) =	static_cast<T>(2)*zn*invTmp1; (*pMatr)(1,0) = static_cast<T>(0);              (*pMatr)(2,0) = static_cast<T>(0);    (*pMatr)(3,0) = static_cast<T>(0);
		(*pMatr)(0,1) = static_cast<T>(0);            (*pMatr)(1,1) = static_cast<T>(2)*zn*invTmp2;   (*pMatr)(2,1) = static_cast<T>(0);    (*pMatr)(3,1) = static_cast<T>(0);
		(*pMatr)(0,2) =	(l+r)*invTmp1;                (*pMatr)(1,2) = (t+b)*invTmp2;                  (*pMatr)(2,2) = zf*invTmp3;           (*pMatr)(3,2) = static_cast<T>(-1);
		(*pMatr)(0,3) =	static_cast<T>(0);            (*pMatr)(1,3) = static_cast<T>(0);              (*pMatr)(2,3) = zn*zf*invTmp3;        (*pMatr)(3,3) = static_cast<T>(0);
	}

	//RH
	template<typename T> inline void MatrixViewLookAt(Matrix44* pMatr, const Vector3Tpl<T>& Eye, const Vector3Tpl<T>& At, const Vector3Tpl<T>& Up)
	{
		const Vector3Tpl<T> vLightDir = (Eye - At);
		const Vector3Tpl<T> zaxis = vLightDir.GetNormalized();
		const Vector3Tpl<T> xaxis = (Up.Cross(zaxis)).GetNormalized();
		const Vector3Tpl<T> yaxis = zaxis.Cross(xaxis);

		(*pMatr)(0,0) = xaxis.x;            (*pMatr)(1,0) = yaxis.x;          (*pMatr)(2,0) = zaxis.x;          (*pMatr)(3,0) = static_cast<T>(0); 
		(*pMatr)(0,1) = xaxis.y;            (*pMatr)(1,1) = yaxis.y;          (*pMatr)(2,1) = zaxis.y;          (*pMatr)(3,1) = static_cast<T>(0); 
		(*pMatr)(0,2) = xaxis.z;            (*pMatr)(1,2) = yaxis.z;          (*pMatr)(2,2) = zaxis.z;          (*pMatr)(3,2) = static_cast<T>(0); 
		(*pMatr)(0,3) = -xaxis.Dot(Eye);    (*pMatr)(1,3) = -yaxis.Dot(Eye);  (*pMatr)(2,3) = -zaxis.Dot(Eye);  (*pMatr)(3,3) = static_cast<T>(1); 
	}

}
