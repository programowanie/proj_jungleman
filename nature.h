#pragma once
#include "action.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class nature //singleton
{
	static nature *jungl;
	nature() 
	{};

	int daytime;
	bool afternoon;
	int safe_place;
	string killer;
	vector<action> jungle_response;

public:
	static nature *jungle();

	action* random_nature_response(); 

	void set(int day,bool anoon,int place);
	vector<action>* set_jungle_response();

	int get_daytime() {return daytime;}
	bool get_afternoon() {return afternoon;}
	int get_safe_place() {return safe_place;}
	string get_killer() {return killer;}
};



