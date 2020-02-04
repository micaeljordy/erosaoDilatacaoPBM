#include "filtro.h"

int main()
{
    Imagem i;
    char nome[11];

    printf("Diga o nome do arquivo:\n");
    scanf(" %[^\n]", nome);

    i = abrir(nome);

    Imagem img;

    img = erosao(i, oeste);
    img = dilatacao(img, oeste);
    img = dilatacao(img, norte);
    img = erosao(img, sul);

    salvarPBM(img);

    return 0;
}