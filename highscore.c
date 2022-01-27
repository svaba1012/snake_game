#include "highscore.h"

void newHighScore(long long trenutniRezultat, FILE* fajlSaRezultatima){
    fajlSaRezultatima = fopen(".\\highscores1.txt", "r+");
    char* allHighScores[NUMOFHIGHSCORES];
    char strScore[SCORELENGHT];
    long long llscore[NUMOFHIGHSCORES];
    char novoIme[NAMELENGHT];
    int index;
    for(int j = 0; j < NUMOFHIGHSCORES; j++){
        allHighScores[j] = malloc(NAMELENGHT);
        fgets(allHighScores[j], NAMELENGHT, fajlSaRezultatima);
        fgets(strScore, SCORELENGHT, fajlSaRezultatima);
        llscore[j] = strtoll(strScore, NULL, 10);
    }
    if(trenutniRezultat == -1)
        ;
    else if(trenutniRezultat < llscore[0]){
        fclose(fajlSaRezultatima);
        return;
    }else{
        puts("Oborili ste rekord, da li zelite da ga upisete?(1 - DA)(2 - NE)");
        char c[2];
        do{
            fgets(c, 2, stdin);
        }while((strcmp(c, "1") != 0) && (strcmp(c, "2") != 0));
        if((strcmp(c, "1")) != 0){
            fclose(fajlSaRezultatima);
            return;
        }
        puts("Upisite ime:");
        do{
            fgets(novoIme, NAMELENGHT, stdin);
            //printf("*%s*", novoIme);
        }while(novoIme[1] == '\0');
        index = insertInOrder(llscore, trenutniRezultat, NUMOFHIGHSCORES);
        system("cls");
        printf("\nSvaka cast %d. ste na tabeli najboljih rezultata!\n", NUMOFHIGHSCORES - index);
        insertAtIndex(allHighScores, index, novoIme);
        rewind(fajlSaRezultatima);
        for(int i = 0; i < NUMOFHIGHSCORES; i++){
            fputs(allHighScores[i], fajlSaRezultatima);
            sprintf(strScore, "%lld\n", llscore[i]);
            fputs(strScore, fajlSaRezultatima);
        }
    }
    char* nameAndScore;
    char redniBroj[4];
    puts("");
    puts("\t\tHIGH SCORES");
    for(int i = NUMOFHIGHSCORES - 1; i >= 0; i--){
        nameAndScore = malloc(NAMELENGHT * 2 + 10);
        sprintf(redniBroj, "%d) ", NUMOFHIGHSCORES - i);
        strcpy(nameAndScore, redniBroj);
        *(allHighScores[i] + strlen(allHighScores[i]) - 1) = '\0';
        strcat(nameAndScore, allHighScores[i]);
        strcat(nameAndScore, " - ");
        sprintf(strScore, "%lld", llscore[i]);
        strcat(nameAndScore, strScore);
        puts(nameAndScore);
        free(nameAndScore);
    }
    puts("\n");
    fclose(fajlSaRezultatima);
    int end = 0;
    printf("Enter 1 to return to menu\n");
    do{
        scanf("%d", &end);
    }while(end != 1);
}

long long* binaryInsert(long long* niz, long long newValue, int size){
    if(size > 1){
        if(newValue >= niz[size / 2])
            binaryInsert(niz + size / 2 + 1, newValue, size / 2 - 1);
        else
            binaryInsert(niz, newValue, size / 2);
    }else
        if(newValue >= niz[0])
            return niz + 1;
        else
            return niz;
}

int insertInOrder(long long* niz, long long newValue, int size){
    long long *p;
    int index;
    p = binaryInsert(niz, newValue, size);
    index = p - niz;
    if(index == 0)
        return;
    index--;
    memcpy(niz, niz + 1, sizeof(long long) * index);
    niz[index] = newValue;
    return index;
}

void insertAtIndex(char** niz, int index, char* newValue){
    memcpy(niz, niz + 1, sizeof(char*) * index);
    niz[index] = newValue;
}

void display_highscores(){
    rezultati = fopen(".\\highscores1.txt", "r+");
    char usernames[10][20];
    char score[10][10];
    printf("Usernames\tScores\n");
    for(int i = 0; i < 10; i++){
        fgets(usernames[i], 20, rezultati);
        usernames[i][strlen(usernames[i]) - 1] = '\0';
        fgets(score[i], 10, rezultati);
        //printf("%d) %s   \t%s", i, username, score);
    }
    for(int i = 9; i >= 0; i--){
        printf("%d) %s   \t%s", 10 - i, usernames[i], score[i]);
    }

    int end = 0;
    printf("Enter 1 to return to menu\n");
    do{
        scanf("%d", &end);
    }while(end != 1);
    fclose(rezultati);
    main_menu();
}

void main_menu(){
    int menu_option;
    system("cls");
    printf("Enter 1 to start game.\nEnter 2 to display scores. \nEnter other to exit.\n");
    scanf("%d", &menu_option);
    switch(menu_option){
        case 1: start_game();
        case 2: display_highscores();
                break;
        default:    exit(EXIT_SUCCESS);
    }
}


