#include "proj.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/* Função auxiliar novo, responsável pela alocação de memória de tudo o
que é necessário para uma nova reserva. */
link novo(char *idReserva, char idVoo[], Data data, int numPassageiros)
{
    link x = (link)malloc(sizeof(struct reserva));
    x->idReserva =
        (char *)malloc(sizeof(char) * (strlen(idReserva) + 1));
    strcpy(x->idReserva, idReserva);
    strcpy(x->idVoo, idVoo);
    x->data = data;
    x->numPassageiros = numPassageiros;
    x->proximo = NULL;
    return x;
}

/* Função auxiliar print, responsável por mostra todas as reservas. */
void print(link cabeca)
{
    link t;
    for (t = cabeca; t != NULL; t = t->proximo)
    {
        printf("%s %d\n", t->idReserva, t->numPassageiros);
    }
}

/* Função auxiliar insereInicio, responsável por adicionar uma nova reserva
no inicio da lista. */
link insereInicio(link cabeca, char *idReserva, char idVoo[], Data data, int numPassageiros)
{
    link x = novo(idReserva, idVoo, data, numPassageiros);
    x->proximo = cabeca;
    return x; /*retorna a nova "head"*/
}

/* Função auxiliar insereFim, responsável por adicionar uma nova reserva
no fim da lista. */
link insereFim(link cabeca, char *idReserva, char idVoo[], Data data, int numPassageiros)
{
    link x;
    if (cabeca == NULL)
        return novo(idReserva, idVoo, data, numPassageiros);
    /*loop para chegar ao fim da lista*/
    for (x = cabeca; x->proximo != NULL; x = x->proximo);
    x->proximo = novo(idReserva, idVoo, data, numPassageiros);
    return cabeca;
}

/* Função auxiliar procura, responsável por procurar por uma certa reserva. */
link procura(link cabeca, char *idReserva)
{
    link t;
    for (t = cabeca; t != NULL; t = t->proximo)
        if (strcmp(t->idReserva, idReserva) == 0)
            return t;
    return NULL;
}