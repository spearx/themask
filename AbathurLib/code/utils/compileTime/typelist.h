#ifndef INC_TYPELIST_H_
#define INC_TYPELIST_H_

//important Typelist works only adding elements from tail

//typelist macros

#define TYPELIST_1(T1) TypeList<T1, NullType>
#define TYPELIST_2(T1,T2) TypeList<T1, TYPELIST_1(T2)>
#define TYPELIST_3(T1,T2,T3) TypeList<T1, TYPELIST_2(T2,T3)>
#define TYPELIST_4(T1,T2,T3,T4) TypeList<T1, TYPELIST_3(T2,T3,T4)>
#define TYPELIST_5(T1,T2,T3,T4,T5) TypeList<T1, TYPELIST_4(T2,T3,T4,T5)>
#define TYPELIST_6(T1,T2,T3,T4,T5,T6) TypeList<T1, TYPELIST_5(T2,T3,T4,T5,T6)>
#define TYPELIST_7(T1,T2,T3,T4,T5,T6,T7) TypeList<T1, TYPELIST_6(T2,T3,T4,T5,T6.T7)>
#define TYPELIST_8(T1,T2,T3,T4,T5,T6,T7,T8) TypeList<T1, TYPELIST_7(T2,T3,T4,T5,T6.T7,T8)>
#define TYPELIST_9(T1,T2,T3,T4,T5,T6,T7,T8,T9) TypeList<T1, TYPELIST_8(T2,T3,T4,T5,T6.T7,T8,T9)>
#define TYPELIST_10(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10) TypeList<T1, TYPELIST_9(T2,T3,T4,T5,T6.T7,T8,T9,T10)>
//... more if needed


namespace TL{
	
	template < class T, class U > 
	struct TypeList 
	{
		typedef T Head;
		typedef U Tail;
	};

	struct NullType{};

	//Length calculation
	template<class TList> struct Length;
	template<> struct Length<NullType>{	enum { value = 0 };	};
	template<class T, class U> struct Length< TypeList<T, U> >{ enum { value = 1 + Length<U>::value }; };

	//TypeAt (indexed acces)
	template<class TList, unsigned int i> struct TypeAt;
	template<class Head, class Tail> struct TypeAt<TypeList< Head, Tail >, 0>{ typedef Head result;	};
	
	template<class Head, class Tail, unsigned int i>
	struct TypeAt<TypeList<Head,Tail>,i>{
		//TODO add maximum compile time assert using Length
		typedef typename TypeAt<Tail, i - 1>::result result;
	};

	//IndexOf
	template<class TList, class T> struct IndexOf;
	template<class T> struct IndexOf<NullType, T>{ enum { value = -1 }; };
	template<class T, class Tail>	struct IndexOf<TypeList<T,Tail>, T>{ enum{ value = 0 }; };

	template<class Head, class Tail,class T>
	struct IndexOf<TypeList<Head,Tail>, T>
	{
	private:
		enum{ temp = IndexOf<Tail,T>::value };
	public:
		enum{ value = (temp == -1) ? -1 : 1 + temp };
	};
	
	//Append
	template <class TList, class T> struct Append;
	template <> struct Append<NullType,NullType>{ typedef NullType result; };
	template <class T> struct Append<NullType, T>{ typedef TYPELIST_1(T) result; };
	template <class Head, class Tail> struct Append<NullType,TypeList<Head,Tail> >{	typedef TypeList<Head,Tail> result; };
	template <class Head, class Tail, class T> struct Append<TypeList<Head,Tail>, T>{ typedef TypeList< Head, typename Append<Tail,T>::result > result;	};

	//Erase 
	template <class TList, class T> struct Erase;
	template <class T> struct Erase<NullType, T>{	typedef NullType result; };
	template <class T, class Tail> struct Erase<TypeList<T,Tail>, T>{ typedef Tail result; };
	template <class Head, class Tail, class T> struct Erase<TypeList<Head,Tail>, T>{ typedef TypeList<Head, typename Erase<Tail, T>::result> result; };

	//NoDuplicates
	template <class TList> struct NoDuplicates;
	template<> struct NoDuplicates<NullType>{ typedef NullType result; };
	
	template <class Head, class Tail> 
	struct NoDuplicates< TypeList<Head,Tail> >
	{
	private:
		typedef typename NoDuplicates<Tail>::result L1;
		typedef typename Erase<L1, Head>::result L2;
	public:
		typedef TypeList<Head,L2> result;
	};
};

//Typelist Instance

template <class TList> struct TypeListInstance;
template <class Head> struct TypeListInstance<TypeList<Head, NullType> >
{ 
	Head head; 

	TypeListInstance(){}
	TypeListInstance(va_list l){ head = va_arg(l,Head);	}
	TypeListInstance(Head h){ head h; }
};

template <class Head, class Tail> struct TypeListInstance<TypeList<Head,Tail> >
{ 
	Head head; 
	TypeListInstance<Tail> tail; 

	TypeListInstance(){}
	TypeListInstance(va_list l){
		head = va_arg(l,Head);
		tail = TypeListInstance<Tail>(l);
	};

	TypeListInstance(Head h,...){
		va_list ap;
		va_start( ap, h );
		head = h;
		tail = TypeListInstance<Tail>(ap);
		va_end( ap );
	}	
};


#define PODLIST_1(T1) TypeListInstance< TYPELIST_1(T1) >
#define PODLIST_2(T1,T2) TypeListInstance< TYPELIST_2(T1,T2) >
#define PODLIST_3(T1,T2,T3) TypeListInstance< TYPELIST_3(T1,T2,T3) >
#define PODLIST_4(T1,T2,T3,T4) TypeListInstance< TYPELIST_4(T1,T2,T3,T4) >
#define PODLIST_5(T1,T2,T3,T4,T5) TypeListInstance< TYPELIST_5(T1,T2,T3,T4,T5) >
#define PODLIST_6(T1,T2,T3,T4,T5,T6) TypeListInstance< TYPELIST_6(T1,T2,T3,T4,T5,T6) >
#define PODLIST_7(T1,T2,T3,T4,T5,T6,T7) TypeListInstance< TYPELIST_7(T1,T2,T3,T4,T5,T6,T7) >



#endif