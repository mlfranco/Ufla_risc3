#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "dataControl.h"
#include "IF.h"
#define TAM_MEMORIA 1000 //Tamanho da memorio de instruções 
#define TAM_INSTRUCAO 32

extern char memInstrucoes[TAM_MEMORIA][TAM_INSTRUCAO + 1];
extern int pc;

int buscaInstrucao(char *instrucao) { //Instruction Fecth

    int i;
    if (pc <= TAM_MEMORIA) {
        for (i = 0; i < 32; i++) {
            instrucao[i] = memInstrucoes[pc][i];
        }
    }
    while (instrucao[0] == ' ') {
        pc++;
        for (i = 0; i < 32; i++) {
            instrucao[i] = memInstrucoes[pc][i];
        }
    }
    printf("PC: %d, Instrução: %s\n", pc, instrucao);
    pc++;
    if (!strncmp(instrucao, "11111111111111111111111111111111", 32)) {
        return 1;
    }
    return 0;
}
