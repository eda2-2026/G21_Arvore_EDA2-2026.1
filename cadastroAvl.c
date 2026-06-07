#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    char nome[100];
    int matricula;
    char curso[100];
    char nivel[50];
    char status[50];
    char email[100];
    float ira;
    float mp;
    int altura;
    struct no *esq;
    struct no *dir;
} No;

int maior(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int altura(No *raiz) {
    if (raiz == NULL) {
        return -1;
    }
    return raiz->altura;
}

int fatorBalanceamento(No *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return altura(raiz->dir) - altura(raiz->esq);
}

No *criarNo() {
    No *novo = malloc(sizeof(No));

    printf("Nome: ");
    scanf(" %[^\n]", novo->nome);

    printf("Matricula: ");
    scanf("%d", &novo->matricula);

    printf("Curso: ");
    scanf(" %[^\n]", novo->curso);

    printf("Nivel: ");
    scanf(" %[^\n]", novo->nivel);

    printf("Status: ");
    scanf(" %[^\n]", novo->status);

    printf("E-Mail: ");
    scanf(" %[^\n]", novo->email);

    printf("IRA: ");
    scanf("%f", &novo->ira);

    printf("MP: ");
    scanf("%f", &novo->mp);

    novo->altura = 0;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

No *rotEsq(No *raiz) {
    No *novaRaiz = raiz->dir;
    No *temp = novaRaiz->esq;

    novaRaiz->esq = raiz;
    raiz->dir = temp;

    raiz->altura = 1 + maior(altura(raiz->esq), altura(raiz->dir));
    novaRaiz->altura = 1 + maior(altura(novaRaiz->esq), altura(novaRaiz->dir));

    return novaRaiz;
}

No *rotDir(No *raiz) {
    No *novaRaiz = raiz->esq;
    No *temp = novaRaiz->dir;

    novaRaiz->dir = raiz;
    raiz->esq = temp;

    raiz->altura = 1 + maior(altura(raiz->esq), altura(raiz->dir));
    novaRaiz->altura = 1 + maior(altura(novaRaiz->esq), altura(novaRaiz->dir));

    return novaRaiz;
}

No *rotEsqDir(No *raiz) {
    raiz->esq = rotEsq(raiz->esq);
    return rotDir(raiz);
}

No *rotDirEsq(No *raiz) {
    raiz->dir = rotDir(raiz->dir);
    return rotEsq(raiz);
}

No *inserirNo(No *raiz, No *novo) {
    if (raiz == NULL) {
        return novo;
    }

    if (novo->matricula < raiz->matricula) {
        raiz->esq = inserirNo(raiz->esq, novo);
    } else if (novo->matricula > raiz->matricula) {
        raiz->dir = inserirNo(raiz->dir, novo);
    } else {
        printf("Matricula ja cadastrada.\n");
        free(novo);
        return raiz;
    }

    raiz->altura = 1 + maior(altura(raiz->esq), altura(raiz->dir));

    int fb = fatorBalanceamento(raiz);

    if (fb > 1 && novo->matricula > raiz->dir->matricula) {
        return rotEsq(raiz);
    }

    if (fb < -1 && novo->matricula < raiz->esq->matricula) {
        return rotDir(raiz);
    }

    if (fb < -1 && novo->matricula > raiz->esq->matricula) {
        return rotEsqDir(raiz);
    }

    if (fb > 1 && novo->matricula < raiz->dir->matricula) {
        return rotDirEsq(raiz);
    }

    return raiz;
}

void emOrdem(No *raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);

        printf("\nNome: %s\n", raiz->nome);
        printf("Matricula: %d\n", raiz->matricula);
        printf("Curso: %s\n", raiz->curso);
        printf("Nivel: %s\n", raiz->nivel);
        printf("Status: %s\n", raiz->status);
        printf("E-Mail: %s\n", raiz->email);
        printf("IRA: %.2f\n", raiz->ira);
        printf("MP: %.2f\n", raiz->mp);
        printf("\nAltura: %d e Fator de Balanceamento: %d\n", raiz->altura, fatorBalanceamento(raiz));

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
    printf("1 - Inserir aluno\n");
    printf("2 - Exibir alunos em ordem\n");
    printf("3 - Remover aluno\n");
    printf("4 - Buscar aluno por matricula\n");
    printf("0 - Sair\n");
    printf("Digite a opcao: ");
}

int main() {
    int opcao;
    No *raiz = NULL;
    No *novo = NULL;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                novo = criarNo();
                raiz = inserirNo(raiz, novo);
                break;

            case 2:
                emOrdem(raiz);
                break;

            case 0:
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    liberarArvore(raiz);

    return 0;
}