#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct coluna
{
    int * linha;
}Coluna;

typedef struct imagem
{
    int h;
    int l;
    Coluna * coluna;
}Imagem;

void inicializarImagem(Imagem * i, int h, int l, Coluna * coluna)
{
    i->h = h;
    i->l = l;
    i->coluna = coluna;
}

Imagem copiarImagem(Imagem img)
{
    Imagem copia;
    Coluna * coluna;
    coluna = (Coluna*) malloc(img.h*(sizeof(Coluna)));
    inicializarImagem(&copia, img.h, img.l, coluna);

    int i,j;

    for(i = 0; i < img.h; i++)
    {
        copia.coluna[i].linha = (int *) malloc(copia.l*(sizeof(int)));
        for (j= 0; j < img.l; j++)
        {
            copia.coluna[i].linha[j] = img.coluna[i].linha[j];
        }
    }

    return copia;
}

Imagem canvas(Imagem img)
{
    Imagem branco;
    Coluna * coluna;
    coluna = (Coluna*) malloc((img.h)*(sizeof(Coluna)));
    inicializarImagem(&branco, img.h, img.l, coluna);

    int i,j;

    for(i = 0; i < branco.h; i++)
    {
        branco.coluna[i].linha = (int *) malloc(branco.l * (sizeof(int)));
        for (j = 0; j < branco.l; j++)
        {
            branco.coluna[i].linha[j] = 0;
        }
    }

    return branco;
}

Imagem abrir(char nome[])
{
    FILE * arq;
    Imagem img;
    arq = fopen(nome, "r");

    if(arq != NULL)
    {
        int h, l;
        Coluna * coluna;

        fscanf(arq, "%*s\n %*[^\n]\n %d %d\n", &h, &l);

        coluna = (Coluna*) malloc(h*(sizeof(Coluna)));

        inicializarImagem(&img, h, l, coluna);

        int i,j;

        for(i = 0; i < img.h; i++)
        {
            img.coluna[i].linha = (int *) malloc(img.l * (sizeof(int)));
            j = 0;
            char c;
            do
            {
                fscanf(arq, " %c", &c);
                if((c == '0') || (c == '1'))
                {
                    img.coluna[i].linha[j] = c - '0';
                    j++;
                }
            }while(j < img.l);
        }
    }

    fclose(arq);

    return img;
}

void limpar(char * str)
{
    int cont = 0;
    for(cont; strlen(str); cont++)
    {
        str[cont] = '\0';
    }
}

FILE * novoArquivo()
{
    FILE * arq;
    char nome[11] = "img.pbm";

    arq = fopen(nome, "r");

    if(arq != NULL)
    {
        int cont = 0;
        char imagem[] = "img";
        char ppm[] = ".pbm";
        char numero[3];
        do
        {
            fclose(arq);
            limpar(nome);
            strcat(nome,imagem);
            sprintf(numero, "%d", cont);
            strcat(nome,numero);
            strcat(nome,ppm);
            arq = fopen(nome,"r");
            cont++;
        }
        while(arq != NULL);
    }
    
    arq = fopen(nome, "w");

    return arq;
}

void salvarPBM(Imagem img)
{
    FILE * arq;

    arq = novoArquivo();

    

    if(img.coluna != NULL)
    {
        fprintf(arq, "P1\n");
        fprintf(arq, "# editado por: MJLC\n");
        fprintf(arq, "%d %d\n", img.h, img.l);

        int i, j, k;
        k = 0;
        for(i = 0; i < img.h; i++)
        {
            for(j = 0; j < img.l; j++)
            {
                fprintf(arq, "%d", img.coluna[i].linha[j]);
                k++;
                if(k % 70 == 0) fprintf(arq, "\n");
            }
        }
    }   

    fclose(arq); 
}