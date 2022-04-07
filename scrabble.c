#include <stdio.h>
#include "util/print_board.h"
#include <stdlib.h>
#include <string.h>
#include "util/scrabble.h"

#define SIZE 15
#define read_blanc getchar()
#define getInt(character) ((int)character - (int)'0') 
#define LINES 50
#define ROWS 30



void readOneLine(char *x){
    int c;
    int i =0;
    do {
        c= getchar();
        *(x+i) = c;
        i++;
    }while (c != '\n');
    *(x+i-1) = 0;
}


void read(char data_input[LINES][ROWS], int *N){ //trimitem prin pointer pentru a ramane updatata valoarea lui N
     int i;
    *N = 0;
    data_input[0][0] = getchar();
    data_input[0][1] = getchar();

    *N = getInt(data_input[0][0]);//adaugam prima cifra a numarului de cuvinte

    if(data_input[0][1] != '\n'){//daca nr este format din doua cifre
         *N = *N*10 +  getInt((int)data_input[0][1]);//actualizam nr
         read_blanc;
         data_input[0][2]=0;
    }else{
        data_input[0][1]= 0;
    }
    for(i = 1; i <= *N; i++){
         readOneLine(data_input[i]);       
     }
    
}

void read_Bonus(char data_input[LINES][ROWS], int *N){ // se fac pasi in plus pt a citi "literele" bonus
    int i;
    data_input[1][0] = getchar();
    data_input[1][1] = getchar();
    read_blanc;
    data_input[2][0] = getchar();
    data_input[2][1] =getchar();
    read_blanc;
    for(i = 3; i <= *N+2; i++){
         readOneLine(data_input[i]);       
     }
    
}

void add_OneWord(char board[15][15], int coord[3], char word[16]){
    if( coord[2] == 0 ){
        int poz = 0;
        while(word[poz] != 0){
            board[coord[0]][coord[1]+poz] = word[poz];
            poz++;
        }
    }
    if(coord[2] == 1){
        int poz = 0;
        while(word[poz] != 0){
            board[coord[0]+poz][coord[1]] =  word[poz];
            poz++;
        }
    }

}


void split_Words(char data_input[LINES][ROWS], int coord[3], char word[16], int i){
        int space = 0, poz = 0;// avem trei " " care delimiteaza informatiile
        coord[0] = 0;
        coord[1] = 0;
        coord[2] = 0;
        while(space < 3){
            if(data_input[i][poz] != ' '){
                switch(space)
                { 
                    case 0:
                        coord[0] = coord[0]*10 + getInt(data_input[i][poz]);
                        break;
                    case 1:
                        coord[1] = coord[1]*10 + getInt(data_input[i][poz]);
                        break;
                        
                    case 2:
                        coord[2] = getInt(data_input[i][poz]);
                         break;
                
                }
            }else {
                space++;
            }
             poz++;
        }
        strcpy(word, data_input[i]+poz);
}


int score(char word[16], int scoreLetter[26]){
    int i, n = strlen(word), points = 0;
    for(i = 0; i < n; i++){
        points += scoreLetter[(int)word[i]- (int)'A'];
    }
    return points;
}

int score_Bonus(char lBonus[2][2],char word[16],int coord[3], int scrLetter[26]){
    int i, n = strlen(word), points = 0;
    int no_Bonus1 = 0, no_Bonus2 = 0,found1 = 0, found2 = 0;
    for(i = 0; i < n; i++){
        points += scrLetter[(int)word[i]- (int)'A'];
        if(word[i] == lBonus[0][0] && word[i+1] == lBonus[0][1]){
            found1 = 1; //s-a gasit in cuvant un substring pentru bonusul 1
        }
        if(word[i] == lBonus[1][0] && word[i+1] == lBonus[1][1] && i == (n-2)){
            found2 = 1;//s-a gasit in cuvant substring-ul necesar pt bonusul 2
        }
        if(coord[2] == 0){
            if(bonus_board[coord[0]][coord[1]+i] == 1 )
                no_Bonus1++;//cuvantul se suprapune cu o casuta cu 1
            if(bonus_board[coord[0]][coord[1]+i] == 2)
                no_Bonus2 ++;// cuvantul se suprapune cu o casuta cu 2
        }
        else{
            if(bonus_board[coord[0]+i][coord[1]] == 1 )
                no_Bonus1++;//cuvantul se suprapune cu o casuta cu 1
            if(bonus_board[coord[0]+i][coord[1]] == 2)
                no_Bonus2++;// cuvantul se suprapune cu o casuta cu 2
        }
    }

    if(found1 == 1 && no_Bonus1 != 0)
        for(i = 0; i < no_Bonus1; i++)
            points *= 2;
    if(found2 == 1 && no_Bonus2 != 0){
        for(i = 0; i < no_Bonus2; i++)
            points *= 3;
    }
    return points;
}


