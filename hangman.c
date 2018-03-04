#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

//FUNCTIE PENTRU PRELUCRAREA EXPRESIEI

void cuvant_ascuns(char s[50], char aux[50])
{
	int i, fr[26], lenght;
	char x[50];
	char * tok;

	for (i = 0; i <= 25; i++)
		fr[i] = 0;
	aux[0]=0;
	strcpy(x, s);

//Impartim expresia in cuvinte
	tok = strtok(x, " ");
	while (tok != NULL)
	{
		printf("%s\n", tok);
		lenght = strlen(tok); //Aflam lungimea cuvantului
		if (lenght == 1)
			strncpy(&tok[0], "_", 1);
		else
			if (lenght == 2)
			{
				fr[tok[0]-'a'] = 1;
				strncpy(&tok[1], "_", 1);
			}
			else
			{
				fr[tok[0]-'a'] = 1;
				fr[tok[lenght-1]-'a'] = 1;
				for (i = 1; i < lenght-1; i++)
					strncpy(&tok[i], "_", 1);
			}
		printf("%s\n", tok);
		strcat(aux, tok);//Formam la loc expresia
		strcat(aux, " ");
		tok = strtok(NULL, " ");
	}
	lenght = strlen(s); //Aflam lungimea expresiei
//Completam literele care au fost ascunse, dar apar in marginea cuvintelor
	for (i = 0; i < lenght; i++)
		if (fr[s[i]-'a'] == 1 && aux[i] == '_')
			aux[i] = s[i];
}

//FUNCTIE PENTRU DATA

void data()
{
	time_t t;
	time(&t); 	
	mvprintw(1, 16, "%s\n", ctime(&t));
}

//FUNCTIE PENTRU A REVENI IN JOC

