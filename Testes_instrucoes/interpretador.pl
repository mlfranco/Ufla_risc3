#!/usr/bin/perl
# Autor: Rubens Takiguti Ribeiro
# Descricao: Programa que le um arquivo com instrucoes 
# do UFLA-RISC e converte para um arquivo binario.
# As constantes devem ser escritas em numeros inteiros.
#
# Utilizacao:
# $ ./interpretador.pl arquivo_entrada
#

if (scalar(@ARGV) < 1) {
   print "Norma para escrever as instruções:\n";
   print "1 - Uma instrução por linha\n";
   print "2 - Comentários usando # desconsidera ate o final da linha\n";
   print "3 - Pode deixar linhas em branco\n";
   print "4 - Todo numero deve ser representado com inteiros\n";
   print "5 - Os registradores seguem o padrao \"RN\" onde N e' o numero do registrador (intervalo de 0 a 31)\n";
   print "6 - Os operandos podem ser separados por virgula, mas devem conter espacoes entre eles\n";
   print "7 - Lista de palavras chave e significados:\n";
   print " address     = endereco das linhas seguintes\n";
   print " halt        = instrucao de parada\n";

   print " add         = 1 - soma\n";
   print " sub         = 2 - subtracao\n";
   print " zeros       = 3 - zera o registrador\n";
   print " xor         = 4 - xor bit a bit\n";
   print " or          = 5 - or bit a bit\n";
   print " passnota    = 6 - not bit a bit\n";
   print " and         = 7 - and bit a bit\n";
   print " asl         = 8 - shift aritmetico a esquerda\n";
   print " asr         = 9 - shift aritmetico a direita\n";
   print " lsl         = 10 - shift logico a esquerda\n";
   print " lsr         = 11 - shift logico a direita\n";
   print " passa       = 12 - copia valor do registrador\n";
   print " noop        = 13 - instrucao de intervalo\n";
   print " lch         = 14 - carrega para 2 bytes mais significativos\n";
   print " lcl         = 15 - carrega para 2 bytes menos significativos\n";
   print " load        = 16 - carrega dado da memoria para registrador\n";
   print " store       = 17 - grava dado do registrador na memoria\n";
   print " jal         = 18 - jump and link\n";
   print " jr          = 19 - jump register\n";
   print " beq         = 20 - branch if equal\n";
   print " bne         = 21 - branch if not equal\n";
   print " j           = 22 - jump\n";

   print "\nInstrucoes do grupo ()";
   print " slt         = 23 - set on less then\n";
   print " smt         = 24 - set on more then\n";
   print " inc         = 25 - incrementa\n";
   print " dec         = 26 - decrementa\n";
   print " ses         = 27 - set on equal signals\n";
   print " snes        = 28 - set on not equal signals\n";
   print " nand        = 29 - not and\n";
   print " nor         = 30 - not or\n";
   print " esp         = 31 - espelho\n";

   exit(0);
}

open(arq, $ARGV[0]) or die("Erro: Nao foi possivel abrir o arquivo ".$ARGV[0]);
while (<arq>) { print conversao($_)."\n"; }
close(arq) or die("Erro: Nao foi possivel fechar o arquivo ".$ARGV[0]);
exit(0);

