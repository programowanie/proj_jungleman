/*! \mainpage Opis

DOKUMENTACJA PROJEKTU JUNGLEMAN
========================================
Popiel Michał Wojciech

Program — survival mieszczucha w dżungli.
-----------------------------------------

Mieszczuch, posiadający kilka całkowicie zaspokojonych potrzeb, ( zdrowie, głód, pragnienie, sen ) zostaje porzucony w dżungli. Minie 30 dni(tur, kolejek) zanim odnajdzie go ekipa ratunkowa. Jego zadaniem jest przeżyć do tego momentu. Wraz z upływem czasu mieszczuch bardzo szybko zaczyna potrzebować jedzenia, snu, schronienia itd. 

Podejmuje więc różne akcje takie jak _poszukiwanie jedzenia_, _poszukiwanie schronienia_ itp. zależne od tego czego mu w danym momencie najbardziej brakuje, a także od pory dnia. Akcje mogą zakończyć się powodzeniem lub fiaskiem z odpowiednim prawdopodobieństwem. W przeżyciu mieszczucha przeszkadzają najróżniejsze zdarzenia losowe:

- dzikie zwierzęta, 
- zanieczyszczona woda, 
- kanibale 
- itd. 

Mogące wystąpić z odpowiednim prawdopodobieństwem w zależności od akcji mieszczucha i pory dnia. 

Program wyświetla podsumowania codziennego zmagania mieszczucha z przyrodą wraz z informacją czy udało mu się przeżyć. 


*/

/*! \file main.cpp
\brief Główny plik wykonywalny.
*/
#include "human.h"
#include "action.h"
#include "nature.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <unistd.h>
using namespace std;
//! Funkcja wyświetlająca raport o śmierci.
	/*! Tylko jeśli zginie. Przyjmuje parametry:
	\param day numer dnia
	\param daytime porę dnia
	\param killer ostatnią reakcję natury
	\param action ostatnią akcję człowieka.
	*/
void death_announcement(int day,int daytime,string killer,string action);

//! Funkcja wyświetlająca informację o przetrwaniu człowieka.
	/*! Tylko jeśli przeżyje 30 dni.
	*/
void alive_announcement();

//! Funkcja która ładuje wektory akcji i akcji długoterminowych dla Natury i Człowieka.
	/*! Przyjmuje parametry:
	\param natureActions wskaźnik na wektor akcji natury
	\param humanActions wskaźnik na wektor akcji człowieka
	\param longtermActions wskaźnik na wektor akcji długoterminowych natury
	\param filename nazwa pliku z bazą danych.
	*/
void get_me_some_action(vector<action>*natureActions,vector<action>*humanActions,vector<longaction>*longtermActions,string filename);

//! Główna funkcja programu. 
/*! Nadaje warunki początkowe (wywołuje konstruktory klas Człowiek i Natura, uzupełnia wektory akcjami z bazy danych),
zawiera pętlę czynności które wykonuje człowiek w ciągu dnia. Pętla powtarza się 30 razy (30 dni).
Funkcja main() zawiera też odwołania do funkcji wyświetlających informacje o zgonie / przeżyciu człowieka.
Przyjmuje argumenty:
\param argc określa liczbę argumentów
\param argv kolejne argumenty:
- nazwa pierwszej bazy danych (akcji)
- nazwa drugiej bazy danych (akcji długoterminowych)
- liczba określająca wartość początkową statystk Człowieka.
*/
int main(int argc, char const *argv[])
{
	srand( time( NULL ) );

	int k = atoi(argv[3]);
	string filename1 = argv[1];
	string filename2 = argv[2];
	
	int basic_stats[]={k,k,k,k};
	human Idler(basic_stats,0); //tworze czlowieka "Idler"
	
	get_me_some_action(nature::jungle()->set_jungle_response(),Idler.set_human_action(),nature::jungle()->set_long_term_conditions(),filename1); //-----------ładuje wektor akcji dla czlowieka i dla natury
	get_me_some_action(nature::jungle()->set_jungle_response(),Idler.set_human_action(),nature::jungle()->set_long_term_conditions(),filename2); //-----------ładuje wektor longakcji


unsigned int uslp=500000;
for(int i=0;i<30;i++) //30 dni
{
			nature::jungle()->set(1,0,0); //nowy dzien,czas na nowa kryjowke: (day,afternoon,safeplace)
			//głód
			if(i!=0)Idler.organism(0);



	//poranne staty
	if(!Idler.check_status(k)) death_announcement(i,nature::jungle()->get_daytime(),nature::jungle()->get_killer(),Idler.get_last_human_action()->get_action_name());
	Idler.show_stats(i,nature::jungle()->get_daytime()); 
	usleep(uslp);

	

			//robi cos rano
			Idler.do_something(nature::jungle()->get_daytime(),Idler.get_human_action( Idler.think(nature::jungle()->get_daytime(),nature::jungle()->get_afternoon()) ),nature::jungle()->get_safe_place(),nature::jungle()->random_nature_response());
			if(Idler.get_longterm_success_h()) Idler.effect_cause(nature::jungle()->get_longaction(Idler.get_last_human_action()));
			if(Idler.get_longterm_success_n()) Idler.effect_cause(nature::jungle()->get_longaction(Idler.get_last_nature_response()));
			usleep(uslp);


	if(!Idler.check_status(k)) death_announcement(i,nature::jungle()->get_daytime(),nature::jungle()->get_killer(),Idler.get_last_human_action()->get_action_name());



			//i popoludniem (zwraca safe place jesli takie znajdzie)
			nature::jungle()->set(1,1,Idler.do_something(nature::jungle()->get_daytime(),Idler.get_human_action(Idler.think(nature::jungle()->get_daytime(),1) ),nature::jungle()->get_safe_place(),nature::jungle()->random_nature_response()));
			if(Idler.get_longterm_success_h()) Idler.effect_cause(nature::jungle()->get_longaction(Idler.get_last_human_action()));
			if(Idler.get_longterm_success_n()) Idler.effect_cause(nature::jungle()->get_longaction(Idler.get_last_nature_response()));
			usleep(uslp);

	
	if(!Idler.check_status(k)) death_announcement(i,nature::jungle()->get_daytime(),nature::jungle()->get_killer(),Idler.get_last_human_action()->get_action_name());
	


			//noc
			nature::jungle()->set(2,0,3);
			//senność
			Idler.organism(1);

			//robi cos w nocy
			Idler.do_something(nature::jungle()->get_daytime(),Idler.get_human_action(Idler.think(nature::jungle()->get_daytime(),nature::jungle()->get_afternoon()) ),nature::jungle()->get_safe_place(),nature::jungle()->random_nature_response());
			if(Idler.get_longterm_success_h()) Idler.effect_cause(nature::jungle()->get_longaction(Idler.get_last_human_action()));
			if(Idler.get_longterm_success_n()) Idler.effect_cause(nature::jungle()->get_longaction(Idler.get_last_nature_response()));
			usleep(uslp);
			Idler.longterm(); //sprawdza co tam sobie siedzi w wektorze longakcji
			

	//staty na dobranoc
	if(!Idler.check_status(k)) death_announcement(i,nature::jungle()->get_daytime(),nature::jungle()->get_killer(),Idler.get_last_human_action()->get_action_name());
	Idler.show_stats(i,nature::jungle()->get_daytime());
	usleep(uslp);

	Idler.learn(1); //codziennie troche mądrzejszy

	if(i==29)alive_announcement();
	usleep(2000000);

}
	return 0;
}
