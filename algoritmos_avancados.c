#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Sala {
    char nome[50];          
    struct Sala* esquerda;  
    struct Sala* direita;   
} Sala;

Sala* criarSala(char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    
    if (novaSala == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

void explorarSalas(Sala* salaAtual) {
    char escolha;

    if (salaAtual == NULL) {
        printf("O mapa está vazio!\n");
        return;
    }

    printf("\n=== INÍCIO DA EXPLORAÇÃO: DETECTIVE QUEST ===\n");

    while (salaAtual != NULL) {
        printf("\n-------------------------------------------------\n");
        printf("Voce entrou em: ** %s **\n", salaAtual->nome);

        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("\nEsta sala não tem mais saídas. Você investigou tudo aqui!\n");
            printf("Fim da linha para este caminho.\n");
            break;
        }

        printf("Caminhos disponíveis:\n");
        if (salaAtual->esquerda != NULL) printf(" [e] Ir para a esquerda\n");
        if (salaAtual->direita != NULL) printf(" [d] Ir para a direita\n");
        
        printf(" [s] Sair do jogo\n");
        printf("Sua escolha: ");
        
        scanf(" %c", &escolha); 

        if (escolha == 's' || escolha == 'S') {
            printf("Você decidiu encerrar a investigação por hoje.\n");
            break;
        } 
        else if (escolha == 'e' || escolha == 'E') {
            if (salaAtual->esquerda != NULL) {
                salaAtual = salaAtual->esquerda; 
            } else {
                printf(">> Não há passagem para a esquerda aqui.\n");
            }
        } 
        else if (escolha == 'd' || escolha == 'D') {
            if (salaAtual->direita != NULL) {
                salaAtual = salaAtual->direita; 
            } else {
                printf(">> Não há passagem para a direita aqui.\n");
            }
        } 
        else {
            printf(">> Opção inválida! Tente novamente.\n");
        }
    }
    
    printf("\nObrigado por jogar Detective Quest!\n");
}

int main() {
    Sala* raiz = criarSala("Hall de Entrada");
    
    Sala* salaEsq = criarSala("Sala de Estar");
    Sala* salaDir = criarSala("Cozinha");
    
    Sala* salaEsq_Esq = criarSala("Biblioteca");
    Sala* salaEsq_Dir = criarSala("Jardim de Inverno");
    
    Sala* salaDir_Esq = criarSala("Despensa");
    Sala* salaDir_Dir = criarSala("Porão Escuro");

    raiz->esquerda = salaEsq;
    raiz->direita = salaDir;

    salaEsq->esquerda = salaEsq_Esq;
    salaEsq->direita = salaEsq_Dir;

    salaDir->esquerda = salaDir_Esq;
    salaDir->direita = salaDir_Dir;

    explorarSalas(raiz);
    
    return 0;
}