int found_Board(char data_input[LINES][ROWS], int N, char words[16]){
    int i, coord[3];
    char word[16];
  
    for(i = 1; i <= N; i++){
        split_Words(data_input, coord, word, i);
        if(strcmp(word , words) == 0){ 
            return 0;}
    }

    return 1;
}

int board_limits( char words[16], int i, int j){

    int n = strlen(words);
    int position = -1;// => cuvantul nu se poate pune nici pe verticala nici pe orizontala
    if(j+n <= SIZE)
       position = 0;//position == 0 => se poate pune doar pe orizontala
    if(i+n <= SIZE)
        position = 1;//position == 1 => se poate pune doar pe verticala
    if((i+n <= SIZE) && (j+n <= SIZE))
        position = 2; //position == 2 => se poate pune si pe orizontala si pe verticala
    return position;
}

int canBePlaced(char board[SIZE][SIZE], char words[16], int y, int x, int d){
    int n = strlen(words) ;
    int i = 1;
    if(d == 0){
     for(i = 1; i < n ; i ++){
            if( (x+i) > SIZE || board[y][x+i] != '.'){//daca se afla o litera 
                return 0;}
        }
    }
    if(d == 1){
        for(i = 1; i < n; i++){
            if((y+i) > SIZE || board[y+i][x] != '.')
                return 0;
        }
    }
    return 1;
    
}

void assign(int coord_New_Word[3], int y, int x, int d){
    coord_New_Word[0] = y;
    coord_New_Word[1] = x;
    coord_New_Word[2] = d;
}

void find_Position(char board[SIZE][SIZE], char words[16], int coord[3]){
    int i, j, ok = 0, ok2 = 0;
    coord[0] = 16;
    for( i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){//cautam prima litera a cuvantului pe tabla
            if (board[i][j] == words[0]){
                coord[2] = board_limits(words, i, j);//returneaza daca se va plasa pe orizontala sau pe verticala
                 if(coord[2] == -1){//daca nu incape nici pe orizontala nici pe verticala
                     continue;
                 }else{
                     if(coord[2] == 0 || coord[2] == 1){//se poate pune doar pe orizontala sau pe verticala
                     
                        ok = canBePlaced(board, words, i , j, coord[2]);
                        if(ok == 1){// nu exista suprapuneri
                            assign(coord, i, j, coord[2]);
                            return;
                        }
                     }else{//se poate pune in ambele moduri
                     //intai incercam pe orizontala
                     ok = canBePlaced(board, words, i , j ,0);
                         if(ok == 1){
                           assign(coord, i , j, 0);
                             return;
                     }else{//incercam pe verticala
                           
                            ok2 = canBePlaced(board, words, i, j, 1);
                            if(ok2 == 1){
                                assign(coord, i, j, 1);
                                return;
                        }
                     }

                     }
                 }
            }
        }
    }
}

int find_Position_Bonus(char board[SIZE][SIZE], char words[16], int coord[3], char lBonus[2][2],int scrLetter[26] ){
int i, j, ok = 0, ok2 = 0, scrMax = -1, coord_prov[3];
coord[0] = 16;
    for( i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){//cautam prima litera a cuvantului pe tabla
            if (board[i][j] == words[0]){
                coord_prov[2] = board_limits(words, i, j);//returneaza daca se va plasa pe orizontala sau pe verticala
                 if(coord_prov[2] == -1){//daca nu incape nici pe orizontala nici pe verticala
                     continue;
                 }else{
                     if(coord_prov[2] == 0 || coord_prov[2] == 1){//se poate pune doar pe orizontala sau pe verticala
                        ok = canBePlaced(board, words, i , j, coord_prov[2]);
                        if(ok == 1){// nu exista suprapuneri
                            coord_prov[0] = i;
                            coord_prov[1] = j;
                            if(scrMax  < score_Bonus(lBonus, words, coord_prov, scrLetter)){
                                scrMax = score_Bonus(lBonus, words, coord_prov, scrLetter);
                                assign(coord, coord_prov[0], coord_prov[1], coord_prov[2]);
                            }
                        }
                     }else{//se poate pune in ambele moduri
                     //intai incercam pe orizontala
                     ok = canBePlaced(board, words, i , j ,0);
                         if(ok == 1){
                            coord_prov[0] = i;
                            coord_prov[1] = j;
                            coord_prov[2] = 0;
                            if(scrMax  < score_Bonus(lBonus, words, coord_prov, scrLetter)){
                                scrMax = score_Bonus(lBonus, words, coord_prov, scrLetter);
                                assign(coord, coord_prov[0], coord_prov[1], coord_prov[2]);
                            }
                     }else{//incercam pe verticala
                           
                            ok2 = canBePlaced(board, words, i, j, 1);
                            if(ok2 == 1){
                                 coord_prov[0] = i;
                                 coord_prov[1] = j;
                                 coord_prov[2] = 1;
                                 if(scrMax  < score_Bonus(lBonus, words, coord_prov, scrLetter)){
                                    scrMax = score_Bonus(lBonus, words, coord_prov, scrLetter);
                                    assign(coord, coord_prov[0], coord_prov[1], coord_prov[2]);
                            }
                        }
                     }

                     }
                 }
            }
        }
    }
    if(coord[0] < 16)
        return scrMax;
    else
    {
        return -1;
    }
    
}