int resume_game(int nr_expr, int nr_char, char **sir, int random_nr, int mistake, char copy[50], char wrong_let[6], char abc[26])
{
	int i, j;
	char x;

	clear();
	mvprintw(1, 10, "Data:");
	data();
//Afisam cadrul spanzuratorii
	for (j = 10; j < 38; j++)
		mvprintw(5, j, "<");
	for (j = 6; j < 24; j++)
		mvprintw(j, 15, "|");
	for (j = 6; j < 10; j++)
		mvprintw(j, 32, "|");
	for (j = 10; j < 21; j++)
		mvprintw(24, j, ">");
//Afisam panoul de control
	mvprintw(8, 50, "Pentru a reveni la meniul principal apasa Q");
	mvprintw(9, 50, "Pentru a porni un nou joc apasa N");
	mvprintw(10, 50, "Expresii valide: %d\n", nr_expr);
	mvprintw(11, 50, "Caractere: %d\n", nr_char);
	mvprintw(26, 10, "Litere gresite:");
	mvprintw(5, 50, "Greseli: %d", mistake);
	mvprintw(3, 10, copy);
	mvprintw(27, 10, "%s", wrong_let);
//Completam cu greselile facute deja
	if (mistake >= 1)
	{
		mvprintw(10, 32, "*");
		mvprintw(10, 31, "*");
		mvprintw(10, 33, "*");
		mvprintw(12, 32, "*");
		mvprintw(12, 31, "*");
		mvprintw(12, 33, "*");
		mvprintw(11, 31, "*");
		mvprintw(11, 33, "*");
	}
	if (mistake >= 2)
	{
		mvprintw(13, 32, "*");
		mvprintw(14, 32, "*");
		mvprintw(15, 32, "*");
		mvprintw(16, 32, "*");
		mvprintw(17, 32, "*");	
	}
	if (mistake >= 3)
	{
		mvprintw(15, 33, "*");
		mvprintw(14, 34, "*");
		mvprintw(13, 35, "*");
	}
	if (mistake >= 4)
	{
		mvprintw(15, 31, "*");
		mvprintw(14, 30, "*");
		mvprintw(13, 29, "*");
	}
	if (mistake >= 5)
	{
		mvprintw(18, 33, "*");
		mvprintw(19, 34, "*");
		mvprintw(20, 35, "*");
	}
	refresh();
//Continuam jocul
	while (1)
	{
		x = getchar();
		data();
		if (x == 'Q')
		{
			clear();
			mvprintw(10,10,"New Game");
			mvprintw(11,10,"* Resume Game");
			mvprintw(12,10,"Quit");
			move(11,10);
			break;
		}
		if (x == 'N')
			return 1;
		if (strcmp(sir[random_nr], copy)+32 == 0)
			mvprintw(29, 10, "WIN");
		else	
			if (mistake == 6)
				mvprintw(29, 10, "GAME OVER");
			else
			{
				x = tolower(x);
				if (strchr(sir[random_nr], x) == NULL && strchr(abc, x))
				{
					//Eliminam caracterul tastat din sirul cu alfabetul
					for (j = 0; j < strlen(abc); j++)
						if (x == abc[j])
							strcpy(&abc[j], &abc[j+1]);
					if (mistake >= 0)
					{
						mvprintw(10, 32, "*");
						mvprintw(10, 31, "*");
						mvprintw(10, 33, "*");
						mvprintw(12, 32, "*");
						mvprintw(12, 31, "*");
						mvprintw(12, 33, "*");
						mvprintw(11, 31, "*");
						mvprintw(11, 33, "*");
						wrong_let[mistake] = x;
					}
					if (mistake >= 1)
					{
						mvprintw(13, 32, "*");
						mvprintw(14, 32, "*");
						mvprintw(15, 32, "*");
						mvprintw(16, 32, "*");
						mvprintw(17, 32, "*");						
						wrong_let[mistake] = x;
					}
					if (mistake >= 2)
					{
						mvprintw(15, 33, "*");
						mvprintw(14, 34, "*");
						mvprintw(13, 35, "*");
						wrong_let[mistake] = x;
						
					}
					if (mistake >= 3)
					{
						mvprintw(15, 31, "*");
						mvprintw(14, 30, "*");
						mvprintw(13, 29, "*");
						wrong_let[mistake] = x;
					}
					if (mistake >= 4)
					{
						mvprintw(18, 33, "*");
						mvprintw(19, 34, "*");
						mvprintw(20, 35, "*");
						wrong_let[mistake] = x;
					}
					if (mistake == 5)
					{
						mvprintw(18, 31, "*");
						mvprintw(19, 30, "*");
						mvprintw(20, 29, "*");
						wrong_let[mistake] = x;	
					}
					if (mistake <= 5)						
						mistake ++;
					//Afisam literele gresite introduse
					mvprintw(27, 10, "%s", wrong_let);
					//Afisam numarul de greseli
					mvprintw(5, 50, "Greseli: %d", mistake);
				}
				else
				{
					//Completam in expresia ascunsa caracterul introdus
					for (i = 0; i < strlen(sir[random_nr]); i++)
						if (sir[random_nr][i] == x)
							copy[i] = x;
					mvprintw(3, 10, copy);
				}
				if (strcmp(sir[random_nr], copy)+32 == 0)
					mvprintw(29, 10, "WIN");
				else	
					if (mistake == 6)
						mvprintw(29, 10, "GAME OVER");
				
		}
		refresh();
	}
	return 0;
}

//FUNCTIE PENTRU A INCEPE UN JOC NOU

