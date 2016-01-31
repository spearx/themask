#pragma once

#include <type_traits>

#include "../log.h"
#include "../crc_hash.h"

//////////////////////
// Conversion Check //
//////////////////////

template<class FROM, class TO>
class SInheritanceChecker
{
	typedef char Small;
	class Big { char dummy[2]; };
	static Small Test(const TO&);
	static Big Test(...);
	static FROM MakeFrom();
public:
	enum { value = sizeof(Test(MakeFrom())) == sizeof(Small) };
};

template <typename FROM, typename TO> struct SConversion
{
	enum
	{
		Exists         = SInheritanceChecker<FROM,TO>::value,
		ExistsBothWays = SInheritanceChecker<FROM,TO>::value && SInheritanceChecker<TO, FROM>::value,
		SameType       = false
	};
};

template <class T> struct SConversion<T, T>    
{
	enum
	{
		Exists         = true,
		ExistsBothWays = true,
		SameType       = true
	};
};

template <class FROM> struct SConversion<FROM, void>    
{
	enum
	{
		Exists         = false,
		ExistsBothWays = false,
		SameType       = false
	};
};

template <class TO> struct SConversion<void, TO>    
{
	enum
	{
		Exists         = false,
		ExistsBothWays = false,
		SameType       = false
	};
};

template <> struct SConversion<void, void>    
{
	enum
	{
		Exists         = true,
		ExistsBothWays = true,
		SameType       = true
	};
};

/////////////////////
// procedural Type //
/////////////////////

template<int i> struct SintToType{ enum { v = i };};
#define PROCEDURAL_TYPE( value ) SIntToType< value > procedural_type
#define PROCEDURAL_INSTANCE( value ) SIntToType< value >()

//////////////////
// Math Helpers //
//////////////////

//static power of X^Y
template<size_t X, size_t Y> struct SPower { enum { value = X * SPower<X, Y - 1>::value }; };
template<size_t X> struct SPower<X, 1>{ enum{ value = X; }; };
template<size_t X> struct SPower<X, 0>{ enum{ value = 1; }; };

//static min & max
template<int A, int B> struct SMin{ enum { value = (A > B ? B : A) }; };
template<int A, int B> struct SMax{ enum { value = (A > B ? A : B) }; };

//static log2
template<unsigned num> struct SLog2 { enum { value = SLog2<(num >> 1)>::value + 1 }; };
template<> struct SLog2<1>{ enum { value = 0 }; };
template<> struct SLog2<0>{}; // invalid result

// Triangle number ( sum of all numbers up to N )
template <int N> struct TriangleNumber{ enum{ value = (N*(N+1)) / 2 }; };

////////////////////////
// TYPE NAME AND CRCs //
////////////////////////

#ifdef _MSC_VER
#define COMPILE_TIME_FUNCTION_NAME __FUNCSIG__
#else
#define COMPILE_TIME_FUNCTION_NAME __PRETTY_FUNCTION__
#endif

#pragma optimize("",off)

// Function to extract the name of a given type
template <typename TYPE> const char* GetTypeName()
{
	static const char* szResult = "";
	if (!szResult[0])
	{
		const char* szFunctionName = COMPILE_TIME_FUNCTION_NAME;
		const char* szPrefix = "GetTypeName<";
		const char* szStartOfTypeName = strstr(szFunctionName, szPrefix);
		if (szStartOfTypeName)
		{
			szStartOfTypeName += strlen(szPrefix);
			enum { KeywordsCount = 3};
			const char* keyWords[KeywordsCount] = { "struct ", "class ", "enum " };
			for (size_t iKeyWord = 0; iKeyWord < KeywordsCount; ++iKeyWord)
			{
				const char*  keyWord = keyWords[iKeyWord];
				const size_t keyWordLength = strlen(keyWord);
				if (strncmp(szStartOfTypeName, keyWord, keyWordLength) == 0)
				{
					szStartOfTypeName += keyWordLength;
					break;
				}
			}
			static const char* szSffix = ">";
			const char*        szEndOfTypeName = strstr(szStartOfTypeName, szSffix);
			if (szEndOfTypeName)
			{
				while (*(szEndOfTypeName - 1) == ' ')
				{
					--szEndOfTypeName;
				}
				enum { MaxStorage = 128 };
				static char storage[MaxStorage] = "";
				strncpy_s(storage, szStartOfTypeName, static_cast<size_t>(szEndOfTypeName - szStartOfTypeName));
				szResult = storage;
			}
		}
		ASSERT_MSG(szResult[0], "Failed to extract type name!");
	}
	return szResult;
}

