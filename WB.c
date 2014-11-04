#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ID.h"


/**
 *  Função responsavel por selecionar o que deve ser passado para a função 
 * de escrita no banco deregistradores
 * 
 * @param mem2Reg variavel de controle
 * @param read_data conteudo para possivel escrita
 * @param aluResult conteudo para possivel escrita
 * @param regC variavel que armazena a posição onde dever ser armazenado
 */
void mux_WB(int mem2Reg, char *read_data, char *aluResult, char *regC) {
    if (mem2Reg == 1) {
        escreverBancoRegistradores(read_data, regC);
    } else if (mem2Reg == 0) {
        escreverBancoRegistradores(aluResult, regC);

    }

}


