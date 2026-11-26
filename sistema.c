#include "cabecalho.h"

// Lê uma espécie e retorna verdadeiro. Retorna falso só se o usuário cancelar.
int incluirEspecie(int *especie) {
    const int TAM_RESP = 10+1;

    char resp[TAM_RESP]; int respInt = -1;
    
    while (!(respInt > 0 && respInt < 4)) {
        resp[0] = 'a';
        while (!isdigit(resp[0])) {
            printf("Digite a espécie\n(1 - Cão, 2 - Gato e 3 - Outro): ");

            fgets(resp, TAM_RESP, stdin);

            if (strcmp(resp, "q\n") == 0 || strcmp(resp, "Q\n") == 0) return 0;

            if (!isdigit(resp[0])) {
                printf("\nERRO: NÃO É UM DÍGITO. Tente novamente.\n\n"); sleepU(2);
            }
        }
        removerQuebraDeLinha(resp);
        respInt = atoi(resp);

        if (respInt > 0 && respInt < 4) *especie = respInt;
        else {
            printf("\nERRO: ESPÉCIE INVÁLIDA. Tente novamente.\n\n"); sleepU(2); clear();
        }
    }

    return 1;
}

// Lê um nome e retorna verdadeiro. Retorna falso só se o usuário cancelar.
int incluirNome(char *nome, char *titulo) {
    char nomeTemp[TAM_NOME] = "";

    while (strlen(nomeTemp)  < 1) {
        printf("Digite o nome %s: ", titulo); fgets(nomeTemp, TAM_NOME, stdin);
        removerQuebraDeLinha(nomeTemp);

        if (strcmp(nomeTemp, "q") == 0 || strcmp(nomeTemp, "Q") == 0) return 0;

        if (strlen(nomeTemp) > 1) strcpy(nome, nomeTemp);
        else {
            printf("\nERRO: NOME INVÁLIDO (VAZIO). Tente novamente.\n\n"); sleepU(2);
        }
    }

    return 1;
}

// Lê uma data de nascimento e retorna verdadeiro. Retorna falso só se o usuário cancelar.
int incluirDataNascimento(Data *dataNascimento) {
    Data dataNascimentoTemp = {0, 0, 0};

    const int TAM_RESP = 20+1;

    char resp[TAM_RESP], subResp[TAM_RESP];
    while (dataNascimentoTemp.dia == 0 || dataNascimentoTemp.mes == 0 || dataNascimentoTemp.ano == 0) {
        printf("Digite a data de nascimento do animal\n(dia/mês/ano): ");
        fgets(resp, TAM_RESP, stdin);

        if (resp[0] == 'q' || resp[0] == 'Q') return 0;

        // Define o dia.
        int i = 0, posSub = 0;
        while (resp[i] != '/' && resp[i] != '\n' && resp[i] != '\0') {
            if (isdigit(resp[i])) {
                subResp[posSub] = resp[i];
                posSub++;
            }
            i++;
        }
        subResp[posSub] = '\0';
        
        if (isDigitCompleto(subResp)) dataNascimentoTemp.dia = atoi(subResp);

        // Define o mês.
        i++; posSub = 0;
        while (resp[i] != '/' && resp[i] != '\n' && resp[i] != '\0') {
            if (isdigit(resp[i])) {
                subResp[posSub] = resp[i];
                posSub++;
            }
            i++;
        }
        subResp[posSub] = '\0';
        
        if (isDigitCompleto(subResp)) dataNascimentoTemp.mes = atoi(subResp);

        // Define o ano.
        i++; posSub = 0;
        while (resp[i] != '/' && resp[i] != '\n' && resp[i] != '\0') {
            if (isdigit(resp[i])) {
                subResp[posSub] = resp[i];
                posSub++;
            }
            i++;
        }
        subResp[posSub] = '\0';
        
        if (isDigitCompleto(subResp)) dataNascimentoTemp.ano = atoi(subResp);

        if (!(dataNascimentoTemp.dia == 0 || dataNascimentoTemp.mes == 0 || dataNascimentoTemp.ano == 0)) {
            dataNascimento->dia = dataNascimentoTemp.dia;
            dataNascimento->mes = dataNascimentoTemp.mes;
            dataNascimento->ano = dataNascimentoTemp.ano;
        }
        else {
            printf("\nERRO: DATA INVÁLIDA (NULA). Tente novamente.\n\n"); sleepU(2);
        }
    }

    return 1;
}

