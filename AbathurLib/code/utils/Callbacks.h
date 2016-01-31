#pragma once 

//Simple Functor with the constructor overloaded such in a way to be able to force assign of similar but different functors
template <typename OUTPUT = void>
class CFunctionCaller0
{
public:

	typedef OUTPUT(*stub_type)(void* object_ptr);

	CFunctionCaller0() : m_pObject(nullptr), m_pStub(nullptr) {}
	template <class OTHER_OUTPUT>
	explicit CFunctionCaller0(const CFunctionCaller0<OTHER_OUTPUT>& other) : m_pObject(other.m_pObject), m_pStub(reinterpret_cast<stub_type>(other.m_pStub)) {}

	template <OUTPUT(*METHOD)()> static CFunctionCaller0<OUTPUT> SetFunction()
	{
		CFunctionCaller0 funct;
		funct.m_pObject = 0;
		funct.m_pStub = &functionStub<METHOD>;
		return funct;
	}

	template <OUTPUT(*METHOD)()>
	static OUTPUT functionStub(void* pObject) { return (*METHOD)(); }

	template <class T, OUTPUT(T::*METHOD)()> static CFunctionCaller0<OUTPUT> SetMethod(T* pObject)
	{
		CFunctionCaller0 funct;
		funct.m_pObject = pObject;
		funct.m_pStub = &MethodStub<T, METHOD>;
		return funct;
	}

	template <class T, OUTPUT(T::*METHOD)()> static OUTPUT MethodStub(void* pObject)
	{
		T* p = static_cast<T*>(pObject);
		return (p->*METHOD)();
	}

	OUTPUT operator()() const { return (*m_pStub)(m_pObject); }

	inline const bool IsFunctionValid() const { return (m_pStub != nullptr); }
	inline const bool IsMethodValid() const { return (m_pStub != nullptr) && (m_pObject != nullptr); }

	void Clear() { m_pObject = nullptr; m_pStub = nullptr; }

	void*     m_pObject;
	stub_type m_pStub;
};


template <typename INPUT1, typename OUTPUT = void>
class CFunctionCaller1
{
public:

	typedef OUTPUT (*stub_type)(void* object_ptr, INPUT1 p1);

	CFunctionCaller1(): m_pObject(nullptr), m_pStub(nullptr){}
	template <class OTHER_INPUT, class OTHER_OUTPUT> 
	explicit CFunctionCaller1(const CFunctionCaller1<OTHER_INPUT, OTHER_OUTPUT>& other): m_pObject(other.m_pObject), m_pStub(reinterpret_cast<stub_type>(other.m_pStub)){}

	template <OUTPUT (*METHOD)(INPUT1)> static CFunctionCaller1<INPUT1, OUTPUT> SetFunction()
	{
		CFunctionCaller1 funct;
		funct.m_pObject = 0;
		funct.m_pStub = &functionStub<METHOD>;
		return funct;
	}

	template <OUTPUT (*METHOD)(INPUT1)> 
	static OUTPUT functionStub(void* pObject, INPUT1 p1) { return (*METHOD)(p1); }

	template <class T, OUTPUT (T::*METHOD)(INPUT1)> static CFunctionCaller1<INPUT1, OUTPUT> SetMethod(T* pObject)
	{
		CFunctionCaller1 funct;
		funct.m_pObject = pObject;
		funct.m_pStub = &MethodStub<T, METHOD>;
		return funct;
	}

	template <class T, OUTPUT (T::*METHOD)(INPUT1)> static OUTPUT MethodStub(void* pObject, INPUT1 p1)
	{
		T* p = static_cast<T*>(pObject);
		return (p->*METHOD)(p1);
	}

	OUTPUT operator()(INPUT1 p1) const {	return (*m_pStub)(m_pObject, p1); }

	inline const bool IsFunctionValid() const { return (m_pStub != nullptr); }
	inline const bool IsMethodValid() const { return (m_pStub != nullptr) && (m_pObject != nullptr); }

	void Clear(){ m_pObject = nullptr; m_pStub = nullptr; }

