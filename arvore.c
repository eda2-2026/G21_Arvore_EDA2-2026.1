#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *esq;
    struct no *dir;
} No;

No *criarNo(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No *inserirNo(No *raiz, int valor) {
    if (raiz == NULL)
        return criarNo(valor);

    if (valor < raiz->valor)
        raiz->esq = inserirNo(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserirNo(raiz->dir, valor);

    return raiz;
}

void emOrdem(No *raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("%d ", raiz->valor);
        emOrdem(raiz->dir);
    }
}

void liberarArvore(No *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

void menu() {
    printf("\nMenu\n"); 
    printf("1 - Inserir numero\n");
    printf("2 - Exibir numeros\n");
    printf("0 - Sair\n");
    printf("Digite a opcao: ");
}

int main() {
    int opcao, valor;
    No *raiz = NULL;

    do{
        menu();
        scanf("%i", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o numero a ser inserido: ");
            scanf("%i", &valor);
            raiz = inserirNo(raiz, valor);
            break;
        case 2:
            emOrdem(raiz);
            break;
        case 0:
            printf("programa encerrado.\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    }while(opcao != 0);

    liberarArvore(raiz);

    return 0;
}