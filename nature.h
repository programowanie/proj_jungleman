 /*! \file nature.h
    \brief Biblioteka dodająca klasę Natura.
*/
#pragma once
#include "action.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
//! Klasa Natura (singleton)
/*! Jest tylko jest jedna instancja tej klasy -> Jungle (jest to singleton)
	Przechowuje informacje o wszystkim co dzieje się poza Człowiekiem, posiada swoje akcje (reakcje na czynności człowieka).
*/
class nature //singleton
{
	//! Jedyna instancja tej klasy.
	static nature *jungl;
	//! Prywatny konstruktor
	nature() 
	{};

	int daytime; //!<aktualna pora dani 1 (rano/wieczór)
	bool afternoon; //!< aktualna pora dnia 2 (rano/popołudnie)
	int safe_place; //!< czy aktualne miejsce jest bezpieczne
	string killer; //!< nazwa ostatniej reakcji natury
	vector<action> jungle_response; //!< wektor przechowujący akcje natury
	vector<longaction> long_term_conditions; //!< wektor przechowujący akcje długoterminowe natury


public:
	//! Funkcja tworząca instancję klasy. 
	/*! Działa jako konstruktor */
	static nature *jungle();

	//!Funkcja zwracająca losową akcję natury.
	action* random_nature_response(); 

	//!Funkcja nadająca wartości:
	/*! 
	\param day aktualnej pory dnia 1 
	\param anoon aktualnej pory dnia 1
	\param place czy miejsce jest bezpieczne
	*/
	void set(int day,bool anoon,int place);

	//!Funkcja do załadowania wektora akcji, zwraca na niego wskaźnik
	vector<action>* set_jungle_response() {return &jungle_response;}

	//!Funkcja do załadowania wektora akcji długoterminowych, zwraca na niego wskaźnik
	vector<longaction>* set_long_term_conditions() {return &long_term_conditions;}

	//!Funkcja-getter, zwraca porę dnia 1
	int get_daytime() {return daytime;}

	//!Funkcja-getter, zwraca porę dnia 2
	bool get_afternoon() {return afternoon;}

	//!Funkcja-getter, zwraca info czy aktualne miejsce jest bezpieczne
	int get_safe_place() {return safe_place;}

	//!Funkcja-getter, zwraca nazwę ostatniej akcji natury
	string get_killer() {return killer;}

	//!Funkcja zwracająca losową akcję długoterminową określonego typu, bazującego na typie parametru:
	/*! \param last jest to wskaźnik na ostatnią akcję natury*/
	longaction get_longaction(action* last);

};




