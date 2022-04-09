#include "proj.h"
#include <stdio.h>
#include <string.h>
/* Funcoes Voos */

/* Função que mostra um voo */
void mostraVoo(int index)
{
    printf("%s %s %s ", _voos[index].id, _voos[index].partida,
           _voos[index].chegada);
    mostraData(_voos[index].data);
    printf(" ");
    mostraHora(_voos[index].hora);
    printf("\n");
}

/* Função que mostra um voo de partida */
void mostraVooPartida(int index)
{
    printf("%s %s ", _voos[index].id, _voos[index].chegada);
    mostraData(_voos[index].data);
    printf(" ");
    mostraHora(_voos[index].hora);
    printf("\n");
}

/* Função que mostra um voo de chegada */
void mostraVooChegada(int index)
{
    Hora h = converteNumHora(_voos[index].horaChegada);
    printf("%s %s ", _voos[index].id, _voos[index].partida);
    mostraData(converteNumData(_voos[index].horaChegada));
    printf(" ");
    mostraHora(h);
    printf("\n");
}

/* Função que encontra um voo com um dado id e uma dada data, caso exista. */
int encontraVoo(char id[], Data d)
{
    int numData = converteDataNum(d);
    int i;

    for (i = 0; i < _numVoos; i++)
        if (!strcmp(id, _voos[i].id) && numData == converteDataNum(_voos[i].data))
            return i;
    return NAO_EXISTE;
}

/* Função que verifica se um id de aeroporto é válido */
int validaIDVoo(char id[])
{
    int i = 0, l = strlen(id);
    if (l < 3)
        return FALSE;
    for (i = 0; i < 2; i++)
        if (!(id[i] >= 'A' && id[i] <= 'Z'))
            return FALSE;

    while (id[i] != '\0')
    {
        if (!(id[i] >= '0' && id[i] <= '9'))
            return FALSE;
        i++;
    }
    return TRUE;
}

/* Função que verifica se um voo é válido */
int validaVoo(Voo v)
{
    if (validaIDVoo(v.id) == FALSE)
        printf("invalid flight code\n");
    else if (encontraVoo(v.id, v.data) != NAO_EXISTE)
        printf("flight already exists\n");
    else if (encontraAeroporto(v.partida) == NAO_EXISTE)
        printf("%s: no such airport ID\n", v.partida);
    else if (encontraAeroporto(v.chegada) == NAO_EXISTE)
        printf("%s: no such airport ID\n", v.chegada);
    else if (_numVoos == MAX_NUM_VOOS)
        printf("too many flihts\n");
    else if (validaData(v.data) == FALSE)
        printf("invalid date\n");
    else if (validaHora(v.duracao) == FALSE)
        printf("invalid duration\n");
    else if (v.capacidade < 10 || v.capacidade > 100)
        printf("invalid capacity\n");
    else
        return TRUE;
    return FALSE;
}

/* Função que cria um voo */
void criaVoo(Voo v)
{
    strcpy(_voos[_numVoos].id, v.id);
    strcpy(_voos[_numVoos].partida, v.partida);
    strcpy(_voos[_numVoos].chegada, v.chegada);
    _voos[_numVoos].data = v.data;
    _voos[_numVoos].hora = v.hora;
    _voos[_numVoos].duracao = v.duracao;
    _voos[_numVoos].capacidade = v.capacidade;
    _voos[_numVoos].horaPartida =
        converteDataHoraNum(_voos[_numVoos].data,
                            _voos[_numVoos].hora);
    _voos[_numVoos].horaChegada =
        _voos[_numVoos].horaPartida +
        converteHoraNum(_voos[_numVoos].duracao);
    _numVoos++;
}

/* Função que compara a hora de partida de dois aeroportos */
int cmpVoosPartida(int a, int b)
{
    return (_voos[a].horaPartida > _voos[b].horaPartida);
}

/* Função que compara a hora de chegada de dois aeroportos */
int cmpVoosChegada(int a, int b)
{
    return (_voos[a].horaChegada > _voos[b].horaChegada);
}

int encontraVooSemData(char id[])
{
    int i;
    for (i = 0; i < _numVoos; i++)
        if (!strcmp(id, _voos[i].id))
            return i;
    return NAO_EXISTE;
}