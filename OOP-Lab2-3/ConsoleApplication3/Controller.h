#pragma once
#include "Repo.h"

/*
Controller struct which initialises a new countryRepo.
*/
typedef struct Controller {
	countryRepo* repo;
};

/*
Function which creates a controller, by allocating memory, while also calling
create_repo. Returns a pointer to the new Controller.
*/
Controller* create_controller(countryRepo* repo);

/*
Function which frees the memory allocated for a Controller struct.
*/
void destroy_controller(Controller* ctrl);
/*Function which adds a country to the controller by calling the
method in the repository.
Takes as params a controller and the address of the new country.
*/
void add_countryCtrl(Controller* ctrl, Country* country);

/*Function which deletes a country to the controller by calling the
method in the repository.
Takes as params a controller and the address of the new country.
*/
void del_countryCtrl(Controller* ctrl, char* countryName);

/*Function which updates a country to the controller by calling the
method in the repository.
Takes as params a controller and the new country name, continent and population.
*/
void update_countryCtrl(Controller* ctrl, char* countryName, char* newContinent, int newPop);

/*Function which migrates from a country to another to the controller by calling the
method in the repository.
Takes as params a controller and the address of from and to country and the amount of migration.
*/
void migration_countryCtrl(Controller* ctrl, char* fromCountry, char* toCountry, int amount);

/*Function which lists all country to the controller by calling the
method in the repository which contain the string stored in msg.
Takes as params a controller and the string with the message.
if message is empty all countries are listed
*/
void display_countriesCtrl(Controller* ctsrl, char* msg);

/*
Undo last action i.e. add, delete, update
*/
void undo(Controller* ctrl,Operation* opList[100], int * opCount, int*current);
/*
Redo last undo action
*/
void redo(Controller * ctrl, Operation * opList[100], int * opCount, int * current);

void ctrlTest();
