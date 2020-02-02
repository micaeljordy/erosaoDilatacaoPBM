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
    Coluna * coluna;
    int centroX;
    int centroY;
}Mascara;

void iniciarMask(Mascara * mask, char tipo, Coluna * coluna, int centroX, int centroY)
{
    mask->tipo = tipo;
    mask->coluna = coluna;
    mask->centroX = centroX;
    mask->centroY = centroY;
}

Mascara construirMask(char tipo)
{
    Mascara mask;
    Coluna * colunaMask;
    colunaMask = (Coluna *) malloc(tamMask * sizeof(Coluna)); 
    colunaMask[0].linha = (int *) malloc(tamMask*(sizeof(int)));
    colunaMask[1].linha = (int *) malloc(tamMask*(sizeof(int)));
    colunaMask[2].linha = (int *) malloc(tamMask*(sizeof(int)));

    iniciarMask(&mask, tipo, colunaMask, tamMask/2, tamMask/2);

        switch (tipo)
        {
        case horizontal:
            mask.coluna[0].linha[0] = 0;
            mask.coluna[0].linha[1] = 0;
            mask.coluna[0].linha[2] = 0;
            mask.coluna[1].linha[0] = 1;
            mask.coluna[1].linha[1] = 1;
            mask.coluna[1].linha[2] = 1;
            mask.coluna[2].linha[0] = 0;
            mask.coluna[2].linha[1] = 0;
            mask.coluna[2].linha[2] = 0;
        break;

        case vertical:
            mask.coluna[0].linha[0] = 0;
            mask.coluna[0].linha[1] = 1;
            mask.coluna[0].linha[2] = 0;
            mask.coluna[1].linha[0] = 0;
            mask.coluna[1].linha[1] = 1;
            mask.coluna[1].linha[2] = 0;
            mask.coluna[2].linha[0] = 0;
            mask.coluna[2].linha[1] = 1;
            mask.coluna[2].linha[2] = 0;
        break;

        case noroeste:
            mask.coluna[0].linha[0] = 1;
            mask.coluna[0].linha[1] = 0;
            mask.coluna[0].linha[2] = 0;
            mask.coluna[1].linha[0] = 0;
            mask.coluna[1].linha[1] = 1;
            mask.coluna[1].linha[2] = 0;
            mask.coluna[2].linha[0] = 0;
            mask.coluna[2].linha[1] = 0;
            mask.coluna[2].linha[2] = 0;
            break;

        case nordeste:
            mask.coluna[0].linha[0] = 0;
            mask.coluna[0].linha[1] = 0;
            mask.coluna[0].linha[2] = 1;
            mask.coluna[1].linha[0] = 0;
            mask.coluna[1].linha[1] = 1;
            mask.coluna[1].linha[2] = 0;
            mask.coluna[2].linha[0] = 0;
            mask.coluna[2].linha[1] = 0;
            mask.coluna[2].linha[2] = 0;
            break;

        case sudoeste:
            mask.coluna[0].linha[0] = 0;
            mask.coluna[0].linha[1] = 0;
            mask.coluna[0].linha[2] = 0;
            mask.coluna[1].linha[0] = 0;
            mask.coluna[1].linha[1] = 1;
            mask.coluna[1].linha[2] = 0;
            mask.coluna[2].linha[0] = 1;
            mask.coluna[2].linha[1] = 0;
            mask.coluna[2].linha[2] = 0;
            break;

        case sudeste:
            mask.coluna[0].linha[0] = 0;
            mask.coluna[0].linha[1] = 0;
            mask.coluna[0].linha[2] = 0;
            mask.coluna[1].linha[0] = 0;
            mask.coluna[1].linha[1] = 1;
            mask.coluna[1].linha[2] = 0;
            mask.coluna[2].linha[0] = 0;
            mask.coluna[2].linha[1] = 0;
            mask.coluna[2].linha[2] = 1;
            break;
        
        case leste:
            mask.coluna[0].linha[0] = 0;
            mask.coluna[0].linha[1] = 0;
            mask.coluna[0].linha[2] = 0;
            mask.coluna[1].linha[0] = 0;
            mask.coluna[1].linha[1] = 1;
            mask.coluna[1].linha[2] = 1;
            mask.coluna[2].linha[0] = 0;
            mask.coluna[2].linha[1] = 0;
            mask.coluna[2].linha[2] = 0;
            break;

        case oeste:
            mask.coluna[0].linha[0] = 0;
            mask.coluna[0].linha[1] = 0;
            mask.coluna[0].linha[2] = 0;
            mask.coluna[1].linha[0] = 1;
            mask.coluna[1].linha[1] = 1;
            mask.coluna[1].linha[2] = 0;
            mask.coluna[2].linha[0] = 0;
            mask.coluna[2].linha[1] = 0;
            mask.coluna[2].linha[2] = 0;
            break;

        case cruz:
            mask.coluna[0].linha[0] = 0;
            mask.coluna[0].linha[1] = 1;
            mask.coluna[0].linha[2] = 0;
            mask.coluna[1].linha[0] = 1;
            mask.coluna[1].linha[1] = 1;
            mask.coluna[1].linha[2] = 1;
            mask.coluna[2].linha[0] = 0;
            mask.coluna[2].linha[1] = 1;
            mask.coluna[2].linha[2] = 0;
            break;

        case norte:
            mask.coluna[0].linha[0] = 0;
            mask.coluna[0].linha[1] = 1;
            mask.coluna[0].linha[2] = 0;
            mask.coluna[1].linha[0] = 0;
            mask.coluna[1].linha[1] = 1;
            mask.coluna[1].linha[2] = 0;
            mask.coluna[2].linha[0] = 0;
            mask.coluna[2].linha[1] = 0;
            mask.coluna[2].linha[2] = 0;
            break;

        case sul:
            mask.coluna[0].linha[0] = 0;
            mask.coluna[0].linha[1] = 0;
            mask.coluna[0].linha[2] = 0;
            mask.coluna[1].linha[0] = 0;
            mask.coluna[1].linha[1] = 1;
            mask.coluna[1].linha[2] = 0;
            mask.coluna[2].linha[0] = 0;
            mask.coluna[2].linha[1] = 1;
            mask.coluna[2].linha[2] = 0;
            break;

        case diagonal:
            mask.coluna[0].linha[0] = 1;
            mask.coluna[0].linha[1] = 0;
            mask.coluna[0].linha[2] = 1;
            mask.coluna[1].linha[0] = 0;
            mask.coluna[1].linha[1] = 1;
            mask.coluna[1].linha[2] = 0;
            mask.coluna[2].linha[0] = 1;
            mask.coluna[2].linha[1] = 0;
            mask.coluna[2].linha[2] = 1;
            break;

        default:
            mask.coluna[0].linha[0] = 0;
            mask.coluna[0].linha[1] = 0;
            mask.coluna[0].linha[2] = 0;
            mask.coluna[1].linha[0] = 0;
            mask.coluna[1].linha[1] = 1;
            mask.coluna[1].linha[2] = 0;
            mask.coluna[2].linha[0] = 0;
            mask.coluna[2].linha[1] = 0;
            mask.coluna[2].linha[2] = 0;
            break;
        }

    return mask;
}

