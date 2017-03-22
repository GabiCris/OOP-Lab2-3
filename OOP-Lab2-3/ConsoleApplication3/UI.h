#pragma once
#include "Controller.h"
#include "DomainCountry.h"

/*
UI struct which initializez a new controler using the create_controller function.
*/
typedef struct UI {
	Controller* ctrl;
};

UI* create_UI(Controller* ctrl);

void appstart();

void read_cmd(char*);

void split_string(char[100][20], char[100]);

void bonus(UI * ui, int pop);

void input_newCountry(Country* newCountry);

void init_values(UI* ui);

void printRepoAscending(UI* ui);

void taskC(UI* ui, char continent[100], int pop, int);

void addToOpList(Operation* opList[100], int *opCount,int*, Country* c, int opName);