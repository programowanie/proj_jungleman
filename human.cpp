#include "human.h"
#include "action.h"


human::human(int construct_stats[4])
{
	for(int i=0;i<4;i++)stats[i]=construct_stats[i];
} 


void human::show_stats(int i,int daytime)
{
	if (i==0&&daytime==1)printf("|Day | daytime |  HP | Hydrated | Stuffed |  Rested |\n");
	string _time;
	daytime==1?_time="morning":_time="evening";
	
	if(daytime==1)cout <<"-----------------------------------------------------"<<endl;
	printf("| %2d | %s | %3d |  %4d    |  %3d    |  %4d   |\n",i+1,_time.c_str(),stats[0],stats[1],stats[2],stats[3]);
	if(daytime==2)cout <<"-----------------------------------------------------"<<endl<<endl;
}


void human::organism(int n)
{
	if(n==0)
	{
		stats[2]-=10; //hungry
		stats[1]-=25; //thirsty
	}
	else
	{
		stats[3]-=30; //tired
		if(stats[1]<20)stats[0]-=40;	//podupada na zdrowiu lub zdrowieje
		if(stats[2]<20)stats[0]-=10;		
		if(stats[3]<20)stats[0]-=20; 
		if(stats[1]>80)stats[0]+=10;
		if(stats[2]>80)stats[0]+=15;		
		if(stats[3]>90)stats[0]+=15;
	}
}

bool human::check_status(int k)
{
	for(int i=0;i<4;i++)
		if(stats[i]<0)stats[i]=0;

	for(int i=0;i<4;i++)
		if(stats[i]>k)stats[i]=k;
	
	
	if(stats[0]==0)
	{
		return 0; //is he alive?	
	} 
	else return 1;	
}

bool human::do_something(int daytime, action* chosen_action,bool safeplace,action* nature_response)
{
 	int chance=(*chosen_action).get_action_chance_single(daytime-1);

 	int fate=rand() % 100;
 	bool success;
 	if ((fate-chance)<0)
 	{
 		for(int i=0;i<4;i++) stats[i]+=(*chosen_action).get_action_stat_single(i);
 		success=1;
 	}else success =0;

 	if((safeplace==1)&&((*chosen_action).get_action_name()=="trying to sleep")&&(success==1)) for(int i=0;i<4;i++) stats[i]+=(*chosen_action).get_action_stat_single(i);
 	//komunikat:
 	cout <<"Idler was "<<(*chosen_action).get_action_name();
 	if(success==1)cout<<" and he succeeded.";
 	else cout<<" but he failed.";

 	
 	int sleep_deep=rand() % 100;
 	 	
			if((*chosen_action).get_action_name()=="trying to sleep"&&last_action_name!="looking for a safe place to sleep") //podczas snu w bezpiecznym miejscu nie ma zagrozen
		 	{
			 	if(sleep_deep>80) //podczas snu wystepuje o 80% mniej zdarzen losowych
		 		{	
				 	for(int i=0;i<4;i++)
				 	stats[i]+=(*nature_response).get_action_stat_single(i);	//odpowiedź natury
				 	if((*nature_response).get_action_name()!="nothing")
				 	cout  << " But he was "<<(*nature_response).get_action_name()<<"!";	 	
				}
		 	}
		 	if((*chosen_action).get_action_name()!="trying to sleep")
			 	{
			 		for(int i=0;i<4;i++)
				 	stats[i]+=(*nature_response).get_action_stat_single(i);	//odpowiedź natury
				 	if((*nature_response).get_action_name()!="nothing")
				 	cout  << " But he was "<<(*nature_response).get_action_name()<<"!";
			 	}

	cout<<endl;

 	last_action_name=(*chosen_action).get_action_name();
 	if((success==1)&&((*chosen_action).get_action_name()=="looking for a safe place to sleep"))return success;
 	else return 0;
}



int human::think(int daytime,bool afternoon)
{
		if(stats[1]>=70&&stats[2]>=70&&stats[3]>=70) //staty (100-70)
		{
			if(daytime==1&&afternoon==0) return 0;
			if(daytime==1&&afternoon==1) return 1; //tylko jesli jest zdrowy bedzie szukał odpowiedniego miejsca do spania, inaczej to strata czasu
			else return 2;
		}
		else if(stats[1]>=50&&stats[2]>=50&&stats[3]>=50)// staty 70-50
			{
				if(daytime==1)
				{
					if((stats[1]<=stats[3])||(stats[2]<=stats[3])) return 0; //robi to czego mu potrzeba, ale tylko w dzien
					else return 2;						
				} 		
				else return 2;
			}else // staty 50-0
				{
					if((stats[1]<=stats[3])||(stats[2]<=stats[3])) return 0; //robi to czego mu potrzeba nawet w nocy
					else return 2;
				}
}