	void*     m_pObject;
	stub_type m_pStub;
};

template <typename INPUT1, typename INPUT2, typename OUTPUT = void>
class CFunctionCaller2
{
public:

	typedef OUTPUT (*stub_type)(void* object_ptr, INPUT1 p1, INPUT2 p2);

	CFunctionCaller2(): m_pObject(nullptr), m_pStub(nullptr){}
	template <class OTHER_INPUT1, class OTHER_INPUT2, class OTHER_OUTPUT> 
	explicit CFunctionCaller2(const CFunctionCaller2<OTHER_INPUT1, OTHER_INPUT2, OTHER_OUTPUT>& other): m_pObject(other.m_pObject), m_pStub(reinterpret_cast<stub_type>(other.m_pStub)){}

	template <OUTPUT (*METHOD)(INPUT1,INPUT2)> static CFunctionCaller2<INPUT1, INPUT2, OUTPUT> SetFunction()
	{
		CFunctionCaller2 funct;
		funct.m_pObject = 0;
		funct.m_pStub = &functionStub<METHOD>;
		return funct;
	}

	template <OUTPUT (*METHOD)(INPUT1,INPUT2)> 
	static OUTPUT functionStub(void* pObject, INPUT1 p1, INPUT2 p2) { return (*METHOD)(p1,p2); }

	template <class T, OUTPUT (T::*METHOD)(INPUT1,INPUT2)> static CFunctionCaller2<INPUT1, INPUT2, OUTPUT> SetMethod(T* pObject)
	{
		CFunctionCaller2 funct;
		funct.m_pObject = pObject;
		funct.m_pStub = &MethodStub<T, METHOD>;
		return funct;
	}

	template <class T, OUTPUT (T::*METHOD)(INPUT1,INPUT2)> static OUTPUT MethodStub(void* pObject, INPUT1 p1, INPUT2 p2)
	{
		T* p = static_cast<T*>(pObject);
		return (p->*METHOD)(p1,p2);
	}

	OUTPUT operator()(INPUT1 p1, INPUT2 p2) const {	return (*m_pStub)(m_pObject, p1, p2); }

	inline const bool IsFunctionValid() const { return (m_pStub != nullptr); }
	inline const bool IsMethodValid() const { return (m_pStub != nullptr) && (m_pObject != nullptr); }

	void Clear(){ m_pObject = nullptr; m_pStub = nullptr; }

	void*     m_pObject;
	stub_type m_pStub;
};

template <typename INPUT1, typename INPUT2, typename INPUT3, typename OUTPUT = void>
class CFunctionCaller3
{
public:

	typedef OUTPUT (*stub_type)(void* object_ptr, INPUT1 p1, INPUT2 p2, INPUT3 p3);

	CFunctionCaller3(): m_pObject(nullptr), m_pStub(nullptr){}
	template <class OTHER_INPUT1, class OTHER_INPUT2, class OTHER_INPUT3, class OTHER_OUTPUT> 
	explicit CFunctionCaller3(const CFunctionCaller3<OTHER_INPUT1, OTHER_INPUT2, OTHER_INPUT3, OTHER_OUTPUT>& other): m_pObject(other.m_pObject), m_pStub(reinterpret_cast<stub_type>(other.m_pStub)){}

	template <OUTPUT (*METHOD)(INPUT1,INPUT2,INPUT3)> static CFunctionCaller3<INPUT1, INPUT2, INPUT3, OUTPUT> SetFunction()
	{
		CFunctionCaller3 funct;
		funct.m_pObject = 0;
		funct.m_pStub = &functionStub<METHOD>;
		return funct;
	}

	template <OUTPUT (*METHOD)(INPUT1,INPUT2,INPUT3)> 
	static OUTPUT functionStub(void* pObject, INPUT1 p1, INPUT2 p2, INPUT3 p3) { return (*METHOD)(p1,p2,p3); }

