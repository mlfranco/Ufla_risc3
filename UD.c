#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"


extern char bancoRegistradores[32][32];
extern int pc;
extern int branch;
extern int jump;
extern int FLAG_JAL;
extern int FLAG_JR;

void unidadeDesvio(char *regA, char *regB, char *regC) {
    
    //verifica qual tipo de JUMP (JR /NORMAL /JAL)
    
    if (FLAG_JR == 1) {
        /*
         * FLAG_JR == 1 incica que o tipo dejumpé JR 
         *  logo o valor armazenado no bancoRegistradores[31] é convertido para inteiro e
         *  PC recebe estevalor
         */
       pc =  bin2dec(bancoRegistradores[31]);
       FLAG_JR = 0;
    } else {
        /*
         * FLAG_JR == 0 incica que o tipo éJAL
         *  logo o valor  de PC deve ser armazenado no bancoRegistradores[31]
         *  e o desvio deve ser tomado normalmente
         */
        int endereco = 0;
        strcat(regA, regB);
        strcat(regA, regC);
        endereco = bin2dec(regA);
        
        if (jump == 0) {
            int i;
            char enderecoPC[33];
            char endereco31[32];
            int aux;
            aux = pc - 1;
            dec2bin(aux, enderecoPC);
            
            strcpy(bancoRegistradores[31], enderecoPC); // salva nobanco possicao31
            for (i=0 ;i<31 ;i++){
                bancoRegistradores[31][i+1]= bancoRegistradores[31][i];
            }
            bancoRegistradores[31][0]= '0';
        }

        /*
         * neste ponto é feito o JUMP em si, com os 3 tipos de jump executam
         * esta parte ,ele fica fora de todas as condiçoes
         * 
         * vale resaltar que o JUMP "normal" é realizado nesta parte
         * OBS.: FLAG de JAL é setada para 0
         */
        FLAG_JAL = 0;
        pc = endereco;
    }
}