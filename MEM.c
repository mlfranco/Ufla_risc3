#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

extern int memRead; //operação de leitura em memoria
extern int memWrite; //operação de escrita em memoria
extern char memoria[65536][32];
extern char bancoRegistradores[32][32]; //banco de registradores
/**
 * Função responsavel pela parte dememoria do ciclo 
 * ela verifica os sinais "memRead" e "memWrite"  e realiza a operaçãonecessaria
 * 
 * @param aluResult valor para ser escrito ou lido damemoria
 * @param memRead variavel de controle
 * @param memWrite variavelde controle
 * @param ReadData variavelde controle
 * @param regC variavel utilizada para se ter o endereço no qual sera escrito namemoria
 */
void carregaRegistradorDaMemoria(char *aluResult, int memRead, int memWrite, char *ReadData, char *regC) {
    if ((memRead == 0) && (memWrite == 1)) {
        int i ;
        char  endereco[32];
        for (i = 0; i < 32; i++) {
            endereco[i] = bancoRegistradores[bin2dec(regC)][i];
        }
        strcpy(memoria[bin2dec(endereco)], aluResult);
    } else if ((memRead == 1) && (memWrite == 0)) {
        strcpy(ReadData, memoria[bin2dec(aluResult)]);
    }
}
