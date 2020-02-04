#include "imagem.h"
#define tamMask 3
#define leste 'l'
#define oeste 'o'
#define cruz 'c'
#define norte 'n'
#define sul 's'
#define diagonal 'd'
#define ponto 'p'
#define nordeste '1'
#define sudoeste '3'
#define noroeste '2'
#define sudeste '4'
#define vertical 'v'
#define horizontal 'h'

typedef struct mascara
{
    char tipo;
    Linha * linha;
}Mascara;

void iniciarMask(Mascara * mask, char tipo, Linha * linha)
{
    mask->tipo = tipo;
    mask->linha = linha;
}

Mascara construirMask(char tipo)
{
    Mascara mask;
    Linha * linha;
    linha = (Linha *) malloc(tamMask * sizeof(linha));
    linha[0].coluna = (int *) calloc(tamMask, sizeof(int));
    linha[1].coluna = (int *) calloc(tamMask, sizeof(int));
    linha[2].coluna = (int *) calloc(tamMask, sizeof(int));

    iniciarMask(&mask, tipo, linha);

        switch (tipo)
        {
        case vertical:
            mask.linha[0].coluna[1] = 1;
            mask.linha[2].coluna[1] = 1;
        break;

        case horizontal:
            mask.linha[1].coluna[0] = 1;
            mask.linha[1].coluna[2] = 1;
        break;
        
        case leste:
            mask.linha[1].coluna[1] = 1;
            mask.linha[1].coluna[2] = 1;
            break;

        case oeste:
            mask.linha[1].coluna[0] = 1;
            mask.linha[1].coluna[1] = 1;
            break;

        case norte:
            mask.linha[0].coluna[1] = 1;
            mask.linha[1].coluna[1] = 1;
            break;

        case sul:
            mask.linha[1].coluna[1] = 1;
            mask.linha[2].coluna[1] = 1;
            break;

        case cruz:
            mask.linha[0].coluna[1] = 1;
            mask.linha[2].coluna[1] = 1;
            mask.linha[1].coluna[0] = 1;
            mask.linha[1].coluna[2] = 1;
            break;

        case diagonal:
            mask.linha[0].coluna[0] = 1;
            mask.linha[0].coluna[2] = 1;
            mask.linha[2].coluna[0] = 1;
            mask.linha[2].coluna[2] = 1;
            break;

        default:
            mask.linha[1].coluna[1] = 1;
            break;
        }

    return mask;
}

void apagarMask(Mascara * mask)
{
    mask->tipo = '\0';
    free(mask->linha[0].coluna);
    free(mask->linha[1].coluna);
    free(mask->linha[2].coluna);
    free(mask->linha);
}

Mascara espelharMask(char tipo)
{

    Mascara mask;

    switch (tipo)
    {
    case horizontal:
        mask = construirMask(horizontal);
        break;

    case vertical:
        mask = construirMask(vertical);
        break;
    
    case leste:
        mask = construirMask(oeste);
        break;

    case oeste:
        mask = construirMask(leste);
        break;

    case norte:
        mask = construirMask(sul);
        break;

    case sul:
        mask = construirMask(norte);
        break;

    case cruz:
        mask = construirMask(cruz);
        break;

    case diagonal:
        mask = construirMask(diagonal);
        break;

    default:
        mask = construirMask(ponto);
        break;
    }

    return mask;
}

void dilatar(Linha * linha, Mascara tipo, int posicaoX, int posicaoY)
{
    int i, j;
    for (i = 0; i < tamMask; i++)
    {
        for(j = 0; j < tamMask; j++)
        {
            if(tipo.linha[i].coluna[j] == 1)
            linha[posicaoX + i].coluna[posicaoY + j] = 1;
        }
    }
}

void maskDil(Mascara tipo, Linha * original, Linha * vazia, int posicaoX, int posicaoY)
{
    int i, j;

    for (i = 0; i < tamMask; i++)
    {
        for (j = 0; j < tamMask; j++)
        {
            if(original[posicaoX + i].coluna[posicaoY + j] + tipo.linha[i].coluna[j] > 1) 
            {
                dilatar(vazia, tipo, posicaoX, posicaoY);
                return;
            }
        }
    }
}

Imagem dilatacao(Imagem imgI, char tipo)
{
    Imagem img;
    img = apagar(imgI);
    Mascara mask;

    mask = construirMask(tipo);

    int i, j;

    for(i = 0; i < imgI.l - tamMask; i++)
    {
        for(j = 0; j < imgI.h - tamMask; j++)
        {
            maskDil(mask, imgI.linha, img.linha, i, j);
        }
    }

    apagarMask(&mask);

    return img;
}

void erodir(Linha * linha, Mascara tipo, int posicaoX, int posicaoY)
{
    int i, j;
    for (i = 0; i < tamMask; i++)
    {
        for(j = 0; j < tamMask; j++)
        {
            if(tipo.linha[i].coluna[j] == 1)
            linha[posicaoX + i].coluna[posicaoY + j] = 0;
        }
    }
}

void maskEro(Mascara tipo, Linha * original, Linha * copia, int posicaoX, int posicaoY)
{
    int i, j;

    for (i = 0; i < tamMask; i++)
    {
        for (j = 0; j < tamMask; j++)
        {
            if(original[posicaoX + i].coluna[posicaoY + j] - tipo.linha[i].coluna[j] < 0) 
            {
                erodir(copia, tipo, posicaoX, posicaoY);
                return;
            }
        }
    }
}

Imagem erosao(Imagem imgI, char tipo)
{
    Imagem img;
    img = copiarImagem(imgI);
    Mascara mask;

    mask = espelharMask(tipo);

    int i, j;

    for(i = 0; i < imgI.l - tamMask; i++)
    {
        for(j = 0; j < imgI.h - tamMask; j++)
        {
            maskEro(mask, imgI.linha, img.linha, i, j);
        }
    }

    apagarMask(&mask);

    return img;
}