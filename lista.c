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
    bubbleSortList(cabeca);
    for (t = cabeca; t != NULL; t = t->proximo)
        printf("%s %d\n", t->idReserva, t->numPassageiros);
}

/* Função auxiliar insereFim, responsável por adicionar uma nova reserva
no fim da lista. */
link insereFim(link cabeca, char *idReserva, char idVoo[], Data data, int numPassageiros)
{
    link x;
    if (cabeca == NULL)
        return novo(idReserva, idVoo, data, numPassageiros);
    /*loop para chegar ao fim da lista*/
    for (x = cabeca; x->proximo != NULL; x = x->proximo)
        ;
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

/* Função auxiliar bubbleSortList, responsável por orderar as reservas
por ordem lexicografica. */
void bubbleSortList(link cabeca)
{
    int trocado, tamanho;
    Reserva *reserva;
    Reserva *ultReserva = NULL;

    /* Verifica se a lista é vazia */
    if (cabeca == NULL)
        return;

    do
    {
        trocado = 0;
        reserva = cabeca;

        while (reserva->proximo != ultReserva)
        {
            if (strcmp(reserva->idReserva, reserva->proximo->idReserva) > 0)
            {
                printf("TROCA:\n");
                printf("%s para %s\n", reserva->idReserva, reserva->proximo->idReserva);
                tamanho = strlen(reserva->idReserva);
                troca(reserva, reserva->proximo, tamanho);
                trocado = 1;
            }
            reserva = reserva->proximo;
        }
        ultReserva = reserva;
    } while (trocado);
}

/* Função auxiliar troca, responsável por trocar a ordem de duas reservas.*/
void troca(Reserva *a, Reserva *b, int tamanho)
{
    char *temp;
    int auxNumPassegeiros;
    Data auxData;
    char auxIdVoo[MAX_CODIGO_VOO];
    temp = (char *)malloc(sizeof(char) * tamanho + 1);
    /* troca ID reserva */
    strcpy(temp, a->idReserva);
    strcpy(a->idReserva, b->idReserva);
    strcpy(b->idReserva, temp);

    /* troca numero de passageiros */
    auxNumPassegeiros = a->numPassageiros;
    a->numPassageiros = b->numPassageiros;
    temp = (char *)malloc(sizeof(char) * tamanho + 1);
    b->numPassageiros = auxNumPassegeiros;

    /* troca data */
    auxData = a->data;
    a->data = b->data;
    b->data = auxData;

    /* troca Id voo */
    strcpy(auxIdVoo, a->idVoo);
    strcpy(a->idVoo, b->idVoo);
    strcpy(b->idVoo, auxIdVoo);

    free(temp);
}

/* Função auxiliar apaga, responsável por apagar uma reserva*/
link apaga(link cabeca, char *idReserva)
{
    link t, prev;
    for (t = cabeca, prev = NULL; t != NULL;
         prev = t, t = t->proximo)
    {
        if (strcmp(t->proximo->idReserva, idReserva) == 0)
        {
            if (t == cabeca)
                cabeca = t->proximo;
            else
                prev->proximo = t->proximo;
            free(t->proximo);
            free(t);
            break;
        }
    }
    return cabeca;
}