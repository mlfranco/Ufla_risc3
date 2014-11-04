#include <stdio.h>
#include <stdlib.h>
//Variaveis Globals:
//Variaveis Criadas
extern int FLAG_CARREGAR_CONSTANTE;
extern int FLAG_JAL;
extern int FLAG_BEQ;
extern int FLAG_JR;

//sinais de controle;
extern int jump; //operação de jump
extern int branch; //operação de desvio
extern int memRead; //operação de leitura em memoria
extern int memWrite; //operação de escrita em memoria
extern int mem2Reg; //operação de memoria para registrador
extern int aluSrc; //alu Source
extern int regWrite; //escrita em registradores
extern int regDestino; //registrador de destino
extern int aluOp; // operacao da alu




//Funções e Procedimentos:

void dataControl(char *opcode) {
    //1 add
    if (strcmp(opcode, "00000001") == 0) {//adicionar
        jump = 0;
        branch = 0;
        memRead = 0;
        memWrite = 0;
        mem2Reg = 0;
        aluSrc = 0;
        regWrite = 1;
        regDestino = 1;
        aluOp = 10;
        aluOp = 10;


    }//2 sub
    else if (strcmp(opcode, "00000010") == 0) {//sub
        jump = 0;
        branch = 0;
        memRead = 0;
        memWrite = 0;
        mem2Reg = 0;
        aluSrc = 1;
        regWrite = 1;
        regDestino = 0;
        aluOp = 10;
    }//3 zera
    else if (strcmp(opcode, "00000011") == 0) {//Zero
        jump = 0;
        branch = 0;
        memRead = 0;
        memWrite = 0;
        mem2Reg = 0;
        aluSrc = 0;
        regWrite = 1;
        regDestino = 0;
        aluOp = 10;
    }//4 xor
    else if (strcmp(opcode, "00000100") == 0) {//Xor
        jump = 0;
        branch = 0;
        memRead = 0;
        memWrite = 0;
        mem2Reg = 0;
        aluSrc = 1;
        regWrite = 1;
        regDestino = 0;
        aluOp = 10;
    }//5 or
    else if (strcmp(opcode, "00000101") == 0) {//or
        jump = 0;
        branch = 0;
        memRead = 0;
        memWrite = 0;
        mem2Reg = 0;
        aluSrc = 1;
        regWrite = 1;
        regDestino = 0;
        aluOp = 10;
    }//6 not
    else if (strcmp(opcode, "00000110") == 0) {//not
        jump = 0;
        branch = 0;
        memRead = 0;
        memWrite = 0;
        mem2Reg = 0;
        aluSrc = 1;
        regWrite = 1;
        regDestino = 0;
        aluOp = 10;
    }//7 and
    else if (strcmp(opcode, "00000111") == 0) {//and
        jump = 0;
        branch = 0;
        memRead = 0;
        memWrite = 0;
        mem2Reg = 0;
        aluSrc = 1;
        regWrite = 1;
        regDestino = 0;
        aluOp = 10;
    }//8 asl
    else if (strcmp(opcode, "00001000") == 0) {//shift arit esquerda
        jump = 0;
        branch = 0;
        memRead = 0;
        memWrite = 0;
        mem2Reg = 0;
        aluSrc = 1;
        regWrite = 1;
        regDestino = 0;
        aluOp = 10;
    }//9 asr
    else if (strcmp(opcode, "00001001") == 0) {//shift arit direita
        jump = 0;
        branch = 0;
        memRead = 0;
        memWrite = 0;
        mem2Reg = 0;
        aluSrc = 1;
        regWrite = 1;
        regDestino = 0;
        aluOp = 10;
    }//10 lsl
    else if (strcmp(opcode, "0001010") == 0) {//shift log esquerda
        jump = 0;
        branch = 0;
        memRead = 0;
        memWrite = 0;
        mem2Reg = 0;
        aluSrc = 1;
        regWrite = 1;
        regDestino = 0;
        aluOp = 10;
    }//11 lsr
    else if (strcmp(opcode, "0001011") == 0) {//shift log direita
        jump = 0;
        branch = 0;
        memRead = 0;
        memWrite = 0;
        mem2Reg = 0;
        aluSrc = 1;
        regWrite = 1;
        regDestino = 0;
        aluOp = 10;
    }//12 passa
    else if (strcmp(opcode, "00001100") == 0) {//copia
        jump = 0;
        branch = 0;
        memRead = 0;
        memWrite = 0;
        mem2Reg = 0;
        aluSrc = 1;
        regWrite = 1;
        regDestino = 0;
        aluOp = 10;
    }        //13 não tem essa poha
        //14 lch
    else if (strcmp(opcode, "00001110") == 0) {//carrega constante de 16bits nos 2 bytes mais significativos
        jump = 0;
        branch = 0;
        memRead = 0;
        memWrite = 0;
        mem2Reg = 0;
        aluSrc = 1;
        regWrite = 1;
        regDestino = 0;
        aluOp = 10;
        FLAG_CARREGAR_CONSTANTE = 1;
    }//15 lcl
    else if (strcmp(opcode, "00001111") == 0) {//carrega constante de 16bits nos 2 bytes menos significativos
        jump = 0;
        branch = 0;
        memRead = 0;
        memWrite = 0;
        mem2Reg = 0;
        aluSrc = 1;
        regWrite = 1;
        regDestino = 0;
        aluOp = 10;
        FLAG_CARREGAR_CONSTANTE = 1;
    }//16 load
    else if (strcmp(opcode, "00010000") == 0) {//lw configurado
        jump = 0;
        branch = 0;
        memRead = 1;
        memWrite = 0;
        mem2Reg = 1;
        aluSrc = 1;
        regWrite = 1;
        regDestino = 0;
        aluOp = 0;

    }//17
    else if (strcmp(opcode, "00010001") == 0) {//sw  configurado
        jump = 0;
        branch = 0;
        memRead = 0;
        memWrite = 1;
        mem2Reg = 1;
        aluSrc = 1;
        regWrite = 0;
        regDestino = 1;
        aluOp = 0;
    }//18
    else if (strcmp(opcode, "00010010") == 0){//jal
        jump = 0;
        branch = 0;
        memRead = 0;
        memWrite = 0;
        mem2Reg = 0;
        aluSrc = 0;
        regWrite = 0;
        regDestino = 0;
        aluOp = 1;
        FLAG_JAL = 1;
    }//20
    else if (strcmp(opcode, "00010100") == 0) {//beq
        jump = 0;
        branch = 1;
        memRead = 0;
        memWrite = 0;
        mem2Reg = 0;
        aluSrc = 0;
        regWrite = 0;
        regDestino = 0;
        aluOp = 1;
    }//22
    else if (strcmp(opcode, "00010110") == 0){//jump
        jump = 1;
        branch = 0;
        memRead = 1;
        memWrite = 0;
        mem2Reg = 1;
        aluSrc = 1;
        regWrite = 1;
        regDestino = 0;
        aluOp = 10;
        FLAG_JAL = 1;
    }//21
    else if (strcmp(opcode, "00010011") == 0){//JR
        jump = 0;
        branch = 0;
        memRead = 1;
        memWrite = 0;
        mem2Reg = 1;
        aluSrc = 1;
        regWrite = 1;
        regDestino = 0;
        aluOp = 10;
         FLAG_JAL = 1;
         FLAG_JR= 1;
         
    }//22
    else if (strcmp(opcode, "00010101") == 0){//beq
        jump=0;
        branch = 1;
        memRead = 0;
        memWrite = 0;
        mem2Reg = 2;
        aluSrc = 0;
        regWrite = 0;
        regDestino = 2;
        aluOp = 1;
    }
}


