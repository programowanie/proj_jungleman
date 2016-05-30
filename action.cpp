#include "nature.h"
#include "action.h"

using namespace std;

action::action(int i, string nam, int stats_ad[4],int chance_at[2])
{
	id=i;
	name=nam;

	for(int i=0;i<4;i++)stats_add[i]=stats_ad[i];
	for(int i=0;i<2;i++)chance_at_daytime[i]=chance_at[i];
}

string action::get_action_name()
{
	return name;
}

int action::get_action_id()
{
	return id;
}

int action::get_action_stat_single(int a)
{	
	return stats_add[a];
}

int action::get_action_chance_single(int a)
{
	return chance_at_daytime[a];
}