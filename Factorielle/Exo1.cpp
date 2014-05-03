// Exo1.cpp : définit le point d'entrée pour l'application console.
//

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

#define calcul2fact(i)  Factorielle<i>::valeur,Factorielle<i+1>::valeur
int Factotab[10] ={calcul2fact(0),calcul2fact(2),calcul2fact(4),calcul2fact(6),calcul2fact(8)}; 


int factorielle(unsigned int N){
 if(N<10) return Factotab[N]; 
 cout<<"calculer au run time \n";
 return N*factorielle(N-1); 
}
 
// Factorielle<4>::valeur == 24
// Factorielle<0>::valeur == 1


int _tmain(int argc, _TCHAR* argv[])
{

	cout<<"factorielle(5)"<<factorielle(5)<<"\n" ;


	cout<<"factorielle(15)"<<factorielle(15)<<"\n" ;

	system("pause"); 

	return 0;
}