int game(int nr_expr, int nr_char, char **sir, int random_nr, char copy[50], char wrong_let[6], char abc[26])
{
	int i, j, mistakes = 0;
	char x;
	clear();
	//Memoram alfabetul in sirul abc
	for (i = 0; i <= 25; i++)
		abc[i] ='a'+i;
	abc[26]='\0';
	for (i = 0; i <= 5; i++)
		wrong_let[i] = 0;
	//Eliminam din sirul care contine alfabetul, literele care sunt vizibile
	for (i = 0; i <= strlen(sir[random_nr]); i++)
		if (isalpha(sir[random_nr][i]) != 0)
			for (j = 0; j < strlen(abc); j++)
				if (sir[random_nr][i] == abc[j])
					strcpy(&abc[j], &abc[j+1]);
	strcpy(copy, sir[random_nr]);
	cuvant_ascuns(sir[random_nr], copy);
	mvprintw(1, 10, "Data:");
	data();
	for (j = 10; j < 38; j++)
		mvprintw(5, j, "<");
	for (j = 6; j < 24; j++)
		mvprintw(j, 15, "|");
	for (j = 6; j < 10; j++)
		mvprintw(j, 32, "|");
	for (j = 10; j < 21; j++)
		mvprintw(24, j, ">");
	mvprintw(8, 50, "Pentru a reveni la meniul principal apasa Q");
	mvprintw(9, 50, "Pentru a porni un nou joc apasa N");
	mvprintw(10, 50, "Expresii valide: %d\n", nr_expr);
	mvprintw(11, 50, "Caractere: %d\n", nr_char);
	mvprintw(26, 10, "Litere gresite:");
	mvprintw(3, 10, copy);
	refresh();
	while (1)
	{
		x = getchar();
		data();
		if (x == 'Q')
		{
			clear();
			mvprintw(10,10,"* New Game");
			mvprintw(11,10,"Resume Game");
			mvprintw(12,10,"Quit");
			move(10,10);
			return mistakes;
		}
		if (x == 'N')
			return 7;
		if (strcmp(sir[random_nr], copy)+32 == 0)
			mvprintw(29, 10, "WIN");
		else	
			if (mistakes == 6)
				mvprintw(29, 10, "GAME OVER");
			else
			{
				x = tolower(x);
				if (strchr(sir[random_nr], x) == NULL && strchr(abc, x))
				{
					for (j = 0; j < strlen(abc); j++)
						if (x == abc[j])
							strcpy(&abc[j], &abc[j+1]);
					if (mistakes == 0)
					{
						mvprintw(10, 32, "*");
						mvprintw(10, 31, "*");
						mvprintw(10, 33, "*");
						mvprintw(12, 32, "*");
						mvprintw(12, 31, "*");
						mvprintw(12, 33, "*");
						mvprintw(11, 31, "*");
						mvprintw(11, 33, "*");
						wrong_let[mistakes] = x;
					}
					if (mistakes == 1)
					{
						mvprintw(13, 32, "*");
						mvprintw(14, 32, "*");
						mvprintw(15, 32, "*");
						mvprintw(16, 32, "*");
						mvprintw(17, 32, "*");						
						wrong_let[mistakes] = x;
					}
					if (mistakes == 2)
					{
						mvprintw(15, 33, "*");
						mvprintw(14, 34, "*");
						mvprintw(13, 35, "*");
						wrong_let[mistakes] = x;
						
					}
					if (mistakes == 3)
					{
						mvprintw(15, 31, "*");
						mvprintw(14, 30, "*");
						mvprintw(13, 29, "*");
						wrong_let[mistakes] = x;
					}
					if (mistakes == 4)
					{
						mvprintw(18, 33, "*");
						mvprintw(19, 34, "*");
						mvprintw(20, 35, "*");
						wrong_let[mistakes] = x;
					}
					if (mistakes == 5)
					{
						mvprintw(18, 31, "*");
						mvprintw(19, 30, "*");
						mvprintw(20, 29, "*");
						wrong_let[mistakes] = x;
					}
					if (mistakes <= 5)						
						mistakes ++;
					mvprintw(27, 10, "%s", wrong_let);
					mvprintw(5, 50, "Greseli: %d", mistakes);
				}
				else
				{
					for (i = 0; i < strlen(sir[random_nr]); i++)
						if (sir[random_nr][i] == x)
							copy[i] = x;
					mvprintw(3, 10, copy);
				}
				if (strcmp(sir[random_nr], copy)+32 == 0)
					mvprintw(29, 10, "WIN");
				else	
					if (mistakes == 6)
						mvprintw(29, 10, "GAME OVER");
				
		}
		refresh();
	}
	return 0;
}

//FUNCTIE PENTRU MENIU

