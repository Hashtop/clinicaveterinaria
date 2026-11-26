#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#ifdef __linux__
    #include <unistd.h>
    static void sleepU(int seg) {
        sleep(seg);
    }
    static void clear() {
        system("clear");
    }
#elif _WIN32
    #include <windows.h>
    static void sleepU(int seg) {
        Sleep(seg*1000);
    }
    static void clear() {
        system("cls");
    }
#endif

#define TAM_NOME 100 + 1

extern int debug;

typedef struct data {
    int dia, mes, ano;
} Data;

typedef struct animal {
    int codigo, especie;
    char nomeAnimal[TAM_NOME], nomeTutor[TAM_NOME];
    Data dataNascimento;
    float peso;
} Animal;

Animal *incluirAnimal(Animal *animaisClinica, int *qtdAnimais);
    int incluirEspecie(int *especie);
    int incluirNome(char *nome, char *titulo);
    int incluirDataNascimento(Data *dataNascimento);
    int incluirPeso(float *peso);
    int incluirCodigo(Animal *animaisClinica, int pos);
    int existeDuplicata(Animal *animaisClinica, int *qtdAnimais, Animal animalAtual);
Animal *excluirAnimal(Animal *animaisClinica, int *qtdAnimais);
    int encontrarPosicaoPorCodigo(Animal *animaisClinica, int *qtdAnimais, int codigo);
void pesquisarAnimal(Animal *animaisClinica, int *qtdAnimais);
void alterarAnimal(Animal *animaisClinica, int *qtdAnimais);
void listarAnimais(Animal *animaisClinica, int *qtdAnimais);

void imprimirAnimal(Animal animal);
    void imprimirEspecie(int especie);
    void imprimirData(Data data);

static void removerQuebraDeLinha(char *texto) {
    if (texto[strlen(texto) - 1] == '\n') texto[strlen(texto) - 1] = '\0';
    else if (texto[strlen(texto) - 2] == '\n') texto[strlen(texto) - 2] = '\0';
}

static int isDigitCompleto(char *texto) {
    for (int i = 0; i < strlen(texto); i++) {
        if (!isdigit(texto[i]) && texto[i] != '\n') return 0;
    }
    return 1;
}