#include "labirinto.h"

int main(){
    int n;
    char arquivo[20] = "labirinto.txt";
    int **mat = ler_arquivo(&n, arquivo);
    Coordenadas inicio, fim;
    Pilha *pilha = inicializar_pilha();

    identificar_inicio_fim(mat, &inicio.x, &inicio.y, &fim.x, &fim.y, n); //Encontrando coordenadas do inicio e da chegada.
    andar(pilha, inicio.x, inicio.y);                                     //Definindo início do labirinto.
    achar_caminho(pilha, fim, mat, n);

    printf("\nCaminho correto: ");
    imprimir_caminho(pilha->topo);
    printf("\nPassos: %d\n\n", pilha->passos);
    
    liberar_matriz(mat, n);
    liberar_pilha(pilha);

    return 0;
}