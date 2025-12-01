#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NoPista {
    char texto[100];
    struct NoPista* esquerda;
    struct NoPista* direita;
} NoPista;

typedef struct Sala {
    char nome[50];
    char pista[100]; 
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

Sala* criarSala(char* nome, char* pista) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro de memória!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

NoPista* inserirPista(NoPista* raiz, char* texto) {
    if (raiz == NULL) {
        NoPista* novo = (NoPista*)malloc(sizeof(NoPista));
        strcpy(novo->texto, texto);
        novo->esquerda = NULL;
        novo->direita = NULL;
        printf(">> [!] Pista coletada: \"%s\"\n", texto);
        return novo;
    }

    int comparacao = strcmp(texto, raiz->texto);

    if (comparacao < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, texto);
    } 
    else if (comparacao > 0) {
        raiz->direita = inserirPista(raiz->direita, texto);
    }

    return raiz;
}

void exibirPistas(NoPista* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf(" - %s\n", raiz->texto);
        exibirPistas(raiz->direita);
    }
}

void explorarSalasComPistas(Sala* salaAtual, NoPista** raizPistas) {
    char escolha;

    if (salaAtual == NULL) return;

    printf("\n=== DETECTIVE QUEST: A BUSCA POR PISTAS ===\n");

    while (salaAtual != NULL) {
        printf("\n-------------------------------------------------\n");
        printf("Local atual: ** %s **\n", salaAtual->nome);

        if (strlen(salaAtual->pista) > 0) {
            *raizPistas = inserirPista(*raizPistas, salaAtual->pista);
            
        } else {
            printf("(Nenhuma pista nova encontrada aqui.)\n");
        }

        printf("\nPara onde deseja ir?\n");
        if (salaAtual->esquerda != NULL) printf(" [e] Esquerda\n");
        if (salaAtual->direita != NULL) printf(" [d] Direita\n");
        printf(" [s] Sair e ver relatório\n");
        
        printf("Sua escolha: ");
        scanf(" %c", &escolha);

        if (escolha == 's' || escolha == 'S') {
            break;
        } 
        else if (escolha == 'e' || escolha == 'E') {
            if (salaAtual->esquerda) salaAtual = salaAtual->esquerda;
            else printf(">> Parede. Não há passagem.\n");
        } 
        else if (escolha == 'd' || escolha == 'D') {
            if (salaAtual->direita) salaAtual = salaAtual->direita;
            else printf(">> Parede. Não há passagem.\n");
        }
        else {
            printf(">> Opção inválida.\n");
        }
    }
}

int main() {
    NoPista* inventarioPistas = NULL;

    Sala* raiz = criarSala("Hall de Entrada", ""); 
    
    Sala* salaEsq = criarSala("Sala de Estar", "Relógio parado às 10h");
    Sala* salaEsq_Esq = criarSala("Biblioteca", "Livro sobre venenos aberto");
    Sala* salaEsq_Dir = criarSala("Jardim", "Pegadas de lama");
    
    Sala* salaDir = criarSala("Cozinha", "Faca faltando no faqueiro");
    Sala* salaDir_Esq = criarSala("Despensa", "");
    Sala* salaDir_Dir = criarSala("Porão", "Bilhete rasgado com ameaça");

    raiz->esquerda = salaEsq;
    raiz->direita = salaDir;

    salaEsq->esquerda = salaEsq_Esq;
    salaEsq->direita = salaEsq_Dir;

    salaDir->esquerda = salaDir_Esq;
    salaDir->direita = salaDir_Dir;

    explorarSalasComPistas(raiz, &inventarioPistas);

    printf("\n========================================\n");
    printf("     RELATÓRIO FINAL DO DETETIVE      \n");
    printf("========================================\n");
    
    if (inventarioPistas == NULL) {
        printf("Você não coletou nenhuma pista!\n");
    } else {
        printf("Pistas coletadas (Ordem Alfabética):\n");
        exibirPistas(inventarioPistas);
    }
    printf("\nFim do jogo.\n");

    return 0;
}