void meniu(int nr_expr, int nr_char, char **sir)
{
	int c, exit = 0, i = 10, start = 0, random_nr, val_desen, mistake;
	char copy[50], wrong_let[6], abc[26];
	//Afisam optiunile
	mvprintw(10,10,"* New Game");
	mvprintw(11,10,"Resume Game");
	mvprintw(12,10,"Quit");
	move(10,10);
	while (1)
	{
		c = getch();
		switch(c)
		{
			case KEY_DOWN: //Daca se apasa sageata jos
				clear();
				if (i == 12)
					i = 10;
				else
					i ++;
//Daca ne aflat pe optiunea Resume Game dar aceasta nu este disponibila se trece la urmatoarea optiune
				if (i == 11 && start == 0) 
					i ++;
				if (i == 10)
				{
					mvprintw(10,10,"* New Game");
					mvprintw(11,10,"Resume Game");
					mvprintw(12,10,"Quit");
				}
				if (i == 11)
				{
					mvprintw(10,10,"New Game");
					mvprintw(11,10,"* Resume Game");
					mvprintw(12,10,"Quit");
				}
				if (i == 12)
				{
					mvprintw(10,10,"New Game");
					mvprintw(11,10,"Resume Game");
					mvprintw(12,10,"* Quit");
				}
				break;
				
			case KEY_UP: //Daca se apasa sageata sus	
				clear();
				if (i == 10)
					i = 12;
				else
					i --;
//Daca ne aflat pe optiunea Resume Game dar aceasta nu este disponibila se trece la optiunea anterioara
				if (i == 11 && start == 0)
					i --;
				if (i == 10)
				{
					mvprintw(10,10,"* New Game");
					mvprintw(11,10,"Resume Game");
					mvprintw(12,10,"Quit");
				}
				if (i == 11)
				{
					mvprintw(10,10,"New Game");
					mvprintw(11,10,"* Resume Game");
					mvprintw(12,10,"Quit");
				}
				if (i == 12)
				{
					mvprintw(10,10,"New Game");
					mvprintw(11,10,"Resume Game");
					mvprintw(12,10,"* Quit");
				}
				break;

			case 10: //Daca se apasa ENTER
				if (i == 10)
				{
					start = 1;
					clear();
					while (1)
					{
						//Generam un numar random
						srand(time(NULL));
						random_nr = rand() % nr_expr;
						//Se incepe un joc nou
						val_desen = game(nr_expr, nr_char, sir, random_nr, copy, wrong_let, abc);
						if (val_desen != 7)
							break;
					}
					if (val_desen != 0)
						mistake = val_desen;
				}
				if (i == 11)
				{
					clear();
					//Se revine la jocul anterior
					resume_game(nr_expr, nr_char, sir, random_nr, mistake, copy, wrong_let, abc);
				}
				if (i == 12)
					exit = 1;
		}		
		refresh();
		//Se iese din joc
		if (exit == 1)
			break;
	}
}

int main(int argc, char *argv[])
{
	FILE *f;
	int nr_expr=0, nr_files=1, nr_char=0, i, j;
	char **sir=malloc(100 * sizeof(char *));
	if( argc < 2 )
		printf("[Eroare]: Nu s-au dat argumente de comanda.\n");
	else
	{
		while (nr_files < argc)
		{
			f = fopen (argv[nr_files], "r");   
			if ( f == 0 ) 
			{
				printf("[Eroare]: Fisierul %s nu poate fi deschis.\n", argv[nr_files]);
				break;
			}
			else
			{
				sir[nr_expr] = malloc(50 * sizeof(char));
				while ( fgets(sir[nr_expr], 50, f) != NULL )
				{
					nr_char += strlen(sir[nr_expr]); //Memoram numarul de caractere
					nr_expr ++; //Memoram numarul de expresii
					sir[nr_expr] = malloc(50 * sizeof(char));
				}
				for (i = 0; i < nr_expr;)
				{
					for (j = 0; j < strlen(sir[i]);)
					{
						//Stergem caracterele neprintabile
						if (isprint(sir[i][j]) == 0)
							strcpy(&sir[i][j], &sir[i][j+1]);
						else
						{			
							if (isalpha(sir[i][j]) != 0)
								sir[i][j] = tolower(sir[i][j]);
							j++;
						}
					}
					if (strlen(sir[i]) > 0)
						i++;
					else
					{
						strcpy(sir[i], sir[i+1]);
						nr_expr--;
					}
				} 
				nr_files++;
				fclose(f);
			}
		}
		//Initializam ecranul
		initscr();
		//Stergem ecranul
		clear();
		//Nu se afiseaza caracterele introduse de la tastatura
		noecho();
		//Caracterele tastate sunt citite imediat
		cbreak();
		//Ascundem cursorul
		curs_set(0);
		//Activam sagetile, F1,...
		keypad(stdscr, TRUE);
		//Afisam schimbarile pe ecran
		refresh();
		meniu(nr_expr, nr_char, sir);
		endwin();
	}
	return 1;
}
	
	