// Lê um peso e retorna verdadeiro. Retorna falso só se o usuário cancelar.
int incluirPeso(float *peso) {
    float pesoTemp = -1.0;

    const int TAM_RESP = 20+1;

    char resp[TAM_RESP], subResp[TAM_RESP];
    while (pesoTemp <= 0) {
        printf("Digite o peso \n(kg): ");
        
        fgets(resp, TAM_RESP, stdin);

        if (resp[0] == 'q' || resp[0] == 'Q') return 0;

        // Define o lado esquerdo do float.
        int i = 0, posSub = 0, multi = 1;
        while (resp[i] != '.' && resp[i] != ',' && resp[i] != '\n' && resp[i] != '\0') {
            if (isdigit(resp[i]) && resp[i] != '-') {
                subResp[posSub] = resp[i];
                posSub++;
            }
            else if (resp[i] == '-') multi *= -1;

            i++;
        }
        subResp[posSub] = '\0';
        
        if (isDigitCompleto(subResp)) pesoTemp = (float) multi * atoi(subResp);

        // Define o lado direito do float.
        i++; posSub = 0;
        while (resp[i] != '.' && resp[i] != ',' && resp[i] != '\n' && resp[i] != '\0') {
            if (isdigit(resp[i])) {
                subResp[posSub] = resp[i];
                posSub++;
            }
            i++;
        }
        subResp[posSub] = '\0';
        
        if (isDigitCompleto(subResp)) pesoTemp += (float) atoi(subResp) / pow(10, strlen(subResp));

        if (pesoTemp > 0) *peso = pesoTemp;
        else {
            printf("\nERRO: PESO INVÁLIDO (NEGATIVO OU NULO). Tente novamente.\n\n"); sleepU(2);
        }
    }

    return 1;
}

// Retorna um código novo que é o código do animal na posição pos + 1;
int incluirCodigo(Animal *animaisClinica, int pos) {
    return animaisClinica[pos].codigo + 1;
}

/*  
    Verifica se já existe um outro animal com a mesma espécie, nome e nome de tutor do animalAtual.
    Retorna a posição da duplicata, caso exista, ou -1 se não.
*/
int existeDuplicata(Animal *animaisClinica, int *qtdAnimais, Animal animalAtual) {
    for (int i = 0; i < *qtdAnimais; i++) {
        if (animaisClinica[i].especie == animalAtual.especie)
            if (strcmp(animaisClinica[i].nomeAnimal, animalAtual.nomeAnimal) == 0)
                if (strcmp(animaisClinica[i].nomeTutor, animalAtual.nomeTutor) == 0)
                    return i;
    }
    return -1;
}

// Encontra a posição do animal no vetor pelo código disponibilizado.
int encontrarPosicaoPorCodigo(Animal *animaisClinica, int *qtdAnimais, int codigo) {
    for (int i = 0; i < *qtdAnimais; i++) {
        if (animaisClinica[i].codigo == codigo) return i;
    }
    return -1;
}

/*
    Inclui um animal no fim do vetor e retorna o novo endereço do vetor (aumentado).
    Caso seja cancelado, retorna o endereço atual do vetor.
*/
Animal *incluirAnimal(Animal *animaisClinica, int *qtdAnimais) {
    if (debug) printf("DENTRO\nAnimaisClinica: %p qtd: %p *qtd: %d\n\n", animaisClinica, qtdAnimais, *qtdAnimais);
    
    Animal cadastroNovo;

    printf("INCLUSÃO DE ANIMAL (INSIRA 'q' PARA CANCELAR)\n\n");

    if (!incluirEspecie(&cadastroNovo.especie)) return animaisClinica;
    if (!incluirNome((char *) &cadastroNovo.nomeAnimal, "do animal")) return animaisClinica;
    if (!incluirDataNascimento(&cadastroNovo.dataNascimento)) return animaisClinica;
    if (!incluirPeso(&cadastroNovo.peso)) return animaisClinica;
    if (!incluirNome((char *) &cadastroNovo.nomeTutor, "do tutor")) return animaisClinica;
    cadastroNovo.codigo = -1;

    int posDuplicata = existeDuplicata(animaisClinica, qtdAnimais, cadastroNovo);
    if (posDuplicata >= 0) {
        clear();
        printf("DUPLICATA ENCONTRADA\n\n");
        printf("CADASTRO NOVO\n");
        imprimirAnimal(cadastroNovo);
        printf("\nCADASTRO ANTERIOR\n");
        imprimirAnimal(animaisClinica[posDuplicata]);

        printf("\nDeseja mesmo efetivar o cadastro? (S/N) ");
        char c = toupper(getc(stdin));
        while (c != 'S' && c != 'N') {
            printf("Deseja mesmo efetivar o cadastro? (S/N) ");
            c = toupper(getc(stdin));
        }
        if (c == 'N') return animaisClinica;
    }

    if (*qtdAnimais == 0)
        cadastroNovo.codigo = 1;
    else
        cadastroNovo.codigo = incluirCodigo(animaisClinica, *qtdAnimais - 1);

    if (animaisClinica == NULL && *qtdAnimais == 0) {
        (*qtdAnimais)++;
        animaisClinica = (Animal *) malloc(sizeof(Animal));
    }
    else {
        (*qtdAnimais)++;
        animaisClinica = (Animal *) realloc(animaisClinica, sizeof(Animal) * *qtdAnimais);
    }

    animaisClinica[*qtdAnimais - 1].codigo = cadastroNovo.codigo;
    animaisClinica[*qtdAnimais - 1].especie = cadastroNovo.especie;
    strcpy(animaisClinica[*qtdAnimais - 1].nomeAnimal, cadastroNovo.nomeAnimal);
    animaisClinica[*qtdAnimais - 1].dataNascimento = cadastroNovo.dataNascimento;
    animaisClinica[*qtdAnimais - 1].peso = cadastroNovo.peso;
    strcpy(animaisClinica[*qtdAnimais - 1].nomeTutor, cadastroNovo.nomeTutor);

    clear();
    printf("CADASTRO REALIZADO\n");
    imprimirAnimal(animaisClinica[*qtdAnimais-1]); printf("\n");

    return animaisClinica;
}

