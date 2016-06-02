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
	int rand_max=0; //algorytm losowania z uwzglednieniem szansy wystapienia
	
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

longaction nature::get_longaction(action* last) 
{
    string _type; //pobieram sobie typ statniej akcji 
    _type=(*last).get_action_longterm_type();

    vector<longaction*>longactionsOfSpecyficType;
    for (vector<longaction>::iterator it = long_term_conditions.begin() ; it != long_term_conditions.end(); ++it)
    {
        if((*it).get_longaction_type()==_type)
        longactionsOfSpecyficType.push_back(&(*it));
    }

    //algorytm losowania longakcji z uwzglednieniem szansy wystapienia pomiędzy innymi longakcjami teog samego typu
    int rand_max=0;
    
    for (vector<longaction*>::iterator it = longactionsOfSpecyficType.begin() ; it != longactionsOfSpecyficType.end(); ++it)
    {
        rand_max+=(*it)->get_action_chance_single(0);
    }
    int fate=rand() % rand_max;
    int i;
    int sum=0;
    for (i = 0 ; i<= longactionsOfSpecyficType.size(); i++)
    {
        sum+=longactionsOfSpecyficType[i]->get_action_chance_single(0);
        if(sum>=rand_max-fate) break;
    }

    longaction to_return=*longactionsOfSpecyficType[i];
    longactionsOfSpecyficType.clear();
    
    return to_return;
}
