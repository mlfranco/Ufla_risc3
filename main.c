/* 
 * File:   main.c
 * Author: aluno
 *
 * Created on 6 de Fevereiro de 2014, 19:30
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataControl.h"
#include "IF.h"
#include "EX.h"
#include "ID.h"
#include "funcoes.h"

#define TAM_MEMORIA 1000 //Tamanho da memorio de instruções 
#define TAM_INSTRUCAO 32

char memInstrucoes[TAM_MEMORIA][TAM_INSTRUCAO+1]; //Memoria de instruções global

char bancoRegistradores[32][32]; //banco de registradores
int pc; //registrador PC

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
*/
}

void teste() {
    char instrucao[32];
    int fim = 0;
    while (1) {
        printf("Inicio IF:\n");
        fim = buscaInstrucao(instrucao);
        printf("Fim IF:\n");
        if (!fim) {
            printf("Inicio ID:\n");
            printf("Fim ID:\n");
            printf("Inicio EX:\n");
            printf("Fim EX:\n");
            printf("Inicio MEM:\n");
            printf("Fim MEM:\n");
            printf("Inicio WB:\n");
            printf("Fim WB:\n");
        } else {
            printf("Halt alcançado!\n");
            break;
        }
    }

}

int main(int argc, char** argv) {
    carregaMemoria();
    teste();
    return (EXIT_SUCCESS);
}


