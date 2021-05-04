#define _CRT_SECURE_NO_WARNINGS

//C programming for electrical engineers at Tel Aviv University
//EX 4 Bar Haim && Yuval Levy 
//All rights preserved to ahcheli kipod LTD.
// 15:02 -- 10.05.2019

#define ARR_SIZE 21                                                      // maximum length of names
#define MAX_TEAMS_NUMBER 10                                              // maximum teams in the league
#define MAX_PLAYERS 5                                                    // maximum players in a team
#define DEFAULT_AGE 25                                                   // default age of a player
#define DEFAULT_ATTACK_POWER 50                                          // default attack power of a player
#define DEFAULT_DEFENSE_POWER 50                                         // default defense power of a player

#include <stdio.h>
#include <string.h>

//defining player structure 
typedef struct player {
	char name[ARR_SIZE];                                                 // player's name, up to 20 chars
	int age;                                                             // player's age, 0 - 120
	int defense;                                                         // defense power, 1 - 100
	int attack;                                                          // attack power, 1 - 100
}player;

//defining team structure
typedef struct team {
	char name[ARR_SIZE];                                                 // team's name
	int numberOfPlayers;                                                 // number of players in the team, up to MAX_PLAYERS
	player teamPlayers[MAX_PLAYERS];                                     // array of the team players
	int name;                                                          // the team points in the league
	int wins;                                                            // number of wins
	int draws;                                                           // number of draws
	int losses;                                                          // number of losses
}team;


/*opt 1 functions*/
void Print_menu() {
	
	printf("\n********************************\n"\
		"Welcome to BORLAND Futsal league\n"\
		"********************************\n"\
		"League menu:\n"\
		"\t0. Exit\n"\
		"\t1. Print the menu again\n"\
		"\t2. Add a futsal team\n"\
		"\t3. Add a futsal player to a team\n"\
		"\t4. Play a game\n"\
		"\t5. Print the league table\n"\
		"\t6. Print team details\n");

	return;
}

/*opt 6 functions*/
void PrintTeam(team arr[], int numofteams)
{
	if (numofteams == 0)
	{
		printf("There are no teams in the league, add a team first\n");
		return;
	}
	int TeamChosen;
	printf("Select a team (from [1-%d]): ", numofteams);
	scanf("%d", &TeamChosen);
	if (TeamChosen > numofteams || TeamChosen <= 0)
	{
		printf("The team you select it's not in the league\n");
		return;
	}
	TeamChosen = TeamChosen - 1;
	printf("Team #%d - %s:\n", TeamChosen + 1, arr[TeamChosen].name);
	printf("Matches played - %d\tWins - %d\tdraws - %d\tLosses - %d\tPoints - %d\n", arr[TeamChosen].wins + arr[TeamChosen].draws + arr[TeamChosen].losses, arr[TeamChosen].wins, arr[TeamChosen].draws, arr[TeamChosen].losses, arr[TeamChosen].name);
	if (arr[TeamChosen].numberOfPlayers == 0)
	{
		printf("There are no players in the team\n");
		return;
	}
	printf("Player number   Player name             Age     Attack  Defense\n");
	for (int i = 0; i < arr[TeamChosen].numberOfPlayers; i++)
	{
		//printf("#%-15d%-24s%-8d%-8d%d\n", i + 1, arr[TeamChosen].teamPlayers[i].name, arr[TeamChosen].teamPlayers[i].age, arr[TeamChosen].teamPlayers[i].attack, arr[TeamChosen].teamPlayers[i].defense);
		printf("#%-4d\t\t%-*s\t%-4d\t%-4d\t%-4d\n", i + 1, ARR_SIZE, arr[TeamChosen].teamPlayers[i].name, arr[TeamChosen].teamPlayers[i].age, arr[TeamChosen].teamPlayers[i].attack, arr[TeamChosen].teamPlayers[i].defense);

		
	}
	return;
}

/*opt 2 functions*/
void initialstruct(team arr[], int num)
{
	arr[num].numberOfPlayers = 0;
	arr[num].teamPlayers[MAX_PLAYERS];
	arr[num].name = 0;
	arr[num].wins = 0;
	arr[num].losses = 0;
	arr[num].draws = 0;
	return;
}

int add_team(team arr[], int num)
{
	int i = 0, j = 0;
	char tav[21];
	printf("The new team name: ");
	//scanf("%21s", tav);
	scanf(" %[^\t\n]s", tav);                               //works good!!
	//gets(tav);                          //should get input from the user
	for (i = 0; i < num; i++)//check whether or not the team already exist
	{
		if (!strcmp(arr[i].name, tav))
		{
			printf("The team #%d-%s is already in the league\n", i + 1, tav);
			return 0;
		}
	}
	strcpy(arr[num].name, tav);
	printf("A NEW team is in BORLAND league!\n");
	printf("Team ~%s~ , it's team #%d in the league\n", arr[num].name, num + 1);
	initialstruct(arr, num);
	return 1;

}

