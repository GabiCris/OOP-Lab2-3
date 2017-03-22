#pragma once
#include "DomainCountry.h"
/*
Repository for Countries.
Contains: -Pointer to a dynamically alocated array of Countries struct;
		  -Integer current with the index of the last inserted country;
		  -Integer max signaling the current maximum capacity of the array.
*/
typedef struct countryRepo {
	Country* countryList = (Country*)malloc(10*sizeof(Country));
	int current = -1;
	int max = 10;
};
/*
Function which creates an object of type struct countryRepo and returns a pointer to it.
The struct is initialised with the following:
	-Dynammic array of size 10 Countries;
	-Current initialised with -1, signaling no countries in the array;
	-Max initialised with 10, the maximum capacity allocated to the array when initialised.
*/
countryRepo* create_repo();

/*
Function which frees the memory of the countryRepo at the given address.
*/
void destroy_repo(countryRepo* repo);

/*
Function which adds a specified country to a countryRepo.
The parameters are: a pointer to the countryRepo and a pointer to the new Country to be added.
If the countryList of the CountryRepo is already full, the array will be reallocated double the initial
size and then, the country will be added.
*/
void add_country(countryRepo* repo, Country* newCountry);
/*
Function which deletes a specified country to a countryRepo.
The parameters are: a char string to the country name.
If the country does not exist, a meesage is shown
*/
void del_country(countryRepo* repo, char* countryName);

/*
Function which updates a country with the given values.
Takes as parameters a repository, country name of the country to be updatedm new Continent and new population.
*/
void update_country(countryRepo* repo, char* countryName, char* newContinent, int newPop);

void migration_country(countryRepo* repo, char* fromCountry, char* toCountry, int amount);

void display_countries(countryRepo* repo, char* msg);

int check_duplicateCountries(countryRepo* repo, char* countryName);

Country* get_country(countryRepo* repo, char name[30]);

void repoTest();