#include "proj.h"
#include <stdio.h>
#include <string.h>
/* Funcoes Aeroportos */

/* Função que verifica se um id de aeroporto é válido */
int aeroportoInvalido(char id[])
{
    int i;
    for (i = 0; id[i] != '\0'; i++)
        if (!(id[i] >= 'A' && id[i] <= 'Z'))
            return TRUE;
    return FALSE;
}
/* Função que encontra o aeroporto com um dado id, caso este exista */
int encontraAeroporto(char id[])
{
    int i;
    for (i = 0; i < _numAeroportos; i++)
        if (!strcmp(id, _aeroportos[i].id))
            return i;
    return NAO_EXISTE;
}

/* Função que mostra um aeroporto */
void mostraAeroporto(int index)
{
    printf("%s %s %s %d\n", _aeroportos[index].id,
           _aeroportos[index].cidade, _aeroportos[index].pais,
           _aeroportos[index].numVoos);
}

/* Função que compara dois aeroportos pelos seus ids */
int cmpAeroportos(int a, int b)
{
    return (strcmp(_aeroportos[a].id, _aeroportos[b].id) > 0);
}

/* Função que lista todos os aeroportos, ordenados por ordem alfabética do id */
void listaTodosAeroportos()
{
    int i;
    int indexAeroportos[MAX_NUM_AEROPORTOS];

    for (i = 0; i < _numAeroportos; i++)
        indexAeroportos[i] = i;

    bubbleSort(indexAeroportos, _numAeroportos, cmpAeroportos);

    for (i = 0; i < _numAeroportos; i++)
        mostraAeroporto(indexAeroportos[i]);
}
