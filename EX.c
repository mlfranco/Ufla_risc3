#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int branch;
extern int pc;
extern int FLAG_DESVIO;

/**
 * Função "soma" realiza soma entre dois registradores (A e B) , esta soma é feita bit a bit
 * 
 * @param valorA é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador A".
 * 
 * @param valorB  é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador B".
 * 
 * @param aluResult variavel utiliza para armazenar o resultadoda operação , valendo resaltar
 * que esta é passada por referencia para a função .
 * 
 * @param FLAG_OVER para 1 caso haja over flow para que seja tratar possiveis erros ou tomar decisoes .
 * 
 * @param FLAG_ZERO  OBSERVAÇÃO IMPORTANTE a flag de zero é setada para 1 caso a variavel seja DIFERENTE DE 0!!!
 * este valor sera invertido no final da função "ALU" , antes de ser retornada para o programa de simulação!
 */
void soma(char *valorA, char *valorB, char *aluResult, int *FLAG_OVER, int *FLAG_ZERO) {
    int tamanho, i;
    tamanho = strlen(valorA);
    for (i = tamanho; i >= 0; i--) {
        if ((valorA[i] == '1') && (valorB[i] == '1')) {
            if (*FLAG_OVER == 1) {
                aluResult[i] = '1';
                *FLAG_OVER = 1;
                *FLAG_ZERO = 1;
            } else {
                aluResult[i] = '0';
                *FLAG_OVER = 1;
            }
        } else if ((valorA[i] == '1') && (valorB[i] == '0') || (valorA[i] == '0') && (valorB[i] == '1')) {
            if (*FLAG_OVER == 1) {
                aluResult[i] = '1';
                *FLAG_OVER = 0;
                *FLAG_ZERO = 1;
            } else {
                aluResult[i] = '1';
                *FLAG_OVER = 0;
            }
        } else if ((valorA[i] == '0') && (valorA[i] == '0')) {
            if (*FLAG_OVER == 1) {
                aluResult[i] = '1';
                *FLAG_OVER = 0;
                *FLAG_ZERO = 1;
            } else {
                aluResult[i] = '0';
                *FLAG_OVER = 0;
            }
        }
    }
}
/**
 * Função "subtracao" realiza a subtração entre dois registradores (A e B) , esta subtração é 
 * feita bit a bit sendo que quando necessario o flag de over flow e setado em 1 (ou seja ativado /positivo)
 * 
 * As FLAG's OVER e ZERO sao setadas para 1 caso haja over flow ou o resultado da operação seja 0 ,
 * para que um suposto "S.O." possa tratar possiveis erros ou tomar decisoes . 
 * 
 * @param valorA é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador A".
 * 
 * @param valorB  é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador B".
 * 
 * @param aluResult variavel utiliza para armazenar o resultadoda operação , valendo resaltar
 * que esta é passada por referencia para a função .
 * 
 * @param FLAG_UNDER  para 1 caso haja under flow para que seja tratar possiveis erros ou tomar decisoes .
 * 
 * @param FLAG_ZERO OBSERVAÇÃO IMPORTANTE a flag de zero é setada para 1 caso a variavel seja DIFERENTE DE 0!!!
 * este valor sera invertido no final da função "ALU" , antes de ser retornada para o programa de simulação!
 */
void subtracao(char *valorA, char *valorB, int aluOp, char *aluResult, int *FLAG_UNDER, int *FLAG_ZERO) {
    int tamanho, i;
    tamanho = strlen(valorA);
    for (i = tamanho; i >= 0; i--) {
        if ((valorA[i] == '1') && (valorB[i] == '1')) {
            if (*FLAG_UNDER == 1) {
                aluResult[i] = '1';
                *FLAG_UNDER = 0;
                *FLAG_ZERO = 1;
            } else {
                aluResult[i] = '0';
                *FLAG_UNDER = 0;
            }
        } else if ((valorA[i] == '1') && (valorB[i] == '0')) {
            if (*FLAG_UNDER == 1) {
                aluResult[i] = '0';
                *FLAG_UNDER = 0;
            } else {
                aluResult[i] = '0';
                FLAG_UNDER = 0;
            }
        } else if ((valorA[i] == '0') && (valorA[i] == '0')) {
            if (*FLAG_UNDER == 1) {
                aluResult[i] = '0';
                *FLAG_UNDER = 1;
            } else {
                aluResult[i] = '0';
                *FLAG_UNDER = 0;
            }
        } else if ((valorA[i] == '0') && (valorB[i] == '1'))
            if (*FLAG_UNDER == 1) {
                aluResult[i] = '1';
                *FLAG_UNDER = 1;
                *FLAG_ZERO = 1;
            } else {
                aluResult[i] = '1';
                *FLAG_UNDER = 1;
                *FLAG_ZERO = 1;
            }

    }

}
/**
 * A função zera tem como objetivo setar o valor de um registrador para 0 (zero)
 * 
 * @param aluResult aluResult variavel utiliza para armazenar o resultadoda operação , valendo resaltar
 * que esta é passada por referencia para a função .
 * 
 * @param FLAG_ZERO  OBSERVAÇÃO IMPORTANTE a flag de zero é setada para 1 caso a variavel seja DIFERENTE DE 0!!!
 * este valor sera invertido no final da função "ALU" , antes de ser retornada para o programa de simulação!
 */
