#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "wait.h"
#include "queue.h"
#include "highscore.h"

#define X 20
#define SIZE 5
#define MAXSIZE 100
#define POCETNABRZINA 25




void crtajTablu(int *a, int lenght);
int vocka(int *a);
void rasteZmija(int *nizX, int *nizY, int a, int lenght);
void start_game();


int main(){
    main_menu();
    start_game();
    fclose(rezultati);
}

void crtajTablu(int a[], int lenght){
    for(int *p = a; p < a + (lenght) * (lenght); p++){
        putchar(*p);
        if(((p - a + 1) % lenght) == 0)
        putchar('#');
          if(((p - a) % X) == X - 1)
            putchar('\n');
    }
    for(int i = 0; i <= lenght; i++)
        putchar('#');
    putchar('\n');

}

int vocka(int *a){
    int b = rand() % (X * X);
    *(a + b) = 'J';
    return b;
}

void rasteZmija(int *nizX, int *nizY, int a, int lenght){
    switch(a){
        case 'w':   enqueue(nizX, &lenght, nizX[lenght - 1]);
                    lenght--;
                    enqueue(nizY, &lenght, nizY[lenght - 1] - 1);

        case 'd':   enqueue(nizX, &lenght, nizX[lenght - 1] + 1);
                    lenght--;
                    enqueue(nizY, &lenght, nizY[lenght - 1]);

        case 's':   enqueue(nizX, &lenght, nizX[lenght - 1]);
                    lenght--;
                    enqueue(nizY, &lenght, nizY[lenght - 1] + 1);

        case 'a':   enqueue(nizX, &lenght, nizX[lenght - 1] - 1);
                    lenght--;
                    enqueue(nizY, &lenght, nizY[lenght - 1]);

    }
}

void start_game(){
    bool nemaVocke = true;
    srand((unsigned) time(NULL));
    int pozVocke;
    int duzina = SIZE;
    int score = 0;
    int tabla[X][X], pocetak = 10;
    int zmijaX[MAXSIZE];
    int zmijaY[MAXSIZE] = {0};
    int smer = 'd';
    clock_t t;
    double v = POCETNABRZINA;
    for(int *p = tabla[0]; p < tabla[0] + (X) * (X); p++){
            *p = ' ';
    }
    for(int *p = zmijaX; p < zmijaX + SIZE; p++){
        *p = pocetak++;
    }
    while(1){
        for(int i = 0; i < duzina; i++){
            tabla[zmijaY[i]][zmijaX[i]] = 'O';
        }
        if(nemaVocke){
            pozVocke = vocka(tabla[0]);
            nemaVocke = false;
        }
        if(pozVocke == zmijaY[duzina - 1] * X + zmijaX[duzina - 1]){
            rasteZmija(zmijaX, zmijaY, smer, duzina);
            duzina++;
            nemaVocke = true;
            score++;
        }
        crtajTablu(tabla[0], X);
        for(t = clock(); clock() - t < v;){
            if(kbhit()){//kbhit() funkcija iz conio.h koja proverava da li je pritisnut neki od tastera na tastaturi
                smer = getch();
                break;
            }
        }
        for(t = clock(); clock() - t < v;)
            ;
        system("cls");//funkcija iz stdlib.h koja cisti konzolu od prethodnog unosa
        tabla[zmijaY[0]][zmijaX[0]] = ' ';
        switch(smer){
            case 'd':   if((zmijaX[duzina - 1] == X - 1) || (tabla[zmijaY[duzina - 1]][zmijaX[duzina - 1] + 1] == 'O')){
                            system("cls");
                            printf("Kraj\nRezultat: %d\n", score);
                            newHighScore(score, rezultati);
                            main_menu();
                            return;
                        }
                        izbi(zmijaX, &duzina, zmijaX[duzina - 1] + 1);
                        izbi(zmijaY, &duzina, zmijaY[duzina - 1]);
                        break;

            case 's':   if((zmijaY[duzina - 1] == X - 1) || (tabla[zmijaY[duzina - 1] + 1][zmijaX[duzina - 1]] == 'O')){
                            system("cls");
                            printf("Kraj\nRezultat: %d\n", score);
                            newHighScore(score, rezultati);
                            main_menu();
                            return;
                        }
                        izbi(zmijaX, &duzina, zmijaX[duzina - 1]);
                        izbi(zmijaY, &duzina, zmijaY[duzina - 1] + 1);
                        break;

            case 'a':   if((zmijaX[duzina - 1] == 0) || (tabla[zmijaY[duzina - 1]][zmijaX[duzina - 1] - 1] == 'O')){
                            system("cls");
                            printf("Kraj\nRezultat: %d\n", score);
                            newHighScore(score, rezultati);
                            main_menu();
                            return;
                        }
                        izbi(zmijaX, &duzina, zmijaX[duzina - 1] - 1);
                        izbi(zmijaY, &duzina, zmijaY[duzina - 1]);
                        break;

            case 'w':   if((zmijaY[duzina - 1] == 0) || (tabla[zmijaY[duzina - 1] - 1][zmijaX[duzina - 1]] == 'O')){
                            system("cls");
                            printf("Kraj\nRezultat: %d\n", score);
                            newHighScore(score, rezultati);
                            main_menu();
                            return;
                        }
                        izbi(zmijaX, &duzina, zmijaX[duzina - 1]);
                        izbi(zmijaY, &duzina, zmijaY[duzina - 1] - 1);
                        break;
        }
    }
}
