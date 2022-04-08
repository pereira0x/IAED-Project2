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
void adicionaReservaAux(char idReserva[], char idVoo[], Data d, int numPassageiros)
{
    int index;
    index = encontraVoo(idVoo, d);
    if (validaIdReserva(idReserva) == FALSE)
        printf("invalid reservation code\n");
    else if (validaPassageiros(numPassageiros) == FALSE)
        printf("invalid passager number\n");
    else if (procura(cabeca, idReserva) != NULL)
        printf("%s: flight reservation already used", idReserva);
    else if (_voos[index].ocupacao + numPassageiros > _voos[index].capacidade)
        printf("too many reservations\n");
    else
    {
        _voos[index].ocupacao += numPassageiros;
        cabeca = insereFim(cabeca, idReserva, idVoo, d, numPassageiros);
    }
}