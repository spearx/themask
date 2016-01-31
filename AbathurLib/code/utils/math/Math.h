#ifndef INC_MATH_H
#define INC_MATH_H

#pragma once

#include <float.h>
#include <limits.h>
#include <math.h>

#include "utils/types.h"
#include "utils/log.h"

// DEFINITIONS
#define gfPI  f32(3.14159265358979323846264338327950288419716939937510)     // pi
#define gfPI2 f32(3.14159265358979323846264338327950288419716939937510*2.0) // 2*pi

#define	VEC_EPSILON	( 0.05f )
#define	RAD_EPSILON	( 0.01f )
#define DEG2RAD( a ) ( (a) * (gfPI/180.0f) )
#define RAD2DEG( a ) ( (a) * (180.0f/gfPI) )

#define GET_MIN(x,y) (x<y)?x:y;
#define GET_MAX(x,y) (x>y)?x:y;

#include "atomic.h"

namespace MathUtils
{
	//////////////////////////////////////////////////////////////////////////
	enum ETypeZero     { ZERO };
	enum ETypeMin      { VMIN };
	enum ETypeMax      { VMAX };
	enum ETypeIdentity { IDENTITY };

	//////////////////////////////////////////////////////////////////////////
	template <typename T> struct Vector2Tpl; 
	template <typename T> struct Vector3Tpl; 
	template <typename T> struct Vector4Tpl; 

	template <typename T> struct Angle3Tpl;
	template <typename T> struct PlaneTpl;
	template <typename T> struct QuatTpl;
	template <typename T> struct QuatTTpl;
	template <typename T> struct DualQuatTpl;

	template <typename T> struct Matrix33Tpl;
	template <typename T> struct Matrix34Tpl;
	template <typename T> struct Matrix44Tpl;
}

#include "valid_number.h"

#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

#include "angle3.h"
#include "quat.h"
#include "matrix33.h"
#include "matrix34.h"
#include "matrix44.h"

#include "color.h"
#include "aabb.h"
#include "bsphere.h"

////////////////////////////////
// Final typedefs             //
////////////////////////////////

typedef MathUtils::Vector2f   Vector2;
typedef MathUtils::Vector3f   Vector3;
typedef MathUtils::Vector4f   Vector4;
typedef MathUtils::Angle3f    Angle3;
typedef MathUtils::Planef     Plane;
typedef MathUtils::Quatf      Quat;
typedef MathUtils::QuatTf     QuatT;
typedef MathUtils::DualQuatf  DualQuat;
typedef MathUtils::Matrix33f  Matrix33;
typedef MathUtils::Matrix34f  Matrix34;
typedef MathUtils::Matrix44f  Matrix44;

#endif // INC_MATH_H
