/* José Pereira - ist1103252 */

#include "proj.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Função auxiliar novo, responsável pela alocação de memória de tudo o
que é necessário para umareserva nova reserva. */
link novo(char *idReserva, char idVoo[], Data d, int numPassageiros)
{
    link reserva = (link)malloc(sizeof(struct reserva));
    /* Caso nao exista memória suficiente para criar a reserva */
    if (reserva == NULL)
    {
        printf("No memory.\n");
        exit(1);
    }

    reserva->idReserva = (char *)malloc(sizeof(char) * (strlen(idReserva) + 1));
    /* Caso nao exista memória suficiente para criar o idReserva */
    if (reserva->idReserva == NULL)
    {
        printf("No memory.\n");
        exit(1);
    }
    /* Atribui os dados à reserv. */
    strcpy(reserva->idReserva, idReserva);
    strcpy(reserva->idVoo, idVoo);
    reserva->data = d;
    reserva->numPassageiros = numPassageiros;
    reserva->proximo = NULL;
    _voos[encontraVoo(idVoo, d)].numReservas += 1;
    return reserva;
}

/* Função auxiliar print, responsável por mostra todas as reservas de um
certo voo. */
void print(link cabeca, char idVoo[], Data d)
{
    link temporario;
    int num_reservas = _voos[encontraVoo(idVoo, d)].numReservas;
    for (temporario = cabeca; temporario != NULL;
         temporario = temporario->proximo)
        if ((strcmp(temporario->idVoo, idVoo) == 0) &&
            (converteDataNum(temporario->data) == converteDataNum(d)) &&
            num_reservas > 0)
        {
            printf("%s %d\n", temporario->idReserva, temporario->numPassageiros);
            num_reservas--;
        }
}

/* Função auxiliar insereOrdenado, responsável por adicionar uma nova reserva
na lista de forma ordenada. */
link insereOrdenado(link cabeca, char *idReserva, char idVoo[], Data d, int numPassageiros)
{
    link atual, reserva = novo(idReserva, idVoo, d, numPassageiros);
    /* Primeira posição */
    if (cabeca == NULL || strcmp(cabeca->idReserva, reserva->idReserva) > 0)
    {
        reserva->proximo = cabeca;
        return cabeca = reserva;
    }

    atual = cabeca;
    /* Procura onde inserir a nova reserva */
    while (atual->proximo != NULL &&
           strcmp(atual->proximo->idReserva, reserva->idReserva) <= 0)
        atual = atual->proximo;

    /* Insere a nova reserva */
    reserva->proximo = atual->proximo;
    atual->proximo = reserva;
    return cabeca;
}

/* Função auxiliar procura, responsável por procurar por uma certa reserva. */
link procura(link cabeca, char *idReserva)
{
    link temporario;
    for (temporario = cabeca; temporario != NULL;
         temporario = temporario->proximo)
        if (strcmp(temporario->idReserva, idReserva) == 0)
            return temporario;
    /* Caso tal reserva nao exista, retorna NULL */
    return NULL;
}

/* Função auxiliar procuraApagaIdVoo, responsável por procurar e apagar todas
as reservas determinado voo */
link procuraApagaIDVoo(link cabeca, char idVoo[])
{
    link temporario, primeiro = NULL;
    int reservasTotais = reservasTotalVoo(idVoo);
    while (cabeca != NULL)
    {
        /* Caso já nao haja mais reservas a apagar */
        if (reservasTotais == 0)
            break;
        if (strcmp(cabeca->idVoo, idVoo) == 0)
        {
            reservasTotais--;
            temporario = cabeca;
            cabeca = cabeca->proximo;
            free(temporario->idReserva);
            free(temporario);
        }
        else
        {
            if (primeiro == NULL)
                primeiro = cabeca;
            if (cabeca->proximo == NULL)
                break;
            if (strcmp(cabeca->proximo->idVoo, idVoo) == 0)
            {
                reservasTotais--;
                temporario = cabeca->proximo;
                cabeca->proximo = cabeca->proximo->proximo;
                free(temporario->idReserva);
                free(temporario);
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
    link reserva, anterior;
    int i;
    /* Caso nao seja apagada nenhuma reserva, 'acontecimento' mantem-se a 0 */
    acontecimento = 0;
    for (reserva = cabeca, anterior = NULL; reserva != NULL; anterior = reserva,
        reserva = reserva->proximo)
    {
        if (strcmp(reserva->idReserva, idReserva) == 0)
        {
            acontecimento += 1;
            /* Remove a ocupação provocada pela reserva */
            i = encontraVoo(reserva->idVoo, reserva->data);
            _voos[i].ocupacao -= reserva->numPassageiros;
            if (reserva == cabeca)
                cabeca = reserva->proximo;
            else
                anterior->proximo = reserva->proximo;
            free(reserva->idReserva);
            free(reserva);
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