void zera(char *aluResult, int *FLAG_ZERO) {
    int i;
    for (i = 0; i < 32; i++) {
        aluResult[i] = '0';
    }
    *FLAG_ZERO = 1;
}
/**
 * Afunção XOR realiza  uma operação logica (XOR) bit a bit , entre as variaveis valorA e valorB
 * exemplo : 
 * 
 * realiza operação entre valorA[1] e valorB[1]
 * 
 * 
 * @param valorA é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador A".
 * 
 * @param valorB  é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador B".
 * 
 * @param aluResult aluResult variavel utiliza para armazenar o resultadoda operação , valendo resaltar
 * que esta é passada por referencia para a função .
 * 
 * @param FLAG_ZERO  OBSERVAÇÃO IMPORTANTE a flag de zero é setada para 1 caso a variavel seja DIFERENTE DE 0!!!
 * este valor sera invertido no final da função "ALU" , antes de ser retornada para o programa de simulação!
 */
void XOR(char *valorA, char *valorB, char *aluResult, int *FLAG_ZERO) {
    int tamanho, i;
    tamanho = strlen(valorA);
    for (i = tamanho; i >= 0; i--) {
        if ((valorA[i] == '1') && (valorB[i] == '1')) {
            aluResult[i] = '0';
        } else if ((valorA[i] == '1') && (valorB[i] == '0') || (valorA[i] == '0') && (valorB[i] == '1')) {
            aluResult[i] = '1';
            *FLAG_ZERO = 1;
        } else if ((valorA[i] == '0') && (valorA[i] == '0')) {
            aluResult[i] = '0';
        }
    }

}
/**
 * Afunção OR realiza  uma operação logica (OR) bit a bit , entre as variaveis valorA e valorB
 * exemplo : 
 * 
 * realiza operação entre valorA[1] e valorB[1]
 * 
 * @param valorA é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador A".
 * 
 * @param valorB  é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador B".
 * 
 * @param aluResult aluResult variavel utiliza para armazenar o resultadoda operação , valendo resaltar
 * que esta é passada por referencia para a função .
 * 
 * @param FLAG_ZERO OBSERVAÇÃO IMPORTANTE a flag de zero é setada para 1 caso a variavel seja DIFERENTE DE 0!!!
 * este valor sera invertido no final da função "ALU" , antes de ser retornada para o programa de simulação!
 */
void OR(char *valorA, char *valorB, char *aluResult, int *FLAG_ZERO) {
    int tamanho, i;
    tamanho = strlen(valorA);
    for (i = tamanho; i >= 0; i--) {
        if ((valorA[i] == '1') && (valorB[i] == '1')) {
            aluResult[i] = '1';
            *FLAG_ZERO = 1;
        } else if ((valorA[i] == '1') && (valorB[i] == '0') || (valorA[i] == '0') && (valorB[i] == '1')) {
            aluResult[i] = '1';
            *FLAG_ZERO = 1;
        } else if ((valorA[i] == '0') && (valorA[i] == '0')) {
            aluResult[i] = '0';
        }
    }
}
/**
 * Afunção NOT realiza  uma operação logica (NOT) bit a bit , entre as variaveis valorA e ela mesma
 * ou seja retorna o valor 
 * exemplo : 
 * 
 * valorA[1] = negação (valorA[1])
 * 
 * @param valorA é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador A".
 * 
 * @param aluResult aluResult variavel utiliza para armazenar o resultadoda operação , valendo resaltar
 * que esta é passada por referencia para a função .
 * 
 * @param FLAG_ZERO  OBSERVAÇÃO IMPORTANTE a flag de zero é setada para 1 caso a variavel seja DIFERENTE DE 0!!!
 * este valor sera invertido no final da função "ALU" , antes de ser retornada para o programa de simulação!
 */
