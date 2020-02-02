#include "filtro.h"

int main()
{
    Imagem img, img2;
    char nome[50];
    char tipo, tipo2;
    //int v;

    printf("Diga o nome do arquivo:\n");
    scanf(" %[^\n]", nome);

    /*
    printf("Diga o tipo da mascara dilatacao:\n");
    scanf(" %c", &tipo);
    printf("Diga o tipo da mascara erosao:\n");
    scanf(" %c", &tipo2);
    printf("Repeticoes:\n");
    scanf(" %d", &v);
    */

    img = abrir(nome);
    img2 = erosao(img, leste);
    img2 = dilatacao(img2, oeste);
    img2 = erosao(img2, oeste);
    img2 = dilatacao(img2, leste);
    
    /*
    int cont;
    for(cont = 0; cont < v; cont++)
    { 
        img2 = dilatacao(img2, tipo);
        img2 = erosao(img2, tipo2);
    }
    */
    

    salvarPBM(img2);
    return 0;
}