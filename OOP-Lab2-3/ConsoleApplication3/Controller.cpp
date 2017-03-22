#include "Controller.h"
#include <string.h>

Controller * create_controller(countryRepo* repo)
{
	Controller* ctrl = (Controller*)malloc(sizeof(Controller));
	ctrl->repo = repo;
	return ctrl;
}

void destroy_controller(Controller * ctrl)
{
	destroy_repo(ctrl->repo);
	free(ctrl);
}

void add_countryCtrl(Controller * ctrl, Country * country)
{
	add_country(ctrl->repo, country);
}

void del_countryCtrl(Controller * ctrl, char* countryName)
{
	del_country(ctrl->repo, countryName);
}

void update_countryCtrl(Controller * ctrl, char * countryName,  char * newContinent, int newPop)
{
	update_country(ctrl->repo, countryName, newContinent, newPop);
}

void migration_countryCtrl(Controller * ctrl, char * fromCountry, char * toCountry, int amount)
{
	migration_country(ctrl->repo, fromCountry, toCountry, amount);
}

void display_countriesCtrl(Controller * ctrl, char * msg)
{
	display_countries(ctrl->repo, msg);
}

void undo(Controller* ctrl, Operation * opList[100], int* opCount, int* current)
{
	if (*current < 0)
	{
		printf("No operation to undo!");
	}
	else
	{
		Operation* op = opList[*current];
	
		if (op->opName == 1)
			del_countryCtrl(ctrl, op->country->countryName);
			
		if (op->opName == 2)
			add_countryCtrl(ctrl, op->country);

		if (op->opName == 3)
			update_countryCtrl(ctrl, op->country->countryName, op->country->continent, op->country->population);

		(*current)--;
	}
}

void redo(Controller* ctrl, Operation * opList[100], int* opCount, int* current)
{
	if ((*current) == (*opCount))
		printf("No operation to redo!");
	else
	{
		Operation* op = opList[*current+1];

		if (op->opName == 2)
			del_countryCtrl(ctrl, op->country->countryName);

		if (op->opName == 1)
			add_countryCtrl(ctrl, op->country);

		if (op->opName == 3)
			update_countryCtrl(ctrl, op->country->countryName, op->country->continent, op->country->population);

		(*current)++;
	}
}
