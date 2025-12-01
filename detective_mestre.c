#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 31

typedef struct HashNode {
    char chavePista[100];
    char valorSuspeito[50];
    struct HashNode* proximo;
} HashNode;

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

HashNode* tabelaHash[TAM_HASH];

int funcaoHash(char* chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % TAM_HASH;
}

void inserirNaHash(char* pista, char* suspeito) {
    int indice = funcaoHash(pista);
    HashNode* novo = (HashNode*)malloc(sizeof(HashNode));
    strcpy(novo->chavePista, pista);
    strcpy(novo->valorSuspeito, suspeito);
    
    novo->proximo = tabelaHash[indice];
    tabelaHash[indice] = novo;
}

char* encontrarSuspeito(char* pista) {
    int indice = funcaoHash(pista);
    HashNode* atual = tabelaHash[indice];
    
    while (atual != NULL) {
        if (strcmp(atual->chavePista, pista) == 0) {
            return atual->valorSuspeito;
        }
        atual = atual->proximo;
    }
    return NULL;
}

NoPista* inserirPista(NoPista* raiz, char* texto) {
    if (raiz == NULL) {
        NoPista* novo = (NoPista*)malloc(sizeof(NoPista));
        strcpy(novo->texto, texto);
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }
    int cmp = strcmp(texto, raiz->texto);
    if (cmp < 0) raiz->esquerda = inserirPista(raiz->esquerda, texto);
    else if (cmp > 0) raiz->direita = inserirPista(raiz->direita, texto);
    return raiz;
}

void exibirPistasBST(NoPista* raiz) {
    if (raiz != NULL) {
        exibirPistasBST(raiz->esquerda);
        printf(" - %s\n", raiz->texto);
        exibirPistasBST(raiz->direita);
    }
}

void contarEvidencias(NoPista* raiz, char* suspeitoAcusado, int* contador) {
    if (raiz != NULL) {
        contarEvidencias(raiz->esquerda, suspeitoAcusado, contador);
        
        char* suspeitoReal = encontrarSuspeito(raiz->texto);
        if (suspeitoReal != NULL && strcmp(suspeitoReal, suspeitoAcusado) == 0) {
            (*contador)++;
        }
        
        contarEvidencias(raiz->direita, suspeitoAcusado, contador);
    }
}

Sala* criarSala(char* nome, char* pista) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

void explorarSalas(Sala* salaAtual, NoPista** inventario) {
    char escolha;
    if (salaAtual == NULL) return;

    printf("\n=== DETECTIVE QUEST: FASE FINAL ===\n");

    while (salaAtual != NULL) {
        printf("\n-------------------------------------------------\n");
        printf("Local: ** %s **\n", salaAtual->nome);

        if (strlen(salaAtual->pista) > 0) {
            printf(">> VOCÊ ENCONTROU UMA PISTA: \"%s\"\n", salaAtual->pista);
            *inventario = inserirPista(*inventario, salaAtual->pista);
            strcpy(salaAtual->pista, ""); 
        }

        printf("Opções: [e] Esquerda | [d] Direita | [s] Sair e Acusar\n");
        printf("Escolha: ");
        scanf(" %c", &escolha);

        if (escolha == 's' || escolha == 'S') break;
        else if (escolha == 'e' || escolha == 'E') {
            if (salaAtual->esquerda) salaAtual = salaAtual->esquerda;
            else printf(">> Bloqueado.\n");
        }
        else if (escolha == 'd' || escolha == 'D') {
            if (salaAtual->direita) salaAtual = salaAtual->direita;
            else printf(">> Bloqueado.\n");
        }
    }
}

void verificarSuspeitoFinal(NoPista* inventario) {
    char acusado[50];
    int provas = 0;

    printf("\n========================================\n");
    printf("        TRIBUNAL DA MANSÃO            \n");
    printf("========================================\n");

    if (inventario == NULL) {
        printf("Você não coletou nenhuma pista! Caso encerrado por falta de provas.\n");
        return;
    }

    printf("Pistas coletadas:\n");
    exibirPistasBST(inventario);

    printf("\nQuem é o culpado? (Ex: Mordomo, Governanta, Jardineiro): ");
    scanf("%s", acusado);

    contarEvidencias(inventario, acusado, &provas);

    printf("\nAnalisando evidências contra %s...\n", acusado);
    printf("Provas concretas encontradas: %d\n", provas);

    if (provas >= 2) {
        printf("\n[VITÓRIA] A policia prendeu o(a) %s! As provas eram irrefutáveis.\n", acusado);
        printf("Parabéns, Detetive!\n");
    } else {
        printf("\n[DERROTA] O juiz rejeitou a acusação.\n");
        printf("Você precisa de pelo menos 2 provas conectadas a este suspeito.\n");
    }
}


int main() {
    for(int i=0; i<TAM_HASH; i++) tabelaHash[i] = NULL;

    inserirNaHash("Faca enferrujada", "Mordomo");
    inserirNaHash("Relógio de bolso", "Mordomo");
    inserirNaHash("Luvas de couro", "Mordomo");
    
    inserirNaHash("Veneno de rato", "Governanta");
    inserirNaHash("Diário secreto", "Governanta");
    
    inserirNaHash("Pá suja de terra", "Jardineiro");

    NoPista* meuInventario = NULL;

    Sala* raiz = criarSala("Hall", "");
    
    Sala* s1 = criarSala("Sala de Jantar", "Faca enferrujada");
    Sala* s2 = criarSala("Cozinha", "Relógio de bolso");
    
    Sala* s3 = criarSala("Biblioteca", "Veneno de rato");
    Sala* s4 = criarSala("Quarto Principal", "Diário secreto");

    raiz->esquerda = s1;
    raiz->direita = s3;
    s1->esquerda = s2;
    s3->direita = s4;

    explorarSalas(raiz, &meuInventario);

    verificarSuspeitoFinal(meuInventario);

    return 0;
}
