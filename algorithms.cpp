       /*! \file algorithms.cpp
    \brief Plik zawierający funkcje poboczne, wykorzystywane w pliku main.cpp.
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

void death_announcement(int day, int daytime, string killername, string action)
{	
	string _time,end;
	
	daytime==1?_time="morning":_time="evening";
	if(day==1||day==21)end="st";
	if(day==2||day==22)end="nd";
	if(day==3||day==23)end="rd";
	else end="th";

	if(killername=="nothing") killername="killed by his own apathy and weakness";
	usleep(3000000);

	printf("\n----------DEATH ANNOUNCEMENT-----------\n");
	printf("I.D. Ler died horribly in the %s\non the %d%s day of his tragic journey.\n",_time.c_str(),day+1,end.c_str());
	printf("He was unfortunately %s, while %s.\n---------------------------------------\n",killername.c_str(),action.c_str());
	exit(0);
}

void alive_announcement()
{	
	printf("\n-----------------ANNOUNCEMENT------------------\n");
	printf("I.D. Ler has survived in the jungle for 30 days.\n");
	printf("He was finally rescued by a rescue crew.\n-----------------------------------------------\n");
	
}


void get_me_some_action(vector<action>*NATURE,vector<action>*HUMAN,vector<longaction>*Longterm,string filename)
{
	/* Akcje 1,2,3 =akcje czlowieka
		<4,99> =reakcje "złe"
		<100,199> =reakcje "dobre"
		200+ =długotrwałe */
	ifstream file;
	file.open(filename);

	if( file.good())
	{  	
		int id;
		int long_chance;
		string name;
		string long_type;
		
		int stats_add[4];
		int chance_at_daytime[2];

		string name2;
		string type;
		int atime;

		string phrase;
		string row;
	
	     while( !file.eof() )
        {
     		getline(file, row, '\n');
			istringstream line(row);

	            getline( line, phrase, ',' );
	            id=atoi(phrase.c_str());
	            
	            getline( line, name, ',' );

	            for(int i=0;i<4;i++)
	            {
	            	getline( line, phrase, ',' );
	           		stats_add[i]=atoi(phrase.c_str());
	        	}

	            for(int i=0;i<2;i++)
	            {
	            	getline( line, phrase, ',' );
	           		chance_at_daytime[i]=atoi(phrase.c_str());
	        	}
	        	getline( line, long_type, ',' );

	        	getline( line, phrase, ',' );
	            long_chance=atoi(phrase.c_str());

	            if(id>=200)
	            {
	            	getline( line, type, ',' );
	            	getline( line, name2, ',' );

	            	getline( line, phrase, ',' );
	           		atime=atoi(phrase.c_str());
	            }
	            

	        if(id<4)(*HUMAN).push_back(action(id,name,stats_add,chance_at_daytime,long_type,long_chance));	  
	        else if(id<200)(*NATURE).push_back(action(id,name,stats_add,chance_at_daytime,long_type,long_chance));
	        else (*Longterm).push_back(longaction(id,name,stats_add,chance_at_daytime,long_type,long_chance,name2,type,atime));
        }if(id<4)(*HUMAN).pop_back();
        else if(id<200) (*NATURE).pop_back();

	file.close();
	} else cout << "file access denied!" << endl;

}

