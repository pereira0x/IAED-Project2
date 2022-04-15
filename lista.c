/* José Pereira - ist1103252 */

#include "proj.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Função auxiliar novo, responsável pela alocação de memória de tudo o
que é necessário para umareserva nova reserva. */
link novo(char *idReserva, char idVoo[], Data d, int numPassageiros)
{
    link x = (link)malloc(sizeof(struct reserva));
    if (x == NULL)
    {
        printf("No memory.\n");
        exit(1);
    }
    x->idReserva = (char *)malloc(sizeof(char) * (strlen(idReserva) + 1));
    if (x->idReserva == NULL)
    {
        printf("No memory.\n");
        exit(1);
    }
    strcpy(x->idReserva, idReserva);
    strcpy(x->idVoo, idVoo);
    x->data = d;
    x->numPassageiros = numPassageiros;
    x->proximo = NULL;
    return x;
}

/* Função auxiliar print, responsável por mostra todas as reservas. */
void print(link cabeca, char idVoo[], Data d)
{
    link t;
    for (t = cabeca; t != NULL; t = t->proximo)
        if ((strcmp(t->idVoo, idVoo) == 0) &&
            (converteDataNum(t->data) == converteDataNum(d)))
            printf("%s %d\n", t->idReserva, t->numPassageiros);
}

/* Função auxiliar insereOrdenado, responsável por adicionar uma nova reserva
na lista, ordenada. */
link insereOrdenado(link cabeca, char *idReserva, char idVoo[], Data d, int numPassageiros)
{
    link x = novo(idReserva, idVoo, d, numPassageiros);
    link current;
    if (cabeca == NULL || strcmp(cabeca->idReserva, x->idReserva) > 0)
    {
        x->proximo = cabeca;
        cabeca = x;
        return cabeca;
    }

    current = cabeca;
    while (current->proximo != NULL && strcmp(current->proximo->idReserva, x->idReserva) <= 0)
        current = current->proximo;

    x->proximo = current->proximo;
    current->proximo = x;
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

/* Função auxiliar procuraIdVoo, responsável por procura por uma certa reserva,
de um determinado voo e apagar, até nao restar nenhuma */
link procuraApagaIDVoo(link cabeca, char idVoo[])
{
    link primeiro = NULL;
    link temp;
    while (cabeca != NULL)
    {
        if (strcmp(cabeca->idVoo, idVoo) == 0)
        {
            temp = cabeca;
            cabeca = cabeca->proximo;
            free(temp->idReserva);
            free(temp);
        }
        else
        {

            if (primeiro == NULL)
                primeiro = cabeca;

            if (cabeca->proximo == NULL)
                break;

            if (strcmp(cabeca->proximo->idVoo, idVoo) == 0)
            {
                temp = cabeca->proximo;
                cabeca->proximo = cabeca->proximo->proximo;
                free(temp->idReserva);
                free(temp);
            }
            else
                cabeca = cabeca->proximo;
        }
    }
    return primeiro;
}

/* Função auxiliar apaga, responsável por apagar uma reserva*/
link apaga(link cabeca, char *idReserva)
{
    link t, prev;
    for (t = cabeca, prev = NULL; t != NULL;
         prev = t, t = t->proximo)
    {
        if (strcmp(t->idReserva, idReserva) == 0)
        {
            if (t == cabeca)
                cabeca = t->proximo;
            else
                prev->proximo = t->proximo;
            free(t->idReserva);
            free(t);
            break;
        }
    }
    return cabeca;
}

/* Função auxiliar apagaTodasReservas, responsável por apagar todas todas
as reversas.*/
void apagaTodasReservas(link cabeca)
{
    Reserva *reserva = cabeca;
    Reserva *proximo;

    while (reserva != NULL)
    {
        proximo = reserva->proximo;
        free(reserva->idReserva);
        free(reserva);
        reserva = proximo;
    }
    cabeca = NULL;
}