/*
    Exclui um animal do vetor e retorna o novo endereço do vetor (diminuído).
    Caso seja cancelado, retorna o endereço atual do vetor. 
*/
Animal *excluirAnimal(Animal *animaisClinica, int *qtdAnimais) {
    if (debug) printf("DENTRO\nAnimaisClinica: %p qtd: %p *qtd: %d\n\n", animaisClinica, qtdAnimais, *qtdAnimais);
    
    Animal cadastroAExcluir;

    printf("EXCLUSÃO DE ANIMAL (INSIRA 'q' PARA CANCELAR)\n\n");

    if (!incluirNome((char *) &cadastroAExcluir.nomeAnimal, "do animal")) return animaisClinica;
    if (!incluirNome((char *) &cadastroAExcluir.nomeTutor, "do tutor")) return animaisClinica;
    
    clear();
    printf("REGISTROS SEMELHANTES\n\n");

    int qtdParecidos = 0, posExcluir = -1;
    for (int i = 0; i < *qtdAnimais; i++) {
        if (strcmp(animaisClinica[i].nomeAnimal, cadastroAExcluir.nomeAnimal) == 0)
        if (strcmp(animaisClinica[i].nomeTutor, cadastroAExcluir.nomeTutor) == 0) {
            imprimirAnimal(animaisClinica[i]);
            printf("\n");

            qtdParecidos++; posExcluir = i;
        }
    }

    if (qtdParecidos > 1) {
        printf("\nHouve dois ou mais resultados.\n");

        char respCodigo[40+1];
        do {
            printf("Digite o código daquele que deseja excluir (ou q para cancelar): ");
            fgets(respCodigo, 40+1, stdin);

            if (respCodigo[0] == 'q' || respCodigo[0] == 'Q') return animaisClinica;

            if (!isDigitCompleto(respCodigo)) {
                printf("\nERRO: código deve ser numérico. Tente novamente.\n\n");
            }
        } while (!isDigitCompleto(respCodigo));

        cadastroAExcluir.codigo = atoi(respCodigo);

        posExcluir = encontrarPosicaoPorCodigo(animaisClinica, qtdAnimais, cadastroAExcluir.codigo);
    }

    if (posExcluir >= 0) {
        clear();
        printf("O SEGUINTE REGISTRO SERÁ EXCLUIDO\n");
        imprimirAnimal(animaisClinica[posExcluir]);
        printf("\nDeseja mesmo continuar com a exclusão? (S/N) ");
        char c = toupper(getc(stdin));
        while (c != 'S' && c != 'N') {
            printf("Deseja mesmo continuar com a exclusão? (S/N) ");
            c = toupper(getc(stdin));
        }
        if (c == 'N') return animaisClinica;

        // Joga a lista inteira, depois do item a ser excluído, uma posição para trás.
        for (int i = posExcluir; i < *qtdAnimais - 1; i++) {
            animaisClinica[i].codigo = animaisClinica[i + 1].codigo;
            animaisClinica[i].especie = animaisClinica[i + 1].especie;
            strcpy(animaisClinica[i].nomeAnimal, animaisClinica[i + 1].nomeAnimal);
            animaisClinica[i].dataNascimento = animaisClinica[i + 1].dataNascimento;
            animaisClinica[i].peso = animaisClinica[i + 1].peso;
            strcpy(animaisClinica[i].nomeTutor, animaisClinica[i + 1].nomeTutor);
        }

        (*qtdAnimais)--;
        animaisClinica = (Animal *) realloc(animaisClinica, sizeof(Animal) * *qtdAnimais);
        
        clear();
        printf("EXCLUSÃO REALIZADA\n\n");
    }
    else {
        clear();
        printf("NÃO FOI POSSÍVEL EXCLUIR. ITEM NÃO ENCONTRADO.\n\n");
    }

    return animaisClinica;
}