void task0(char board[SIZE][SIZE]){
    int i,j;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            board[i][j]='.';
        }
    }
}

void task1(char board[SIZE][SIZE], char data_input[LINES][ROWS]){
    int *p, N = 0;
    p = &N;
    char word[16];
    int coord[3] = {0};//coord[0] = y, coord[1] = x, coord[2] = d;
    task0(board);
    read(data_input, p);
    for(int i = 1; i <= N; i++){//adaugarea in tabla a cuvintelor
        split_Words(data_input, coord, word, i);
        add_OneWord(board, coord, word);
    }
}

void task2( char data_input[LINES][ROWS]){
    int *p, N = 0,  score1 = 0, score2 = 0;
    p = &N;
    int coord[3] = {0};
    char word[16];
    read(data_input, p);
    int scoreLetters[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};//scorul asociat fiecarei litere
    for(int i = 1; i <= N; i++){
        if(i%2 == 1)//player1
        {
            split_Words(data_input, coord, word, i);
            score1 += score(word, scoreLetters);

        }else{
            split_Words(data_input, coord, word, i);
            score2 += score(word, scoreLetters);
        }
    }
    printf("Player 1: %d Points\n", score1);
    printf("Player 2: %d Points\n", score2);
}


void task3(char data_input[LINES][ROWS], int scorePlayers[2], char lettersBonus[2][2]){
    int *p, N = 0, score1 = 0, score2 = 0; 
    char word[16];
    int coord[3];
    p = &N;
    int scoreLetters[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};//scorul asociat fiecarei litere
   lettersBonus[0][0] = getchar();
   lettersBonus[0][1] = getchar();
   read_blanc;
   lettersBonus[1][0] = getchar ();
   lettersBonus[1][1] = getchar();
   read_blanc;
   read(data_input, p);
    for(int i = 1; i <= N; i++){
        if(i%2 == 1)//player1
        {
            split_Words(data_input, coord, word, i);
            score1 += score_Bonus(lettersBonus, word, coord, scoreLetters);

        }else{
            split_Words(data_input, coord, word, i);
            score2 += score_Bonus(lettersBonus,word, coord, scoreLetters);
        }
    }
    scorePlayers[0] = score1;
    scorePlayers[1] = score2;
}


void task4(char board[SIZE][SIZE], char data_input[LINES][ROWS]){
    int i, N, coord[3], found;
   for(i = 0; i < 6; i++){
       read_blanc;//nu folosim substring-urile pentru bonusuri in acest task
   }
    task1(board, data_input);
    N = getInt(data_input[0][0]);
   if(data_input[0][1] != 0 ){
       N = N*10 + getInt(data_input[0][1]);
   }
   for(i = 0; i < 100; i++){  
       found = found_Board(data_input, N, words[i]);//vedem daca s-a gasit cuvantul pe tabla
       if(found == 0){
            continue;}// nu mai are rost sa continuam verificarile
        find_Position(board, words[i], coord);//cautam pozitia pe care am putea pune cuvantul si testam daca poate intra pe tabla/se intersecteaza cu alt cuvant
        if(coord[0] < 16){

            add_OneWord(board, coord, words[i]);
            return;
        }
   }
   
}


void task5(char data_input[LINES][ROWS], char board[SIZE][SIZE]){
    int scorePlayers[2] = {0,0};
    int scrLetter[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};//scorul asociat fiecarei litere
    char lBonus[2][2], word[16];
    task3(data_input, scorePlayers, lBonus);//am calculat scorul celor 2 jucatori
    //gasim cuvantul optim 
    int i, N, coord_New_Word[3], coord_Max[3], coord[3],found, score_Max = -1, aux, position = -1;
    task0(board);
    N = getInt(data_input[0][0]);
   if(data_input[0][1] != 0 ){
       N = N*10 +  getInt(data_input[0][1]);
   }
    for( i = 1; i <= N; i++){//adaugarea in tabla a cuvintelor
        split_Words(data_input, coord, word, i);
        add_OneWord(board, coord, word);
    }
   for(i = 0; i < 100; i++){  
       found = found_Board(data_input, N, words[i]);//vedem daca s-a gasit cuvantul pe tabla
       if(found == 0){
            continue;}// nu mai are rost sa continuam verificarile  
        aux = find_Position_Bonus(board, words[i], coord_New_Word, lBonus, scrLetter);//gasim pozitia si in functie de punctaj
        if(score_Max <= aux){
            position = i;
            score_Max = aux;
            assign(coord_Max, coord_New_Word[0], coord_New_Word[1], coord_New_Word[2]);
        }
   }
    if(scorePlayers[0] <= scorePlayers[1]+score_Max){
        add_OneWord(board, coord_Max, words[position]);
        print_board(board);
    }
    else{
        printf("Fail!\n");
    }

}