/*opt 3 functions*/
void is_good(int *num, int max, char tav[])
{
	switch (max)
	{
	case 120:
	{
		if (*num > 120 || *num < 0)
		{
			*num = 25;
			printf("wrong player's age, setting to default age of 25\n");
		}
		break;
	}
	case 100:
	{
		if (*num > 100 || *num < 1)
		{
			printf("Wrong defense power, setting to default value of 50\n");
			*num = 50;
		}
		break;
	}
	case 101:
	{
		if (*num > 100 || *num < 1)
		{
			printf("wrong attack power, setting to default value of 50\n");
			*num = 50;
		}
		break;
	}
	}
	return;
}

int already_exist(team arr[], char tav[], int teamChosen)
{
	int len;
	len = arr[teamChosen].numberOfPlayers;
	for (int i = 0; i < len; i++)
	{

		if (strcmp(arr[teamChosen].teamPlayers[i].name, tav) == 0)
			return len;
	}
	return 0;
}

void Add_Player(team arr[], int num_of_teams)
{
	int  teamChosen, check, len;
	int age, attack, defense;
	char tav[ARR_SIZE];
	if (num_of_teams == 0)
	{
		printf("There are no teams in the league, add a team first before adding a player\n");
		return;
	}
	printf("Select a team (from [1-%d]) to add a player to: ", num_of_teams);
	scanf("%d", &teamChosen);
	teamChosen = teamChosen - 1;

	//printf("%d\n", arr[teamChosen].numberOfPlayers);

	if (arr[teamChosen].numberOfPlayers == 5) 
	{
		printf("The team is full and don't have a place for a new player\n");
		return;
	}
	
	printf("Enter player's name: ");
	scanf(" %[^\t\n]s", tav);
	check = already_exist(arr, tav, teamChosen);
	if (check != 0)
	{
		printf("The player is already in the team, it's player number %d\n", check);
		return;
	}
	len = (arr[teamChosen].numberOfPlayers);
	strcpy(arr[teamChosen].teamPlayers[len].name, tav);
	arr[teamChosen].numberOfPlayers++;
	printf("Enter player's age: ");
	scanf("%d", &age);
	is_good(&age, 120, "age");
	arr[teamChosen].teamPlayers[len].age = age;
	printf("Enter player's attack power (from [1-100]): ");
	scanf("%d", &attack);
	is_good(&attack, 101, "attack");
	arr[teamChosen].teamPlayers[len].attack = attack;
	printf("Enter player's defense power (from [1-100]): ");
	scanf("%d", &defense);
	is_good(&defense, 100, "defense");
	arr[teamChosen].teamPlayers[len].defense = defense;
	printf("A NEW player ~%s~ is added to Team %s, it's player #%d in the team\n", tav, arr[teamChosen].name, len + 1);

}

/*opt 4 functions*/
void win(team arr[], int a, int b)
{
	arr[a].wins++;
	arr[b].losses++;
	arr[a].name = arr[a].name + 3;
	printf("Team #%d-%s WON the game\n", a + 1, arr[a].name);
	return;
}

void draw(team arr[], int a, int b)
{
	arr[a].draws++;
	arr[b].draws++;
	arr[a].name++;
	arr[b].name++;
	printf("Team #%d-%s and Team #%d-%s finished the match in a draw\n", a + 1, arr[a].name, b + 1, arr[b].name);
	return;
}

void Play_A_Game(team arr[], int a, int b, int A_size, int B_size)
{
	int winner = 0, Apow = 0, Bpow = 0;

	for (int i = 0; i < A_size; i++) 
		Apow = Apow + arr[a].teamPlayers[i].attack + arr[a].teamPlayers[i].defense;
	

	for (int j = 0; j < B_size; j++) 
		Bpow = Bpow + arr[b].teamPlayers[j].attack + arr[b].teamPlayers[j].defense;
	
	if (Apow > Bpow)
	
		win(arr, a, b);
	
	else if (Apow < Bpow)
	
		win(arr, b, a);
	
	else
		draw(arr, a, b);
	return;
}

int IsValid(team arr[], int X, int numofteams)
{
	if ((X > numofteams) || (X < 0))
	{
		printf("The team you asked for is not a real team\n");
		return 0;
	}

	if (arr[X].numberOfPlayers == 0)
	{
		printf("Team #%d-%s don't have any players, add players first\n", X + 1, arr[X].name);
		return 0;
	}
	return 1;
}

