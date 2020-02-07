#include "headers/interface.h"

void limparTela()
{
    system("cls");
}

char menuOperacoes()
{
    printf("Selecione a operacao:\n");
    printf("Dilatacao: d\n");
    printf("Erosao: e\n");
    printf("Abertura: a\n");
    printf("Fechamento: f\n");
    printf("Salvar: s\n");
    printf("Abrir arquivo: o\n");
    printf("Retornar Imagem: r\n");
    printf("Sair: q\n");

    char operacao;
    scanf(" %c", &operacao);
    limparTela();
    return operacao;
}

Imagem abrirArquivo()
{
    Imagem imgI;
    char nome[100];

    printf("Diga o nome do arquivo:\n");
    scanf(" %[^\n]", nome);

    imgI = abrir(nome);

    limparTela();

    return imgI;
}

char selecionarMask()
{
    printf("Selecione a mascara utilizada:\n");
    printf("Norte, cima: n\n");
    printf("Sul, baixo: s\n");
    printf("Leste, direita: l\n");
    printf("Oeste, esquerda: e\n");
    printf("Cruz, intersecao vertical e horizontal: c\n");
    printf("Vertical: v\n");
    printf("Horizontal: h\n");
    printf("Diagonal: d\n");
    printf("Nordeste: 1\n");
    printf("Noroeste: 2\n");
    printf("Sudeste: 3\n");
    printf("Sudoeste: 4\n");
    printf("Personalizada (necessita do arquivo mask.txt preenchido com uma matriz 3x3 na pasta do executavel!): p\n");

    char mask;
    scanf(" %c", &mask);
    limparTela();
    return mask;
}

void iniciarInterface()
{
    char chave = '1';
    Imagem img, anterior, anteanterior;
    primeiraIni(&img);
    primeiraIni(&anterior);
    primeiraIni(&anteanterior);

    do
    {
        char operacao = menuOperacoes();

        switch (operacao)
        {
        case 'd':

            if(img.linha != NULL) 
            {
                apagarImagem(&anteanterior);
                anteanterior = copiarImagem(anterior);
                apagarImagem(&anterior);
                anterior = copiarImagem(img);
                apagarImagem(&img);
                img = dilatacao(anterior, selecionarMask());
            }
            else printf("Nenhum arquivo foi aberto!");

            break;

        case 'e':

            if(img.linha != NULL) 
            {
                apagarImagem(&anteanterior);
                anteanterior = copiarImagem(anterior);
                apagarImagem(&anterior);
                anterior = copiarImagem(img);
                apagarImagem(&img);
                img = erosao(anterior, selecionarMask());
            }
            else printf("Nenhum arquivo foi aberto!");

            break;

        case 'a':

            if(img.linha != NULL) 
            {
                apagarImagem(&anteanterior);
                anteanterior = copiarImagem(anterior);
                apagarImagem(&anterior);
                anterior = copiarImagem(img);
                apagarImagem(&img);
                img = abertura(anterior, selecionarMask());
            }
            else printf("Nenhum arquivo foi aberto!");

            break;

        case 'f':

            if(img.linha != NULL) 
            {
                apagarImagem(&anteanterior);
                anteanterior = copiarImagem(anterior);
                apagarImagem(&anterior);
                anterior = copiarImagem(img);
                apagarImagem(&img);;
                img = fechamento(anterior, selecionarMask());
            }
            else printf("Nenhum arquivo foi aberto!");
            
            break;

        case 'o':
            img = abrirArquivo();
            anterior = copiarImagem(img);
            anteanterior = copiarImagem(img);
            break;

        case 's':
            salvarPBM(img);
            break;

        case 'q':
            chave = '0';
            break;

        case 'r':
            apagarImagem(&img);
            img = copiarImagem(anterior);
            apagarImagem(&anterior);
            anterior = anteanterior;

            break;

        default:
            printf("Comando Invalido!\n");
            getchar();
            break;
        }

        limparTela();
        
    } while (chave == '1');
}
