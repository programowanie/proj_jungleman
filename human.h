#pragma once
#include "action.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class human{
	int stats[4]; //healthy; hydrated; stuffed; rested;
	int survival_skill;	
	vector<action> human_action;
	

public:
	human(int construcs_stats[4], int skill);
	
	void organism(int n);
	bool check_status(int k);
	void show_stats(int i, int daytime);
	
	bool do_something(int daytime, action* chosen_action, bool safeplace,action* nature_response);

	int think(int daytime, bool afternoon); 

	void learn(int);
	
	string last_action_name;
	
	vector<action>* set_human_action();
	action* get_human_action(int i);
};


