#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "dataControl.h"
#include "IF.h"
#define TAM_MEMORIA 1000 //Tamanho da memorio de instruções 
#define TAM_INSTRUCAO 32

extern char memInstrucoes[TAM_MEMORIA][TAM_INSTRUCAO];
extern int pc;
 /**
  * Função responsavel pelo partede IF do ciclo 
  * tem como objetivo carregar a intrução que era isada no ciclo
  * @param instrucao variavel no qualé armazenada intrução
  */
void buscaInstrucao(char *instrucao) { //Instruction Fecth

    int i;
    if (pc <= TAM_MEMORIA) {
        instrucao[0] = memInstrucoes[pc][0];
    }
    while (instrucao[0] == '\0') {
        pc++;
        instrucao[0] = memInstrucoes[pc][0];
    }
    for (i = 0; i < 32; i++) {
        instrucao[i] = memInstrucoes[pc][i];
    }
    printf("Valor atual do PC: %d       Instrução Atual : %s\n", pc, instrucao);
    pc++;

}
