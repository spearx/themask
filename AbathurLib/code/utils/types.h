#pragma once

#include <stdio.h>

#include "log.h"

STATIC_ASSERT(sizeof(char) == 1);
STATIC_ASSERT(sizeof(float) == 4);
STATIC_ASSERT(sizeof(int) >= 4);

typedef unsigned char  uchar;
typedef signed   char  schar;

typedef unsigned short ushort;
typedef signed   short sshort;

typedef unsigned int   uint;
typedef signed   int   sint;

typedef unsigned long  ulong;
typedef signed   long  slong;

typedef unsigned long long ulonglong;
typedef signed   long long slonglong;

STATIC_ASSERT(sizeof(uchar)     == sizeof(schar));
STATIC_ASSERT(sizeof(ushort)    == sizeof(sshort));
STATIC_ASSERT(sizeof(uint)      == sizeof(sint));
STATIC_ASSERT(sizeof(ulong)     == sizeof(slong));
STATIC_ASSERT(sizeof(ulonglong) == sizeof(slonglong));

STATIC_ASSERT(sizeof(uchar)  <= sizeof(ushort));
STATIC_ASSERT(sizeof(ushort) <= sizeof(uint));
STATIC_ASSERT(sizeof(uint)   <= sizeof(ulong));
STATIC_ASSERT(sizeof(ulong)  <= sizeof(ulonglong));


typedef schar int8;
typedef schar sint8;
typedef uchar uint8;
STATIC_ASSERT(sizeof(uint8) == 1);
STATIC_ASSERT(sizeof(sint8) == 1);

typedef sshort int16;
typedef sshort sint16;
typedef ushort uint16;
STATIC_ASSERT(sizeof(uint16) == 2);
STATIC_ASSERT(sizeof(sint16) == 2);

typedef sint int32;
typedef sint sint32;
typedef uint uint32;
STATIC_ASSERT(sizeof(uint32) == 4);
STATIC_ASSERT(sizeof(sint32) == 4);

typedef slonglong int64;
typedef slonglong sint64;
typedef ulonglong uint64;
STATIC_ASSERT(sizeof(uint64) == 8);
STATIC_ASSERT(sizeof(sint64) == 8);


typedef float  f32;
typedef double f64;
STATIC_ASSERT(sizeof(f32) == 4);
STATIC_ASSERT(sizeof(f64) == 8);

//INTERESANT MACROS

#define MAX(a,b) ( ((a)<(b))? (b) : (a) )
#define BIT(x) (1 << (x))

//CASTING

template<typename DestinationType, typename SourceType> inline DestinationType alias_cast( SourceType pPtr )
{
	// Provide special cast function which mirrors C++ style casts to support aliasing correct type punning casts in gcc with strict-aliasing enabled
	union { SourceType pSrc; DestinationType pDst; } conv_union;
	conv_union.pSrc = pPtr;
	return conv_union.pDst;
}