int found_Board_plus(char data_input[LINES][ROWS], int N, char words[16], char compar[LINES][16]){
    int i, coord[3];
    char word[16];
    for(i = 1; i <= N; i++){
        split_Words(data_input, coord, word, i);
        if(strcmp(word , words) == 0){ 
            return 0;}
        if(strcmp(compar[i], words) == 0){
            return 0;
        }
    }

    return 1;
}

int pick_Word(char data_input[LINES][ROWS],char board[SIZE][SIZE], char lBonus[2][2], int scrLetter[26], int N){
int i;
int coord[3], coord_Max[3],found, scr_Max = -1, aux, position = -1;
char compar[LINES][16];
 for(i = 0; i < 100; i++){  
       found = found_Board_plus(data_input, N, words[i], compar);
       if(found == 0){
            continue;}  
        aux = find_Position_Bonus(board, words[i], coord, lBonus, scrLetter);
        if(scr_Max <= aux){
            if(scr_Max == aux){
                if(coord[0] < coord_Max[0]){
                    position = i;
                    scr_Max = aux;
                    assign(coord_Max, coord[0], coord[1], coord[2]);
                }else{
                    if(coord[0] == coord_Max[0] && coord[1] < coord_Max[1]){
                        position = i;
                        scr_Max = aux;
                        assign(coord_Max, coord[0], coord[1], coord[2]);
                    }
                }
            }else{
                position = i;
                 scr_Max = aux;
                assign(coord_Max, coord[0], coord[1], coord[2]);
            }
        }
    
   }
   add_OneWord(board, coord_Max, words[position]);
   strcpy(words[position], compar[N-1]);
   //compar retine cuvintele introduse de catre player-ul 2
   return scr_Max;
}

void task6(char data_input[LINES][ROWS],char board[SIZE][SIZE]){
    int N, scorePlayers[2] = {0,0};
    char lBonus[2][2];
    int scrLetter[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};//scorul asociat fiecarei litere
    int coord[3];
    char word[16];
    lBonus[0][0] = getchar();
   lBonus[0][1] = getchar();
   read_blanc;
   lBonus[1][0] = getchar ();
   lBonus[1][1] = getchar();
   read_blanc;
    N = 0;
    data_input[0][0] = getchar();
    data_input[0][1] = getchar();

    N = getInt(data_input[0][0]);//adaugam prima cifra a numarului de cuvinte

    if(data_input[0][1] != '\n'){
        N = N*10 +  getInt(data_input[0][1]);//actualizam nr
        read_blanc;
        data_input[0][2]=0;
    }else{
        data_input[0][1]= 0;
    }
    task0(board);
    for(int i = 0; i < N; i++){
        readOneLine(data_input[i]);
        split_Words(data_input, coord, word, i);
        add_OneWord(board, coord, word);
        scorePlayers[0] += score_Bonus(lBonus, word, coord, scrLetter);
        scorePlayers[1] += pick_Word(data_input, board, lBonus, scrLetter, i+1);
        print_board(board);
    }
    print_board(board);
    if(scorePlayers[0] > scorePlayers[1]){
        printf("Player 1 Won!\n");
    }else{
        printf("Player 2 Won!\n");
    }

}



int main(void)
{
    char board[SIZE][SIZE], task[2], data_input[LINES][ROWS], letterBonus[2][2];
    int scorePlayers[2] = {0, 0};
    task[0] = getchar();
    task[1] = 0;
    read_blanc;
    switch(task[0]){
        case '0':
            task0(board);
            print_board(board);
            break;

        case '1':
            task1(board, data_input);
            print_board(board);  
            break;

        case '2':
            task2(data_input);
            break;

        case '3':
        task3(data_input, scorePlayers, letterBonus);//letterBonus-->first line: bonus1; second line: bonus2
        //folosesc functia si la task5, motiv pentru care este parametru letterBonus
        printf("Player 1: %d Points\n", scorePlayers[0]);
        printf("Player 2: %d Points\n", scorePlayers[1]);
        break;

        case '4':
        task4(board, data_input);
        print_board(board);
        break;
    
        case '5':
            task5(data_input, board);
            break;
        case '6':
            task6(data_input, board);
            break;
        default:
            break;
    }
    return 0;
}