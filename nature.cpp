#include "nature.h"
#include "action.h"


nature *nature::jungl = 0;


nature *nature::jungle()
{
  if (!jungl)  jungl = new nature();
   
  return jungl;
}

void nature::set(int day,bool anoon,int place)
{
	daytime=day;
	afternoon=anoon;
	if(place!=2)
	safe_place=place;
}


action* nature::random_nature_response()
{
	int rand_max=0;
	
	for (vector<action>::iterator it = jungle_response.begin() ; it != jungle_response.end(); ++it)
    {
    	rand_max+=(*it).get_action_chance_single(daytime-1);
    }
    int fate=rand() % rand_max;
    int i;
    int sum=0;
    for (i = 0 ; i<= jungle_response.size(); i++)
    {
    	sum+=jungle_response[i].get_action_chance_single(daytime-1);
    	if(sum>=rand_max-fate) break;
    }
    killer=jungle_response[i].get_action_name();
    return &jungle_response[i];
}