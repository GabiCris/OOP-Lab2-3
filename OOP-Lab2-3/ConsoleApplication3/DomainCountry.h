#pragma once
#include <stdlib.h>
#include <stdio.h>

/*
Country Structure which contains the following:
	-pointer to a char, representing the address in mem. where the countryName will be stored;
	-pointer to a char, representing the address in mem. where the continent will be stored;
	-Integer representing the population (in millions).
*/
typedef struct Country
{
	char* countryName;
	char* continent;
	int population;
};


typedef struct Operation
{
	Country* country;
	int opName;
};

/*
Function which creates a country struct and then returns a pointer to it.
The parameters are:
	-pointer to a char representing the countryName;
	-pointer to a char representing the continent;
	-integer representing the population.
The function allocates memory for the new Country struct and all its attributes and
returns a pointer to the new Country.
*/
Country* create_country(char* countryName, char* continent, int population);

/*
Function which frees the memory occupied by a struct Country.
*/
void destroy_country(Country* country);

void print_country(Country c);

Operation* create_operation(Country* country, int);

void destroy_operation(Operation* op);

Country* deepCopy_country(Country*);