void NOT(char *valorA, char *aluResult, int *FLAG_ZERO) {
    int tamanho, i;
    tamanho = strlen(valorA);
    for (i = tamanho; i >= 0; i--) {
        if (valorA[i] == '1') {
            aluResult[i] = '0';
        } else if (valorA[i] == '0') {
            aluResult[i] = '1';
            *FLAG_ZERO = 1;
        }
    }
}
/**
 * Afunção AND realiza  uma operação logica (AND) bit a bit , entre as variaveis valorA e valorB
 * exemplo : 
 * 
 * realiza operação entre valorA[1] e valorB[1]
 * 
 * @param valorA é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador A".
 * 
 * @param valorB  é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador B".
 * 
 * @param aluResult aluResult variavel utiliza para armazenar o resultadoda operação , valendo resaltar
 * que esta é passada por referencia para a função .
 * 
 * @param FLAG_ZERO OBSERVAÇÃO IMPORTANTE a flag de zero é setada para 1 caso a variavel seja DIFERENTE DE 0!!!
 * este valor sera invertido no final da função "ALU" , antes de ser retornada para o programa de simulação!
 */
void AND(char *valorA, char *valorB, char *aluResult, int *FLAG_ZERO) {
    int tamanho, i;
    tamanho = strlen(valorA);
    for (i = tamanho; i >= 0; i--) {
        if ((valorA[i] == '1') && (valorB[i] == '1')) {
            aluResult[i] = '1';
            *FLAG_ZERO = 1;
        } else if ((valorA[i] == '1') && (valorB[i] == '0') || (valorA[i] == '0') && (valorB[i] == '1')) {
            aluResult[i] = '0';
        } else if ((valorA[i] == '0') && (valorA[i] == '0')) {
            aluResult[i] = '0';
        }
    }
}
/**
 * 
 * Função  realia um SHIFT ARITMETRICO para a ESQUERDA na variavel "valorA" , quendo que a quantidade
 * de "SHIFT's" realizados dependem do valor armazenado navariavel "valorB"
 * 
 * @param valorA é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador A".
 * 
 * @param valorB  é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador B".
 * 
 * @param aluResult aluResult variavel utiliza para armazenar o resultadoda operação , valendo resaltar
 * que esta é passada por referencia para a função .
 * 
 * @param FLAG_ZERO  OBSERVAÇÃO IMPORTANTE a flag de zero é setada para 1 caso a variavel seja DIFERENTE DE 0!!!
 * este valor sera invertido no final da função "ALU" , antes de ser retornada para o programa de simulação!
 */
void ASL(char *valorA, char *valorB, char *aluResult, int *FLAG_ZERO) {
    int quanto_deslocar, i;
    quanto_deslocar = bin2dec(valorB);
    strcpy(aluResult, valorA);
    for (i = quanto_deslocar; i < 32; i++) {
        aluResult[quanto_deslocar ] = aluResult[quanto_deslocar + 1];
    }

    aluResult[quanto_deslocar] = '0';
    aluResult[32] = '\0';

    //verificar se o flag de zero deve ser ativado !
    for (i = 0; i > 32; i++) {
        if (aluResult[i] == '1') {
            *FLAG_ZERO = 1;
        }
    }
}
 /**
 * Função  realia um SHIFT ARITMETRICO para a DIREITA na variavel "valorA" , quendo que a quantidade
 * de "SHIFT's" realizados dependem do valor armazenado navariavel "valorB"
  * 
 * @param valorA é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador A".
 * 
 * @param valorB  é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador B".
 * 
 * @param aluResult aluResult variavel utiliza para armazenar o resultadoda operação , valendo resaltar
 * que esta é passada por referencia para a função .
  * 
  * @param FLAG_ZERO OBSERVAÇÃO IMPORTANTE a flag de zero é setada para 1 caso a variavel seja DIFERENTE DE 0!!!
  * este valor sera invertido no final da função "ALU" , antes de ser retornada para o programa de simulação!
  */