//function to extract a given hash 
template <typename TYPE> uint32 GetTypeCRC()
{
	static uint32 result = 0u; 
	if (!result)
	{
		result = CCrc32::Compute(GetTypeName<TYPE>());
#ifdef _DEBUG
		//TODO ~ ramonv ~ check collisions with a debug map 
#endif 
	}
	return result;
}


//Wrap Type
#define WRAP_TYPE(baseType, type, invalid) struct type##_traits { static const baseType s_invalid = invalid; }; \
                                           typedef CTypeWrapper<baseType, type##_traits> type;

template <typename BASE_TYPE, typename TRAITS> class CTypeWrapper
{
public:

	typedef BASE_TYPE Type;
	inline CTypeWrapper() : m_value(s_invalid.GetValue()){}
	explicit inline CTypeWrapper(const Type value){m_value = value;}
	inline CTypeWrapper(const CTypeWrapper& rhs): m_value(rhs.m_value){}

	inline void SetValue(BASE_TYPE value){ m_value = value; }
	inline BASE_TYPE GetValue() const{ return m_value; }

	inline void Invalidate() { m_value = s_invalid.GetValue(); }
	inline bool IsValid() const { return m_value != s_invalid.GetValue(); }

	inline CTypeWrapper& operator = (const CTypeWrapper& rhs) { m_value =  rhs.m_value; return *this; }
	inline CTypeWrapper& operator += (const CTypeWrapper& rhs){ m_value += rhs.m_value; return *this; }
	inline CTypeWrapper operator ++ (){ ++m_value; return *this; }
	inline CTypeWrapper operator ++ (int){ CTypeWrapper prev(m_value); ++m_value; return prev; }

	inline CTypeWrapper& operator -= (const CTypeWrapper& rhs) { m_value -= rhs.m_value; return *this; }
	inline CTypeWrapper operator -- (){ --m_value; return *this; }
	inline CTypeWrapper operator -- (int){ CTypeWrapper prev(m_value); --m_value; return prev; }

	inline CTypeWrapper& operator &= (const CTypeWrapper& rhs) { m_value &= rhs.m_value; return *this; }
	inline CTypeWrapper& operator %= (const CTypeWrapper& rhs) { m_value %= rhs.m_value; return *this; }

	inline bool operator == (const CTypeWrapper& rhs) const { return m_value == rhs.m_value; }
	inline bool operator != (const CTypeWrapper& rhs) const { return m_value != rhs.m_value; }

	inline bool operator < (const CTypeWrapper& rhs) const { return m_value < rhs.m_value; }
	inline bool operator <= (const CTypeWrapper& rhs) const { return m_value <= rhs.m_value; }

	inline bool operator > (const CTypeWrapper& rhs) const { return m_value > rhs.m_value; }
	inline bool operator >= (const CTypeWrapper& rhs) const { return m_value >= rhs.m_value; }

	inline CTypeWrapper operator + (const CTypeWrapper& rhs) const { CTypeWrapper result(*this); return result += rhs; }
	inline CTypeWrapper operator - (const CTypeWrapper& rhs) const { CTypeWrapper result(*this); return result -= rhs; }
	inline CTypeWrapper operator & (const CTypeWrapper& rhs) const { CTypeWrapper result(*this); return result &= rhs; }
	inline CTypeWrapper operator % (const CTypeWrapper& rhs) const { CTypeWrapper result(*this); return result %= rhs; }

	static const CTypeWrapper s_invalid;

private:

	Type m_value;
};

template <typename BASE_TYPE, typename TRAITS> const CTypeWrapper<BASE_TYPE, TRAITS> CTypeWrapper<BASE_TYPE, TRAITS>::s_invalid = CTypeWrapper<BASE_TYPE, TRAITS>(TRAITS::s_invalid);


// Privilege Access Pattern
// Class used as internal limited access to the Access_Type functionality, only Privileged_Types can use protected methods, but still not accessible from outside. 
template<class ACCESS_TYPE, class PRIVILEGED_TYPE> class PrivilegeAccess : public ACCESS_TYPE { friend PRIVILEGED_TYPE; };

//Enum Class Converter
template<typename ENUMERATION_TYPE> constexpr inline auto ToUnderlyingType(const ENUMERATION_TYPE input) -> typename std::underlying_type<ENUMERATION_TYPE>::type
{
	STATIC_ASSERT(std::is_enum<ENUMERATION_TYPE>::value);
	return static_cast<typename std::underlying_type<ENUMERATION_TYPE>::type>(input);
}