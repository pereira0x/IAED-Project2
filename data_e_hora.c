#include "proj.h"
#include <stdio.h>

/* Funções de datas e horas */

/* Função que mostra uma data */
void mostraData(Data d)
{
    printf("%02d-%02d-%02d", d.dia, d.mes, d.ano);
}

/* Função que mostra uma hora */
void mostraHora(Hora h)
{
    printf("%02d:%02d", h.hora, h.minuto);
}

/* Função que converte uma data num número */
int converteDataNum(Data d)
{
    return (d.ano - ANO_INICIO) * DIAS_ANO + _diasMesAc[d.mes - 1] +
           d.dia - 1;
}

/* Função que converte uma hora num número */
int converteHoraNum(Hora h)
{
    return ((h.hora * MINUTOS_HORA) + h.minuto);
}

/* Função que converte uma data e uma hora num número */
int converteDataHoraNum(Data d, Hora h)
{
    return converteDataNum(d) * MINUTOS_DIA + converteHoraNum(h);
}

/* Função que converte um número numa hora */
Hora converteNumHora(int num)
{
    Hora h;
    h.minuto = num % MINUTOS_HORA;
    h.hora = ((num - h.minuto) / MINUTOS_HORA) % HORAS_DIA;
    return h;
}

/* Função que converte um número numa data */
Data converteNumData(int num)
{
    Data d;
    int i = 0;
    num = (num - (num % MINUTOS_DIA)) / MINUTOS_DIA;
    d.ano = (num / DIAS_ANO) + ANO_INICIO;
    num = num - ((d.ano - ANO_INICIO) * DIAS_ANO);
    while (i <= 11 && num >= _diasMesAc[i])
        i++;
    d.mes = i;
    d.dia = num - _diasMesAc[i - 1] + 1;
    return d;
}

/* Função que verifica se uma data é válida */
int validaData(Data d)
{
    int numData = converteDataNum(d);
    Data proximoAno = _hoje;
    proximoAno.ano++;
    return !(numData < converteDataNum(_hoje) ||
             numData > converteDataNum(proximoAno));
}

/* Função que verifica se uma hora é válida */
int validaHora(Hora h)
{
    return !(h.hora > 12 || (h.hora == 12 && h.minuto > 0));
}