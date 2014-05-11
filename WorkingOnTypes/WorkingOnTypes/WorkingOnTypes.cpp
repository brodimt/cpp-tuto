// WorkingOnTypes.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include<iostream> 
#include <typeinfo> 
using namespace std; 



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

