#include "filtro.h"

int main()
{
    Imagem imgI;
    char nome[11];

    printf("Diga o nome do arquivo:\n");
    scanf(" %[^\n]", nome);

    imgI = abrir(nome);

    Imagem img;

    img = abertura(imgI);
    img = fechamento(img);

    salvarPBM(img);

    return 0;
}