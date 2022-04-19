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
    if (reserva_len < MIN_IDRESERVA)
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
        printf(ERROR_ALREADY_USED, idReserva);
    else if (_voos[index].ocupacao + numPassageiros > _voos[index].capacidade)
        printf(ERROR_TO_MANY_RESERVATIONS);
    else if (validaData(d) == FALSE)
        printf(ERROR_INVALID_DATE);
    else if (validaPassageiros(numPassageiros) == FALSE)
        printf(ERROR_INVALID_PASSENGER_NUMBER);
    else
    {
        _voos[index].ocupacao += numPassageiros;
        _numReservas++;
        cabeca = insereOrdenado(cabeca, idReserva, idVoo, d, numPassageiros);
    }
}

/* Função responsável por apagar uma reserva */
void apagaReserva(char idReserva[])
{
    cabeca = apaga(cabeca, idReserva);
    if (acontecimento == 0)
        printf(ERROR_NOT_FOUND);
}
