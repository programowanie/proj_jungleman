#pragma once
#include "action.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class human{
	int stats[4]; //healthy; hydrated; stuffed; rested;
	int survival_skill;	//z kazdym dniem i z każdą przeżytą reakcją dzungli łatwiej mu zakonczyc sukcesem swoje akcje i uniknąć złych zdarzen
	vector<action> human_action;

	vector<longaction> conditions; //aktualne długotrwałe efekty działające na cżłowieka


	bool longterm_success_h; //te zmienne traktuje jako "pamięć"" mojego cżłowieka, bo przecież wie co mu sie przytrafiło ostatnio
	bool longterm_success_n;
	action* last_nature_response;
	action* last_human_action;

public:
	human(int construcs_stats[4], int skill);
	
	void organism(int n);
	bool check_status(int k);
	void show_stats(int i, int daytime);

	
	bool do_something(int daytime, action* chosen_action, bool safeplace,action* nature_response);
	void effect_cause(longaction long_action);
	void longterm();

	int think(int daytime, bool afternoon); 
	void learn(int);


	
	bool get_longterm_success_h() {return longterm_success_h;}
	bool get_longterm_success_n() {return longterm_success_n;}

	action* get_last_nature_response(){return last_nature_response;}
	action* get_last_human_action(){return last_human_action;}

	vector<action>* set_human_action() {return &human_action;} //vector of actions loading
	action* get_human_action(int i) {return &human_action[i];} //single action
};


