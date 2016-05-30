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
using namespace std;

void death_announcement(int day,int daytime,string killer,string action);
void alive_announcement();
void get_me_some_action(vector<action>*vectorOfActions1,vector<action>*vectorOfActions2,string filename);

int main(int argc, char const *argv[])
{
	srand( time( NULL ) );

	int k = atoi(argv[2]);
	string filename = argv[1];
	
	int basic_stats[]={k,k,k,k};
	human Idler(basic_stats,0); //tworze czlowieka "Idler"
	
	get_me_some_action(nature::jungle()->set_jungle_response(),Idler.set_human_action(),filename); //-----------ładuje wektor akcji dla czlowieka i dla natury





for(int i=0;i<30;i++) //30 dni
{
			nature::jungle()->set(1,0,0); //nowy dzien,czas na nowa kryjowke: day/afternoon/safeplace
			//głód
			if(i!=0)Idler.organism(0);

	//poranne staty
	if(!Idler.check_status(k)) death_announcement(i,nature::jungle()->get_daytime(),nature::jungle()->get_killer(),Idler.last_action_name);
	Idler.show_stats(i,nature::jungle()->get_daytime()); 
	

	

			//robi cos rano
			Idler.do_something(nature::jungle()->get_daytime(),Idler.get_human_action( Idler.think(nature::jungle()->get_daytime(),nature::jungle()->get_afternoon()) ),nature::jungle()->get_safe_place(),nature::jungle()->random_nature_response());
	

	if(!Idler.check_status(k)) death_announcement(i,nature::jungle()->get_daytime(),nature::jungle()->get_killer(),Idler.last_action_name);



			//i popoludniem (zwraca safe place jesli takie znajdzie)
			nature::jungle()->set(1,1,Idler.do_something(nature::jungle()->get_daytime(),Idler.get_human_action(Idler.think(nature::jungle()->get_daytime(),1) ),nature::jungle()->get_safe_place(),nature::jungle()->random_nature_response()));
			


	
	if(!Idler.check_status(k)) death_announcement(i,nature::jungle()->get_daytime(),nature::jungle()->get_killer(),Idler.last_action_name);
	


			//noc
			nature::jungle()->set(2,0,3);
			//senność
			Idler.organism(1);

			//robi cos w nocy
			Idler.do_something(nature::jungle()->get_daytime(),Idler.get_human_action(Idler.think(nature::jungle()->get_daytime(),nature::jungle()->get_afternoon()) ),nature::jungle()->get_safe_place(),nature::jungle()->random_nature_response());
			
			

	//staty na dobranoc
	if(!Idler.check_status(k)) death_announcement(i,nature::jungle()->get_daytime(),nature::jungle()->get_killer(),Idler.last_action_name);
	Idler.show_stats(i,nature::jungle()->get_daytime());

	Idler.learn(1); //codziennie troche mądrzejszy

	if(i==29)alive_announcement();
}
	return 0;
}
