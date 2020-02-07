#include "headers/imagem.h"

typedef struct linha
{
    int * coluna;
}Linha;

typedef struct imagem
{
    int h;
    int l;
    Linha * linha;
}Imagem;

void primeiraIni(Imagem * img)
{
    img->linha = NULL;
}

void inicializarImagem(Imagem * i, int l, int h, Linha * linha)
{
    i->h = h;
    i->l = l;
    i->linha = linha;
}

Imagem copiarImagem(Imagem img)
{
    Imagem copia;
    Linha * linha;
    linha = (Linha *) malloc(img.l * (sizeof(Linha)));
    inicializarImagem(&copia, img.l, img.h, linha);

    int i,j;

    for(i = 0; i < img.l; i++)
    {
        copia.linha[i].coluna = (int *) malloc(copia.h * (sizeof(int)));
        for (j= 0; j < img.h; j++)
        {
            copia.linha[i].coluna[j] = img.linha[i].coluna[j];
        }
    }

    return copia;
}

Imagem copiaExpandida(Imagem img)
{
    Imagem copia;
    Linha * linha;
    linha = (Linha *) malloc((img.l + 3) * (sizeof(Linha)));
    inicializarImagem(&copia, img.l + 3, img.h + 3, linha);

    int i, j;

    for(i = 0; i < copia.l; i++)
    {
        copia.linha[i].coluna = (int *) calloc(copia.h, sizeof(int));
    }

    for(i = 1; i <= img.l; i++)
    {
        for(j = 1; j <= img.h; j++)
        {
            copia.linha[i].coluna[j] = img.linha[i - 1].coluna[j - 1];
        }
    }

    return copia;
}

void pintarBordas(Imagem * img)
{
    int i;

    for(i = 0; i < img->h; i++)
    {
        img->linha[0].coluna[i] = 1;
        img->linha[img->l -1].coluna[i] = 1;
        img->linha[img->l -2].coluna[i] = 1;
    }

    for(i = 0; i < img->l; i++)
    {
        img->linha[i].coluna[0] = 1;
        img->linha[i].coluna[img->h -1] = 1;
        img->linha[i].coluna[img->h -2] = 1;
    }
}

Imagem pintarDeBranco(Imagem img)
{
    Imagem vazia;
    Linha * linha;
    linha = (Linha *) malloc(img.l * (sizeof(Linha)));
    inicializarImagem(&vazia, img.l, img.h, linha);

    int i;

    for (i = 0; i < vazia.l; i++)
    {
        vazia.linha[i].coluna = (int *) calloc(vazia.h, sizeof(int));
    }
    

    return vazia;
}

void apagarImagem(Imagem * img)
{
    int i;

    for(i = 0; i < img->l; i++)
    {
        free(img->linha[i].coluna);
    }

    free(img->linha);
    img->linha = NULL;
    img->h = 0;
    img->l = 0;
}

Imagem abrir(char nome[])
{
    FILE * arq;
    Imagem img;
    arq = fopen(nome, "r");

    if(arq != NULL)
    {
        int h, l;
        Linha * linha;

        fscanf(arq, "%*s\n %*[^\n]\n %d %d\n", &h, &l);

        linha = (Linha*) malloc(l * (sizeof(Linha)));

        inicializarImagem(&img, l, h, linha);

        int i,j;

        for(i = 0; i < img.l; i++)
        {
            img.linha[i].coluna = (int *) malloc(img.h * (sizeof(int)));
            j = 0;
            char c;
            do
            {
                fscanf(arq, " %c", &c);
                if(c == '1') img.linha[i].coluna[j] = 1;
                else img.linha[i].coluna[j] = 0;
                
                j++;
                
            }while((j < img.h) && (c != EOF));
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

FILE * novoArquivoPBM()
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

FILE * novoArquivoPGM()
{
    FILE * arq;
    char nome[11] = "img.pgm";

    arq = fopen(nome, "r");

    if(arq != NULL)
    {
        int cont = 0;
        char imagem[] = "img";
        char pgm[] = ".pgm";
        char numero[3];
        do
        {
            fclose(arq);
            limpar(nome);
            strcat(nome,imagem);
            sprintf(numero, "%d", cont);
            strcat(nome,numero);
            strcat(nome,pgm);
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

    arq = novoArquivoPBM();

    if(img.linha != NULL)
    {
        fprintf(arq, "P1\n");
        fprintf(arq, "# editado por: MJLC\n");
        fprintf(arq, "%d %d\n", img.h, img.l);

        int i, j, k;
        k = 0;
        for(i = 0; i < img.l; i++)
        {
            for(j = 0; j < img.h; j++)
            {
                fprintf(arq, "%d", img.linha[i].coluna[j]);
                k++;
                if(k % 70 == 0) fprintf(arq, "\n");
            }
        }
    }   

    fclose(arq); 
}

void salvarPGM(Imagem img)
{
    FILE * arq;

    arq = novoArquivoPGM();

    if(img.linha != NULL)
    {
        fprintf(arq, "P2\n");
        fprintf(arq, "# editado por: MJLC\n");
        fprintf(arq, "%d %d\n", img.h, img.l);
        fprintf(arq, "255\n");

        int i, j;
        for(i = 0; i < img.l; i++)
        {
            for(j = 0; j < img.h; j++)
            {
                if(img.linha[i].coluna[j] == 1) fprintf(arq, "0\n");
                else fprintf(arq, "255\n");
            }
        }
    }   

    fclose(arq); 
}
