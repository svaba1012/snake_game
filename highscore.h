#ifndef HIGH_SCORE
#define HIGH_SCORE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NAMELENGHT 20
#define SCORELENGHT 20
#define NUMOFHIGHSCORES 10

FILE* rezultati;

void main_menu();
void newHighScore(long long trenutniRezultat, FILE* fajlSaRezultatima);
long long* binaryInsert(long long* niz, long long newValue, int size);
int insertInOrder(long long* niz, long long newValue, int size);
void insertAtIndex(char** niz, int index, char* newValue);
void display_highscores();

#endif // HIGH_SCORE
