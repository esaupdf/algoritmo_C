#include <stdio.h>
#include <string.h>
#include <locale.h>

#define MAX_TENIS 100

typedef struct {
    char nome[50];
    char cor[30];
    int tamanho;
    float preco;
} Tenis;

Tenis loja[MAX_TENIS];
int total_tenis = 0;

void aguardar() {
    printf("Pressione Enter para continuar...");
    while(getchar() != '\n');
    getchar();
}

void cadastrar() {
    if (total_tenis >= MAX_TENIS) {
        printf("Limite de tenis atingido!\n");
        aguardar();
        return;
    }

    printf("Nome do tenis: ");
    getchar();
    fgets(loja[total_tenis].nome, 50, stdin);
    loja[total_tenis].nome[strcspn(loja[total_tenis].nome, "\n")] = 0;

    printf("Cor do tenis: ");
    fgets(loja[total_tenis].cor, 30, stdin);
    loja[total_tenis].cor[strcspn(loja[total_tenis].cor, "\n")] = 0;

    printf("Tamanho do tenis (numero): ");
    scanf("%d", &loja[total_tenis].tamanho);

    printf("Preco do tenis: R$ ");
    scanf("%f", &loja[total_tenis].preco);

    total_tenis++;
    printf("Tenis cadastrado!\n");
    aguardar();
}

void listar() {
    if (total_tenis == 0) {
        printf("Nenhum tenis cadastrado.\n");
        aguardar();
        return;
    }

    for (int i = 0; i < total_tenis; i++) {
        printf("%d. %s - Cor: %s - Tamanho: %d - R$ %.2f\n",
               i + 1, loja[i].nome, loja[i].cor, loja[i].tamanho, loja[i].preco);
    }
    aguardar();
}

void buscar() {
    char nome[50];
    printf("Nome do tenis: ");
    getchar();
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = 0;

    for (int i = 0; i < total_tenis; i++) {
        if (strcmp(loja[i].nome, nome) == 0) {
            printf("Encontrado: %s - Cor: %s - Tamanho: %d - R$ %.2f\n",
                   loja[i].nome, loja[i].cor, loja[i].tamanho, loja[i].preco);
            aguardar();
            return;
        }
    }

    printf("Tenis nao encontrado.\n");
    aguardar();
}

void alterar() {
    char nome[50];
    printf("Nome do tenis: ");
    getchar();
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = 0;

    for (int i = 0; i < total_tenis; i++) {
        if (strcmp(loja[i].nome, nome) == 0) {
            printf("Novo preco: R$ ");
            scanf("%f", &loja[i].preco);

            printf("Nova cor: ");
            getchar();
            fgets(loja[i].cor, 30, stdin);
            loja[i].cor[strcspn(loja[i].cor, "\n")] = 0;

            printf("Novo tamanho: ");
            scanf("%d", &loja[i].tamanho);

            printf("Dados alterados!\n");
            aguardar();
            return;
        }
    }

    printf("Tenis nao encontrado.\n");
    aguardar();
}

void remover() {
    char nome[50];
    printf("Nome do tenis: ");
    getchar();
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = 0;

    for (int i = 0; i < total_tenis; i++) {
        if (strcmp(loja[i].nome, nome) == 0) {
            for (int j = i; j < total_tenis - 1; j++) {
                loja[j] = loja[j + 1];
            }
            total_tenis--;
            printf("Tenis removido!\n");
            aguardar();
            return;
        }
    }

    printf("Tenis nao encontrado.\n");
    aguardar();
}

void aplicar_desconto(float total) {
    float desconto = 0.0f;

    if (total >= 600.0f) {
        desconto = total * 0.15f;
        printf("Desconto progressivo de 15%% aplicado!\n");
    } else if (total >= 300.0f) {
        desconto = total * 0.10f;
        printf("Desconto progressivo de 10%% aplicado!\n");
    } else if (total >= 200.0f) {
        desconto = total * 0.05f;
        printf("Desconto progressivo de 5%% aplicado!\n");
    } else {
        printf("Nenhum desconto aplicado. Gaste mais para obter desconto.\n");
    }

    printf("Total: R$ %.2f\nDesconto: R$ %.2f\nTotal apos desconto: R$ %.2f\n",
           total, desconto, total - desconto);
    aguardar();
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    strcpy(loja[0].nome, "Nike");
    strcpy(loja[0].cor, "Preto");
    loja[0].tamanho = 42;
    loja[0].preco = 500.0f;
    total_tenis = 1;

    char usuario[50];
    char tipo[15];

    printf("Ola! Seja bem-vindo a Loja de Tenis.\n");
    printf("Por favor, informe seu nome: ");
    fgets(usuario, 50, stdin);
    usuario[strcspn(usuario, "\n")] = 0;

    do {
        printf("Voce e 'vendedor' ou 'comprador'? ");
        fgets(tipo, 15, stdin);
        tipo[strcspn(tipo, "\n")] = 0;

        for (int i = 0; tipo[i]; i++) {
            if (tipo[i] >= 'A' && tipo[i] <= 'Z') {
                tipo[i] = tipo[i] + ('a' - 'A');
            }
        }

        if (strcmp(tipo, "vendedor") != 0 && strcmp(tipo, "comprador") != 0) {
            printf("Tipo invalido. Tente novamente.\n");
        }
    } while (strcmp(tipo, "vendedor") != 0 && strcmp(tipo, "comprador") != 0);

    printf("\nOla %s, voce esta logado como %s.\n", usuario, tipo);

    int opcao;
    float total_gasto = 0.0f;

    do {
        printf("\n=== Menu Loja de Tenis ===\n");

        if (strcmp(tipo, "vendedor") == 0) {
            printf("1. Cadastrar tenis\n");
            printf("2. Listar tenis\n");
            printf("3. Buscar tenis\n");
            printf("4. Alterar tenis\n");
            printf("5. Remover tenis\n");
            printf("6. Aplicar desconto\n");
            printf("7. Trocar para comprador\n"); 
            printf("8. Sair\n");
        } else {
            printf("1. Listar tenis\n");
            printf("2. Buscar tenis\n");
            printf("3. Trocar para vendedor\n"); 
            printf("4. Sair\n");
        }

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (strcmp(tipo, "vendedor") == 0) {
            switch (opcao) {
                case 1: cadastrar(); break;
                case 2: listar(); break;
                case 3: buscar(); break;
                case 4: alterar(); break;
                case 5: remover(); break;
                case 6:
                    printf("Digite o total gasto: R$ ");
                    scanf("%f", &total_gasto);
                    aplicar_desconto(total_gasto);
                    break;
                case 7:
                    strcpy(tipo, "comprador");  
                    printf("Trocando para comprador...\n");
                    aguardar();
                    opcao = 0; 
                    break;
                case 8:
                    printf("Encerrando o programa...\n");
                    break;
                default:
                    printf("Opcao invalida!\n");
                    aguardar();
            }
        } else {  
            switch (opcao) {
                case 1: listar(); break;
                case 2: buscar(); break;
                case 3:
                    strcpy(tipo, "vendedor");  
                    printf("Trocando para vendedor...\n");
                    aguardar();
                    opcao = 0; 
                    break;
                case 4:
                    printf("Encerrando o programa...\n");
                    break;
                default:
                    printf("Opcao invalida!\n");
                    aguardar();
            }
        }

    } while ((strcmp(tipo, "vendedor") == 0 && opcao != 8) ||
             (strcmp(tipo, "comprador") == 0 && opcao != 4));

    return 0;
}
