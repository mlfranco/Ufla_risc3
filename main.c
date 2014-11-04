#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Unidades de processamento
#include "dataControl.h"
#include "IF.h"
#include "EX.h"
#include "ID.h"
#include "UD.h"
#include "funcoes.h"

//tamanho das coisas
#define TAM_MEMORIA 1000 //Tamanho da memorio de instruções 
#define TAM_INSTRUCAO 32

//Flags criadas 
int FLAG_JAL = 0; //se 1 indica que umdesvio de tipo JAL deve ser tomada
int FLAG_CARREGAR_CONSTANTE = 0; //se 1 indica que o valor passado é umaconstante e nao umemdereço de registrador
int FLAG_JR = 0; //se 1 indica que umdesvio de tipo JR deve ser tomada
int FLAG_DESVIO = 0; //usado no beq e bne 


//Banco de registradores e memoria
int pc = 0; //registrador PC
char bancoRegistradores[32][32]; //banco de registradores
char memInstrucoes[TAM_MEMORIA][TAM_INSTRUCAO + 1]; //Memoria de instruções global
char memoria [65536][32]; //memoria quer dizer memoria ou seja...é a memoria fodasticamente grande....pois é .. eu falei muito fodasticamente grande?

//DATA_CONTROL
int jump; //operação de jump
int branch; //operação de desvio
int memRead; //operação de leitura em memoria
int memWrite; //operação de escrita em memoria
int mem2Reg; //operação de memoria para registrador
int aluSrc; //alu Source
int regWrite; //escrita em registradores
int regDestino; //registrador de destino
int aluOp; // operacao da alu

void simulador() {
    char regA[9];
    char regB[9];
    char regC[9];
    char opCode[9];
    char valorA[33];
    char valorB[33];
    char aluResult[32];
    char ReadData[32];
    int fim = 0;
    char instrucao[33];
    int i, j;

    /*
     * PARTE DO CODIGO UTILIZADA PARA TESTE!
    for (i = 0; i < 32; i++) {
        for (j = 0; j < 32; j++) {
            bancoRegistradores[i][j] = '1';
            if (j == 0) {
                bancoRegistradores[i][j] = '1';
            }
        }
    }
    
    for (j = 0; j < 32; j++) {
        bancoRegistradores[29][j] = '0';
        bancoRegistradores[i][j] = '1';
    }

    bancoRegistradores[29][31] = '1';
     */
    do {
        printf("===========================================================================\n");
        printf("==============================Inicio do cilco==============================\n");
        printf("===========================================================================\n");
        buscaInstrucao(instrucao);
        if (instrucao[0] != '1') {
            //IF
            separaInstrucao(instrucao, opCode, regA, regB, regC);
            dataControl(opCode);

            if (FLAG_JAL == 1) {
                unidadeDesvio(regA, regB, regC);
            } else {
                //ID
                lerBancoRegistradores(regA, regB, regC, valorA, valorB);
                printf("\nOpCode : %s     RegA : %s     RegB : %s     RegC : %s", opCode, regA, regB, regC);
                printf("\nValorA : %s   ValorB : %s \n", valorA, valorB);
                //EXE
                ALU(valorA, valorB, aluOp, opCode, aluResult);

                if (FLAG_DESVIO == 1) {
                    pc = (bin2dec(regC));
                    FLAG_DESVIO = 0;
                }
                //MEM
                carregaRegistradorDaMemoria(aluResult, memRead, memWrite, ReadData, regC);
                //WB
                mux_WB(mem2Reg, ReadData, aluResult, regC);
            }
        } else {

            printf("Halt alcançado!\n");
            fim = 1;
        }
        ImprimirBancoDeRegistradores();
    } while (fim == 0);

}

int main(int argc, char** argv) {
    /**
     * Função que carrega as informaçoes do arquivos
     * @param argc
     * @param argv
     * @return 
     */
    carregaMemoria();
    /**
     * Função que inializa o simulador
     * @param argc
     * @param argv
     * @return 
     */
    simulador();
    return (EXIT_SUCCESS);
}








