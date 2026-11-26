/*
Heitor de Oliveira Fonseca - CEFET-MG
    01/12/2026 - Trabalho Prático 2

Implementa um sistema de cadastro de animais para um clínica veterinária.
Ele possui as seguintes funcionalidades:
- Inclusão de animal
- Pesquisa de animal
- Listagem de animais
- Alteração de animal
- Exclusão de animal

Estrutura:
main.c - Vetor principal atualizado/realocado conforme as necessidades do programa.
    Além da contagem de animais.
sistema.c - Funções necessárias ao funcionamento do registro.
    Todas as que modificam o tamanho do vetor retornam um novo ponteiro Animal
    e recebem a quantidade atual de animais por referência.
cabecalho.h - Protótipos necessários das funções, declarações de tipos,
    constantes e algumas funções genéricas.
*/

#include "cabecalho.h"

int debug;

void imprimirMenu() {
    printf("REGISTRO CLÍNICA VETERINÁRIA V1.1\n\n");
    printf("1 - Incluir um animal.\n");
    printf("2 - Pesquisar um animal.\n");
    printf("3 - Listar animais.\n");
    printf("4 - Alterar um animal.\n");
    printf("5 - Excluir um animal.\n\n");

    printf("0 - SAIR.\n\n");

    printf("ESCOLHA SUA OPÇÃO: ");
}

int main(int argc, char **argv)
{
    if (argc > 1) if (strcmp(argv[1], "debug") == 0) debug = 1;

    Animal *animaisClinica = NULL;
    int qtdAnimais = 0;
    
    const int TAM_RESP = 10+1;
    int respInt = -1;

    while (respInt != 0) {
        clear();
        
        if (debug) printf("FORA\nanimaisClinica: %p &qtd: %p *qtd: %d\n", animaisClinica, &qtdAnimais, qtdAnimais);
        if (debug) printf("é digito 1: %d  é digito 2: %d   é digito 3: %d\n\n", isDigitCompleto("1234123"), isDigitCompleto("12313."), isDigitCompleto("12313\n"));
        
        // Imprime menu e lida com a resposta.
        char resp[TAM_RESP]; resp[0] = 'a';
        while (!isdigit(resp[0]) || strlen(resp) > 2) {
            imprimirMenu();
            fgets(resp, TAM_RESP, stdin);

            if (!isdigit(resp[0])) {
                printf("\nERRO: NÃO É DÍGITO. Tente novamente.\n");
                sleepU(2); clear();
            }
            else if (strlen(resp) > 2) {
                printf("\nERRO: RESPOSTA ULTRAPASSA LIMITES. Tente novamente.\n");
                sleepU(2); clear();
            }
        }

        clear();

        removerQuebraDeLinha(resp);
        respInt = atoi(resp);

        switch (respInt) {
            // Incluir
            case 1:
                animaisClinica = incluirAnimal(animaisClinica, &qtdAnimais);

                printf("Aperte ENTER para retornar ao menu."); getchar();

                break;

            // Pesquisar
            case 2:
                pesquisarAnimal(animaisClinica, &qtdAnimais);

                printf("Aperte ENTER para retornar ao menu."); getchar();

                break;

            // Listar
            case 3:
                listarAnimais(animaisClinica, &qtdAnimais);

                printf("Aperte ENTER para retornar ao menu."); getchar();

                break;

            // Alterar
            case 4:
                alterarAnimal(animaisClinica, &qtdAnimais);

                printf("Aperte ENTER para retornar ao menu."); getchar();

                break;

            // Excluir
            case 5:
                animaisClinica = excluirAnimal(animaisClinica, &qtdAnimais);

                printf("Aperte ENTER para retornar ao menu."); getchar();

                break;

            // Sair
            case 0:
                break;

            default:
                printf("\nERRO: OPÇÃO INVÁLIDA. Tente novamente.\n\n");
                sleepU(2);
                break;
        }
    }
    
    free(animaisClinica);

    return 0;
}
