// Factorielle.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

// Exo 1 
// Factorielle à la compilation en utilisant les enum 

#include "stdafx.h"
#include <iostream> 

using namespace std ; 
template <unsigned int N>
struct Factorielle 
{
   enum { valeur =  N * Factorielle<N-1>::valeur  };
};
 
template <>
struct Factorielle<0> 
{
   enum { valeur = 1 };
};


// Exercice 2 
// on veut calculer pour x <N fact(x) à la compilation et le reste au runtime 
// On utilise un tableau pour sauvegarder un certain nombre de valeur 
#define calcul2fact(i)  Factorielle<i>::valeur,Factorielle<i+1>::valeur
int Factotab[10] ={calcul2fact(0),calcul2fact(2),calcul2fact(4),calcul2fact(6),calcul2fact(8)}; 


int factorielle(unsigned int N){
 if(N<10) return Factotab[N]; 
 cout<<"calculer au run time \n";
 return N*factorielle(N-1); 
}
 
//Meilleure solution  utilisant une seule fonction facto

template<unsigned int n> struct fact {
  typedef fact<n-1> parent;
  static const int value = n * parent::value;
  static int f(int x) {
    return
    x > n ?  x*f(x-1) :   
    x == n ? value :
             parent::f(x);
  }
};
 
template<> struct fact<0> {
 static const int value  = 1 ;
  static int f(int x) { return x ? x * f(x-1) : value; }
};

int _tmain(int argc, _TCHAR* argv[])
{

	cout<<"factorielle(5)"<<factorielle(5)<<"\n" ;
	cout<<"factorielle(15)"<<factorielle(15)<<"\n" ;



	cout<<"factorielle(4)"<<fact<3>::f(4)<<"\n" ;
	cout<<"factorielle(3)"<<fact<3>::f(3)<<"\n" ;

	system("pause"); 

	return 0;
}


