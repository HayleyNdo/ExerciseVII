#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP(ms) usleep((ms) * 1000)
#endif

#define SIZE 8

void display(char board[SIZE][SIZE]) {
    printf("\n  +--+--+--+--+--+--+--+--+\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d |", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf(" %c |", board[i][j]);
        }
        printf("\n  +--+--+--+--+--+--+--+--+\n");
    }
    printf("    A  B  C  D  E  F  G  H\n");
}

void initializeBoard(char board[SIZE][SIZE], char A, char B) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
    
    // Placement des pièces
    char P1 = A, P2 = B;
    for (int i = 0; i < 3; i++) {
        for (int j = (i % 2); j < SIZE; j += 2) {
            board[i][j] = P2;
        }
    }
    for (int i = 5; i < SIZE; i++) {
        for (int j = (i % 2); j < SIZE; j += 2) {
            board[i][j] = P1;
        }
    }
}

void saveHighScore(const char *player, int score) {
    FILE *f = fopen("highscore.txt", "w");
    if (f) {
        fprintf(f, "%s = %d\n", player, score);
        fclose(f);
    } else {
        printf("Erreur : Impossible d'enregistrer le score.\n");
    }
}

int getBoardIndex(char letter) {
    return letter - 'A';
}

int isValidMove(char board[SIZE][SIZE], int startRow, int startCol, int endRow, int endCol, char player) {
    if (startRow < 0 || startRow >= SIZE || startCol < 0 || startCol >= SIZE ||
        endRow < 0 || endRow >= SIZE || endCol < 0 || endCol >= SIZE) {
        return 0; // Hors limites
    }
    if (board[startRow][startCol] != player || board[endRow][endCol] != ' ') {
        return 0; // Pas une pièce du joueur ou la case cible n'est pas vide
    }
    return 1;
}

void makeMove(char board[SIZE][SIZE], int startRow, int startCol, int endRow, int endCol, char player) {
    board[startRow][startCol] = ' ';
    board[endRow][endCol] = player;
}

int main() {
    char board[SIZE][SIZE];
    char name1[25], name2[25], A, B;
    int pla = 0, opp = 0;
    
    printf("\nBienvenue au jeu de dames !\n");
    printf("Entrez le nom du joueur 1 : ");
    scanf("%s", name1);
    printf("Entrez le nom du joueur 2 : ");
    scanf("%s", name2);
    
    printf("Joueur 1, choisissez votre symbole : ");
    scanf(" %c", &A);
    printf("Joueur 2, choisissez votre symbole : ");
    scanf(" %c", &B);
    
    while (A == B) {
        printf("Les symboles ne peuvent pas être identiques. Joueur 2, choisissez un autre symbole : ");
        scanf(" %c", &B);
    }
    
    initializeBoard(board, A, B);
    display(board);
    
    // Boucle de jeu
    int turn = 0;
    while (1) {
        char currentPlayer = (turn % 2 == 0) ? A : B;
        char playerName[25];
        strcpy(playerName, (turn % 2 == 0) ? name1 : name2);
        
        printf("\n%s (%c), entrez votre coup (ex: A3 B4) : ", playerName, currentPlayer);
        char start[3], end[3];
        scanf("%s %s", start, end);
        
        int startCol = getBoardIndex(start[0]);
        int startRow = start[1] - '1';
        int endCol = getBoardIndex(end[0]);
        int endRow = end[1] - '1';
        
        if (isValidMove(board, startRow, startCol, endRow, endCol, currentPlayer)) {
            makeMove(board, startRow, startCol, endRow, endCol, currentPlayer);
        } else {
            printf("Mouvement invalide, essayez encore.\n");
            continue;
        }
        
        display(board);
        
        // Vérifier conditions de victoire (à implémenter)
        
        turn++;
    }
    
    printf("Fin du jeu.\n");
    return 0;
}