void ASR(char *valorA, char *valorB, char *aluResult, int *FLAG_ZERO) {
    int quanto_deslocar, i;
    quanto_deslocar = bin2dec(valorB);

    for (i = 31 - quanto_deslocar; i >= 0; i--) {
        aluResult[i + quanto_deslocar] = valorA[32 - quanto_deslocar];
    }
    for (i = 0; i < quanto_deslocar; i++) {
        aluResult[quanto_deslocar] = '0';

    }
    //verificar se o flag de zero deve ser ativado !
    for (i = 0; i > 32; i++) {
        if (aluResult[i] == '1') {
            *FLAG_ZERO = 1;
        }
    }
}
/**
 * Função  realia um SHIFT LOGICO para a ESQUERDA na variavel "valorA" , quendo que a quantidade
 * de "SHIFT's" realizados dependem do valor armazenado navariavel "valorB"
 * 
 * @param valorA é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador A".
 * 
 * @param valorB  é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador B".
 * 
 * @param aluResult aluResult variavel utiliza para armazenar o resultadoda operação , valendo resaltar
 * que esta é passada por referencia para a função .
 * 
 * @param FLAG_ZERO OBSERVAÇÃO IMPORTANTE a flag de zero é setada para 1 caso a variavel seja DIFERENTE DE 0!!!
 * este valor sera invertido no final da função "ALU" , antes de ser retornada para o programa de simulação!
 */
void LSL(char *valorA, char *valorB, char *aluResult, int *FLAG_ZERO) {
    int quanto_deslocar, i;
    quanto_deslocar = bin2dec(valorB);
    for (i = quanto_deslocar; i < 32; i++) {
        aluResult[ i - quanto_deslocar ] = valorA[quanto_deslocar];
    }
    for (i = 32; i > (31 - quanto_deslocar); i--) {
        aluResult[i] = '0';
    }
    //verificar se o flag de zero deve ser ativado !
    for (i = 0; i > 32; i++) {
        if (aluResult[i] == '1') {
            *FLAG_ZERO = 1;
        }
    }
}
/**
 * Função  realia um SHIFT LOGICO para a DIREITA na variavel "valorA" , quendo que a quantidade
 * de "SHIFT's" realizados dependem do valor armazenado navariavel "valorB"
 * 
 * @param valorA é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador A".
 * 
 * @param valorB  é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador B".
 * 
 * @param aluResult aluResult variavel utiliza para armazenar o resultadoda operação , valendo resaltar
 * que esta é passada por referencia para a função .
 * 
 * @param FLAG_ZERO OBSERVAÇÃO IMPORTANTE a flag de zero é setada para 1 caso a variavel seja DIFERENTE DE 0!!!
 * este valor sera invertido no final da função "ALU" , antes de ser retornada para o programa de simulação!
 */
void LSR(char *valorA, char *valorB, char *aluResult, int *FLAG_ZERO) {
    int quanto_deslocar, i;
    quanto_deslocar = bin2dec(valorB);

    for (i = 31 - quanto_deslocar; i >= 0; i--) {
        aluResult[i + quanto_deslocar] = valorA[32 - quanto_deslocar];
    }
    for (i = 0; i < quanto_deslocar; i++) {
        aluResult[i] = '0';

    }
    //verificar se o flag de zero deve ser ativado !
    for (i = 0; i > 32; i++) {
        if (aluResult[i] == '1') {
            *FLAG_ZERO = 1;
        }
    }
}
/**
 * Função COPY copia o conteudo de "valorA" para a varavel aluResult 
 * 
 * @param valorA é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador A".
 * 
 * @param aluResult aluResult variavel utiliza para armazenar o resultadoda operação , valendo resaltar
 * que esta é passada por referencia para a função .
 * 
 * @param FLAG_ZERO OBSERVAÇÃO IMPORTANTE a flag de zero é setada para 1 caso a variavel seja DIFERENTE DE 0!!!
 * este valor sera invertido no final da função "ALU" , antes de ser retornada para o programa de simulação!
 */
