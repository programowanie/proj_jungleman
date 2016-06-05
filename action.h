    /*! \file action.h
    \brief Biblioteka dodająca klasę Akcja i klasę Akcja Długoterminowa.
*/
#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;
//! Klasa Akcja. 
/*! Instancje tej klasy są podstawowym sposobem oddziaływania na Człowieka.
*/
class action
{
	int id; //!< Zmienna określająca ID danej akcji.

	//! Tablica 4 zmiennych akcji odpowiadających za zwiększanie/zmniejszanie statystyk człowieka.
	/* Kolejno: health/water/food/rest*/ 
	int stats_add[4]; 

	//! Tablica 2 zmiennych akcji odpowiadających za szansę jej wylosowania za dnia i w nocy.
	/* Kolejno: za dnia / w nocy*/ 
	int chance_at_daytime[2]; 
	int chance_of_longterm; //!<Zmienna określająca szansę wystąpienia akcji długoterminowej danego typu.
	string longterm_type; //!<Zmienna określająca typ możliwej do wystapienia akcji długoterminowej.
	string name; //!< Zmienna określająca nazwę akcji.

public:

	//! Konstruktor klasy. 
	/*!Nadaje:
	 \param stats_ad wartości podstawowych statystyk do zwiększenia / zmniejszenia
	 \param i wartość ID akcji
	 \param chance_at wartości szansy wylosowania akcji za dnia / w nocy
	 \param longtype typ możliwej do wystapienia akcji długoterminowej.
	 \param chance_long szansę wystąpienia akcji długoterminowej danego typu.
	 */
	action(int i, string nam, int stats_ad[4],int chance_at[2],string longtype,int chance_long)
	{
		id=i;
		name=nam;
		longterm_type=longtype;
		chance_of_longterm=chance_long;

		for(int i=0;i<4;i++)stats_add[i]=stats_ad[i];
		for(int i=0;i<2;i++)chance_at_daytime[i]=chance_at[i];
	}

	//! Funkcja-getter, zwraca nazwę akcji.
	string get_action_name() {return name;}

	//! Funkcja-getter, zwraca ID akcji.
	int get_action_id() {return id;}

	//! Funkcja-getter, zwraca wartość zwiększenia odpowiedniej statystyki człowieka.
	/*! Przyjmuje:
	\param a numer - którą statystykę należy zwiększyć*/
	int get_action_stat_single(int a) {return stats_add[a];}

	//! Funkcja-getter, zwraca szansę wystąpienia akcji.
	/*! Przyjmuje:
	\param a numer, dla którego zwraca szansę w dzień / w nocy*/
	int get_action_chance_single(int a) {return chance_at_daytime[a];}

	//! Funkcja-getter, zwraca typ możliwej akcji długoterminowej.
	string get_action_longterm_type() {return longterm_type;}

	//! Funkcja-getter, zwraca sznasę na akcję długoterminową.
	int get_longterm_chance() {return chance_of_longterm;}

	//! Dla Klasy pochodnej- \b akcji \b długoterminowej zwraca jej CZAS BAZOWY.
	/*! Czas bazowy przechowywany jest w miejscu "szansy wystąpienia w dzień"" dla klasy [AKCJA](@ref Action)*/
	int get_longterm_base_time() {return chance_at_daytime[1];}
};

//! Klasa Akcja Długoterminowa. 
/*! Instancje tej klasy są drugim z podstawowych sposobów oddziaływania na Człowieka.
	Wyróżniają się tym, że trwają przez określoną ilość dni.
	W pierwszym dniu wyświetlony jest jedynie komunikat o tym, że akcja zaczyna działać - przechowywany jako zmienna "name"
	W kolejnych dniach działania wyświetlany jest komunikat o działaniu akcji (zmienna "name2") + zaczyna ona oddziaływać na Człowieka.
*/
class longaction : public action
{

	string name2; //!< Zmienna określająca komunikat o tym, że akcja działa na człowieka.
	string type;	//!< Zmienna określająca typ akcji długoterminowej.
	int atime; //!< Zmienna określająca czas trwania akcji ðługoterminowej (w dniach).
public:
	//! Konstruktor klasy. 
	/*!	Oprócz wartości nadawanych przez konstruktor klasy Action, nadaje:
	 \param nam2 komunikat o tym, że akcja działa na człowieka.
	 \param typ typ akcji długoterminowej.
	 \param tim czas trwania akcji ðługoterminowej (w dniach).
	 */
	longaction(int id, string name, int stats_add[4], int chance_at_daytime[2], string longterm_type, int chance_of_longterm, string nam2, string typ, int tim)
		: action(id,name,stats_add,chance_at_daytime,longterm_type,chance_of_longterm) 
		{
			name2=nam2;
			type=typ;
			atime=tim;
		}

	//! Funkcja-getter, zwraca 2 komunikat akcji długoterminowej.
	string get_longaction_name2() {return name2;}

	//! Funkcja-getter, zwraca typ akcji długoterminowej.
	string get_longaction_type() {return type;}

	//! Funkcja-getter, zwraca długość trwania akcji długoterminową.
	int get_longaction_time() {return atime;}

	//! Funkcja zmniejszająca czas pozostały do końca trwania akcji długoterminowej
	/*! Przyjmuje:
	\param a wartość o jaką ma zmniejszyć czas trwania akcji długoterminowej
	*/
	void time_is_running_out(int a) {atime-=a;}
};