/*
void teste_real() {
    char regA[9];
    char regB[9];
    char regC[9];
    char opCode[9];
    char valorA[33];
    char valorB[33];
    char aluResult[32];
    char ReadData[32];
    char instrucao[32];
    int FLAG_BEQ;
    int j, i;

    for (i = 0; i < 32; i++) {
        for (j = 0; j < 32; j++) {
            bancoRegistradores[i][j] = '1';
            if (j == 0) {
                bancoRegistradores[i][j] = '1';
            }
        }
    }




    strcpy(memInstrucoes[0], "00000001000000110000100100000001");



    //TESTE ADD E SUB
    buscaInstrucao(instrucao);
    puts(instrucao);
    separaInstrucao(instrucao, opCode, regA, regB, regC);
    printf("OpCode :");
    puts(opCode);
    printf("RegA :");
    puts(regA);
    printf("RegB :");
    puts(regB);
    printf("RegC :");
    puts(regC);
    Imprimir();
    lerBancoRegistradores(regA, regB, valorA, valorB);
    printf("ValorA :");
    puts(valorA);
    printf("ValorB :");
    puts(valorB);
    dataControl(opCode);


    ALU(valorA, valorB, aluOp, opCode, aluResult, &FLAG_BEQ);
    //memoria!!!!!

    mux_WB(mem2Reg, ReadData, aluResult, regC);

    //ImprimirBancoDeRegistradores();
    /*
        //TESTE ZERA

        strcpy(memInstrucoes[1], "00000011000000110000100100000001");

        buscaInstrucao(instrucao);
        puts(instrucao);
        separaInstrucao(instrucao, opCode, regA, regB, regC);
        printf("OpCode :");
        puts(opCode);
        printf("RegA :");
        puts(regA);
        printf("RegB :");
        puts(regB);
        printf("RegC :");
        puts(regC);
        Imprimir();
        lerBancoRegistradores(regA, regB, valorA, valorB);
        printf("ValorA :");
        puts(valorA);
        printf("ValorB :");
        puts(valorB);
        dataControl(opCode);

        ALU(valorA, valorB, aluOp, opCode, aluResult, &FLAG_BEQ);

        //memoria!!!!!

        mux_WB(mem2Reg, ReadData, aluResult, regC);

        //ImprimirBancoDeRegistradores();



        //==============================================================================LOAD
        strcpy(memInstrucoes[1], "000011110000000100000100100000011");

        for (i = 0; i < 32; i++) {
            bancoRegistradores[2][i] = '0';
        }
        // escrevendo endereço 10 no registrador 2 para teste
        bancoRegistradores[2][31] = '1';
        bancoRegistradores[2][29] = '1';

        //colocando valor de teste na memoria
        for (i = 0; i < 16; i++) {
            memoria [10][i] = '1';
        }


        buscaInstrucao(instrucao);
        puts(instrucao);
        separaInstrucao(instrucao, opCode, regA, regB, regC);
        printf("OpCode :");
        puts(opCode);
        printf("RegA :");
        puts(regA);
        printf("RegB :");
        puts(regB);
        printf("RegC :");
        puts(regC);
        Imprimir();
        lerBancoRegistradores(regA, regB, valorA, valorB);
        printf("ValorA :");
        puts(valorA);
        printf("ValorB :");
        puts(valorB);
        dataControl(opCode);

        ALU(valorA, valorB, aluOp, opCode, aluResult, &FLAG_BEQ);
        if (FLAG_BEQ == 1) {

        }
        //memoria!!!!!

        mux_WB(mem2Reg, ReadData, aluResult, regC);

        //ImprimirBancoDeRegistradores();

        printf("\n\n\n\n Testefubçoes logicas : \n");

        printf("XOR  : ");
        ALU("11111111111111111111111111111111", "11111111111111111111111111111111", aluOp, "00000100", aluResult, &FLAG_BEQ);
        mux_WB(0, ReadData, aluResult, "00000100");

        printf("OR   : ");
        ALU("11111111111111111111111111111111", "11111111111111111111111111111111", aluOp, "00000101", aluResult, &FLAG_BEQ);
        mux_WB(0, ReadData, aluResult, "00000101");

        printf("NOT  : ");
        ALU("11111111111111111111111111111111", "11111111111111111111111111111111", aluOp, "00000110", aluResult, &FLAG_BEQ);
        mux_WB(0, ReadData, aluResult, "00000110");

        printf("AND  : ");
        ALU("11111111111111111111111111111111", "11111111111111111111111111111111", aluOp, "00000111", aluResult, &FLAG_BEQ);
        mux_WB(0, ReadData, aluResult, "00000111");

        printf("ASL  : ");
        ALU("11111111111111111111111111111111", "00000000000000000000000000000011", aluOp, "00001000", aluResult, &FLAG_BEQ);
        mux_WB(0, ReadData, aluResult, "00001000");

        printf("ASR  : ");
        ALU("11111111111111111111111111111111", "00000000000000000000000000000011", aluOp, "00001001", aluResult, &FLAG_BEQ);
        mux_WB(0, ReadData, aluResult, "00001001");

        printf("LSL  : ");
        ALU("11111111111111111111111111111111", "00000000000000000000000000000011", aluOp, "00001010", aluResult, &FLAG_BEQ);
        mux_WB(0, ReadData, aluResult, "00001010");

        printf("LSR  : ");
        ALU("11111111111111111111111111111111", "00000000000000000000000000000011", aluOp, "00001011", aluResult, &FLAG_BEQ);
        mux_WB(0, ReadData, aluResult, "00001011");

        printf("COPY  : ");
        ALU("11111111111111111111111111111111", "00000000000000000000000000000011", aluOp, "00001011", aluResult, &FLAG_BEQ);
        mux_WB(0, ReadData, aluResult, "00001011");

        printf("LCH  : ");
        ALU("11111111111111111111111111111111", "00000000000000000000000000000011", aluOp, "00001011", aluResult, &FLAG_BEQ);
        mux_WB(0, ReadData, aluResult, "00001101");
    
        printf("LCL  : ");
      //  ALU("11111111111111111111111111111111", "00000000000000000000000000000011", aluOp, "00001011", aluResult, &FLAG_BEQ);
      //  mux_WB(0, ReadData, aluResult, "00001110");
        ImprimirBancoDeRegistradores();
     
}
 */