#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "DomainCountry.h"
#include <stdlib.h>
#include <string.h>

Country * create_country(char* name, char* continent, int population)
{
	Country* newC = (Country*)malloc(sizeof(Country));
	newC->countryName = (char*)malloc(sizeof(name));
	newC->continent = (char*)malloc(sizeof(continent));

	strcpy(newC->countryName, name);
	strcpy(newC->continent, continent);

	newC->population = population;
	return newC;

}

void destroy_country(Country * country)
{
	free(country->continent);
	free(country->countryName);
	free(country);
}

void print_country(Country c)
{
	printf("Country Name: %s; Continent: %s; Population: %d; ", c.countryName, c.continent, c.population);
}

Operation* create_operation(Country * country, int opName)
{
	Operation* op = (Operation*)malloc(sizeof(Operation));
	op->opName = opName;
	op->country = create_country(country->countryName, country->continent, country->population);

	return op;
}

void destroy_operation(Operation * op)
{
	destroy_country(op->country);
	free(op);
}

Country * deepCopy_country(Country *c)
{
	Country* newC = create_country(c->countryName, c->continent, c->population);
	return newC;

}
