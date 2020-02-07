#include "../imagem.c"
#define tamMask 3 //tamanho das linhas e colunas da matriz da mascara

//constantes char das mascaras
#define leste 'l'
#define oeste 'o'
#define cruz 'c'
#define norte 'n'
#define sul 's'
#define diagonal 'd'
#define ponto 'x'
#define nordeste '1'
#define sudoeste '3'
#define noroeste '2'
#define sudeste '4'
#define vertical 'v'
#define horizontal 'h'
#define personalizada 'p'

typedef struct mascara Mascara; // struct para armazenar informacoes da mascara

void iniciarMask(Mascara * mask, char tipo, Linha * linha); // atribui valores a uma variavel mascara

void abrirMask(Mascara * mask); // abre uma mascara personalizada de um arquivo "mask.txt que esta na mesma pasta do executavel"

Mascara construirMask(char tipo); // preenche a matriz linha da mascara com valores inteiros

void apagarMask(Mascara * mask); // libera memoria da matriz linha

void refletirMaskP(Mascara * mask); // espelha os valores da matriz de uma mascara personalizada

Mascara refletirMask(char tipo); // espelha os valores da matriz de uma mascara

FILE * novoArquivoRelatorio(); // gera um arquivo "rel(numero).txt" e devolve seu ponteiro

void imprimirRelatorio(char * operacao, Mascara mask); // salva um arquivo "rel(numero).txt" para se ter um index das mascaras e das funcoes aplicadas na imagem

void pintar(Imagem * resultado, int posicaoXI, int posicaoYI, int posicaoX, int posicaoY); // pinta uma posicao da matriz imagem

void fazerDil(Imagem * resultado, Mascara tipo, Linha * original, int posicaoX, int posicaoY); // calcula as posicoes que devem ser pintadas na dilatacao

Imagem dilatacao(Imagem imgI, char tipo); // funcao que translada a mascara por toda matriz do struct imagem com o objetivo de dilatar

void fazerEro(Imagem * resultado, Mascara tipo, Linha * original, int posicaoX, int posicaoY); // calcula as posicoes que devem ser pintadas na erosao

Imagem erosao(Imagem imgI, char tipo); // funcao que translada a mascara por toda matriz do struct imagem com o objetivo de erodir

Imagem abertura(Imagem imgI, char tipo); // operacao de abertura

Imagem fechamento(Imagem imgI, char tipo); // operacao de fechamento
