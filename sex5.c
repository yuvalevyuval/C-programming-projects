#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable : 4996)

//C programming for electrical engineers at Tel Aviv University
//EX 5 Bar Haim && Yuval Levy 
//All rights preserved to ahcheli kipod LTD.
//29.05.2019

#define ARR_SIZE 21                                                      // maximum length of names

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crtdbg.h>

//defining player structure
typedef struct player {
	char name[ARR_SIZE];                   // player's name, up to 20 chars
	int age;                               // player's age, 0 - 120
	int defense;                           // defense power, 1 - 100
	int attack;                            // attack power, 1 - 100
	struct player *next;                   // next player in the list
}player;

//defining team structure
typedef struct team {
	char name[ARR_SIZE];                   // team's name
	player *teamPlayers;                   // pointer to the team players list
	int points;                            // the team points in the league
	int wins;                              // number of wins
	int draws;                             // number of draws
	int losses;                            // number of losses
	struct team *next;                     // Next team in the list
}team;



//part 1 - initial teams according to text given
int is_there_copy(team* head, char check[ARR_SIZE])
{
	team* cur = head;
	while (cur != NULL)
	{
		if (strcmp(cur->name, check) == 0)
		{
			printf("There is a team already with the same name\n");
			return 0;
		}
		cur = cur->next;
	}
	return 1;
}

team* initial_team(char* name, team* B, team* A)
{
	strcpy(B->name, name);
	B->teamPlayers = NULL;
	B->points = 0;
	B->wins = 0;
	B->losses = 0;
	B->draws = 0;
	B->next = A;
	return B;
}

team* new_team(char* name, team* A)
{
	team *B = (team*)malloc(sizeof(team));
	if (is_there_copy(A, name) == 0)
	{
		free(B);
		return A;
	}
	B = initial_team(name, B, A);
	return B;
}

void get_off_n(char name[ARR_SIZE])
{
	int i = 0;
	for (i = 0; name[i] != '\n' && name[i] != '\0'; i++);
	name[i] = '\0';
	return;
}

team* EnlistTeams(FILE *teams) {
	team *A = (team*)malloc(sizeof(team));
	team *B = NULL;

	if (A == NULL)
	{
		printf("FATAL ERROR!!!, shuting the fucking program down!\n");
		return A;
	}
	char name[ARR_SIZE];
	if (fgets(name, ARR_SIZE, teams) == NULL)
	{
		printf("invalid file - no teams listed!!!\n");
		return NULL;
	}
	get_off_n(name);
	initial_team(name, A, NULL);
	while (fgets(name, ARR_SIZE, teams) != NULL)
	{
		get_off_n(name);
		if (A != NULL)
		{
			B = new_team(name, A);
			A = B;
		}
	}
	printf("all teams loaded sucsessfully\n");
	return A;
}



//part 2 - initial players according to text given, and send them to corresponding teams
team* find_group(char team_name[ARR_SIZE], team* head) //returns us the group of that player
{
	team *current_team = head;
	int check = -1;
	while (current_team->next != NULL)
	{
		if (strcmp(current_team->name, team_name) == 0)
		{
			check = 1;
			break;
		}
		current_team = current_team->next;
	}
	if (strcmp(current_team->name, team_name) == 0)
		check = 1;
	if (check == -1)
	{
		return NULL;
	}
	return current_team;
}

int is_player_exist(player* head, char check[ARR_SIZE])
{
	player* cur = head;
	while (cur != NULL)
	{
		if (strcmp(cur->name, check) == 0)
		{
			///printf("There is already a player with the same name\n");
			return 0;
		}
		cur = cur->next;
	}
	return 1;
}

void push_player(team* current_team, char player_name[ARR_SIZE], int age, int defense, int attack)
{
	//in case we have a non-empty player list
	player *current = current_team->teamPlayers;
	if (!is_player_exist(current, player_name))
		return;
	player *A = (player*)malloc(sizeof(player));
	strcpy(A->name, player_name);
	A->age = age;
	A->defense = defense;
	A->attack = attack;
	A->next = current;
	current_team->teamPlayers = A;
	///printf("team player: %s. player name: %s. attack: %d. def: %d\n", current_team->name, A->name, A->attack, A->defense);
}

void get_off_space(char player_name[ARR_SIZE])
{
	int i = ARR_SIZE - 1;
	for (i = ARR_SIZE; i >= 0; i--)
	{
		//printf("%c", player_name[i]);
		if ((player_name[i] >= 'A' && player_name[i] <= 'Z') || (player_name[i] >= 'a' && player_name[i] <= 'z'))
			break;
	}
	i = i + 1;
	player_name[i] = '\0';
	return;
}

void initial_first_player(team* current_team, char player_name[ARR_SIZE], int age, int defense, int attack)
{
	if (current_team->teamPlayers != NULL)
	{
		push_player(current_team, player_name, age, defense, attack);
		return;
	}
	player *A = (player*)malloc(sizeof(player));
	strcpy(A->name, player_name);
	A->age = age;
	A->defense = defense;
	A->attack = attack;
	A->next = NULL;
	current_team->teamPlayers = A;
	///printf("team player: %s. player name: %s. attack: %d. def: %d\n", current_team->name, A->name, A->attack, A->defense);
}

