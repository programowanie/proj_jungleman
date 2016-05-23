#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;
class action
{

	int id;
	string name;


	int stats_add[4]; // health/water/food/rest
	int chance_at_daytime[2]; //chance of success at daytime / nighttime
public:
	action(int i, string nam, int stats_ad[4],int chance_at[2]);
	string get_action_name();
	int get_action_id();
	int get_action_stat_single(int a);
	int get_action_chance_single(int a);
};
