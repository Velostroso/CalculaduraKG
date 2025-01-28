#include <stdio.h>
#include <locale.h>

//Estrutura para representar um estoque.
typedef struct {
    int codigo;                  //C�digo do produto.
    char nome[30];               //Nome do produto.
    float quantidade_em_estoque; //Quantidade dispon�vel em Kg.
} Produto;

//Fun��o que simula o fornecimento do peso de uma balan�a.
float obter_peso() {
    float peso;
    printf("Peso lido da balan�a (kg) ou digite 0 para cancelar: ");
    scanf("%f", &peso);
    return peso;
}

//Fun��o que busca um produto no estoque pelo c�digo.
int buscar_produto_por_codigo(Produto estoque[], int tamanho_estoque, int codigo_produto) {
    for (int i = 0; i < tamanho_estoque; i++) {
        if (estoque[i].codigo == codigo_produto) {
            return i;  //Retorna o �ndice do produto encontrado.
        }
    }
    return -1;  //Produto n�o encontrado.
}

//Fun��o que serve para vender e atualizar o produto vendido no estoque.
void vender_produto(Produto estoque[], int tamanho_estoque) {
    int codigo_produto, indice_produto;
    float preco_por_kg, peso, valor_total;

    //Solicita o c�digo do produto.
    printf("Digite o c�digo do produto: ");
    scanf("%d", &codigo_produto);

    //Busca o produto no estoque pelo c�digo.
    indice_produto = buscar_produto_por_codigo(estoque, tamanho_estoque, codigo_produto);

    if (indice_produto == -1) {
        printf("Produto n�o encontrado no estoque.\n");
        return;  //Sai da fun��o se o produto n�o for encontrado.
    }

    //Obter o peso do produto.
    peso = obter_peso();

    if (peso == 0) {
        printf("Opera��o cancelada. Retornando ao menu principal...\n");
        return;
    }

    //Verifica se h� quantidade suficiente no estoque.
    if (peso > estoque[indice_produto].quantidade_em_estoque) {
        printf("Quantidade insuficiente no estoque.\n");
        return;
    }

    //Solicita o pre�o por quilo do produto.
    printf("Digite o pre�o por quilo (R$): ");
    scanf("%f", &preco_por_kg);

    if (preco_por_kg == 0) {
        printf("Opera��o cancelada. Retornando ao menu principal...\n");
        return;
    }

    //Calcula o valor total do produto.
    valor_total = peso * preco_por_kg;

    //Atualiza o produto no estoque.
    estoque[indice_produto].quantidade_em_estoque -= peso;

    //Exibi o valor da compra e a quantidade restante em estoque.
    printf("O valor total �: R$ %.2f\n", valor_total);
    printf("Quantidade restante de %s no estoque: %.2f kg\n", estoque[indice_produto].nome, estoque[indice_produto].quantidade_em_estoque);
}

//Fun��o para visualizar o estoque com nome, c�digo e quantidade
void visualizar_estoque(Produto estoque[], int tamanho_estoque){
    printf("\n----ESTOQUE----\n");
    for (int i = 0; i < tamanho_estoque; i++){
        printf("PRODUTO: %s | C�DIGO: %d | QUANTIDADE: %.2f Kg\n",
               estoque[i].nome, estoque[i].codigo, estoque[i].quantidade_em_estoque);
    }
    printf("-------------------\n");
}

int main() {
    setlocale(LC_ALL, "portuguese");
    //Foi definido um estoque inicial com 5 produtos.
    Produto estoque[5] = {
        {0001, "MA�A", 50.0},
        {0002, "BANANA", 50.0},
        {0003, "LARANJA", 50.0},
        {0004, "CEBOLA", 50.0},
        {0005, "TOMATE", 50.0}
    };
    int opcao = 0;

    //Menu principal.
    while (opcao != 3) {
        printf("\nMenu de Opera��es:\n");
        printf("1 - Vender\n");
        printf("2 - Estoque\n");
        printf("3 - Sair\n");
        printf("Escolha uma op��o.");
        scanf("%d", &opcao);

        if (opcao == 1) {
            vender_produto(estoque, 5); //Para realizar a venda do produto.
        } else if (opcao == 2) {
            visualizar_estoque(estoque, 5);//Para visualizar o estoque.
        } else if (opcao == 3) {
            printf("Saindo do programa...\n");//Para sair do programa.
        }
    }

}