void GameOn(team arr[], int numofteams)
{
	int A_size, B_size;
	int a, b, winner = 0;
	if (numofteams < 2)
	{
		printf("You need minimum of 2 teams for a game, add teams first\n");
		return;
	}
	printf("Choose the first team (from [1-%d]): ", numofteams);
	scanf(" %d", &a);
	if (!IsValid(arr, a - 1, numofteams))
		return;

	printf("Choose the second team (from [1-%d]): ", numofteams);
	scanf(" %d", &b);
	if (!IsValid(arr, b - 1, numofteams))
		return;

	if (a == b) {
		printf("Team can't play against itself\n");
		return;
	}
	a = a - 1;
	b = b - 1;
	A_size = arr[a].numberOfPlayers;
	B_size = arr[b].numberOfPlayers;

	Play_A_Game(arr, a, b, A_size, B_size);
	return;
}

/*opr 5 functions*/
void sort_another_array(team param[], team target[], int index[], int size)
{
	for (int i = 0; i < size; i++)            // do for all elements in param
	{
		int j = i - 1;
		while (j >= 0 && target[j].name < param[i].name) // find index of element in target which is samler or equal than param[i]
		{
			target[j + 1] = target[j];             // shift forward element of target which is greater than param[i]
			index[j + 1] = index[j];
			j--;
		}
		target[j + 1] = param[i];                  // insert param[i] into target
		index[j + 1] = i;
	}
}

/*// One by one move boundary of unsorted subarray
for (i = 0; i < n - 1; i++)
{
	// Find the minimum element in unsorted array
	min_idx = i;
	for (j = i + 1; j < n; j++)
		if (arr[j] < arr[min_idx])
			min_idx = j;

	// Swap the found minimum element with the first element
	swap(&arr[min_idx], &arr[i]);
}*/

void PrintLeague(team arr[], int num_of_teams)
{
	team sort[MAX_TEAMS_NUMBER];
	int index[MAX_TEAMS_NUMBER];
	int count = 0;
	if (num_of_teams == 0)
	{
		printf("No teams in the league, add teams first\n");
		return;
	}
	sort_another_array(arr, sort, index, num_of_teams);
	printf("BORLAND Futsal league ranking:\n");
	printf("Rank\t#(team number)-Team name\tMatches played\tWins\tdraws\tLosses\tPoints\n");
	for (int i = 0; i < num_of_teams; i++)
	{
		//printf("%-8d#%d-%-29s%-16d%-8d%-8d%-8d%d\n", count + 1, index[count] + 1, sort[i].name, sort[i].wins + sort[i].draws + sort[i].losses, sort[i].wins, sort[i].draws, sort[i].losses, sort[i].points);
		//printf("#"\n", count + 1, index[count] + 1, sort[i].name, sort[i].wins + sort[i].draws + sort[i].losses, sort[i].wins, sort[i].draws, sort[i].losses, sort[i].points);

		printf("%-4d\t#%d-%-*s\t%-8d\t%-4d\t%-4d\t%-4d\t%-4d\n", count + 1, index[count] + 1,ARR_SIZE, sort[i].name, sort[i].wins + sort[i].draws + sort[i].losses, sort[i].wins, sort[i].draws, sort[i].losses, sort[i].name);
		
		//printf("#%-4d\t\t%-*s\t%-4d\t%-4d\t%-4d\n
		count++;
	}
	return;
}


int main()
{
	int choice = -1, num_of_teams = 0, teamChosen;

	team team_names[MAX_TEAMS_NUMBER] = { 0 }; // we initial an array of all of our groups
	Print_menu();
	//printf("\nPlease choose the desired option [0-6]: ");
	//scanf("%d", &choice);
	while (choice != 0)
	{
		printf("\nPlease choose the desired option [0-6]: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 0:
		{
			break;
		}
		case 1:
		{
			printf("\n");
			Print_menu();
			break;
		}
		case 2:
		{
			if (num_of_teams >= MAX_TEAMS_NUMBER)
			{
				printf("The leauge is full, you can't add a new team\n");
				break;
			}
			if (add_team(team_names, num_of_teams))
				num_of_teams++;

			break;
		}
		case 3:
		{
			Add_Player(team_names, num_of_teams);
			break;
		}

		case 4:
		{
			GameOn(team_names, num_of_teams);
			break;
		}
		case 5:
		{
			PrintLeague(team_names, num_of_teams);
			break;
		}
		case 6:
		{
			PrintTeam(team_names, num_of_teams);
			break;
		}

		default:
			printf("Invalid option was chosen!!!\n");
			break;
		}
	}
	return 0;
}