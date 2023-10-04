#ifndef LABIRINTO_
#define LABIRINTO_

#ifdef _WIN32 || _WIN64
    #include <Windows.h>
    #define SLEEP Sleep(200)
    #define CLEAR system("cls")
#else
    #include <unistd.h>
    #define SLEEP usleep(200000)
    #define CLEAR system("clear")
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct no{
    int x;
    int y;
    struct no *proximo;
} No;

typedef struct{
    No *topo;
    int passos;
} Pilha;

typedef struct{ //Estrutura para armazenar coordenadas de inicio e chegada.
    int x, y;
} Coordenadas;

Pilha *inicializar_pilha();
void andar(Pilha *pilha, int x, int y);
void voltar(Pilha *pilha);
void imprimir_labirinto(int **mat, int n, Pilha *pilha);
void achar_caminho(Pilha *pilha, Coordenadas fim, int **mat, int n);
int **ler_arquivo(int *n, const char *arquivo);
void identificar_inicio_fim(int **mat, int *iX, int *iY, int *fX, int*fY, int n);
void imprimir_caminho(No *no);
void liberar_pilha(Pilha *pilha);
void liberar_matriz(int **mat, int n);

#endif