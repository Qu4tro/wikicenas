#ifndef STRUCTS_H
#define STRUCTS_H

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <glib.h>
#include "tst.h"
#include "topN.h"

typedef unsigned int id_t;

typedef struct Colaborador{
    id_t id;
    id_t nContribuicoes;
    char* username;
}* Colaborador;

typedef struct Artigo {
    id_t id;
    char* titulo;

    size_t nBytes;
    size_t nPalavras;
}* Artigo;

typedef struct Revisao {
    id_t id;
    id_t idArtigo;
    char* timestamp;
}* Revisao;

typedef struct TCD_istruct {
    size_t artigosLidos;

    GHashTable* artigosHT;
    TTNode*     artigosTT;
    PriorityQueue artigosTopW;
    /* PriorityQueue artigosTopB; */

    GHashTable* colaboradoresHT;
    PriorityQueue colaboradoresTop;

    GHashTable* revisoesHT;

    /* pheap     colabs #nContribuicoes */
    /* pheap     artigo #nBytes */
    /* pheap     artigo #nWords */
}* TCD_istruct;


Artigo novoArtigo(int id, char* titulo);
void contagemArtigo(Artigo a, int nBytes, int nWords);
void inserirArtigo(Artigo a, TCD_istruct TCD);

Revisao novaRevisao(int id, int idArtigo, char* timestamp);
void inserirRevisao(Revisao r, TCD_istruct TCD);

Colaborador novoColaborador(int id, char* username);
void inserirContribuicao(Colaborador c1, id_t revisaoID, TCD_istruct TCD);

#endif
