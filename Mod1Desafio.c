#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;               // Identificador único do item (ex: 1 para Arma, 2 para Munição, etc.)
    char nome[50];        
    char tipo[20];        
    int quantidade;       
} Item;

#define MAX_ITENS 10 
typedef struct {
    Item itens[MAX_ITENS]; 
    int totalItens;        
} Inventario;

void inicializarInventario(Inventario *inv);
void exibirMenu();
void cadastrarItem(Inventario *inv);
void listarItens(const Inventario *inv);
void removerItem(Inventario *inv);
void buscarItem(const Inventario *inv);

// --- Implementação das Funções ---

void inicializarInventario(Inventario *inv) {
    inv->totalItens = 0;
}

void exibirMenu() {
    printf("\n MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA \n");
    printf("1. Adicionar Item (Loot)\n");
    printf("2. Listar Itens da mochila\n");
    printf("3. Remover Item\n");
    printf("4. Buscar Item por Nome\n");
    printf("0. Sair\n");
    printf("--------------------------------------\n");
    printf("Escolha uma opcao: ");
}

void cadastrarItem(Inventario *inv) {
    if (inv->totalItens >= MAX_ITENS) {
        printf("\n Mochila Cheia! Nao e possivel coletar mais itens.\n");
        return;
    }

    Item novoItem;
    printf("\n--- Adicionar novo item ---\n");
    printf("ID do Item (inteiro): ");
    if (scanf("%d", &novoItem.id) != 1) {
        printf("\n Erro de leitura de ID.\n");    
        while (getchar() != '\n');
        return;
    }
    
    while (getchar() != '\n'); 
    printf("Nome do Item: ");
    if (fgets(novoItem.nome, sizeof(novoItem.nome), stdin) != NULL) {        
        novoItem.nome[strcspn(novoItem.nome, "\n")] = 0; 
    } else {
        printf("\n Erro de leitura de Nome.\n");
        return;
    }

    printf("Tipo do Item (Arma, Municao, Cura, Etc...): ");
    if (fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin) != NULL) {
        
        novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0;
    } else {
        printf("\n Erro de leitura de Tipo.\n");
        return;
    }

    printf("Quantidade: ");
    if (scanf("%d", &novoItem.quantidade) != 1) {
        printf("\n Erro de leitura de Quantidade.\n");
        while (getchar() != '\n');
        return;
    }
    
    while (getchar() != '\n');
    
    inv->itens[inv->totalItens] = novoItem;
    inv->totalItens++;

    printf("\n Item '%s' adicionado com sucesso!\n", novoItem.nome);
}


void listarItens(const Inventario *inv) {
    if (inv->totalItens == 0) {
        printf("\n A mochila esta vazia. Nao ha itens para listar.\n");
        return;
    }

    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", inv->totalItens, MAX_ITENS);
    printf("------------------------------------------------------------------------\n");
    printf("| %-4s | %-15s | %-15s | %-10s |\n", "ID", "NOME", "TIPO", "QUANTIDADE");
    printf("------------------------------------------------------------------------\n");

    for (int i = 0; i < inv->totalItens; i++) {
        printf("| %-4d | %-15s | %-15s | %-10d |\n", 
               inv->itens[i].id, 
               inv->itens[i].nome, 
               inv->itens[i].tipo, 
               inv->itens[i].quantidade);
    }
    printf("------------------------------------------------------------------------\n");    
}

void removerItem(Inventario *inv) {
    if (inv->totalItens == 0) {
        printf("\n A mochila esta vazia. Nao ha itens para remover.\n");
        return;
    }

    char nomeBusca[50];
    printf("\n--- REMOVER ITEM ---\n");
    printf("Digite o NOME do item a ser removido: ");
    if (fgets(nomeBusca, sizeof(nomeBusca), stdin) != NULL) {
        nomeBusca[strcspn(nomeBusca, "\n")] = 0; 
    } else {
        printf("\n Erro de leitura de Nome.\n");
        return;
    }

    int indiceRemover = -1;
    
    for (int i = 0; i < inv->totalItens; i++) {
        if (strcmp(inv->itens[i].nome, nomeBusca) == 0) {
            indiceRemover = i;
            break;
        }
    }

    if (indiceRemover != -1) {        
        for (int i = indiceRemover; i < inv->totalItens - 1; i++) {
            inv->itens[i] = inv->itens[i + 1];
        }        
        
        inv->totalItens--;
        printf("\n Item '%s' removido com sucesso da mochila.\n", nomeBusca);
    } else {
        printf("\n Erro: Item '%s' nao encontrado na mochila.\n", nomeBusca);
    }
}

void buscarItem(const Inventario *inv) {
    if (inv->totalItens == 0) {
        printf("\n A mochila esta vazia. Nao ha itens para buscar.\n");
        return;
    }

    char nomeBusca[50];
    printf("\n--- BUSCA DE ITEM ---\n");
    printf("Digite o NOME do item a ser buscado: ");
    if (fgets(nomeBusca, sizeof(nomeBusca), stdin) != NULL) {
        nomeBusca[strcspn(nomeBusca, "\n")] = 0; 
    } else {
        printf("\n Erro de leitura de Nome.\n");
        return;
    }

    int encontrado = 0;

    printf("\n--- RESULTADO DA BUSCA ---\n");
    for (int i = 0; i < inv->totalItens; i++) {        
        if (strstr(inv->itens[i].nome, nomeBusca) != NULL) {
            printf("ID: %d | Nome: %s | Tipo: %s | Quantidade: %d (Posicao %d)\n",
                   inv->itens[i].id, 
                   inv->itens[i].nome, 
                   inv->itens[i].tipo, 
                   inv->itens[i].quantidade,
                   i);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Item '%s' nao encontrado na mochila.\n", nomeBusca);
    }
}

// Função Principal (main)

int main() {
    Inventario mochila;
    inicializarInventario(&mochila);
    int opcao;
    
    do {
        exibirMenu();
        if (scanf("%d", &opcao) != 1) {
            printf("\n Entrada invalida. Tente novamente.\n");
            
            while (getchar() != '\n'); 
            opcao = -1;
            continue;
        }
        
        while (getchar() != '\n'); 

        switch (opcao) {
            case 1:
                cadastrarItem(&mochila);
                break;
            case 2:
                listarItens(&mochila);
                break;
            case 3:
                removerItem(&mochila);
                break;
            case 4:
                buscarItem(&mochila);
                break;
            case 0:
                printf("\n Saindo do sistema de inventario. Boa Sorte no Jogo!\n");
                break;
            default:
                printf("\n Opcao invalida. Por favor, escolha uma opcao valida.\n");
        }
    } while (opcao != 0);

    return 0;
}
