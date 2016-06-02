#include "human.h"
#include "action.h"


human::human(int construct_stats[4], int skill)
{
	for(int i=0;i<4;i++)stats[i]=construct_stats[i];
	survival_skill=skill;
} 

void human::show_stats(int i,int daytime)
{
	if (i==0&&daytime==1)printf("|Day | daytime |  HP | Hydrated | Stuffed |  Rested | Skill |\n");
	string _time;
	daytime==1?_time="morning":_time="evening";
	
	if(daytime==1)cout <<"-------------------------------------------------------------"<<endl;
	printf("| %2d | %s | %3d |  %4d    |  %3d    |  %4d   |  %3d  |\n",i+1,_time.c_str(),stats[0],stats[1],stats[2],stats[3],survival_skill);
	if(daytime==2)cout <<"-------------------------------------------------------------"<<endl<<endl;
}


void human::organism(int n)
{
	if(n==0) //w czasie dnia
	{
		stats[2]-=15; //hungry
		stats[1]-=32; //thirsty
	}
	else	//w nocy
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
	{
		if(stats[i]<0)stats[i]=0;
		if(stats[i]>k)stats[i]=k;
	}
	
	if(stats[0]==0) return 0; //is he alive?	
	else return 1;	
}

bool human::do_something(int daytime, action* chosen_action,bool safeplace,action* nature_response)
{
	last_nature_response=nature_response;
	last_human_action=chosen_action;

	//-----------------------------działanie czlowieka--------------------------

 	int chance=(*chosen_action).get_action_chance_single(daytime-1);

 	int fate=rand() % 100;
 	bool success;
 	if ((fate-chance-survival_skill)<0) //survival_skill sprawia, ze latwiej mu zakonczyc akcję sukcesem
 	{
 		for(int i=0;i<4;i++) stats[i]+=(*chosen_action).get_action_stat_single(i);
 		success=1;
 	}else success =0;

 	if((safeplace==1)&&((*chosen_action).get_action_name()=="trying to sleep")&&(success==1)) for(int i=0;i<4;i++) stats[i]+=(*chosen_action).get_action_stat_single(i);
 	//komunikat:
 	cout <<"Idler was "<<(*chosen_action).get_action_name();
 	if(success==1)cout<<" and he succeeded.";
 	else cout<<" but he failed.";

 	//dlugotrwale zdarzenie?:
 	longterm_success_h=0;
	if(success==1)	
	{
	 	if((*chosen_action).get_longterm_chance()!=0)
	 	{
	 		int fate2=rand() %100;
		 	if ((fate2-(*chosen_action).get_longterm_chance())<0) longterm_success_h=1; //efekty przyjdą później
	 	}
	}
 	
 	//-------------------------------odpowiedź natury---------------------------
 	int avoid_killers=rand() % 100;
 	bool positive_impact=0; //czy zdarzenie losowe jest dobre, czy nie? dobre mają numery 100-199
 	if((*nature_response).get_action_id()>=100 && (*nature_response).get_action_id()<200) positive_impact=1;
 	
 	//dlugotrwale zdarzenie?:
 	longterm_success_n=0;
 	
 	

 	 	
			if((*chosen_action).get_action_name()=="trying to sleep"&& safeplace==0) //bo podczas snu w bezpiecznym miejscu nie ma zagrozen,
		 	{
			 	if(avoid_killers>80 &&positive_impact==0) //podczas snu wystepuje o 80% mniej zdarzen losowych(bo go nie widać!) i jesli juz, to same złe
		 		{	
				 	for(int i=0;i<4;i++)
				 	stats[i]+=(*nature_response).get_action_stat_single(i);	//odpowiedź natury
				 	if((*nature_response).get_action_name()!="nothing")
				 	{
					 	cout  << " But he was "<<(*nature_response).get_action_name()<<"!";
						survival_skill++; //uczy sie czegos
						if((*nature_response).get_longterm_chance()!=0)
					 	{
					 		int fate3=rand() %100;
						 	if ((fate3-(*nature_response).get_longterm_chance())<0) longterm_success_n=1; //efekty przyjdą później
					 	}
					} 		
				}
		 	}
		 	if((*chosen_action).get_action_name()!="trying to sleep")
			{ 	
				if( avoid_killers>survival_skill &&positive_impact==0) //im jest sprytniejszy, tym wieksza ma szanse na unikniecie zagrozen
			 	{
			 		for(int i=0;i<4;i++)
				 	stats[i]+=(*nature_response).get_action_stat_single(i);	//odpowiedź natury
				 	if((*nature_response).get_action_name()!="nothing")
				 	{
					 	cout  << " But he was "<<(*nature_response).get_action_name()<<"!";
						survival_skill++; //uczy sie czegos
						if((*nature_response).get_longterm_chance()!=0)
					 	{
					 		int fate3=rand() %100;
						 	if ((fate3-(*nature_response).get_longterm_chance())<0) longterm_success_n=1; //efekty przyjdą później
					 	}
					}
			 	}
			 	if(positive_impact==1) 
			 	{
			 		for(int i=0;i<4;i++)
				 	stats[i]+=(*nature_response).get_action_stat_single(i);	//odpowiedź natury
				 	if((*nature_response).get_action_name()!="nothing")
				 	{
					 	cout  << " But he was "<<(*nature_response).get_action_name()<<"!";
						survival_skill++; //uczy sie czegos
						if((*nature_response).get_longterm_chance()!=0)
					 	{
					 		int fate3=rand() %100;
						 	if ((fate3-(*nature_response).get_longterm_chance())<0) longterm_success_n=1; //efekty przyjdą później
					 	}
					}
			 	}

			}
			cout<<endl;
	//--------------------------------------------------------------------------------
	

 	
 	if((success==1)&&((*chosen_action).get_action_name()=="looking for a safe place to sleep"))return success;
 	else return 0;
}

void human::effect_cause(longaction long_action)
{
	bool duplicate=0;
	for (vector<longaction>::iterator it = conditions.begin() ; it != conditions.end(); ++it) //żeby nie zapadł dwa razy na tę samą chorobę itd.
	{
		if((*it).get_action_name()==long_action.get_action_name()) duplicate=1;
	}

	if(!duplicate)conditions.push_back(long_action);
}

void human::longterm()
{
	vector<string>null_vector_names;
	for (vector<longaction>::iterator it = conditions.begin() ; it != conditions.end(); ++it)
	{
		if((*it).get_longterm_base_time()==(*it).get_longaction_time()) //jezeli to jest pierwsze wywołanie danej longakcji
		{
			cout << "This day, he also was "<<(*it).get_action_name() <<"."<<endl;

		(*it).time_is_running_out(1);
		}
		else if((*it).get_longaction_time()!=0) //jeżeli któreś z kolei wywołanie danej longakcji
		{
			cout << "He was also "<< (*it).get_longaction_name2() <<"."<<endl;
			for(int i=0;i<4;i++)
			stats[i]+=(*it).get_action_stat_single(i);

		(*it).time_is_running_out(1);
		}
		else if((*it).get_longaction_time()==0)
		{
			null_vector_names.push_back((*it).get_action_name());
			(*it).time_is_running_out(1);
		}
	}

	for(int j=0;j<null_vector_names.size();j++) //sprzątam "wykorzystane" longakcje, żeby mógł się zarazić czymś na nowo.
	{
		for (vector<longaction>::iterator it = conditions.begin() ; it != conditions.end(); ++it)
		{
			if((*it).get_action_name()==null_vector_names[j])
			{
				conditions.erase(it);
				break;
			}
		}
	}null_vector_names.clear();

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

void human::learn(int skill)
{
	survival_skill+=skill;
}