#include "headers/filtro.h"

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

void abrirMask(Mascara * mask)
{
    char nome[] = "mask.txt";

    FILE * arq;
    arq = fopen(nome, "r");
    
    if(arq != NULL)
    {
        int i,j;
        for(i = 0; i < tamMask; i++)
        {
            j = 0;
            char c;
            do 
            {
                fscanf(arq, " %c", &c);
                if(c == '1') mask->linha[i].coluna[j] = 1;
                else mask->linha[i].coluna[j] = 0;
                j++;
            }while((j < tamMask) && (c != EOF));
        }
    }

    fclose(arq);
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
            mask.linha[1].coluna[1] = 1;
            mask.linha[2].coluna[1] = 1;
        break;

        case horizontal:
            mask.linha[1].coluna[0] = 1;
            mask.linha[1].coluna[1] = 1;
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
            mask.linha[1].coluna[1] = 1;
        break;

        case diagonal:
            mask.linha[0].coluna[0] = 1;
            mask.linha[0].coluna[2] = 1;
            mask.linha[2].coluna[0] = 1;
            mask.linha[2].coluna[2] = 1;
            mask.linha[1].coluna[1] = 1;
        break;

        case nordeste:
            mask.linha[0].coluna[2] = 1;
            mask.linha[1].coluna[1] = 1;
        break;

        case sudeste:
            mask.linha[2].coluna[2] = 1;
            mask.linha[1].coluna[1] = 1;
        break;

        case noroeste:
            mask.linha[0].coluna[0] = 1;
            mask.linha[1].coluna[1] = 1;
        break;

        case sudoeste:
            mask.linha[2].coluna[0] = 1;
            mask.linha[1].coluna[1] = 1;
        break;

        case personalizada:
            abrirMask(&mask);
        break;

        default:
            printf("Nenhuma mascara selecionada!\n");
        break;
        }

        mask.linha[1].coluna[1] = 1;

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

void refletirMaskP(Mascara * mask)
{
    int aux[tamMask][tamMask];
    int i, j;

    for(i = 0; i < tamMask; i++)
    {
        for(j = 0; j < tamMask; j++)
        {
            aux[i][j] = mask->linha[i].coluna[j];
        }
    }

    for(i = 0; i < tamMask; i++)
    {
        for(j = 0; j < tamMask; j++)
        {
            mask->linha[tamMask - 1 - i].coluna[tamMask - 1 - j] = aux[i][j];
        }
    }
}

Mascara refletirMask(char tipo)
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

    case sudeste:
        mask = construirMask(noroeste);
    break;

    case noroeste:
        mask = construirMask(sudoeste);
    break;

    case personalizada:
        mask = construirMask(personalizada);
        refletirMaskP(&mask);
    break;

    default:
        mask = construirMask(ponto);
    break;
    }

    return mask;
}

FILE * novoArquivoRelatorio()
{
    FILE * arq;
    char nome[11] = "rel.txt";

    arq = fopen(nome, "r");

    if(arq != NULL)
    {
        int cont = 0;
        char relatorio[] = "rel";
        char txt[] = ".txt";
        char numero[3];
        do
        {
            fclose(arq);
            limpar(nome);
            strcat(nome,relatorio);
            sprintf(numero, "%d", cont);
            strcat(nome,numero);
            strcat(nome,txt);
            arq = fopen(nome, "r");
            cont++;
        }
        while(arq != NULL);
    }
    
    arq = fopen(nome, "w");

    return arq;
}

void imprimirRelatorio(char * operacao, Mascara mask)
{
    FILE * arq;
    arq = novoArquivoRelatorio();

    int i, j;

    fprintf(arq, "Operacao: %s\n", operacao);
    fprintf(arq, "Mascara: %c\n\n", mask.tipo);

    for (i = 0; i < tamMask; i++)
    {
        for (j = 0; j < tamMask; j++)
        {
            fprintf(arq, "%d ", mask.linha[i].coluna[j]);
        }
        fprintf(arq, "\n");
    }

    fclose(arq);
}

void pintar(Imagem * resultado, int posicaoXI, int posicaoYI, int posicaoX, int posicaoY)
{
    int x = posicaoXI + posicaoX - 1;
    int y = posicaoYI + posicaoY - 1;

    if((x >= 0) && (y >= 0))
    {
        if(((x) < resultado->l) && ((y) < resultado->h)) resultado->linha[x].coluna[y] = 1;
    }
}

void fazerDil(Imagem * resultado, Mascara tipo, Linha * original, int posicaoX, int posicaoY)
{
    int meioMask = tamMask/2;

    if(original[posicaoX + meioMask].coluna[posicaoY + meioMask] == tipo.linha[meioMask].coluna[meioMask])
    {
        int i, j;

        for (i = 0; i < tamMask; i++)
        {
            for (j = 0; j < tamMask; j++)
            {
                if(tipo.linha[i].coluna[j] == 1) pintar(resultado, posicaoX, posicaoY, i, j);
            }
        }
    }
}

Imagem dilatacao(Imagem imgI, char tipo)
{
    Imagem resultado, copia;
    copia = copiaExpandida(imgI);
    resultado = pintarDeBranco(imgI);
    Mascara mask;

    mask = refletirMask(tipo);

    int i, j;

    for(i = 0; i < copia.l - tamMask; i++)
    {
        for(j = 0; j < copia.h - tamMask; j++)
        {
            fazerDil(&resultado, mask, copia.linha, i, j);
        }
    }

    imprimirRelatorio("Dilatacao", mask);
    apagarMask(&mask);
    apagarImagem(&copia);

    return resultado;
}

void fazerEro(Imagem * resultado, Mascara tipo, Linha * original, int posicaoX, int posicaoY)
{
    int i, j; 
    int meioMask = tamMask/2;

    if(original[posicaoX + meioMask].coluna[posicaoY + meioMask] == tipo.linha[meioMask].coluna[meioMask])
    {
        int z = 0;
        for (i = 0; i < tamMask; i++)
        {
            for (j = 0; j < tamMask; j++)
            {
                if((tipo.linha[i].coluna[j] == 1) && (original[posicaoX + i].coluna[posicaoY + j] != 1)) z++;
            }
        }

        if(z == 0) pintar(resultado, posicaoX, posicaoY, meioMask, meioMask);
    }
}

Imagem erosao(Imagem imgI, char tipo)
{
    Imagem resultado, copia;

    copia = copiaExpandida(imgI);
    pintarBordas(&copia);
    resultado = pintarDeBranco(imgI);
    
    Mascara mask;

    mask = construirMask(tipo);

    int i, j;

    for(i = 0; i < copia.l - tamMask; i++)
    {
        for(j = 0; j < copia.h - tamMask; j++)
        {
            fazerEro(&resultado, mask, copia.linha, i, j);
        }
    }

    imprimirRelatorio("Erosao", mask);
    apagarMask(&mask);
    apagarImagem(&copia);

    return resultado;
}

Imagem abertura(Imagem imgI, char tipo)
{
    Imagem img, aux;

    img = erosao(imgI, tipo);
    aux = img;
    img = dilatacao(img, tipo);
    apagarImagem(&aux);

    return img;
}

Imagem fechamento(Imagem imgI, char tipo)
{
    Imagem img, aux;

    img = dilatacao(imgI, tipo);
    aux = img;
    img = erosao(img, tipo);
    apagarImagem(&aux);

    return img;
}