#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linha Linha; // um struct com array de inteiros

typedef struct imagem Imagem; // um struct para guardar informacoes dos arquivos .PBM

void primeiraIni(Imagem * img); // atribui NULL ao ponteiro linha do struct imagem

void inicializarImagem(Imagem * i, int l, int h, Linha * linha); // atribui valores lidos de um arquivo .PBM para a struct imagem

Imagem copiarImagem(Imagem img); // copia uma imagem sem copiar o endereco do ponteiro

Imagem copiaExpandida(Imagem img); // copia uma imagem, aumenta a matriz em 3 linhas e colunas para finalmente transladar uma unidade de linha e coluna

Imagem pintarDeBranco(Imagem img); // cria uma nova imagem com o mesmo tamanho com a matriz composta somente de zeros

void pintarBordas(Imagem * img); // pinta as bordas de uma imagem de preto. Uso pratico na erosao 

void apagarImagem(Imagem * img); // libera memoria da matriz imagem

Imagem abrir(char nome[]); // abre um arquivo .PPM e guarda os valores em um struct imagem

void limpar(char * str); // apaga uma string. Uso pratico nas funcoes "novoArquivo"

FILE * novoArquivoPBM(); // cria um arquivo .PBM e retorna o seu ponteiro

FILE * novoArquivoPGM(); // cria um arquivo .PGM e retorna o seu ponteiro

void salvarPBM(Imagem img); // salva informacoes do struct imagem em um arquivo PBM

void salvarPGM(Imagem img); // salva informacoes do struct imagem em um arquivo PGM