// Encontra as ocorrências de um certo nomeAnimal e nomeTutor no vetor.
void pesquisarAnimal(Animal *animaisClinica, int *qtdAnimais) {
    Animal cadastroAPesquisar;

    printf("PESQUISA DE ANIMAL (INSIRA 'q' PARA CANCELAR)\n\n");

    if (!incluirNome((char *) &cadastroAPesquisar.nomeAnimal, "do animal")) return;
    if (!incluirNome((char *) &cadastroAPesquisar.nomeTutor, "do tutor")) return;
    
    clear();
    printf("REGISTROS SEMELHANTES\n\n");

    int qtdParecidos = 0;
    for (int i = 0; i < *qtdAnimais; i++) {
        if (strcmp(animaisClinica[i].nomeAnimal, cadastroAPesquisar.nomeAnimal) == 0
        && strcmp(animaisClinica[i].nomeTutor, cadastroAPesquisar.nomeTutor) == 0) {
            imprimirAnimal(animaisClinica[i]);
            printf("\n");

            qtdParecidos++;
        }
    }

    if (qtdParecidos == 0) printf("Nenhum registro semelhante encontrado.\n\n");
}

// Modifica os valores de um certo animal selecionado no vetor.
void alterarAnimal(Animal *animaisClinica, int *qtdAnimais) {
    if (debug) printf("DENTRO\nAnimaisClinica: %p qtd: %p *qtd: %d\n\n", animaisClinica, qtdAnimais, *qtdAnimais);
    
    Animal cadastroAAlterar;

    printf("ALTERAÇÃO DE ANIMAL (INSIRA 'q' PARA CANCELAR)\n\n");

    if (!incluirNome((char *) &cadastroAAlterar.nomeAnimal, "do animal")) return;
    if (!incluirNome((char *) &cadastroAAlterar.nomeTutor, "do tutor")) return;
    
    clear();
    printf("REGISTROS SEMELHANTES\n\n");

    int qtdParecidos = 0, posAlterar = -1;
    for (int i = 0; i < *qtdAnimais; i++) {
        if (strcmp(animaisClinica[i].nomeAnimal, cadastroAAlterar.nomeAnimal) == 0)
        if (strcmp(animaisClinica[i].nomeTutor, cadastroAAlterar.nomeTutor) == 0) {
            imprimirAnimal(animaisClinica[i]);
            printf("\n");

            qtdParecidos++; posAlterar = i;
        }
    }

    if (qtdParecidos > 1) {
        printf("\nHouve dois ou mais resultados.\n");

        char respCodigo[40+1];
        do {
            printf("Digite o código daquele que deseja alterar (ou q para cancelar): ");
            fgets(respCodigo, 40+1, stdin);

            if (respCodigo[0] == 'q' || respCodigo[0] == 'Q') return;

            if (!isDigitCompleto(respCodigo)) {
                printf("\nERRO: código deve ser numérico. Tente novamente.\n\n");
            }
        } while (!isDigitCompleto(respCodigo));

        cadastroAAlterar.codigo = atoi(respCodigo);

        posAlterar = encontrarPosicaoPorCodigo(animaisClinica, qtdAnimais, cadastroAAlterar.codigo);
    }

    if (posAlterar >= 0) {
        clear();

        printf("REGISTRO ENCONTRADO\n\n");
        imprimirAnimal(animaisClinica[posAlterar]); printf("\n");
        
        printf("ALTERAÇÕES (INSIRA 'q' PARA MANTER COMO ESTÁ)\n\n");
        printf("ESPÉCIE ATUAL: %d - ", animaisClinica[posAlterar].especie); imprimirEspecie(animaisClinica[posAlterar].especie);
        if (!incluirEspecie(&cadastroAAlterar.especie)) cadastroAAlterar.especie = animaisClinica[posAlterar].especie;

        printf("\nNOME DO ANIMAL ATUAL: %s.\n", animaisClinica[posAlterar].nomeAnimal);
        if (!incluirNome((char *) &cadastroAAlterar.nomeAnimal, "do animal")) strcpy(cadastroAAlterar.nomeAnimal, animaisClinica[posAlterar].nomeAnimal);

        printf("\nDATA DE NASCIMENTO ATUAL: "); imprimirData(animaisClinica[posAlterar].dataNascimento); printf("\n");
        if (!incluirDataNascimento(&cadastroAAlterar.dataNascimento)) cadastroAAlterar.dataNascimento = animaisClinica[posAlterar].dataNascimento;
        
        printf("\nPESO ATUAL: %.2fkg.\n", animaisClinica[posAlterar].peso);
        if (!incluirPeso(&cadastroAAlterar.peso)) cadastroAAlterar.peso = animaisClinica[posAlterar].peso;

        printf("\nNOME DO TUTOR ATUAL: %s.\n", animaisClinica[posAlterar].nomeTutor);
        if (!incluirNome((char *) &cadastroAAlterar.nomeTutor, "do tutor")) strcpy(cadastroAAlterar.nomeTutor, animaisClinica[posAlterar].nomeTutor);

        cadastroAAlterar.codigo = animaisClinica[posAlterar].codigo;

        int posDuplicata = existeDuplicata(animaisClinica, qtdAnimais, cadastroAAlterar);
        
        clear();
        printf("REGISTRO ATUAL\n");
        imprimirAnimal(animaisClinica[posAlterar]);

        printf("\nREGISTRO ALTERADO\n");
        imprimirAnimal(cadastroAAlterar);

        if (posDuplicata >= 0) {
            printf("\nAVISO: EXISTE UMA DUPLICATA COM OS NOVOS DADOS\n\n");
            imprimirAnimal(animaisClinica[posDuplicata]);
        }

        printf("\nDeseja mesmo salvar a alteração? (S/N) ");
        char c = toupper(getc(stdin));
        while (c != 'S' && c != 'N') {
            printf("Deseja mesmo salvar a alteração? (S/N) ");
            c = toupper(getc(stdin));
        }
        if (c == 'N') return;

        animaisClinica[posAlterar].especie = cadastroAAlterar.especie;
        strcpy(animaisClinica[posAlterar].nomeAnimal, cadastroAAlterar.nomeAnimal);
        animaisClinica[posAlterar].dataNascimento = cadastroAAlterar.dataNascimento;
        animaisClinica[posAlterar].peso = cadastroAAlterar.peso;
        strcpy(animaisClinica[posAlterar].nomeTutor, cadastroAAlterar.nomeTutor);

        clear();
        printf("ALTERAÇÃO SALVA NO NOVO REGISTRO\n");
        imprimirAnimal(animaisClinica[posAlterar]); printf("\n");
    }
    else {
        clear();
        printf("NÃO FOI POSSÍVEL ALTERAR. ITEM NÃO ENCONTRADO.\n\n");
    }
}

