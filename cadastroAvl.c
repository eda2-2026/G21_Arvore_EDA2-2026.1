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

    if (novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

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

void imprimirAluno(No *aluno) {
    printf("\nNome: %s\n", aluno->nome);
    printf("Matricula: %d\n", aluno->matricula);
    printf("Curso: %s\n", aluno->curso);
    printf("Nivel: %s\n", aluno->nivel);
    printf("Status: %s\n", aluno->status);
    printf("E-Mail: %s\n", aluno->email);
    printf("IRA: %.2f\n", aluno->ira);
    printf("MP: %.2f\n", aluno->mp);
    printf("Altura: %d\n", aluno->altura);
    printf("Fator de Balanceamento: %d\n", fatorBalanceamento(aluno));
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

No *menorNo(No *raiz) {
    No *atual = raiz;

    while (atual->esq != NULL) {
        atual = atual->esq;
    }

    return atual;
}

No *removerNo(No *raiz, int matricula) {
    if (raiz == NULL) {
        printf("Aluno nao encontrado.\n");
        return NULL;
    }

    if (matricula < raiz->matricula) {
        raiz->esq = removerNo(raiz->esq, matricula);
    } else if (matricula > raiz->matricula) {
        raiz->dir = removerNo(raiz->dir, matricula);
    } else {
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        } else if (raiz->esq == NULL) {
            No *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            No *temp = raiz->esq;
            free(raiz);
            return temp;
        } else {
            No *temp = menorNo(raiz->dir);

            raiz->matricula = temp->matricula;
            strcpy(raiz->nome, temp->nome);
            strcpy(raiz->curso, temp->curso);
            strcpy(raiz->nivel, temp->nivel);
            strcpy(raiz->status, temp->status);
            strcpy(raiz->email, temp->email);
            raiz->ira = temp->ira;
            raiz->mp = temp->mp;

            raiz->dir = removerNo(raiz->dir, temp->matricula);
        }
    }

    raiz->altura = 1 + maior(altura(raiz->esq), altura(raiz->dir));

    int fb = fatorBalanceamento(raiz);

    if (fb > 1 && fatorBalanceamento(raiz->dir) >= 0) {
        return rotEsq(raiz);
    }

    if (fb > 1 && fatorBalanceamento(raiz->dir) < 0) {
        return rotDirEsq(raiz);
    }

    if (fb < -1 && fatorBalanceamento(raiz->esq) <= 0) {
        return rotDir(raiz);
    }

    if (fb < -1 && fatorBalanceamento(raiz->esq) > 0) {
        return rotEsqDir(raiz);
    }

    return raiz;
}

No *buscarAluno(No *raiz, int matricula) {
    if (raiz == NULL) {
        return NULL;
    }

    if (matricula < raiz->matricula) {
        return buscarAluno(raiz->esq, matricula);
    } else if (matricula > raiz->matricula) {
        return buscarAluno(raiz->dir, matricula);
    }

    return raiz;
}

void emOrdem(No *raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        imprimirAluno(raiz);
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
    printf("5 - Mostrar altura e fator da raiz\n");
    printf("0 - Sair\n");
    printf("Digite a opcao: ");
}

int main() {
    int opcao;
    int matricula;
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

            case 3:
                printf("Digite a matricula: ");
                scanf("%d", &matricula);
                raiz = removerNo(raiz, matricula);
                break;

            case 4: {
                printf("Digite a matricula: ");
                scanf("%d", &matricula);

                No *aluno = buscarAluno(raiz, matricula);

                if (aluno != NULL) {
                    imprimirAluno(aluno);
                } else {
                    printf("Aluno nao encontrado.\n");
                }

                break;
            }

            case 5:
                if (raiz != NULL) {
                    printf("Altura da raiz: %d\n", raiz->altura);
                    printf("Fator de balanceamento da raiz: %d\n", fatorBalanceamento(raiz));
                } else {
                    printf("Arvore vazia.\n");
                }
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