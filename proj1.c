/* José Pereira - ist1103252 */

#include "proj.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Variaveis Globais */

int _numAeroportos = 0;					   /* número de aeroportos introduzidos */
Aeroporto _aeroportos[MAX_NUM_AEROPORTOS]; /* vetor de aeroportos */

int _numVoos = 0 /* número de voos introduzidos */;

Voo _voos[MAX_NUM_VOOS]; /* vetor de voos */

Data _hoje = {1, 1, 2022}; /* data atual do sistema */

const int _diasMesAc[] = /* dias acumulados por mês (jan=1) */
	{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

int _numReservas = 0; /* Número de reservas */

int acontecimento; /* Variavel usada para verificar se algo aconteceu */

link cabeca = NULL; /* cabeca da lista simplesmente ligada é NULL */

/**
 * Comando 'a' - adiciona um novo aeroporto ao sistema.
 * Formato de entrada: a <IDAeroporto> <país> <cidade>
 * Formato de saida: airport <IDAeroporto>
 */
void adicionaAeroporto()
{
	Aeroporto a;

	leProximaPalavra(a.id);
	leProximaPalavra(a.pais);
	lePalavraAteFimDeLinha(a.cidade);

	if (aeroportoInvalido(a.id))
		printf("invalid airport ID\n");
	else if (_numAeroportos == MAX_NUM_AEROPORTOS)
		printf("too many airports\n");
	else if (encontraAeroporto(a.id) != NAO_EXISTE)
		printf("duplicate airport\n");
	else
	{
		strcpy(_aeroportos[_numAeroportos].id, a.id);
		strcpy(_aeroportos[_numAeroportos].pais, a.pais);
		strcpy(_aeroportos[_numAeroportos].cidade, a.cidade);
		_aeroportos[_numAeroportos].numVoos = 0;
		_numAeroportos++;
		printf("airport %s\n", a.id);
	}
}

/**
 * Comando 'l' - lista os aeroportos.
 * Se o comando for invocado sem argumentos, todos os
 * aeroportos são listados por ordem alfabética do código.
 * Se o comando for invocado com uma lista de identificadores de aeroportos, os
 * aeroportos são listados pela ordem dos respetivos identificadores no comando
 * Formato de entrada: l [<IDAeroporto> <IDAeroporto> ...]
 * Formato de saida: <IDAeroporto> <cidade> <país> #voos
 */
void listaAeroportos()
{
	char id[MAX_CODIGO_AEROPORTO];
	int indexAeroporto, ultima = 0;

	ultima = leProximaPalavra(id);
	if (strlen(id) == 0)
		listaTodosAeroportos();
	else
	{
		while (strlen(id) != 0)
		{
			indexAeroporto = encontraAeroporto(id);
			if (indexAeroporto == NAO_EXISTE)
				printf("%s: no such airport ID\n", id);
			else
				mostraAeroporto(indexAeroporto);
			if (!ultima)
				ultima = leProximaPalavra(id);
			else
				break;
		}
	}
}
/**
 * Comando 'v' - adiciona um voo ou lista todos os voos.
 * Formato de entrada: v [<códigoVoo> <IDAeroportoPartida> <IDAeroportoChegada>
 * <dataPartida> <horaPartida> <duração> <capacidade>]
 * Formato de saída: <códigoVoo> <IDAeroportoPartida> <IDAeroportoChegada>
 * <dataPartida> <horaPartida> (ou nada, se for criado um novo voo)
 *
 */
void adicionaListaVoos()
{
	Voo v;
	int i;

	if (leProximaPalavra(v.id))
	{
		for (i = 0; i < _numVoos; i++)
			mostraVoo(i);
		return;
	}
	else
	{
		leProximaPalavra(v.partida);
		leProximaPalavra(v.chegada);
		v.data = leData();
		v.hora = leHora();
		v.duracao = leHora();
		scanf("%d", &v.capacidade);
		leAteFimDeLinha();
	}

	if (validaVoo(v))
		criaVoo(v);
}

/**
 * Comando 'p' - lista os voos com partida de um aeroporto.
 * Formato de entrada: p <IDAeroporto>
 * Formato de saída: <códigoVoo> <IDAeroportoChegada> <dataPartida>
 * <horaPartida>
 */
void listaVoosPartida()
{
	int indexVoos[MAX_NUM_VOOS], i, n = 0;
	char partida[MAX_CODIGO_AEROPORTO];

	lePalavraAteFimDeLinha(partida);

	if (encontraAeroporto(partida) == NAO_EXISTE)
		printf("%s: no such airport ID\n", partida);

	for (i = 0; i < _numVoos; i++)
	{
		if (!strcmp(_voos[i].partida, partida))
			indexVoos[n++] = i;
	}

	bubbleSort(indexVoos, n, cmpVoosPartida);

	for (i = 0; i < n; i++)
		mostraVooPartida(indexVoos[i]);
}

/**
 * Comando 'c' - lista os voos com chegada a um aeroporto.
 * Formato de entrada: p <IDAeroporto>
 * Formato de saída: <códigoVoo> <IDAeroportoPartida> <dataChegada>
 * <horaChegada>
 */
void listaVoosChegada()
{
	int indexVoos[MAX_NUM_VOOS], i, n = 0;
	char chegada[MAX_CODIGO_AEROPORTO];

	lePalavraAteFimDeLinha(chegada);

	if (encontraAeroporto(chegada) == NAO_EXISTE)
		printf("%s: no such airport ID\n", chegada);

	for (i = 0; i < _numVoos; i++)
	{
		if (!strcmp(_voos[i].chegada, chegada))
			indexVoos[n++] = i;
	}

	bubbleSort(indexVoos, n, cmpVoosChegada);

	for (i = 0; i < n; i++)
		mostraVooChegada(indexVoos[i]);
}

/**
 * Comando 't' - avança a data do sistema.
 * Formato de entrada: t <data>
 * Formato de saída: <data> onde <data>
 */
void alteraData()
{
	Data d;

	d = leData();
	leAteFimDeLinha();
	if (validaData(d) == FALSE)
		printf("invalid date\n");
	else
	{
		_hoje = d;
		mostraData(_hoje);
		printf("\n");
	}
}

/**
 * Comando 'r' - adiciona uma reserva ou lista as reserva de um voo.
 * Formato de entrada: r <códigoVoo> <data>
 * [<códigoReserva> <númeroPassageiros>]
 * Formato de saída: <códigoReserva> <númeroPassageiros>
 */
void adicionaReserva()
{
	char idVoo[MAX_CODIGO_VOO], idReserva[MAX_CHAR];
	int numPassageiros;
	Data d;
	leProximaPalavra(idVoo);
	d = leData();
	if (leProximaPalavra(idReserva))
	{
		if (encontraVoo(idVoo, d) == NAO_EXISTE)
			printf(ERROR_FLIGHT_DOES_NOT_EXIST, idVoo);
		else if (validaData(d) == FALSE)
			printf(ERROR_INVALID_DATE);
		else
			print(cabeca, idVoo, d);
	}
	else
	{
		if (validaIdReserva(idReserva) == FALSE)
			printf(ERROR_INVALID_CODE);
		else if (encontraVoo(idVoo, d) == NAO_EXISTE)
			printf(ERROR_FLIGHT_DOES_NOT_EXIST, idVoo);
		else
		{
			scanf("%d", &numPassageiros);
			adicionaReservaAux(idReserva, idVoo, d, numPassageiros);
		}
	}
}

/**
 * Comando 'e' - elimina voos ou reserva.
 * Formato de entrada: e <código>
 * Formato de saída: nada
 */
void eliminaVoosReserva()
{
	char idVoo[MAX_CODIGO_VOO], idReserva[MAX_CHAR];
	leProximaPalavra(idReserva);
	if (strlen(idReserva) < MIN_IDRESERVA)
	{
		strcpy(idVoo, idReserva);
		if (encontraVooSemData(idVoo) == NAO_EXISTE)
			printf(ERROR_NOT_FOUND);
		else
		{
			cabeca = procuraApagaIDVoo(cabeca, idVoo);
			apagaVoo(idVoo);
		}
	}
	else
		apagaReserva(idReserva);
}

int main()
{
	int c;

	while ((c = getchar()) != EOF)
	{
		switch (c)
		{
		case 'q':
			apagaTodasReservas(cabeca);
			return 0;
		case 'a':
			adicionaAeroporto();
			break;
		case 'l':
			listaAeroportos();
			break;
		case 'v':
			adicionaListaVoos();
			break;
		case 'p':
			listaVoosPartida();
			break;
		case 'c':
			listaVoosChegada();
			break;
		case 't':
			alteraData();
			break;
		case 'r':
			adicionaReserva();
			break;
		case 'e':
			eliminaVoosReserva();
			break;
		default:
			break;
		}
	}

	return 0;
}