// Lista todos os animais do vetor.
void listarAnimais(Animal *animaisClinica, int *qtdAnimais) {
    printf("LISTA DE ANIMAIS\n\n");

    if (qtdAnimais == 0) {
        printf("Não há nenhum animal cadastrado.\n\n");
        return;
    }

    for (int i = 0; i < *qtdAnimais; i++) {
        printf("Animal %d/%d\n", i+1, *qtdAnimais);
        imprimirAnimal(animaisClinica[i]);
        printf("\n");
    }
}

void imprimirEspecie(int especie) {
    switch (especie) {
        case 1:
            printf("cão.\n");
            break;
        case 2:
            printf("gato.\n");
            break;
        case 3:
            printf("outro.\n");
            break;
    }
}

void imprimirData(Data data) {
    printf("%02d/%02d/%04d", data.dia, data.mes, data.ano);
}

void imprimirAnimal(Animal animal) {
    if (animal.codigo > 0) printf("Código: %d.\n", animal.codigo);
    else printf("Código: à definir.\n");
    printf("Nome: %s.\n", animal.nomeAnimal);
    printf("Espécie: "); imprimirEspecie(animal.especie);
    printf("Data de nascimento: "); imprimirData(animal.dataNascimento); printf(".\n");
    printf("Peso: %.2fkg.\n", animal.peso);
    printf("Nome do tutor: %s.\n", animal.nomeTutor);
}