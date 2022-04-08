#include "proj.h"
#include <stdio.h>

/* Funções de Leitura */

/* Função que lê uma hora. */
Hora leHora()
{
    Hora h;
    scanf("%d:%d", &h.hora, &h.minuto);
    return h;
}

/* Função que lê uma daata. */
Data leData()
{
    Data d;
    scanf("%d-%d-%d", &d.dia, &d.mes, &d.ano);
    return d;
}

/* Função que lê uma palavra */
int leProximaPalavra(char str[])
{
    char c = getchar();
    int i = 0;
    while (c == ' ' || c == '\t')
        c = getchar();
    while (c != ' ' && c != '\t' && c != '\n')
    {
        str[i++] = c;
        c = getchar();
    }
    str[i] = '\0';
    return (c == '\n');
}

/* Função que lê palavras até ao fim de linha */
void lePalavraAteFimDeLinha(char str[])
{
    char c = getchar();
    int i = 0;
    while (c == ' ' || c == '\t')
        c = getchar();
    while (c != '\n')
    {
        str[i++] = c;
        c = getchar();
    }
    str[i] = '\0';
}

/* Função que lê até ao fim de linha */
void leAteFimDeLinha()
{
    char c = getchar();
    while (c != '\n')
        c = getchar();
}