void apagarMask(Mascara * mask)
{
    mask->tipo = '\0';
    mask->centroX = 0;
    mask->centroY = 0;
    free(mask->coluna[0].linha);
    free(mask->coluna[1].linha);
    free(mask->coluna[2].linha);
    free(mask->coluna);
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

    case nordeste:
        mask = construirMask(sudoeste);
        break;
    
    case sudoeste:
        mask = construirMask(nordeste);
        break;

    case noroeste:
        mask = construirMask(sudeste);
        break;

    case sudeste:
        mask = construirMask(noroeste);
        break;

    default:
        mask = construirMask(ponto);
        break;
    }

    return mask;
}

void dilatar(Coluna * coluna, Mascara tipo, int posicaoX, int posicaoY)
{
    int i, j;
    for (i = 0; i < tamMask; i++)
    {
        for(j = 0; j < tamMask; j++)
        {
            if(tipo.coluna[i].linha[j] == 1)
            coluna[posicaoX + i].linha[posicaoY + j] = 1;
        }
    }
}

void maskDil(Mascara tipo, Coluna * original, Coluna * quadro, int posicaoX, int posicaoY)
{
    int i, j;

    for (i = 0; i < tamMask; i++)
    {
        for (j = 0; j < tamMask; j++)
        {
            if(original[posicaoX + i].linha[posicaoY + j] + tipo.coluna[i].linha[j] > 1) 
            {
                dilatar(quadro, tipo, posicaoX, posicaoY);
                return;
            }
        }
    }
}

Imagem dilatacao(Imagem imgI, char tipo)
{
    Imagem img;
    img = canvas(imgI);
    Mascara mask;

    mask = construirMask(tipo);

    int i, j;

    for(i = 0; i < imgI.h - tamMask; i++)
    {
        for(j = 0; j < imgI.l - tamMask; j++)
        {
            maskDil(mask, imgI.coluna, img.coluna, i, j);
        }
    }

    apagarMask(&mask);

    return img;
}

void erodir(Coluna * coluna, Mascara tipo, int posicaoX, int posicaoY)
{
    int i, j;
    for (i = 0; i < tamMask; i++)
    {
        for(j = 0; j < tamMask; j++)
        {
            if(tipo.coluna[i].linha[j] == 1)
            coluna[posicaoX + i].linha[posicaoY + j] = 0;
        }
    }
}

void maskEro(Mascara tipo, Coluna * original, Coluna * quadro, int posicaoX, int posicaoY)
{
    int i, j;

    for (i = 0; i < tamMask; i++)
    {
        for (j = 0; j < tamMask; j++)
        {
            if(original[posicaoX + i].linha[posicaoY + j] - tipo.coluna[i].linha[j] < 0) 
            {
                erodir(quadro, tipo, posicaoX, posicaoY);
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

    for(i = 0; i < imgI.h - tamMask; i++)
    {
        for(j = 0; j < imgI.l - tamMask; j++)
        {
            maskEro(mask, imgI.coluna, img.coluna, i, j);
        }
    }

    apagarMask(&mask);

    return img;
}