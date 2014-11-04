#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"
#define TAM_MEMORIA 1000
#define TAM_INSTRUCAO 32
#define TAMANHO_DA_LINHA 33
#define TAMANHO_DA_MEMORIA 65536


extern int jump; //operação de jump
extern int branch; //operação de desvio
extern int memRead; //operação de leitura em memoria
extern int memWrite; //operação de escrita em memoria
extern int mem2Reg; //operação de memoria para registrador
extern int aluSrc; //alu Source
extern int regWrite; //escrita em registradores
extern int regDestino; //registrador de destino
extern int aluOp; // operacao da alu
extern char bancoRegistradores[32][32];
extern char memoria [65536][32];
extern char memInstrucoes[TAM_MEMORIA][TAM_INSTRUCAO];
/**
 * Função que zera a memoria principal
 * obs.:usada em alguns testes
 */
void zeraMemoriaprincipal() {
    int i, k;
    for (i = 0; i < 65536; i++) {
        for (k = 0; k < 32; k++) {
            memoria [i][k] = '0';
        }

    }
}
/**
 * Função que zera a Banco degistradores com 1 em todas as posiçoes
 * obs.:usada em alguns testes
 */
void iniciaBancoReg() {
    int i, k;
    for (i = 0; i < 32; i++) {
        for (k = 0; k < 32; k++) {
            bancoRegistradores [i][k] = '1';
        }

    }
}
/**
 * Função converte um numero binario (que esta em umastring) para um decimal ( tipo int)
 * 
 * @param valor string que contem o numero em binario
 * @return inteiro em cedimal
 */
int bin2dec(char* valor) {
    int pos = 0;
    int dec = 0;
    while (valor[pos] != '\0') {
        if (valor[pos] == '1') dec = dec * 2 + 1;
        else if (valor[pos] == '0') dec *= 2;
        pos++;
    }
    return dec;
}
/**
 * Função converte um numero decimal (int) para um binario ( string)
 * @param value valor que sera convertido
 * @param output resultado da converção
 */
void dec2bin(int value, char* output){
    int i;
   // output[32] = '\0';
    for (i = 30; i >= 0; --i, value >>= 1)
    {
        output[i] = (value & 1) + '0';
    }
}
/**
 * Função que imprime o banco de registradores
 * 
 */
void ImprimirBancoDeRegistradores() {
    int i, j;
    printf("Banco de Registradores :\n");
    for (i = 0; i < 32; i++) {
        printf("linha %d :", i);
        for (j = 0; j < 32; j++) {
            printf("%c", bancoRegistradores[i][j]);
        }
        printf("\n");
    }
}
/**
 * Função que imprime o toda a memoria
 * 
 */
void imprimeMemoria() {
    int i, j;
    for (i = 0; i < TAM_MEMORIA; i++) {
        printf("Linha %d - ", i);
        for (j = 0; j < 32; j++) {
            printf("%c", memInstrucoes[i][j]);
        }
        printf("\n");
    }
}
/**
 * função que carrega(de um arquivo com nome "entrada.bin" as instruçoes que seram utilizadas no simulador 
 * e o coloca n memori de instruçoes
 */
void carregaMemoria() {
    int i = 0;
    int j = 0;
    char linhaArquivo[TAM_INSTRUCAO + 1];
    FILE *arquivo;
    arquivo = fopen("entrada.bin", "r");
    while (fgets(linhaArquivo, 33, arquivo) != NULL) {
        if (linhaArquivo[0] == 'a') {
            char endereco[17];
            for (j = 8; j < 24; j++) {
                endereco[j - 8] = linhaArquivo[j];
            }
            endereco[16] = '\0';
            i = bin2dec(endereco);
        } else if (linhaArquivo[0] == '\n') {
            memInstrucoes[i][0] = ' ';
        } else {
            for (j = 0; j < 32; j++) {
                memInstrucoes[i][j] = linhaArquivo[j];
            }
            memInstrucoes[i][33] = '\0';
            i++;
        }
    }

}



