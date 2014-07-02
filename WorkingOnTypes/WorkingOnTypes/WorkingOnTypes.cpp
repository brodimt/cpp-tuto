// WorkingOnTypes.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include<iostream> 
#include <typeinfo> 
using namespace std; 

template<class T, T v> struct value_ { static const T value = v;  };
template<bool v> using bool_ = value_<bool, v>;
using true_ = bool_<true>;
using false_ = bool_<false>;
template<int v> using int_ = value_<int, v>;
using zero_ = int_<0>;
template<class A, class B> using add_ = int_<A::value + B::value>;

template<class T> struct type_ { using type = T; };
template<class A, class B> struct same_ : false_ {};
template<class A> struct same_<A, A> : true_{};

template<typename A> struct is_pointer_ : false_{};
template<typename A> struct is_pointer_<A*> : true_{};
template<typename A> struct is_pointer_<A* const> : true_{};

static_assert(same_< zero_, add_<zero_, zero_> >::value,"add 0");
static_assert(is_pointer_<int* const>::value, "is pointer");



struct s1 {
	using toto = int;
};
struct s2 {
	using tata = int;
};
struct s3 {};
struct s4 : s1 {};

HAS_TYPE(T, type) = bool(T::type existe et est un type);

static_assert(HAS_TYPE(s1, toto), "s1");
static_assert(!HAS_TYPE(s2, toto), "s2");
static_assert(!HAS_TYPE(s3, toto), "s3");
static_assert(HAS_TYPE(s4, toto), "s4");
static_assert(HAS_TYPE(float, toto), "float");

/*
struct Toto {};
typedef const Toto Const_Toto; 


template <typename T, typename U> 
struct same_type {
	static  const bool value = false;

};

template<typename T>
struct same_type<T,T>{
	static const bool value = true;
};

template <typename T>
struct is_constant{
	static const bool value = false; 
};

template<typename T>
struct is_constant<const T> {
	static const bool value = true;
};


template <typename T>
struct is_apointer{
	static const bool value = false;
};

template<typename T>
struct is_apointer<T*> {
	static const bool value = true;
};

template<typename T> 
struct make_const 
{ 
	typedef const T type; 
};


int _tmain(int argc, _TCHAR* argv[])
{
	cout << " HEllo W ! \n ";
	int a(45); 
	int b(45);
	int ints[12]; 
	cout <<"same_type<int,int>::value  ->"<< same_type<int,int>::value << "\n"; 
	cout <<"same_type<Toto, Toto>::value ->" <<same_type<Toto, Toto>::value << "\n";
	cout <<"same_type<Toto, Const_Toto>::value " << same_type<Toto, Const_Toto>::value << "\n";
	cout << "same_type<Const_Toto, make_const<Toto>::type>::value ->" << same_type<Const_Toto, make_const<Toto>::type>::value << "\n";
	system("pause");
	return 0;
	
}

*/