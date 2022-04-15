/* José Pereira - ist1103252 */

#include "proj.h"
#include <string.h>
#include <stdio.h>

/* Função que verifica se o número de passageiros é válido */
int validaPassageiros(int numPassageiros)
{
    return numPassageiros > 0;
}

/* Função que verifica se um id de reserva é válido */
int validaIdReserva(char idReserva[])
{
    int i, reserva_len = strlen(idReserva);
    if (reserva_len < 10)
        return FALSE;
    for (i = 0; i < reserva_len; i++)
    {
        if (idReserva[i] >= 'A' && idReserva[i] <= 'Z')
            continue;
        else if (idReserva[i] >= '0' && idReserva[i] <= '9')
            continue;
        else
            return FALSE;
    }
    return TRUE;
}

/* Função auxilar à função adicionaReserva. Adiciona, caso seja válido, uma
reserva à lista. */
void adicionaReservaAux(char idReserva[], char idVoo[], Data d,
                        int numPassageiros)
{
    int index;
    index = encontraVoo(idVoo, d);
    if (procura(cabeca, idReserva) != NULL)
        printf("%s: flight reservation already used\n", idReserva);
    else if (_voos[index].ocupacao + numPassageiros > _voos[index].capacidade)
        printf("too many reservations\n");
    else if (validaData(d) == FALSE)
        printf("invalid date\n");
    else if (validaPassageiros(numPassageiros) == FALSE)
        printf("invalid passenger number\n");
    else
    {
        _voos[index].ocupacao += numPassageiros;
        _numReservas++;
        cabeca = insereInicio(cabeca, idReserva, idVoo, d, numPassageiros);
        bubbleSortList(cabeca);
    }
}

/* Função responsável por apagar uma reserva */
void apagaReserva(char idReserva[])
{
    int i;
    link reserva;
    reserva = procura(cabeca, idReserva);
    if (reserva == NULL)
        printf("not found\n");
    else
    {
        i = encontraVoo(reserva->idVoo, reserva->data);
        _voos[i].ocupacao -= reserva->numPassageiros;
        cabeca = apaga(cabeca, idReserva);
    }
}


