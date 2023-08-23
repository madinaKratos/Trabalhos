#include <stdio.h>
#include <stdlib.h>

struct NoArvore {
    int valor;
    struct NoArvore* esquerda;
    struct NoArvore* direita;
};

struct Caminho {
    int caminho[100];
    int tamanho;
    struct Caminho* proximo;
};

struct NoArvore* criarNo(int valor) {
    struct NoArvore* novoNo = (struct NoArvore*)malloc(sizeof(struct NoArvore));
    novoNo->valor = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

struct NoArvore* inserirNoInicio(struct NoArvore* raiz, int valor) {
    struct NoArvore* novoNo = criarNo(valor);
    novoNo->direita = raiz;
    return novoNo;
}

void mostrarProfundidade(struct NoArvore* raiz) {
    if (raiz == NULL) {
        return;
    }
    printf("%d ", raiz->valor);
    mostrarProfundidade(raiz->esquerda);
    mostrarProfundidade(raiz->direita);
}

void mostrarLargura(struct NoArvore* raiz) {
    if (raiz == NULL) {
        return;
    }

    struct NoArvore* fila[100];
    int frente = 0, tras = 0;

    fila[tras++] = raiz;

    while (frente < tras) {
        struct NoArvore* atual = fila[frente++];
        printf("%d ", atual->valor);

        if (atual->esquerda != NULL) {
            fila[tras++] = atual->esquerda;
        }
        if (atual->direita != NULL) {
            fila[tras++] = atual->direita;
        }
    }
}

int compararCaminhos(int caminho1[], int tamanho1, int caminho2[], int tamanho2) {
    if (tamanho1 != tamanho2) {
        return 0; // Os caminhos têm comprimentos diferentes
    }
	int i;
    for (i = 0; i < tamanho1; i++) {
        if (caminho1[i] != caminho2[i]) {
            return 0; // Os caminhos não são iguais
        }
    }

    return 1; // Os caminhos são iguais
}

int caminhoExiste(struct Caminho* pilha, int caminho[], int tamanho) {
    struct Caminho* atual = pilha;
    while (atual != NULL) {
        if (compararCaminhos(atual->caminho, atual->tamanho, caminho, tamanho)) {
            return 1; // O caminho já existe na pilha
        }
        atual = atual->proximo;
    }
    return 0; // O caminho não existe na pilha
}

void imprimirCaminhos(struct Caminho* pilha) {
    int numCaminho = 1;
    while (pilha != NULL) {
        printf("Caminho %d: ", numCaminho);
        int i;
        for (i = 0; i < pilha->tamanho; i++) {
            printf("%d", pilha->caminho[i]);
            if (i != pilha->tamanho - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
        pilha = pilha->proximo;
        numCaminho++;
    }
}

void buscarCaminhos(struct NoArvore* raiz, int alvo, struct Caminho* pilha, int passos) {
    if (raiz == NULL) {
        return;
    }

    pilha->caminho[pilha->tamanho++] = raiz->valor;

    if (raiz->valor == alvo) {
        int caminhoAtual[100];
        int i;
        for (i = 0; i < pilha->tamanho; i++) {
            caminhoAtual[i] = pilha->caminho[i];
        }

        if (!caminhoExiste(pilha->proximo, caminhoAtual, pilha->tamanho)) {
            struct Caminho* novoCaminho = (struct Caminho*)malloc(sizeof(struct Caminho));
            int i;
            for (i = 0; i < pilha->tamanho; i++) {
                novoCaminho->caminho[i] = pilha->caminho[i];
            }
            novoCaminho->tamanho = pilha->tamanho;
            novoCaminho->proximo = pilha->proximo;
            pilha->proximo = novoCaminho;
        }
    }

    buscarCaminhos(raiz->esquerda, alvo, pilha, passos + 1);
    buscarCaminhos(raiz->direita, alvo, pilha, passos + 1);

    pilha->tamanho--;
}

int main() {
    struct NoArvore* raiz = criarNo(10);

   	raiz = inserirNoInicio(raiz, 7);
    raiz = inserirNoInicio(raiz, 12);
    raiz = inserirNoInicio(raiz, 5);
    raiz = inserirNoInicio(raiz, 9);
    raiz = inserirNoInicio(raiz, 1);
    raiz = inserirNoInicio(raiz, 3);
    raiz = inserirNoInicio(raiz, 2);
    raiz = inserirNoInicio(raiz, 4);
    raiz = inserirNoInicio(raiz, 7);
    raiz = inserirNoInicio(raiz, 6);
    raiz = inserirNoInicio(raiz, 8);
    raiz = inserirNoInicio(raiz, 11);
    raiz = inserirNoInicio(raiz, 13);
    raiz = inserirNoInicio(raiz, 14);
    raiz = inserirNoInicio(raiz, 15);
    raiz = inserirNoInicio(raiz, 18);
    raiz = inserirNoInicio(raiz, 19);
    raiz = inserirNoInicio(raiz, 20);
    raiz = inserirNoInicio(raiz, 16);
    raiz = inserirNoInicio(raiz, 17);

    printf("Nós por profundidade: ");
    mostrarProfundidade(raiz);
    printf("\n");

    printf("Nós por largura: ");
    mostrarLargura(raiz);
    printf("\n");

    int alvo = 9;
    struct Caminho* pilha = (struct Caminho*)malloc(sizeof(struct Caminho));
    pilha->tamanho = 0;
    pilha->proximo = NULL;

    buscarCaminhos(raiz, alvo, pilha, 0);

    imprimirCaminhos(pilha->proximo);

    return 0;
}