void Enlistplayer(FILE *players, team* head)
{
	int myage = 0, myattack = 0, mydef = 0, k, count;
	team *current_team;
	char player_name[ARR_SIZE], team_name[ARR_SIZE];
	char line[ARR_SIZE * 6];
	//player *A = (player*)malloc(sizeof(player));
	//player *B = NULL;
	if (fgets(line, sizeof(line), players) == NULL)
	{
		printf("invalid file - no teams listed!!!\n");
		return;
	}
	//fgets(line, ARR_SIZE, players);
	while (fgets(line, sizeof(line), players) != NULL)
	{
		myage = 0;
		myattack = 0;
		mydef = 0;
		count = 0;
		for (k = 0; k < 20; k++)       //name
		{
			player_name[count] = line[k];
			count++;
		}
		get_off_space(player_name);
		///printf("%s\n", player_name);
		///printf("%s", player_name);
		for (k = 21; k < 26 || line[k] == ' '; k++)             //age
		{
			///fscanf(players, "%d", &myage);
			if (line[k] >= '0' && line[k] <= '9') {
				myage = myage * 10 + (line[k] - '0');
			}
		}
		if (myage < 0 || myage>120)
			myage = 25;

		for (k = 26; k < 33 || line[k] == ' '; k++)             //attack
		{
			///fscanf(players, "%d", &myattack);
			if (line[k] >= '0' && line[k] <= '9') {
				myattack = myattack * 10 + (line[k] - '0');
			}
		}
		if (myattack < 1 || myattack>100)
			myattack = 50;

		for (k = 33; k < 41 || line[k] == ' '; k++)          //def
		{
			///fscanf(players, "%d", &mydef);
			if (line[k] >= '0' && line[k] <= '9') {
				mydef = mydef * 10 + (line[k] - '0');
			}
		}
		if (mydef < 1 || mydef>100)
			mydef = 50;

		count = 0;
		for (int k = 41; (line[k] != '\n'); k++)      //team name
		{
			///fscanf(players, "%c", &tav);
			team_name[count] = line[k];
			///team_name[count] = tav;
			count++;
		}
		team_name[count] = '\0';
		///team_name[count + 1] = '\0';
		current_team = find_group(team_name, head);
		if (current_team == NULL)
			continue;
		else
			initial_first_player(current_team, player_name, myage, mydef, myattack);
		//fgets(line, ARR_SIZE, players);
	}
	printf("all players loaded sucsessfully\n");
	return;
}



//part 3 - run games according to text given and print outcomes
int Calc_team_strength(team* team_name)
{
	int tot = 0;
	player* current_player = NULL;
	if (team_name == NULL)
		return -1;
	current_player = team_name->teamPlayers;
	while (current_player != NULL)
	{
		tot = tot + current_player->defense + current_player->attack;
		current_player = current_player->next;
	}
	///printf("the total %s team strength is %d\n", team_name->name, tot);
	return tot;
}

int is_game_possible(char A_char[ARR_SIZE], char B_char[ARR_SIZE], team* A_team, team* B_team)
{
	if ((A_team == NULL) || (B_team == NULL) || (A_team->name == B_team->name) || (A_team->teamPlayers == NULL) || (B_team->teamPlayers == NULL))
		return 0;

	else
		return 1;
}

void Run_A_Game(int totA, int totB, team* A_team, team* B_team, FILE* results)
{
	//we categorize to 3 options - A won, B won, or a draw
	if (totA == totB)
	{
		fprintf(results, "Team %s and Team %s finished the match in a draw\n", A_team->name, B_team->name);
		A_team->draws++;
		B_team->draws++;
		A_team->points++;
		B_team->points++;
		return;
	}
	else if (totA > totB)
	{
		fprintf(results, "Team %s WON the game\n", A_team->name);
		A_team->wins++;
		B_team->losses++;
		A_team->points += 3;
		return;
	}
	else
	{
		fprintf(results, "Team %s WON the game\n", B_team->name);
		B_team->wins++;
		A_team->losses++;
		B_team->points += 3;
		return;
	}
}

void initial_string(char string[ARR_SIZE])
{
	int i = 0;
	for (i = 0; i < ARR_SIZE; i++)
		string[i] = 0;
	return;
}

