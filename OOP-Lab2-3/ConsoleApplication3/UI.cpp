#include "UI.h"
#include <string.h>

UI * create_UI(Controller* ctrl)
{
	UI* ui = (UI*)malloc(sizeof(UI));
	ui->ctrl = ctrl;
	return ui;
}
void appstart()
{
	countryRepo* repo = create_repo();
	Controller* ctrl = create_controller(repo);
	UI* ui = create_UI(ctrl);
	init_values(ui);

	int amount;
	char cmd[100], countryName[30], name2[30], continent[30];
	char commandSplit[100][20];
	printf("Welcome to the most innovative and comprehensive WORLD POPULATION MONITORING app!!!\n");
	printf("In order to display all this application has to offer, type \"commands\" \n");

	int opCount=-1, current =-1;
	Operation* opList[100];

	while (1)
	{
		read_cmd(cmd);
	
		if (strcmp(cmd, "exit") == 0)
		{
			destroy_controller(ctrl);
			free(ui);
			exit(1);
		}
		else if (strcmp(cmd, "commands") == 0)
		{
			printf("-> \"add\" to add a country;\n");
			printf("-> \"delete\" to delete a country;\n");
			printf("-> \"list\" to list all countries in no specific order;\n");
			printf("-> \"update\" to update a country;\n");
			printf("-> \"migration\" to migrate from a country to another;\n");
			printf("-> \"display\" to list all countries containing a specified string or all countries if no string is given;\n");
			printf("-> \"lab\" for LAB ACTIVITY;\n");
			printf("-> \"taskC\" for the display task from c);\n");
			printf("-> \"undo\" to undo last command;\n");
			printf("-> \"redoC\" to redo last undo command;\n");
			printf("-> \"bonus1\" to display all countries whose popoulation is smaller than an input;\n");
			printf("-> \"redoC\" to redo last undo command;\n");
		}
		else if (strcmp(cmd, "list") == 0)
		{
			int i;
			for (i = 0; i <= ui->ctrl->repo->current; i++)
			{
				print_country(ui->ctrl->repo->countryList[i]);
				printf("\n");
			}
		}
		else if (strcmp(cmd, "display") == 0)
		{
			fgetc(stdin);
			printf("Search for countries with keyword: ");
			fgets(countryName, 100, stdin);
			//printf("..%s..", countryName)
			if (countryName[0] == '\n')
			{
				int i;
				for (i = 0; i <= ui->ctrl->repo->current; i++)
				{
					print_country(ui->ctrl->repo->countryList[i]);
					printf("\n");
				}
			}
			else
			{
				countryName[strlen(countryName) - 1] = '\0';
				display_countriesCtrl(ui->ctrl, countryName);
			}
		
		}
		else if (strcmp(cmd, "lab") == 0)
		{
			printRepoAscending(ui);
		}
		else if (strcmp(cmd, "taskC") == 0)
		{
			int pop, ascDesc;
			fgetc(stdin);
			printf("Continent: ");
			fgets(continent, 100, stdin);
			printf("Min Population: ");
			scanf("%d", &pop);
			printf("Press 1 for ASCENDING!\nPress 2 for DESCENDING!\nYour choice: ");
			scanf("%d", &ascDesc);
			continent[strlen(continent) - 1] = '\0';
			taskC(ui, continent, pop, ascDesc);
		}
		//split_string(commandSplit, cmd);		
		else if (strcmp(cmd, "add") == 0)
		{
			Country* newCountry=(Country*)malloc(sizeof(Country));
			input_newCountry(newCountry);
			addToOpList(opList, &opCount, &current, newCountry, 1);

			if (check_duplicateCountries(ui->ctrl->repo, newCountry->countryName) == 1)
				add_countryCtrl(ui->ctrl, newCountry);
			else
				printf("Country already stored in the application!");
	
		}
		else if (strcmp(cmd, "delete") == 0)
		{
			printf("Name of the country to be razed to the ground: ");
			scanf("%s", countryName);
			addToOpList(opList, &opCount, &current, get_country(ui->ctrl->repo, countryName), 2);

			if (check_duplicateCountries(ui->ctrl->repo, countryName) == 0)
				del_countryCtrl(ui->ctrl, countryName);
			else
				printf("No country with that name in the database!");
		}
		else if (strcmp(cmd, "update") == 0)
		{
			printf("Name of the country to be updated: ");
			scanf("%s", countryName);
			printf("New Continent of the Country: ");
			scanf("%s", continent);
			printf("New Population of the Country: ");
			scanf("%d", &amount);

			addToOpList(opList, &opCount, &current, get_country(ui->ctrl->repo, countryName), 3);
			update_countryCtrl(ui->ctrl, countryName, continent, amount);

		}
		else if (strcmp(cmd, "migration") == 0)
		{
			printf("Country FROM which people flee: ");
			scanf("%s", name2);
			printf("Country TO which people go in search of a better life: ");
			scanf("%s", continent);
			printf("Number of migrants: ");
			scanf("%d", &amount);
			migration_countryCtrl(ui->ctrl, name2, continent, amount);
		}
		else if (strcmp(cmd, "undo") == 0)
		{
			undo(ctrl, opList, &opCount, &current);
		}
		else if (strcmp(cmd, "redo") == 0)
		{
			redo(ctrl, opList, &opCount, &current);
		}
		else if (strcmp(cmd, "bonus1") == 0)
		{
			int pop;
			printf("Input maximum population: ");
			scanf("%d", &pop);
			bonus(ui, pop);
		}
		printf("\n");

	}
}

void read_cmd(char* cmd)
{
	printf("Your wish is my command: ");
	scanf("%s", cmd);
}

