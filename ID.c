#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_MEMORIA 1000 //Tamanho da memorio de instruções 
#define TAM_INSTRUCAO 32

extern int regWrite;
extern char bancoRegistradores[32][32]; //banco de registradores
extern int FLAG_CARREGAR_CONSTANTE;
//FUNÇOES UTILIZADAS NA PARTE DE ID DO CICLO

/**
 * Função responsavel por tartar a "instrução" ,separando  os valores corretamente
 * 
 * @param instrucao string que sera tratada
 * @param opCode codigo que define como astring sera tratada
 * @param regA variavel utilizada para armazenar o edereço do registrador A
 * @param regB variavel utilizada para armazenar o edereço do registrador B
 * @param regC variavel utilizada para armazenar o edereço do registrador C
 */
void separaInstrucao(char *instrucao, char *opCode, char *regA, char *regB, char *regC) {
    int i;
    for (i = 0; i < 8; i++) {
        opCode[i] = instrucao[i];
        regA[i] = instrucao[i + 8];
        regB[i] = instrucao[i + 16];
        regC[i] = instrucao[i + 24];
    }
    opCode[i] = '\0';
    regA[8] = '\0';
    regB[8] = '\0';
    regC[8] = '\0';
}
 /**
  * 
  * Função resposavel por carregar os valores do registradores , ou seja pega o edereço
  * passado, busca se valor nobanco de registradores , e aramazena na variavel correta
  * 
 * @param regA variavel que armazena armazenar o edereço do registrador A
 * @param regB variavel que armazena armazenar o edereço do registrador B
 * @param regC variavel que armazena armazenar o edereço do registrador C
  * @param valorA variavel que armazena armazenar o valor do registrador A
  * @param valorB variavel que armazena armazenar o valor do registrador B ou registrado C dependendo do opCode
  */
void lerBancoRegistradores(char *regA, char *regB, char *regC, char *valorA, char *valorB) {
    int endRegA = bin2dec(regA); //Converte o endereço binario do resgistrador para DECIMAL
    int endRegB = bin2dec(regB);
    int i;
    if (FLAG_CARREGAR_CONSTANTE == 0) {

        if ((endRegA < 32)&&(endRegB < 32)) {
            //verifica se sera usando a constante ou o valor dos registradores 
            for (i = 0; i < 32; i++) {
                valorA[i] = bancoRegistradores[endRegA][i];
                valorB[i] = bancoRegistradores[endRegB][i];
            }
            valorA[32] = '\0';
            valorB[32] = '\0';
        }
    } else {
        strcat(regA, regB);
        strcpy(valorA, regA);
        valorA[160] = '\0';
        // neste caso o conteudo de Valor B, na verdade tem o conteudo valor C! Isto porque o valor de C sero utilizado na ula na função 13 (LCH)
        for (i = 0; i < 32; i++) {
            valorB[i] = bancoRegistradores[bin2dec(regC)][i];
        }
        valorB[32] = '\0';
        FLAG_CARREGAR_CONSTANTE = 0;
    }
}
/**
 * 
 * Função responsavel por armazenar os valores em registradores
 * 
 * @param writeData varial que armazena o conteudo a ser armazenado no banco
 * @param writeRegister variavel armazena o endereço do registrador dedestino
 */
void escreverBancoRegistradores(char *writeData, char *writeRegister) {
    if (regWrite == 1) { //Verifica se é habilitado para escrever
        int endRegDest = bin2dec(writeRegister); //Converte o endereçopara decimal 
        if (endRegDest < 32) { //Verifica se é maior que 32
            int i;
            for (i = 0; i < 32; i++) {
                bancoRegistradores[endRegDest][i] = writeData[i]; // Escreve no banco de registradores
            }
        }
    }
}
