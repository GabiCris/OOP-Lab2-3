#include "Repo.h"
#include <stdlib.h>
#include <string.h>

countryRepo * create_repo()
{
	countryRepo* newRepo = (countryRepo*)malloc(sizeof(countryRepo));
	newRepo->countryList = (Country*)malloc(10 * sizeof(Country));
	newRepo->current = -1;
	newRepo->max = 10;
	return newRepo;
}

void destroy_repo(countryRepo* repo)
{
	free(repo->countryList);
	free(repo);
}

void add_country(countryRepo * repo, Country * newCountry)
{
	/*if (strcpy(newCountry->continent, "Europe\n") == 0 ||
		strcpy(newCountry->continent, "Asia\n") == 0 ||
		strcpy(newCountry->continent, "Africa\n") == 0 ||
		strcpy(newCountry->continent, "America\n") == 0 ||
		strcpy(newCountry->continent, "Australia\n") == 0)*/

		if (repo->current == repo->max - 1)
		{
			repo->max *= 2;
			repo->countryList = (Country*)realloc(repo->countryList, repo->max * sizeof(Country));
		}
		repo->current++;
		repo->countryList[repo->current] = *newCountry;
	

}

void del_country(countryRepo * repo, char* countryName)
{
	
	int i, k, n= repo->current;
	
	for (i = 0; i <= n; i++)
	{
		if (strcmp(repo->countryList[i].countryName, countryName) == 0)
		{
			k = i;
			break;
		}
	}
	//printf("%d", k);
	
	for (i = k; i <= repo->current - 1;i++)
		repo->countryList[i] = repo->countryList[i + 1];
	repo->current--;
}

void update_country(countryRepo * repo, char * countryName, char * newContinent, int newPop)
{
	int i, k, n = repo->current;

	for (i = 0; i <= n; i++)
	{
		if (strcmp(repo->countryList[i].countryName, countryName) == 0)
		{
			k = i;
			break;
		}
	}

	strcpy(repo->countryList[k].continent, newContinent);
	repo->countryList[k].population = newPop;
}

void migration_country(countryRepo * repo, char * fromCountry, char * toCountry, int amount)
{
	int i, k1, k2, n = repo->current;

	for (i = 0; i <= n; i++)
		if (strcmp(repo->countryList[i].countryName, fromCountry) == 0)
		{
			k1 = i;
			break;
		}

	for (i = 0; i <= n; i++)
		if (strcmp(repo->countryList[i].countryName, toCountry) == 0)
		{
			k2 = i;
			break;
		}
	
	repo->countryList[k1].population -= amount;
	repo->countryList[k2].population += amount;
}

void display_countries(countryRepo * repo, char * msg)
{
	int i, n = repo->current;
	for (i = 0; i <= n; i++)
		if (strstr(repo->countryList[i].countryName, msg) != NULL)
		{
			print_country(repo->countryList[i]);
			printf("\n");
		}
}

int check_duplicateCountries(countryRepo * repo, char * countryName)
{
	int i;
	for (i = 0; i <= repo->current; i++)
		if (strcmp(repo->countryList[i].countryName, countryName) == 0)
			return 0;
	return 1;
}

Country * get_country(countryRepo * repo, char name[30])
{
	int i;
	for (i = 0; i <= repo->current; i++)
		if (strcmp(repo->countryList[i].countryName, name) == 0)
			return &repo->countryList[i];
}