	template <class T, OUTPUT (T::*METHOD)(INPUT1,INPUT2,INPUT3)> static CFunctionCaller3<INPUT1, INPUT2, INPUT3, OUTPUT> SetMethod(T* pObject)
	{
		CFunctionCaller3 funct;
		funct.m_pObject = pObject;
		funct.m_pStub = &MethodStub<T, METHOD>;
		return funct;
	}

	template <class T, OUTPUT (T::*METHOD)(INPUT1,INPUT2,INPUT3)> static OUTPUT MethodStub(void* pObject, INPUT1 p1, INPUT2 p2, INPUT3 p3)
	{
		T* p = static_cast<T*>(pObject);
		return (p->*METHOD)(p1,p2,p3);
	}

	OUTPUT operator()(INPUT1 p1, INPUT2 p2, INPUT3 p3) const {	return (*m_pStub)(m_pObject, p1, p2, p3); }

	inline const bool IsFunctionValid() const { return (m_pStub != nullptr); }
	inline const bool IsMethodValid() const { return (m_pStub != nullptr) && (m_pObject != nullptr); }

	void Clear(){ m_pObject = nullptr; m_pStub = nullptr; }

	void*     m_pObject;
	stub_type m_pStub;
};

template <typename INPUT1, typename INPUT2, typename INPUT3, typename INPUT4, typename OUTPUT = void>
class CFunctionCaller4
{
public:

	typedef OUTPUT(*stub_type)(void* object_ptr, INPUT1 p1, INPUT2 p2, INPUT3 p3, INPUT4 p4);

	CFunctionCaller4() : m_pObject(nullptr), m_pStub(nullptr) {}
	template <class OTHER_INPUT1, class OTHER_INPUT2, class OTHER_INPUT3, class OTHER_INPUT4, class OTHER_OUTPUT>
	explicit CFunctionCaller4(const CFunctionCaller4<OTHER_INPUT1, OTHER_INPUT2, OTHER_INPUT3, OTHER_INPUT4, OTHER_OUTPUT>& other) : m_pObject(other.m_pObject), m_pStub(reinterpret_cast<stub_type>(other.m_pStub)) {}

	template <OUTPUT(*METHOD)(INPUT1, INPUT2, INPUT3, INPUT4)> static CFunctionCaller4<INPUT1, INPUT2, INPUT3, INPUT4, OUTPUT> SetFunction()
	{
		CFunctionCaller4 funct;
		funct.m_pObject = 0;
		funct.m_pStub = &functionStub<METHOD>;
		return funct;
	}

	template <OUTPUT(*METHOD)(INPUT1, INPUT2, INPUT3, INPUT4)>
	static OUTPUT functionStub(void* pObject, INPUT1 p1, INPUT2 p2, INPUT3 p3, INPUT4 p4) { return (*METHOD)(p1, p2, p3, p4); }

	template <class T, OUTPUT(T::*METHOD)(INPUT1, INPUT2, INPUT3, INPUT4)> static CFunctionCaller4<INPUT1, INPUT2, INPUT3, INPUT4, OUTPUT> SetMethod(T* pObject)
	{
		CFunctionCaller4 funct;
		funct.m_pObject = pObject;
		funct.m_pStub = &MethodStub<T, METHOD>;
		return funct;
	}

	template <class T, OUTPUT(T::*METHOD)(INPUT1, INPUT2, INPUT3, INPUT4)> static OUTPUT MethodStub(void* pObject, INPUT1 p1, INPUT2 p2, INPUT3 p3, INPUT4 p4)
	{
		T* p = static_cast<T*>(pObject);
		return (p->*METHOD)(p1,p2,p3,p4);
	}

	OUTPUT operator()(INPUT1 p1, INPUT2 p2, INPUT3 p3, INPUT4 p4) const { return (*m_pStub)(m_pObject, p1, p2, p3, p4); }

	inline const bool IsFunctionValid() const { return (m_pStub != nullptr); }
	inline const bool IsMethodValid() const { return (m_pStub != nullptr) && (m_pObject != nullptr); }

	void Clear() { m_pObject = nullptr; m_pStub = nullptr; }

	void*     m_pObject;
	stub_type m_pStub;
};
