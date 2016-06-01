#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;
class action
{
	int id;
	int stats_add[4]; // health/water/food/rest
	int chance_at_daytime[2]; //chance of success at daytime / nighttime
	int chance_of_longterm;
	string longterm_type;
	string name;

public:
	action(int i, string nam, int stats_ad[4],int chance_at[2],string type,int chance_long)
	{
		id=i;
		name=nam;
		longterm_type=type;
		chance_of_longterm=chance_long;

		for(int i=0;i<4;i++)stats_add[i]=stats_ad[i];
		for(int i=0;i<2;i++)chance_at_daytime[i]=chance_at[i];
	}
	string get_action_name() {return name;}
	int get_action_id() {return id;}
	int get_action_stat_single(int a) {return stats_add[a];}
	int get_action_chance_single(int a) {return chance_at_daytime[a];}
	string get_action_longterm_type() {return longterm_type;}
	int get_longterm_chance() {return chance_of_longterm;}
	int get_longterm_base_time() {return chance_at_daytime[1];}
};

class longaction : public action
{
	string name2,type;
	int atime;
public:
	longaction(int id, string name, int stats_add[4], int chance_at_daytime[2], string longterm_type, int chance_of_longterm, string nam2, string typ, int tim)
		: action(id,name,stats_add,chance_at_daytime,longterm_type,chance_of_longterm) 
		{
			name2=nam2;
			type=typ;
			atime=tim;
		}
	string get_longaction_name2() {return name2;}
	string get_longaction_type() {return type;}
	int get_longaction_time() {return atime;}
	void time_is_running_out(int a) {atime-=a;}
};
