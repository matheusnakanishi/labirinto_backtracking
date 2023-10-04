#include "labirinto.h"

Pilha *inicializar_pilha(){
    Pilha *novo = (Pilha*)malloc(sizeof(Pilha));

    novo->topo = NULL;
    novo->passos = 0;

    return novo;
}

void andar(Pilha *pilha, int x, int y){
    No *novo = (No*)malloc(sizeof(No));

    if (novo == NULL){
       printf("Erro ao alocar memoria.");
       exit(1);
    }

    novo->x = x;
    novo->y = y;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
    pilha->passos++;
}

void voltar(Pilha *pilha){
    No *excluir = pilha->topo;

    pilha->topo = pilha->topo->proximo;
    free(excluir);
    pilha->passos--;
}

void imprimir_labirinto(int **mat, int n, Pilha *pilha){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == pilha->topo->x && j == pilha->topo->y) //Posição atual.
                printf("o ");
            else{
                switch (mat[i][j]){
                    case 1:
                        printf("# "); //Parede;
                        break;
                    case 2:
                        printf(". "); //Início. Imprime ponto, pois vira rastro após o início.
                        break;
                    case 3:
                        printf("x "); //Chegada.
                        break;
                    case 4:
                        printf(". "); //Caminho percorrido.
                        break;
                    default:
                        printf("  "); //Caminho livre.
                        break;
                }
            }
        }
        printf("\n");
    }
}

void achar_caminho(Pilha *pilha, Coordenadas fim, int **mat, int n){

    while (pilha->topo->x != fim.x || pilha->topo->y != fim.y) //Enquanto as coordenadas do topo da pilha não forem iguais as da chegada.
    {
        int i = pilha->topo->x; //Ponto atual.
        int j = pilha->topo->y;

        if (i-1 >= 0 && mat[i-1][j] == 0 || mat[i-1][j] == 3) //Verificando posições possíveis.
        {
            andar(pilha, i-1, j);
            mat[i-1][j] = 4; //Valor 4 atribuído para saber que o caminho ja foi percorrido.

        } else if (i+1 <= n-1 && mat[i+1][j] == 0 || mat[i+1][j] == 3)
        {
            andar(pilha, i+1, j);
            mat[i+1][j] = 4;
            
        } else if (j-1 >= 0 && mat[i][j-1] == 0 || mat[i][j-1] == 3)
        {
            andar(pilha, i, j-1);
            mat[i][j-1] = 4;  

        } else if (j+1 <= n-1 && mat[i][j+1] == 0 || mat[i][j+1] == 3)
        {
            andar(pilha, i, j+1);
            mat[i][j+1] = 4;

        } else{
            if (pilha->topo->proximo)
                voltar(pilha);
            else{               //Sem solução, pois teve que desimpilhar o início para tentar encontrar um caminho.
                system("clear");
                printf("\nLabirinto sem solucao.\n");
                exit(1);
            }
            mat[i][j] = 5;  //Valor 5 atribuído para identificar caminho bloqueado.
        }
        CLEAR;
        imprimir_labirinto(mat, n, pilha); //Atualiza o labirinto.
        SLEEP;
    }
}

int **ler_arquivo(int *n, const char *arquivo){
    FILE *file = fopen(arquivo, "r");

    if (file == NULL){
        printf("Nao foi possivel ler o arquivo.");
        exit(1);
    }

    fscanf(file, "%d", n);  //Lendo dimensão.

    int **mat = (int**)malloc((*n) * sizeof(int*)); //Alocando matriz.
    for (int i = 0; i < (*n); i++)
        mat[i] = (int*)malloc((*n) * sizeof(int));
    
    for (int i = 0; i < (*n); i++)  //Lendo labirinto.
    {
        for (int j = 0; j < (*n); j++)
            fscanf(file, "%d", &mat[i][j]);
    }

    fclose(file);
    
    return mat;
}

void identificar_inicio_fim(int **mat, int *iX, int *iY, int *fX, int*fY, int n){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (mat[i][j] == 2){ //Início.
                *iX = i;
                *iY = j;
            }
            else if (mat[i][j] == 3){ //Fim.
                *fX = i;
                *fY = j;
            }
        }       
    }   
}

void imprimir_caminho(No *no){
    No *aux = no;
    //Imprime a pilha inversa, usando recursão.
    if (aux->proximo)
        imprimir_caminho(aux->proximo);
    
    printf("(%d,%d) ",aux->x, aux->y);
}

void liberar_pilha(Pilha *pilha){
    while (pilha->topo)
        voltar(pilha);
}

void liberar_matriz(int **mat, int n){
    for (int i = 0; i < n; i++)
        free(mat[i]);
    
    free(mat);
}