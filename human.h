#pragma once
#include "action.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;
/*! \file human.h
    \brief Biblioteka dodająca klasę Człowiek.
*/

//! Klasa Człowiek.
/*!
	Odpowiada za wszystko co robi człowiek.
*/
class human{
	//! Statystki człowieka.
	/*! W kolejności: zdrowie, napojenie, najedzenie, wypoczęcie */
	int stats[4];
	//! Umiejętność przetrwania.
	/*!Zz kazdym dniem i z każdą przeżytą reakcją dzungli, łatwiej mu zakończyc sukcesem swoje akcje i uniknąć złych zdarzen. */
	int survival_skill;	
	vector<action> human_action; //!< Wektor składujący akcje człowieka.

	vector<longaction> conditions; //!< Wektor składujący aktualne długotrwałe efekty działające na cżłowieka.


	bool longterm_success_h; //!< zmienna określająca czy ostatnia akcja człowieka zakończyła sie sukcesem. "pamięć" cżłowieka.
	bool longterm_success_n; //!< zmienna określająca czy ostatnia reakcja natury zakończyła sie sukcesem. "pamięć" cżłowieka.
	action* last_nature_response;	//!< zmienna określająca ostatnią reakcję natury. "pamięć" cżłowieka.
	action* last_human_action; //!< zmienna określająca ostatnią akcję człowieka. "pamięć" cżłowieka.

public:
	//! Konstruktor klasy. 
	/*!Nadaje:
	 \param construcs_stats podstawowe statystyki
	 \param skill wartość umiejętności przetrwania
	 */
	human(int construcs_stats[4], int skill); 

	//! Funkcja sprawdzająca, czy człowiek żyje.
	/*! W przypadku śmierci wyświetla komunikat.
	*/
	bool check_status(int k);

	//! Funkcja wyświetlająca statystki.
	/*! Przyjmuje parametry:
	\param i numer dnia
	\param daytime porę dnia
	*/
	void show_stats(int i, int daytime);

	//! Funkcja określająca wykonywanie akcji przez człowieka i reakcji przez naturę.
	/*! Przyjmuje parametry:
	\param daytime porę dnia
	\param chosen_action konkretną akcja którą wykonuje człowiek
	\param safeplace czy znajduje się w bezpiecznym miejscu
	\param nature_response konkretną reakcję natury
	*/
	bool do_something(int daytime, action* chosen_action, bool safeplace,action* nature_response);

	//! Funkcja dodająca akcję długoterminową do wektora takich akcji działających na człowieka.
	/*! Przyjmuje parametry:
	\param long_action wybraną akcję długoterminową
	*/
	void effect_cause(longaction long_action);

	//! Funkcja wywołująca wszystkie akcje długoterminowe działające na człowieka.
	void longterm();

	//! Funkcja wybierająca dla człowieka akcję, którą wykona.
	/*! Przyjmuje parametry:
	\param daytime porę dnia 1
	\param afternoon porę dnia 2
	*/
	int think(int daytime, bool afternoon); 

	//! Funkcja zwiększająca umiejętność przetrwania.
	void learn(int);

	//! Funkcja obniżająca statystyki człowieka bazując na porze dnia:
	/*! \param n pora dnia*/
	void organism(int n);

	//! Funkcja-getter, zwraca info o sukcesie ostatniej akcji człowieka.
	bool get_longterm_success_h() {return longterm_success_h;}

	//! Funkcja-getter, zwraca info o sukcesie ostatniej reakcji natury.
	bool get_longterm_success_n() {return longterm_success_n;}

	//! Funkcja-getter,zwraca wskaźnik na ostatnią reakcję natury.
	action* get_last_nature_response(){return last_nature_response;}

	//! Funkcja-getter,zwraca wskaźnik na ostatnią akcję człowieka.
	action* get_last_human_action(){return last_human_action;}

	//! Funkcja do ładowania wektora akcji człowieka.
	vector<action>* set_human_action() {return &human_action;} //vector of actions loading
	//! Funkcja-getter, zwraca konkretną akcję z wektora akcji człowieka
	/*!Przyjmuje paramter:
	\param i miejsce, na jakim jest wybrana akcja w wektorze akcji
	*/
	action* get_human_action(int i) {return &human_action[i];} //single action
};