void GameOn(FILE *games, team* head_team, FILE* results)
{
	team *current_team = head_team, *A_team, *B_team;
	char A_char[ARR_SIZE], B_char[ARR_SIZE];
	char line[ARR_SIZE * 3];
	int count = 0, k, totA, totB;
	while (fgets(line, sizeof(line), games) != NULL)
	{
		for (k = 0; line[k] != ':'; k++) {
			A_char[count] = line[k];
			count++;
		}
		A_char[count] = '\0';
		///printf("%s\n", A_char);
		count = 0;
		for (k = k + 1; line[k] != '\n'; k++) {
			B_char[count] = line[k];
			count++;
		}
		B_char[count] = '\0';
		A_team = find_group(A_char, current_team);
		current_team = head_team;
		B_team = find_group(B_char, current_team);
		totA = Calc_team_strength(A_team);
		totB = Calc_team_strength(B_team);

		if (!(is_game_possible(A_char, B_char, A_team, B_team)))
			fprintf(results, "The game ~%s:%s~ can't play\n", A_char, B_char);


		else if (is_game_possible(A_char, B_char, A_team, B_team))
			Run_A_Game(totA, totB, A_team, B_team, results);

		initial_string(A_char);
		initial_string(A_char);
		count = 0;
	}
	printf("all games loaded sucsessfully\n");
	return;
}



//part 4 - print league to final text 
team* sortList(team* list)
{
	if (list == NULL || list->next == NULL)   // the list is sorted.
		return list;
	//replace largest node with the first : 
	//1- find largest node : 
	team* curr = list;
	team* largest = list;
	team* prev = list;
	team* largestPrev = list;
	while (curr != NULL) {
		if (curr->points > largest->points)
		{
			largestPrev = prev;
			largest = curr;
		}
		else if (curr->points == largest->points)
		{
			if (strcmp(curr->name, largest->name) < 0)
			{
				largestPrev = prev;
				largest = curr;
			}
		}
		prev = curr;
		curr = curr->next;
	}
	//largest node is in largest. 

	//2- switching firt node and largest node : 
	team* tmp;
	if (largest != list)
	{
		largestPrev->next = list;
		tmp = list->next;
		list->next = largest->next;
		largest->next = tmp;
	}
	// now largest is the first node of the list.
	// calling the function again with the sub list :
	//            list minus its first node :
	largest->next = sortList(largest->next);
	return largest;
}
void free_players(player *head) {
	player* temp;
	while (head != NULL)
	{
		printf(" %s ", head->name);
		temp = head;
		head = head->next;
		free(temp);
	}
}

void free_all(team *head) {
	team *temp = NULL;
	while (head != NULL)
	{
		printf("the team is: %s ", temp->name);
		temp = head;
		head = head->next;
		free_players(temp->teamPlayers);
		free(temp);
		printf("\n");
	}
}
void print_league(team *head, FILE *final_table)
{
	int count = 1;
	team* temp = head;
	player *headPlayer, *templayer;
	head = sortList(head);
	fprintf(final_table, "Rank\tTeam name            	Matches played\tWins\tDraws\tLosses\tPoints\n");
	while (head != NULL)
	{
		fprintf(final_table, "%-4d\t%-*s\t%-8d\t%-4d\t%-4d\t%-4d\t%-4d\n", count, ARR_SIZE, head->name, head->draws + head->wins + head->losses, head->wins, head->draws, head->losses, head->points);
		count++;
		temp = head;
		head = head->next;
		if (temp->teamPlayers == NULL)
		{
			printf("the team is: %s \n", temp->name);
			free(temp);
			continue;
		}
		headPlayer = temp->teamPlayers;
		while (headPlayer->next != NULL)
		{
			templayer = headPlayer;
			headPlayer = headPlayer->next;
			printf("the player is: %s ", templayer->name);
			free(templayer);
		}
		printf("the player is: %s ", headPlayer->name);
		free(headPlayer);
		printf("the team is: %s ", temp->name);
		free(temp);
		printf("\n");
	}
	//printf("the team is: %s ", head->name);

	//free(head); head->next != NULL &&
	//printf("all files written sucsessfully\n");

	return;
}


//the main function
int main(int argc, char *argv[])
{
	//  exercise5.exe teams.txt players.txt games.txt final_table.txt
	int i = 0;
	team *head, *temp, *copy;
	FILE *teams = NULL, *players = NULL, *games = NULL, *final_table = NULL, *results = NULL;
	teams = fopen(argv[1], "r");
	players = fopen(argv[2], "r");
	games = fopen(argv[3], "r");
	final_table = fopen(argv[4], "w");
	/*if (!feof(games))
	{
		fclose(teams);
		fclose(players);
		fclose(games);
		fclose(final_table);
		return 0;
	}*/
	results = fopen("results.txt", "w+");
	if (teams == NULL || players == NULL || games == NULL || final_table == NULL || results == NULL)
	{
		if (teams != NULL)  fclose(teams);
		if (players != NULL)  fclose(players);
		if (games != NULL)  fclose(games);
		if (final_table != NULL)  fclose(final_table);
		if (results != NULL)  fclose(results);
		printf("err2");
		return 1;
	}
	if (teams == NULL) {//|| player == NULL || games == NULL || final_table == NULL) {
		///printf("File did not open ya kipod!\n");
		return 1;
	}
	head = EnlistTeams(teams);
	Enlistplayer(players, head);
	GameOn(games, head, results);
	//copy = head;
	print_league(head, final_table);
	fclose(teams);
	fclose(players);
	fclose(games);
	fclose(results);
	fclose(final_table);
	//free_all(head);

	return 0;
}