void COPY(char *valorA, char *aluResult, int *FLAG_ZERO) {
    int i;
    strcpy(aluResult, valorA);
    //verificar se o flag de zero deve ser ativado !
    for (i = 0; i > 32; i++) {
        if (aluResult[i] == '1') {
            *FLAG_ZERO = 1;
        }
    }
}
/**
 * 
 * A Função LCH carrega uma constante de 2bytes (16 byte), nos 2 bytes MAIS significativos
 * do registrador C ,que neste caso esta armazenado na variavel "valorB"
 * 
 * @param valorA é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador A".
 * 
 * @param valorB ATENÇÃO >> valorB  é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do >>>"registrador C"
 * 
 * @param aluResult  variavel utiliza para armazenar o resultadoda operação , valendo resaltar
 * que esta é passada por referencia para a função .
 */
void LCH(char *valorA, char *valorB, char *aluResult) {
    //ATENÇÃO VALOR B , neste caso tem o valor o registrador C
    int i;
    for (i = 0; i < 16; i++) {
        valorB[i] = valorA[i];
    }
    strcpy(aluResult, valorB);

}
/**
 * 
 * A Função LCL carrega uma constante de 2bytes (16 byte), nos 2 bytes MENOS significativos
 * do registrador C ,que neste caso esta armazenado na variavel "valorB"
 * 
 * @param valorA é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador A".
 * 
 * @param ATENÇÃO >> valorB  é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do >>>"registrador C"
 * 
 * @param aluResult variavel utiliza para armazenar o resultadoda operação , valendo resaltar
 * que esta é passada por referencia para a função .
 * 
 */
void LCL(char *valorA, char *valorB, char *aluResult) {
    //ATENÇÃO VALOR B , neste caso tem o valor o valoristrador C
    int i;
    for (i = 16; i < 32; i++) {
        valorB[i] = valorA[i - 16];
    }
    strcpy(aluResult, valorB);
}
/**
 * A função copia oconteudo do regsitrador A(valorA) para aluresult ,para que este possa ser 
 * carregado na memoria
 * 
 * @param valorA é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador A".
 * 
 * @param aluResult variavel utiliza para armazenar o resultadoda operação , valendo resaltar
 * que esta é passada por referencia para a função .
 */
void load(char *valorA, char *aluResult) {
    strcpy(aluResult, valorA);
}
/**
 * A função copia oconteudo do regsitrador A(valorA) para aluresult ,para que este possa ser 
 * carregado para o banco de registradores
 * 
 * @param valorA é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador A".
 * 
 * @param aluResult variavel utiliza para armazenar o resultadoda operação , valendo resaltar
 * que esta é passada por referencia para a função .
 * 
 */
void store(char *valorA, char *aluResult) {
    strcpy(aluResult, valorA);
}
/**
 * 
 * Função responsavel por simular uma ALU ( unidade aritmetrica logica ) ,ela recebe o
 * opCode de uma operação e osvalores necessarios para a execução e chama a função
 * necessario para executar esta .
 * A ALU tambem é responsavel por retornar o resultado da operação (aluResult) para 
 * o programa principal.
 * no final da ALU o flag deZERO é invertido ,pois a logica usada para verificar se o 
 * conteudo é ZERO é INVERSA!
 * 
 * @param valorA é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador A".
 * 
 * @param valorB  é uma string(vetor de caracteres) de tamanho 32 , estava armazenada
 * destro do "registrador B".
 * 
 * @param aluResult aluResult variavel utiliza para armazenar o resultadoda operação , valendo resaltar
 * que esta é passada por referencia para a função .
 * 
 * @param opCode variavel que armazena o codigo da opeção a ser executada , esta 
 * é usada para escolher a operação correta
 * 
 * @param aluResult variavel que armazena o resultado das operações executadas
 */
