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

void death_announcement(int day, int daytime, string killername, string action)
{	
	string _time,end;
	
	daytime==1?_time="morning":_time="evening";
	if(day==1||day==21)end="st";
	if(day==2||day==22)end="nd";
	if(day==3||day==23)end="rd";
	else end="th";

	if(killername=="nothing") killername="killed by his own apathy and weakness";


	printf("\n----------DEATH ANNOUNCEMENT-----------\n");
	printf("I.D. Ler died horribly in the %s\non the %d%s day of his tragic journey.\n",_time.c_str(),day+1,end.c_str());
	printf("He was unfortunately %s, while %s.\n---------------------------------------\n",killername.c_str(),action.c_str());
	exit(0);
}

void alive_announcement()
{	
	

	printf("\n-----------------ANNOUNCEMENT------------------\n");
	printf("I.D. Ler has survived in the jungle for 30 days.\n");
	printf("He was rescued by a group of natives.\n-----------------------------------------------\n");
	
}


void get_me_some_action(vector<action>*vectorOfActions1,vector<action>*vectorOfActions2,string filename)
{
	ifstream file;
	file.open(filename);

	if( file.good())
	{  	
		int id;
		string name;
		
		int stats_add[4];
		int chance_at_daytime[2];

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
	         
	        if(id<4)(*vectorOfActions2).push_back(action(id,name,stats_add,chance_at_daytime));	  
	        else (*vectorOfActions1).push_back(action(id,name,stats_add,chance_at_daytime));
        }if(id<4)(*vectorOfActions2).pop_back();
         else (*vectorOfActions1).pop_back();

	file.close();
	} else cout << "file access denied!" << endl;

}