void split_string(char commandSplit[100][20], char cmd[100])
{
	int i = -1;
	char * word;
	word = strtok(cmd, ";");
	while (word != NULL)
	{
		printf("%s", word);
		word[strlen(word)] = '\0';
		//printf("%s", strlen(word));
		strcpy(commandSplit[++i], word);
		word = strtok(NULL, ";");
	}
	strcpy(commandSplit[++i] ,"\0");

}

void printRepoAscending(UI* ui)
{
	int i, j;
	Country aux;
	for (i = 0; i<=ui->ctrl->repo->current; i++)
		for (j = i+1; j<=ui->ctrl->repo->current; j++)
			if (strcmp(ui->ctrl->repo->countryList[i].continent, ui->ctrl->repo->countryList[j].continent) > 0)
			{
				aux = ui->ctrl->repo->countryList[i];
				ui->ctrl->repo->countryList[i] = ui->ctrl->repo->countryList[j];
				ui->ctrl->repo->countryList[j] = aux;
			}
	for (i = 0; i <= ui->ctrl->repo->current; i++)
	{
		print_country(ui->ctrl->repo->countryList[i]);
		printf("\n");
	}

}

void taskC(UI* ui, char continent[100], int pop, int ascDesc)
{
	int i, k = -1, j;
	Country* newList = (Country*)malloc(ui->ctrl->repo->max * sizeof(Country));
	Country aux;

	if (!continent[0])
	{
		for (i = 0; i <= ui->ctrl->repo->current; i++)
			if (ui->ctrl->repo->countryList[i].population > pop)
				newList[++k] = ui->ctrl->repo->countryList[i];
	}
	else
	{
		for (i = 0; i <= ui->ctrl->repo->current; i++)
			if (ui->ctrl->repo->countryList[i].population > pop && strcmp(ui->ctrl->repo->countryList[i].continent, continent)== 0)
				newList[++k] = ui->ctrl->repo->countryList[i];
	}

	if (ascDesc == 1)
	{
		for (i = 0; i <= k; i++)
			for (j = i + 1; j <= k; j++)
				if (newList[i].population > newList[j].population)
				{
					aux = newList[i];
					newList[i] = newList[j];
					newList[j] = aux;
				}
	}
	else
	{
		for (i = 0; i <= k; i++)
			for (j = i + 1; j <= k; j++)
				if (newList[i].population < newList[j].population)
				{
					aux = newList[i];
					newList[i] = newList[j];
					newList[j] = aux;
				}
	}

	for (i = 0; i <= k; i++)
	{
		print_country(newList[i]);
		printf("\n");
	}

	free(newList);
}

void bonus(UI* ui, int pop)
{
	int i, k = -1, j;
	Country* newList = (Country*)malloc(ui->ctrl->repo->max * sizeof(Country));
	for (i = 0; i <= ui->ctrl->repo->current; i++)
		if (ui->ctrl->repo->countryList[i].population < pop)
			newList[++k] = ui->ctrl->repo->countryList[i];
	for (i = 0; i <= k; i++)
	{
		print_country(newList[i]);
		printf("\n");
	}

}
void input_newCountry(Country* newCountry)
{
	char name[100], continent[100];
	int pop;

	printf("\nNew Country Name: ");
	scanf("%s", name);
	name[strlen(name)-1] = '\0';
	printf("New Country Continent: ");
	scanf("%s", continent);
	continent[strlen(continent)-1] = '\0';
	printf("New Country Population(in millons): ");
	scanf("%d", &pop);

	
	newCountry->countryName = (char*)malloc(sizeof(name));
	newCountry->continent = (char*)malloc(sizeof(continent));
	strcpy(newCountry->continent, continent);
	strcpy(newCountry->countryName, name);
	newCountry->population = pop; 
	
}

void addToOpList(Operation* opList[100], int *opCount,int* current, Country* c,int opName)
{
	Operation* op = create_operation(c, opName);
	if ((*opCount) == (*current))
	{
		opList[++(*opCount)] = op;
		(*current)++;
	}
	else
	{
		int i;
		for (i = (*current) + 1; i <= *opCount; i++)
			destroy_operation(opList[i]);
		opList[++(*current)] = op;
		*opCount = *current;
	}
}


void init_values(UI * ui)
{
	Country* c1, *c2, *c3, *c4, *c5, *c6, *c7, *c8, *c9, *c10, *c11, *c12;
	c1 = create_country("Romania", "Europe", 12);
	c2 = create_country("Germany", "Europe", 25);
	c3 = create_country("Canada", "America", 65);
	c4 = create_country("China", "Asia", 80);
	c5 = create_country("Japan", "Asia", 9);
	c6 = create_country("Madagascar", "Africa", 4);
	c7 = create_country("Malaesia", "Asia", 29);
	c8 = create_country("Usa", "America", 68);
	c9 = create_country("Denmark", "Europe", 13);
	c10 = create_country("Uae", "Asia", 29);
	c11 = create_country("Nepal", "Africa", 24);
	c12 = create_country("Kazahstan", "Asia", 31);
	add_countryCtrl(ui->ctrl, c1);
	add_countryCtrl(ui->ctrl, c2);
	add_countryCtrl(ui->ctrl, c3);
	add_countryCtrl(ui->ctrl, c4);
	add_countryCtrl(ui->ctrl, c5);
	add_countryCtrl(ui->ctrl, c6);
	add_countryCtrl(ui->ctrl, c7);
	add_countryCtrl(ui->ctrl, c8);
	add_countryCtrl(ui->ctrl, c9);
	add_countryCtrl(ui->ctrl, c10);
	add_countryCtrl(ui->ctrl, c11);
	add_countryCtrl(ui->ctrl, c12);
}