#
#     conversao(entrada): Converte uma linha de codigo para binario
#
sub conversao {
   $entrada = $_[0];
   chomp($entrada);
   $entrada = substr($entrada, 0, index($entrada, '#')) if (index($entrada, '#') >= 0);
   $entrada =~ s/,//g;
   $entrada =~ s/R//g;
   @vt = split(' ', lc($entrada));

   # INSTRUCOES DO UFLA-RISC
   ################################################ RC #### RA #### RB #####
   if    ($vt[0] eq 'add')       { return tipoR( 1, $vt[1], $vt[2], $vt[3]); }
   elsif ($vt[0] eq 'sub')       { return tipoR( 2, $vt[1], $vt[2], $vt[3]); }
   elsif ($vt[0] eq 'zeros')     { return tipoR( 3, $vt[1],      0,      0); }
   elsif ($vt[0] eq 'xor')       { return tipoR( 4, $vt[1], $vt[2], $vt[3]); }
   elsif ($vt[0] eq 'or')        { return tipoR( 5, $vt[1], $vt[2], $vt[3]); }
   elsif ($vt[0] eq 'passnota') { return tipoR( 6, $vt[1], $vt[2],      0); }
   elsif ($vt[0] eq 'and')       { return tipoR( 7, $vt[1], $vt[2], $vt[3]); }
   elsif ($vt[0] eq 'asl')       { return tipoR( 8, $vt[1], $vt[2], $vt[3]); }
   elsif ($vt[0] eq 'asr')       { return tipoR( 9, $vt[1], $vt[2], $vt[3]); }
   elsif ($vt[0] eq 'lsl')       { return tipoR(10, $vt[1], $vt[2], $vt[3]); }
   elsif ($vt[0] eq 'lsr')       { return tipoR(11, $vt[1], $vt[2], $vt[3]); }
   elsif ($vt[0] eq 'passa')     { return tipoR(12, $vt[1], $vt[2],      0); }
   elsif ($vt[0] eq 'noop')      { return tipoR(13,      0,      0,      0); }
   elsif ($vt[0] eq 'lch')       { return tipoC(14, $vt[1],         $vt[2]); }
   elsif ($vt[0] eq 'lcl')       { return tipoC(15, $vt[1],         $vt[2]); }
   elsif ($vt[0] eq 'load')      { return tipoR(16, $vt[1], $vt[2],      0); }
   elsif ($vt[0] eq 'store')     { return tipoR(17, $vt[1], $vt[2],      0); }
   elsif ($vt[0] eq 'jal')       { return tipoJ(18, $vt[1]                ); }
   elsif ($vt[0] eq 'jr')        { return tipoR(19, $vt[1],      0,      0); }
   elsif ($vt[0] eq 'beq')       { return tipoR(20, $vt[1], $vt[2], $vt[3]); }
   elsif ($vt[0] eq 'bne')       { return tipoR(21, $vt[1], $vt[2], $vt[3]); }
   elsif ($vt[0] eq 'j')         { return tipoJ(22, $vt[1]                ); }

   # INSTRUCOES DO GRUPO
   elsif ($vt[0] eq 'slt')       { return tipoR(23, $vt[1], $vt[2], $vt[3]); }
   elsif ($vt[0] eq 'smt')       { return tipoR(24, $vt[1], $vt[2], $vt[3]); }
   elsif ($vt[0] eq 'inc')       { return tipoR(25, $vt[1], $vt[2], $vt[3]); }
   elsif ($vt[0] eq 'dec')       { return tipoR(26, $vt[1], $vt[2], $vt[3]); }
   elsif ($vt[0] eq 'ses')       { return tipoR(27, $vt[1], $vt[2], $vt[3]); }
   elsif ($vt[0] eq 'snes')      { return tipoR(28, $vt[1], $vt[2], $vt[3]); }
   elsif ($vt[0] eq 'nand')      { return tipoR(29, $vt[1], $vt[2], $vt[3]); }
   elsif ($vt[0] eq 'nor')       { return tipoR(30, $vt[1], $vt[2], $vt[3]); }
   elsif ($vt[0] eq 'esp')       { return tipoR(31, $vt[1], $vt[2],      0); }

   # OUTRAS INTRUCOES
   elsif ($vt[0] eq 'address') { return 'address '.ib($vt[1], 16); }
   elsif ($vt[0] eq 'halt')    { return '11111111'.'11111111'.'11111111'.'11111111';}
   elsif (length($vt[0]))      { return ib($_[0], 32); }
   return;
}

#
#     tipoX: Retorna o binario de acordo com o tipo da instrucao
#
sub tipoR { return ib($_[0], 8).ib($_[2], 8).ib($_[3], 8).ib($_[1], 8); }
sub tipoJ { return ib($_[0], 8).ib($_[1], 24); }
sub tipoC { return ib($_[0], 8).ib($_[2], 16).ib($_[1], 8); }

#
#     ib(int, N): Converte numero inteiro para binario de N bits
#
sub ib {
   for (my $int = $_[0], my $j = $_[1], $r = ''; $j > 0; $j--) {
      $sub = $int % 2;
      $r = $sub.$r;
      $int = ($int - $sub) / 2;
   }
   return $r;
}