void ALU(char *valorA, char *valorB, int aluOp, char *opCode, char *aluResult) {

    int tamanho, i;
    int FLAG_OVER = 0, FLAG_UNDER = 0, FLAG_ZERO = 0;
    //flag deZERO é invertido ,pois a logica usada para verificar se o 
    //conteudo é ZERO é INVERSA!
    //======================================================================SOMA!!!!!
    if ((aluOp == 10) && (strcmp(opCode, "00000001") == 0)) {
        soma(valorA, valorB, aluResult, &FLAG_OVER, &FLAG_ZERO);
    }//=========================================================================subtação
    else if ((aluOp == 10) && (strcmp(opCode, "00000010") == 0)) {
        subtracao(valorA, valorB, aluOp, aluResult, &FLAG_UNDER, &FLAG_ZERO);
    }//=========================================================================ZERA
    else if ((aluOp == 10) && (strcmp(opCode, "00000011") == 0)) {
        zera(aluResult, &FLAG_ZERO);
    }//=========================================================================XOR
    else if ((aluOp == 10) && (strcmp(opCode, "00000100") == 0)) {
        XOR(valorA, valorB, aluResult, &FLAG_ZERO);
    }//=========================================================================OR
    else if ((aluOp == 10) && (strcmp(opCode, "00000101") == 0)) {
        OR(valorA, valorB, aluResult, &FLAG_ZERO);
    }//=========================================================================NOT
    else if ((aluOp == 10) && (strcmp(opCode, "00000110") == 0)) {
        NOT(valorA, aluResult, &FLAG_ZERO);
    }//=========================================================================AND
    else if ((aluOp == 10) && (strcmp(opCode, "00000111") == 0)) {
        AND(valorA, valorB, aluResult, &FLAG_ZERO);
    }//=========================================================================ASL
    else if ((aluOp == 10) && (strcmp(opCode, "00001000") == 0)) {
        ASL(valorA, valorB, aluResult, &FLAG_ZERO);
    }//=========================================================================ASR
    else if ((aluOp == 10) && (strcmp(opCode, "00001001") == 0)) {
        ASR(valorA, valorB, aluResult, &FLAG_ZERO);
    }//=========================================================================LSL
    else if ((aluOp == 10) && (strcmp(opCode, "00001010") == 0)) {
        LSL(valorA, valorB, aluResult, &FLAG_ZERO);
    }//=========================================================================LSR
    else if ((aluOp == 10) && (strcmp(opCode, "00001011") == 0)) {
        LSR(valorA, valorB, aluResult, &FLAG_ZERO);
    }//=========================================================================COPY
    else if ((aluOp == 10) && (strcmp(opCode, "00001100") == 0)) {
        COPY(valorA, aluResult, &FLAG_ZERO);
    }//=========================================================================LCH
    else if ((aluOp == 10) && (strcmp(opCode, "00001110") == 0)) {
        LCH(valorA, valorB, aluResult);
    }//=========================================================================LCL
    else if ((aluOp == 10) && (strcmp(opCode, "00001111") == 0)) {
        LCL(valorA, valorB, aluResult);
    }//=========================================================================load
    else if ((aluOp == 0) && (strcmp(opCode, "00010000") == 0)) {
        load(valorA, aluResult);
    }//=========================================================================store
    else if ((aluOp == 0) && (strcmp(opCode, "00010001") == 0)) {
        store(valorA, aluResult);
    }//=========================================================================beq  
    
    //ATENçÃO como o flag de ZERo ainda nao foi corrigido deve se adotar 
    //FLAG deZERO  == 1 -> FALSO
    //FLAG deZERO  == 0 -> VERDADEIRO
    else if ((aluOp == 1) && (strcmp(opCode, "00010100") == 0)) {
        subtracao(valorA, valorB, aluOp, aluResult, &FLAG_UNDER, &FLAG_ZERO);
        if ((FLAG_ZERO == 0) && (branch == 1)) {
            FLAG_DESVIO =1 ;
        }
    }//=========================================================================bne 
    else if ((aluOp == 1) && (strcmp(opCode, "00010101") == 0)) {
        subtracao(valorA, valorB, aluOp, aluResult, &FLAG_UNDER, &FLAG_ZERO);
        if ((FLAG_ZERO == 1) && (branch == 1)) {
            FLAG_DESVIO =1 ;
        }
    }


    //INVERÇÃO do flag de ZERO (logica usada é invertida , logo o flag tem o valor "trocado")
    FLAG_ZERO = !FLAG_ZERO;
    //ATENçÃO como o flag de ZERo corrigido deve se adotar 
    //FLAG deZERO  == 1 -> VERDADEIRO
    //FLAG deZERO  == 0 -> FALSO
    
    printf("aluResult :");
    for (i = 0; i < 32; i++) {
        printf("%c", aluResult[i]);
    }
    
    
    printf("\n");
    printf("valor dos flags\n");
    printf("FLAG_ZERO  : %d\n", FLAG_ZERO);
    printf("FLAG_OVER  : %d\n", FLAG_OVER);
    printf("FLAG_UNDER : %d\n", FLAG_UNDER);

}
